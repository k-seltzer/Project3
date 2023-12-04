#include "MinHeap.h"
void MinHeap::insert(string key, int value) {
	minHeap.push_back(pair<string, int>(key, value));
	heapifyup(minHeap.size() - 1);
}

void MinHeap::heapifyup(int index) {
	if (index != 0) {
		if (minHeap[index].second < minHeap[(index - 1) / 2].second) {
			pair<string, int> copy = minHeap[index];
			minHeap[index] = minHeap[(index - 1) / 2];
			minHeap[(index - 1) / 2] = copy;
			heapifyup((index - 1) / 2);
		}
	}
}

void MinHeap::heapifydown(int index) {
	if (index != minHeap.size() - 1) {
		pair <int, int> min(-1, -1);
		if (minHeap.size() > index * 2 + 1) {
			if (minHeap[index].second > minHeap[index * 2 + 1].second) {
				min.first = minHeap[index * 2 + 1].second;
				min.second = index * 2 + 1;
			}
		}
		if (minHeap.size() > index * 2 + 2) {
			if (minHeap[index].second > minHeap[index * 2 + 2].second) {
				if (min.first > -1 && min.first > minHeap[index * 2 + 2].second) {
					min.first = minHeap[index * 2 + 2].second;
					min.second = index * 2 + 2;
				}
				else if (min.first == -1) {
					min.first = minHeap[index * 2 + 2].second;
					min.second = index * 2 + 2;
				}
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

pair<string, int> MinHeap::front() {
	return minHeap[0];
}

bool MinHeap::empty() {
	return minHeap.empty();
}