#include "stdafx.h"
#include "Sphere.h"

namespace VoxerEngine
{
	Sphere::Sphere(const Vector3& pos, float r)
		: Pos(pos), R(r)
	{
	}

	float Sphere::GetDistance(const Vector3& pos)
	{
		float leng = (Pos - pos).Length() - R;
		if (leng <= 0.0f) return 0.0f;

		return leng;
	}
}


