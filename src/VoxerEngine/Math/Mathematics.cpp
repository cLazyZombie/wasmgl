#include "stdafx.h"
#include "Mathematics.h"

namespace VoxerEngine
{
	const float Math::PiValue = 3.14159265359f;
	const Radian Math::RadianZero = Radian(0.0f);
	const Radian Math::PI = Radian(PiValue);
	const Radian Math::DoublePI = Radian(Math::PiValue * 2.0f);
	const Radian Math::HalfPI = Radian(Math::PiValue * 0.5f);
	const float Math::SquareRoot2 = 1.414213562373095f;
	const float Math::InverseSquareRoot2 = 1.0f / Math::SquareRoot2;
	const float Math::Epsilon = 0.001f;

	float Math::Max(float left, float right)
	{
		return left >= right ? left : right;
	}

	float Math::Min(float left, float right)
	{
		return left < right ? left : right;
	}

	float Math::AbsMin(float left, float right)
	{
		if (Absf(left) <= Absf(right)) return left;
		return right;
	}

	float Math::Clamp(float x, float min, float max)
	{
		x = Math::Max(x, min);
		return Math::Min(x, max);
	}

	Radian Math::MakeRadian0ToTwoPI(Radian radian)
	{
		if (radian == DoublePI) return Radian(0.0f);

		if (radian > DoublePI)
		{
			int32_t div = (int32_t)((radian / DoublePI).value);
			radian = Radian::Min(radian - Radian((float)div) * DoublePI, DoublePI);
			if (radian == DoublePI) return Radian(0.0f);
			return radian;
		}

		if (radian < RadianZero)
		{
			int32_t div = (int32_t)((-radian / DoublePI).value) + 1;
			return Radian::Max(radian + Radian((float)div) * DoublePI, RadianZero);
		}

		return radian;
	}

	Radian Math::MakeRadianInPI(Radian radian)
	{
		radian = MakeRadian0ToTwoPI(radian);
		if (radian > PI)
		{
			return Radian::Max(radian - DoublePI, -PI);
		}
		return Radian::Min(PI, radian);
	}

	Radian Math::GetAngleBetween(Radian radian1, Radian radian2)
	{
		Radian diff = radian1 - radian2;
		return MakeRadianInPI(diff);
	}

	Radian Math::DegreeToRadian(float degree)
	{
		return Radian(degree / 180.0f * PiValue);
	}

	int32_t Math::Abs(int32_t val)
	{
		return val >= 0 ? val : -val;
	}

	float Math::Absf(float val)
	{
		return val >= 0.0f ? val : -val;
	}

	float Math::Sin(Radian r)
	{
		return sin(r.value);
	}

	float Math::Cos(Radian r)
	{
		return cos(r.value);
	}

	float Math::Tan(Radian r)
	{
		return tan(r.value);
	}

	float Math::Sqrt(float v)
	{
		return sqrt(v);
	}

	Radian Math::ATan(float y, float x)
	{
		double theta = atan2(y, x);
		return Radian((float)theta);
	}

	int32_t Math::Floor(double v)
	{
		return (int32_t) floor(v);
	}
}