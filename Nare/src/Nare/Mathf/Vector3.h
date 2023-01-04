#pragma once
#include "nrpch.h"

struct Vector2;

struct Vector3
{
	float x, y, z;

#pragma region CONSTRUCTORS
	explicit Vector3(const float& scalar);
	Vector3(float x = 0.0, float y = 0.0, float z = 0.0);
	Vector3(const Vector3 &rhs);
	Vector3(const Vector2& rhs);
	Vector3(const Vector2& rhs, float z);
	~Vector3();

#pragma endregion CONSTRUCTORS

#pragma region UTILITY

	std::string ToString() const;
	float operator[](const unsigned int index) const;

#pragma endregion UTILITY
	
#pragma region OPERATORS
	void Set(float a = 0, float b = 0, float c = 0);
	void SetZero();
	bool IsZero() const;

	Vector3 operator+(const Vector3& rhs) const; 
	Vector3& operator+=(const Vector3& rhs); 
	
	Vector3 operator-(const Vector3& rhs) const; 
	Vector3& operator-=(const Vector3& rhs);
	
	Vector3 operator-() const; 
	
	Vector3 operator*(float scalar) const; 
	Vector3& operator*=(float scalar);

	Vector3 operator/(float scalar) const; 
	Vector3& operator/=(float scalar);

	bool operator==(const Vector3& rhs) const;
	bool operator!= (const Vector3& rhs) const;

	Vector3& operator=(const Vector3& rhs); 

	float Length() const; 
	float LengthSquared () const; 
	float Distance(const Vector3& rhs) const; 
	float DistanceSquared(const Vector3& rhs) const; 
	static float Distance(const Vector3& lhs, const Vector3& rhs);
	static float DistanceSquared(const Vector3& lhs, const Vector3& rhs);

	float Dot(const Vector3& rhs) const; 
	Vector3 Cross(const Vector3& rhs) const; 
	
	Vector3 Normalized() const;
	
	Vector3& Normalize();

	Vector3 Reflect(const Vector3& rhs) const;
	friend Vector3 operator*( float scalar, const Vector3& rhs ); 

	friend std::ostream& operator<<(std::ostream& os, Vector3& rhs); 
#pragma endregion OPERATORS 
	

};
