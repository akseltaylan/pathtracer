#ifndef VEC2_H
#define VEC2_H

class vec2 {

    public:

        float x;
        float y;

        vec2();
        vec2(float xx, float yy);
        vec2(float c);

        vec2& operator*=(const float c);

	    friend vec2 operator+(const vec2& a, const vec2& b);
	    friend vec2 operator*(const vec2& a, const float c);

};

#endif