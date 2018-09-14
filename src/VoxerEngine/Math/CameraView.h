#pragma once

#include "Vector3.h"
#include "Frustum.h"
#include "Matrix.h"

namespace VoxerEngine
{
	struct CameraView
	{
		Vector3 Pos;
		Vector3 Dir;
		Vector3 Up;
		float Near;
		float Far;
		Radian Fov;
		float Aspect;
		Matrix ViewMatrix;

		Frustum GetFrustum() const;
	};
}