//Samuel Méndez Galán
//Pedro Morgado Alarcón

#ifndef CIRCLEH
#define CIRCLEH

#include "Obstacle.h" 
#include "Pencil.h"
#include <math.h>

class Circle : public Obstacle {
	private:
		PV2D center;
		GLfloat radius, radius2; // r and r^2
		std::vector<PV2D> vertex;
		int numSides;
	public:
		Circle();
		Circle(PV2D center, GLfloat radius);
		void drawCircle();

		virtual bool intersection2Ball(PV2D p, PV2D v, double& tIn, PV2D& normalIn);

};

#endif