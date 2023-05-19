#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int width;
	int height;
	cin >> width >> height; cin.ignore();

	vector<string> grid;

	for (int i = 0; i < height; i++) {
		string	line;
		cin >> line; cin.ignore();
		cerr << line << endl;
		grid.push_back(line);
	}

	for (vector<string>::iterator it = grid.begin(); it != grid.end(); ++it) {
		for (string::iterator it2 = it->begin(); it2 != it->end(); ++it2) {
			if (*it2 == '0') {
				int	count = 0;
				if (it2 != it->begin() && *(it2 - 1) == '0') {
					count++;
				}
				if (it2 != it->end() - 1 && *(it2 + 1) == '0') {
					count++;
				}
				if (it != grid.begin() && (*(it - 1))[it2 - it->begin()] == '0') {
					count++;
				}
				if (it != grid.end() - 1 && (*(it + 1))[it2 - it->begin()] == '0') {
					count++;
				}
				cout << count;
			} else {
				cout << *it2;
			}
		}
		cout << endl;
	}

	return (0);
}
