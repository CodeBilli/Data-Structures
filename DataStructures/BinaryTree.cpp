#include "stdafx.h"
#include <string>
#include <iostream>

#include "BinaryTree.h"

using namespace std;

BinaryTree::BinaryTree()
{
	m_root = NULL;
}


BinaryTree::~BinaryTree()
{

}

void BinaryTree::addNode(int value)
{
	tnode* newNode = new tnode;
	newNode->data = value;
	newNode->parent = NULL;
	newNode->rightChild = NULL;
	newNode->leftChild = NULL;

	if (m_root == NULL) {
		m_root = newNode;
	}
	else {
		tnode* temp = m_root;
		tnode* prevTemp = temp;
		string pos = "left";
		while (temp != NULL) {
			if (temp->data == value) {
				cout << "Data already present!!!" << endl;
				break;
			}
			else if (temp->data > value) {
				// keep moving on the left side of the tree...
				prevTemp = temp;
				temp = temp->leftChild;
				pos = "left";
			}
			else if(temp->data < value) {
				// keep moving on the right side of the tree...
				prevTemp = temp;
				temp = temp->rightChild;
				pos = "right";
			}
		}
		if (pos == "left") {
			prevTemp->leftChild = newNode;
		}
		else {
			prevTemp->rightChild = newNode;
		}
	}
}

void BinaryTree::insertNode(tnode** n, tnode* parent, int value)
{
	if (*n == NULL)
	{
		tnode* newNode = new tnode;
		newNode->data = value;
		newNode->parent = parent;
		newNode->rightChild = NULL;
		newNode->leftChild = NULL;
		*n = newNode;
	}
	else {
		if ((*n)->data > value) {
			insertNode(&((*n)->leftChild), *n, value);
		}
		else if ((*n)->data < value) {
			insertNode(&((*n)->rightChild), *n, value);
		}
		else {
			cout << "Data already present!!!" << endl;
		}
	}
}

void BinaryTree::insertIntoTree(int value)
{
	insertNode(&m_root, NULL, value);
}

void BinaryTree::printTree()
{
	//cout << "-----------------NLR--------------" << endl;
	//printNLR(m_root);
	//cout << "-----------------LNR--------------" << endl;
	//printLNR(m_root);
	//cout << "-----------------LRN--------------" << endl;
	//printLRN(m_root);

	cout << endl << "-----------------Breadth First Display --------------" << endl;
	printBreadthFirst(m_root);
}

void BinaryTree::printNLR(tnode* node)
{
	if (node == NULL)
		return;
	cout << "Element Value is " << node->data << endl;
	printNLR(node->leftChild);
	printNLR(node->rightChild);
}

void BinaryTree::printLNR(tnode* node)
{
	if (node == NULL)
		return;
	printLNR(node->leftChild);
	cout << "Element Value is " << node->data << endl;
	printLNR(node->rightChild);
}

void BinaryTree::printLRN(tnode* node)
{
	if (node == NULL)
		return;
	printLRN(node->leftChild);
	printLRN(node->rightChild);
	cout << "Element Value is " << node->data << endl;

}

void BinaryTree::printBreadthFirst(tnode* node)
{
	tnode* tmp = node;
	while (tmp != NULL) {
		cout << "Node : " << tmp->data << " Parent : " << (tmp->parent ? (tmp->parent->data) : 0) << " Left : " << (tmp->leftChild ? (tmp->leftChild->data) : 0) << " Right : " << (tmp->rightChild ? (tmp->rightChild->data) : 0) << endl;

		if (tmp->leftChild != NULL)
			m_q.push(tmp->leftChild);

		if (tmp->rightChild != NULL)
			m_q.push(tmp->rightChild);

		if (!m_q.empty()) {
			tmp = m_q.front();
			m_q.pop();
		}
		else
			tmp = NULL;
	}
}

tnode* BinaryTree::findSuccessor(tnode* n)
{
	tnode* temp = NULL;
	if (n != NULL) {
		temp = n->rightChild;
		if (temp != NULL) {
			while (temp->leftChild != NULL) {
				temp = temp->leftChild;
			}
		}
		else {
			// There is no left child for this right child... Just return the same node...
		}
	}
	return temp;
}

tnode* BinaryTree::findNode(tnode* n, int value)
{
	if (n == NULL)
		return NULL;
	else {
		if (n->data > value)
			return findNode(n->leftChild, value);
		else if (n->data < value)
			return findNode(n->rightChild, value);
		else
			return n;
	}
	
}

void BinaryTree::deleteTree(tnode* tn)
{
	// Use LRN to delete tree...
	if (tn->leftChild != NULL)
		deleteTree(tn->leftChild);

	if (tn->rightChild != NULL)
		deleteTree(tn->rightChild);

	cout << "Deleting Node with Value : " << tn->data << endl;
	deleteFromTree(tn);
}

void BinaryTree::deleteFromTree(tnode* n)
{
	if (n != NULL) {
		if (n->parent == NULL) {
			if (n->leftChild == NULL && n->rightChild == NULL) {
				cout << "Deleting the root node..." << endl;
				delete n;
				m_root = NULL;
				return;
			}
			else {
				cout << "Root has children... Cannot delete!!!" << endl;
				deleteTree(m_root);
				return;
			}
		}
		cout << "Found the element.. Its root is " << n->parent->data << endl;

		// Find the successor of the node...
		tnode* succ = findSuccessor(n);
		if (succ != NULL) {
			cout << "Found the Successor.. Data : " << succ->data << endl;

			// copy succ data to the node to delete...
			n->data = succ->data;

			// delete that successor node...
			if (succ->rightChild == NULL) {
				if (succ->parent->leftChild == succ) {
					succ->parent->leftChild = NULL;
				}
				else if (succ->parent->rightChild == succ) {
					succ->parent->rightChild = NULL;
				}
			}
			else {
				// Succ has a right child...
				succ->parent->rightChild = succ->rightChild;
				succ->rightChild->parent = succ->parent;
			}

			delete succ;
		}
		else {
			cout << "There is no successor..." << endl;

			// find out if this node is left node or right node of its parent...
			if (n->parent->leftChild == n) {
				n->parent->leftChild = NULL;
			}
			else if (n->parent->rightChild == n) {
				n->parent->rightChild = NULL;
			}
			delete n;
		}
	}
}

void BinaryTree::deleteFromTree(int value)
{
	// First, find this node in the tree...
	tnode* n = findNode(m_root, value);

	deleteFromTree(n);
}
