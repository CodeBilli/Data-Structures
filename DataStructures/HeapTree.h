#pragma once
class HeapTree
{
public:
	HeapTree();
	~HeapTree();
	void insertIntoHeap(int *he);
	void insert(int data);
	void printHeap();
	void printMergedHeap();
	int removeHeapRoot();
	void sortHeap();
	void mergeHeap(HeapTree* ht);

	int m_numElements;

private:
	int m_heap[20]; /* Array will be used to stote elements in heap tree */
};

