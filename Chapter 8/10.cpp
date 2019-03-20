#include "pch.h"
#include "D:\cpp_files\std_lib_facilities.h"

double largest_value(const vector<double>& v)
{
	double largest = 0;
	for (double d : v) if (d > largest) largest = d;
	return largest;
}

int main()
{
	vector<double> my_vector{ 1,2,55,44,404,3 };
	cout << largest_value(my_vector) << endl;
	keep_window_open();
}