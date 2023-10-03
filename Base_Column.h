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

	//stuck here
	virtual Node<int>* getHead();
	virtual Node<string>* getHead();

	virtual void insertAtTail(int);
	virtual void insertAtTail(string);
	virtual void insertAtTail(char);
	virtual void insertAtTail(float);
	virtual void insertAtTail(bool);

};

