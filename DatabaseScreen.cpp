#include "DatabaseScreen.h"
#include "ui_DatabaseScreen.h"

DatabaseScreen::DatabaseScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DatabaseScreen)
{
    ui->setupUi(this);
}

DatabaseScreen::~DatabaseScreen()
{
    delete ui;
}

void DatabaseScreen::on_pushButton_clicked()
{
    QString text;
    text = ui->textEdit->toPlainText();
   // qDebug() << text;

    QStringList textLines = text.split("\n");

    //qDebug() << textLines[0];
    Queue<std::string> input;

    for(int i=0; i<textLines.size(); i++)
    {
        //input.push_back(QString(textLines[i]).toStdString());
        input.enQueue(QString(textLines[i]).toStdString());
    }

    input2 = g1.GetWords(input);
//    int a = input.size;
//    for(int i=0; i<a; i++){
//        input2.push_back(input.peek());
//        input.deQueue();
//    }

    for(int i=0; i<input2.size(); i++){
        cout<<input2.at(i)<<endl;
    }

    validateQuery v1;
    if(v1.validate(input2)){
        if (v1.query.second.size() > 0) {
            std::cout << "Create Query: " << std::endl;
            std::cout << "table name: " << v1.query.first << std::endl;
            for (int i = 0; i < v1.query.second.size(); i++) {
                std::cout << "column " << i + 1 << " : " << v1.query.second[i].first << "\t" << v1.query.second[i].second << std::endl;

            }
        }
        if (!v1.InsertQuery.second.empty()) {
            std::cout << "Insertion Query: " << std::endl;
            std::cout << "table name: " << v1.InsertQuery.first << std::endl;
            for (int i = 0; i < v1.InsertQuery.second.size(); i++) {
                for (int j = 0; j < v1.InsertQuery.second.at(i).size(); j++) {
                    std::cout << " Row " << i+1 << " : " << v1.InsertQuery.second.at(i).at(j).first << " -> " << v1.InsertQuery.second.at(i).at(j).second << std::endl;
                }

            }
        }
        if (!v1.deleteQuery.empty()) {
            cout << "delete query: " << endl;
            cout << v1.deleteQuery << endl;
            if (v1.whereSelect.first.size() > 0)
                std::cout << "where query: " << std::endl;
            std::cout << v1.whereSelect.second << std::endl;
            for (int i = 0; i < v1.whereSelect.first.size(); i++) {
                std::cout << std::get<0>(v1.whereSelect.first[i]) << " " << std::get<1>(v1.whereSelect.first[i]) << " " << std::get<2>(v1.whereSelect.first[i]) << std::endl;
            }
        }
        if (!v1.alterQuery.second.empty()) {
            cout << "Alter query: " << endl;
            cout << "Table : " << v1.alterQuery.first << endl;
            for (int i = 0; i < v1.alterQuery.second.size(); i++) {
                cout << v1.alterQuery.second.at(i).first << " " << v1.alterQuery.second.at(i).second << endl;
            }
        }
        if (!v1.updateQuery.second.empty()) {
            cout << "Update query: " << endl;
            cout << "Table : " << v1.updateQuery.first << endl;
            for (int i = 0; i < v1.updateQuery.second.size(); i++) {
                cout << v1.updateQuery.second.at(i).first << " changed to " << v1.updateQuery.second.at(i).second << endl;
            }
        }
        if (v1.selectQuery.second.size() > 0) {
            std::cout << "Selection Query: " << std::endl;
            std::cout << "table name: " << v1.selectQuery.first << std::endl;
            for (int i = 0; i < v1.selectQuery.second.size(); i++) {
                std::cout << "column " << i + 1 << " : " << v1.selectQuery.second[i] << std::endl;

            }

            if(v1.whereSelect.first.size()>0)
                std::cout << "where query: " << std::endl;
            std::cout << v1.whereSelect.second << std::endl;
            for (int i = 0; i < v1.whereSelect.first.size(); i++) {
                std::cout <<  std::get<0>(v1.whereSelect.first[i]) <<" " << std::get<1>(v1.whereSelect.first[i]) << " " << std::get<2>(v1.whereSelect.first[i]) << std::endl;
            }

            if(!v1.orderSelect.first.empty())
                std::cout <<"Order query: " << v1.orderSelect.first <<" " << v1.orderSelect.second << std::endl;

            if (!v1.joinSelect.first.first.empty()) {
                std::cout << "Join query: " << std::endl;
                std::cout << v1.joinSelect.first.first << " -> " << v1.joinSelect.first.second << " on " << v1.joinSelect.second.first << " = " << v1.joinSelect.second.second << std::endl;
            }
        }
        if (v1.keys.size() > 0) {
            std::cout << "Primary key: " << v1.keys["pk"] << std::endl;
            std::string foreignKey;
            int fkCount = 0;
            foreignKey = foreignKey + "fk" + std::to_string(fkCount);
            for (int i = 0; i < v1.keys.size() - 1; i++) {
                std::cout << "Foreign key " <<i+1<<" : " << v1.keys[foreignKey] << std::endl;
                foreignKey.clear();
                fkCount++;
                foreignKey = foreignKey + "fk" + std::to_string(fkCount);
            }

        }
        if (!v1.dropTableQuery.empty()) {
            std::cout << "drop table: " << v1.dropTableQuery << std::endl;
        }



    }
    return;
}

