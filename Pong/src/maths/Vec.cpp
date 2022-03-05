#include "Vec.h"
#include <iostream>

namespace PongMaths
{
	Vec2::Vec2()
		:x(0), y(0)
	{
	}

	Vec2::Vec2(float x, float y)
		: x(x), y(y)
	{
	}

	Vec2& Vec2::Add(const Vec2& other)
	{
		this->x += other.x;
		this->y += other.y;

		return *this;
	}

	Vec2& Vec2::Subtract(const Vec2& other)
	{
		this->x -= other.x;
		this->y -= other.y;

		return *this;
	}

	Vec2& Vec2::Multiply(const Vec2& other)
	{
		this->x *= other.x;
		this->y *= other.y;

		return *this;
	}

	Vec2& Vec2::Divide(const Vec2& other)
	{
		this->x /= other.x;
		this->y /= other.y;

		return *this;
	}



	Vec2 operator+(const Vec2& left, const Vec2& right)
	{
		Vec2 result;

		result.x = left.x + right.x;
		result.y = left.y + right.y;

		return result;
	}

	Vec2 operator-(const Vec2& left, const Vec2& right)
	{
		Vec2 result;

		result.x = left.x - right.x;
		result.y = left.y - right.y;

		return result;
	}

	Vec2 operator*(const Vec2& left, const Vec2& right)
	{
		Vec2 result;

		result.x = left.x * right.x;
		result.y = left.y * right.y;

		return result;
	}

	Vec2 operator/(const Vec2& left, const Vec2& right)
	{
		Vec2 result;

		result.x = left.x / right.x;
		result.y = left.y / right.y;

		return result;
	}

	std::ostream& operator>>(std::ostream& COUT, const Vec2& vec)
	{
		COUT << "(x: " << vec.x << ") (y: " << vec.y << ")" << std::endl;
		return COUT;
	}

	//

	iVec2::iVec2()
		: x(0), y(0)
	{
	}

	iVec2::iVec2(int x, int y)
		: x(x), y(y)
	{
	}

	iVec2& iVec2::Add(const iVec2& other)
	{
		this->x += other.x;
		this->y += other.y;

		return *this;
	}

	iVec2& iVec2::Subtract(const iVec2& other)
	{
		this->x -= other.x;
		this->y -= other.y;

		return *this;
	}

	iVec2& iVec2::Multiply(const iVec2& other)
	{
		this->x *= other.x;
		this->y *= other.y;

		return *this;
	}

	iVec2& iVec2::Divide(const iVec2& other)
	{
		this->x /= other.x;
		this->y /= other.y;

		return *this;
	}

	iVec2 operator+(const iVec2& left, const iVec2& right)
	{
		iVec2 result;

		result.x = left.x + right.x;
		result.y = left.y + right.y;

		return result;
	}

	iVec2 operator-(const iVec2& left, const iVec2& right)
	{
		iVec2 result;

		result.x = left.x - right.x;
		result.y = left.y - right.y;

		return result;
	}

	iVec2 operator*(const iVec2& left, const iVec2& right)
	{
		iVec2 result;

		result.x = left.x * right.x;
		result.y = left.y * right.y;

		return result;
	}

	iVec2 operator/(const iVec2& left, const iVec2& right)
	{
		iVec2 result;

		result.x = left.x / right.x;
		result.y = left.y / right.y;

		return result;
	}

	std::ostream& operator>>(std::ostream& COUT, const iVec2& vec)
	{
		COUT << "(x: " << vec.x << ") (y: " << vec.y << std::endl;
		return COUT;
	}

	// // // // // // // // // // //

	Vec3::Vec3()
		: x(0), y(0), z(0)
	{

	}

	Vec3::Vec3(float x, float y, float z)
		: x(x), y(y), z(z)
	{

	}

	Vec3& Vec3::Add(const Vec3& other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;

		return *this;
	}

	Vec3& Vec3::Subtract(const Vec3& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;

		return *this;
	}

	Vec3& Vec3::Multiply(const Vec3& other)
	{
		this->x *= other.x;
		this->y *= other.y;
		this->z *= other.z;

		return *this;
	}

	Vec3& Vec3::Divide(const Vec3& other)
	{
		this->x /= other.x;
		this->y /= other.y;
		this->z /= other.z;

		return *this;
	}

	Vec3 operator+(const Vec3& left, const Vec3& right)
	{
		Vec3 result;

		result.x = left.x + right.x;
		result.y = left.y + right.y;
		result.z = left.z + right.z;

		return result;
	}

	Vec3 operator-(const Vec3& left, const Vec3& right)
	{
		Vec3 result;

		result.x = left.x - right.x;
		result.y = left.y - right.y;
		result.z = left.z - right.z;

		return result;
	}

	Vec3 operator*(const Vec3& left, const Vec3& right)
	{
		Vec3 result;

		result.x = left.x * right.x;
		result.y = left.y * right.y;
		result.z = left.z * right.z;

		return result;
	}

	Vec3 operator/(const Vec3& left, const Vec3& right)
	{
		Vec3 result;

		result.x = left.x / right.x;
		result.y = left.y / right.y;
		result.z = left.z / right.z;

		return result;
	}

	std::ostream& operator>>(std::ostream& COUT, const Vec3& vec)
	{
		COUT << "(x: " << vec.x << ") (y: " << vec.y << ") (z: " << vec.z << ")" << std::endl;
		return COUT;
	}

	// // // // // // // // // // //

	Vec4::Vec4()
		: x(0), y(0), z(0), w(0)
	{
	}

	Vec4::Vec4(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w)
	{

	}

	Vec4& Vec4::Add(const Vec4& other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		this->w += other.w;

		return *this;
	}

	Vec4& Vec4::Subtract(const Vec4& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		this->w -= other.w;

		return *this;
	}

	Vec4& Vec4::Multiply(const Vec4& other)
	{
		this->x *= other.x;
		this->y *= other.y;
		this->z *= other.z;
		this->w *= other.w;

		return *this;
	}

	Vec4& Vec4::Divide(const Vec4& other)
	{
		this->x /= other.x;
		this->y /= other.y;
		this->z /= other.z;
		this->w /= other.w;

		return *this;
	}

	Vec4 operator+(const Vec4& left, const Vec4& right)
	{
		Vec4 result;

		result.x = left.x + right.x;
		result.y = left.y + right.y;
		result.z = left.z + right.z;
		result.w = left.w + right.w;

		return result;
	}

	Vec4 operator-(const Vec4& left, const Vec4& right)
	{
		Vec4 result;

		result.x = left.x - right.x;
		result.y = left.y - right.y;
		result.z = left.z - right.z;
		result.w = left.w - right.w;

		return result;
	}

	Vec4 operator*(const Vec4& left, const Vec4& right)
	{
		Vec4 result;

		result.x = left.x * right.x;
		result.y = left.y * right.y;
		result.z = left.z * right.z;
		result.w = left.w * right.w;

		return result;
	}

	Vec4 operator/(const Vec4& left, const Vec4& right)
	{
		Vec4 result;

		result.x = left.x / right.x;
		result.y = left.y / right.y;
		result.z = left.z / right.z;
		result.w = left.w / right.w;

		return result;
	}

	std::ostream& operator>>(std::ostream& COUT, const Vec4& vec)
	{
		COUT << "(x: " << vec.x << ") (y: " << vec.y << ") (z: " << vec.z << ") (w: " << vec.w << ")" << std::endl;
		return COUT;
	}
}
