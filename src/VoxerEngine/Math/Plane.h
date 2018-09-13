#pragma once

#include "Vector3.h"
#include "AABB.h"

namespace VoxerEngine
{
	struct Plane
	{
		union 
		{
			struct {
				float X;
				float Y;
				float Z;
			};

			Vector3 Dir;
		};
		
		float Distance;

		inline Plane() {}
		inline Plane(float x, float y, float z, float d) : X(x), Y(y), Z(z), Distance(d) {}
		inline Plane(const Vector3& dir, float distance) : Dir(dir), Distance(distance) {}
		Plane(const Vector3& p1, const Vector3& p2, const Vector3& p3);
		float GetDistance(const Vector3& pos) const;
		float GetDistance(const AABB& aabb) const;
	};
}