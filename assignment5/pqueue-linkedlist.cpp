/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */

#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	currentSize=0;
	head = new Node;
	tail = new Node;
	head -> next=tail;
	tail -> next=NULL;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	Node* ptr=head;
	while(ptr!=tail){
		Node*tmp=ptr;
		ptr=ptr->next;
		delete tmp;
	}
}

int LinkedListPriorityQueue::size() {
	return currentSize;
}

bool LinkedListPriorityQueue::isEmpty() {
	return currentSize==0;
}

void LinkedListPriorityQueue::enqueue(string val) {
	currentSize++;
	Node* ptr=head;
	bool q=false;
	while(ptr->next!=tail){
		if(val<ptr->next->value){
			Node* newNode = new Node;
			newNode -> value = val;
			newNode -> next = ptr->next;;
			ptr -> next = newNode;
			q=true;
			break;
		}ptr=ptr->next;
	}
	/*If current string is the biggest lexicography in the linked list*/
	if(q==false){
	Node* newNode = new Node;
	newNode -> value = val;
	newNode -> next = ptr -> next;
    ptr -> next = newNode;
	}
}

string LinkedListPriorityQueue::peek() {
	if(isEmpty()){
		error("No more elements");
	}
	Node*tmp=head->next;
	string result=tmp->value;

	return result;
}

string LinkedListPriorityQueue::dequeueMin() {
	if(isEmpty()){
		error("No more elements");
	}currentSize--;
	
	Node* tmp = head -> next;
	head -> next = tmp -> next;
	string result = tmp -> value;

	delete tmp;
	return result;
}

