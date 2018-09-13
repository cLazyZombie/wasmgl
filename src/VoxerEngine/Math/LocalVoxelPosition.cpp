#include "stdafx.h"
#include "LocalVoxelPosition.h"

namespace VoxerEngine
{
	LocalVoxelPosition::LocalVoxelPosition() : X(0), Y(0), Z(0) 
	{
	}

	LocalVoxelPosition::LocalVoxelPosition(int32_t x, int32_t y, int32_t z) : X(x), Y(y), Z(z) 
	{
	}

	LocalVoxelPosition LocalVoxelPosition::GetNeighborPosition(Direction direction) const
	{
		switch(direction)
		{
		case Direction::Right:
			return LocalVoxelPosition(X, Y+1, Z);

		case Direction::Left:
			return LocalVoxelPosition(X, Y-1, Z);

		case Direction::Up:
			return LocalVoxelPosition(X, Y, Z+1);

		case Direction::Down:
			return LocalVoxelPosition(X, Y, Z-1);

		case Direction::Front:
			return LocalVoxelPosition(X+1, Y, Z);

		case Direction::Back:
			return LocalVoxelPosition(X-1, Y, Z);

		default:
			return LocalVoxelPosition(X, Y, Z);
		}
	}

	LocalVoxelPosition LocalVoxelPosition::operator+(const LocalVoxelPosition& other) const
	{
		return LocalVoxelPosition(X + other.X, Y + other.Y, Z + other.Z);
	}

	vector<Direction> LocalVoxelPosition::GetSurfacse() const
	{
		vector<Direction> surfaceDirs;

		if (X == 0) surfaceDirs.push_back(Direction::Back);
		if (X == VOXEL_IN_CHUNK_XY - 1) surfaceDirs.push_back(Direction::Front);

		if (Y == 0) surfaceDirs.push_back(Direction::Left);
		if (Y == VOXEL_IN_CHUNK_XY - 1) surfaceDirs.push_back(Direction::Right);

		if (Z == 0) surfaceDirs.push_back(Direction::Down);
		if (Z == VOXEL_IN_CHUNK_Z - 1) surfaceDirs.push_back(Direction::Up);

		return surfaceDirs;
	}

}