//Samuel Mendez Galán
//Pedro Morgado Alarcón

#include "PV2D.h"

PV2D::PV2D(){
	this->x = 0;
	this->y = 0;
}

PV2D::PV2D(GLfloat x, GLfloat y){
	this->x = x;
	this->y = y;
}

GLfloat PV2D::getPointX(){
	return this->x;
}

GLfloat PV2D::getPointY(){
	return this->y;
}

GLfloat PV2D::getVectorX(){
	return this->x;
}

GLfloat PV2D::getVectorY(){
	return this->y;
}

void PV2D::setPointX(GLfloat x){
	this->x = x;
}

void PV2D::setPointY(GLfloat y){
	this->y = y;
}

void PV2D::setVectorX(GLfloat x){
	this->x = x;
}

void PV2D::setVectorY(GLfloat y){
	this->y = y;
}

GLfloat PV2D::vectorModule(){
	return sqrt(pow(this->getVectorX(),2) + pow(this->getVectorY(),2));
}

PV2D PV2D::normalizeVector(){
	// Same direction but module = 1
	PV2D newV;
	GLfloat module = this->vectorModule();

	newV.setVectorX((1 / module) * this->getVectorX());
	newV.setVectorY((1 / module) * this->getVectorY());

	return newV;
}

GLfloat PV2D::dot(PV2D w){
	return (this->getVectorX() * w.getVectorX()) + (this->getVectorY() * w.getVectorY());
}

PV2D PV2D::normalVector(){
	// Perpendicular vector to v with same module as v. Result by turning v to the left.
	PV2D normal;

	normal.setVectorX(-this->getVectorY());
	normal.setVectorY(this->getVectorX());

	return normal;
}

std::vector<GLfloat> PV2D::vectorDecomposition(PV2D v, PV2D n){
	GLfloat a, b;
	std::vector<GLfloat> numbers;

	a = v.dot(n) / n.dot(n);
	numbers.push_back(a);
	b = v.dot(n.normalVector()) / n.normalVector().dot(n.normalVector());
	numbers.push_back(b);

	return numbers;
}