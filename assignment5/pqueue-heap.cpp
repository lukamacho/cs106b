/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
#include <iostream>
#include "pqueue-heap.h"
#include "error.h"

/*
This function changes data index element to its parent if it is smaller than parent.
*/
void bubbleUp(string *data,int index){
	if(data[index]<data[(index-1)/2]){
		swap(data[(index-1)/2],data[index]);
		bubbleUp(data,(index-1)/2);
	}
}
/*
This function changes places to its data index element to the smallest of his children if it is smaller than
the index element in data.
*/
void bubbleDown(string * data,int index, int currentSize){
	if(2*index+2<currentSize){
		if(data[2*index+1]<data[2*index+2] && data[index]>data[2*index+1]){
			swap(data[index],data[2*index+1]);
			bubbleDown(data,2*index+1,currentSize);
		}else if(data[2*index+2]<=data[2*index+1] && data[index]>data[2*index+2])
			swap(data[index],data[2*index+2]);
			bubbleDown(data,2*index+2,currentSize);
	}else if(2*index+1<currentSize){
		if(data[index]>data[2*index+1]){
			swap(data[index],data[2*index+1]);
			bubbleDown(data,2*index+1,currentSize);
		}
	}
}
HeapPriorityQueue::HeapPriorityQueue() {
	data=new string[1];
	capacity=1;
	currentSize=0;
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete []data;
}

int HeapPriorityQueue::size() {
	return currentSize;
}

bool HeapPriorityQueue::isEmpty() {
	return currentSize==0;
}
void HeapPriorityQueue::enqueue(string value) {
	if(capacity==currentSize){
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
	bubbleUp(data,currentSize);
	currentSize++;
}

string HeapPriorityQueue::peek() {
	if(isEmpty()){
		error("No more elements");
	}
	return data[0];
}

string HeapPriorityQueue::dequeueMin() {
	if(isEmpty()){
		error("No more elements");
	}
	currentSize--;
	string result=data[0];
	data[0]=data[currentSize];
	bubbleDown(data,0,currentSize);
	return result;
}


