#include "stdafx.h"
#include "AABB.h"
#include "Mathematics.h"

namespace VoxerEngine
{
	AABB::AABB(const Vector3& minPos, const Vector3& maxPos)
		: MinPos(minPos), MaxPos(maxPos)
	{
	}

	bool AABB::Has(const Vector3& pos) const
	{
		if (pos.X < MinPos.X || pos.Y < MinPos.Y || pos.Z < MinPos.Z) return false;
		if (pos.X > MaxPos.X || pos.Y > MaxPos.Y || pos.Z > MaxPos.Z) return false;
		return true;
	}

	float AABB::GetDistance(const Vector3& pos) const
	{
		float dx = Math::Max(Math::Max(MinPos.X - pos.X, pos.X - MaxPos.X), 0.0f);
		float dy = Math::Max(Math::Max(MinPos.Y - pos.Y, pos.Y - MaxPos.Y), 0.0f);
		float dz = Math::Max(Math::Max(MinPos.Z - pos.Z, pos.Z - MaxPos.Z), 0.0f);

		return Math::Sqrt(dx * dx + dy * dy + dz * dz);
	}
}