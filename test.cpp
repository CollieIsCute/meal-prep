#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
	string s = "123\n123";
	bool f = (find(s.begin(), s.end(), '\n') != s.end());
	cout << f;
}