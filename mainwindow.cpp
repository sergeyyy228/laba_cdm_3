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
            fillVariables(variables);
            buildTable(variables);
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

    for (int i = 0; i < operations.length();i++)
    {
        if (i!= 0)
            headers.append(headers[headers.length()-1] + data[i]+operations[i]+data[i+1]);
        else
            headers.append(data[i]+operations[i]+data[i+1]);
    }
//    headers.append("f");

    ui->tableWidget->setHorizontalHeaderLabels(headers);

    for (int i = variables.length(); i < headers.length(); i++)
    {
        for (int j = 0; j < (int)pow(2,variables.length());j++)
        {
            QTableWidgetItem * item;
            if (i == variables.length())
            {
                        int a = variables.indexOf(data[0]);
                int b = variables.indexOf(data[0]);
                
                item = new QTableWidgetItem(QString::number(calculate(ui->tableWidget->item(j,a)->text().toInt(), ui->tableWidget->item(j,b)->text().toInt(), operations[i-variables.length()])));
            }
            else
            {
                item = new QTableWidgetItem(QString::number(calculate(ui->tableWidget->item(j,variables.indexOf(data[0]))->text().toInt(), ui->tableWidget->item(j,i-1)->text().toInt(), operations[i-variables.length()])));
            }

            ui->tableWidget->setItem(j,i,item);
        }
        data.pop_front();
    }
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


void MainWindow::fillVariables(QStringList variables)
{
    int rows = (int)pow(2,variables.length());
    QStringList operations = getOrder();

    ui->tableWidget->setColumnCount(variables.length() + operations.length());
    ui->tableWidget->setRowCount((int)pow(2,variables.length()));

    for (int i = 0; i < rows;i++)
    {
        if (i < rows/2)
        {
            QTableWidgetItem * item = new QTableWidgetItem(QString::number(0));

            ui->tableWidget->setItem(i, 0, item);
        }
        else
        {
            QTableWidgetItem * item = new QTableWidgetItem(QString::number(1));

            ui->tableWidget->setItem(i, 0, item);
        }
    }

    if (variables.length() >= 2)
    {
        int period;

        if (variables.length() == 2)
            period = 1;
        if (variables.length() == 3)
            period = 2;
        if (variables.length() == 4)
            period = 4;

        for (int i = 0; i < rows; i++)
        {
//            if (i )
        }
    }
}


QStringList MainWindow::getOrder()
{
    QStringList order;
    if (ui->lineEdit->text().indexOf('(') == -1)
        order = ui->lineEdit->text().split(QRegularExpression("\\w+"));
    else
    {
//        QString text = ui->lineEdit->text();
//        do
//        {

//        }
//        while(text.indexOf('(') != -1);
    }
    return order;
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+'+');
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+'&');
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
