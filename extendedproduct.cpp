#include "extendedproduct.h"
#include "ui_extendedproduct.h"
#include <QMessageBox>


extendedProduct::extendedProduct(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::extendedProduct)
{
    ui->setupUi(this);
}
extendedProduct::extendedProduct(QString* values, QByteArray byteArray, QSqlQuery varinat, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::extendedProduct) {
        ui->setupUi(this);
        this->variant = variant;
        this->values = values;
        this->byteArray = byteArray;
        ui->lineEditType->setText(values[0]);
        ui->lineEditProducer->setText(values[1]);
        ui->lineEditModel->setText(values[2]);
        ui->textEditInfo->setText(values[4]);
        ui->lineEditEnable->setText(values[6]);
        ui->lineEditPrice->setText(values[3]);
        QPixmap pix = QPixmap();
        pix.loadFromData(byteArray);
        ui->photo->setPixmap(pix);
    }

extendedProduct::~extendedProduct()
{
    delete ui;
}


void extendedProduct::on_buttonBox_accepted()
{
    int var = values[6].toInt();
    if (var < ui->spinBoxCount->value()) {
        QMessageBox::critical(this, "Ошибка количества товара", "Вы не можете заказать больше товара чем есть у нас на складе", QMessageBox::Ok);
        return;
    }

    values[6] = ui->spinBoxCount->text();
    emit this->accept();
}

void extendedProduct::on_buttonBox_rejected()
{
    emit this->reject();
}
