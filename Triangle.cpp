//Samuel Méndez Galán
//Pedro Morgado Alarcón

#include "Triangle.h"

Triangle::Triangle(){
	this->p1 = PV2D();
	this->p2 = PV2D();
	this->p3 = PV2D();
}

Triangle::Triangle(PV2D p1, PV2D p2, PV2D p3){
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
}

void Triangle::drawTriangle(PV2D p1, PV2D p2, PV2D p3){
	glBegin(GL_TRIANGLES);
		glVertex2f(p1.getPointX(), p1.getPointY());
		glVertex2f(p2.getPointX(), p2.getPointY());
		glVertex2f(p3.getPointX(), p3.getPointY());
	glEnd();
} 

void Triangle::drawWalls(GLfloat xRight, GLfloat xLeft, GLfloat yTop, GLfloat yBot){
	Triangle tR, tT, tL, tB;

	tR.drawTriangle(PV2D(xRight-30, yTop+20), PV2D(xRight-30, yBot-20), PV2D(xRight+300, yBot-20));
    tT.drawTriangle(PV2D(xLeft-20, yTop-30), PV2D(xRight+20, yTop-30), PV2D(xRight+20, yTop+450));
    tL.drawTriangle(PV2D(xLeft+30, yBot-20), PV2D(xLeft+30, yTop+20), PV2D(xLeft-300, yTop+20));
    tB.drawTriangle(PV2D(xRight+20, yBot+30), PV2D(xLeft-20, yBot+30), PV2D(xLeft-20, yBot-450));
}

bool Triangle::intersection2Ball(PV2D p, PV2D v, double& tIn, PV2D& normalIn){
	return true;
}