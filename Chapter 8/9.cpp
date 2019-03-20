#include "pch.h"
#include "D:\cpp_files\std_lib_facilities.h"

double compute_value(const vector<double>& x, const vector<double>& y)
// pre-condition: containers of the same size, with only positive values
// post-condition: no truncation
{
	if (x.size() != y.size()) error("Data structures with different number of items");
	
	for (int i = 0; i < x.size(); ++i)
		if (x[i] <= 0 || y[i] <= 0)
			error("Not all the values are above zero");

	double sum{ 0 };

	for (int i = 0; i < x.size(); ++i)
		sum += x[i] * y[i];

	if (sum <= 0) error("compute_value(): post-condtion");
	return sum;
}

int main()
try
{
	vector<double> price{ 10, 30, 15, 20 };
	vector<double> weight{ 5,10,35,20 };

	cout << "The sum of price and weight is: " << compute_value(price, weight) << endl;

	keep_window_open();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << '\n';
	keep_window_open("~~");
}
catch (...) {
	cerr << "Unknown error\n";
	keep_window_open("~~");
}