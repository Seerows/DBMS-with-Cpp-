#ifndef DEPENDENCIES_H
#define DEPENDENCIES_H

#include <iostream>
#include <QDataStream>
#include <QString>
#include "Table.h"
#include "Node.h"
#include "Column.h"

using namespace std;

extern int temp_rows;

QDataStream& operator<<(QDataStream& out, Table& obj);
QDataStream& operator>>(QDataStream& in, Table& obj);

QDataStream& operator>>(QDataStream& in, Table& obj);

QDataStream& operator<<(QDataStream& out, std::pair<string, string> &obj);
QDataStream& operator>>(QDataStream& in, std::pair<string, string> &obj);
QDataStream& operator<<(QDataStream& out, string& str);
QDataStream& operator>>(QDataStream& in, string& str);
QDataStream& operator<<(QDataStream& out, vector<pair<string, string>> &obj);
QDataStream& operator>>(QDataStream& in, vector<pair<string, string>> &obj);

#endif // DEPENDENCIES_H
