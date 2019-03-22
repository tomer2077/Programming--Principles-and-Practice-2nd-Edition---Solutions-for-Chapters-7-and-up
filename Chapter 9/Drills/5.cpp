#include "pch.h"
#include "D:\cpp_files\std_lib_facilities.h"

enum class Month {
	jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

class Date {
public:
	Date();									// default constructor
	Date(int y, Month m, int d);		// check for valid date and initialize
	Date(int y);						// January 1 of year y

	int day() const { return d; }			// what day is it?
	Month month() const { return m; }		// what month is it?
	int year() const { return y; }			// what year is it?

	void add_day(int n);					// increase the Date by n days
	
	class Invalid {};						// an exception for an invalid date
private:
	int y;		// year
	Month m;
	int d;		// day
	bool is_valid(); // return true if date is valid
};

const Date& default_date()
{
	static Date dd { 2001,Month::jan,1 };
	return dd;
}
Date::Date()
	:y{ default_date().year() },
	 m{ default_date().month() },
	 d{ default_date().day() }
{
}

Date::Date(int yy)						// January 1 of year yy
	:y{ yy }
{
	if (!is_valid()) throw Invalid{};
}


// prefix increment operator
Month operator++(Month& m)
{
	m = (m == Month::dec) ? Month::jan : Month(int(m) + 1);	// “wrap around"
	return m;
}

Month int_to_month(int x)
{
	if (x < int(Month::jan) || x > int(Month::dec)) error("bad month");
	return Month(x);
}

int get_days_in_month(Month);

bool Date::is_valid()
{
	if (int(m) < 1 || int(m) > 12) return false;	// check month is between 1-12
	if (d < 1 || d > get_days_in_month(m)) return false;
	return true;
}


Date::Date(int yy, Month mm, int dd)
	:y{ yy }, m{ mm }, d{ dd }
{
	if (!is_valid()) throw Invalid{};
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
			if (m == Month::dec) ++y;
			++m; d = 1; --n;
		}
		else { ++d; --n; }					// if it's not the last day of the
	}										// month, just increment the day
}

ostream& operator<<(ostream& os, const Date& d)
// this ver doesn't define Date::year, month, day as const, so I chose
// to copy-by-value, because that ensures that there can't be "someone"
// ever modifying the original Date by obliviously changing this body's code
{
	return os << '(' << d.year()
		<< ',' << int(d.month())
		<< ',' << d.day() << ')';
}



int get_days_in_month(Month m)
{
	switch (m) {
	case Month::feb:
		return 28;
	case Month::apr: case Month::jun: case Month::sep: case Month::nov:
		return 30;
	default:
		return 31; // the rest of the months have 31 days
	}
}


int main()
try {

	try {
		Date today{ 1978, Month::jun, 25 };

		Date tomorrow{ today };

		tomorrow.add_day(249); // 79/3/1
		
		cout << today << endl << tomorrow << endl;
	}
	catch (Date::Invalid) {
		error("Invalid date");
	}

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