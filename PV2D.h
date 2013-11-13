//Samuel Mendez Galán
//Pedro Morgado Alarcón

#ifndef PV2DH
#define PV2DH

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

class PV2D{
    private:
    	GLdouble x;
    	GLdouble y;
    public:
        PV2D();
        PV2D(GLdouble x, GLdouble y);
        GLdouble getPointX();
        GLdouble getPointY();
        GLdouble getVectorX();
        GLdouble getVectorY();
        void setPointX(GLdouble x);
        void setPointY(GLdouble y);
};

#endif