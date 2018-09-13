#pragma once

#include "Vector3.h"
#include "AABB.h"
#include "Direction.h"

namespace VoxerEngine
{
	struct Ray
	{
		Vector3 Pos;
		Vector3 Dir;
		float Distance;

		Ray(const Vector3& pos, const Vector3& dir, float distance = 30000.0f);

		bool Intersect(const AABB& aabb, bool checkInside = false, float* hitDistance = nullptr, Direction* hitDir = nullptr) const;
	};
}