#include "stdafx.h"
#include "PolarAngle.h"
#include "Mathematics.h"

namespace VoxerEngine
{
	PolarAngle::PolarAngle()
		: Horizon(0), Vertical(0)
	{
	}

	PolarAngle::PolarAngle(Radian horizon, Radian vertical)
		: Horizon(horizon), Vertical(vertical)
	{
	}

	PolarAngle::PolarAngle(const Vector3& direction)
		: Horizon(atan2(direction.Y, direction.X)), Vertical(asin(direction.Z))
	{
	}

	wstring PolarAngle::ToString() const
	{
		wchar_t str[100];
		swprintf(str, 100, L"Horizon: %f, Vertical: %f", Horizon.GetAngle().value, Vertical.GetAngle().value);
		return wstring(str);
	}

	bool PolarAngle::operator==(const PolarAngle& other) const
	{
		return Horizon == other.Horizon && Vertical == other.Vertical;
	}

	bool PolarAngle::operator!=(const PolarAngle& other) const
	{
		return !(operator==(other));
	}

	void PolarAngle::RotateHorizon(Radian radian)
	{
		Horizon += radian;
	}

	void PolarAngle::RotateVertical(Radian radian)
	{
		Vertical += radian;
	}

	Vector3 PolarAngle::GetDirection() const
	{
		Vector3 base (1, 0, 0);
		base.RotateY(-Vertical);
		base.RotateZ(Horizon);

		return base;
	}

	Vector3 PolarAngle::GetRight() const
	{
		Vector3 base (0, 1, 0);
		base.RotateZ(Horizon);

		return base;
	}

	Vector3 PolarAngle::GetUp() const
	{
		Vector3 base (0, 0, 1);
		base.RotateY(-Vertical);
		base.RotateZ(Horizon);

		return base;
	}
}