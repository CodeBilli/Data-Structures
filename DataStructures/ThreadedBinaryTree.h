#pragma once

typedef struct _threadedTreeNode {
	int data;
	struct _threadedTreeNode* parent;
	struct _threadedTreeNode* leftChild;
	struct _threadedTreeNode* rightChild;
	int leftTag;
	int rightTag;
} threadedTnode;

class ThreadedBinaryTree
{
private:
	threadedTnode* m_tRoot;
public:
	ThreadedBinaryTree();
	~ThreadedBinaryTree();

	threadedTnode* findLeftMostNode(threadedTnode* n);
	threadedTnode* findRightMostNode(threadedTnode* n);
	void insertIntoThreadedBT(int value);
	void traverseThreadedBT();
	threadedTnode* findNode(threadedTnode* n, int value);
	void deleteFromThreadedBT(int val);
};

