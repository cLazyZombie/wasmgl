#pragma once
#include "Vector3.h"
#include "Radian.h"
#include "VoxelPosition.h"

namespace VoxerEngine
{
	class Math
	{
	public:
		static const float PiValue;
		static const Radian RadianZero;
		static const Radian PI;
		static const Radian DoublePI;
		static const Radian HalfPI;
		static const float SquareRoot2;
		static const float InverseSquareRoot2;
		static const float Epsilon;

		static float Max(float left, float right);
		static float Min(float left, float right);
		static float AbsMin(float left, float right);

		static float Clamp(float x, float min, float max);

		// 0 <= result < 2*PI
		static Radian MakeRadian0ToTwoPI(Radian radian);

		// -PI < result <= PI
		static Radian MakeRadianInPI(Radian radian);

		// -PI~PI
		static Radian GetAngleBetween(Radian radian1, Radian radian2);

		static Radian DegreeToRadian(float degree);

		static int32_t Abs(int32_t val);
		static float Absf(float val);

		static float Sin(Radian r);
		static float Cos(Radian r);
		static float Tan(Radian r);
		static float Sqrt(float v);
		static Radian ATan(float y, float x);

		static int32_t Floor(double v);
	};
}