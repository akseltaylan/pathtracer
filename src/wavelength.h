#ifndef WAVELENGTH_H
#define WAVELENGTH_H

#include "vec4.h"

class wavelength {

    private:
        int samples;
        vec4 totColor;
        double nWL;
        double low;
        double high;

    public:
        wavelength();
        wavelength(int s, vec4 col, double nWLx); 
        int getNumSamples();
        vec4 getColSample(int num, double r, double& nwl);
        wavelength getSample(int num, double r);
        vec4 getTotColor();
        vec4 getColMultiplier(double m);
        double getLow();
        double getHigh();
        double getWL();

};

#endif