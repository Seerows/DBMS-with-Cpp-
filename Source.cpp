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
	query.second.push_back(pair<string, string>("char", "Grade"));

	Table table(query);

	table.addRow(5, string("Row1"), 'A');
	table.addRow(6, string("Row2"), 'C');
	table.addRow(1, string("Row3"), 'D');
	table.addRow(4, string("Row4"), 'E');
	table.addRow(7, string("Row5"), 'F');

	
	table.display();

	Base_Node* temp = table.col_head->getHead()->getDown();
	while (temp != NULL) {
		cout << temp->getValue() << "\t";
		temp = temp->right;
	}
	cout << endl;

	table["ID"][3].setValue(6);
	cout << table["Name"][3].getValue();

}

//use union that has all 5 datatypes along with an extra string variable that contains the data type.
//Then implement a getData() function to retrieve the data.
//U can also implement a LinkedList for this union to be used for rows.