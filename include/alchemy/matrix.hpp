#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "types.hpp"

namespace alc
{
	// 3x3 matrix
	struct Matrix3
	{
		i64 matrix[3][3] = {
			{ 0,  0,  0},
			{ 0,  0,  0},
			{ 0,  0,  0},
		};

		inline i64 mult_index(const Matrix3 &other, i32 x, i32 y)
		{
			return (this->matrix[0][y] * other.matrix[x][0]) + (this->matrix[1][y] * other.matrix[x][1]) + (this->matrix[2][y] * other.matrix[x][2]); 
		}

		inline Matrix3& operator *(const Matrix3 &other)
		{
			Matrix3 output_matrix;

			output_matrix.matrix[0][0] = this->mult_index(other, 0, 0);
			output_matrix.matrix[1][0] = this->mult_index(other, 1, 0);
			output_matrix.matrix[2][0] = this->mult_index(other, 2, 0);

			output_matrix.matrix[0][1] = this->mult_index(other, 0, 1);
			output_matrix.matrix[1][1] = this->mult_index(other, 1, 1);
			output_matrix.matrix[2][1] = this->mult_index(other, 2, 1);

			output_matrix.matrix[0][2] = this->mult_index(other, 0, 2);
			output_matrix.matrix[1][2] = this->mult_index(other, 1, 2);
			output_matrix.matrix[2][2] = this->mult_index(other, 2, 2);

			return output_matrix;
		}
	};
};

#endif // __MATRIX_H__