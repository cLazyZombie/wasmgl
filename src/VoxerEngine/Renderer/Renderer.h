#pragma once
#include "IRenderer.h"

namespace VoxerEngine
{
	class Renderer : public IRenderer
	{
	public:
		struct Info
		{
			int32 Width;
			int32 Height;
		};

	private:
		Info m_info;
		SDL_Window* m_sdl = nullptr;
		GLuint m_shaderProgram = 0;
		GLuint m_vertexShader = 0;
		GLuint m_fragmentShader = 0;
		
		vector<shared_ptr<IVoxelMesh>> m_voxelMeshes;

	public:
		Renderer(const Info& info);
		virtual ~Renderer();

		virtual void Add(shared_ptr<IVoxelMesh> voxelMesh) override;
		virtual void Draw(const CameraView& cameraView) override;
		virtual IVoxelMesh* CreateVoxelMesh() override;

	private:
		static void PrintShaderCompileStatus(GLuint shader);
		static void PrintProgramLinkStatus(GLuint program);
	};
}