#pragma once
#include "Direction.h"

namespace VoxerEngine
{
	// world ��ġ
	struct VoxelPosition
	{
		int32_t X;
		int32_t Y;
		int32_t Z;

		VoxelPosition();
		VoxelPosition(int32_t x, int32_t y, int32_t z);
		bool operator==(const VoxelPosition& other) const;

		// test
		VoxelPosition operator+(const VoxelPosition& other) const;
		VoxelPosition operator-(const VoxelPosition& other) const;
		VoxelPosition GetNeighborPosition(Direction direction) const;
	};

	wstring ToString(const VoxelPosition& pos);
}