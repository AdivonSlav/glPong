#include "Mat4.h"

namespace PongMaths
{
	Mat4::Mat4()
	{
		for (int i = 0; i < 16; i++)
		{
			mat[i] = 0.0f;
		}
	}

	Mat4::Mat4(float diagonalVal)
	{
		for (int i = 0; i < 16; i++)
		{
			mat[i] = 0.0f;
		}

		mat[0 + 0 * 4] = 1.0f;
		mat[1 + 1 * 4] = 1.0f;
		mat[2 + 2 * 4] = 1.0f;
		mat[3 + 3 * 4] = 1.0f;
	}

	Mat4 Mat4::Identity()
	{
		return Mat4(1.0f);
	}

	Mat4 Mat4::Orthographic(float left, float right, float top, float bottom, float near, float far)
	{
		Mat4 result = Identity();

		result.mat[0 + 0 * 4] = 2.0f / (right - left);
		result.mat[1 + 1 * 4] = 2.0f / (top - bottom);
		result.mat[2 + 2 * 4] = 2.0f / (near - far);

		result.mat[0 + 3 * 4] = (left + right) / (left - right);
		result.mat[1 + 3 * 4] = (bottom + top) / (bottom - top);
		result.mat[2 + 3 * 4] = (far + near) / (far - near);

		return result;
	}

	Mat4 Mat4::Translation(const Vec3& translation)
	{
		Mat4 result = Identity();

		result.mat[0 + 3 * 4] = translation.x;
		result.mat[1 + 3 * 4] = translation.y;
		result.mat[2 + 3 * 4] = translation.z;

		return result;
	}

	Mat4 Mat4::Scale(const Vec3& scale)
	{
		Mat4 result = Identity();

		result.mat[0 + 0 * 4] = scale.x;
		result.mat[1 + 1 * 4] = scale.y;
		result.mat[2 + 2 * 4] = scale.z;

		return result;
	}

	Mat4& Mat4::operator*=(const Mat4& right)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					mat[i + j * 4] += mat[i + k * 4] * right.mat[k + j * 4];
				}
			}
		}

		return *this;
	}

	Mat4 operator*(Mat4 left, const Mat4& right)
	{
		Mat4 result;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					result.mat[i + j * 4] += left.mat[i + k * 4] * right.mat[k + j * 4];
				}
			}
		}

		return result;
	}
}
