#pragma once

#include "Vector3.h"

namespace VoxerEngine
{
	class Matrix
	{
	public:
		union {
			struct {
				float        _11, _12, _13, _14;
				float        _21, _22, _23, _24;
				float        _31, _32, _33, _34;
				float        _41, _42, _43, _44;

			};
			float m[4][4];
		};

	public:
		static const Matrix IdentityMatrix;
		static const Matrix ZeroMatrix;

	public:
		Matrix();
		Matrix(float m11, float m12, float m13, float m14,
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44);

		Matrix& Identity();
		Matrix& Translate(const Vector3& v);

		float& operator()(int32 row, int32 column);
		float operator() (int32 row, int32 column) const;
		Matrix operator* (const Matrix& other) const;
		void Inverse();
		Vector3 RotateDirection(const Vector3& v) const;
		Vector3 RotatePosition(const Vector3& v) const;
		Vector3 TransformVector3(const Vector3& v) const;

		wstring ToString() const;

	public:
		static Matrix ViewMatrix(const Vector3& from, const Vector3& at, const Vector3& up);
		static Matrix ProjectionMatrix(float fov, float ratio, float nearZ, float farZ);
		static Matrix Inverse(const Matrix& m);
	};
}