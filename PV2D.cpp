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

GLfloat PV2D::vectorModule(PV2D v){
	return sqrt(pow(v.getVectorX(),2) + pow(v.getVectorY(),2));
}

PV2D PV2D::normalizeVector(PV2D v){
	// Same direction but module = 1
	PV2D newV;
	GLfloat module = vectorModule(v);

	newV.setVectorX((1 / module) * v.getVectorX());
	newV.setVectorY((1 / module) * v.getVectorY());

	return newV;
}

GLfloat PV2D::dot(PV2D v, PV2D w){
	return (v.getVectorX() * w.getVectorX()) + (v.getVectorY() * w.getVectorY());
}

PV2D PV2D::normalVector(PV2D v){
	// Perpendicular vector to v with same module as v. Result by turning v to the left.
	PV2D normal;

	normal.setVectorX(-v.getVectorY());
	normal.setVectorY(v.getVectorX());

	return normal;
}

std::vector<GLfloat> PV2D::vectorDecomposition(PV2D v, PV2D n){
	GLfloat a, b;
	std::vector<GLfloat> numbers;

	a = dot(v, n) / dot(n, n);
	numbers.push_back(a);
	b = dot(v, normalVector(n)) / dot(normalVector(n), normalVector(n));
	numbers.push_back(b);

	return numbers;
}