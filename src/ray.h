#ifndef RAY_H
#define RAY_H
#include "vec4.h"
#include "vec2.h"
#include "wavelength.h"

#define STACK_SIZE 12

class ray {

    public:

        vec4 hitCol;
        vec2 hitUV;
        wavelength spectrum;
        vec4 origin;
        vec4 direction;
        double t;
        int hitMTL;
        short stack[STACK_SIZE];

        ray();
        ray(vec4 o, vec4 d);
        vec4 end();
        ray derive();

};

#endif