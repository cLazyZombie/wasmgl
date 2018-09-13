#pragma once
#include "Direction.h"

namespace VoxerEngine
{
	struct LocalVoxelPosition
	{
		int32_t X;
		int32_t Y; 
		int32_t Z;

		LocalVoxelPosition();
		LocalVoxelPosition(int32_t x, int32_t y, int32_t z);
		LocalVoxelPosition GetNeighborPosition(Direction direction) const;
		LocalVoxelPosition operator+(const LocalVoxelPosition& other) const;
		vector<Direction> GetSurfacse() const;
	};
}