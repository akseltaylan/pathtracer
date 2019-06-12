#include "vec2.h"

vec2::vec2() {
    x = 0.0f;
    y = 0.0f;
}

vec2::vec2(float xx, float yy) {
    x = xx;
    y = yy;
}

vec2::vec2(float c) {
    x = c;
    y = c;
}

vec2& vec2::operator*=(const float c) {
    x *= c;
    y *= c;
    return *this;
}

vec2 operator+(const vec2& a, const vec2& b) {
    return vec2(a.x + b.x, a.y + b.y);
}

vec2 operator*(const vec2& a, const float c) {
    return vec2(a.x * c, a.y * c);
}

