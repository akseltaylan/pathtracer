#include "vec2.h"

vec2::vec2() {
    x = 0.0;
    y = 0.0;
}

vec2::vec2(double xx, double yy) {
    x = xx;
    y = yy;
}

vec2::vec2(double c) {
    x = c;
    y = c;
}

vec2& vec2::operator*=(const double c) {
    x *= c;
    y *= c;
    return *this;
}

vec2 operator+(const vec2& a, const vec2& b) {
    return vec2(a.x + b.x, a.y + b.y);
}

vec2 operator*(const vec2& a, const double c) {
    return vec2(a.x * c, a.y * c);
}

