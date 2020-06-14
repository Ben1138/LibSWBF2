#pragma once
#include "FileWriter.h"
#include "FileReader.h"

namespace LibSWBF2::Types
{
	struct LIBSWBF2_API Vector2
	{
		static const ChunkSize SIZE = sizeof(float_t) * 2;

		Vector2();
		Vector2(const float_t x, const float_t y);
		virtual ~Vector2();

		virtual void WriteToStream(FileWriter& stream);
		virtual void ReadFromStream(FileReader& stream);

		float_t m_X = 0.0f;
		float_t m_Y = 0.0f;

		virtual String ToString();
	};

	Vector2 operator+(const Vector2& left, const Vector2& right);
	Vector2 operator-(const Vector2& left, const Vector2& right);
	Vector2 operator*(const Vector2& left, const Vector2& right);
	Vector2 operator/(const Vector2& left, const Vector2& right);
	  
	Vector2 operator+(const Vector2& left, const float right);
	Vector2 operator-(const Vector2& left, const float right);
	Vector2 operator*(const Vector2& left, const float right);
	Vector2 operator/(const Vector2& left, const float right); 

	Vector2 operator+(const float left, const Vector2& right);
	Vector2 operator-(const float left, const Vector2& right);
	Vector2 operator*(const float left, const Vector2& right);
	Vector2 operator/(const float left, const Vector2& right);
}