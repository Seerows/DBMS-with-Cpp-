#include "getWords.h"
vector<std::string> getWords::GetWords(vector<std::string> v) {

    int a = v.size();
    string* q1 = new string[a];
    for (int i = 0; i < a; i++) {
        q1[i] = v[i];
    }

    string q2;
    int k = 0;


    for (int i = 0; i < a; i++) {
        if (q1[i][0] != ' ') {
            q2 = q2 + ' ' + q1[i];
        }
        else {
            q2 = q2 + q1[i];
        }


    }

    std::cout << "QUERY IN 1D ARRAY(SPACES EXIST): " << q2 << endl;
    bool check = false;
    int count = 0;
    std::vector<char> vTemp;
    for (int i = 0; i < q2.length(); i++) {
        //vTemp.push_back(q2[i]);
        /*if ((q2[i] >= 97 && q2[i] <= 122) || (q2[i] >= 65 && q2[i] <= 90)) {
            if ((q2[i + 1] == ';' || q2[i + 1] == '(' || q2[i + 1] == ')')) {

                vTemp.push_back(' ');
            }
        }*/
        if ((q2[i] >= 58 && q2[i] <= 63) || (q2[i] >= 33 && q2[i] <= 47)) {

            vTemp.push_back(' ');
            vTemp.push_back(q2[i]);
            vTemp.push_back(' ');

        }
        else {
            vTemp.push_back(q2[i]);
        }
    }
    string q3;
    for (int i = 0; i < vTemp.size(); i++) {
        q3 = q3 + vTemp[i];
    }
    for (int i = 0; i < q3.length(); i++) {

        if (q3[i] == ' ' && check == false && count < 1) {
            check = true;
            q3[i] = '\\';
            count++;
            i++;
        }

        if (q3[i] != ' ') {
            check = false;
            count = 0;
        }
    }

    q3.erase(remove_if(q3.begin(), q3.end(), ::isspace),
             q3.end());


    std::cout << "QUERY IN 1D ARRAY(NO SPACES, \\ DELIMITER): " << q3 << endl;
    std::vector<std::string> v2;
    string word;
    for (auto x : q3) {
        if (x == '\\')
        {
            if (word != "") {
                v2.push_back(word);
                word = "";
            }
        }
        else {
            word = word + x;
        }

    }
    v2.push_back(word);
    std::cout << endl << "WORDS IN THE QUERY: " << endl;
    for (int i = 0; i < v2.size(); i++) {
        std::cout << v2[i] << endl;
    }
    return v2;
}
