#pragma once

#include "IVoxelMesh.h"
#include "Math/CameraView.h"

namespace VoxerEngine 
{
    class IRenderer
    {
    public:
        virtual ~IRenderer();

        virtual void Add(shared_ptr<IVoxelMesh> voxelMesh)=0;
        virtual void Draw(const CameraView& cameraView)=0;

        virtual IVoxelMesh* CreateVoxelMesh() = 0;
    };
}