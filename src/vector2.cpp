#include "vector2.hpp"
#include <cmath>

Vector2::Vector2(double ix, double iy): x(ix), y(iy) {}
Vector2::Vector2(): x(0), y(0) {}

Vector2 Vector2::operator+(const Vector2 &right) const {
    Vector2 temp(*this);
    temp += right;
    return temp;
}

Vector2 Vector2::operator-(const Vector2 &right) const {
    Vector2 temp(*this);
    temp -= right;
    return temp;
}

Vector2 Vector2::operator*(const Vector2 &right) const {
    Vector2 temp(*this);
    temp *= right;
    return temp;
}

Vector2 Vector2::operator/(const Vector2 &right) const {
    Vector2 temp(*this);
    temp /= right;
    return temp;
}

Vector2& Vector2::operator+=(const Vector2 &right) {
    x += right.x;
    y += right.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2 &right) {
    x -= right.x;
    y -= right.y;
    return *this;
}

Vector2& Vector2::operator*=(const Vector2 &right) {
    x *= right.x;
    y *= right.y;
    return *this;
}

Vector2& Vector2::operator/=(const Vector2 &right) {
    x /= right.x;
    y /= right.y;
    return *this;
}

double Vector2::magnitude() const {
    return sqrt(pow(x, 2) + pow(y, 2));
}