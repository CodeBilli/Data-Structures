#pragma once

typedef struct _data
{
	int num;
	struct _data* next;
} Node;

class Queue
{
private:
	Node* m_front = NULL;
	Node* m_back = NULL;
	int m_size;

public:
	Queue();
	~Queue();
	void add(int num);
	int remove();
	void print();
};

