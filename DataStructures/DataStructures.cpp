// DataStructures.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Hash.h"
#include <stdlib.h>
#include <time.h>
#include "Queue.h"

#include <string>
#include <vector>
#include <iostream>

#include "BinaryTree.h"
#include "ThreadedBinaryTree.h"
#include "HeapTree.h"

using namespace std;

void demoHash()
{
	time_t t;
	vector<int> v;

	srand((unsigned)time(&t));
	int hashMethod = 1;
	cout << endl << "Inserting some random hash values..." << endl;
	cout << endl << "1. Linear Hashing" << endl;
	cout << endl << "2. Quadratic Hashing" << endl;
	cout << endl << "3. Double Hashing" << endl;
	cout << endl << "Choose the hashing algorithm : ";
	cin >> hashMethod;

	Hash *h = new Hash(hashMethod);
	for (int i = 0; i < MAX_SIZE / 2; i++) {
		int num = rand() % 50;
		v.push_back(num);
		h->insert(num);
	}

	cout << endl << "---------Hash Table Created-----------" << endl;
	h->printHashTable();

	for (int j = 0; j < v.size(); j++)
	{
		int num = v[j];
		cout << endl << "Finding " << num << " in the hash table" << endl;
		bool ret = h->find(num);
	}

	delete h;

}

void demoQueues()
{
	cout << endl << "------------Queues-------------" << endl;
	Queue q;

	q.add(10);
	q.add(23);
	q.add(45);

	q.print();

	cout << "\nRemoving " << q.remove() << endl;
	cout << "Removing " << q.remove() << endl;

	q.add(44);

	q.print();
}

void demoBST()
{
	cout << endl << "------------Binary Search Trees-------------- " << endl;
	BinaryTree bt;

	bt.insertIntoTree(10);
	bt.insertIntoTree(5);
	bt.insertIntoTree(3);
	bt.insertIntoTree(7);
	bt.insertIntoTree(6);
	bt.insertIntoTree(8);
	bt.insertIntoTree(15);
	bt.insertIntoTree(13);
	bt.insertIntoTree(18);
	bt.insertIntoTree(16);
	bt.insertIntoTree(17);
	bt.insertIntoTree(21);
	bt.insertIntoTree(19);
	bt.insertIntoTree(23);

	bt.printTree();

	int nodeToDelete;
	do {
		cout << endl << "Enter node to delete from BT (-1 to end) : ";
		cin >> nodeToDelete;
		bt.deleteFromTree(nodeToDelete);
		bt.printTree();
	} while (nodeToDelete != -1);
}

void demoHeapTree()
{
	cout << endl << "------------Heap Trees-------------- " << endl;
	HeapTree ht;
	int heapElements[] = { 10,5,15,3,7,13,18, 14 };
	ht.insertIntoHeap(heapElements);
	ht.printHeap();
	//ht.sortHeap();

	HeapTree ht1;
	int heapElements1[] = { 76, 69, 85, 35, 46, 58, 92, 40 };
	ht1.insertIntoHeap(heapElements1);
	ht1.printHeap();
	//ht1.sortHeap();

	ht.mergeHeap(&ht1);
	ht.printMergedHeap();
	ht.sortHeap();
	ht.printMergedHeap();
}

void demoTBT()
{
	cout << endl << "---------------------Threaded Trees-------------------" << endl;
	ThreadedBinaryTree tbt;
	tbt.insertIntoThreadedBT(15);
	tbt.insertIntoThreadedBT(10);
	tbt.insertIntoThreadedBT(3);
	tbt.insertIntoThreadedBT(1);
	tbt.insertIntoThreadedBT(7);
	tbt.insertIntoThreadedBT(6);
	tbt.insertIntoThreadedBT(5);
	tbt.insertIntoThreadedBT(8);
	tbt.insertIntoThreadedBT(12);
	tbt.insertIntoThreadedBT(20);
	tbt.insertIntoThreadedBT(19);
	tbt.insertIntoThreadedBT(22);

	tbt.traverseThreadedBT();

	int nodeToDelete;
	do {
		cout << endl << "Enter node to delete from threaded BT (-1 to end) : ";
		cin >> nodeToDelete;
		tbt.deleteFromThreadedBT(nodeToDelete);

		tbt.traverseThreadedBT();
	} while (nodeToDelete != -1);
}

int main()
{
	cout << "============This program will demonstrate usage of multiple data structures=============" << endl;
	cout << endl << "1. Hash" << endl;
	cout << endl << "2. Queues" << endl;
	cout << endl << "3. Binary Search Tree" << endl;
	cout << endl << "4. Heap Tree" << endl;
	cout << endl << "5. Threaded Binary Tree" << endl;
	cout << endl << "6. Quit" << endl;

	int choice = 0;
	cout << endl << "Please choose an Option : ";
	cin >> choice;
	switch (choice) {
	case 1:
		demoHash();
		break;
	case 2:
		demoQueues();
		break;
	case 3:
		demoBST();
		break;
	case 4:
		demoHeapTree();
		break;
	case 5:
		demoTBT();
		break;
	default:
		exit(0);
	}

	exit(0);
}

