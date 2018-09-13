#include "stdafx.h"
#include "ChunkPosition.h"

namespace VoxerEngine
{
	ChunkPosition::ChunkPosition() : X(0), Y(0), Z(0)
	{
	}

	ChunkPosition::ChunkPosition(int32_t x, int32_t y, int32_t z) : X(x), Y(y), Z(z)
	{
	}

	VoxerEngine::ChunkPosition ChunkPosition::GetNeighborPos(Direction dir) const
	{
		switch (dir)
		{
		case Direction::Front:
			return ChunkPosition{ X + 1, Y, Z };

		case Direction::Back:
			return ChunkPosition{ X - 1, Y, Z };

		case Direction::Left:
			return ChunkPosition{ X, Y - 1, Z };

		case Direction::Right:
			return ChunkPosition{ X, Y + 1, Z };

		case Direction::Up:
			return ChunkPosition{ X, Y , Z + 1};

		case Direction::Down:
			return ChunkPosition{ X, Y , Z - 1 };

		default:
			assert(0);
			return *this;
		}
	}

}