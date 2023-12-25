#include "basket.h"
#include "ui_basket.h"

Basket::Basket(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Basket)
{
    ui->setupUi(this);
}
Basket::Basket(std::vector<QString> result, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Basket)
{
    ui->setupUi(this);
    int i = 0;
    ui -> tableWidgetBasket->setRowCount(0);
    ui->tableWidgetBasket->insertRow(ui->tableWidgetBasket->rowCount());
    bool flag = true;
    int count = 0;
    int summ = 0;
    while(flag) {
        if (count == 6) {
            count = 0;

            ui->tableWidgetBasket->insertRow(ui->tableWidgetBasket->rowCount());
        }
        ui->tableWidgetBasket->setItem(ui->tableWidgetBasket->rowCount()-1, i % 6, new QTableWidgetItem(result[i]));
        count++;
        if(i % 6 == 5) summ += result[i].toInt();
        i++;
        if( result.size() <= i) flag = false;
    }
    ui->labelSumm->setText(QString::number(summ));

}
Basket::~Basket()
{
    delete ui;
}


void Basket::on_buttonBox_accepted()
{
    bool flag;
    QString summ = ui->labelSumm->text();
    QString number = ui->lineEditNumber->text();
    number.toLongLong(&flag);
    if (!flag){
        QMessageBox::critical(this, "Ошибка телефона", "Телефон может содержать только цифры от 0 до 9", QMessageBox::Ok);
        return;
    }
    if (number.length() > 11){
        QMessageBox::critical(this, "Ошибка телефона", "Должно быть не более 11 цифр", QMessageBox::Ok);
        return;
    }
    QString Surname = ui->lineEditSur->text();
    for (int j = 0; j < Surname.length(); ++j){
        if (!Surname[j].isLetter()){
            QMessageBox::critical(this, "Ошибка строк", "В имени, фамилии или же отчестве могут быть только буквы", QMessageBox::Ok);
            return;
        }
    }
    QString Name = ui->lineEditName->text();
    for (int j = 0; j < Name.length(); ++j){
        if (!Name[j].isLetter()){
            QMessageBox::critical(this, "Ошибка строк", "В имени, фамилии или же отчестве могут быть только буквы", QMessageBox::Ok);
            return;
        }
    }
    QString Patronomic = ui->lineEditPat->text();
    for (int j = 0; j < Patronomic.length(); ++j){
        if (!Patronomic[j].isLetter()){
            QMessageBox::critical(this, "Ошибка строк", "В имени, фамилии или же отчестве могут быть только буквы", QMessageBox::Ok);
            return;
        }
    }
    QString addres = ui->lineEditAddres->text();
    if(addres == "") {
        QMessageBox::critical(this, "Ошибка адреса", "Адрес не может быть пустым", QMessageBox::Ok);
        return;
    }


    emit sendToWidget(summ, number, Surname, Name, Patronomic, addres);
    close();
    //emit this->accept();
}

void Basket::on_buttonBox_rejected()
{
    emit this->reject();
}
