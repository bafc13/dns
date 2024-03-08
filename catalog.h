#ifndef CATALOG_H
#define CATALOG_H

#include <QDialog>
#include <fstream>
#include <QList>
#include <QIcon>
#include <QCheckBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <basket.h>



namespace Ui {
class catalog;
}

class catalog : public QDialog
{
    Q_OBJECT

public:
    explicit catalog(QWidget *parent = 0);
    ~catalog();
    void set_catalog_pos();
    void set_tableView();
    void set_category();
    void set_checkBoxes();
    QList <QString> pos;
    int line_counter = 0;
    QList <QString> basket_pos;

private slots:
    void on_exit_button_clicked();

signals:
    void basket_set_SIGNAL(QList <QString>&, int);

private:
    Ui::catalog *ui;
    const QString name = "catalog.txt";
    std::fstream catalog_file;
    std::string position_in_catalog;
    QList <QCheckBox*> checks;
    QList <int> selected_pos_keeper;
};

#endif // CATALOG_H
