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

private:
    Ui::MainWindow *ui;
    bool countBrackets(QString data);
    QStringList findVariables(QString data);

    QStringList findOperatons(QString str);
    void buildTable(QStringList variables, QString lineEdit);
};

#endif // MAINWINDOW_H
