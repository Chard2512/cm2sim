#ifndef cm2_vector2_hpp
#define cm2_vector2_hpp

class Vector2{
public:
    Vector2(double ix, double iy);
    Vector2();

    double x, y;

	Vector2 operator+(const Vector2 &right) const;
	Vector2 operator-(const Vector2 &right) const;
	Vector2 operator*(const Vector2 &right) const;
	Vector2 operator/(const Vector2 &right) const;
	Vector2& operator+=(const Vector2 &right);
	Vector2& operator-=(const Vector2 &right);
	Vector2& operator*=(const Vector2 &right);
	Vector2& operator/=(const Vector2 &right);

    double magnitude() const;
};

#endif