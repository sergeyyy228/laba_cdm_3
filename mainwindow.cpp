#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    try {
        QStringList variables = findVariables(ui->lineEdit->text());
        buildTable(variables);
    } catch (...) {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText("Something went wrong. Check the data you entered!");
        msgBox.exec();
    }
}


QStringList MainWindow::findVariables(QString str)
{
    QStringList list = str.split(QRegularExpression("\\W+"));
    list.removeDuplicates();

    return list;
}


QStringList MainWindow::findOperatons(QString str)
{
    QStringList list = str.split(QRegularExpression("\([&|+]{1,})"));
    list.removeDuplicates();
    list.sort();

    return list;
}


int MainWindow::calculate(int x, int y, QString action)
{
    if (action == '&')
    {
        if ( x == 1 && y == 1)
            return 1;
        else
            return 0;
    }
    else if(action == '|')
    {
        if (x == 1 && y == 1)
            return 0;
        else
            return 1;
    }
    else if (action == '*')
    {
        if (x == 0 && y == 0)
            return 0;
        else
            return 1;
    }
}


void MainWindow::buildTable(QStringList variables)
{
    QStringList data = ui->lineEdit->text().split(QRegularExpression("\\W+"));
    QStringList operations = getOrder();
    operations.removeAll("");

    QStringList headers;
    headers.append(variables);


    ui->tableWidget->setColumnCount(variables.length() + operations.length());
    ui->tableWidget->setRowCount((int)pow(2,variables.length()));


    fillVariables((int)pow(2,variables.length()),0,2,variables.length());

    for (int i = 0; i < operations.length();i++)
    {
        if (i!= 0)
            headers.append(headers[headers.length()-1] + operations[i]+data[i+1]);
        else
            headers.append(data[i]+operations[i]+data[i+1]);
    }

    ui->tableWidget->setHorizontalHeaderLabels(headers);

    for (int i = variables.length(); i < headers.length(); i++)
    {
        for (int j = 0; j < (int)pow(2,variables.length());j++)
        {
            QTableWidgetItem * item;
            if (i == variables.length())
            {
                int a = variables.indexOf(data[0]);
                int b = variables.indexOf(data[1]);
                
                item = new QTableWidgetItem(QString::number(calculate(ui->tableWidget->item(j,a)->text().toInt(), ui->tableWidget->item(j,b)->text().toInt(), operations[0])));
            }
            else
                item = new QTableWidgetItem(QString::number(calculate(ui->tableWidget->item(j,i-1)->text().toInt(), ui->tableWidget->item(j,variables.indexOf(data[0]))->text().toInt(), operations[0])));

            ui->tableWidget->setItem(j,i,item);
        }
        if (i == variables.length())
            data.pop_front();

        data.pop_front();
        operations.pop_front();
    }
    // змінюємо розміри таблиці
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->resizeColumnsToContents();
}


void MainWindow::fillVariables(int rows, int column, int multiplier, int variables)
{
    if (variables == column)
        return;

    bool isIt = false;
    for (int i = 1; i <= rows; i++)
    {
        QTableWidgetItem * item;
        if (!isIt)
            item = new QTableWidgetItem("0");
        else
            item = new QTableWidgetItem("1");
        if (i % (rows/(multiplier)) == 0)
            isIt = !isIt;

        ui->tableWidget->setItem(i-1, column, item);
    }

    fillVariables(rows,column+1,multiplier*2, variables);
}


QStringList MainWindow::getOrder()
{
    QStringList order = ui->lineEdit->text().split(QRegularExpression("\\w+"));

    return order;
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+'+');
    ui->lineEdit->setFocus();
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+'&');
    ui->lineEdit->setFocus();
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+'*');
    ui->lineEdit->setFocus();
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+'!');
    ui->lineEdit->setFocus();
}

void MainWindow::on_pushButton_9_clicked()
{
     ui->lineEdit->setText(ui->lineEdit->text()+'@');
     ui->lineEdit->setFocus();
}

void MainWindow::on_pushButton_8_clicked()
{
     ui->lineEdit->setText(ui->lineEdit->text()+'=');
     ui->lineEdit->setFocus();
}

void MainWindow::on_pushButton_7_clicked()
{
     ui->lineEdit->setText(ui->lineEdit->text()+'#');
     ui->lineEdit->setFocus();
}

void MainWindow::on_pushButton_6_clicked()
{
     ui->lineEdit->setText(ui->lineEdit->text()+'|');
     ui->lineEdit->setFocus();
}
