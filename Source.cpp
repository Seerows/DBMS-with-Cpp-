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

	size_t initial_pos = 0;
	auto pos = query.second.at(0).second.find('_');
	string sub = query.second.at(0).second.substr(initial_pos, pos);

	string label = "Table1";

	Table table(query);
	
	table.addRow(5, string("Row1"));
	table.addRow(6, string("Row2"));
	table.addRow(1, string("Row3"));

	table.display();


}