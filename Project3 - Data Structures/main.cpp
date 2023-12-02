#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
using namespace std;

int main() {
	ifstream dataset("airlines.csv", ifstream::in);
	string line, token;
	queue <string> lines;
	if (dataset.is_open()) {
		while (getline(dataset, line)) {
			lines.push(line);
		}
	}
	while (!lines.empty()) {
		cout << lines.front() << endl;
		lines.pop();
	}
	return 0;
}