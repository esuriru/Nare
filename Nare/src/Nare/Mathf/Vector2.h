#pragma once

#include <string>
#include <ostream>

/**
 * \brief Two-element vector
 */
struct Vector2
{
	float x, y;

#pragma region CONSTRUCTORS

	Vector2();
	Vector2(float x, float y);
	Vector2(double x, double y);
	Vector2(unsigned int x, unsigned int y);

#pragma endregion CONSTRUCTORS

#pragma region UTILITY

	// TODO: Might make all classes that can be represented as strings inherit from an interface that implements that.
	std::string ToString() const;

	float operator[](const unsigned int& index) const;

#pragma endregion UTILITY

#pragma region LOCAL_OPERATORS

	bool IsZero() const;
	bool operator==(const Vector2& rhs) const;
	bool operator!=(const Vector2& rhs) const;

	Vector2 operator-() const;

	Vector2& operator+=(const Vector2& rhs);
	Vector2 operator+(const Vector2& rhs) const;

	Vector2& operator-=(const Vector2& rhs);
	Vector2 operator-(const Vector2& rhs) const;

	Vector2 operator*(float scalar) const;
	Vector2& operator*=(float scalar);

	Vector2 operator/(float scalar) const;
	Vector2& operator/=(float scalar);

	Vector2& Normalize();
	Vector2 Normalized() const;

	float Dot(const Vector2& rhs) const;

	float LengthSquared() const;
	float Length() const;

	float DistanceSquared(const Vector2& rhs) const;
	float Distance(const Vector2& rhs) const;
	
	Vector2 PerpendicularClockwise() const;
	Vector2 PerpendicularAntiClockwise() const;

	// Reverse operations
	friend Vector2 operator*(float scalar, const Vector2& rhs);

	friend std::ostream& operator<<(std::ostream& os, const Vector2 & rhs);

#pragma endregion LOCAL_OPERATORS

	// TODO: Probably make a base class that creates static template functions that just enables static functionality between vectors
#pragma region STATIC_OPERATORS

	static Vector2 Normalize(const Vector2& vec);
	static float Dot(const Vector2& vec1, const Vector2& vec2);

	static Vector2 Reflect(const Vector2& incident, const Vector2& normal);

	static float Length(const Vector2& vec);
	static float LengthSquared(const Vector2& vec);

	static float Distance(const Vector2& lhs, const Vector2& rhs);
	static float DistanceSquared(const Vector2& lhs, const Vector2& rhs);

#pragma endregion STATIC_OPERATORS
};

