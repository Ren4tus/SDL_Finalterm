#pragma once
#include <math.h>
class Vector2D
{
public:
	Vector2D(float x, float y) : m_x(x), m_y(y)
	{

	}

	~Vector2D()
	{
	}

	float getX() const { return m_x; }
	float getY() const { return m_y; }
	void setX(float x) { m_x = x; }
	void setY(float y) { m_y = y; }
	float length() const { return (float)sqrt(pow(m_x, 2) + pow(m_y, 2)); }
	Vector2D operator+(const Vector2D& v2) const {
		return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
	}
	friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2) {
		v1.m_x += v2.m_x;
		v1.m_y += v2.m_y;
		return v1;
	}
	Vector2D operator-(const Vector2D& v2) const {
		return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
	}
	friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2) {
		v1.m_x = v2.m_x;
		v1.m_y = v2.m_y;
		return v1;
	}
	Vector2D operator*(float scalar) {
		return Vector2D(m_x * scalar, m_y * scalar);
	}
	Vector2D& operator*=(float scalar) {
		m_x *= scalar;
		m_y *= scalar;
		return *this;
	}
	Vector2D operator/(float scalar) {
		return Vector2D(m_x / scalar, m_y / scalar);
	}
	Vector2D& operator/=(float scalar) {
		m_x /= scalar;
		m_y /= scalar;
		return *this;
	}

	void normalize();


private:
	float m_x;
	float m_y;

};