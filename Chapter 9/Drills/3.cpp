#include "pch.h"
#include "D:\cpp_files\std_lib_facilities.h"

class Date {
	int y, m, d;                                          // year, month, day
public:
	Date(int y, int m, int d);                   // check for valid date and initialize
	void add_day(int n);                        // increase the Date by n days
	int month() { return m; }
	int day() { return d; }
	int year() { return y; }
};

bool is_date(int, int, int);
int get_days_in_month(int);

Date::Date(int yy, int mm, int dd)
	:y{ yy }, m{ mm }, d{ dd }
{
	if (!is_date(yy, mm, dd)) error("Invalid date");
}

void Date::add_day(int n)
// adds a non-negative amount of days to the Date
{
	if (n < 0) error("You can't add negative days to a date");

	int days_in_month;
	while (n > 0) {
		days_in_month = get_days_in_month(m);

		if (d == days_in_month)				// is the next date a new month?
		{
			if (m == 12)
			{
				m = 1; d = 1; ++y; --n;		// if it's the last day of dec
			}								// "wrap around" to next year
			else
			{
				d = 1; ++m; --n;			// otherwise, change to the 1st
			}								// of next month
		}
		else { ++d; --n; }					// if it's not the last day of the
	}										// month, just increment the day
}

ostream& operator<<(ostream& os, Date d)
// this ver doesn't define Date::year, month, day as const, so I chose
// to copy-by-value, because that ensures that there can't be "someone"
// ever modifying the original Date by obliviously changing this body's code
{
	return os << '(' << d.year()
		<< ',' << d.month()
		<< ',' << d.day() << ')';
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

bool is_date(int y, int m, int d)
{
	if (y < 1) return false;
	if (m < 1 || m > 12) return false;
	if (d < 1 || d > get_days_in_month(m)) return false;
	return true;
}

int main()
try {
	Date today(1978, 6, 25);
	Date tomorrow{ today };
	tomorrow.add_day(249); // 79/3/1

	cout << today << endl << tomorrow << endl << "Kappa" << endl;

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