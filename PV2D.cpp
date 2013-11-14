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