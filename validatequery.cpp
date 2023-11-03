#include "validateQuery.h"
validateQuery::validateQuery(int numOfColumns) {
    this->numOfColumns = numOfColumns;
}
bool isAlphaCheck(std::string s) {
    bool check = true;
    for (int i = 0; i < s.length(); i++) {
        if (!(s[i] >= 65 && s[i] <= 90) && !(s[i] >= 97 && s[i] <= 122)) {
            check = false;
            //std::cout << "Error, column or table name cannot contain any special character." << std::endl;
        }
    }
    return check;

}

bool isDataTypeCheck(std::string s) {
    if (s == "char" || s == "varchar" || s == "text" || s == "bool" || s == "int" || s == "float" || s == "datetime" || s == "date" || s == "year" || s == "time" || s == "timestamp") {
        return true;
    }
    return false;
}
bool isAvailable(std::string s) {
    if (s == "create"||s=="drop" || s == "table" || s == "insert" || s == "alter" || s == "update" || s == "order" || s == "having" || s == "not" || s == "null" || s == "references" || s == "on" || s == "use" || s == "delete" || s == "by" || s == "desc" || s == "asc" || s == "group" || s == "distinct" || s == "from" || s == "limit" || s == "where" || s == "in" || s == "like" || s == "values" || s == "into" || isDataTypeCheck(s)) {
        return false;
    }
    return true;
}


bool isdigit(std::string s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] < 48 || s[i] > 57) {
            return false;
        }
    }
    return true;
}
std::string getDataType(std::string s1) {
    std::string type = typeid(std::stof(s1)).name();

    /*if (type == "f") {
        type = "float";
    }
    else if (type == "i") {
        type = "int";
    }
    else if (type == "b") {
        type = "bool";
    }
    else if (type == "c") {
        type = "char";
    }
    else if (type == "std::basic_string<char, std::char_traits<char>, std::allocator<char>>") {
        type = "string";
    }
    else {
        type = "---";
    }
    return type;*/

    if (isdigit(s1)) {
        return "int";
    }
    else if (!isdigit(s1) && (s1 == "True" || s1 == "False")) {
        return "bool";
    }
    else if (isAlphaCheck(s1) && s1.length() > 1) {
        return "std::basic_string<char, std::char_traits<char>, std::allocator<char>>";
    }
    else if (isAlphaCheck(s1)) {
        return "char";
    }
    else if (type == "float") {
        return "float";
    }
    else {
        return "---";
    }


}
bool validateQuery::validate(std::vector<std::string> v1) {
    std::pair<std::string, std::string> temp1;
    bool pcheck = false;
    int fkCount = 0;
    std::string foreignKey;
    std::string s1, s2, s3, s4;
    std::vector<std::pair<std::string, std::string>> temp;
    bool check = true;
    int innerNum = 0;
    std::string dataType;



    int num = 0;
    int a=0;
    int count = 0;
    std::pair<std::string, std::string> column;
    for (int i = 0; i < v1.size(); i++) {
        std::cout << i + 1 << " : |" << v1[i] <<"|" << std::endl;
        if (v1[i] == "") {
            v1.pop_back();
        }
    }

    std::vector<std::string> v1Copy = v1;
    /*for (int i = 0; i < v1.size(); i++) {
        v1Copy.push_back(v1.at(i));
    }*/
    for (int i = 0; i < v1.size(); i++) {
        std::transform(v1[i].begin(), v1[i].end(), v1[i].begin(), ::tolower);
    }

    for (int i = 0; i<v1.size();i++) {
        try {
            if (v1.at(i) + v1.at(i + 1) == "createtable" && isAlphaCheck(v1.at(i + 2)) && v1.at(i + 2) != "(" && v1.at(i + 3) == "(") {
                std::cout << v1[i] << " " << v1[i + 1] << v1[i + 2] << v1[i + 3] << std::endl;
                query.first = v1Copy.at(i + 2);
                a = i + 4;
                while (v1[a] != ")") {
                    if (isAlphaCheck(v1.at(a)) && !isDataTypeCheck(v1.at(a)) && isDataTypeCheck(v1.at(a + 1))) {
                        std::cout << v1.at(a) << " " << v1.at(a + 1) << " *" << a << " " << v1.size() << " " << v1.at(a + 2);
                        column.first = v1Copy.at(a);
                        column.second = v1Copy.at(a + 1);
                        query.second.push_back(column);
                        count++;
                        if (v1.at(a + 2) == ",") {
                            std::cout << v1[a + 2] << std::endl;
                            a += 3;


                        }
                        else if (v1.at(a + 2) == ")") {
                            std::cout << v1[a + 2] << std::endl;
                            a += 2;

                        }



                        else if (v1.at(a + 2) + v1.at(a + 3) == "primarykey" /*&& (v1[a + 4] == "," || v1[a+4]==")")*/) {
                            keys["pk"] = v1Copy[a];
                            if (v1.at(a + 4) == ",") {
                                std::cout << v1[a + 2] << " " << v1[a + 3] << v1[a + 4] << std::endl;
                                a += 5;
                            }
                            else if (v1.at(a + 4) == ")") {
                                std::cout << v1[a + 2] << " " << v1[a + 3] << v1[a + 4] << std::endl;
                                a += 4;
                            }
                            else {
                                check = false;
                                break;
                            }


                        }
                        else if (v1.at(a + 2) + v1.at(a + 3) + v1.at(a + 4) == "foreignkeyreferences" && isAlphaCheck(v1.at(a + 5)) &&!isDataTypeCheck(v1.at(a+5))&& v1.at(a + 6) == "(" && isAlphaCheck(v1.at(a + 7)) && v1.at(a + 8) == ")") {
                            foreignKey = foreignKey + "fk" + std::to_string(fkCount);
                            keys[foreignKey] = v1Copy.at(a);
                            foreignKey.clear();
                            fkCount++;
                            if (v1.at(a + 9) == ",") {
                                std::cout << v1[a + 2] << " " << v1[a + 3] << v1[a + 4] << std::endl;
                                a += 10;
                            }
                            else if (v1.at(a + 9) == ")") {
                                std::cout << v1[a + 2] << " " << v1[a + 3] << v1[a + 4] << std::endl;
                                a += 9;
                            }
                            else {
                                check = false;
                                break;
                            }
                        }


                        else {
                            check = false;
                            break;
                        }

                    }
                    else {
                        check = false;
                        break;
                    }
                    std::cout << v1[a] << std::endl;
                }

                if (v1.at(a + 1) == ";") {
                    check = true;
                    a++;
                    std::cout << count << "\t" << query.second.size() << std::endl;
                }
                else {
                    check = false;
                }


                i += a;
                std::cout << "index: " << i << std::endl;
                std::cout << "size: " << v1.size() << std::endl;
                std::cout << "**************" << v1.at(i) << "****************" << std::endl;
                std::cout << "check 1:" << check << std::endl;
                /*if (v1[i] == ";") {
                    check = true;
                    break;
                }*/

            }
            else if (v1.at(i) + v1.at(i + 1) == "insertinto" && isAlphaCheck(v1.at(i + 2)) && isAvailable(v1.at(i + 2)) && v1.at(i + 3) == "values")
            {std::cout << v1[i] << " " << v1[i + 1] << std::endl;
                a = 0;
                a = i + 4;
                int counter = 0;
                std::pair<std::string, std::string> p1;
                InsertQuery.first = v1.at(i + 2);
                while (v1.at(a) != ";") {
                    std::string s1;
                    if (v1.at(a) == "(") {
                        counter = a + 1;
                        std::cout << "Counter at start: " << counter << std::endl;
                        while (v1.at(counter) !=")") {
                            if (v1.at(counter) != ",") {


                                /*if (v1.at(counter - 1) == "'" ||(v1.at(counter - 2) == "'" && v1.at(counter) == "'")) {
                                        s1 = s1 + v1.at(counter);
                                    }
                                    else {
                                        s1 = s1 + ' ' + v1.at(counter);
                                    }*/
                                if (v1.at(counter) == "'") {
                                    s1 = s1 + v1Copy.at(++counter);
                                    while (v1Copy.at(++counter) != "'") {
                                        s1 = s1 + v1Copy.at(counter);
                                    }
                                    //s1 = s1 + v1.at(counter);

                                    p1.first = getDataType(s1);
                                    p1.second = s1;
                                    //std::cout << v1.at(counter) << std::endl;
                                    innerNum++;
                                }
                                else {
                                    //std::cout << v1.at(counter) << std::endl;

                                    p1.first = getDataType(s1);
                                    p1.second = v1Copy.at(counter);
                                    innerNum++;


                                }
                                //std::cout << innerNum << std::endl;
                                //insertQuery.second.push_back(p1);

                                temp.push_back(p1);
                                for (int i = 0; i < temp.size(); i++) {
                                    std::cout << temp.at(i).first << " " << temp.at(i).second << std::endl;
                                }
                                if (innerNum == numOfColumns) {
                                    innerNum = 0;
                                    InsertQuery.second.push_back(temp);
                                    std::cout << "Ran once" << std::endl;

                                    temp.clear();
                                }

                                s1.clear();

                                /*insertQuery.second.at(counter).first = isdigit(v1.at(counter))?"int":"char";
                                insertQuery.second.at(counter).second = v1.at(counter);*/



                            }
                            /*else {
                                check = false;
                                break;
                            }*/

                            counter++;
                        }

                        std::cout << s1 << std::endl;
                        std::cout << counter << " "<<v1.at(counter)<<std::endl;
                        if (v1.at(counter + 1) == ";") {
                            a = counter+1;
                        }
                        else if (v1.at(counter + 1) == ",") {
                            a = counter + 2;
                        }
                        else {
                            check = false;
                            break;
                        }

                        std::cout << v1.at(a) << std::endl;
                        counter = 0;
                        std::cout << std::endl;
                        //s1.clear();
                    }
                    else {
                        check = false;
                        break;
                    }

                }
                std::cout << v1.size() << std::endl;
                i += a;
            }
            else if (v1.at(i) == "select" || v1.at(i) == "delete" || v1.at(i)=="update") {
                std::cout << "select" << std::endl;
                a = 0;
                a = i + 1;
                int b = 0;
                while (v1.at(a) != ";" && check!=false) {
                    if (v1.at(a) == "*") {
                        selectQuery.second.push_back(v1Copy.at(a));
                        a++;
                    }
                    else if (isAlphaCheck(v1.at(a)) && !isDataTypeCheck(v1.at(a)) && v1.at(a-1)=="select") {
                        b = a;
                        //std::cout << v1.at(a) << std::endl;
                        while (v1.at(b) != "from") {
                            if (v1.at(b) == "," ) {
                                if (v1.at(b + 1) == "from") {
                                    check = false;
                                    break;
                                }
                                else {
                                    std::cout << "," << std::endl;
                                    b += 1;
                                }

                            }
                            else if (isAlphaCheck(v1.at(b)) && !isDataTypeCheck(v1.at(b)) && v1.at(b+1)=="(" && ((isAlphaCheck(v1.at(b+2)) && !isDataTypeCheck(v1.at(b+2))) || v1.at(b+2) =="*") && v1.at(b + 3) == ")") {
                                std::string function = v1Copy.at(b) + v1Copy.at(b + 1) + v1Copy.at(b + 2) + v1Copy.at(b + 3);
                                if (num > 0 && v1.at(b - 1) != "," && v1.at(b + 4) != "from") {
                                    check = false;
                                    break;
                                }
                                selectQuery.second.push_back(function);
                                std::cout << function << std::endl;
                                b += 4;
                                num++;
                                std::cout << v1.at(b) << std::endl;
                            }
                            else if (isAlphaCheck(v1.at(b)) && !isDataTypeCheck(v1.at(b))) {
                                if (num > 0 && v1.at(b - 1) != "," && v1.at(b + 1) != "from") {
                                    check = false;
                                    break;
                                }
                                selectQuery.second.push_back(v1Copy.at(b));
                                std::cout << v1.at(b) << std::endl;
                                b += 1;
                                num++;
                            }
                            else {
                                check = false;
                                break;
                            }



                        }

                        a = b;
                        std::cout << v1.at(a) << std::endl;

                    }
                    else if (isAlphaCheck(v1.at(a)) && !isDataTypeCheck(v1.at(a)) && v1.at(a - 1) == "update") {
                        updateQuery.first = v1Copy.at(a);
                        std::pair<std::string, std::string> p;
                        if (v1.at(a + 1) == "set") {
                            a += 2;
                            while (v1.at(a) != ";" && v1.at(a) != "where") {
                                if (isAlphaCheck(v1.at(a)) && !isDataTypeCheck(v1.at(a)) && v1.at(a + 1) == "=" && isdigit(v1.at(a + 2))) {
                                    p.first = v1Copy.at(a);
                                    p.second = v1Copy.at(a + 2);
                                    updateQuery.second.push_back(p);
                                    a += 3;

                                }
                                else if (isAlphaCheck(v1.at(a)) && !isDataTypeCheck(v1.at(a)) && v1.at(a + 1) == "=" && v1.at(a + 2) == "'" && isAlphaCheck(v1.at(a + 3)) && !isDataTypeCheck(v1.at(a + 3)) && v1.at(a + 4) == "'") {
                                    p.first = v1Copy.at(a);
                                    p.second = v1Copy.at(a + 3);
                                    updateQuery.second.push_back(p);
                                    a += 5;
                                }
                                else {
                                    check = false;
                                    break;
                                }
                                if (v1.at(a) != "where" && v1.at(a)!=";") {
                                    if (v1.at(a) != ",") {
                                        std::cout << "update error" << std::endl;
                                        check = false;
                                        break;
                                    }
                                    else {
                                        a++;
                                    }
                                }
                            }
                        }
                    }
                    else if (v1.at(a) == "from" && v1.at(a-1) == "delete") {
                        if (isAlphaCheck(v1.at(a + 1)) && !isDataTypeCheck(v1.at(a + 1))) {
                            deleteQuery = v1Copy.at(a + 1);
                            a += 2;
                            std::cout << v1.at(a) << std::endl;
                        }
                        else {
                            check = false;
                            break;
                        }
                    }
                    else if (v1.at(a) == "from" ) {
                        if (isAlphaCheck(v1.at(a + 1)) && !isDataTypeCheck(v1.at(a + 1))) {
                            selectQuery.first = v1Copy.at(a + 1);
                            a += 2;
                            std::cout << v1Copy.at(a) << std::endl;
                        }
                        else {
                            check = false;
                            break;
                        }
                    }
                    else if (v1.at(a) == "where") {
                        std::tuple<std::string, std::string, std::string> tupleTemp;
                        std::cout << "where" << std::endl;
                        a++;
                        while (v1.at(a) != ";") {

                            if (isAlphaCheck(v1.at(a)) && !isDataTypeCheck(v1.at(a))) {
                                std::cout << v1.at(a) << std::endl;
                                if (v1.at(a + 1) + v1.at(a + 2) == "!=" || v1.at(a + 1) + v1.at(a + 2) == "<=" || v1.at(a + 1) + v1.at(a + 2) == ">=") {
                                    std::cout << v1.at(a + 1) + v1.at(a + 2) << std::endl;
                                    if (isdigit(v1.at(a + 3))) {
                                        tupleTemp = make_tuple(v1Copy.at(a), v1Copy.at(a + 1) + v1Copy.at(a + 2), v1Copy.at(a + 3));
                                        whereSelect.push_back(tupleTemp);
                                        a += 4;
                                    }
                                    else if (v1.at(a + 3) == "'" && isAlphaCheck(v1.at(a + 4)) && v1.at(a + 5) == "'") {
                                        tupleTemp = make_tuple(v1Copy.at(a), v1Copy.at(a + 1) + v1Copy.at(a + 2), v1Copy.at(a + 4));
                                        whereSelect.push_back(tupleTemp);
                                        a += 6;
                                    }
                                    else {
                                        check = false;
                                        break;
                                    }
                                }
                                else if (v1.at(a + 1) == "=" || v1.at(a + 1) == "<" || v1.at(a + 1) == ">") {
                                    std::cout << v1.at(a + 1) << std::endl;
                                    if (isdigit(v1.at(a + 2))) {
                                        tupleTemp = make_tuple(v1Copy.at(a), v1Copy.at(a + 1), v1Copy.at(a + 2));
                                        whereSelect.push_back(tupleTemp);
                                        a += 3;
                                    }
                                    else if (v1.at(a + 2) == "'" && isAlphaCheck(v1.at(a + 3)) && v1.at(a + 4) == "'") {
                                        tupleTemp = make_tuple(v1Copy.at(a), v1Copy.at(a+1), v1Copy.at(a + 3));
                                        whereSelect.push_back(tupleTemp);
                                        a += 5;
                                    }


                                    else {
                                        check = false;
                                        break;
                                    }
                                }

                                else {
                                    check = false;
                                    break;
                                }

                                if (v1.at(a) == "and") {
                                    a++;
                                }
                            }
                        }

                    }
                    else if (v1.at(a) + v1.at(a + 1) == "orderby") {
                        if (isAlphaCheck(v1.at(a + 2)) && !isDataTypeCheck(v1.at(a + 2)) && (v1.at(a+3)=="asc" || v1.at(a+3)=="desc")) {
                            orderSelect.first = v1Copy.at(a + 2);
                            orderSelect.second = v1Copy.at(a + 3);
                            a += 4;
                        }
                        else {
                            check = false;
                            break;
                        }
                    }
                    else if (v1.at(a) == "join") {
                        std::cout << "reached" << std::endl;
                        temp1.first = v1Copy.at(a - 1);
                        if (isAlphaCheck(v1.at(a + 1)) && !isDataTypeCheck(v1.at(a + 1)) && v1.at(a + 2) == "on") {
                            std::cout << "reached" << std::endl;
                            temp1.second= v1Copy.at(a + 1);
                            if (isAlphaCheck(v1.at(a + 3)) && !isDataTypeCheck(v1.at(a + 3)) && v1.at(a+4)=="." && isAlphaCheck(v1.at(a + 5)) && !isDataTypeCheck(v1.at(a + 5)) && v1.at(a + 6) == "=" && isAlphaCheck(v1.at(a + 7)) && !isDataTypeCheck(v1.at(a + 7)) && v1.at(a+8)=="." && isAlphaCheck(v1.at(a + 9)) && !isDataTypeCheck(v1.at(a + 9))) {
                                std::cout << "reached" << std::endl;
                                joinSelect.first= temp1;
                                std::cout << "reached" << std::endl;
                                /*while (v1.at(a+3)[periodCount] != '.') {
                                    s1 = s1 + v1.at(a + 3)[periodCount];
                                    periodCount++;
                                }
                                std::cout << s1 << std::endl;
                                periodCount++;
                                while (periodCount < v1.at(a + 3).length()) {
                                    s2 = s2 + v1.at(a + 3)[periodCount];
                                    periodCount++;
                                }
                                std::cout << s2 << std::endl;

                                periodCount = 0;
                                while (v1.at(a + 5)[periodCount] != '.') {
                                    s3 = s3 + v1.at(a + 5)[periodCount];
                                    periodCount++;
                                }
                                std::cout << s3 << std::endl;
                                periodCount++;
                                while (periodCount < v1.at(a + 5).length()) {
                                    s4 = s4 + v1.at(a + 5)[periodCount];
                                    periodCount++;
                                }
                                std::cout << s4 << std::endl;
                                */
                                if (v1.at(a+3) != temp1.first || v1.at(a+7) != temp1.second) {
                                    check = false;
                                    std::cout << "Invalid on" << std::endl;
                                    break;
                                }
                                temp1.first = v1Copy.at(a+5);
                                temp1.second = v1Copy.at(a+9);
                                joinSelect.second = temp1;
                                a += 10;
                            }
                            else {
                                check = false;
                                break;
                            }
                        }
                        else {
                            check = false;
                            break;
                        }
                    }
                    else {
                        check = false;
                        break;
                    }
                }
                std::cout << v1.size() << " " << a << std::endl;
                i += a;

            }
            else if (v1.at(i) + v1.at(i + 1) == "altertable" && isAlphaCheck(v1.at(i+2)) && !isDataTypeCheck(v1.at(i+2))) {
                std::cout << "alter" << std::endl;
                a = i + 3;
                alterQuery.first = v1Copy.at(i + 2);
                std::pair<std::string, std::string> p;
                if (v1.at(a) == "add") {
                    std::cout << "add" << std::endl;
                    a++;
                    if (v1.at(a) == "(") {
                        a++;
                        pcheck = true;


                    }
                    while (v1.at(a) != ";") {

                        if (pcheck) {
                            std::cout << v1.at(a) << std::endl;
                            if (isAlphaCheck(v1.at(a)) && !isDataTypeCheck(v1.at(a)) && isDataTypeCheck(v1.at(a + 1))) {
                                std::cout << v1.at(a) << std::endl;
                                p.first = v1Copy.at(a + 1);
                                p.second = v1Copy.at(a);
                                alterQuery.second.push_back(p);
                                a += 2;
                                std::cout << v1.at(a) << std::endl;
                            }
                            else {
                                check = false;
                                break;
                            }
                            if (v1.at(a) != ")") {
                                if (v1.at(a) != ",") {
                                    check = false;
                                    break;
                                }
                                else {
                                    a++;
                                }
                            }
                            else {
                                a++;
                                pcheck = false;
                                if (v1.at(a) != ";") {
                                    check = false;
                                    break;
                                }
                            }
                        }
                        else if (isAlphaCheck(v1.at(a)) && !isDataTypeCheck(v1.at(a)) && isDataTypeCheck(v1.at(a+1))) {
                            std::cout << v1.at(a) << std::endl;
                            p.first = v1Copy.at(a + 1);
                            p.second = v1Copy.at(a );
                            alterQuery.second.push_back(p);
                            a += 2;
                            if (v1.at(a) != ";") {
                                check = false;
                                break;
                            }
                        }
                        else {
                            check = false;
                            break;
                        }


                    }
                }
                else if (v1.at(a)+v1.at(a+1) == "dropcolumn") {
                    std::cout << "drop" << std::endl;
                    if (isAlphaCheck(v1.at(a + 2)) && !isDataTypeCheck(v1.at(a + 2)) && v1.at(a+3)==";") {
                        p.first = "drop";
                        p.second = v1Copy.at(a + 2);
                        alterQuery.second.push_back(p);
                        a += 4;
                    }
                    else {
                        check = false;
                        break;
                    }
                }
                else if (v1.at(a) + v1.at(a + 1) == "renamecolumn") {
                    std::cout << "rename" << std::endl;
                    if (isAlphaCheck(v1.at(a + 2)) && !isDataTypeCheck(v1.at(a + 2)) && v1.at(a + 3) == "to" && isAlphaCheck(v1.at(a + 4)) && !isDataTypeCheck(v1.at(a + 4)) && v1.at(a + 5) == ";") {
                        p.first = "rename";
                        p.second = v1Copy.at(a + 2) + '~' + v1Copy.at(a + 4);
                        alterQuery.second.push_back(p);
                        a += 6;
                    }
                    else {
                        check = false;
                    }
                }
                i += a;
            }
            else if (v1.at(a)+v1.at(a+1) == "droptable") {
                std::cout << "drop" << std::endl;
                if (isAlphaCheck(v1.at(a + 2)) && !isDataTypeCheck(v1.at(a + 2)) && v1.at(a + 3) == ";") {
                    dropTableQuery = v1.at(a + 2);
                    a += 4;
                }
                else {
                    check = false;
                    break;
                }
                i += a;
            }
            else {
                check = false;
                std::cout << "check 3:" << check << std::endl;
                break;
            }
        }
        catch (...) {
            std::cout << "Error" << std::endl;
            check = false;
            break;
        }

    }

    std::cout << check << std::endl;
    return check;
}
