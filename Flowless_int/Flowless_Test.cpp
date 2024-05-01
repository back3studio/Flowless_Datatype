/*
Since Fi_pretest1.0 to ? , you can use this code to test whether the Fi run correctly or not.
Of course, you should put the main code of fi in the same file folder.
*/

#include "Flowless_int.cpp"
using namespace std;

flowless_int<32> a, b, c;
int main() {
	cin >> a >> b;
	c = a + b;
	cout << c.get_val() << endl;
	cout << c << endl;
	c = a - b;
	cout << c.get_val() << endl;
	cout << c << endl;
	c = a * b;
	cout << c.get_val() << endl;
	cout << c << endl;
	c = a / b;
	cout << c.get_val() << endl;
	cout << c << endl;
}
