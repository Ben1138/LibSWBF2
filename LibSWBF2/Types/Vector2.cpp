#include "stdafx.h"
#include "Types\LibString.h"
#include "Vector2.h"

namespace LibSWBF2::Types
{
	Vector2::Vector2() : m_X(m_X), m_Y(m_Y) 
	{
	
	}

	Vector2::Vector2(const float_t x, const float_t y) : m_X(x), m_Y(y) 
	{
	
	}

	Vector2::~Vector2()
	{

	}

	void Vector2::WriteToStream(FileWriter& stream)
	{
		stream.WriteFloat(m_X);
		stream.WriteFloat(m_Y);
	}

	void Vector2::ReadFromStream(FileReader& stream)
	{
		m_X = stream.ReadFloat();
		m_Y = stream.ReadFloat();
	}

	String Vector2::ToString()
	{
		return ("[" + std::to_string(m_X) + ", " + std::to_string(m_Y) + "]").c_str();
	}

	Vector2 operator+(const Vector2& left, const Vector2& right)
	{
		return Vector2(
			left.m_X + right.m_X,
			left.m_Y + right.m_Y
		);
	}

	Vector2 operator-(const Vector2& left, const Vector2& right)
	{
		return Vector2(
			left.m_X - right.m_X,
			left.m_Y - right.m_Y
		);
	}

	Vector2 operator*(const Vector2& left, const Vector2& right)
	{
		return Vector2(
			left.m_X * right.m_X,
			left.m_Y * right.m_Y
		);
	}

	Vector2 operator/(const Vector2& left, const Vector2& right)
	{
		return Vector2(
			left.m_X / right.m_X,
			left.m_Y / right.m_Y
		);
	}

	Vector2 operator+(const Vector2& left, const float right)
	{
		return Vector2(
			left.m_X + right,
			left.m_Y + right
		);
	}

	Vector2 operator-(const Vector2& left, const float right)
	{
		return Vector2(
			left.m_X - right,
			left.m_Y - right
		);
	}

	Vector2 operator*(const Vector2& left, const float right)
	{
		return Vector2(
			left.m_X * right,
			left.m_Y * right
		);
	}

	Vector2 operator/(const Vector2& left, const float right)
	{
		return Vector2(
			left.m_X / right,
			left.m_Y / right
		);
	}

	Vector2 operator+(const float left, const Vector2& right)
	{
		return Vector2(
			left + right.m_X,
			left + right.m_Y
		);
	}

	Vector2 operator-(const float left, const Vector2& right)
	{
		return Vector2(
			left - right.m_X,
			left - right.m_Y
		);
	}

	Vector2 operator*(const float left, const Vector2& right)
	{
		return Vector2(
			left * right.m_X,
			left * right.m_Y
		);
	}

	Vector2 operator/(const float left, const Vector2& right)
	{
		return Vector2(
			left / right.m_X,
			left / right.m_Y
		);
	}
}