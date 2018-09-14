#include "stdafx.h"
#include "Renderer.h"
#include "VoxelMesh.h"

namespace VoxerEngine
{
	Renderer::Renderer(const Info& info) :
		m_info(info)
	{
        SDL_CreateWindowAndRenderer(info.Width, info.Height, 0, &m_sdl, nullptr);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        const GLchar* vertexSource = 
            "#version 300 es\n"\
            "uniform mat4 VPMatrix;\n"\
			"uniform vec3 Offset;\n"\
            "attribute vec4 position;                       \n"\
            "attribute vec3 normal;                         \n"\
            "attribute vec2 uv;                             \n"\
			"varying vec3 oColor;                           \n"\
            "varying vec2 oUV;                              \n"\
			"//texture2D DiffuseTexture;\n"\
			"//sampler DiffuseSampler = sampler_state\n"\
			"//{\n"\
			"//	Texture = <DiffuseTexture>;\n"\
			"//};\n"\
			"void main()            \n"\
			"{\n"\
			"	float3 worldPosition = position + Offset;\n"\
			"	float4 projPosition = vec4(worldPosition, 1.0) * VPMatrix;\n"\
            "   gl_Position = projPosition;\n"\
            "   oColor.rgb = (vec3(1.0, 1.0, 1.0) * dot(normal, normalize(vec3(0.7. 0.3, 1.0))) + 1) * 0.5;\n"\
			"	oColor.a = 1.0;\n"\
			"	oUV = uv;\n"\
			"}\n";

        const GLchar* fragmentSource = 
            "#version 300 es                                \n"\
            "precision mediump float;                       \n"\
            "varying vec3 oColor;                           \n"\
            "varying vec2 oUV;                              \n"\
            "void main()                                    \n"\
            "{                                              \n"
            "  gl_FragColor = oColor;           \n"
            "}      \n";

        m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
        assert(m_vertexShader != 0);

        glShaderSource(m_vertexShader, 1, &vertexSource, nullptr);
        glCompileShader(m_vertexShader);
        assert(glGetError() == 0);

        m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        assert(m_fragmentShader != 0);

        glShaderSource(m_fragmentShader, 1, &fragmentSource, nullptr);
        glCompileShader(m_fragmentShader);
        assert(glGetError() == 0);

        m_shaderProgram = glCreateProgram();
        glAttachShader(m_shaderProgram, m_vertexShader);
        glAttachShader(m_shaderProgram, m_fragmentShader);
        glLinkProgram(m_shaderProgram);
        glUseProgram(m_shaderProgram);

        // Specify the layout of the vertex data
        GLint posAttrib = glGetAttribLocation(m_shaderProgram, "position");
        glEnableVertexAttribArray(posAttrib);
        glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(VoxelMesh), 0);

        GLint normalAttrib = glGetAttribLocation(m_shaderProgram, "normal");
        glEnableVertexAttribArray(normalAttrib);
        glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(VoxelMesh), (const GLvoid *)(3 * sizeof(GLfloat)));

        GLint uvAttrib = glGetAttribLocation(m_shaderProgram, "uv");
        glEnableVertexAttribArray(uvAttrib);
        glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(VoxelMesh), (const GLvoid *)(6 * sizeof(GLfloat)));
	}

	Renderer::~Renderer()
	{
    }
	void Renderer::Start()
	{
		m_renderThread = thread(&Renderer::DoRender, this);
	}

	void Renderer::Add(shared_ptr<IVoxelMesh> voxelMesh)
	{
		m_voxelMeshesForAdd.push_back(voxelMesh);
	}

	void Renderer::PrepareRender(const CameraView& cameraView)
	{
		unique_lock<mutex> locker(m_mutex);
		
		if (m_started == false)
		{
			m_gameCV.wait(locker);
		}

		m_started = false;

		m_cameraView = cameraView;
		m_voxelMeshesForRender = std::move(m_voxelMeshesForAdd);
		assert(m_voxelMeshesForAdd.size() == 0);

		m_renderCV.notify_all();
	}

	void Renderer::DoRender()
	{
		unique_lock<mutex> locker(m_mutex);

		while (true)
		{
			m_renderCV.wait(locker);
			if (m_terminated) break;

			m_started = true;

			// HRESULT hr;
			// hr = m_device->Clear(0, nullptr, D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0xff), 1.0f, 0);
			// assert(SUCCEEDED(hr));

			// hr = m_device->SetVertexDeclaration(m_voxelVertexDeclaration);
			// assert(SUCCEEDED(hr));

			// V(m_device->BeginScene());
			// V(m_voxelEffect->SetTechnique("Normal"));

			// auto projectionMatrix = Matrix::ProjectionMatrix(m_cameraView.Fov.value, (float)m_info.Width / m_info.Height, m_cameraView.Near, m_cameraView.Far);

			// auto viewProjectionMatrix = m_cameraView.ViewMatrix * projectionMatrix;

			// hr = m_voxelEffect->SetMatrix("VPMatrix", (D3DXMATRIX*)&viewProjectionMatrix);
			// assert(SUCCEEDED(hr));

			// if (m_texture)
			// {
			// 	hr = m_voxelEffect->SetTexture("DiffuseTexture", m_texture);
			// 	assert(SUCCEEDED(hr));
			// }

			// for (shared_ptr<IVoxelMesh>& voxelMesh : m_voxelMeshesForRender)
			// {
			// 	Render(voxelMesh.get());
			// }

			// hr = m_device->EndScene();
			// assert(SUCCEEDED(hr));

			// hr = m_device->Present(nullptr, nullptr, nullptr, nullptr);
			// assert(SUCCEEDED(hr));

			m_voxelMeshesForRender.clear();

			m_gameCV.notify_all();
		}
	}

	void Renderer::Terminate()
	{
		{
			unique_lock<mutex> locker(m_mutex);
			m_terminated = true;
			m_renderCV.notify_all();
		}

		if (m_renderThread.joinable())
		{
			m_renderThread.join();
		}
	}

	void Renderer::Render(IVoxelMesh* voxel)
	{
		voxel->BindBuffer();

		// // set vertex
		// hr = m_voxelEffect->Begin(&maxPass, 0);

		// assert(SUCCEEDED(hr));
		// for (UINT pass = 0; pass < maxPass; ++pass)
		// {
		// 	hr = m_voxelEffect->BeginPass(pass);
		// 	assert(SUCCEEDED(hr));

		// 	Vector3 offset = Vector3::ZeroVector;
		// 	hr = m_voxelEffect->SetValue("Offset", &offset, sizeof(offset));
		// 	assert(SUCCEEDED(hr));

		// 	hr = m_voxelEffect->CommitChanges();
		// 	assert(SUCCEEDED(hr));

		// 	voxel->Render();

		// 	m_voxelEffect->EndPass();
		// }

		// hr = m_voxelEffect->End();
		// assert(SUCCEEDED(hr));
	}

	IVoxelMesh* Renderer::CreateVoxelMesh()
	{
		return new VoxelMesh();
	}
}