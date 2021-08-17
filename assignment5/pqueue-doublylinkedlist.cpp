/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */

#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	currentSize=0;
	head = new Node;
	tail = new Node;
	head->next=tail;
	head->prev=NULL;
	tail->prev=head;
	tail->next=NULL;
	
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	Node* ptr=head;
	while(ptr!=tail){
		Node*tmp=ptr;
		ptr=ptr->next;
		delete tmp;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	return currentSize;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	return currentSize==0;
}

void DoublyLinkedListPriorityQueue::enqueue(string val) {
	currentSize++;
	Node * ptr=head;
	bool q=false;
	while(ptr->next!=tail){
		if(val<ptr->next->value){
			Node *newNode= new Node;
			newNode->value=val;
			newNode->next=ptr->next;
			newNode->prev=ptr;
			ptr->next=newNode;
			newNode->next->prev=newNode;
			q=true;
			break;
		}
		ptr=ptr->next;
	}
	/*If current string is the biggest lexicography in the linked list*/
	if(q==false){
	Node* newNode = new Node;
	newNode -> value = val;
	newNode -> next = ptr -> next;
    ptr -> next = newNode;
	newNode->next->prev=newNode;
	}
}

string DoublyLinkedListPriorityQueue::peek() {
	if(isEmpty()){
		error("No more elements");
	}
	Node*tmp= head->next;
	string result =tmp->value;
	return result;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	if(isEmpty()){
		error("No more elements");
	}
	currentSize--;
	Node* tmp = head -> next;
	head -> next = tmp -> next;
	tmp -> next -> prev = head;
	string result = tmp -> value;

	delete tmp;
	return result;
}

