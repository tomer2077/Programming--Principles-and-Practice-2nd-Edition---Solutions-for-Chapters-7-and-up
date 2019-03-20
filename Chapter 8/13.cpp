//------------------------------------------------------------------------------

#include "pch.h"
#include "D:\cpp_files\std_lib_facilities.h"

//------------------------------------------------------------------------------

vector<int> nums_of_chars_in_each_string(const vector<string>& v)
{
	// make a vector<int>, append to it the number of each character in v
	vector<int> chars_in_each_string;
	for (string s : v) chars_in_each_string.push_back(s.size());


	double shortest_length = v[0].size();
	for (string s : v) if (s.size() < shortest_length) shortest_length = s.size();

	double longest_length = v[0].size();
	for (string s : v) if (s.size() > longest_length) longest_length = s.size();

	vector<string> shortest_words;
	for (string s : v) if (s.size() == shortest_length) shortest_words.push_back(s);

	vector<string> longest_words;
	for (string s : v) if (s.size() == longest_length) longest_words.push_back(s);

	if (shortest_words.size() == 1) cout << "Shortest: " << shortest_words[0];
	if (shortest_words.size() > 1) {
		cout << "Shortest:\n";
		for (string s : shortest_words) cout << s << endl;
	}
	if (shortest_words.size() < 1) error("vector<string> shortest_words < 1");

	if (longest_words.size() == 1) cout << "\nLongest: " << longest_words[0];
	if (longest_words.size() > 1) {
		cout << "\nLongest:\n";
		for (string s : longest_words) cout << s << endl;
	}
	if (longest_words.size() < 1) error("vector<string> longest_words < 0");

	vector<string> v_copy = v;
	sort(v_copy);
	cout << "\nLexicographically first: " << v_copy[0] << endl;
	cout << "\nLexicographically last: " << v_copy[v_copy.size() - 1] << endl;

	// then return
	return chars_in_each_string;
}

//------------------------------------------------------------------------------

int main()
try {
	vector<string> v{ "kappa","keepo","EleGiggle","SeemsGood","lul","aha","Aha" };
	vector<int> chars_in_each_string_of_v = nums_of_chars_in_each_string(v);

	cout << "\nNumbers of characters:\n";
	for (int i = 0; i < v.size(); ++i) {
		cout << '(' << v[i] << ", " << chars_in_each_string_of_v[i] << ")\n";
		if (i == v.size() - 1) cout << '\n';
	}
	
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