#include "Queue.h"
#include<iostream>


template<typename query>
Queue<query>::Queue() {
	top = bottom = nullptr;
	size = 0;
}

template<typename query>
void Queue<query>::enqueue(query data) {
	std::cout << data << std::endl;
	if (top == nullptr) {
		top =bottom= new node(data);
	}
	else {
		bottom->next = new node(data);
		bottom = bottom->next;
		
	}
	size++;
}

template<typename query>
void Queue<query>::dequeue() {
	if (top == nullptr) {
		std::cout << "empty queue, underflow." << std::endl;
	}
	else {
		node* temp = top;
		top = top->next;
		if (top == nullptr) {
		 bottom = nullptr;
		}
		delete temp;
	}
}

template<typename query>
query Queue<query>::peek() {
	if (top == nullptr) {
		std::cout << "empty queue, underflow."<<std::endl;
	}
	else {
		return top->data;
	}
}

template class Queue<std::string>;
