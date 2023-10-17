#include "mainwindow.h"

#include <QApplication>
#include "Table.h"
using namespace std;

int main(int argc, char *argv[])
{

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
    employees.addColumn(pair<string, string>("float", "Salary"));

    employees.addRow(9, string("Row6"), 'U', 2, true, 900.2f);

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

    cout << "\nJoining Employees and Departments..." << endl;
    Table* table = employees.join(&employees["Dept_ID"], &departments["ID"]);
    table->display();

//    pair<string, vector<pair<string, string>>> query3;
//    query3.first = "Temp";
//    query3.second.push_back(pair<string, string>("class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >", "Name"));
//    query3.second.push_back(pair<string, string>("float", "Pay"));

//    Table temp(query3);

//    temp.addRow(string("Row2"), 3.4f);
//    temp.addRow(string("Row5"), 2.2f);
//    temp.addRow(string("Row6"), 8.7f);

//    temp.display();
//    table = temp.join(&temp["Name"], &employees["Name"]);
//    table->display();

    return 0;
    //make a Primary_Column class that handles creation of Primary Key (as well as autoincrement?) and makes sure all keys are unique
    //make a Foreign_Column class that checkes if all keys exist in the reference column
    //add error handling in the addRow function. Also add backtracking.


}
