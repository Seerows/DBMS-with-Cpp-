#include "Table.h"

Table::Table(pair<string, vector<pair<string, string>>> query) {
	metadata = query;
	counter = num_of_cols = num_of_rows = 0;

	Base_Column* curr;

	for (int i = 0; i < query.second.size(); i++) {
		string type = query.second.at(i).first;
		curr = col_head;
		num_of_cols++;

		if (i == 0) {

			if (type == "float") {
				col_head = new Column<float>(query.second.at(i).second);
			}
			else if (type == "string") {
				col_head = new Column<string>(query.second.at(i).second);
			}
			else if (type == "char") {
				col_head = new Column<char>(query.second.at(i).second);
			}
			else if (type == "bool") {
				col_head = new Column<bool>(query.second.at(i).second);
			}
			else {			//for int case. Removing this gives an error.
				col_head = new Column<int>(query.second.at(i).second);
			}

		}
		else{
			
			if (i == 1) {
				curr = col_head;
			}
			else if (i > 1) {
				curr = curr->next_col;
			}

			if (type == "float") {
				curr->next_col = new Column<float>(query.second.at(i).second);
			}
			else if (type == "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >") {
				curr->next_col = new Column<string>(query.second.at(i).second);
			}
			else if (type == "char") {
				curr->next_col = new Column<char>(query.second.at(i).second);
			}
			else if (type == "bool") {
				curr->next_col = new Column<bool>(query.second.at(i).second);
			}
			else {			//for int case. Removing this gives an error.
				curr->next_col = new Column<int>(query.second.at(i).second);
			}

		}

	}

	current = col_head;
}

void Table::display() {

	for (int i = 0; i < num_of_rows; i++) {
		Base_Column* curr_col = col_head;

		while (curr_col != NULL) {

			cout << (*curr_col)[i].getValue();

			/*if (Column<int>* col = dynamic_cast<Column<int>*>(curr_col)) {
				cout << (*col)[i].getValue();
			}
			else if (Column<float>* col = dynamic_cast<Column<float>*>(curr_col)) {
				cout << (*col)[i].getValue();
			}
			else if (Column<char>* col = dynamic_cast<Column<char>*>(curr_col)) {
				cout << (*col)[i].getValue();
			}
			else if (Column<string>* col = dynamic_cast<Column<string>*>(curr_col)) {
				cout << (*col)[i].getValue();
			}
			else if (Column<bool>* col = dynamic_cast<Column<bool>*>(curr_col)) {
				cout << (*col)[i].getValue();
			}*/
			cout << "\t";
			curr_col = curr_col->next_col;
		}
		cout << endl;
	}
	cout << endl;
}

void Table::connect() {

	Base_Column* curr_col = col_head;

	while (curr_col->next_col != NULL) {
		Base_Node* node = curr_col->getTail();
		Base_Node* next_node = curr_col->next_col->getTail();

		node->right = next_node;
		next_node->left = node;

		curr_col = curr_col->next_col;
	}

}


Base_Column& Table::operator[](string label) {

	Base_Column* curr_col = col_head;

	while (curr_col != NULL) {

		if (curr_col->label == label) {
			return *curr_col;
			/*if (Column<int>* col = dynamic_cast<Column<int>*>(curr_col)) {
				return (*col);
			}*/
			/*else if (Column<float>* col = dynamic_cast<Column<float>*>(curr_col)) {
				return (*col);
			}
			else if (Column<char>* col = dynamic_cast<Column<char>*>(curr_col)) {
				return (*col);
			}
			else if (Column<string>* col = dynamic_cast<Column<string>*>(curr_col)) {
				return (*col);
			}
			else if (Column<bool>* col = dynamic_cast<Column<bool>*>(curr_col)) {
				return (*col);
			}*/
		}

		curr_col = curr_col->next_col;
	}

	cout << "Column not found." << endl;
	return *curr_col;
}

//template Column<int>& Table::operator[]<int>(string label);
//template Column<float>& Table::operator[]<float>(string label);
//template Column<char>& Table::operator[]<char>(string label);
//template Column<string>& Table::operator[]<string>(string label);
//template Column<bool>& Table::operator[]<bool>(string label);

//template bool Table::addRow<int>(int);
//template bool Table::addRow<char>(char);
//template bool Table::addRow<string>(string);
//template bool Table::addRow<float>(float);
//template bool Table::addRow<bool>(bool);
//
//template bool Table::addRow<int, int>(int, int);
//template bool Table::addRow<int, string>(int, string);
//template bool Table::addRow<string, int>(string, int);
//template bool Table::addRow<string, string>(string, string);