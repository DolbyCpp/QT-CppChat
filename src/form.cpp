#include "form.h"
#include "ui_form.h"
#include "mainwindow.h"
#include "registro.h"
#include <QtSql>
#include <QMessageBox>

bool open = false;
QString user;

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_pressed()
{
    user = ui->user->text();
    QString senha = ui->pass->text();

    QSqlQuery query("CREATE TABLE IF NOT EXISTS usuarios (`id` int(5) NOT NULL AUTO_INCREMENT,`nome` varchar(30) NOT NULL,`senha` varchar(20) NOT NULL,`username` varchar(20) NOT NULL, PRIMARY KEY (`id`))"); //cria ela novamente
    QSqlQuery query2("CREATE TABLE IF NOT EXISTS contatos (`id` int(5) NOT NULL AUTO_INCREMENT,`dono` varchar(30) NOT NULL,`contato` varchar(20) NOT NULL, `nome` varchar(20) NOT NULL, PRIMARY KEY (`id`))"); //cria ela novamente


    QSqlQuery Login;
    Login.prepare("SELECT * FROM usuarios WHERE username = ?");
    Login.addBindValue(user);
    bool Status = Login.exec();
    if(!Status) qDebug() << "Execução do código falhou!";
    if(!Login.next())
    {

        QMessageBox::warning(this, tr("Chat"),
                             tr("Usuário inexistente.\n\n"
                             "Uma conta é necessaria para logar-se!"),
                             QMessageBox::Ok);
        return;
    }
    if(Login.value(2).toString() != senha)
    {
        QMessageBox::warning(this, tr("Chat"),
                             tr("Senha Incorreta.\n\n"
                             "Você digitou uma senha incorreta!"),
                             QMessageBox::Ok);
        return;

    }

    Form::close();
    MainWindow* window = new MainWindow();
    window->show();
    window->LoadContatos();

}

void Form::on_pushButton_2_pressed()
{
    Form::close();
    Registro* window = new Registro();
    window->show();
}
