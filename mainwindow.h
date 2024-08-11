#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "catalog.h"
#include "basket.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    catalog *catal;
    Basket *basket;

signals:
    void rotate_balance(int balance);
    void give_back_sel_pos_keeper(QList<int>selected_pos_keeper);

private slots:
    void on_exit_button_clicked();
    void on_catalog_button_clicked();
    void on_basket_button_clicked();
    void on_deposit_line_returnPressed();
    void money_transfer(int sum);

private:
    Ui::MainWindow *ui;
    int balance = 0;
    int sum = 0;
    QList <int> selected_pos_keeper;
};

#endif // MAINWINDOW_H
