#ifndef BASKET_H
#define BASKET_H

#include <QList>
#include <QDialog>
#include <QTableWidgetItem>


namespace Ui {
class Basket;
}

class Basket : public QDialog
{
    Q_OBJECT

public slots:
    void basket_set_SLOT(QList<QString> &, int);
    void set_balance(int balance);


public:
    explicit Basket(QWidget *parent = 0);
    ~Basket();
    QList<QString> positions;
    void set_tableView();
signals:
    void money_transfer(int sum);

private slots:
    void on_exit_button_clicked();
    void data_recieved();
    void on_pushButton_clicked();

private:
    Ui::Basket *ui;
    int lines = 0;
    int balance = 0;
    int sum = 0;
};

#endif // BASKET_H
