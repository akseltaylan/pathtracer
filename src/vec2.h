#ifndef VEC2_H
#define VEC2_H

class vec2 {

    public:

        double x;
        double y;

        vec2();
        vec2(double xx, double yy);
        vec2(double c);

        vec2& operator*=(const double c);

	    friend vec2 operator+(const vec2& a, const vec2& b);
	    friend vec2 operator*(const vec2& a, const double c);

};

#endif