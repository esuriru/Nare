#pragma once
#include "nrpch.h"

struct Vector2;
struct Vector3;

struct Vector4
{
	float x, y, z, w;

	// For colours
	float& r = x;
	float& g = y;
	float& b = z;
	float& a = w;

#pragma region CONSTRUCTORS
	explicit Vector4(const float& scalar);
    Vector4();
	Vector4(float x, float y, float z, float w);
	Vector4(const Vector3& rhs);
	~Vector4();

#pragma endregion CONSTRUCTORS

#pragma region UTILITY

	std::string ToString() const;
	float operator[](const unsigned int index) const;
	const float* data() const;

#pragma endregion UTILITY
	
#pragma region OPERATORS
	bool IsZero() const;

	Vector4 operator+(const Vector4& rhs) const; 
	Vector4& operator+=(const Vector4& rhs); 
	
	Vector4 operator-(const Vector4& rhs) const; 
	Vector4& operator-=(const Vector4& rhs);
	
	Vector4 operator-() const; 
	
	Vector4 operator*(float scalar) const; 
	Vector4& operator*=(float scalar);

	Vector4 operator/(float scalar) const; 
	Vector4& operator/=(float scalar);

	bool operator==(const Vector4& rhs) const;
	bool operator!= (const Vector4& rhs) const;

	Vector4& operator=(const Vector4& rhs); 

	float Length() const; 
	float LengthSquared () const; 
	float Distance(const Vector4& rhs) const; 
	float DistanceSquared(const Vector4& rhs) const; 

	static float Distance(const Vector4& lhs, const Vector4& rhs);
	static float DistanceSquared(const Vector4& lhs, const Vector4& rhs);

	float Dot(const Vector4& rhs) const; 
	
	Vector4 Normalized() const;
	
	Vector4& Normalize();

	friend Vector4 operator*( float scalar, const Vector4& rhs ); 

	friend std::ostream& operator<<(std::ostream& os, Vector4& rhs); 
#pragma endregion OPERATORS 
	

};
