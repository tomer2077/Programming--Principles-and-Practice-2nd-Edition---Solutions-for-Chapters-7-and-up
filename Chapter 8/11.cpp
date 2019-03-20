//------------------------------------------------------------------------------

#include "pch.h"
#include "D:\cpp_files\std_lib_facilities.h"

//------------------------------------------------------------------------------

struct details {
	double smallest;
	double largest;
	double mean;
	double median;
};

//------------------------------------------------------------------------------

details get_details(const vector<double>& v)
{
	// find largest
	double largest = numeric_limits<double>::min(); // smallest possible
	for (double d : v) if (d > largest) largest = d;

	// find smallest
	double smallest = numeric_limits<double>::max(); // largest possible
	for (double d : v) if (d < smallest) smallest = d;

	// calculate mean
	double mean;
	double sum = 0;
	for (double d : v)sum += d;
	mean = { sum / v.size() };

	// is the count of the set even? need to know that to calculate median
	bool even_count;
	if (fmod(v.size(), 2.0) == 0.0) even_count = true;
	else even_count = false;

	// calculate median
	double median;
	if (even_count) median = (v[v.size() / 2.0] + v[v.size() / 2.0 + 1]) / 2.0;
	else median = v[v.size() / 2.0 - 0.5];

	details results{ smallest,largest,mean,median };
	return results;
}

//------------------------------------------------------------------------------

int main()
try {
	vector<double> my_vec {1, 505, 40, 34, 44};
	details my_vec_details = get_details(my_vec);

	cout << "Smallest: " << my_vec_details.smallest << endl
		<< "Largest: " << my_vec_details.largest << endl
		<< "Mean: " << my_vec_details.mean << endl
		<< "Median: " << my_vec_details.median << endl;

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