#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: rgb(227, 227, 222);");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if (!countBrackets(ui->lineEdit->text()))
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText("Number of openning and closing brackets isn't equal!");
        msgBox.exec();
    }else
    {
        QStringList variables = findVariables(ui->lineEdit->text());
        if (variables.length() > 4)
        {
            QMessageBox msgBox;
            msgBox.setText("Error");
            msgBox.setInformativeText("Too more variables.");
            msgBox.exec();
        }
        else
        {
            buildTable(variables, ui->lineEdit->text());
        }
    }
}


bool MainWindow::countBrackets(QString data)
{
    if (data.count("(") == data.count(")"))
        return true;
    else
        return false;
}


QStringList MainWindow::findVariables(QString str)
{
    QStringList list = str.split(QRegularExpression("\\W+"));
    list.removeDuplicates();
    list.sort();

    return list;
}


QStringList MainWindow::findOperatons(QString str)
{
    QStringList list = str.split(QRegularExpression("\([&|+]{1,})"));
    list.removeDuplicates();
    list.sort();

    return list;
}


void MainWindow::buildTable(QStringList variables, QString lineEdit)
{

    QStringList data = ui->lineEdit->text().split(QRegularExpression("\\W+"));
    QStringList operations = lineEdit.split(QRegularExpression("\\w+"));
    operations.removeAll("");

    QStringList headers;
    headers.append(variables);

    for (int i = 0; i < operations.length();i++)
    {
        if (i!= 0)
            headers.append(headers[headers.length()-1] + data[i]+operations[i]+data[i+1]);
        else
            headers.append(data[i]+operations[i]+data[i+1]);
    }
//    headers.append("f");
    ui->tableWidget->setColumnCount(variables.length() + operations.length());
    ui->tableWidget->setRowCount((int)pow(2,variables.length()));

    ui->tableWidget->setHorizontalHeaderLabels(headers);
//    ui->tableWidget->setVerticalHeaderLabels(inArr2);

//    for (int i = 0; i < all;i++)
//    {   // встановлюємо рядок і стовпець
//        int row = i / (inArr1.length());
//        int column = i % (inArr1.length());
//        // встановлюємо значення
//        QTableWidgetItem * item = new QTableWidgetItem(QString::number(compare(inArr1[column].toInt(),inArr2[row].toInt())));

//        ui->tableWidget->setItem(row, column, item);
//    }
    // змінюємо розміри таблиці
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->resizeColumnsToContents();
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+'+');
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+'&'+'&');
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+'*');
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+'!');
}

void MainWindow::on_pushButton_9_clicked()
{
     ui->lineEdit->setText(ui->lineEdit->text()+'@');
}

void MainWindow::on_pushButton_8_clicked()
{
     ui->lineEdit->setText(ui->lineEdit->text()+'=');
}

void MainWindow::on_pushButton_7_clicked()
{
     ui->lineEdit->setText(ui->lineEdit->text()+'#');
}

void MainWindow::on_pushButton_6_clicked()
{
     ui->lineEdit->setText(ui->lineEdit->text()+'|');
}

void MainWindow::on_pushButton_10_clicked()
{
     ui->lineEdit->setText(ui->lineEdit->text()+'(');
}

void MainWindow::on_pushButton_11_clicked()
{
     ui->lineEdit->setText(ui->lineEdit->text()+')');
}
