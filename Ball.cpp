//Samuel Mendez Galán
//Pedro Morgado Alarcón

#include "Ball.h"

Ball::Ball(){
	numSides = 20;
	Pencil pen;
	GLdouble edge = 10;
	PV2D p1 = PV2D(0, 0);

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
	// Sumar vector (1,1) -> diagonal
	std::vector<PV2D>::iterator it;
	it = vertex.begin();

	for(int i=1;i<=numSides; ++i, ++it){
		it->setPointX(it->getPointX() + 1);
		it->setPointY(it->getPointY() + 1);
	}
}