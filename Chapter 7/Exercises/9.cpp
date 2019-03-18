/*
	Simple calculator


	Revision history:

		Revised by Tomer Faibish March 2019
	Revised by Bjarne Stroustrup November 2013
	Revised by Bjarne Stroustrup May 2007
	Revised by Bjarne Stroustrup August 2006
	Revised by Bjarne Stroustrup August 2004
	Originally written by Bjarne Stroustrup
		(bs@cs.tamu.edu) Spring 2004.


		This program implements a basic expression calculator.
	Input from cin; output to cout.


	The grammar for input is:

	Calculation:
		Statement print
		Print
		Help print
		Quit print

	Statement:
		Declaration 
		Expression

	Declaration:
		"let" Name "=" Expression
		"const" Name "=" Expression
	
	Name:
		string starting with a letter, made of letters and/or digits and/or underscores

	Print:
		';'
		'\n'

	Help:
		help

	Quit:
		quit

	Expression:
		Term
		Expression '+' Term
		Expression '–' Term

	Term:
		Primary
		Term '*' Primary
		Term '/' Primary
		Term '%' Primary

	Primary:
		Number
		'–' Primary
		'+' Primary
		'(' Expression ')'
		Number '!'
		"sqrt" '(' Expression ')'
		"pow" '(' Number ',' Integer ')'
		Name '=' Expression
		Name

	Number:
		floating-point-literal
 
	Input comes from cin through the Token_stream called ts.
*/

//------------------------------------------------------------------------------

#include "pch.h"
#include "D:\cpp_files\std_lib_facilities.h"

//------------------------------------------------------------------------------

void print_instructions()
{
	cout << "\nInstructions:\n\n" <<

	"Supported numbers: floating-point numbers (integers and decimal numbers)."
	<< "\n\n" <<

	"Supported operators: +, -, *, /, %.\n\n" <<

	"Supported functions:\n" <<

	"1. Exponents. To use this function, type pow(x,i) with x being the" <<
	"number you want to raise to a power and i being the power you want to" <<
	" raise x to.\n" <<

	"2. Square roots. To use this function, type sqrt(x) with x being" <<
	"the number you want to take the square root of. Taking the square " <<
	"root of a negative number isn't supported.\n" <<

	"3. Squaring a number. To use this function, type sq(x) with x being" <<
	" the number you want to square.\n\n" <<

	"How to declare a variable:\n" <<
	"Type 'let' followed by the name of the variable, then a '=', and" <<
	"then the value you want to assign to it.\nExample: 'let x = 5'\n\n" <<

	"How to assign a new value to a variable:\nType the name of the" <<
	" variable followed by '=' and then the new value you want to assign" <<
	"to it.\nExample: 'x = 4'\n\n" <<

	"How to declare a constant:\n" <<
	"Type 'const' followed by the name of the constant, then a '=', " <<
	"then the value you want to assign to it.\nExample: 'const pi = 3.14'\n\n";
	return;
}

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
	bool check_buffer();
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

bool Token_stream::check_buffer()
{
	return full;
}

//------------------------------------------------------------------------------

const char let = 'L';		     // t.kind==let means t is a variable declaration Token
const char quit = 'Q';		     // t.kind==quit means t is a quit Token
const char print = ';';		     // t.kind==print means t is a print Token
const char number = '8';	     // t.kind==number means t is a number Token
const char name = 'a';		     // t.kind==name means t is a varialbe name Token
const char square_root = 'R';    // t.kind==square_root means t is a square root Token
const char square = 'S';
const char power = 'P';		     // t.kind==power means t is a power Token
const char constant = 'C';	     // t.kind==constant means t is a constant Token
const char newline = '\n';	     // t.kind==newline means t is a newline Token
const char help = 'h';		     // t.kind==help means t is a help Token
const string declkey = "let";    // Variable declaration keyword
const string quitkey = "quit";   // keyword for quit
const string sqrtkey = "sqrt";   // keyword for the square root function
const string powkey = "pow";     // keyword for the exponent function
const string squarekey = "sq";     // keyword for the square function
const string constkey = "const"; // constant Variable declaration keyword
const string helpkey = "help";   // keyword for help
const string prompt = "> ";	     // t.kind== means t is a Token
const string result = "= ";	     // t.kind== means t is a Token
Token_stream ts;	// make a Token_stream to parse input from cin


//------------------------------------------------------------------------------

Token detect_keyword(string s)
{
	if (s == constkey) return Token(constant);
	if (s == declkey) return Token(let);
	if (s == quitkey) return Token(quit);
	if (s == sqrtkey) return Token(square_root);
	if (s == powkey) return Token(power);
	if (s == helpkey) return Token(help);
	return Token(name, s);
}

//------------------------------------------------------------------------------

Token Token_stream::get()
// reads input from cin to parse into a Token
{
	if (full) { full = false; return buffer; } // check if a Token is in buffer
	char ch;
	cin.get(ch);	// >> skips whitespace

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
		if (isspace(ch)) {
			if (ch == newline) return Token(newline);
			else return ts.get();
		}
		if (isalpha(ch)) {
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch)) || ch == '_') s += ch;
			cin.putback(ch);
			if (s == constkey) return Token(constant);
			if (s == declkey) return Token(let);
			if (s == quitkey) return Token(quit);
			if (s == sqrtkey) return Token(square_root);
			if (s == powkey) return Token(power);
			if (s == squarekey) return Token(square);
			if (s == helpkey) return Token(help);
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
	while (cin.get(ch))		 // read/"eat" from cin until
		if (ch == print || ch == newline) return; // you've read/"ate" c
}

//------------------------------------------------------------------------------

class Variable {
public:
	string name;
	double value;
	bool constant;
	Variable(string n, double v, bool b) :name(n), value(v), constant(b) { }
	//Variable(string n, double v)
	//	:name(n), value(v), constant(false) { } // make a Variable
};

//------------------------------------------------------------------------------

class Symbol_table {
public:
	Symbol_table();
	double get(string s);
	void set(string s, double d);
	bool is_declared(string s);
	double declare(string var, double val, bool b);
private:
	vector<Variable> var_table; // where Variables are stored
};

//------------------------------------------------------------------------------

Symbol_table::Symbol_table()
	:var_table()
{}

//------------------------------------------------------------------------------

// finds and returns the value of a Variable
double Symbol_table::get(string s)
{
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s) return var_table[i].value;
	error("get: undefined name ", s);
}

//------------------------------------------------------------------------------

void Symbol_table::set(string s, double d)
// finds a Variable and assigns it a value
{
	for (int i = 0; i <= var_table.size(); ++i)
		if (var_table[i].name == s) {
			if (var_table[i].constant) error("Can't change a constant's value.");
			var_table[i].value = d;
			return;
		}
	error("set: undefined name ", s);
}

//------------------------------------------------------------------------------

bool Symbol_table::is_declared(string s)
// checks if a Variable was already declared
{
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s) return true;
	return false;
}

//------------------------------------------------------------------------------

double Symbol_table::declare(string var, double val, bool b)
// add (var, val) to var_table
{
	if (is_declared(var)) error(var, " already declared");
	var_table.push_back(Variable{ var, val, b });
	return val;
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
	if (t.kind != ')') error("number expected after 'pow(number,number");

	return pow(x, i);
}

double second_pow()
{
	Token t = ts.get();
	if (t.kind != '(') error("'(' expected for exponent.");

	double x = primary();

	t = ts.get();
	if (t.kind != ')') error("number expected after 'pow(number,number");

	return pow(x, 2);
}

//------------------------------------------------------------------------------

double expression(); // declare expression() so other functions can see it
Symbol_table symtable;

//------------------------------------------------------------------------------

// deal with parentheses, numbers, and variables
double primary()
{
	Token t = ts.get();

	switch (t.kind) {
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
	case '(':
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') error("'(' expected");
		return d;
	}
	case '-':
		return -primary();
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
	case square:
	{
		double d = second_pow();
		return d;
	}
	case name:
	{
		Token t2 = ts.get();
		if (symtable.is_declared(t.name) && t2.kind == '=') {
			double d = primary();
			symtable.set(t.name, d);
		}
		else ts.putback(t2);
		return symtable.get(t.name);
	}
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

//double define_name(string var, double val)
//// add (var, val) to var_table
//{
//	if (is_declared(var)) error(var, " already declared");
//	var_table.push_back(Variable{ var, val });
//	return val;
//}

//double define_name(string var, double val, bool b)
//// add (var, val) to var_table
//{
//	if (is_declared(var)) error(var, " already declared");
//	var_table.push_back(Variable{ var, val, b });
//	return val;
//}

//------------------------------------------------------------------------------

// assume we have seen "let"
// handle: name = expression
// handles declaring a variable
double declaration(bool constant)
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
	symtable.declare(name, d, constant); // append to the vector of Variables
	return d;	// return that Variable's value(to print to the screen)
}

//------------------------------------------------------------------------------

// handles declarations and expressions
double statement()
{
	Token t = ts.get();	// get a Token from token stream
	switch (t.kind) {
	case let:	// case for declaration Token
		return declaration(false); // declare Variable that's not a constant
	case constant:
		return declaration(true); // declare Variable that's a constant
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

// calculates the result for the user's input
void calculate()
{
	bool first_iteration = true;
		
	while (cin)
	try {
		if (first_iteration) {
			cout << prompt; first_iteration = false;
		}
		
		Token t = ts.get();	// get a Token from the token stream
		while (t.kind == print || t.kind == newline) t = ts.get(); // if it's a print Token, "eat" it
		if (t.kind == help) { print_instructions(); first_iteration = true; continue; }
		if (t.kind == quit) return;
		ts.putback(t); // put Token back into the token stream
		cout << result << statement() << endl; // output the result
		t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == newline) cout << prompt;
		else ts.putback(t);
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
		first_iteration=true;
	}
}

//------------------------------------------------------------------------------

int main()

try
{
	// predefine var_table:
	//define_name("pi", 3.1415926535, true);
	//define_name("e", 2.7182818284);
	//define_name("k", 1000);

	cout << "Simple calculator\nEnter 'help' for instructions\n\n";

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