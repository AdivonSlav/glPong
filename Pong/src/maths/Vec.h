#pragma once
#include <ostream>

namespace PongMaths
{
	struct Vec2
	{
		float x, y;

		Vec2();
		Vec2(float x, float y);

		Vec2& Add(const Vec2& other);
		Vec2& Subtract(const Vec2& other);
		Vec2& Multiply(const Vec2& other);
		Vec2& Divide(const Vec2& other);

		friend Vec2 operator+(const Vec2& left, const Vec2& right);
		friend Vec2 operator-(const Vec2& left, const Vec2& right);
		friend Vec2 operator*(const Vec2& left, const Vec2& right);
		friend Vec2 operator/(const Vec2& left, const Vec2& right);

		friend std::ostream& operator>>(std::ostream& COUT, const Vec2& vec);
	};

	struct iVec2
	{
		int x, y;

		iVec2();
		iVec2(int x, int y);

		iVec2& Add(const iVec2& other);
		iVec2& Subtract(const iVec2& other);
		iVec2& Multiply(const iVec2& other);
		iVec2& Divide(const iVec2& other);

		friend iVec2 operator+(const iVec2& left, const iVec2& right);
		friend iVec2 operator-(const iVec2& left, const iVec2& right);
		friend iVec2 operator*(const iVec2& left, const iVec2& right);
		friend iVec2 operator/(const iVec2& left, const iVec2& right);

		friend std::ostream& operator>>(std::ostream& COUT, const iVec2& vec);
	};

	struct Vec3
	{
		float x, y, z;

		Vec3();
		Vec3(float x, float y, float z);
		   
		Vec3& Add(const Vec3& other);
		Vec3& Subtract(const Vec3& other);
		Vec3& Multiply(const Vec3& other);
		Vec3& Divide(const Vec3& other);

		friend Vec3 operator+(const Vec3& left, const Vec3& right);
		friend Vec3 operator-(const Vec3& left, const Vec3& right);
		friend Vec3 operator*(const Vec3& left, const Vec3& right);
		friend Vec3 operator/(const Vec3& left, const Vec3& right);

		friend std::ostream& operator>>(std::ostream& COUT, const Vec3& vec);
	};

	struct Vec4
	{
		float x, y, z, w;

		Vec4();
		Vec4(float x, float y, float z, float w);

		Vec4& Add(const Vec4& other);
		Vec4& Subtract(const Vec4& other);
		Vec4& Multiply(const Vec4& other);
		Vec4& Divide(const Vec4& other);

		friend Vec4 operator+(const Vec4& left, const Vec4& right);
		friend Vec4 operator-(const Vec4& left, const Vec4& right);
		friend Vec4 operator*(const Vec4& left, const Vec4& right);
		friend Vec4 operator/(const Vec4& left, const Vec4& right);

		friend std::ostream& operator>>(std::ostream& COUT, const Vec4& vec);
	};
}
