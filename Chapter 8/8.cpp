//------------------------------------------------------------------------------

#include "pch.h"
#include "D:\cpp_files\std_lib_facilities.h"

//------------------------------------------------------------------------------

vector<string> names;
vector<double> ages;

//------------------------------------------------------------------------------

void get_input()
{
	string n;
	double a;

	cout << "Type a few sequences of a name and an age (separated by a space) ";
	cout << "and then press enter" << "\n\n";
	cout << "> ";

	while (cin >> n >> a) {
		names.push_back(n);
		ages.push_back(a);
		if (cin.peek() == '\n') break;
	}
	if (!cin) error("Didn't enter sequences of names and ages.");
}

//------------------------------------------------------------------------------

void print_pairs(string label)
{
	cout << '\n' << label << ":\n";
	for (int i = 0; i < names.size(); ++i)
		cout << '(' << names[i] << ", " << ages[i] << ")\n";
}

//------------------------------------------------------------------------------

int find_index(const vector<string>& v, string s)
{
	for (int i = 0; i < v.size(); ++i)
		if (v[i] == s) return i;
	error("Index not found");
}

//------------------------------------------------------------------------------

int main()
try {
	get_input();
	print_pairs("As read");

	vector<string> original_names = names;
	vector<double> original_ages = ages;

	sort(names.begin(), names.end());

	for (int i = 0; i < names.size(); ++i)
		ages[i] = original_ages[find_index(original_names, names[i])];

	print_pairs("Ordered");

	keep_window_open("~");
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