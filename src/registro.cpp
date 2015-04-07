#include "registro.h"
#include "ui_registro.h"
#include "form.h"
#include <QtSql>
#include <QMessageBox>

bool bOpen = false;

Registro::Registro(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registro)
{
    ui->setupUi(this);
}

Registro::~Registro()
{
    delete ui;
}

void Registro::on_pushButton_pressed()
{
    QString username = ui->username->text();
    QString nome = ui->name->text();
    QString senha = ui->password->text();
    ui->label->setText("");
    if(username.isEmpty() || nome.isEmpty() || senha.isEmpty())
    {
        QMessageBox Box;
        Box.setText("Não deixe campos em branco!");
        Box.exec();
        return;
    }
    QSqlQuery check;
    check.prepare("SELECT * FROM usuarios WHERE username = ?");
    check.addBindValue(username);
    check.exec();
    if(check.next())
    {
        ui->label->setText("Nome de usuário em uso!");
        return;
    }
    QSqlQuery insert;
    insert.prepare("INSERT INTO usuarios (nome, senha, username) VALUES (?, ?, ?)");
    insert.bindValue(0, nome);
    insert.bindValue(1, senha);
    insert.bindValue(2, username);
    int ex = insert.exec();
    if(!ex) qDebug() << "Falha!";
    QMessageBox Sucess;
    Sucess.setText("Registrado com sucesso!");
    if(Sucess.exec())
    {
        Registro::close();
        Form* window = new Form();
        window->show();
    }


}
