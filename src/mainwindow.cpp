#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QtGui>
#include <QInputDialog>
#include "form.h"
#include <QtSql>

QString User[15];
int i = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_actionSair_triggered()
{
    int ret = QMessageBox::warning(this, tr("Chat"),tr("Você tem certeza que deseja sair ?"),
                  QMessageBox::Ok | QMessageBox::Cancel);

        switch(ret)
        {
            case QMessageBox::Ok:
            {
                qApp->quit();
                break;
            }
        }
}

void MainWindow::on_actionSobre_triggered()
{
    QMessageBox::information(this, tr("Chat"),tr("Criado por:\n\n\tGustavo Araújo"), QMessageBox::Ok);
}
void MainWindow::on_actionAdd_triggered()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Digite o usuário"),
                                             tr("Usuário:"), QLineEdit::Normal,
                                             NULL, &ok);
    extern QString user;
    qDebug() << user;
    if (ok && !text.isEmpty())
    {
        QSqlQuery Check;
        Check.prepare("SELECT * FROM usuarios WHERE username = ?");
        Check.addBindValue(text);
        bool Status = Check.exec();
        if(!Status) qDebug() << "Execução do código falhou!";
        if(!Check.next())
        {
            QMessageBox::warning(this, tr("Chat"),tr("Usuário inexistente!"), QMessageBox::Ok);
            return;
        }
        QSqlQuery Add;
        Add.prepare("INSERT INTO contatos (dono, contato, nome) VALUES (?, ?, ?)");
        Add.bindValue(0, user);
        Add.bindValue(1, text);
        Add.bindValue(2, Check.value(1).toString());
        qDebug() << user << " contato: " << text << " nome: " << Check.value(1).toString();
        if(!Add.exec())
        {
            QMessageBox::warning(this, tr("Chat"),tr("Ocorreu algum erro!"), QMessageBox::Ok);
            return;
        }
        User[i++] = text;
        QString Name = Check.value(1).toString(); //nome
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(Name);
        ui->listWidget->addItem(item);

    }

}

//Função responsável por adicionar um item a 'List Widget' para testar.
void MainWindow::LoadContatos()
{
    QSqlQuery Load;
    Load.prepare("SELECT * FROM contatos WHERE dono = ?");
    Load.addBindValue("Dolby");
    Load.exec();
    while(Load.next())
    {
        User[i++] = Load.value(2).toString();
        QString Name = Load.value(3).toString(); //nome
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(Name);
        ui->listWidget->addItem(item);
    }
}


void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    qDebug() << ui->listWidget->currentRow();
    qDebug() << User[ui->listWidget->currentRow()];
}
