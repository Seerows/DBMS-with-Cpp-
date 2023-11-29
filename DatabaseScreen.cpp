#include "DatabaseScreen.h"
#include "ui_DatabaseScreen.h"

DatabaseScreen::DatabaseScreen(QWidget *parent) : QMainWindow(parent), ui(new Ui::DatabaseScreen), db("Arqam_DB"){
    ui->setupUi(this);
    db.pull();
}

DatabaseScreen::~DatabaseScreen(){
    delete ui;
}

void DatabaseScreen::on_pushButton_clicked(){

    QString text;
    text = ui->textEdit->toPlainText();

    QRegularExpression regex("(?<=;)");

    QStringList queries = text.split(regex);
    queries.removeAll("");

    for(int i = 0; i<queries.size(); i++){
        QStringList textLines = queries.at(i).split("\n");

        Queue<std::string> input;

        for(int i=0; i<textLines.size(); i++){
            input.enQueue(QString(textLines[i]).toStdString());
        }

        vector<string> words = g1.GetWords(input);
        db.processQuery(words);
    }


}

