#include "Table.h"

using namespace std;

int main() {

	//The input given by user will be parsed by the Query Parser.
	//After parsing a pair of string and vector will be returned
	//(as shown below)
	pair<string, vector<pair<string, string>>> query;
	
	query.first = "Table1";
	query.second.push_back(pair<string, string>("int", "ID"));
	query.second.push_back(pair<string, string>("class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >", "Name"));

	Table table(query);

	table.addRow(5, string("Row1"));
	table.addRow(6, string("Row2"));
	table.addRow(1, string("Row3"));

	table.display();

}