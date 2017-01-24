/*

	Classes for linked list of events - LLNODE, LIST, and EVENT.
	
	Author:		Larry Henschen
	Last Modified:	Dec 1, 2016 (Sara Sood)


*/

#include "definitions.h"
#include "events.h"

#include <iostream>
using namespace std;


// Functions for class LLNODE.  LLNODE is the list node for each element in the list.
// It contains a pointer to the actual data and a pointer to the next node in the list.

LLNODE::LLNODE(EVENT *e) {
	ev = e;
	next = NULL;
}

LLNODE::~LLNODE() {
    delete ev;
}

// Functions for class LIST.  LIST contains the pointer to the front of the list.

LIST::LIST() {
	front = NULL;
}

LIST::~LIST() {
	LLNODE *tmp, *tmpNext;
	
	tmp = front;
	while(tmp!=NULL) {
		tmpNext = tmp->next;
		delete tmp;
		tmp = tmpNext;
	}
}

void LIST::display() {
	LLNODE *tmp;  int k;
	
	tmp = front;   k = 1;
    cout << "Displaying Event list." << endl;
	while(tmp!=NULL) {
        cout << "Node " << k << ":" << endl;
		(tmp->ev)->display();
		tmp = tmp->next;
		k += 1;
	}
}

EVENT *LIST::getFirstEvent() {
	if(front==NULL)  return NULL;
	else             return front->ev;
}

void  LIST::removeFirstEvent() {
	LLNODE *tmp;
	
	if(front==NULL) return;		// If empty, do nothing.
	
	tmp = front;			// Else remember thee front node,
	front = front->next;		//    move ffront to the second node,
	delete tmp;			//    and then delete the old front node.
}

void LIST::insertEvent(EVENT *e) {
    LLNODE* left;
    LLNODE* right;
    LLNODE* newnode;
	int etime, tmptime;
	
	newnode = new LLNODE(e);      // Create the new node.
	etime = e->getProcessTime();
	
	// If the list is empty, then the new node just becomes the front 
	// of the list.
	if(front==NULL) {
		front = newnode;
		return;
	}
	
	// Otherwise, first find where the new node goes.
	left = NULL;
    right = front;
	while(right!=NULL) {
		tmptime = (right->ev)->getProcessTime();
		if(etime<tmptime) break;
		left = right;
		right = right->next;
	}
	
	// There are two cases.  If left is still NULL, the new node goes at the front
	// of the list.  Otherwise, the new node goes between left and right.  The latter
	// case includes the case when the new node goes at the end (right==NULL).
	if(left!=NULL) {
		// The new node goes between left and right, including goes at the
		// end (right==NULL).
		left->next = newnode;
		newnode->next = right;
	}
	else {
		// The new node goes at the front.
		newnode->next = front;
		front = newnode;
	}
}

void LIST::removeEventsNamed(string n) {
	LLNODE* tempNode = front;
	LLNODE* prevNode = NULL;
	
	// Case 1: Is the list empty?
	if (tempNode != NULL) {
		while ((tempNode != NULL) && ((tempNode->ev)->getDeviceName() != n)) {
			prevNode = tempNode;
			tempNode = tempNode->next;
		}
		// Case 2: Did we find the first case?
		if (prevNode == NULL)
		{
			front = front->next;
			delete tempNode;
		}
		// Case 3: Did we find a case in the middle? + Case 4: Did we find a case at the end?
		else if (tempNode != NULL) {
			// we want to remove the node tempNode is on (b/c that means the name matches)
			prevNode->next = tempNode->next;
			delete tempNode;
		}
		// NULL Case: Did we find any matches?
		else
		{
			cout << "No such device exists." << endl;
		}
	}
	// The list is empty
	else
	{
		cout << "List is empty" << endl;
	}
}

// Functions for class EVENT.  

EVENT::EVENT(string n, int v, int pt) {
    device = n;
    value = v;
	processTime = pt;
}

void EVENT::display() {

	cout << "EVENT: Device = " << device <<
    "\nDevice code: " << value << ". Scheduled to be process at : " << processTime << endl;
}

int EVENT::getProcessTime() {
	return processTime;
}

string EVENT::getDeviceName() {
    return device;
}

int EVENT::getValue() {
    return value;
}

