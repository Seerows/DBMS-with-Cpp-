#ifndef GETWORDS_H
#define GETWORDS_H

#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<algorithm>
#include<ctype.h>
#include "Queue.h"


class getWords
{
public:
    vector<std::string> GetWords(Queue<std::string> q1);
};


#endif // GETWORDS_H
