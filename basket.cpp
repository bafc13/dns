#include "basket.h"
#include "ui_basket.h"


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
