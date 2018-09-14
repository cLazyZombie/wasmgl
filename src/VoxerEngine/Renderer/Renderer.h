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
		
		vector<shared_ptr<IVoxelMesh>> m_voxelMeshesForAdd;
		vector<shared_ptr<IVoxelMesh>> m_voxelMeshesForRender;

		mutex m_mutex;
		condition_variable m_gameCV;
		condition_variable m_renderCV;
		bool m_started = true;
		bool m_terminated = false;
		CameraView m_cameraView;
		thread m_renderThread;

	public:
		Renderer(const Info& info);
		virtual ~Renderer();

		virtual void Start() override;
		virtual void Add(shared_ptr<IVoxelMesh> voxelMesh) override;
		virtual void PrepareRender(const CameraView& cameraView) override;
		virtual void Terminate() override;
		virtual IVoxelMesh* CreateVoxelMesh() override;

	private:
		void DoRender();
		void Render(IVoxelMesh* voxel);
	};
}