#pragma once

#define MAX_SIZE 10
#define LINEAR 1
#define QUADRATIC 2
#define DOUBLE_HASH 3

class Hash
{
public:
	Hash(int method = 0);

	bool insert(int num);
	bool insert(int num, int hash);
	bool insertQuad(int num, int hash);
	bool insertDoubleHash(int num, int hash);
	int getLastPrime(int num);
	bool find(int num);
	bool findLinear(int num, int hash);
	void printHashTable();
private:
	int m_data[MAX_SIZE];
	int m_incr;
	int m_startingHashIndex;
	int m_method;
	int m_lastPrime;
};