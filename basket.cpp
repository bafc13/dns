#include "basket.h"
#include "ui_basket.h"
#include <QMessageBox>
#include <QDebug>

Basket::Basket(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Basket)
{
    ui->setupUi(this);
    setWindowTitle("Basket");

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
    ui->exit_button->setStyleSheet("border-radius: 20px; opacity: 0.5;");
}

Basket::~Basket()
{
    delete ui;
}

void Basket::basket_set_SLOT(QList <QString> &pos, int line_count)
{
    lines = line_count;
    positions.clear();

    for(int i = 0; i < pos.length(); i++){
        positions.append(pos.at(i));
    }
    data_recieved();
}

void Basket::set_balance(int balance)
{
    this->balance = balance;
}

void Basket::set_tableView()
{
    ui->tableWidget->setRowCount(lines);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Name" << "Price(rub)" << "Enabled");

    int k = 0;
    for(int i = 0; i < lines; i++){
        for(int j = 0; j < 2; j++){
            QTableWidgetItem *widg = new QTableWidgetItem(positions.at(i + j + k));
            ui->tableWidget->setItem(i,j,widg);
        } k++;
    }
}

void Basket::on_exit_button_clicked()
{
    close();
}

void Basket::data_recieved()
{
    set_tableView();
}

void Basket::on_pushButton_clicked()
{
    sum = 0;
    for(int i = 1; i < positions.length(); i += 2){
        sum += positions.at(i).toInt();
    }
    if(sum > balance){
        QMessageBox *mes = new QMessageBox;
        mes->setText("Not enough funds! Top up your balance");
        mes->exec();
        return;
    } else if (sum != 0){
        QMessageBox *mes = new QMessageBox;
        mes->setText("Order is processed! Wait, our manager will contact you soon!");
        mes->exec();
        emit money_transfer(sum);
        positions.clear();
        close();
    }
}

