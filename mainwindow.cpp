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
    else if (action == '+'){
        if(x!=y){
            return 1;
        }else return 0;
    }
    else if (action == '#'){
        if (x == 0 && y == 0)
            return 1;
        else
            return 0;
    }
    else if (action == '@'){
        if(x==0&&y==1){
            return 0;
        }else return 1;
    }
    else if(action == '='){
        if(x==y){
            return 1;
        }else return 0;
    }
    else if(action == '!'){
        return !x;
    }
}


void MainWindow::buildTable(QStringList variables)
{
    QStringList data = ui->lineEdit->text().split(QRegularExpression("\\W+"));
//    data.removeAll("");
//    QStringList operations = getOrder();

//    operations.removeAll("");
    variables.removeAll("");

    QStringList headers = variables + getOrder();


    ui->tableWidget->setColumnCount(headers.length());
    ui->tableWidget->setRowCount((int)pow(2,variables.length()));


    fillVariables((int)pow(2,variables.length()),0,2,variables.length());

    ui->tableWidget->setHorizontalHeaderLabels(headers);

    for  (int i = variables.length(); i < headers.length(); i++)
    {
        for (int j = 0; j < (int)pow(2,variables.length()); j++)
        {
            QTableWidgetItem *item;
            QString header = headers[i];
             if (headers[i][0] == "!")
             {

                 int columnb = -1;
                 for (int k = 0; k < i;k++)
                 {
                     if (header.contains(headers[k]))
                     {
                         columnb = k;
                     }
                 }

                 header.remove(headers[columnb]);



                 item = new QTableWidgetItem(QString::number(calculate(ui->tableWidget->item(j,columnb)->text().toInt(),1,"!")));

                 if (header != "!")
                 {
                     header = headers[i];
                     int columnb = -1;
                     int columna = -1;

                     for (int k = 0; k < i;k++)
                     {
                         if (header.contains(headers[k]))
                         {
                             columnb = k;
                         }
                     }

                     header.remove(headers[columnb]);

                     for (int k = 0; k < i;k++)
                     {
                         if (header.contains(headers[k]))
                         {
                             columna = k;
                         }
                     }

                     header.remove(headers[columna]);

                     item = new QTableWidgetItem(QString::number(calculate(ui->tableWidget->item(j,columna)->text().toInt(),ui->tableWidget->item(j,columnb)->text().toInt(),header)));
                 }
             }
             else
             {
                 int columnb = -1;
                 int columna = -1;
                 for (int k = 0; k < i;k++)
                 {
                     if (header.contains(headers[k]))
                     {
                         columnb = k;
                     }
                 }

                 header.remove(headers[columnb]);

                 for (int k = 0; k < i;k++)
                 {
                     if (header.contains(headers[k]))
                     {
                         columna = k;
                     }
                 }

                 header.remove(headers[columna]);

                 item = new QTableWidgetItem(QString::number(calculate(ui->tableWidget->item(j,columna)->text().toInt(),ui->tableWidget->item(j,columnb)->text().toInt(),header)));
             }
             ui->tableWidget->setItem(j,i,item);
        }
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
    QStringList variables = ui->lineEdit->text().split(QRegularExpression("\\W+"));
    QStringList operations = ui->lineEdit->text().split(QRegularExpression("\\w{0,1}"));
    operations.removeAll("");
    variables.removeAll("");

    QStringList order;
    std::stack <QString> queue;

    int currentOperation = 0;
    int currentVariable = 0;

    bool operationsFirst = false;

    QStringList decomposed;
    if (operations[0] == "!" || operations[0] == "(")
        operationsFirst = true;
    else
        operationsFirst = false;

    for (int i = 0; i < operations.length() + variables.length();i++)
    {
        if (currentOperation < operations.length() && (operations[currentOperation] == "(" || operations[currentOperation] == "!"))
        {
            if (operationsFirst)
                operationsFirst = !operationsFirst;
            decomposed.append(operations[currentOperation]);
            currentOperation++;
        }
        else if (currentOperation < operations.length() && operationsFirst)
        {
            if (operations[currentOperation] != ")")
                operationsFirst = !operationsFirst;
            decomposed.append(operations[currentOperation]);
            currentOperation++;
        }
        else if(currentVariable < variables.length() && !operationsFirst)
        {
            decomposed.append(variables[currentVariable]);
            currentVariable++;
            operationsFirst = !operationsFirst;
        }

    }

    currentVariable = 0;
    currentOperation = 0;

    // ОБЕРНЕНА ПОЛЬСКА НОТАЦІЯ

    for (int i = 0; i < decomposed.length();i++)
    {
        if (decomposed[i] == "(" || decomposed[i] == "!")
            queue.push(decomposed[i]);
        else if (decomposed[i] == ")")
        {
            while(queue.top() != "(")
            {
                order.append(queue.top());
                queue.pop();
            }
            queue.pop();
        }
        else if (variables.indexOf(decomposed[i]) != -1)
            order.append(decomposed[i]);
        else
        {
            if (queue.empty())
                queue.push(decomposed[i]);
            else if (moveToOutput(queue.top(),decomposed[i]))
            {
                order.append(queue.top());
                queue.pop();
                queue.push(decomposed[i]);
            }
            else
                queue.push(decomposed[i]);
        }
    }

    while (!queue.empty())
    {
        order.append(queue.top());
        queue.pop();
    }

    std::stack<QString> result;
    QStringList headers;

    for (int i = 0; i < order.length();i++)
    {
        if (variables.indexOf(order[i]) != -1)
        {
            result.push(order[i]);
        }
        else
        {
            QString a = result.top();
            result.pop();
            if (order[i] == "!")
            {
                result.push(order[i] + a);
            }
            else
            {
                QString b = result.top();
                result.pop();
                result.push(a + order[i] + b);
            }
            headers.append(result.top());
        }
    }

    return headers;
}


bool MainWindow::moveToOutput(QString stack, QString current)
{
    if (stack == "(")
        return false;
    if (current == "*")
        return false;
    if (stack == "&" && current == "*")
        return false;
    if (stack == "@" && (current == "*" || current == "&"))
        return false;
    if (stack == "=" && (current == "*" || current == "&" || current == "@"))
        return false;
    else
        return true;
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
