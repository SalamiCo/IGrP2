//Samuel Mendez Galán
//Pedro Morgado Alarcón

#ifndef PV2DH
#define PV2DH

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <math.h>
#include <vector>

class PV2D{
    private:
    	GLfloat x;
    	GLfloat y;
    public:
        PV2D();
        PV2D(GLfloat x, GLfloat y);
        GLfloat getPointX();
        GLfloat getPointY();
        GLfloat getVectorX();
        GLfloat getVectorY();
        void setPointX(GLfloat x);
        void setPointY(GLfloat y);
        void setVectorX(GLfloat x);
        void setVectorY(GLfloat y);
        GLfloat vectorModule(PV2D v);
        PV2D normalizeVector(PV2D v);
        GLfloat dot(PV2D v, PV2D w);
        PV2D normalVector(PV2D v);
        std::vector<GLfloat> vectorDecomposition(PV2D v, PV2D n);
};

#endif