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

	table.addColumn(pair<string, string>("bool", "Employed"));
	table.addColumn(pair<string, string>("class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >", "Salary"));
	
	table.display();
	
	cout << endl;

	for (int i = 0; i < table.num_of_rows; i++) {
		for (int j = 0; j < table.num_of_cols; j++) {
			cout << table[j][i].getValue() << "\t";
		}
		cout << endl;
	}
	cout << endl;

	Base_Node* temp = table.col_head->getHead()->getDown();
	while (temp != NULL) {
		cout << temp->getValue() << "\t";
		temp = temp->right;
	}
	cout << endl;

	table["ID"][3].setValue(6);
	cout << table["Name"][3].getValue();

}
