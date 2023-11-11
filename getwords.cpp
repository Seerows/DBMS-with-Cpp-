#include "getWords.h"
#include "Queue.h"
vector<std::string> getWords::GetWords(Queue<std::string> v) {

    string* q1 = new string[v.size];
    for (int i = 0; i < v.size; i++) {
        q1[i] = v.peek();
        v.dequeue();
    }

    string q2;
    int k = 0;


    for (int i = 0; i < v.size; i++) {
        if (q1[i][0] != ' ') {
            q2 = q2 + ' ' + q1[i];
        }
        else {
            q2 = q2 + q1[i];
        }


    }

    bool check = false;
    int count = 0;
    std::vector<char> vTemp;
    for (int i = 0; i < q2.length(); i++) {
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
    std::cout << q3 << std::endl;
    q3.erase(remove_if(q3.begin(), q3.end(), ::isspace),
        q3.end());


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
    for (int i = 0; i < v2.size(); i++) {
        std::cout << v2.at(i) << std::endl;
    }
    return v2;
}
