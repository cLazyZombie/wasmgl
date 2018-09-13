#pragma once

namespace VoxerEngine
{
	enum class NumericTypeEnum
	{
		TestType,
		RadianType,
	};

	template <NumericTypeEnum type, typename R> struct NumericType
	{
		R value;

		NumericType(){}
		NumericType(R v) : value(v){}

		bool operator < (const NumericType& other) const
		{
			return value < other.value;
		}

		bool operator > (const NumericType& other) const
		{
			return value > other.value;
		}

		bool operator <= (const NumericType& other) const
		{
			return value <= other.value;
		}

		bool operator >= (const NumericType& other) const
		{
			return value >= other.value;
		}

		bool operator == (const NumericType& other) const
		{
			return value == other.value;
		}

		bool operator != (const NumericType& other) const
		{
			return value != other.value;
		}

		NumericType operator+(const NumericType& other) const
		{
			return NumericType(value + other.value);
		}

		NumericType operator-(const NumericType& other) const
		{
			return NumericType(value - other.value);
		}

		NumericType operator*(const NumericType& other) const
		{
			return NumericType(value * other.value);
		}

		NumericType operator*(float other) const
		{
			return NumericType(value * other);
		}

		NumericType operator/(const NumericType& other) const
		{
			return NumericType(value / other.value);
		}

		NumericType operator-() const
		{
			return NumericType(-value);
		}

		NumericType& operator+=(const NumericType& other)
		{
			value += other.value;
			return *this;
		}

		NumericType& operator-=(const NumericType& other)
		{
			value -= other.value;
			return *this;
		}

		static NumericType Min(const NumericType& left, const NumericType& right)
		{
			return left < right ? left : right;
		}

		static NumericType Max(const NumericType& left, const NumericType& right)
		{
			return left > right ? left : right;
		}

		static NumericType Clamp(const NumericType& value, const NumericType& clampMin, const NumericType& clampMax)
		{
			if (value < clampMin) return clampMin;
			if (value > clampMax) return clampMax;
			return value;
		}

		static NumericType Abs(const NumericType& v)
		{
			return NumericType(abs(v.value));
		}

		wstring ToString() const
		{
			wchar_t str[100];
			swprintf(str, 100, L"%f", value);
			return wstring(str);
		}
	};

	template <NumericTypeEnum type, typename R> 
	NumericType<type, R> operator*(float s, const NumericType<type, R>& v)
	{
		return NumericType<type, R>(s * v.value);
	}
}