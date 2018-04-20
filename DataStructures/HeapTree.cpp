#include "stdafx.h"
#include "HeapTree.h"

#include <iostream>

using namespace std;

HeapTree::HeapTree()
{
	m_numElements = 0;
	for (int i = 0; i < 20; i++)
		m_heap[i] = 0;
}

void HeapTree::insertIntoHeap(int *he)
{
	for (int i = 0; i < 8; i++) {
		insert(he[i]);
	}
}

/*

Heap Tree stores its contents in an array. First element will be the total number of elements. 
For rest of the elements following rule is followed while inserting.
1. leftChild (i) = 2*i
2. rightChild(i) = 2*i + 1
3. parent (i) = | i/2 |

When we want to insert a new element, first add the element as the last element in the heap.
Then find its parent node and compare the values. If the new element is greater than its parent, 
they should swap their positions. Iteratively keep finding the new parent till the new value is
less than its parent.

*/
void HeapTree::insert(int data)
{
	int last = m_numElements + 1;
	m_heap[last] = data;
	int parent = 0;

	if (last != 1) {
		int j = last;
		while (1) {
			parent = j / 2;
			if (parent == 0) /* zeroth node is total no of elements. Hence skip. */
				break;
			if (m_heap[parent] < m_heap[j]) {
				// swap
				int temp = m_heap[parent];
				m_heap[parent] = m_heap[j];
				m_heap[j] = temp;

				j = parent;
			}
			else
				break;
		}
	}

	m_heap[0] += 1;
	m_numElements++;
	return;
}

int HeapTree::removeHeapRoot() 
{
	// [0] has the total number of elements
	// swap the last element with the root element (which is at [1])
	int numElements = m_heap[0];
	//cout << "Number of elements in heap : " << numElements << endl;
	int currentRoot = m_heap[1];

	// Move the last element to the current root position...
	m_heap[1] = m_heap[numElements];
	m_heap[numElements] = -1; // currentRoot;
	m_heap[0] -= 1;
	m_numElements -= 1;

	// Redraw the heap tree...
	int rootIndex = 1;
	while (1) {
		int leftChild = m_heap[rootIndex*2];
		int rightChild = m_heap[rootIndex*2 + 1];
		int indexToUse;

		if (leftChild > rightChild)
			indexToUse = rootIndex * 2;
		else
			indexToUse = rootIndex * 2 + 1;

		if (indexToUse > (numElements - 1))
			break;

		if (m_heap[rootIndex] < m_heap[indexToUse]) {
			int temp = m_heap[indexToUse];
			m_heap[indexToUse] = m_heap[rootIndex];
			m_heap[rootIndex] = temp;
			rootIndex = indexToUse;
			 
		}
		else {
			// root is greater than both left and right child....
			break;
		}
	}

	//cout << "Removed current root : " << currentRoot << endl;
	m_heap[numElements] = currentRoot;
	return currentRoot;
}

void HeapTree::sortHeap()
{
	while (m_heap[0] > 0)
	{
		removeHeapRoot();
	}
	cout << "Sorted Heap : ";
	cout << endl;
}

void HeapTree::mergeHeap(HeapTree* ht)
{
	cout << "Merging Heaps..." << endl;
	while (ht->m_numElements > 0) {
		int element = ht->removeHeapRoot();
		cout << "Num Elements : " << ht->m_numElements << "   Element : " << element << endl;
		insert(element);
		cout << "Num elements in the merged heap : " << m_numElements << endl;
	}
}

void HeapTree::printHeap()
{
	for (int i = 1; i <= 8; i++) {
		cout << m_heap[i] << " ";
	}
	cout << endl;
}

void HeapTree::printMergedHeap()
{
	for (int i = 1; i <= 16; i++) {
		cout << m_heap[i] << " ";
	}
	cout << endl;
}

HeapTree::~HeapTree()
{
}
