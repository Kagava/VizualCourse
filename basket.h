#ifndef BASKET_H
#define BASKET_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
namespace Ui {
class Basket;
}

class Basket : public QDialog
{
    Q_OBJECT

public:
    explicit Basket(QWidget *parent = nullptr);
    Basket(std::vector<QString> result, QWidget *parent);
    ~Basket();

private slots:

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Basket *ui;
signals:
    void sendToWidget(QString summ, QString number, QString Surname, QString Name, QString Patronomic, QString addres);
};

#endif // BASKET_H
