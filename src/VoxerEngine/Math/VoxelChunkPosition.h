#pragma once

namespace VoxerEngine
{
	// chunk ���� ��ġ
	struct VoxelChunkPosition
	{
		int X;
		int Y; 
		int Z;

		VoxelChunkPosition();
		VoxelChunkPosition(int x, int y, int z);
	};
}