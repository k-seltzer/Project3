#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include "MinHeap.h"
#include "HashMap.h"
using namespace std;

vector <string> heapSort(HashMap dataset) {
	MinHeap minHeap;
	for (auto i = dataset.begin(); i != dataset.end(); ++i) {
		for (auto j = (*i).begin(); j != (*i).end(); ++j) {
			int total = 0;
			for (auto k = ((*j).first).begin(); k != ((*j).first).end(); ++k) {
				total += *k;
			}
			minHeap.insert((*j).first, total);
		}
	}
	vector <string> keys;
	while (minHeap.top() != "") {
		keys.push_back(minHeap.top());
		minHeap.pop();
	}
	return keys;
}

int main() {
	ifstream dataset("airlines.csv", ifstream::in);
	string line, token;
	queue <string> lines;
	if (dataset.is_open()) {
		getline(dataset, line);
		while (getline(dataset, line)) {
			istringstream stream(line);
			for (int i = 0; i < 23; i++) {
				getline(stream, token, ',');
				lines.push(token);
			}
		}
	}
	while (!lines.empty()) {
		cout << lines.front() << endl;
		lines.pop();
	}
	return 0;
}