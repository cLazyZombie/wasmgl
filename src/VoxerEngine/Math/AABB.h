#pragma once

#include "Vector3.h"

namespace VoxerEngine
{
	struct AABB
	{
		Vector3 MinPos;
		Vector3 MaxPos;

		AABB() = default;
		AABB(const Vector3& minPos, const Vector3& maxPos);

		bool Has(const Vector3& pos) const;
		float GetDistance(const Vector3& pos) const;
	};
}