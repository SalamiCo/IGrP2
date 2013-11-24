//Samuel Méndez Galán
//Pedro Morgado Alarcón
 
#include "Circle.h"

Circle::Circle(){
	Pencil pen;
	// Center
	this->center = PV2D(-50, 100);
	// Radius
	this->radius = 30;
	this->radius2 = radius*radius;

	numSides = 20;
	GLfloat edge = 2 * radius * sin(0.157079);

	PV2D p1 = PV2D(this->center.getPointX()+edge/2, this->center.getPointY()-radius);

	// Generate the circle
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

Circle::Circle(PV2D center, GLfloat radius){
	Pencil pen;
	// Center
	this->center = center;
	// Radius
	this->radius = radius;
	this->radius2 = radius*radius;

	numSides = 20;
	GLfloat edge = 2 * radius * sin(0.157079);

	PV2D p1 = PV2D(this->center.getPointX()+edge/2, this->center.getPointY()-radius);

	// Generate the circle
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

void Circle::drawCircle(){
	std::vector<PV2D>::iterator it;
	it = vertex.begin();

	glBegin(GL_POLYGON);
	for (int i=1; i<=numSides; ++i, ++it){
		glVertex2f(it->getPointX(), it->getPointY());
	}
	glVertex2f(this->center.getPointX(), this->center.getPointY());	
	glEnd();
}

bool Circle::intersection2Ball(PV2D p, PV2D v, double& tIn, PV2D& normalIn){
	GLfloat A,B,C, delta;
	PV2D vectorCP;

	A = v.dot(v);
	vectorCP.setVectorX(p.getPointX() - this->center.getPointX());
	vectorCP.setVectorY(p.getPointY() - this->center.getPointY());
	B = 2 * vectorCP.dot(v);
	C = vectorCP.dot(vectorCP) - this->radius2;

	delta = (B*B) - 4*A*C;
	if(delta < 0) return false; // No intersection
	else if(delta == 0){ // One intersection
		tIn = ((-1)*B) / (2*A);
	}else{ //delta > 0 => Two intersections, save only one
		tIn = (((-1)*B) - sqrt(delta)) / (2*A);
	}

	PV2D intersection; //Point of intersection
	intersection.setPointX(p.getPointX() + tIn * v.getVectorX());
	intersection.setPointY(p.getPointY() + tIn * v.getVectorY());

	// Normal vector: from center to intersection point
	normalIn.setVectorX(intersection.getPointX() - this->center.getPointX());
	normalIn.setVectorY(intersection.getPointY() - this->center.getPointY());

	return true;
}