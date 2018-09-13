#pragma once
#include "Radian.h"
#include "InnerAngle.h"
#include "RestrictedRadian.h"
#include "Vector3.h"

namespace VoxerEngine
{
	class PolarAngle
	{
	public:
		InnerAngle Horizon;
		RestrictedRadian Vertical;

	public:
		PolarAngle();
		PolarAngle(Radian horizon, Radian vertical);
		explicit PolarAngle(const Vector3& direction);

		wstring ToString() const;

		void RotateHorizon(Radian radian);
		void RotateVertical(Radian radian);

		Vector3 GetDirection() const;
		Vector3 GetRight() const;
		Vector3 GetUp() const;

		bool operator==(const PolarAngle& other) const;
		bool operator!=(const PolarAngle& other) const;
	};
}