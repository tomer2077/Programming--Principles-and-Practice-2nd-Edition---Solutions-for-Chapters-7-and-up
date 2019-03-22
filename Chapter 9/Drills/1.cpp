/*

	This drill simply involves getting the sequence of versions of Date to work.
	For each version define a Date called today initialized to June 25, 1978.
	Then, define a Date called tomorrow and give it a value by copying today
	into it and increasing its day by one using add_day(). Finally, output
	today and tomorrow using a << defined as in §9.8.

	Your check for a valid date may be very simple. Feel free to ignore
	leap years. However, don’t accept a month that is not in the [1,12]
	range or day of the month that is not in the [1,31] range. Test each
	version with at least one invalid date (e.g., 2004, 13, –5).

*/

#include "pch.h"
#include "D:\cpp_files\std_lib_facilities.h"

struct Date {
	int y;		// year
	int m;		// month in year
	int d;		// day of month
};

ostream& operator<<(ostream& os, const Date& d)
{
	return os << '(' << d.y
			  << ',' << d.m
			  << ',' << d.d << ')';
}

int get_days_in_month(int m)
{
	switch (m) {
	case 2:
		return 28;
	case 4: case 6: case 9: case 11:
		return 30;
	default:
		return 31;
	}
}

bool last_date_of_month(int d, int days_in_month)
{
	return (d == days_in_month) ? true : false;
}

void add_day(Date& dd, int n)
{
	if (n < 0) error("You can't add negative days to a date");
	int days_in_month;

	while (n > 0) {
		days_in_month = get_days_in_month(dd.m);

		if (last_date_of_month(dd.d, days_in_month))
		{
			if (dd.m == 12) {
				dd.m = 1; dd.d = 1; ++dd.y; --n;
			}
			else {
				dd.d = 1; ++dd.m; --n;
			}
		}
		else { ++dd.d; --n; }
	}
}

bool is_date(int y, int m, int d)
{
	if (y < 1) return false;
	if (m < 1 || m > 12) return false;
	if (d < 1 || d > get_days_in_month(m)) return false;
	return true;
}

void init_day(Date& dd, int y, int m, int d)
// check that (y,m,d) is a valid date
// if it is, use it to initialize dd
{
	if (is_date(y, m, d)) {
		dd.y = y;
		dd.m = m;
		dd.d = d;
	}
	else error("Invalid date");
}

int main()
try {
	Date today;
	init_day(today, 1978, 6, 25);
	Date tomorrow{ today };
	add_day(tomorrow, 249); // 79/3/1


	cout << today << endl << tomorrow << endl;
	keep_window_open();
}
catch (exception& e) {
	cerr << "error: " << e.what() << '\n';
	keep_window_open("~");
}
catch (...) {
	cerr << "Unknown error\n";
	keep_window_open("~");
}