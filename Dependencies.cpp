#include "Dependencies.h"

QDataStream& operator<<(QDataStream& out, Table& obj){

    out << obj.metadata.first;
    out << obj.num_of_cols;
    out << obj.num_of_rows;
    out << obj.metadata.second;

    out << obj.num_of_keys;
    out << obj.keys;

    for(int i=0; i<obj.num_of_rows; i++){
        for(int j=0; j<obj.num_of_cols; j++){

            if (Node<float>* node = dynamic_cast<Node<float>*>(&obj[j][i])) {
                out << node->data;
            }
            else if (Node<char>* node = dynamic_cast<Node<char>*>(&obj[j][i])) {
                out << node->data;
            }
            else if (Node<string>* node = dynamic_cast<Node<string>*>(&obj[j][i])) {
                out << node->data;
            }
            else if (Node<bool>* node = dynamic_cast<Node<bool>*>(&obj[j][i])) {
                out << node->data;
            }
            else{
                out << dynamic_cast<Node<int>*>(&obj[j][i])->data;
            }


        }
    }

    return out;
}

QDataStream& operator<<(QDataStream& out, int& obj){
    out << (qint32)obj;
    return out;
}

template <class T>
QDataStream& operator<<(QDataStream& out, Node<T>& obj){
    out << obj.data;
    return out;
}

QDataStream& operator<<(QDataStream& out, Node<string>& obj){
    out << QString::fromStdString(obj.data);
    return out;
}

QDataStream& operator>>(QDataStream& in, Table& obj){

    for(int i=0; i<temp_rows && obj.col_head; i++){
        Base_Column* curr_col = obj.col_head;
        obj.num_of_rows++;

        while(curr_col != NULL){

            if (Column<float>* col = dynamic_cast<Column<float>*>(curr_col)) {
                float temp;
                in >> temp;
                col->insertAtTail(temp);
            }
            else if (Column<char>* col = dynamic_cast<Column<char>*>(curr_col)) {
                char temp;
                in >> temp;
                col->insertAtTail(temp);
            }
            else if (Column<string>* col = dynamic_cast<Column<string>*>(curr_col)) {
                string temp;
                in >> temp;
                col->insertAtTail(temp);
            }
            else if (Column<bool>* col = dynamic_cast<Column<bool>*>(curr_col)) {
                bool temp;
                in >> temp;
                col->insertAtTail(temp);
            }
            else if (Column<int>* col = dynamic_cast<Column<int>*>(curr_col)) {
                int temp;
                in >> temp;
                curr_col->insertAtTail(temp);
            }
            curr_col = curr_col->next_col;
        }

        obj.connect();
    }


    return in;
}

QDataStream& operator<<(QDataStream& out, std::pair<string, string> &obj){
    out << obj.first << obj.second;
    return out;
}

QDataStream& operator>>(QDataStream& in, std::pair<string, string> &obj){
    in >> obj.first >> obj.second;
    return in;
}

QDataStream& operator<<(QDataStream& out, string &str){
    QString temp = QString::fromStdString(str);
    out << temp;
    return out;
}

QDataStream& operator>>(QDataStream& in, string &str){
    QString temp;
    in >> temp;
    str = temp.toStdString();

    return in;
}

QDataStream& operator<<(QDataStream& out, vector<pair<string, string>> &obj){

    for(pair<string, string> i : obj){
        out << i;
    }
    return out;
}


QDataStream& operator>>(QDataStream& in, vector<pair<string, string>> &obj){

    for(int i=0; i<obj.size(); i++){
        pair<string, string> temp;
        in >> temp;
        obj.at(i) = temp;
    }

    return in;
}

QDataStream& operator<<(QDataStream& out, map<string, string> &obj){

    for(const auto& key : obj){
        string s1 = key.first, s2 = key.second;

        out << s1;
        out << s2;
    }

    return out;
}

QDataStream& operator>>(QDataStream& in, map<string, string> &obj){

    for(int i = 0; i < temp_keys; i++){
        string s1, s2;
        in >> s1 >> s2;
        obj.insert(pair<string, string>(s1, s2));
    }

    return in;
}


tuple<string, string, string> parseFk(string s1) {
    int i = 0;

    std::tuple<std::string, std::string, std::string> t1;
    std::string col;
    std::string table;
    std::string refCol;

    while (s1[i] != '.') {
        col = col + s1[i];
        i++;
    }
    i++;
    while (s1[i] != '(') {
        table = table + s1[i];
        i++;
    }
    i++;
    while (s1[i] != ')') {
        refCol = refCol + s1[i];
        i++;
    }

    t1 = make_tuple(col, table, refCol);
    return t1;

}