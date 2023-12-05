#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include "HashMap.h"
#pragma once
using namespace std;
class MinHeap {
	vector <pair <string, int>> minHeap;
public:
	void insert(string key, int value);
	void heapifyup(int index);
	void heapifydown(int index);
	void pop();
	pair<string, int> front();
	bool empty();
};

