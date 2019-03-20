/*

	What might that mean: passing a const copy of a const/non const variable

	Why might we want to do that: perhaps because a different part of a program
	depends on the original variable staying the same, and perhaps the copy
	doesn't cost more memory than one int, and/or perhaps another part of the
	program would be accessing the variable through a reference while this one
	executes, and maybe if f(const int) didn't have (const int) as a parameter,
	we would get undefined behavior.

	Why don't people do that often: perhaps because it is not often useful/necessary.

*/

//------------------------------------------------------------------------------

#include "pch.h"
#include "D:\cpp_files\std_lib_facilities.h"

//------------------------------------------------------------------------------

void f(const int x)
{
	cout << "f(): x == " << x << endl;
}

//------------------------------------------------------------------------------

int main()
try {
	int y = 5;
	f(y);
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