#pragma once
#include <iostream>

using namespace std;

class BaseColumn
{
public:
	BaseColumn* next_col;
	string label;

	BaseColumn();
	virtual void display() = 0;

	virtual void insertAtTail(int);
	virtual void insertAtTail(string);
	virtual void insertAtTail(char);
	virtual void insertAtTail(float);
	virtual void insertAtTail(bool);

};

