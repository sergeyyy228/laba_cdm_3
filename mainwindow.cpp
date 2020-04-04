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
