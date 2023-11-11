#pragma once

template<typename query>
class Queue
{
public:
	class node {
	public:
		query data;
		node* next;

		node() {
			next = nullptr;
		}
		node(query data) {
			this->data = data;
			next = nullptr;
		}
	};
	node* top;
	node* bottom;
	int size;
	
	Queue();
	void enqueue(query data);

	void dequeue();

	query peek();

};

