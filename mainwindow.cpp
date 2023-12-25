#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE", "db");
    db.setDatabaseName("C:/Users/esspa/Desktop/VUZ/5sem/VPandPMM/Corse/Course/OrgTechnik.db");
    if(db.open()) {
        ui->statusBar->showMessage("Database open", 3000);
    }
    else {
        ui->statusBar->showMessage("Database not open", 3000);
    }
    resezeVisualDB();

    ui->mainTableOfProduct->setEditTriggers(QAbstractItemView::NoEditTriggers);
    variant = QSqlQuery(db);
    loadDataBase();
    ui->pushButtonBasket->setEnabled(false);
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
    connect(ui->leaveButton, SIGNAL(triggered()), qApp, SLOT(quit()));
    timer->start(60000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerUpdate() {
    loadDataBase();
}

void MainWindow::loadDataBase() {
    ui -> mainTableOfProduct->setRowCount(0);
    if (!variant.exec("SELECT ID, Type, Producer, Model, Price, Info, Picture, Count FROM dataBaseForShop")){
        ui->statusBar->showMessage("Database table 'DataBaseForShop' not open", 3000);
        return;
    }
    while (variant.next()) {
        ui->mainTableOfProduct->insertRow(ui->mainTableOfProduct->rowCount());
        for (int i = 0; i < 6; i++) ui->mainTableOfProduct->setItem(ui->mainTableOfProduct->rowCount()-1, i, new QTableWidgetItem(variant.value(i).toString()));
    }
}

void MainWindow::on_mainTableOfProduct_itemDoubleClicked()
{
    if (ui->mainTableOfProduct->selectedItems().isEmpty()) return;
    QString ID = ui->mainTableOfProduct->selectedItems()[0]->text();
    if (!variant.exec("SELECT * FROM DataBaseForShop WHERE ID = " +ID)){
        ui->statusBar->showMessage("Database table 'DataBaseForShop' not open", 3000);
        return;
    }
    else {
        ui->statusBar->showMessage("Database table 'DataBaseForShop' is open", 3000);
    }
    values = new QString[7];
    while(variant.next()){
        for (int i = 0; i < 6; i++) values[i] = variant.value(i+1).toString();
        values[6] = variant.value(7).toString();
        byteArray = variant.value(6).toByteArray();
    }
    product = new extendedProduct(values, byteArray, variant, this);
    if (product->exec() == QDialog::Accepted) {
        ui->pushButtonBasket->setEnabled(true);
        ui->statusBar->showMessage(values[6], 10000);
        for(int i = 0; i < 3; i++) {
            result.push_back(values[i]);
        }
        result.push_back(values[6]);
        result.push_back(values[3]);
        int t = values[6].toInt() * values[3].toInt();
       result.push_back(QString::number(t));

    }
}


void MainWindow::on_pushButtonScaner_clicked()
{
    resezeVisualDB();
    const QString data = "Сканер";
    QTableWidget *table = ui->mainTableOfProduct;;
    for(int i = 0; i < table->rowCount(); i++) {
        if (table->item(i, 1)->text() != data) {
            table->setRowHidden(i, true);
        }
        else {
           table->setRowHidden(i, false);
        }
    }

}

void MainWindow::on_pushButtonPrinter_clicked()
{
    resezeVisualDB();
    const QString data = "Принтер";
    QTableWidget *table = ui->mainTableOfProduct;;
    for(int i = 0; i < table->rowCount(); i++) {
        if (table->item(i, 1)->text() != data) {
            table->setRowHidden(i, true);
        }
        else {
           table->setRowHidden(i, false);
        }
    }
}

void MainWindow::on_pushButtonCopy_clicked()
{
    resezeVisualDB();
    const QString data = "Копир";
    QTableWidget *table = ui->mainTableOfProduct;;
    for(int i = 0; i < table->rowCount(); i++) {
        if (table->item(i, 1)->text() != data) {
            table->setRowHidden(i, true);
        }
        else {
           table->setRowHidden(i, false);
        }
    }
}

void MainWindow::on_pushButtonNotebook_clicked()
{
    resezeVisualDB();
    const QString data = "Ноутбук";
    QTableWidget *table = ui->mainTableOfProduct;;
    for(int i = 0; i < table->rowCount(); i++) {
        if (table->item(i, 1)->text() != data) {
            table->setRowHidden(i, true);
        }
        else {
           table->setRowHidden(i, false);
        }
    }
}

void MainWindow::on_pushButtonShredder_clicked()
{
    resezeVisualDB();
    const QString data = "Шреддер";
    QTableWidget *table = ui->mainTableOfProduct;;
    for(int i = 0; i < table->rowCount(); i++) {
        if (table->item(i, 1)->text() != data) {
            table->setRowHidden(i, true);
        }
        else {
           table->setRowHidden(i, false);
        }
    }
}

void MainWindow::on_pushButtonTablet_clicked()
{
    resezeVisualDB();
    const QString data = "Планшет";
    QTableWidget *table = ui->mainTableOfProduct;;
    for(int i = 0; i < table->rowCount(); i++) {
        if (table->item(i, 1)->text() != data) {
            table->setRowHidden(i, true);
        }
        else {
           table->setRowHidden(i, false);
        }
    }
}

void MainWindow::on_pushButtonClear_clicked()
{
    resezeVisualDB();
    QTableWidget *table = ui->mainTableOfProduct;;
    for(int i = 0; i < table->rowCount(); i++) {
            table->setRowHidden(i, false);
    }
}

void MainWindow::resezeVisualDB() {
    ui->mainTableOfProduct->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->mainTableOfProduct->setSelectionBehavior(QAbstractItemView::SelectRows);
}





void MainWindow::on_pushButtonBasket_clicked()
{
    basket = new Basket(result, this);

    basket->setWindowModality(Qt::ApplicationModal);
    connect(basket, SIGNAL(sendToWidget(QString, QString, QString, QString, QString, QString)),
            this, SLOT(addBayer(QString, QString, QString, QString, QString, QString)));
    if (basket->exec() == QDialog::Accepted) {

    }
}


void MainWindow::addBayer(QString summ, QString number, QString Surname, QString Name, QString Patronomic, QString addres) {
    variant.prepare( "INSERT INTO dataBaseOfPuarchase (totalCost, surnameClient, nameClient, pursCleint, addrtesDelivery, clientPhone) "
                   "VALUES (?,?,?,?,?,?)");

    variant.addBindValue(summ);
    variant.addBindValue(Surname);
    variant.addBindValue(Name);
    variant.addBindValue(Patronomic);
    variant.addBindValue(addres);
    variant.addBindValue(number);
    if(!variant.exec()){
        ui->statusBar->showMessage("Can't insert new order to database", 3000);
        return;
    }
    QMessageBox::information(this, "Статус заказа", "Ваш заказ принят и находится в статусе сборки", QMessageBox::Ok);
    result.clear();
    ui->pushButtonBasket->setEnabled(false);
}

void MainWindow::on_lineEditSearch_returnPressed()
{
    resezeVisualDB();
    const QString data = ui->lineEditSearch->text();
    QTableWidget *table = ui->mainTableOfProduct;

    for(int i = 0; i < table->rowCount(); i++) {
        for(int j = 0; j < 6; j++) {
            if (table->item(i, j)->text() != data) {
                table->setRowHidden(i, true);
            }
            else {
               table->setRowHidden(i, false);
               break;
            }
        }
    }
}

