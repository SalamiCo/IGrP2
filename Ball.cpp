//Samuel Mendez Galán
//Pedro Morgado Alarcón

#include "Ball.h"

Ball::Ball(){
	// To calculate the edge size using radius => edge = 2 * radius * sin(0.157079)
	Pencil pen;
	GLfloat centerX=0, centerY=0;
	// Center
	center = PV2D(centerX, centerY);
	// Radius
	radius = 2;
	numSides = 20;
	GLfloat edge = 2 * radius * sin(0.157079);

	PV2D p1 = PV2D(centerX+edge/2, centerY-radius);

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
	/*int randomX, randomY;
	// initialize random seed
  	srand (time(NULL));
  	// Random number between -3 and 3 (creo...)
	randomX = rand() % 3 - 1;
	randomY = rand() % 3 - 1;
	vectorMov.setVectorX((GLfloat) randomX);
	vectorMov.setVectorY((GLfloat) randomY);*/
	vectorMov.setVectorX(1);
	vectorMov.setVectorY(0);
}

PV2D Ball::getCenter(){
	return this->center;
}

PV2D Ball::getV(){
	return this->vectorMov;
}

void Ball::drawBall(){
	std::vector<PV2D>::iterator it;
	it = vertex.begin();

	glBegin(GL_POLYGON);
	for (int i=1; i<=numSides; ++i, ++it){
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(it->getPointX(), it->getPointY());
	}
	glColor3f(1.0,1.0,0.0);
	glVertex2f(center.getPointX(), center.getPointY());	
	glEnd();
}

void Ball::step(double t){
	std::vector<PV2D>::iterator it;
	it = vertex.begin();

	for(int i=1;i<=numSides; ++i, ++it){
		it->setPointX(it->getPointX() + t * vectorMov.getVectorX());
		it->setPointY(it->getPointY() + t * vectorMov.getVectorY());
	}
	center.setPointX(center.getPointX() + t * vectorMov.getVectorX());
	center.setPointY(center.getPointY() + t * vectorMov.getVectorY());
}