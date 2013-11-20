//Samuel Méndez Galán
//Pedro Morgado Alarcón

#include "Triangle.h"

Triangle::Triangle(){
	PV2D v1,v2,v3;

	this->p1 = PV2D();
	this->p2 = PV2D();
	this->p3 = PV2D();
}

Triangle::Triangle(PV2D p1, PV2D p2, PV2D p3){
	PV2D v1,v2,v3;

	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;

	// Normal vectors normalized
	v1.setVectorX(p1.getPointX() - p2.getPointX());
	v1.setVectorY(p1.getPointY() - p2.getPointY());
	this->n1 = v1.normalVector().normalizeVector();

	v2.setVectorX(p2.getPointX() - p3.getPointX());
	v2.setVectorY(p2.getPointY() - p3.getPointY());
	this->n2 = v2.normalVector().normalizeVector();

	v3.setVectorX(p3.getPointX() - p1.getPointX());
	v3.setVectorY(p3.getPointY() - p1.getPointY());
	this->n3 = v3.normalVector().normalizeVector();

	// Center
	this->center = triangleCenter(p1, p2, p3);
}

PV2D Triangle::getP1(){
	return this->p1;
}

PV2D Triangle::getP2(){
	return this->p2;
}

PV2D Triangle::getP3(){
	return this->p3;
}

//Only used for intersection.
PV2D Triangle::getP(int i){
	PV2D p;
	switch(i){
		case 0:
			p = this->p1;
			break;
		case 1:
			p = this->p2;
			break;
		case 2:
			p = this->p3;
			break;
	}
	return p;
}

//Only used for intersection.
PV2D Triangle::getN(int i){
	PV2D n;
	switch(i){
		case 0:
			n = this->n1;
			break;
		case 1:
			n = this->n2;
			break;
		case 2:
			n = this->n3;
			break;
	}
	return n;
}

void Triangle::drawTriangle(PV2D p1, PV2D p2, PV2D p3){

	glColor3f(0.38, 0.19, 0.0);
	glBegin(GL_TRIANGLES);
		glVertex2f(p1.getPointX(), p1.getPointY());
		glVertex2f(p2.getPointX(), p2.getPointY());
		glVertex2f(p3.getPointX(), p3.getPointY());
	glEnd();
} 

void Triangle::drawWalls(Triangle tR, Triangle tT, Triangle tL, Triangle tB){	

	drawTriangle(tR.getP1(), tR.getP2(), tR.getP3());
    drawTriangle(tT.getP1(), tT.getP2(), tT.getP3());
    drawTriangle(tL.getP1(), tL.getP2(), tL.getP3());
    drawTriangle(tB.getP1(), tB.getP2(), tB.getP3());
}

bool Triangle::intersection2Ball(PV2D p, PV2D v, double& tIn, PV2D& normalIn){
	GLfloat dist[3], proj[3], sign[3];
	//Compute the vectors dist, proj and sign
	for(int i=0; i<3; i++){
		PV2D w;
		w.setVectorX(this->getP(i).getPointX() - p.getPointX());
		w.setVectorY(this->getP(i).getPointY() - p.getPointY());
		dist[i] = w.dot(v.normalVector());
		proj[i] = w.dot(v);
		if(dist[i] > 0) sign[i] = 1;
		else if(dist[i] == 0) sign[i] = 0;
		else sign[i] = -1;
	}

	int sum = sign[0] + sign[1] + sign[2];
	if(abs(sum) == 3) return false; // Trivial failure
	int nHits = 0; double hit[3]; PV2D n[3]; // For recording tHits and normals

	for(int i=0; i<3; i++){
		int j = (i+1) % 3; //Intersections edge-line
		if((sign[i]*sign[j]) < 0){
			// Compute numerator
			double numerator = (proj[i] * dist[j]) - (dist[i] * proj[j]); 
			// Compute denominator
			double denominator = dist[j] - dist[i];
			hit[nHits] = numerator/denominator;
			n[nHits] = this->getN(i);
			nHits++;
		}
	}

	if(nHits < 2){ //Intersections vertex-line
		for(int i=0; i<3 && sign[i]==0; i++){
			hit[nHits] = proj[i];
			n[nHits] = vectorFromCenter(this->getP(i));
			nHits++; 
		}
	}

	int m = minimum(hit, nHits);
	tIn = hit[m];
	normalIn = n[m];

	return true;
}

int Triangle::minimum(double hit[], int nHits){
	double minimum = hit[0];
	int index = 0;

	for(int i=1;i<nHits;i++){
		if(hit[i] < minimum){
			minimum = hit[i];
			index = i;
		} 
	}

	return index;
}

PV2D Triangle::vectorFromCenter(PV2D p){
	PV2D vector;

	vector.setVectorX(p.getPointX() - center.getPointX());
	vector.setVectorY(p.getPointY() - center.getPointY());

	return vector;
}

PV2D Triangle::triangleCenter(PV2D p1, PV2D p2, PV2D p3){
	PV2D center;
	GLfloat sumX, sumY;

	sumX = (p1.getPointX() + p2.getPointX() + p3.getPointX())/3;
	sumY = (p1.getPointY() + p2.getPointY() + p3.getPointY())/3;

	center.setPointX(sumX);
	center.setPointY(sumY);

	return center;
}