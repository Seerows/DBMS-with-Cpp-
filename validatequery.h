#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>
#include<cctype>
#include<map>
#include<tuple>
class validateQuery
{
public:
	int numOfColumns;
	validateQuery(int);
	bool validate(std::vector<std::string> v1);
	std::pair<std::string, std::vector<std::pair<std::string, std::string>>> query;
	bool createCheck;

	std::pair<std::string, std::vector < std::vector<std::pair<std::string, std::string> > > > InsertQuery;
	bool insertCheck;

	std::map<std::string, std::string> keys;
	bool pkeyCheck;
	bool fkeyCheck;

	std::pair< std::string, std::vector<std::string>> selectQuery;
	bool selectCheck;

	std::vector<std::tuple<std::string, std::string, std::string>> whereSelect;
	bool whereCheck;
	std::pair<std::string, std::string> orderSelect;
	bool orderCheck;

	std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string>> joinSelect;
	bool joinCheck;
	
	std::string deleteQuery;
	bool deleteCheck;
	
	std::pair<std::string, std::vector<std::pair<std::string, std::string>>> updateQuery;
	bool updateCheck;
	
	std::pair<std::string, std::vector<std::pair<std::string, std::string>>> alterQuery;
	bool alterCheck;
	
	std::string dropTableQuery;
	bool dropTableCheck;
};

