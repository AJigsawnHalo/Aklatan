#include "mainlibrarywindow.h"
#include "ui_mainlibrarywindow.h"
#include "dbmanager.h"
#include "loginform.h"

MainLibraryWindow::MainLibraryWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainLibraryWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Aklatan");
    ui->stackedWidget->setCurrentIndex(0); //set stacked widget to home page

}

MainLibraryWindow::~MainLibraryWindow()
{
    delete ui;
}

//Issue Books Section
void MainLibraryWindow::on_homeIssueButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainLibraryWindow::on_issueHomeButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainLibraryWindow::on_actionIssue_Book_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}

/*void MainLibraryWindow::on_actionAdd_Book_triggered()
{

}*/

//Return Books Section
void MainLibraryWindow::on_returnHomeButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainLibraryWindow::on_homeReturnButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainLibraryWindow::on_actionReturn_Book_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}
