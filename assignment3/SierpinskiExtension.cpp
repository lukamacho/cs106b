/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <cmath>
#include "gwindow.h"
#include "simpio.h"
#include "gtypes.h"
#include "queue.h"
#include "vector.h"
using namespace std;
void drawTriangle(int size, int order,GWindow &gw);
void drawSmallTriangle(GWindow &gw, Vector<double> koors);
int main() {
	GWindow gw;
	double cx=gw.getWidth()/2;
	double cy=gw.getHeight()/2;
	int size=getInteger("Enter the size of the triangle: ");
	int order=getInteger("Enter the order :");
	drawTriangle(size,order,gw);
    return 0;
}
/*
This code paints the n order triangle.
*/
void drawTriangle(int size, int order,GWindow & gw){
	double cx=gw.getWidth()/2;
	double cy=gw.getHeight()/2-size/2;
	double sig=(double)size;
	Queue< Vector<double> > coordinates;
	Vector<double> basics;
	double ydiff=sig*sqrt(3.0)/2;
	basics+=cx,cy,cx+sig/2,cy+ydiff,cx-sig/2,cy+ydiff;
	double numberity=(pow(3.0,order)-1)/2;
	coordinates.enqueue(basics);
	while(numberity>0){
		Vector<double> koors=coordinates.dequeue();
		/*
		Description of the midpoints of this triangle.
		*/
		double midRx=(koors[0]+koors[2])/2;
		double midLx=(koors[0]+koors[4])/2;
		double midx=(koors[2]+koors[4])/2;
		double midRy=(koors[1]+koors[3])/2;
		double midLy=(koors[1]+koors[5])/2;
		double midy=(koors[3]+koors[5])/2;
		/*
		Store traiangle koordinates in vectors.
		*/
		Vector<double>upper;
		upper+=koors[0],koors[1],midRx,midRy,midLx,midLy;
		Vector<double>right;
		right+=midRx,midRy,koors[2],koors[3],midx,midy;
		Vector<double>left;
		left+=midLx,midLy,midx,midy,koors[4],koors[5];
		coordinates.enqueue(upper);
		coordinates.enqueue(right);
		coordinates.enqueue(left);
		drawSmallTriangle(gw,koors);
		numberity--;
	}
}
/*
This code paints a triangle with the indexes of the vector.
*/
void drawSmallTriangle(GWindow & gw, Vector<double> basics){
	for(int i=0;i<6;i+=2){
		int a=(i+2)%6;
		int b=(i+3)%6;
		gw.drawLine(basics[i],basics[i+1],basics[a],basics[b]);
	}
}