#include "stdafx.h"
#include "Renderer.h"
#include "VoxelMesh.h"

namespace VoxerEngine
{
	Renderer::Renderer(const Info& info) :
		m_info(info)
	{
        const GLchar* vertexSource = 
			"#version 300 es                                \n"\
			"layout(location = 0) in vec3 position;                       \n"\
            "layout(location = 1) in vec3 normal;                         \n"\
            "layout(location = 2) in vec2 uv;                             \n"\
            "uniform mat4 VPMatrix;\n"\
			"uniform vec3 Offset;\n"\
			"out vec4 oColor;                           \n"\
            "out vec2 oUV;                              \n"\
			"//texture2D DiffuseTexture;\n"\
			"//sampler DiffuseSampler = sampler_state\n"\
			"//{\n"\
			"//	Texture = <DiffuseTexture>;\n"\
			"//};\n"\
			"void main()            \n"\
			"{\n"\
			"	vec3 worldPosition = position + Offset;\n"\
			"	vec4 projPosition = vec4(worldPosition, 1.0) * VPMatrix;\n"\
            "   gl_Position = projPosition;\n"\
            "   oColor.rgb = (vec3(1.0, 1.0, 1.0) * dot(normal, normalize(vec3(0.7, 0.3, 1.0))) + 1.0) * 0.5;\n"\
			"	oColor.a = 1.0;\n"\
			"	oUV = uv;\n"\
			"}\n";

        const GLchar* fragmentSource = 
            "#version 300 es                                \n"\
            "precision mediump float;                       \n"\
            "in vec4 oColor;                           \n"\
            "in vec2 oUV;                              \n"\
			"out vec4 fragmentColor;						\n"\
            "void main()                                    \n"\
            "{                                              \n"
            "  fragmentColor = oColor;           \n"
            "}      \n";

        m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(m_vertexShader, 1, &vertexSource, nullptr);
        glCompileShader(m_vertexShader);
		PrintShaderCompileStatus(m_vertexShader);

        m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(m_fragmentShader, 1, &fragmentSource, nullptr);
        glCompileShader(m_fragmentShader);
		PrintShaderCompileStatus(m_fragmentShader);

        m_shaderProgram = glCreateProgram();
        glAttachShader(m_shaderProgram, m_vertexShader);
        glAttachShader(m_shaderProgram, m_fragmentShader);
        glLinkProgram(m_shaderProgram);
		PrintProgramLinkStatus(m_shaderProgram);

        glUseProgram(m_shaderProgram);

        // // Specify the layout of the vertex data
        // //GLint posAttrib = glGetAttribLocation(m_shaderProgram, "position");
        // glEnableVertexAttribArray(0);
        // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VoxelMesh), 0);

        // //GLint normalAttrib = glGetAttribLocation(m_shaderProgram, "normal");
        // glEnableVertexAttribArray(1);
        // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VoxelMesh), (const GLvoid *)(3 * sizeof(GLfloat)));

        // //GLint uvAttrib = glGetAttribLocation(m_shaderProgram, "uv");
        // glEnableVertexAttribArray(2);
        // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VoxelMesh), (const GLvoid *)(6 * sizeof(GLfloat)));

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClearDepthf(1.0f);
		glClearStencil(0);
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

        	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			auto projectionMatrix = Matrix::ProjectionMatrix(m_cameraView.Fov.value, (float)m_info.Width / m_info.Height, m_cameraView.Near, m_cameraView.Far);
			auto viewProjectionMatrix = m_cameraView.ViewMatrix * projectionMatrix;

			GLint vpMatrixPos = glGetUniformLocation(m_shaderProgram, "VPMatrix");
			glUniformMatrix4fv(vpMatrixPos, 1, GL_FALSE, (GLfloat *)&viewProjectionMatrix);

			// if (m_texture)
			// {
			// 	hr = m_voxelEffect->SetTexture("DiffuseTexture", m_texture);
			// 	assert(SUCCEEDED(hr));
			// }

			for (shared_ptr<IVoxelMesh>& voxelMesh : m_voxelMeshesForRender)
			{
			 	Render(voxelMesh.get());
			}

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

	 void Renderer::PrintShaderCompileStatus(GLuint shader)
	 {
		GLint param;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &param);
		if (param != GL_TRUE)
		{
			GLsizei len;
			GLchar log[1000];
			glGetShaderInfoLog(shader, 1000, &len, (GLchar*)log);
			printf("compile error: %s\n", log);
		}
	 }

	 void Renderer::PrintProgramLinkStatus(GLuint program)
	 {
		GLint param;
		glGetProgramiv(program, GL_LINK_STATUS, &param);
		if (param != GL_TRUE)
		{
			GLsizei len;
			GLchar log[1000];
			glGetProgramInfoLog(program, 1000, &len, (GLchar*)log);
			printf("link error: %s\n", log);
		}
	 }
}