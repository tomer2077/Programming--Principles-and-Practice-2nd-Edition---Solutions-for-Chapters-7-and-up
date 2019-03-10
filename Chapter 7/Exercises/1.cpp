
/*
	calculator08buggy.cpp

	Helpful comments removed.

	We have inserted 3 bugs that the compiler will catch and 3 that it won't.
*/

//------------------------------------------------------------------------------

#include "pch.h"
#include "D:\cpp_files\std_lib_facilities.h"

//------------------------------------------------------------------------------

class Token {
public:
	char kind;		// the Token's kind
	double value;	// the Token's value
	string name;	// The Token's name
	Token() :kind{ 0 } {}		// default constructor
	Token(char ch) :kind(ch) {}	// initialize kind with ch
	Token(char ch, double val) :kind(ch), value(val) { } // initialize
														 // kind and value
	Token(char ch, string n) :kind{ ch }, name{ n } { }	 // initialize
														 // kind and name
};

//------------------------------------------------------------------------------

// a data stream that parses Tokens from the input from cin
class Token_stream {
public:
	Token_stream(); // make a Token_stream that reads from cin
	Token get();	// get a Token (defined below)
	void putback(Token t);    // put a Token back
	void ignore(char c); // discard all characters until and including c
private:
	bool full{ false };		// is the buffer full?
	Token buffer;	// here is where a Token is kept when one is passed with putback()
};

//void putback(Token t) { buffer = t; full = true; } // place Token back in buffer
//------------------------------------------------------------------------------

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
	:full(false), buffer(0)    // no Token in buffer
{
}

//------------------------------------------------------------------------------


// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
	if (full) error("putback() into a full buffer");
	buffer = t;       // copy t to buffer
	full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

const char let = 'L';		// t.kind==let means t is a variable declaration Token
const char quit = 'Q';		// t.kind==quit means t is a quit Token
const char print = ';';		// t.kind==print means t is a print Token
const char number = '8';	// t.kind==number means t is a number Token
const char name = 'a';		// t.kind==name means t is a varialbe name Token
const char square_root = 'S';
const char power = 'P';
const string declkey = "let";
const string quitkey = "quit";
const string sqrtkey = "sqrt";
const string powkey = "pow";

//------------------------------------------------------------------------------

Token Token_stream::get()
// reads input from cin to parse into a Token
{
	if (full) { full = false; return buffer; } // check if a Token is in buffer
	char ch;
	cin >> ch;	// >> skips whitespace

	switch (ch) {
	case print:
	case ',':
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '=':
	case '!':
		return Token(ch);	// let each character represent itself
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		cin.putback(ch);	// put digit back into the input stream
		double val;
		cin >> val;		// read a floating-point number
		return Token(number, val);	// return a number Token
	}
	default:
		if (isalpha(ch)) {
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch)) || ch == '_') s += ch;
			cin.putback(ch);
			if (s == declkey) return Token(let);
			if (s == quitkey) return Token(quit);
			if (s == sqrtkey) return Token(square_root);
			if (s == powkey) return Token(power);
			return Token(name, s);
		}
		error("Bad token");
	}
}

//------------------------------------------------------------------------------

void Token_stream::ignore(char c)
// c represents the kind of Token
{
	// first look in buffer:
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	// now search input:
	char ch = 0;
	while (cin >> ch)		 // read/"eat" from cin until
		if (ch == c) return; // you've read/"ate" c
}

//------------------------------------------------------------------------------

class Variable {
public:
	string name;
	double value;
	Variable(string n, double v) :name(n), value(v) { }
};

//------------------------------------------------------------------------------

vector<Variable> names;	// where Variables are stored

//------------------------------------------------------------------------------

double get_value(string s)
// finds and returns the value of a Variable
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined name ", s);
}

//------------------------------------------------------------------------------

void set_value(string s, double d)
// finds a Variable and assigns it a value
{
	for (int i = 0; i <= names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined name ", s);
}

//------------------------------------------------------------------------------

bool is_declared(string s)
// checks if a Variable was already declared
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

//------------------------------------------------------------------------------

double factorial(double n)
{
	double fac = 1;

	while (1 < n) {
		fac *= n;
		--n;
		if (fac < 0) error("factorial overflow");
	}

	if (fac == 0) fac = 1;
	return fac;
}

//------------------------------------------------------------------------------

Token_stream ts;	// make a Token_stream
double primary();	// declare primary() so that exp() can see it

//------------------------------------------------------------------------------

double exp()
{
	Token t = ts.get();
	if (t.kind != '(') error("'(' expected for exponent.");

	double x = primary();

	t = ts.get();
	if (t.kind != ',') error("comma expected after 'pow(number'");

	double y = primary();
	int i = narrow_cast<int>(y);

	t = ts.get();
	if (t.kind != ')') error("')' expected after 'pow(number,number");

	return pow(x, i);
}

//------------------------------------------------------------------------------

double expression(); // declare expression() so other functions can see it

//------------------------------------------------------------------------------

// deal with parentheses, numbers, and variables
double primary()
{
	Token t = ts.get();
	
	switch (t.kind) {
	case '(':
	{	
		double d = expression();
		t = ts.get();
		if (t.kind != ')') error("'(' expected");
		return d;
	}
	case '-':
		return -primary();
	case number:
		// we use '8' to represent a number
	{
		Token t2 = ts.get();
		if (t2.kind == '!') {
			t.value = factorial(t.value);
			return t.value;
		}
		else {
			ts.putback(t2);
			return t.value;  // return the number's value
		}
	}
	case square_root:
	{
		double d = primary();
		if (d < 0) error("You can't take the square root of a negative number.");
		return sqrt(d);
		//break;
	}
	case power:
	{
		double d = exp();
		return d;
	}
	case name:
		return get_value(t.name);
	default:
		error("primary expected");
	}
}



//------------------------------------------------------------------------------

// deal with * and /
double term()
{
	double left = primary();
	Token t = ts.get();

	while (true) {
		switch (t.kind) {
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/':
		{
			double d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
			t = ts.get();
			break;
		}
		case '%':
		{
			double d = primary();
			if (d == 0) error("%: divide by zero");
			left = fmod(left, d);
			t = ts.get();
			break;
		}
		default:
			ts.putback(t); // put t back into the token stream
			return left;
		}
	}
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
	double left = term();
	Token t = ts.get();
	
	while (true) {
		switch (t.kind) {
		case '+':
			left += term();
			t = ts.get();
			break;
		case '-':
			left -= term();
			t = ts.get();
			break;
		default:
			ts.putback(t);	// put t back into the token stream
			return left;
		}
	}
}

//------------------------------------------------------------------------------

double define_name(string var, double val)
// add (var, val) to var_table
{
	if (is_declared(var)) error(var, " declared twice");
	names.push_back(Variable{ var, val });
	return val;
}

//------------------------------------------------------------------------------

// assume we have seen "let"
// handle: name = expression
// handles declaring a variable
double declaration()
{
	Token t = ts.get();	// get a Token from the token stream
	if (t.kind != 'a') error("name expected in declaration"); // is it a name
															  // for a variable?
	string name = t.name;
	//if (is_declared(name)) error(name, " declared twice");

	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name); // is it an
																	 // '=' Token?
	double d = expression(); // get the value assigned to the Variable
	define_name(name, d); // append to the vector of Variables
	return d;	// return that Variable's value(to print to the screen)
}

//------------------------------------------------------------------------------

// handles declarations and expressions
double statement()
{
	Token t = ts.get();	// get a Token from token stream
	switch (t.kind) {
	case let:	// case for declaration Token
		return declaration(); // declare the Variable and return its value
	default:
		ts.putback(t);	// put t back into the token stream
		return expression(); // return the result of the expression
	}
}

//------------------------------------------------------------------------------

// discards invalid input
void clean_up_mess()
{
	ts.ignore(print); // discard all input until and including a print Token
}

//------------------------------------------------------------------------------

const string prompt = "> ";
const string result = "= ";

//------------------------------------------------------------------------------

// calculates the result for the user's input
void calculate()
{
	while (cin)
	try {
		cout << prompt;
		Token t = ts.get();	// get a Token from the token stream
		while (t.kind == print) t = ts.get(); // if it's a print Token, "eat" it
		if (t.kind == quit) return;
		ts.putback(t); // put Token back into the token stream
		cout << result << statement() << endl; // output the result
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

//------------------------------------------------------------------------------

int main()

try
{
	// predefine names:
	define_name("pi", 3.1415926535);
	define_name("e", 2.7182818284);
	define_name("k", 1000);
	
		calculate();

	return 0;
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