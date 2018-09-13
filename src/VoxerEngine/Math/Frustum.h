#pragma once

#include "Vector3.h"
#include "Plane.h"
#include "Sphere.h"
#include "AABB.h"

namespace VoxerEngine
{
	enum class FrustumCheckResult : uint8_t
	{
		INSIDE,
		INTERSECT,
		OUTSIDE,
	};

	struct Frustum
	{
		Plane Planes[6];

		enum {
			TOP_PLANE = 0,
			BOTTOM_PLANE,
			LEFT_PLANE,
			RIGHT_PLANE,
			NEAR_PLANE,
			FAR_PLANE,
		};

		// fov: 상하 각도
		// aspectRatio: width / height
		Frustum(const Vector3& pos, const Vector3& dir, const Vector3& up, float n, float f, Radian fov, float aspectRatio); 

		FrustumCheckResult CheckPointInFrustum(const Vector3& pos);
		FrustumCheckResult CheckSphereInFrustum(const Sphere& sphere);
		FrustumCheckResult CheckAABBInFrustum(const AABB& sphere);
	};
}
