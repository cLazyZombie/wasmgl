#pragma once
#include "Radian.h"

namespace VoxerEngine
{
	// -PI < r <= PI
	class InnerAngle
	{
	private:
		Radian angle;

	public:
		InnerAngle(Radian r);

		operator Radian() const;
		Radian GetAngle() const;
		InnerAngle operator-(const InnerAngle& other) const;
		InnerAngle operator+(const InnerAngle& other) const;
		bool operator<(const InnerAngle& other) const;
		bool operator>(const InnerAngle& other) const;
		bool operator<=(const InnerAngle& other) const;
		bool operator>=(const InnerAngle& other) const;
		bool operator==(const InnerAngle& other) const;
		InnerAngle& operator += (const InnerAngle& other);
		InnerAngle& operator -= (const InnerAngle& other);
	};
}