#include "stdafx.h"
#include "InnerAngle.h"
#include "Mathematics.h"

namespace VoxerEngine
{
	InnerAngle::InnerAngle(Radian r)
	{
		angle = Math::MakeRadianInPI(r);
	}

	InnerAngle::operator Radian() const
	{
		return angle;
	}

	Radian InnerAngle::GetAngle() const
	{
		return angle;
	}

	InnerAngle InnerAngle::operator-(const InnerAngle& other) const
	{
		return InnerAngle(angle - other.angle);
	}

	InnerAngle InnerAngle::operator+(const InnerAngle& other) const
	{
		return InnerAngle(angle + other.angle);
	}

	bool InnerAngle::operator<(const InnerAngle& other) const
	{
		return angle < other.angle;
	}

	bool InnerAngle::operator>(const InnerAngle& other) const
	{
		return angle > other.angle;
	}

	bool InnerAngle::operator<=(const InnerAngle& other) const
	{
		return angle <= other.angle;
	}

	bool InnerAngle::operator>=(const InnerAngle& other) const
	{
		return angle >= other.angle;
	}

	bool InnerAngle::operator==(const InnerAngle& other) const
	{
		return angle == other.angle;
	}

	InnerAngle& InnerAngle::operator+=(const InnerAngle& other)
	{
		angle = Math::MakeRadianInPI(angle + other.angle);
		return *this;
	}
	
	InnerAngle& InnerAngle::operator-=(const InnerAngle& other)
	{
		angle = Math::MakeRadianInPI(angle - other.angle);
		return *this;
	}
}