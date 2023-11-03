#ifndef VALIDATEQUERY_H
#define VALIDATEQUERY_H

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
    validateQuery(int);
    int numOfColumns;
    bool validate(std::vector<std::string> v1);
    std::pair<std::string, std::vector<std::pair<std::string, std::string>>> query;
    //std::pair<std::string, std::vector<std::pair<std::string, std::string>>> insertQuery;
    std::pair<std::string, std::vector < std::vector<std::pair<std::string, std::string> > > > InsertQuery;
    std::map<std::string, std::string> keys;
    std::pair< std::string, std::vector<std::string>> selectQuery;
    //std::pair< std::string, std::vector<std::string>> furherSelectQuery;
    std::vector<std::tuple<std::string, std::string, std::string>> whereSelect;
    std::pair<std::string, std::string> orderSelect;
    std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string>> joinSelect;
    std::string deleteQuery;
    std::pair<std::string, std::vector<std::pair<std::string, std::string>>> updateQuery;
    std::pair<std::string, std::vector<std::pair<std::string, std::string>>> alterQuery;
    std::string dropTableQuery;
};



#endif // VALIDATEQUERY_H
