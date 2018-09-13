#pragma once

#include "Direction.h"

namespace VoxerEngine
{
	struct ChunkPosition
	{
		int32_t X;
		int32_t Y;
		int32_t Z;

		ChunkPosition();
		ChunkPosition(int32_t x, int32_t y, int32_t z);

		ChunkPosition GetNeighborPos(Direction dir) const;
	};

	inline bool const operator==(const ChunkPosition& l, const ChunkPosition& r) 
	{
		return l.X == r.X && l.Y == r.Y && l.Z == r.Z;
	}

	inline bool const operator!=(const ChunkPosition& l, const ChunkPosition& r) 
	{
		return !(l == r);
	}

	inline bool const operator<(const ChunkPosition& l, const ChunkPosition& r) 
	{
		if (l.X < r.X)  return true;
		if (l.X > r.X)  return false;

		if (l.Y < r.Y)  return true;
		if (l.Y > r.Y)  return false;

		if (l.Z < r.Z)  return true;
		if (l.Z > r.Z)  return false;

		return false;
	}

	struct ChunkPositionHash
	{
		size_t operator()(const ChunkPosition& c) const
		{
			return c.X ^ (c.Y > 0 ? c.Y : -c.Y) << 11 ^ (c.Z > 0 ? c.Z : -c.Z) << 22;
		}
	};

	struct ChunkPositionEqual
	{
		bool operator()(const ChunkPosition& l, const ChunkPosition& r) const
		{
			return l.X == r.X && l.Y == r.Y && l.Z == r.Z;
		}
	};
}