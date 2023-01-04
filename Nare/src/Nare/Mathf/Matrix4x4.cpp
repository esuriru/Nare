#include "Matrix4x4.h"

#include "Nare/Core.h"
#include "Nare/NareMath.h"

const Matrix4x4& Matrix4x4::identity = Matrix4x4({
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f
	});

const Matrix4x4& Matrix4x4::zero = Matrix4x4();


Matrix4x4::Matrix4x4(const std::array<float, 16>& mat)
	: matrix_(mat)
{
}


Matrix4x4 Matrix4x4::GetTranspose() const
{
	return Matrix4x4(*this).Transpose();
}

Matrix4x4& Matrix4x4::Transpose()
{
	for (int i = 0; i < 4; ++i)
		for (int j = i + 1; j < 4; ++j)
			std::swap(matrix_[i * 4 + j], matrix_[j * 4 + i]);
	return *this;
}

Matrix4x4 Matrix4x4::GetInverse() const
{
	Matrix4x4 temp;

	const float a0 = (matrix_[0] * matrix_[5] - matrix_[1] * matrix_[4]); 
	const float b5 = (matrix_[10] * matrix_[15] - matrix_[11] * matrix_[14]);  
	const float a1 = (matrix_[0] * matrix_[6] - matrix_[2] * matrix_[4]); 
	const float b4 = (matrix_[9] * matrix_[15] - matrix_[11] * matrix_[13]); 
	const float a2 = (matrix_[0] * matrix_[7] - matrix_[3] * matrix_[4]);
	const float b3 = (matrix_[9] * matrix_[14] - matrix_[10] * matrix_[13]); 
	const float a3 = (matrix_[1] * matrix_[6] - matrix_[2] * matrix_[5]);
	const float b2 = (matrix_[8] * matrix_[15] - matrix_[11] * matrix_[12]); 
	const float a4 = (matrix_[1] * matrix_[7] - matrix_[3] * matrix_[5]);
	const float b1 = (matrix_[8] * matrix_[14] - matrix_[10] * matrix_[12]); 
	const float a5 = (matrix_[2] * matrix_[7] - matrix_[3] * matrix_[6]); 
	const float b0 = (matrix_[8] * matrix_[13] - matrix_[9] * matrix_[12]);

	// Get the determinant
	const float determinant = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
	NR_CORE_ASSERT(Mathf::ApproximatelyZero(determinant), "Matrix determinant is zero. Cannot divide by zero.")


	temp.matrix_[ 0] = + matrix_[ 5]*b5 - matrix_[ 6]*b4 + matrix_[ 7]*b3;
	temp.matrix_[ 4] = - matrix_[ 4]*b5 + matrix_[ 6]*b2 - matrix_[ 7]*b1;
	temp.matrix_[ 8] = + matrix_[ 4]*b4 - matrix_[ 5]*b2 + matrix_[ 7]*b0;
	temp.matrix_[12] = - matrix_[ 4]*b3 + matrix_[ 5]*b1 - matrix_[ 6]*b0;
	temp.matrix_[ 1] = - matrix_[ 1]*b5 + matrix_[ 2]*b4 - matrix_[ 3]*b3;
	temp.matrix_[ 5] = + matrix_[ 0]*b5 - matrix_[ 2]*b2 + matrix_[ 3]*b1;
	temp.matrix_[ 9] = - matrix_[ 0]*b4 + matrix_[ 1]*b2 - matrix_[ 3]*b0;
	temp.matrix_[13] = + matrix_[ 0]*b3 - matrix_[ 1]*b1 + matrix_[ 2]*b0;
	temp.matrix_[ 2] = + matrix_[13]*a5 - matrix_[14]*a4 + matrix_[15]*a3;
	temp.matrix_[ 6] = - matrix_[12]*a5 + matrix_[14]*a2 - matrix_[15]*a1;
	temp.matrix_[10] = + matrix_[12]*a4 - matrix_[13]*a2 + matrix_[15]*a0;
	temp.matrix_[14] = - matrix_[12]*a3 + matrix_[13]*a1 - matrix_[14]*a0;
	temp.matrix_[ 3] = - matrix_[ 9]*a5 + matrix_[10]*a4 - matrix_[11]*a3;
	temp.matrix_[ 7] = + matrix_[ 8]*a5 - matrix_[10]*a2 + matrix_[11]*a1;
	temp.matrix_[11] = - matrix_[ 8]*a4 + matrix_[ 9]*a2 - matrix_[11]*a0;
	temp.matrix_[15] = + matrix_[ 8]*a3 - matrix_[ 9]*a1 + matrix_[10]*a0;

	return temp *= 1.f / determinant;
}

/**
 * \brief Inverse this matrix using adjugate divided by determinant
 * \return A reference to the inversed matrix
 */
Matrix4x4& Matrix4x4::Inverse()
{
	std::array<float, 16> initialMat = matrix_;

	const float a0 = (matrix_[0] * matrix_[5] - matrix_[1] * matrix_[4]); 
	const float b5 = (matrix_[10] * matrix_[15] - matrix_[11] * matrix_[14]);  
	const float a1 = (matrix_[0] * matrix_[6] - matrix_[2] * matrix_[4]); 
	const float b4 = (matrix_[9] * matrix_[15] - matrix_[11] * matrix_[13]); 
	const float a2 = (matrix_[0] * matrix_[7] - matrix_[3] * matrix_[4]);
	const float b3 = (matrix_[9] * matrix_[14] - matrix_[10] * matrix_[13]); 
	const float a3 = (matrix_[1] * matrix_[6] - matrix_[2] * matrix_[5]);
	const float b2 = (matrix_[8] * matrix_[15] - matrix_[11] * matrix_[12]); 
	const float a4 = (matrix_[1] * matrix_[7] - matrix_[3] * matrix_[5]);
	const float b1 = (matrix_[8] * matrix_[14] - matrix_[10] * matrix_[12]); 
	const float a5 = (matrix_[2] * matrix_[7] - matrix_[3] * matrix_[6]); 
	const float b0 = (matrix_[8] * matrix_[13] - matrix_[9] * matrix_[12]);

	// Get the determinant
	const float determinant = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
	NR_CORE_ASSERT(Mathf::ApproximatelyZero(determinant), "Matrix determinant is zero. Cannot divide by zero.")


	matrix_[ 0] = + initialMat[ 5]*b5 - initialMat[ 6]*b4 + initialMat[ 7]*b3;
	matrix_[ 4] = - initialMat[ 4]*b5 + initialMat[ 6]*b2 - initialMat[ 7]*b1;
	matrix_[ 8] = + initialMat[ 4]*b4 - initialMat[ 5]*b2 + initialMat[ 7]*b0;
	matrix_[12] = - initialMat[ 4]*b3 + initialMat[ 5]*b1 - initialMat[ 6]*b0;
	matrix_[ 1] = - initialMat[ 1]*b5 + initialMat[ 2]*b4 - initialMat[ 3]*b3;
	matrix_[ 5] = + initialMat[ 0]*b5 - initialMat[ 2]*b2 + initialMat[ 3]*b1;
	matrix_[ 9] = - initialMat[ 0]*b4 + initialMat[ 1]*b2 - initialMat[ 3]*b0;
	matrix_[13] = + initialMat[ 0]*b3 - initialMat[ 1]*b1 + initialMat[ 2]*b0;
	matrix_[ 2] = + initialMat[13]*a5 - initialMat[14]*a4 + initialMat[15]*a3;
	matrix_[ 6] = - initialMat[12]*a5 + initialMat[14]*a2 - initialMat[15]*a1;
	matrix_[10] = + initialMat[12]*a4 - initialMat[13]*a2 + initialMat[15]*a0;
	matrix_[14] = - initialMat[12]*a3 + initialMat[13]*a1 - initialMat[14]*a0;
	matrix_[ 3] = - initialMat[ 9]*a5 + initialMat[10]*a4 - initialMat[11]*a3;
	matrix_[ 7] = + initialMat[ 8]*a5 - initialMat[10]*a2 + initialMat[11]*a1;
	matrix_[11] = - initialMat[ 8]*a4 + initialMat[ 9]*a2 - initialMat[11]*a0;
	matrix_[15] = + initialMat[ 8]*a3 - initialMat[ 9]*a1 + initialMat[10]*a0;

	return *this *= 1.f / determinant;
}

Matrix4x4& Matrix4x4::operator*=(const float scalar)
{
	for (auto& i : matrix_)
		i *= scalar;
	return *this;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& rhs)
{
	Matrix4x4 temp;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			temp.matrix_[i * 4 + j] = matrix_[0 * 4 + j] * rhs.matrix_[i * 4 + 0] + matrix_[1 * 4 + j] * rhs.matrix_[i * 4 + 1] + matrix_[2 * 4 + j] * rhs.matrix_[i * 4 + 2] + matrix_[3 * 4 + j] * rhs.matrix_[i * 4 + 3];
	return temp;
}

Matrix4x4 Matrix4x4::operator*(const float scalar)
{
	return Matrix4x4(*this) *= scalar;
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& rhs) const
{
	Matrix4x4 temp(*this);
	for (int i = 0; i < 16; ++i)
	{
		temp.matrix_[i] += rhs.matrix_[i];
	}
	return temp;
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& rhs) const
{
	Matrix4x4 temp(*this);
	for (int i = 0; i < 16; ++i)
	{
		temp.matrix_[i] -= rhs.matrix_[i];
	}
	return temp;
}

Vector4 Matrix4x4::operator*(const Vector4& rhs) const
{
	return {
		matrix_[0] * rhs.x + matrix_[4] * rhs.y + matrix_[8] * rhs.z + matrix_[12] * rhs.w,
		matrix_[1] * rhs.x + matrix_[5] * rhs.y + matrix_[9] * rhs.z + matrix_[13] * rhs.w,
		matrix_[2] * rhs.x + matrix_[6] * rhs.y + matrix_[10] * rhs.z + matrix_[14] * rhs.w,
		matrix_[3] * rhs.x + matrix_[7] * rhs.y + matrix_[11] * rhs.z + matrix_[15] * rhs.w,
	};
}

Vector3 Matrix4x4::operator*(const Vector3& rhs) const
{
	return {
		matrix_[0] * rhs.x + matrix_[4] * rhs.y + matrix_[8] * rhs.z + matrix_[12],
		matrix_[1] * rhs.x + matrix_[5] * rhs.y + matrix_[9] * rhs.z + matrix_[13],
		matrix_[2] * rhs.x + matrix_[6] * rhs.y + matrix_[10] * rhs.z + matrix_[14]
	};
}

Vector4 Matrix4x4::GetRow(unsigned index) const
{
	return { matrix_[index], matrix_[index + 4 * 1], matrix_[index + 4 * 2], matrix_[index + 4 * 3] };
}

Vector4 Matrix4x4::GetColumn(unsigned index) const
{
	return { matrix_[index], matrix_[index + 1], matrix_[index + 2], matrix_[index + 3] };
}

float Matrix4x4::operator[](std::pair<unsigned, unsigned> index) const
{
	// Not tested
	return matrix_[index.first * 4 + index.second];
}


float Matrix4x4::GetDeterminant() const
{
	return
		(
			(matrix_[0] * matrix_[5] - matrix_[1] * matrix_[4]) // a0
			* (matrix_[10] * matrix_[15] - matrix_[11] * matrix_[14])  // b5
			)
		-
		(
			(matrix_[0] * matrix_[6] - matrix_[2] * matrix_[4]) // a1
			* (matrix_[9] * matrix_[15] - matrix_[11] * matrix_[13])  // b4
			)
		+
		(
			(matrix_[0] * matrix_[7] - matrix_[3] * matrix_[4]) // a2
			* (matrix_[9] * matrix_[14] - matrix_[10] * matrix_[13])  // b3
			)
		+
		(
			(matrix_[1] * matrix_[6] - matrix_[2] * matrix_[5]) // a3
			* (matrix_[8] * matrix_[15] - matrix_[11] * matrix_[12])  // b2
			)
		-
		(
			(matrix_[1] * matrix_[7] - matrix_[3] * matrix_[5]) // a4
			* (matrix_[8] * matrix_[14] - matrix_[10] * matrix_[12])  // b1
			)
		+
		(
			(matrix_[2] * matrix_[7] - matrix_[3] * matrix_[6]) // a5
			* (matrix_[8] * matrix_[13] - matrix_[9] * matrix_[12])  // b0
			);
}

void Matrix4x4::SetTRS(const Vector3& pos, const Quaternion& rot, const Vector3& scale)
{
	*this = TRS(pos, rot, scale);
}

std::string Matrix4x4::ToString() const
{
	std::stringstream ss;
	ss << "[ \n";
	ss << matrix_[0] << ", " << matrix_[1] << ", " << matrix_[2] << ", " << matrix_[3] << ", \n";
	ss << matrix_[4] << ", " << matrix_[5] << ", " << matrix_[6] << ", " << matrix_[7] << ", \n";
	ss << matrix_[8] << ", " << matrix_[9] << ", " << matrix_[10] << ", " << matrix_[11] << ", \n";
	ss << matrix_[12] << ", " << matrix_[13] << ", " << matrix_[14] << ", " << matrix_[15] << "\n";
	ss << "]";

	return ss.str();
}

Matrix4x4 Matrix4x4::Ortho(const float left, const float right, const float bottom, const float top, const float zNear, const float zFar)
{
	return Matrix4x4({
		2 / right - left, 0, 0, 0,
		0, 2 / top - bottom, 0, 0,
		0, 0, -2 / zFar - zNear, 0,
		-((right + left) / (right - left)), -((top + bottom) / (top - bottom)), -((zFar + zNear) / (zFar - zNear)), 1
		});
}

Matrix4x4 Matrix4x4::Perspective(const float fovDegrees, const float aspect, const float zNear, const float zFar)
{
	const float f = 1.0f / Mathf::Tan(Mathf::PI / 180 * fovDegrees / 2);
	return Matrix4x4({
		(f / aspect), 0, 0, 0,
		0, f, 0, 0,
		0, 0, ((zFar + zNear) / (zNear - zFar)), -1,
		0, 0, (2 * zFar * zNear / (zNear - zFar)), 0
		});
}

Matrix4x4 Matrix4x4::LookAt(const Vector3& from, const Vector3& to, Vector3 up)
{
	Vector3 lookDirection = from - to;
	lookDirection.Normalize();

	up.Normalize();
	Vector3 right = lookDirection.Cross(up);
	Vector3 u = right.Cross(lookDirection);

	Matrix4x4 mat ({
		right.x, u.x, -lookDirection.x, 0,
		right.y, u.y, -lookDirection.y, 0,
		right.z, u.z, -lookDirection.z, 0,
		0, 0, 0, 1
		});

	return mat * Translate(-from);
}

Matrix4x4 Matrix4x4::Translate(const Vector3& vec)
{
	Matrix4x4 temp(identity);
	temp.matrix_[12] = vec.x;
	temp.matrix_[13] = vec.y;
	temp.matrix_[14] = vec.z;

	return temp;
}

Matrix4x4 Matrix4x4::Rotate(const Quaternion& quat)
{
	const float x2 = quat.x * quat.x;
	const float y2 = quat.y * quat.y;
	const float z2 = quat.z * quat.z;
	const float xy = quat.x * quat.y;
	const float xz = quat.x * quat.z;
	const float yz = quat.y * quat.z;
	const float wx = quat.w * quat.x;
	const float wy = quat.w * quat.y;
	const float wz = quat.w * quat.z;

	return Matrix4x4(
		{
			1 - 2 * (y2 + z2), 2 * (xy - wz), 2 * (xz + wy), 0,
			2 * (xy + wz), 1 - 2 * (x2 + z2), 2 * (yz - wx), 0,
			2 * (xz - wy), 2 * (yz + wx), 1 - 2 * (x2 + y2), 0,
			0, 0, 0, 1
		});
}

Matrix4x4 Matrix4x4::Scale(const Vector3& vec)
{
	Matrix4x4 temp(identity);
	temp.matrix_[0] = vec.x;
	temp.matrix_[5] = vec.y;
	temp.matrix_[10] = vec.z;

	return temp;
}

Matrix4x4 Matrix4x4::TRS(const Vector3& pos, const Quaternion& rot, const Vector3& scale)
{
	return Translate(pos) * Rotate(rot) * Scale(scale);
}


std::ostream& operator<<(std::ostream& os, const Matrix4x4& mat)
{
	return os << mat.ToString();
}
