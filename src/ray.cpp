#include "ray.h"
#include "vec4.h"
#include "vec2.h"
#include "wavelength.h"

ray::ray() {
    origin = vec4(0,0,0);
    direction = vec4(0,0,0);
}

ray::ray(vec4 o, vec4 d) {
    origin = o;
    direction = d;
    t = std::numeric_limits<double>::infinity();
    for (int i = 0; i < 5; ++i) {
        stack[i] = -1;
    }
}

vec4 ray::end() {
    return origin + (direction * t);
}

ray ray::derive() {
    vec4 ori(0,0,0);
    vec4 dir(0,1,0);
    ray res = ray (ori, dir);
    res.spectrum = spectrum;
    for (int i = 0; i < 5; ++i) {
        res.stack[i] = stack[i];
    }
    return res;
}