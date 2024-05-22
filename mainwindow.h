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

private slots:
    void on_exit_button_clicked();
    void on_catalog_button_clicked();
    void on_basket_button_clicked();
    void on_deposit_line_returnPressed();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
