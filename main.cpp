#include<iostream>
#include<vector>
#include<string>
#include"getWords.h"
#include"validateQuery.h"
#include<tuple>
#include"Queue.h"

int main() {
    
    std::string line;
    Queue<std::string> q1;
    while (std::getline(std::cin, line))
    {
        if (line.empty()) {
            break;
        }
        q1.enqueue(line);
    }
    getWords g1;
    vector<std::string> finalWords = g1.GetWords(q1);
       validateQuery vq;
    //cout << vq.validate(finalWords);
    if (vq.validate(finalWords)) {
        if (vq.query.second.size() > 0) {
            std::cout << "Create Query: " << std::endl;
            std::cout << "table name: " << vq.query.first << std::endl;
            for (int i = 0; i < vq.query.second.size(); i++) {
                std::cout << "column " << i + 1 << " : " << vq.query.second[i].first << "\t" << vq.query.second[i].second << std::endl;

            }
        }
        int count = 0;
        /*if (vq.insertQuery.second.size() > 0) {
            std::cout << "table name: " << vq.insertQuery.first << std::endl;
            for (int i = 0; i < vq.insertQuery.second.size(); i++) {
                if (i % 6 == 0) {
                    count++;
                    std::cout << std::endl;
                }
                std::cout << " Row " << count << " : " << vq.insertQuery.second.at(i).first << " -> " << vq.insertQuery.second.at(i).second << std::endl;
            }
        }*/
        if (!vq.InsertQuery.second.empty()) {
            std::cout << "Insertion Query: " << std::endl;
            std::cout << "table name: " << vq.InsertQuery.first << std::endl;
            for (int i = 0; i < vq.InsertQuery.second.size(); i++) {
                for (int j = 0; j < vq.InsertQuery.second.at(i).size(); j++) {
                    std::cout << " Row " << i+1 << " : " << vq.InsertQuery.second.at(i).at(j).first << " -> " << vq.InsertQuery.second.at(i).at(j).second << std::endl;
                }
                
            }
        }
        if (!vq.deleteQuery.empty()) {
            cout << "delete query: " << endl;
            cout << vq.deleteQuery << endl;
            if (vq.whereSelect.size() > 0)
                std::cout << "where query: " << std::endl;
            for (int i = 0; i < vq.whereSelect.size(); i++) {
                std::cout << std::get<0>(vq.whereSelect[i]) << " " << std::get<1>(vq.whereSelect[i]) << " " << std::get<2>(vq.whereSelect[i]) << std::endl;
            }
        }
        if (!vq.alterQuery.second.empty()) {
            cout << "Alter query: " << endl;
            cout << "Table : " << vq.alterQuery.first << endl;
            for (int i = 0; i < vq.alterQuery.second.size(); i++) {
                cout << vq.alterQuery.second.at(i).first << " " << vq.alterQuery.second.at(i).second << endl;
            }
        }
        if (!vq.updateQuery.second.empty()) {
            cout << "Update query: " << endl;
            cout << "Table : " << vq.updateQuery.first << endl;
            for (int i = 0; i < vq.updateQuery.second.size(); i++) {
                cout << vq.updateQuery.second.at(i).first << " changed to " << vq.updateQuery.second.at(i).second << endl;
            }
        }
        if (vq.selectQuery.second.size() > 0) {
            std::cout << "Selection Query: " << std::endl;
            std::cout << "table name: " << vq.selectQuery.first << std::endl;
            for (int i = 0; i < vq.selectQuery.second.size(); i++) {
                std::cout << "column " << i + 1 << " : " << vq.selectQuery.second[i] << std::endl;

            }

            if(vq.whereSelect.size()>0)
            std::cout << "where query: " << std::endl;
            for (int i = 0; i < vq.whereSelect.size(); i++) {
                std::cout <<  std::get<0>(vq.whereSelect[i]) <<" " << std::get<1>(vq.whereSelect[i]) << " " << std::get<2>(vq.whereSelect[i]) << std::endl;
            }

            if(!vq.orderSelect.first.empty())
            std::cout <<"Order query: " << vq.orderSelect.first <<" " << vq.orderSelect.second << std::endl;

            if (!vq.joinSelect.first.first.empty()) {
                std::cout << "Join query: " << std::endl;
                std::cout << vq.joinSelect.first.first << " -> " << vq.joinSelect.first.second << " on " << vq.joinSelect.second.first << " = " << vq.joinSelect.second.second << std::endl;
            }
        }
        if (vq.keys.size() > 0) {
            std::cout << "Primary key: " << vq.keys["pk"] << std::endl;
            std::string foreignKey;
            int fkCount = 0;
            foreignKey = foreignKey + "fk" + std::to_string(fkCount);
            for (int i = 0; i < vq.keys.size() - 1; i++) {
                std::cout << "Foreign key " <<i+1<<" : " << vq.keys[foreignKey] << std::endl;
                foreignKey.clear();
                fkCount++;
                foreignKey = foreignKey + "fk" + std::to_string(fkCount);
            }
            
        }
        if (!vq.dropTableQuery.empty()) {
            std::cout << "drop table: " << vq.dropTableQuery << std::endl;
        }
        
        
    }
    return 0;



}
