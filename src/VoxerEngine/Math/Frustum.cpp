#include "stdafx.h"
#include "frustum.h"
#include "Mathematics.h"

namespace VoxerEngine
{
	Frustum::Frustum(const Vector3& pos, const Vector3& dir, const Vector3& up, float n, float f, Radian fov, float aspectRatio)
	{
		float tanFov = Math::Tan(fov * 0.5f);
		float nearHeight = n * tanFov;
		float nearWidth = nearHeight * aspectRatio;
		float farHeight = f * tanFov;
		float farWidth = farHeight * aspectRatio;

		Vector3 right = Vector3::Cross(up, dir).Normalize();
		Vector3 nearCenter = pos + dir * n;
		Vector3 farCenter = pos + dir * f;

		// get frustum vertex
		Vector3 nearTopLeft		= nearCenter + up * nearHeight - right * nearWidth;
		Vector3 nearTopRight	= nearCenter + up * nearHeight + right * nearWidth;
		Vector3 nearBottomLeft	= nearCenter - up * nearHeight - right * nearWidth;
		Vector3 nearBottomRight	= nearCenter - up * nearHeight + right * nearWidth;
		Vector3 farTopLeft		= farCenter + up * farHeight - right * farWidth;
		Vector3 farTopRight		= farCenter + up * farHeight + right * farWidth;
		Vector3 farBottomLeft	= farCenter - up * farHeight - right * farWidth;
		Vector3 farBottomRight	= farCenter - up * farHeight + right * farWidth;

		// near, far�� ���� ���Ҽ� ����
		float nearDistance = -Vector3::Dot(dir, nearCenter);
		Planes[NEAR_PLANE] = Plane{ dir, nearDistance };

		float farDistance = -Vector3::Dot(-dir, farCenter);
		Planes[FAR_PLANE] = Plane{ -dir, farDistance };

		// �������� vertex 3���� ����
	/*	Planes[TOP_PLANE]		= Plane(nearTopRight, nearTopLeft, farTopLeft);
		Planes[BOTTOM_PLANE]	= Plane(nearBottomLeft, nearBottomRight, farBottomRight);
		Planes[LEFT_PLANE]		= Plane(nearTopLeft, nearBottomLeft, farBottomLeft);
		Planes[RIGHT_PLANE]		= Plane(nearBottomRight, nearTopRight, farBottomRight);*/

		Planes[TOP_PLANE] = Plane(nearTopLeft, nearTopRight, farTopLeft);
		Planes[BOTTOM_PLANE] = Plane(nearBottomRight, nearBottomLeft, farBottomRight);
		Planes[LEFT_PLANE] = Plane(nearBottomLeft, nearTopLeft, farBottomLeft);
		Planes[RIGHT_PLANE] = Plane(nearTopRight, nearBottomRight, farBottomRight);
	}

	VoxerEngine::FrustumCheckResult Frustum::CheckPointInFrustum(const Vector3& pos)
	{
		bool intersected = false;
		for (const Plane& plane : Planes)
		{
			float d = plane.GetDistance(pos);
			if (d < 0.0f)
			{
				return FrustumCheckResult::OUTSIDE;
			}
			else if (d == 0.0f)
			{
				intersected = true;
			}
		}

		return intersected ? FrustumCheckResult::INTERSECT : FrustumCheckResult::INSIDE;
	}

	VoxerEngine::FrustumCheckResult Frustum::CheckSphereInFrustum(const Sphere& sphere)
	{
		bool intersected = false;
		for (const Plane& plane : Planes)
		{
			float d = plane.GetDistance(sphere.Pos);
			if (d < -sphere.R)
			{
				return FrustumCheckResult::OUTSIDE;
			}
			else if (d < sphere.R)
			{
				intersected = true;
			}
		}

		return intersected ? FrustumCheckResult::INTERSECT : FrustumCheckResult::INSIDE;
	}

	VoxerEngine::FrustumCheckResult Frustum::CheckAABBInFrustum(const AABB& aabb)
	{
		bool intersected = false;
		for (const Plane& plane : Planes)
		{
			float d = plane.GetDistance(aabb);
			if (d < 0.0f)
			{
				return FrustumCheckResult::OUTSIDE;
			}
			else if (d == 0.0f)
			{
				intersected = true;
			}
		}

		return intersected ? FrustumCheckResult::INTERSECT : FrustumCheckResult::INSIDE;
	}

}
