#include "stdafx.h"

#include "Hash.h"
#include <string>
#include <iostream>

using namespace std;

Hash::Hash(int method)
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		m_data[i] = -1;
	}
	m_incr = 0;
	m_startingHashIndex = 0;
	m_method = method;
	m_lastPrime = getLastPrime(MAX_SIZE);
	cout << "Last Prime = " << m_lastPrime << endl;
}

int Hash::getLastPrime(int num)
{
	for (int i = num-1; i > 0; i--)
	{
		bool prime = true;
		for (int j = 2; j < i; j++)
		{
			if (i%j == 0)
			{
				prime = false;
				break;
			}
		}
		if (prime == true)
			return i;
	}
}

bool Hash::insert(int num)
{
	bool ret = true;
	if (m_method == LINEAR)
		ret = insert(num, num);
	else if (m_method == QUADRATIC)
	{
		m_startingHashIndex = num % MAX_SIZE;
		m_incr = 0;
		ret = insertQuad(num, num);
	}
	else if (m_method == DOUBLE_HASH)
	{
		m_startingHashIndex = num % MAX_SIZE;
		m_incr = 0;
		ret = insertDoubleHash(num, num);
	}
	return ret;
}

bool Hash::insert(int num, int hash)
{
	int index = hash % MAX_SIZE;
	if (m_data[index] == -1)
	{
		m_data[index] = num;
		cout << "inserting " << num << " at index " << index << endl;
	}
	else
	{
		cout << "Collision!!! while inserting " << num << " at index " << index << endl;
		insert(num, index + (1));
	}
	return true;
}

bool Hash::insertQuad(int num, int hash)
{
	int index = hash % MAX_SIZE;
	if (m_data[index] == -1)
	{
		m_data[index] = num;
		cout << "inserting " << num << " at index " << index << endl;
	}
	else
	{
		cout << "Collision!!! while inserting " << num << " at index " << index << " m_incr = " << m_incr << endl;
		if (m_incr == MAX_SIZE)
		{
			cout << "Could not find a position to insert " << num << endl;
			return false;
		}
		m_incr++;
		insertQuad(num, m_startingHashIndex + (m_incr*m_incr));
	}
	return true;
}

bool Hash::insertDoubleHash(int num, int hash)
{
	int index = hash % MAX_SIZE;
	if (m_data[index] == -1)
	{
		m_data[index] = num;
		cout << "inserting " << num << " at index " << index << endl;
	}
	else
	{
		int hash2 = m_lastPrime - (num % m_lastPrime);
		cout << "Collision!!! while inserting " << num << " at index " << index << "  hash2 = " << hash2 << endl;
		if (m_incr == MAX_SIZE)
		{
			cout << "Could not find a position to insert " << num << endl;
			return false;
		}
		m_incr++;
		
		insertDoubleHash(num, m_startingHashIndex + (m_incr*(hash2)));
	}
	return true;
}

bool Hash::find(int num)
{
	if (m_method == LINEAR)
		return findLinear(num, num);
	else
		return false;
}

bool Hash::findLinear(int num, int hash)
{
	bool ret = true;
	int index = hash % MAX_SIZE;
	if (m_data[index] == num)
	{
		cout << "Found " << num << " at index " << index << endl;
		return true;
	}
	else if (m_data[index] == -1)
	{
		cout << "Found " << num << endl;
		return false;
	}
	else
	{
		// Could be because of collision.. search next element...
		findLinear(num, index + (1));
	}
	return ret;
}

void Hash::printHashTable()
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		cout << "data[" << i << "] = " << m_data[i] << endl;
	}
}