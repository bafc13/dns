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
    int delim_counter = 0;
    while(getline(test, buf, '\n')){
        while(delim_counter < 1){
            char *arr = new char[buf.length()+1];
            strcpy(arr, buf.c_str());
            string bufStr = strtok(arr,";");
            buff.append(bufStr);
            ++delim_counter;
            while(!bufStr.empty()){
                bufStr = strtok(NULL, ";");
                buff.append(bufStr);
                ++delim_counter;
                if(delim_counter == 4){
                    break;
                }
            }
        } delim_counter = 0;
    }

    for(int i = 0; i < buff.length(); i++){
        pos.append(QString::fromStdString(buff[i]));
    }
    catalog_file.close();
}

void catalog::set_tableView()
{
    ui->tableWidget->setRowCount(line_counter);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Name" << "Price(rub)"
                                               << "Enabled" << "Category" << "In stock");
    set_category();
    set_checkBoxes();
    set_stock();
    set_unabled();

    QList <QString> buff;
    for(int i = 0; i < pos.length(); i+=4){
        buff.append(pos.at(i));
        buff.append(pos.at(i + 1));
    }

    int k = 0;
    for(int i = 0; i < line_counter; i++){
        for(int j = 0; j < 2; j++){
            QTableWidgetItem *widg = new QTableWidgetItem(buff.at(i + j + k));
            ui->tableWidget->setItem(i,j,widg);
        } k++;
    }
}

void catalog::set_category()
{
    for(int i = 0; i < line_counter; ++i){
        QTableWidgetItem *periph = new QTableWidgetItem(pos.at(2 + 4 * i));
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

void catalog::set_stock()
{
    for(int i = 0; i < line_counter; ++i){
        QTableWidgetItem *periph = new QTableWidgetItem(pos.at(3 + 4 * i));
        ui->tableWidget->setItem(i,4,periph);
    }
}

void catalog::set_unabled()
{
    int digit;
    for(int i = 0; i < line_counter; ++i){
        digit = pos.at(3 + 4 * i).toInt();
        if(digit <= 0){
            checks.at(i)->setEnabled(0);
        }
    }
}

QList<int> catalog::get_selected_pos_keeper()
{
    return selected_pos_keeper;
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
    QList <QString> buff;
    for(int i = 0; i < pos.length(); i+=4){
        buff.append(pos.at(i));
        buff.append(pos.at(i + 1));
    }

    int k = 0;
    for(int i = 0; i < line_counter; i++){
        for(int j = 0; j < 2; j++){
            if(selected_pos_keeper.indexOf(i) >= 0){
                basket_pos.append(buff.at(i + j + k));
        }} k++;
    }

    emit basket_set_SIGNAL(basket_pos, selected_pos_keeper.length());
    close();
}

void catalog::set_selected_pos_keeper_after_buying(QList<int> sel_pos_keeper)
{
    for(int i = 0; i < selected_pos_keeper.length(); ++i){
        selected_pos_keeper[i] = sel_pos_keeper[i];
    }

    for(int i = 0; i < selected_pos_keeper.length(); ++i){
        int buf = pos.at(3 + 4 * selected_pos_keeper[i]).toInt();
        buf -= 1;
        pos[3 + 4 * selected_pos_keeper[i]] = QString::number(buf);
    }

    for(int i = 0; i < checks.length(); ++i){
        if(selected_pos_keeper.contains(i)){
            checks.at(i)->setChecked(0);
        }
    }
    set_unabled();

    set_stock();


}
