#include "stdafx.h"
#include "Queue.h"
#include <iostream>

using namespace std;

Queue::Queue()
{
}


Queue::~Queue()
{
}

void Queue::add(int num)
{
	Node *d = new Node;
	d->num = num;
	d->next = NULL;

	if (m_size == 0)
	{
		m_front = m_back = d;
	}
	else
	{
		m_back->next = d;
		m_back = d;
	}
	m_size++;
}

int Queue::remove()
{
	if (m_size == 0)
		return -1;
	int ret = m_front->num;
	Node* cur = m_front;
	m_front = m_front->next;
	delete cur;

	return ret;
}

void Queue::print()
{
	Node* ptr = m_front;
	while (ptr != NULL)
	{
		cout << ptr->num << endl;
		ptr = ptr->next;
	}
}