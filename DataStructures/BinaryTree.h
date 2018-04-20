#pragma once
#include <queue>
using namespace std;

typedef struct _treeNode {
	int data;
	struct _treeNode* parent;
	struct _treeNode* leftChild;
	struct _treeNode* rightChild;
} tnode;

class BinaryTree
{
private:
	tnode* m_root;
	
	queue<tnode*> m_q;
	void printNLR(tnode* node);
	void printLNR(tnode* node);
	void printLRN(tnode* node);
	
public:
	BinaryTree();
	~BinaryTree();
	void addNode(int val);
	void insertIntoTree(int value);
	void insertNode(tnode** n, tnode* parent, int value);
	tnode* findSuccessor(tnode* n);
	void deleteFromTree(int value);
	tnode* findNode(tnode* n, int value);
	void printTree();
	void printBreadthFirst(tnode* node);
	void deleteTree(tnode* tn);
	void deleteFromTree(tnode* n);

	
};

