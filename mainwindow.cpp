#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("www.ElectronicBuy.ru");
    basket = new Basket;
    catal = new catalog;
    connect(catal, SIGNAL(basket_set_SIGNAL(QList <QString>&,int)), basket, SLOT(basket_set_SLOT(QList <QString>&,int)));
    ui->deposit_line->setPlaceholderText("Deposit");
    connect(this, SIGNAL(rotate_balance(int)), basket, SLOT(set_balance(int)));
    connect(basket, SIGNAL(money_transfer(int)), this, SLOT(money_transfer(int)));
    connect(this, SIGNAL(give_back_sel_pos_keeper(QList<int>)), catal, SLOT(set_selected_pos_keeper_after_buying(QList<int>)));

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
    emit rotate_balance(balance);
    basket->show();
}

void MainWindow::on_deposit_line_returnPressed()
{
    if(ui->deposit_line->text().toInt() > 0){
    balance = ui->deposit_line->text().toInt();
    int tempBalance = ui->balance_shower->text().toInt();
    balance += tempBalance;
    ui->balance_shower->setText(QString::number(balance));
    QMessageBox *mes = new QMessageBox;
    mes->setText("Thank you for choosing our store! "
                 "After placing an order in the basket, our manager will contact "
                 "us and tell us more about payment");
    mes->exec();
    }
}

void MainWindow::money_transfer(int sum)
{
    this->sum = sum;
    if(sum > 0){
        balance = ui->balance_shower->text().toInt();
        balance -= sum;
        ui->balance_shower->setText(QString::number(balance));
    }
    selected_pos_keeper = catal->get_selected_pos_keeper();
    emit give_back_sel_pos_keeper(selected_pos_keeper);
}
