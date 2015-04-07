#ifndef REGISTRO_H
#define REGISTRO_H

#include <QWidget>

namespace Ui {
class Registro;
}

class Registro : public QWidget
{
    Q_OBJECT

public:
    explicit Registro(QWidget *parent = 0);
    ~Registro();

private slots:
    void on_pushButton_pressed();

private:
    Ui::Registro *ui;
};

#endif // REGISTRO_H
