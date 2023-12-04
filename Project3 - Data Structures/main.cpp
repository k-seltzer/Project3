#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <chrono>
#include <random>
#include "MinHeap.h"
#include "HashMap.h"
using namespace std;

queue <pair<string, int>> heapSort(HashMap dataset) {
	MinHeap minHeap;
	for (auto i = dataset.begin(); i != dataset.end(); ++i) {
		for (auto j = (*i).begin(); j != (*i).end(); ++j) {
			int total = 0;
			for (auto k = ((*j).second.begin()); k != ((*j).second.end()); ++k) {
				total += *k;
			}
			minHeap.insert((*j).first, total);
		}
	}
	queue <pair<string, int>> keys;
	while (!(minHeap.empty())) {
		keys.push(minHeap.front());
		minHeap.pop();
	}
	return keys;
}

int main() {
	ifstream dataset("airlines.csv", ifstream::in);
	string line, token;
	pair<vector<int>, vector<int>> stats({ 0,0,0,0,0 }, { 0,0,0,0,0 });
	HashMap data(10);
	if (dataset.is_open()) {
		getline(dataset, line);
		while (getline(dataset, line)) {
			istringstream stream(line);
			queue <string> Data1;
			for (int i = 0; i < 23; i++) {
				if (i < 11) {
					getline(stream, token, ',');
					token = token.substr(1, token.length() - 2);
					Data1.push(token);
				}
			}
			for (int i = 0; i < 6; i++)
				Data1.pop();
			for (int i = 0; i < 5; i++) {
				if (stoi(Data1.front()) < stats.first[i]) {
					stats.first[i] = stoi(Data1.front());
				}
				else if (stoi(Data1.front()) > stats.second[i]) {
					stats.second[i] = stoi(Data1.front());
				}
				Data1.pop();
			}
		}
		//unsigned seed = chrono::system_clock::now().time_since_epoch().count();
		unsigned seed = 55444837;
		mt19937 generator(seed);
		for (int i = 0; i < 125000; i++) {
			vector<int> element(5);
			for (int j = 0; j < 5; j++) {
				uniform_int_distribution<int> distribution(stats.first[j], stats.second[j]);
				element[j] = distribution(generator);
			}
			uniform_int_distribution<int> distribution(65, 90);
			string key;
			for (int j = 0; j < 4; j++) {
				key += static_cast<char>(distribution(generator));
			}
			data.insert(key, element);
		}
	}
	/*for (auto i = data.begin(); i != data.end(); ++i) {
		for (auto j = (*i).begin(); j != (*i).end(); ++j) {
			cout << (*j).first << ' ';
			int total = 0;
			for (auto k = ((*j).second.begin()); k != ((*j).second.end()); ++k) {
				total += *k;
			}
			cout << total << endl;
		}
	}*/
	queue <pair<string, int>> min = heapSort(data);
	while (!(min.empty())) {
		cout << min.front().first << ' ' << min.front().second << endl;
		min.pop();
	}
	return 0;
}