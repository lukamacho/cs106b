/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
#include <iostream>
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
	data= new string[1] ;
	capacity=1;
	currentSize=0;
}

VectorPriorityQueue::~VectorPriorityQueue() {
	delete []data;
}

int VectorPriorityQueue::size() {
	return currentSize;
}

bool VectorPriorityQueue::isEmpty() {
	return currentSize==0;
}

void VectorPriorityQueue::enqueue(string value) {
	if(currentSize==capacity){
		string * temp=new string[capacity*2+1];
		for(int i=0;i<capacity;i++){
			temp[i]=data[i];
		}
		delete[]data;
		capacity*=2;
		capacity++;
		data=temp;
	}
	data[currentSize]=value;
	currentSize++;
}

string VectorPriorityQueue::peek() {
	if(isEmpty()){
	error("no more elements");
	}
	//int minIndex=findMinIndex(data,0,currentSize-1,data[0]);
	for(int i=0;i<currentSize-1;i++){
		if(data[i]<=data[i+1]){
			swap(data[i],data[i+1]);
		}
	}
	
	return data[currentSize-1];
}

string VectorPriorityQueue::dequeueMin() {
	if(isEmpty()){
	error("no more elements");
	}
	if(capacity>4*currentSize&&currentSize>0){
		capacity/=2;
		string * tmp=new string [capacity];
		for(int i=0;i<currentSize;i++){
			tmp[i]=data[i];
		}
		delete[]data;
		data=tmp;
	}
	string c=data[0];
	for(int i=0;i<currentSize-1;i++){
		if(data[i]<=data[i+1]){
			swap(data[i],data[i+1]);
		}
	}
	currentSize--;
	
	return data[currentSize];
}

