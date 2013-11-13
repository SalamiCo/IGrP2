//Samuel Mendez Galán
//Pedro Morgado Alarcón

#include "PV2D.h"

PV2D::PV2D(){
	this->x = 0;
	this->y = 0;
}

PV2D::PV2D(GLdouble x, GLdouble y){
	this->x = x;
	this->y = y;
}

GLdouble PV2D::getPointX(){
	return this->x;
}

GLdouble PV2D::getPointY(){
	return this->y;
}

GLdouble PV2D::getVectorX(){
	return this->x;
}

GLdouble PV2D::getVectorY(){
	return this->y;
}

void PV2D::setPointX(GLdouble x){
	this->x = x;
}
void PV2D::setPointY(GLdouble y){
	this->x = y;
}