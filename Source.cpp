#include "Table.h"
#include "Database.h"

using namespace std;

int main() {

	//The input given by user will be parsed by the Query Parser.
	//After parsing a pair of string and vector will be returned
	//(as shown below)

	pair<string, vector<pair<string, string>>> query;
	
	query.first = "Employees";
	query.second.push_back(pair<string, string>("int", "ID"));
	query.second.push_back(pair<string, string>("class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >", "Name"));
	query.second.push_back(pair<string, string>("char", "Grade"));
	query.second.push_back(pair<string, string>("int", "Dept_ID"));

	Table employees(query);

	employees.addRow(5, string("Row1"), 'A', 2);
	employees.addRow(6, string("Row2"), 'C', 1);
	employees.addRow(1, string("Row3"), 'D', 4);
	employees.addRow(4, string("Row4"), 'E', 3);
	employees.addRow(7, string("Row5"), 'F', 1);

	employees.addColumn(pair<string, string>("bool", "Employed"));
	employees.addColumn(pair<string, string>("class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >", "Salary"));

	employees.addRow(9, string("Row6"), 'F', 2, true, string("900.2"));
	
	employees.display();
	cout << endl;

	pair<string, vector<pair<string, string>>> query2;
	
	query2.first = "Departments";
	query2.second.push_back(pair<string, string>("int", "ID"));
	query2.second.push_back(pair<string, string>("class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >", "Name"));
	query2.second.push_back(pair<string, string>("float", "Pay"));

	Table departments(query2);

	departments.addRow(1, string("CS"), 57.5f);
	departments.addRow(2, string("EE"), 39.4f);
	departments.addRow(3, string("AI"), 47.2f);
	departments.addRow(4, string("CYS"), 98.3f);

	departments.display();

	cout << "Joining Employees and Departments..." << endl;
	Table* table = employees.join(&employees["Dept_ID"], &departments["ID"]);
	table->display();

	//make a Primary_Column class that handles creation of Primary Key (as well as autoincrement?) and makes sure all keys are unique
	//make a Foreign_Column class that checkes if all keys exist in the reference column
	//add error handling in the addRow function. Also add backtracking.




	/*Base_Node* temp = employees.col_head->getHead()->getDown();
	while (temp != NULL) {
		cout << temp->getValue() << "\t";
		temp = temp->right;
	}
	cout << endl;*/

	//employees["ID"][3].setValue(6);
	//cout << employees["Name"][3].getValue();

	//for (int i = 0; i < employees.num_of_rows; i++) {
	//	for (int j = 0; j < employees.num_of_cols; j++) {
	//		cout << employees[j][i].getValue() << "\t";
	//	}
	//	cout << endl;
	//}
	//cout << endl;

}
