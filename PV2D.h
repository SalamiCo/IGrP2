//Samuel Mendez Galán
//Pedro Morgado Alarcón

#ifndef PV2DH
#define PV2DH

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

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
};

#endif