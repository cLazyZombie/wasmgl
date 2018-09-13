#pragma once
#include "Radian.h"

namespace VoxerEngine
{
	// HalfAngle로 이름 수정
	// -0.5 PI to 0.5 PI
	class RestrictedRadian
	{
	public:
		Radian m_angle;

	public:
		RestrictedRadian(Radian angle);
		Radian GetAngle() const;
		operator Radian() const;

		bool operator == (const RestrictedRadian& other) const;
		bool operator != (const RestrictedRadian& other) const;
		RestrictedRadian& operator += (Radian other);
		RestrictedRadian& operator -= (Radian other);

		// test
		RestrictedRadian operator-() const;
	};
}