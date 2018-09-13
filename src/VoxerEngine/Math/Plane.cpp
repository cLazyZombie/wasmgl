#include "stdafx.h"
#include "Plane.h"
#include "Mathematics.h"

namespace VoxerEngine
{
	Plane::Plane(const Vector3& p1, const Vector3& p2, const Vector3& p3)
	{
		Vector3 edge1 = p2 - p1;
		Vector3 edge2 = p3 - p1;
		Dir = Vector3::Cross(edge1, edge2).Normalize();
		Distance = -Vector3::Dot(Dir, p1);
	}

	float Plane::GetDistance(const Vector3& pos) const
	{
		return Vector3::Dot(Vector3{ X, Y, Z }, pos) + Distance;
	}

	float Plane::GetDistance(const AABB& aabb) const
	{
		Vector3 ps[] = {
			{ aabb.MinPos.X, aabb.MinPos.Y, aabb.MinPos.Z },
			{ aabb.MinPos.X, aabb.MinPos.Y, aabb.MaxPos.Z },
			{ aabb.MinPos.X, aabb.MaxPos.Y, aabb.MinPos.Z },
			{ aabb.MinPos.X, aabb.MaxPos.Y, aabb.MaxPos.Z },
			{ aabb.MaxPos.X, aabb.MinPos.Y, aabb.MinPos.Z },
			{ aabb.MaxPos.X, aabb.MinPos.Y, aabb.MaxPos.Z },
			{ aabb.MaxPos.X, aabb.MaxPos.Y, aabb.MinPos.Z },
			{ aabb.MaxPos.X, aabb.MaxPos.Y, aabb.MaxPos.Z } };

		bool init = false;
		float pre = 10000000.0f;

		for (auto& p : ps)
		{
			float d = GetDistance(p);

			// intersect
			if (init && ((pre > 0.0f && d < 0.0f) || (pre < 0.0f && d > 0.0f)))
			{
				return 0.0f;
			}

			init = true;
			pre = Math::AbsMin(d, pre);
		}

		return pre;
	}
}