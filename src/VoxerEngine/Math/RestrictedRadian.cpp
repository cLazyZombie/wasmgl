#include "stdafx.h"
#include "RestrictedRadian.h"
#include "Mathematics.h"

namespace VoxerEngine
{
	RestrictedRadian::RestrictedRadian(Radian angle)
	{
		m_angle = Radian::Clamp(angle, -Math::HalfPI, Math::HalfPI);
	}

	Radian RestrictedRadian::GetAngle() const
	{
		return m_angle;
	}

	RestrictedRadian::operator Radian() const
	{
		return m_angle;
	}

	bool RestrictedRadian::operator == (const RestrictedRadian& other) const
	{
		return m_angle == other.m_angle;
	}

	bool RestrictedRadian::operator != (const RestrictedRadian& other) const
	{
		return m_angle != other.m_angle;
	}

	RestrictedRadian& RestrictedRadian::operator += (Radian other)
	{
		m_angle = Radian::Clamp(m_angle + other, -Math::HalfPI, Math::HalfPI);
		return *this;
	}

	RestrictedRadian& RestrictedRadian::operator -= (Radian other)
	{
		m_angle = Radian::Clamp(m_angle - other, -Math::HalfPI, Math::HalfPI);
		return *this;
	}

	RestrictedRadian RestrictedRadian::operator-() const
	{
		return RestrictedRadian(-m_angle);
	}
}