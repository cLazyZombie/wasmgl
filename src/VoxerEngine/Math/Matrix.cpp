#include "stdafx.h"
#include "Matrix.h"


namespace VoxerEngine
{
	const Matrix Matrix::IdentityMatrix{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	const Matrix Matrix::ZeroMatrix{
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	};

	Matrix::Matrix()
	{
	}

	Matrix::Matrix(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
		: _11(m11), _12(m12), _13(m13), _14(m14),
		_21(m21), _22(m22), _23(m23), _24(m24),
		_31(m31), _32(m32), _33(m33), _34(m34),
		_41(m41), _42(m42), _43(m43), _44(m44)
	{
	}

	Matrix& Matrix::Identity()
	{
		for (int32 i = 0; i < 4; ++i)
		{
			for (int32 j = 0; j < 4; ++j)
			{
				if (i == j) m[i][j] = 1.0f;
				else m[i][j] = 0.0f;
			}
		}
		return *this;
	}

	Matrix& Matrix::Translate(const Vector3& v)
	{
		_41 += v.X;
		_42 += v.Y;
		_43 += v.Z;

		return *this;
	}

	float& Matrix::operator() (int32 row, int32 column)
	{
		return m[row][column];
	}

	float Matrix::operator() (int32 row, int32 column) const
	{
		return m[row][column];
	}

	Matrix Matrix::operator* (const Matrix& other) const
	{
		Matrix result;
		result._11 = _11 * other._11 + _12 * other._21 + _13 * other._31 + _14 * other._41;
		result._12 = _11 * other._12 + _12 * other._22 + _13 * other._32 + _14 * other._42;
		result._13 = _11 * other._13 + _12 * other._23 + _13 * other._33 + _14 * other._43;
		result._14 = _11 * other._14 + _12 * other._24 + _13 * other._34 + _14 * other._44;

		result._21 = _21 * other._11 + _22 * other._21 + _23 * other._31 + _24 * other._41;
		result._22 = _21 * other._12 + _22 * other._22 + _23 * other._32 + _24 * other._42;
		result._23 = _21 * other._13 + _22 * other._23 + _23 * other._33 + _24 * other._43;
		result._24 = _21 * other._14 + _22 * other._24 + _23 * other._34 + _24 * other._44;

		result._31 = _31 * other._11 + _32 * other._21 + _33 * other._31 + _34 * other._41;
		result._32 = _31 * other._12 + _32 * other._22 + _33 * other._32 + _34 * other._42;
		result._33 = _31 * other._13 + _32 * other._23 + _33 * other._33 + _34 * other._43;
		result._34 = _31 * other._14 + _32 * other._24 + _33 * other._34 + _34 * other._44;

		result._41 = _41 * other._11 + _42 * other._21 + _43 * other._31 + _44 * other._41;
		result._42 = _41 * other._12 + _42 * other._22 + _43 * other._32 + _44 * other._42;
		result._43 = _41 * other._13 + _42 * other._23 + _43 * other._33 + _44 * other._43;
		result._44 = _41 * other._14 + _42 * other._24 + _43 * other._34 + _44 * other._44;

		return result;
	}

	Matrix Matrix::ViewMatrix(const Vector3& from, const Vector3& at, const Vector3& up)
	{
		Vector3 forward = (at - from).Normalize();
		Vector3 realUp = up;

		Vector3 right = Vector3::Cross(realUp, forward);

		for (int32 i = 0; right.LengthSquare() < 0.01f && i < 3; ++i)
		{
			realUp = Vector3::ZeroVector;
			realUp[i] = 1.0f;
			right = Vector3::Cross(realUp, forward);
		}

		realUp = Vector3::Cross(forward, right);

		Matrix view = Matrix::IdentityMatrix;
		view._11 = right.X;
		view._21 = right.Y;
		view._31 = right.Z;

		view._12 = realUp.X;
		view._22 = realUp.Y;
		view._32 = realUp.Z;

		view._13 = forward.X;
		view._23 = forward.Y;
		view._33 = forward.Z;

		view._41 = -Vector3::Dot(from, right);
		view._42 = -Vector3::Dot(from, realUp);
		view._43 = -Vector3::Dot(from, forward);
		view._44 = 1.0f;

		return view;
	}

	Matrix Matrix::ProjectionMatrix(float fov, float ratio, float nearZ, float farZ)
	{
		/*
		xScale     0          0               0
		0        yScale       0               0
		0          0       zf/(zf-zn)         1
		0          0       -zn*zf/(zf-zn)     0
		where:
		yScale = cot(fovY/2)

		xScale = yScale / aspect ratio
		*/

		float yScale = cos(fov / 2.0f) / sin(fov / 2.0f);
		float xScale = yScale / ratio;
		float zf_zn = farZ - nearZ;

		Matrix projection = Matrix::ZeroMatrix;
		projection._11 = xScale;
		projection._22 = yScale;
		projection._33 = farZ / zf_zn;
		projection._34 = 1.0f;;
		projection._43 = -(nearZ * farZ) / zf_zn;

		return projection;
	}

	void Matrix::Inverse()
	{
		*this = Matrix::Inverse(*this);
	}

	Matrix Matrix::Inverse(const Matrix& matrix)
	{
		Matrix tmp = Matrix::ZeroMatrix;
		float det[4];

		tmp(0, 0) = matrix(2, 2) * matrix(3, 3) - matrix(2, 3) * matrix(3, 2);
		tmp(0, 1) = matrix(1, 2) * matrix(3, 3) - matrix(1, 3) * matrix(3, 2);
		tmp(0, 2) = matrix(1, 2) * matrix(2, 3) - matrix(1, 3) * matrix(2, 2);

		tmp(1, 0) = matrix(2, 2) * matrix(3, 3) - matrix(2, 3) * matrix(3, 2);
		tmp(1, 1) = matrix(0, 2) * matrix(3, 3) - matrix(0, 3) * matrix(3, 2);
		tmp(1, 2) = matrix(0, 2) * matrix(2, 3) - matrix(0, 3) * matrix(2, 2);

		tmp(2, 0) = matrix(1, 2) * matrix(3, 3) - matrix(1, 3) * matrix(3, 2);
		tmp(2, 1) = matrix(0, 2) * matrix(3, 3) - matrix(0, 3) * matrix(3, 2);
		tmp(2, 2) = matrix(0, 2) * matrix(1, 3) - matrix(0, 3) * matrix(1, 2);

		tmp(3, 0) = matrix(1, 2) * matrix(2, 3) - matrix(1, 3) * matrix(2, 2);
		tmp(3, 1) = matrix(0, 2) * matrix(2, 3) - matrix(0, 3) * matrix(2, 2);
		tmp(3, 2) = matrix(0, 2) * matrix(1, 3) - matrix(0, 3) * matrix(1, 2);

		det[0] = matrix(1, 1) * tmp(0, 0) - matrix(2, 1) * tmp(0, 1) + matrix(3, 1) * tmp(0, 2);
		det[1] = matrix(0, 1) * tmp(1, 0) - matrix(2, 1) * tmp(1, 1) + matrix(3, 1) * tmp(1, 2);
		det[2] = matrix(0, 1) * tmp(2, 0) - matrix(1, 1) * tmp(2, 1) + matrix(3, 1) * tmp(2, 2);
		det[3] = matrix(0, 1) * tmp(3, 0) - matrix(1, 1) * tmp(3, 1) + matrix(2, 1) * tmp(3, 2);

		float Determinant = matrix(0, 0) * det[0] - matrix(1, 0) * det[1] + matrix(2, 0) * det[2] - matrix(3, 0) * det[3];
		const float	RDet = 1.0f / Determinant;

		Matrix Result;
		Result(0, 0) = RDet * det[0];
		Result(0, 1) = -RDet * det[1];
		Result(0, 2) = RDet * det[2];
		Result(0, 3) = -RDet * det[3];
		Result(1, 0) = -RDet * (matrix(1, 0) * tmp(0, 0) - matrix(2, 0) * tmp(0, 1) + matrix(3, 0) * tmp(0, 2));
		Result(1, 1) = RDet * (matrix(0, 0) * tmp(1, 0) - matrix(2, 0) * tmp(1, 1) + matrix(3, 0) * tmp(1, 2));
		Result(1, 2) = -RDet * (matrix(0, 0) * tmp(2, 0) - matrix(1, 0) * tmp(2, 1) + matrix(3, 0) * tmp(2, 2));
		Result(1, 3) = RDet * (matrix(0, 0) * tmp(3, 0) - matrix(1, 0) * tmp(3, 1) + matrix(2, 0) * tmp(3, 2));
		Result(2, 0) = RDet * (
			matrix(1, 0) * (matrix(2, 1) * matrix(3, 3) - matrix(2, 3) * matrix(3, 1)) -
			matrix(2, 0) * (matrix(1, 1) * matrix(3, 3) - matrix(1, 3) * matrix(3, 1)) +
			matrix(3, 0) * (matrix(1, 1) * matrix(2, 3) - matrix(1, 3) * matrix(2, 1))
			);
		Result(2, 1) = -RDet * (
			matrix(0, 0) * (matrix(2, 1) * matrix(3, 3) - matrix(2, 3) * matrix(3, 1)) -
			matrix(2, 0) * (matrix(0, 1) * matrix(3, 3) - matrix(0, 3) * matrix(3, 1)) +
			matrix(3, 0) * (matrix(0, 1) * matrix(2, 3) - matrix(0, 3) * matrix(2, 1))
			);
		Result(2, 2) = RDet * (
			matrix(0, 0) * (matrix(1, 1) * matrix(3, 3) - matrix(1, 3) * matrix(3, 1)) -
			matrix(1, 0) * (matrix(0, 1) * matrix(3, 3) - matrix(0, 3) * matrix(3, 1)) +
			matrix(3, 0) * (matrix(0, 1) * matrix(1, 3) - matrix(0, 3) * matrix(1, 1))
			);
		Result(2, 3) = -RDet * (
			matrix(0, 0) * (matrix(1, 1) * matrix(2, 3) - matrix(1, 3) * matrix(2, 1)) -
			matrix(1, 0) * (matrix(0, 1) * matrix(2, 3) - matrix(0, 3) * matrix(2, 1)) +
			matrix(2, 0) * (matrix(0, 1) * matrix(1, 3) - matrix(0, 3) * matrix(1, 1))
			);
		Result(3, 0) = -RDet * (
			matrix(1, 0) * (matrix(2, 1) * matrix(3, 2) - matrix(2, 2) * matrix(3, 1)) -
			matrix(2, 0) * (matrix(1, 1) * matrix(3, 2) - matrix(1, 2) * matrix(3, 1)) +
			matrix(3, 0) * (matrix(1, 1) * matrix(2, 2) - matrix(1, 2) * matrix(2, 1))
			);
		Result(3, 1) = RDet * (
			matrix(0, 0) * (matrix(2, 1) * matrix(3, 2) - matrix(2, 2) * matrix(3, 1)) -
			matrix(2, 0) * (matrix(0, 1) * matrix(3, 2) - matrix(0, 2) * matrix(3, 1)) +
			matrix(3, 0) * (matrix(0, 1) * matrix(2, 2) - matrix(0, 2) * matrix(2, 1))
			);
		Result(3, 2) = -RDet * (
			matrix(0, 0) * (matrix(1, 1) * matrix(3, 2) - matrix(1, 2) * matrix(3, 1)) -
			matrix(1, 0) * (matrix(0, 1) * matrix(3, 2) - matrix(0, 2) * matrix(3, 1)) +
			matrix(3, 0) * (matrix(0, 1) * matrix(1, 2) - matrix(0, 2) * matrix(1, 1))
			);
		Result(3, 3) = RDet * (
			matrix(0, 0) * (matrix(1, 1) * matrix(2, 2) - matrix(1, 2) * matrix(2, 1)) -
			matrix(1, 0) * (matrix(0, 1) * matrix(2, 2) - matrix(0, 2) * matrix(2, 1)) +
			matrix(2, 0) * (matrix(0, 1) * matrix(1, 2) - matrix(0, 2) * matrix(1, 1))
			);

		return Result;
	}

	wstring Matrix::ToString() const
	{
		wchar_t str[1000];
		swprintf(str, 1000, L"[%f %f %f %f]\n[%f %f %f %f]\n[%f %f %f %f]\n[%f %f %f %f]",
			_11, _12, _13, _14,
			_21, _22, _23, _24,
			_31, _32, _33, _34,
			_41, _42, _43, _44);

		return wstring(str);
	}

	Vector3 Matrix::RotateDirection(const Vector3& v) const
	{
		float x = v.X * _11 + v.Y * _21 + v.Z * _31;
		float y = v.X * _12 + v.Y * _22 + v.Z * _32;
		float z = v.X * _13 + v.Y * _23 + v.Z * _33;

		return Vector3{ x, y, z };
	}

	Vector3 Matrix::RotatePosition(const Vector3& v) const
	{
		float x = v.X * _11 + v.Y * _21 + v.Z * _31 + _41;
		float y = v.X * _12 + v.Y * _22 + v.Z * _32 + _42;
		float z = v.X * _13 + v.Y * _23 + v.Z * _33 + _43;

		return Vector3{ x, y, z };
	}

	Vector3 Matrix::TransformVector3(const Vector3& v) const
	{
		float x = v.X * _11 + v.Y * _21 + v.Z * _31 + _41;
		float y = v.X * _12 + v.Y * _22 + v.Z * _32 + _42;
		float z = v.X * _13 + v.Y * _23 + v.Z * _33 + _43;
		float w = v.X * _14 + v.Y * _24 + v.Z * _34 + _44;

		return Vector3{ x / w, y / w, z / w };
	}
}