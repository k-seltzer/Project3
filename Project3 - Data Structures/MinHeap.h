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
	void heapifyup(double index);
	void heapifydown(double index);
	void pop();
	string top();
};

void MinHeap::insert(string key, int value) {
	minHeap.push_back(pair<string, int>(key, value));
	heapifyup(minHeap.size() - 1);
}

void MinHeap::heapifyup(double index) {
	if (index != 0) {
		if (minHeap[index].second < minHeap[(index - 2) / 2].second) {
			pair<string, int> copy = minHeap[index];
			minHeap[index] = minHeap[(index - 2) / 2];
			minHeap[(index - 2) / 2] = copy;
			heapifyup((index - 2) / 2);
		}
	}
}

void MinHeap::heapifydown(double index) {
	if (index != minHeap.size() - 1) {
		pair <int, int> min(-1, -1);
		if (minHeap[index].second > minHeap[index * 2 + 2].second) {
			min.first = minHeap[index * 2 + 2].second;
			min.second = index * 2 + 2;
		}
		if (minHeap.size() - 1 >= index * 2 + 3 && minHeap[index].second > minHeap[index * 2 + 3].second) {
			if (min.first > -1 && min.first < minHeap[index * 2 + 3].second) {
				min.first = minHeap[index * 2 + 3].second;
				min.second = index * 2 + 3;
			}
		}
		if (min.first > -1) {
			pair <string, int> copy = minHeap[index];
			minHeap[index] = minHeap[min.second];
			minHeap[min.second] = copy;
			heapifydown(min.second);
		}
	}
}
void MinHeap::pop() {
	if (!(minHeap.empty())) {
		minHeap[0] = minHeap.back();
		minHeap.resize(minHeap.size() - 1);
		heapifydown(0);
	}
}

string MinHeap::top() {
	if (!(minHeap.empty())) {
		return minHeap[0].first;
	}
	return "";
}

