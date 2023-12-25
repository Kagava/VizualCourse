#ifndef EXTENDEDPRODUCT_H
#define EXTENDEDPRODUCT_H

#include <QDialog>
#include <QSqlQuery>
#include <QSpinBox>
#include "basket.h"

namespace Ui {
class extendedProduct;
}

class extendedProduct : public QDialog
{
    Q_OBJECT

public:
    explicit extendedProduct(QWidget *parent = nullptr);
    extendedProduct(QString* values, QByteArray byteArray, QSqlQuery varinat, QWidget *parent);
    ~extendedProduct();

private slots:



    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::extendedProduct *ui;
    Ui::Basket *uiB;
    QString* values;
    QImage photo;
    QByteArray byteArray;
    QString formatFile;
    QSqlQuery variant;
    Basket *basket;
};

#endif // EXTENDEDPRODUCT_H
