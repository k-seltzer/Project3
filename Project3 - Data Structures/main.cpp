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