//Samuel Méndez Galán
//Pedro Morgado Alarcón

#ifndef TRIANGLEH
#define TRIANGLEH

#include "Obstacle.h"

class Triangle : public Obstacle {
	private:
		PV2D p1,p2,p3, n1,n2,n3;
		double minimum(double hit[]);
	public:
		Triangle();
		Triangle(PV2D p1, PV2D p2, PV2D p3);
		PV2D getP1();
		PV2D getP2();
		PV2D getP3();
		PV2D getP(int i);
		PV2D getN(int i);
		void static drawTriangle(PV2D p1, PV2D p2, PV2D p3);
		void static drawWalls(GLfloat xRight, GLfloat xLeft, GLfloat yTop, GLfloat yBot);
		virtual bool intersection2Ball(PV2D p, PV2D v, double& tIn, PV2D& normalIn);
};

#endif
 