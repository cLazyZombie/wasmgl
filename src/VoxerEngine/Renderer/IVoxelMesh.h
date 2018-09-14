#pragma once
#include "VoxelVertex.h"

namespace VoxerEngine
{
	class IVoxelMesh
	{
	public:
		virtual ~IVoxelMesh();

		virtual uint32_t AddVertex(const VoxelVertex& vertex) = 0;
		virtual void AddTriangle(uint32_t index1, uint32_t index2, uint32_t index3) = 0;
		virtual void Build() = 0;

		virtual void BindBuffer() = 0;
		virtual void Render() = 0;
	};
}