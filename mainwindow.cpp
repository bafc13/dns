#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("www.ElectronicBuy.ru");
    basket = new Basket;
    catal = new catalog;
    connect(catal, SIGNAL(basket_set_SIGNAL(QList <QString>&,int)), basket, SLOT(basket_set_SLOT(QList <QString>&,int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exit_button_clicked()
{
    close();
}

void MainWindow::on_catalog_button_clicked()
{
    catal->show();
}

void MainWindow::on_basket_button_clicked()
{
    basket->show();
}
