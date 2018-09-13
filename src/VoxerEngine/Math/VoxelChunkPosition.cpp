#include "stdafx.h"
#include "VoxelChunkPosition.h"

namespace VoxerEngine
{
	VoxelChunkPosition::VoxelChunkPosition() : X(0), Y(0), Z(0)
	{
	}

	VoxelChunkPosition::VoxelChunkPosition(int x, int y, int z) : X(x), Y(y), Z(z)
	{
	}
}