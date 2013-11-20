//Samuel Mendez Galán
//Pedro Morgado Alarcón

#ifndef BallH
#define BallH

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

#include "PV2D.h"
#include "Pencil.h"

class Ball{
    private:
    	std::vector<PV2D> vertex;
    	int numSides;
    	GLfloat radius;
    	PV2D center;
    	PV2D vectorMov;
    public:
        Ball();
        PV2D getCenter();
        PV2D getV();
        void drawBall();
        void step(double t);
        void rebound(PV2D normal);
};

#endif