//Samuel Méndez Galán
//Pedro Morgado Alarcón

#ifndef TRIANGLEH
#define TRIANGLEH

#include "Obstacle.h"

class Triangle : public Obstacle{
	private:
		PV2D p1,p2,p3;
	public:
		Triangle();
		Triangle(PV2D p1, PV2D p2, PV2D p3);
		void drawTriangle(PV2D p1, PV2D p2, PV2D p3);
		void drawWalls(GLfloat xRight, GLfloat xLeft, GLfloat yTop, GLfloat yBot);
		virtual bool intersection2Ball(PV2D p, PV2D v, double& tIn, PV2D& normalIn);
};

#endif
 