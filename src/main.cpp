#include "form.h"
#include "mainwindow.h"
#include <QApplication>
#include <QtSql>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Form start;
    start.show();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("mysql");
    db.setUserName("root");
    db.setPassword("root");
    if (!db.open())
    {
        QMessageBox msgBox;
        msgBox.setText("Nosso servidor encontra-se em manutenção!");
        msgBox.exec();
    }

    MainWindow Main;
    //MainWindow window;
    //window.show();
    //window.close();
    return a.exec();
}
