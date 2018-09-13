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
			HWND WindowHandle;
		};

	private:
		Info m_info;
		IDirect3D9* m_direct3d = nullptr;
		IDirect3DDevice9* m_device = nullptr;
		
		IDirect3DVertexDeclaration9* m_voxelVertexDeclaration = nullptr;
		ID3DXEffect* m_voxelEffect = nullptr;

		IDirect3DVertexBuffer9* m_pVoxelVB = nullptr;
		IDirect3DIndexBuffer9* m_pVoxelIB = nullptr;

		vector<shared_ptr<IVoxelMesh>> m_voxelMeshesForAdd;
		vector<shared_ptr<IVoxelMesh>> m_voxelMeshesForRender;

		IDirect3DTexture9* m_texture = nullptr;

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
		virtual void Terminate();
		virtual IVoxelMesh* CreateVoxelMesh() override;

	private:
		void DoRender();
		void Render(IVoxelMesh* voxel);
	};
}