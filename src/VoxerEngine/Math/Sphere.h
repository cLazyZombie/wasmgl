#pragma once

#include "Vector3.h"

namespace VoxerEngine
{
	struct Sphere
	{
		Vector3 Pos;
		float R;

		inline Sphere() {}
		Sphere(const Vector3& pos, float r);

		float GetDistance(const Vector3& pos);
	};
}