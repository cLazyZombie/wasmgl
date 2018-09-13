#pragma once

namespace VoxerEngine
{
	// chunk 내부 위치
	struct VoxelChunkPosition
	{
		int X;
		int Y; 
		int Z;

		VoxelChunkPosition();
		VoxelChunkPosition(int x, int y, int z);
	};
}