#include "stdafx.h"
#include "ThreadedBinaryTree.h"

#include <string>
#include <iostream>

using namespace std;

ThreadedBinaryTree::ThreadedBinaryTree()
{
}


ThreadedBinaryTree::~ThreadedBinaryTree()
{
}

void ThreadedBinaryTree::insertIntoThreadedBT(int value)
{
	threadedTnode* newNode = new threadedTnode;
	newNode->data = value;
	newNode->parent = NULL;
	newNode->rightChild = NULL;
	newNode->leftChild = NULL;
	newNode->leftTag = 0;
	newNode->rightTag = 0;

	if (m_tRoot == NULL) {
		m_tRoot = newNode;
	}
	else {
		threadedTnode* temp = m_tRoot;
		threadedTnode* current = temp;
		string pos = "";
		while (temp != NULL) {
			current = temp;
			if (value < temp->data) {
				if (temp->leftTag == 0) {
					temp = NULL;
				}
				else {
					temp = temp->leftChild;
				}
				pos = "left";
			}
			else if (value > temp->data) {
				if (temp->rightTag == 0) {
					temp = NULL;
				}
				else {
					temp = temp->rightChild;
				}
				pos = "right";
			}
			else {
				cout << "Node already present!!!" << endl;
				return;
			}
		}

		if (current != NULL) {
			if (pos == "left") {
				newNode->parent = current;
				newNode->rightTag = 0;
				newNode->rightChild = current;

				current->leftTag = 1;
				current->leftChild = newNode;
			}
			else if (pos == "right") {
				newNode->parent = current;

				newNode->leftTag = 0;
				newNode->leftChild = NULL;

				newNode->rightTag = 0;
				newNode->rightChild = current->rightChild;

				current->rightTag = 1;
				current->rightChild = newNode;
			}
		}
	}
}

threadedTnode* ThreadedBinaryTree::findLeftMostNode(threadedTnode* n)
{
	//cout << "Traversing threaded Tree..." << endl;
	if (n != NULL) {
		while (n->leftChild != NULL) {
			if (n->leftTag == 0) {
				break;
			}
			n = n->leftChild;
		}
	}
	return n;
}

threadedTnode* ThreadedBinaryTree::findRightMostNode(threadedTnode* n)
{
	//cout << "Traversing threaded Tree..." << endl;
	if (n != NULL) {
		while (n->rightChild != NULL) {
			if (n->rightTag == 0) {
				break;
			}
			n = n->rightChild;
		}
	}
	return n;
}

void ThreadedBinaryTree::traverseThreadedBT()
{
	// This is always In order traversal...

	// First find the left most node...
	threadedTnode* temp = findLeftMostNode(m_tRoot);

	while (temp != NULL) {
		// Print the value of the node...
		cout << "Node : " << temp->data << " Parent : " << (temp->parent ? (temp->parent->data) : 0) << " Left : " << (temp->leftChild ? (temp->leftChild->data) : 0) << " Right : " << (temp->rightChild ? (temp->rightChild->data) : 0) << endl;

		// check if this node is a threaded node...
		if (temp->rightTag == 0) {
			temp = temp->rightChild;
		}
		else {
			temp = findLeftMostNode(temp->rightChild);
		}
	}
	cout << endl;
}

threadedTnode* ThreadedBinaryTree::findNode(threadedTnode* n, int value)
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

void ThreadedBinaryTree::deleteFromThreadedBT(int val)
{
	// Find the node in threaded BT...
	threadedTnode* ttn = findNode(m_tRoot, val);
	if (ttn == NULL)
		return;

	// Get the parent of this node...
	threadedTnode* pn = ttn->parent;
	if (pn == NULL) {
		if (ttn->leftChild == NULL && ttn->rightChild == NULL) {
			cout << "Only root node is present.. Safe to delete the root..." << endl;
			delete ttn;
			m_tRoot = NULL;
			return;
		}
		else {
			cout << "Root node has children.. cannot delete non-empty root..." << endl;
			return;
		}
	}

	cout << "Parent of " << val << " is " << pn->data << endl;

	// check for various cases...
	if ((ttn->leftChild == NULL || ttn->leftTag == 0) &&
		(ttn->rightChild == NULL || ttn->rightTag == 0)) {
		cout << "Leaf Node...";
		// Leaf node...
		if ((pn->leftChild) && (pn->leftChild)->data == val) {
			// left child of parent
			cout << "Left child of parent..." << endl;

			pn->leftChild = NULL;
		}
		else if ((pn->rightChild) && (pn->rightChild)->data == val) {
			// Right child of parent
			cout << "Right child of parent..." << endl;

			pn->rightTag = 0;
			pn->rightChild = ttn->rightChild;
		}
		delete ttn;
	}
	else {
		// Not a leaf node...
		// Find successor...
		threadedTnode* succ = NULL;
		threadedTnode* rightMost = NULL;

		if (ttn->rightChild && ttn->rightTag == 1) {
			succ = findLeftMostNode(ttn->rightChild);
			cout << "Not a leaf node... Successor is " << succ->data << endl;
		}
		else {
			cout << "No successor..." << endl;
		}

		if (succ != NULL) {
			// copy succ data to the node to delete...
			ttn->data = succ->data;

			// delete that successor node...
			if (succ->rightChild == NULL || succ->rightTag == 0) {
				if (succ->parent->leftChild == succ) {
					succ->parent->leftChild = NULL;
				}
				else if (succ->parent->rightChild == succ) {
					succ->parent->rightTag = 0;
					succ->parent->rightChild = succ->rightChild;
				}
			}
			else {
				// Succ has a right child...
				cout << "Successor has right child : " << succ->rightChild->data << endl;
				succ->parent->rightChild = succ->rightChild;
				succ->rightChild->parent = succ->parent;
			}
			delete succ;
		}
		else {
			// There is no successor...
			if (ttn->leftChild != NULL) {
				cout << "Left child is not NULL.. Left child is : " << ttn->leftChild->data << endl;
				if (ttn->parent->leftChild == ttn) {
					cout << "Setting parents leftchild..." << endl;
					ttn->parent->leftChild = ttn->leftChild;
				}
				else if (ttn->parent->rightChild == ttn) {
					cout << "Setting parents rightchild..." << endl;
					ttn->parent->rightChild = ttn->leftChild;
				}

				if (ttn->leftChild->rightTag == 0) {
					// leftchild is a leaf node...
					cout << "Left child is a leaf node..." << endl;
					ttn->leftChild->parent = ttn->parent;
					if (ttn->data > ttn->parent->data) {
						// If we are on the Right side of root, we should not set threaded successor...
						ttn->leftChild->rightTag = 1;
						ttn->leftChild->rightChild = NULL;
					}
					else {
						ttn->leftChild->rightTag = 0;
						ttn->leftChild->rightChild = ttn->parent;
					}
				}
				else {
					cout << "Left child is NOT a leaf node..." << endl;
					ttn->leftChild->parent = ttn->parent;
					cout << "Finding predecessor to parent" << endl;
					// Find the predecessor to the parent...
					rightMost = findRightMostNode(ttn->leftChild);
					cout << "Predecessor to parent is : " << rightMost->data << endl;
					rightMost->rightChild = ttn->parent;
				}

				cout << "deleting the node" << endl;
				delete ttn;
			}
		}
	}
}
