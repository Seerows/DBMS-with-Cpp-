#pragma once
#include <iostream>
#include <Node.h>

using namespace std;

class Base_Column{

public:
	Base_Column* next_col;

	string label;

	Base_Column();
	virtual void display() = 0;

	virtual Base_Node& operator[](int index) = 0;

	virtual Base_Node* getHead() = 0;
	virtual Base_Node* getTail() = 0;

	virtual void insertAtTail(int);
	virtual void insertAtTail(string);
	virtual void insertAtTail(char);
	virtual void insertAtTail(float);
	virtual void insertAtTail(bool);

};

