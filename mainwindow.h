#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTableWidgetItem>
#include <QTimer>
#include <vector>
#include "extendedproduct.h"
#include "basket.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:

    void on_mainTableOfProduct_itemDoubleClicked();
    void on_pushButtonScaner_clicked();

    void on_pushButtonPrinter_clicked();

    void on_pushButtonCopy_clicked();

    void on_pushButtonNotebook_clicked();

    void on_pushButtonShredder_clicked();

    void on_pushButtonTablet_clicked();

    void on_pushButtonClear_clicked();
    void on_pushButtonBasket_clicked();
    void timerUpdate();
    void addBayer(QString, QString, QString, QString, QString, QString);

    void on_lineEditSearch_returnPressed();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlQuery variant;
    void loadDataBase();
    void resezeVisualDB();
    extendedProduct *product;
    Basket *basket;
    QString* values;
    QByteArray byteArray;
    std::vector<QString> result;
    QTimer *timer;
    QString summ;
    QString number;
    QString Surname;
    QString Name;
    QString Patronomic;
    QString addres;

};

#endif // MAINWINDOW_H
