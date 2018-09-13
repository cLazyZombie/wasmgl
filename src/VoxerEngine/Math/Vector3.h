#pragma once
#include "Radian.h"

namespace VoxerEngine
{
	class Vector3
	{
	public:
		union
		{
			struct
			{
				float X;
				float Y;
				float Z;  
			}; 
			float V[3];
		};

	public:
		static const Vector3 ZeroVector;
		static const Vector3 ForwardVector;
		static const Vector3 RightVector;
		static const Vector3 UpVector;

	private:
		static const float NORMALIZE_EPSILON_SQ;	//  normalize������ �ּ� ������ ����

	public:
		Vector3(){}
		Vector3(float x, float y, float z);

		Vector3& Normalize();
		float Length() const;
		float LengthSquare() const;

		bool operator==(const Vector3& other) const;
		Vector3 operator+(const Vector3& other) const;
		Vector3 operator-(const Vector3& other) const;
		Vector3 operator*(float s) const;
		Vector3& operator*=(float s);
		Vector3& operator+=(const Vector3& other);
		Vector3 operator-() const;
		friend Vector3 operator*(float s, const Vector3& v);
		float& operator[](const int32_t index);
		const float& operator[](const int32_t index) const;

		static Vector3 Cross(const Vector3& lhs, const Vector3& rhs);
		static float Dot(const Vector3& l, const Vector3& r);
		Vector3& RotateX(Radian radian);	
		Vector3& RotateY(Radian radian);
		Vector3& RotateZ(Radian radian); 
		Vector3& RotateAxis(const Vector3& axis, Radian radian);

		wstring ToString() const;
	};

	Vector3 operator*(float s, const Vector3& v);
}