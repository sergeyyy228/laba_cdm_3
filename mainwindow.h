#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <math.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

private:
    Ui::MainWindow *ui;
    bool countBrackets(QString data);
    QStringList findVariables(QString data);

    int calculate(int x, int y, QString action);
    QStringList findOperatons(QString str);
    void buildTable(QStringList variables);


    QStringList getOrder();

    void fillVariables(QStringList variables);


    void fillVariables(int rows, int column, int multiplier, int variables);


};

#endif // MAINWINDOW_H
