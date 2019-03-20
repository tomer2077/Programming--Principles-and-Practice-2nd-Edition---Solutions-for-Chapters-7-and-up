//------------------------------------------------------------------------------

#include "pch.h"
#include "D:\cpp_files\std_lib_facilities.h"

//------------------------------------------------------------------------------

void print_until_s(const vector<string>& v, const string& quit)
{
	cout << "\nStrings in the vector:\n";
	for (string s : v) {
		if (s == quit) return;
		cout << s << '\n';
	}
	cout << "Printed all the items and did not find '" << quit << "'\n\n";
}

//------------------------------------------------------------------------------

void print_until_ss(const vector<string>& v, const string& quit)
{
	cout << "\nStrings in the vector:\n";
	int count{ 0 };
	for (string s : v) {
		if (s == quit) ++count;
		if (count == 2) return;
		cout << s << '\n';
	}
	cout << "Printed all the items. ";
	cout << "Number of times " << quit << "' appeared: " << count << ".\n\n";
}

//------------------------------------------------------------------------------

int main()
try {
	vector<string> x{ "one","two","three","three", "two" };
	print_until_s(x, "two");
	print_until_ss(x, "two");
	keep_window_open();
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
	keep_window_open("~~");
	return 1;
}
catch (...) {
	cerr << "exception\n";
	keep_window_open("~~");
	return 2;
}

//------------------------------------------------------------------------------