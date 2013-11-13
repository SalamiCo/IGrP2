//Samuel Mendez Galán
//Pedro Morgado Alarcón

#include "Pencil.h"

Pencil::Pencil(){
	this->pos = PV2D();
	this->dir = 0;
}

Pencil::Pencil(PV2D p, GLdouble dir){
	this->pos = p;
	this->dir = dir;
}

void Pencil::setPos(PV2D p){
	this->pos = p;
}

void Pencil::setDir(GLdouble d){
	this->dir = d;
}

GLdouble Pencil::getDir(){
	return this->dir;
}

PV2D Pencil::getPos(){
	return this->pos;
}

void Pencil::turn(GLdouble d){
	//d>0 -> left, d<0 -> right
	this->dir += d;
} 

void Pencil::forward(GLdouble dist){
	GLdouble x = dist*cos(this->dir);
	GLdouble y = dist*sin(this->dir);
    this->pos.setPointX(pos.getPointX() + x);
    this->pos.setPointY(pos.getPointY() + y);     
}
