#pragma once

#include "Vec.h"

namespace PongMaths
{
	struct Mat4
	{
		float mat[4 * 4];

		Mat4();
		Mat4(float diagonalVal);
		~Mat4() = default;

		static Mat4 Identity();
		static Mat4 Orthographic(float left, float right, float top, float bottom, float near, float far);

		static Mat4 Translation(const Vec3& translation);
		static Mat4 Scale(const Vec3& scale);

		Mat4& operator*=(const Mat4& right);
		friend Mat4 operator*(Mat4 left, const Mat4& right);
	};
}

