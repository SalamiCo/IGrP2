//Samuel Méndez Galán
//Pedro Morgado Alarcón

#ifndef TRIANGLEH
#define TRIANGLEH

#include "Obstacle.h"

class Triangle : public Obstacle {
	private:
		PV2D p1,p2,p3, n1,n2,n3, center;
		PV2D getP(int i);
		PV2D getN(int i);
		int minimum(double hit[], int nHits);
		PV2D triangleCenter(PV2D p1, PV2D p2, PV2D p3);
	public:
		Triangle();
		Triangle(PV2D p1, PV2D p2, PV2D p3);
		PV2D getP1();
		PV2D getP2();
		PV2D getP3();
		void static drawTriangle(PV2D p1, PV2D p2, PV2D p3);
		void static drawWalls(Triangle tR, Triangle tT, Triangle tL, Triangle tB);

		virtual bool intersection2Ball(PV2D p, PV2D v, double& tIn, PV2D& normalIn);
};

#endif
 