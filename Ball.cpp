//Samuel Mendez Galán
//Pedro Morgado Alarcón

#include "Ball.h"

Ball::Ball(){
	Pencil pen;
	GLdouble edge = 30;
	// Center
	center = PV2D(0, 0);
	// Radius
	radius = 15;
	numSides = 20;

	// NO CONSIGO QUE SALGA CON EL CENTRO EN (0,0)
	PV2D p1 = PV2D(edge/2, -radius * cos(0.157079));

	// Generate the ball
	vertex.push_back(p1);
	pen.setPos(p1);
	pen.setDir(0.31415);
	pen.forward(edge);

	for(int i=1; i<numSides; i++){
		PV2D p = pen.getPos();
		vertex.push_back(p);

		pen.turn(0.31415);
		pen.forward(edge);
	}

	// Movement vector
	vectorMov = PV2D(1,1);
}

void Ball::drawBall(){
	std::vector<PV2D>::iterator it;
	it = vertex.begin();

	glBegin(GL_POLYGON);
	for (int i=1; i<=numSides; ++i, ++it){
		glVertex2f(it->getPointX(), it->getPointY());
	}	
	glEnd();
}

void Ball::step(){
	std::vector<PV2D>::iterator it;
	it = vertex.begin();

	for(int i=1;i<=numSides; ++i, ++it){
		it->setPointX(it->getPointX() + vectorMov.getVectorX());
		it->setPointY(it->getPointY() + vectorMov.getVectorY());
	}
}