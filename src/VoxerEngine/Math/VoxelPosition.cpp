#include "stdafx.h"
#include "VoxelPosition.h"

namespace VoxerEngine
{
	VoxelPosition::VoxelPosition() : X(0), Y(0), Z(0)
	{
	}

	VoxelPosition::VoxelPosition(int32_t x, int32_t y, int32_t z) : X(x), Y(y), Z(z)
	{
	}

	bool VoxelPosition::operator==(const VoxelPosition& other) const
	{
		return X == other.X && Y == other.Y && Z == other.Z;
	}

	VoxelPosition VoxelPosition::operator+(const VoxelPosition& other) const
	{
		return VoxelPosition(X + other.X, Y + other.Y, Z + other.Z);
	}

	VoxelPosition VoxelPosition::operator-(const VoxelPosition& other) const
	{
		return VoxelPosition(X - other.X, Y - other.Y, Z - other.Z);
	}

	VoxelPosition VoxelPosition::GetNeighborPosition(Direction direction) const
	{
		switch(direction)
		{
		case Direction::Right:
			return VoxelPosition(X, Y+1, Z);

		case Direction::Left:
			return VoxelPosition(X, Y-1, Z);

		case Direction::Up:
			return VoxelPosition(X, Y, Z+1);

		case Direction::Down:
			return VoxelPosition(X, Y, Z-1);

		case Direction::Front:
			return VoxelPosition(X+1, Y, Z);

		case Direction::Back:
			return VoxelPosition(X-1, Y, Z);

		default:
			return VoxelPosition(X, Y, Z);
		}
	}

	std::wstring ToString(const VoxelPosition& pos)
	{
		wchar_t msg[1000];
		swprintf(msg, 1000, L"%d, %d, %d", pos.X, pos.Y, pos.Z);
		return wstring(msg);
	}

}