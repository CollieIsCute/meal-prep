#include <iostream>

using namespace std;

class C {
public:
	int c;
};

int main(void) {
	C a;
	a.c = 28;
	C b(a);
	a.c = 15;
	cout << b.c << endl;
	return 0;
}