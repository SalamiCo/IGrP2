//Samuel Mendez Galán
//Pedro Morgado Alarcón

#ifndef BallH
#define BallH

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

#include <vector>
#include <algorithm>
#include "PV2D.h"
#include "Pencil.h"

class Ball{
    private:
    	std::vector<PV2D> vertex;
    public:
        Ball();
        void drawBall();
};

#endif