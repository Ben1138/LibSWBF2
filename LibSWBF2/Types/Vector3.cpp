#include "stdafx.h"
#include "Types\LibString.h"
#include "Vector3.h"

namespace LibSWBF2::Types
{
	Vector3::Vector3() : Vector2(), m_Z(0)
	{
		
	}

	Vector3::Vector3(const float_t x, const float_t y, const float_t z) : Vector2(x, y), m_Z(z)
	{
		
	}

	Vector3::~Vector3()
	{

	}

	void Vector3::WriteToStream(FileWriter& stream)
	{
		stream.WriteFloat(m_X);
		stream.WriteFloat(m_Y);
		stream.WriteFloat(m_Z);
	}

	void Vector3::ReadFromStream(FileReader& stream)
	{
		m_X = stream.ReadFloat();
		m_Y = stream.ReadFloat();
		m_Z = stream.ReadFloat();
	}

	String Vector3::ToString()
	{
		return ("[" + std::to_string(m_X) + ", " + std::to_string(m_Y) + ", " + std::to_string(m_Z) + "]").c_str();
	}

	Vector3 operator+(const Vector3& left, const Vector3& right)
	{
		return Vector3(
			left.m_X + right.m_X,
			left.m_Y + right.m_Y,
			left.m_Z + right.m_Z
		);
	}

	Vector3 operator-(const Vector3& left, const Vector3& right)
	{
		return Vector3(
			left.m_X - right.m_X,
			left.m_Y - right.m_Y,
			left.m_Z - right.m_Z
		);
	}

	Vector3 operator*(const Vector3& left, const Vector3& right)
	{
		return Vector3(
			left.m_X * right.m_X,
			left.m_Y * right.m_Y,
			left.m_Z * right.m_Z
		);
	}

	Vector3 operator/(const Vector3& left, const Vector3& right)
	{
		return Vector3(
			left.m_X / right.m_X,
			left.m_Y / right.m_Y,
			left.m_Z / right.m_Z
		);
	}

	Vector3 operator+(const Vector3& left, const float right)
	{
		return Vector3(
			left.m_X + right,
			left.m_Y + right,
			left.m_Z + right
		);
	}

	Vector3 operator-(const Vector3& left, const float right)
	{
		return Vector3(
			left.m_X - right,
			left.m_Y - right,
			left.m_Z - right
		);
	}

	Vector3 operator*(const Vector3& left, const float right)
	{
		return Vector3(
			left.m_X * right,
			left.m_Y * right,
			left.m_Z * right
		);
	}

	Vector3 operator/(const Vector3& left, const float right)
	{
		return Vector3(
			left.m_X / right,
			left.m_Y / right,
			left.m_Z / right
		);
	}

	Vector3 operator+(const float left, const Vector3& right)
	{
		return Vector3(
			left + right.m_X,
			left + right.m_Y,
			left + right.m_Z
		);
	}

	Vector3 operator-(const float left, const Vector3& right)
	{
		return Vector3(
			left - right.m_X,
			left - right.m_Y,
			left - right.m_Z
		);
	}

	Vector3 operator*(const float left, const Vector3& right)
	{
		return Vector3(
			left * right.m_X,
			left * right.m_Y,
			left * right.m_Z
		);
	}

	Vector3 operator/(const float left, const Vector3& right)
	{
		return Vector3(
			left / right.m_X,
			left / right.m_Y,
			left / right.m_Z
		);
	}
}