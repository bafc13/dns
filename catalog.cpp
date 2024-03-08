#include "catalog.h"
#include "ui_catalog.h"
using namespace std;
#include <string.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <QDebug>


catalog::catalog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::catalog)
{
    ui->setupUi(this);
    setWindowTitle("Catalog");
    set_catalog_pos();
    set_tableView();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
    ui->exit_button->setStyleSheet("border-radius: 20px; opacity: 0.5;");
}

catalog::~catalog()
{
    delete ui;
}

void catalog::set_catalog_pos()
{
    catalog_file.open(name.toStdString());
    string each_line;
    while(std::getline(catalog_file,position_in_catalog)){
        each_line += " ";
        each_line += position_in_catalog;
        each_line += '\n';
        line_counter++;
    }

    QList <string> buff;
    string buf;
    stringstream test(each_line);
    while(getline(test, buf, '\n')){
        char *arr = new char[buf.length()+1];
        strcpy(arr, buf.c_str());
        buff.append(strtok(arr,";"));
        if(arr != ""){
            buff.append(strtok(NULL,";"));
        }
    }

    for(int i = 0; i < buff.length(); i++){
        pos.append(QString::fromStdString(buff[i]));
    }
    catalog_file.close();
}

void catalog::set_tableView()
{

    ui->tableWidget->setRowCount(line_counter);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Name" << "Price(rub)" << "Enabled" << "Category");
    set_category();
    set_checkBoxes();

    QList <QString> buff;
    for(int i =0; i< pos.length(); i++){
        buff.append(pos.at(i));
    }

    int k = 0;
    for(int i = 0; i < line_counter; i++){
        for(int j = 0; j < 2; j++){
            QTableWidgetItem *widg = new QTableWidgetItem(buff.at(i+j+k));
            ui->tableWidget->setItem(i,j,widg);
        } k++;
    }
}

void catalog::set_category()
{
    for(int i = 0; i < line_counter; i++){
        QTableWidgetItem *periph = new QTableWidgetItem("Peripherals");
//        QIcon icon(":/new/prefix1/mini_peripherals.jpg");
//        periph->setIcon(icon);
        ui->tableWidget->setItem(i,3,periph);
    }
}

void catalog::set_checkBoxes()
{
    for(int i = 0; i < line_counter; i++){
        QCheckBox *check = new QCheckBox(QString("take?"), this);
        check->setChecked(0);
        checks.append(check);
    }

    for(int i = 0; i < line_counter; i++){
        ui->tableWidget->setCellWidget(i,2,checks[i]);
    }
}

void catalog::on_exit_button_clicked()
{
    selected_pos_keeper.clear();
    for(int i = 0; i < line_counter; i++){
        if(checks[i]->isChecked() == 1){
            selected_pos_keeper.append(i);
        }
    }

    basket_pos.clear();

    int k = 0;
    for(int i = 0; i < line_counter; i++){
        if(selected_pos_keeper.indexOf(i) >= 0){
            basket_pos.append(pos.at(i + k));
            basket_pos.append(pos.at(i + k + 1));
        }k++;
    }

    emit basket_set_SIGNAL(basket_pos, selected_pos_keeper.length());
    close();
}
