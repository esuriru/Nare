#pragma once


struct Quaternion;
struct Vector4;
struct Vector3;
/**
 * \brief Column-major 4 by 4 transformation matrix
 */
struct Matrix4x4
{
#pragma region CONSTRUCTORS
	explicit Matrix4x4() = default;
	Matrix4x4(const std::array<float, 16>& mat);

#pragma endregion CONSTRUCTORS

#pragma region UTILITY

	std::string ToString() const;

	// NOTE: Could do some handy syntactic sugar, but avoiding it.
	// TODO: replace with Vector2Int, do away with the pair
	float operator[](std::pair<unsigned int, unsigned int> index) const;

#pragma endregion UTILITY

#pragma region OPERATORS
	Matrix4x4 GetTranspose() const;
	Matrix4x4& Transpose();

	Matrix4x4 GetInverse() const;
	Matrix4x4& Inverse();

	Matrix4x4& operator*=(const float scalar);

	Matrix4x4 operator*(const Matrix4x4& rhs);
	Matrix4x4 operator*(const float scalar);

	Vector4 GetRow(unsigned int index) const;
	Vector4 GetColumn(unsigned int index) const;

	friend std::ostream& operator<<(std::ostream& os, const Matrix4x4& mat);
	// Matrix4x4 GetAdjugate() const; 

	float GetDeterminant() const;

	void SetTRS(const Vector3& pos, const Quaternion& rot, const Vector3& scale);

#pragma endregion OPERATORS

#pragma region STATIC
	const static Matrix4x4& identity;
	const static Matrix4x4& zero;

	static Matrix4x4 Ortho(float left, float right, float bottom, float top, float zNear, float zFar);
	static Matrix4x4 Perspective(float fovDegrees, float aspect, float zNear, float zFar);
	static Matrix4x4 LookAt(const Vector3& from, const Vector3& to, Vector3 up);
	static Matrix4x4 Translate(const Vector3& vec);
	static Matrix4x4 Rotate(const Quaternion& quat);
	static Matrix4x4 Scale(const Vector3& vec);
	static Matrix4x4 TRS(const Vector3& pos, const Quaternion& rot, const Vector3& scale);


#pragma endregion STATIC
	
private:
	/**
	 * \brief Data
	 */
	std::array<float, 16> matrix_{};

};