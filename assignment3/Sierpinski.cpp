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
using namespace std;
/*
Description of the orders.
*/
void paintSierpinskiTriangle(GWindow &gw,double x,double y,double size,int order);
void drawTriangle(GWindow &gw, double x,double y, double size);
int main() {
	GWindow gw;
	int sizes=getInteger("Enter the size of the triangle: ");
	double size=(double)sizes;
	double cx=gw.getWidth()/2+size/2;
	double cy=gw.getHeight()/2+(size/2)/sqrt(3.0);
	int order;
	while(true){
		order=getInteger("Enter the order : ");
		if(pow(2.0,order)<sizes){
			break;
		}
		cout<<"Enter lower order!"<<endl;
	}
	paintSierpinskiTriangle(gw,cx,cy,size,order);
    return 0;
}
/*
This code paints sierpinski n order triangle by recurion.
*/
void paintSierpinskiTriangle(GWindow &gw,double x,double y,double size,int order){
	if(order==0){
		drawTriangle(gw,x,y,size);
	}
	else{
		paintSierpinskiTriangle(gw,x,y,size/2,order-1);
		paintSierpinskiTriangle(gw,x-size/2,y,size/2,order-1);
		paintSierpinskiTriangle(gw,x-size/4,y-size*sqrt(3.0)/4,size/2,order-1);
	}
}
/*
This code paints sierpinskis 0 order triangle.
*/
void drawTriangle(GWindow & gw,double x, double y,double size){
	GPoint pt(x,y);
	pt=gw.drawPolarLine(pt,size,0);
	pt=gw.drawPolarLine(pt,size,120);
	pt=gw.drawPolarLine(pt,size,-120);
}
			   
