//Samuel Mendez Galán
//Pedro Morgado Alarcón

#ifndef PencilH
#define PencilH

#include "PV2D.h"
#include <math.h>

class Pencil{
	private:
		PV2D pos;
		GLdouble dir;
	public:
		Pencil();
		Pencil(PV2D p, GLdouble dir);
		void setPos(PV2D p);
		void setDir(GLdouble d);
		GLdouble getDir();
		PV2D getPos();
        void turn(GLdouble d);
        void forward(GLdouble dist);
};

#endif