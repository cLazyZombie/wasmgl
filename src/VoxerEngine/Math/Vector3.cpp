#include "stdafx.h"
#include "Vector3.h"
#include "Matrix.h"
#include "Mathematics.h"

namespace VoxerEngine
{
	const Vector3 Vector3::ZeroVector{ 0.0f, 0.0f, 0.0f };
	const Vector3 Vector3::ForwardVector{ 1.0f, 0.0f, 0.0f };
	const Vector3 Vector3::RightVector{ 0.0f, 1.0f, 0.0f };
	const Vector3 Vector3::UpVector{ 0.0f, 0.0f, 1.0f };
	const float Vector3::NORMALIZE_EPSILON_SQ = 0.01f;

	Vector3::Vector3(float x, float y, float z)
		: X(x), Y(y), Z(z)
	{
	}

	Vector3& Vector3::Normalize()
	{
		float lengSq = X * X + Y * Y + Z * Z;
		if (lengSq < NORMALIZE_EPSILON_SQ)
		{
			fprintf(stderr, "[Vector3::Normalize()] error. lengSq: %f\n", lengSq);
			return *this;
		}

		float leng = Math::Sqrt(lengSq);

		X /= leng;
		Y /= leng;
		Z /= leng;

		return *this;
	}

	float Vector3::Length() const
	{
		float lengSq = X * X + Y * Y + Z * Z;
		return Math::Sqrt(lengSq);
	}

	float Vector3::LengthSquare() const
	{
		return X * X + Y * Y + Z * Z;
	}

	float& Vector3::operator[](const int32 index)
	{
		return V[index];
	}

	const float& Vector3::operator[](const int32 index) const
	{
		return V[index];
	}

	Vector3 Vector3::Cross(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 cross;
		cross.X = lhs.Y * rhs.Z - lhs.Z * rhs.Y;
		cross.Y = lhs.Z * rhs.X - lhs.X * rhs.Z;
		cross.Z = lhs.X * rhs.Y - lhs.Y * rhs.X;

		return cross;
	}

	float  Vector3::Dot(const Vector3& lhs, const Vector3& rhs)
	{
		return lhs.X * rhs.X + lhs.Y * rhs.Y + lhs.Z * rhs.Z;
	}

	bool Vector3::operator==(const Vector3& other) const
	{
		return X == other.X && Y == other.Y && Z == other.Z;
	}

	Vector3 Vector3::operator+(const Vector3& other) const
	{
		return Vector3(X + other.X, Y + other.Y, Z + other.Z);
	}

	Vector3& Vector3::operator+=(const Vector3& other)
	{
		*this = *this + other;
		return *this;
	}

	Vector3 Vector3::operator-(const Vector3& other) const
	{
		return Vector3(X - other.X, Y - other.Y, Z - other.Z);
	}

	Vector3 Vector3::operator*(float s) const
	{
		return Vector3(X * s, Y * s, Z * s);
	}

	Vector3& Vector3::operator*=(float s)
	{
		*this = *this * s;
		return *this;
	}

	Vector3 operator*(float s, const Vector3& v)
	{
		return v * s;
	}

	Vector3 Vector3::operator-() const
	{
		return Vector3(-X, -Y, -Z);
	}

	Vector3& Vector3::RotateX(Radian radian)
	{
		float cosine = Math::Cos(radian.value);	// Radian으로 옮기자
		float sine = Math::Sin(radian.value);		// Radian으로 옮기자

		auto newZ = Z * cosine + Y * sine;
		auto newY = Y * cosine - Z * sine;
		Z = newZ;
		Y = newY;

		return *this;
	}

	Vector3& Vector3::RotateY(Radian radian)
	{
		float cosine = Math::Cos(radian.value);
		float sine = Math::Sin(radian.value);
		auto newX = X * cosine + Z * sine;
		auto newZ = Z * cosine - X * sine;
		X = newX;
		Z = newZ;

		return *this;
	}

	Vector3& Vector3::RotateZ(Radian radian)
	{
		float cosine = Math::Cos(radian.value);
		float sine = Math::Sin(radian.value);

		auto newX = X * cosine - Y * sine;
		auto newY = Y * cosine + X * sine;
		X = newX;
		Y = newY;

		return *this;
	}
	
	Vector3& Vector3::RotateAxis(const Vector3& axis, Radian radian)
	{
		float cosR = Math::Cos(radian.value);
		float sinR = Math::Sin(radian.value);
		float t = 1 - cosR;

		//Matrix m {
		//	cosR + t * axis.X * axis.X, t * axis.X * axis.Y - sinR * axis.Z, t * axis.X * axis.Z + sinR * axis.Y, 0.0f,
		//	t * axis.X * axis.Y + sinR * axis.Z, t * axis.Y * axis.Y + cosR, t * axis.Y * axis.Z - sinR * axis.X, 0.0f,
		//	t * axis.X * axis.Z - sinR * axis.Y, t * axis.Y * axis.Z + sinR * axis.X, t * axis.Z * axis.Z + cosR, 0.0f,
		//	0.0f, 0.0f, 0.0f, 1.0f
		//};

		Matrix m{
			cosR + t * axis.X * axis.X, t * axis.X * axis.Y + sinR * axis.Z, t * axis.X * axis.Z - sinR * axis.Y, 0.0f,
			t * axis.X * axis.Y - sinR * axis.Z , t * axis.Y * axis.Y + cosR,  t * axis.Y * axis.Z + sinR * axis.X, 0.0f,
			t * axis.X * axis.Z + sinR * axis.Y,t * axis.Y * axis.Z - sinR * axis.X, t * axis.Z * axis.Z + cosR, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		*this = m.RotatePosition(*this);
		return *this;
	}

	std::wstring Vector3::ToString() const
	{
		wchar_t str[300];
		swprintf(str, 300, L"v3{%f %f %f}", X, Y, Z);

		return wstring(str);
	}

}