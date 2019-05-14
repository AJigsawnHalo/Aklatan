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
    ui->lineBookID->setText("");
    ui->lineBookName->setText("");
    ui->lineAuthor->setText("");
    ui->lineCategory->setText("");
    ui->linePublisher->setText("");
    ui->lineEdition->setText("");
    ui->linePubYear->setText("");
}

void MainLibraryWindow::on_issueHomeButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainLibraryWindow::on_actionIssue_Book_triggered() //clears the Page
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->lineBookID->setText("");
    ui->lineBookName->setText("");
    ui->lineAuthor->setText("");
    ui->lineCategory->setText("");
    ui->linePublisher->setText("");
    ui->lineEdition->setText("");
    ui->linePubYear->setText("");
}

/*void MainLibraryWindow::on_actionAdd_Book_triggered()
{

}*/

//Return Books Section
void MainLibraryWindow::on_returnHomeButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainLibraryWindow::on_homeReturnButton_clicked() //clears the Page
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->lineBookID2->setText("");
    ui->lineBookName2->setText("");
    ui->lineAuthor2->setText("");
    ui->lineCategory2->setText("");
    ui->linePublisher2->setText("");
    ui->lineEdition2->setText("");
    ui->linePubYear2->setText("");
}

void MainLibraryWindow::on_actionReturn_Book_triggered() //clears the Page
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->lineBookID2->setText("");
    ui->lineBookName2->setText("");
    ui->lineAuthor2->setText("");
    ui->lineCategory2->setText("");
    ui->linePublisher2->setText("");
    ui->lineEdition2->setText("");
    ui->linePubYear2->setText("");
}

void MainLibraryWindow::on_lineBookID_textChanged(const QString &arg1) //Queries the database for the book using the book ID
{
    dbManager db;
    QString bookID = arg1;
    QSqlQuery query; //initialize the query
    query.prepare("SELECT * FROM BOOKS WHERE ID='"+bookID+"' ");
    if (query.exec()){
        while (query.next()){ //This sets the text to the corresponding query
            ui->lineBookName->setText(query.value(1).toString());
            ui->lineAuthor->setText(query.value(3).toString());
            ui->lineCategory->setText(query.value(2).toString());
            ui->linePublisher->setText(query.value(4).toString());
            ui->lineEdition->setText(query.value(5).toString());
            ui->linePubYear->setText(query.value(6).toString());

        }

    }
    else{
        qDebug() << "Database Failed";
    }

}

void MainLibraryWindow::on_lineBookID2_textChanged(const QString &arg1) //Queries the database for the book using the book ID
{
    dbManager db;
    QString bookID = arg1;
    QSqlQuery query; //initialize the query
    query.prepare("SELECT * FROM BOOKS WHERE ID='"+bookID+"' ");
    if (query.exec()){
        while (query.next()){ //This sets the text to the corresponding query
            ui->lineBookName2->setText(query.value(1).toString());
            ui->lineAuthor2->setText(query.value(3).toString());
            ui->lineCategory2->setText(query.value(2).toString());
            ui->linePublisher2->setText(query.value(4).toString());
            ui->lineEdition2->setText(query.value(5).toString());
            ui->linePubYear2->setText(query.value(6).toString());

        }

    }
    else{
        qDebug() << "Database Failed";
    }
}

void MainLibraryWindow::on_refreshButton_2_clicked() //clears the Page
{
    ui->lineBookID2->setText("");
    ui->lineBookName2->setText("");
    ui->lineAuthor2->setText("");
    ui->lineCategory2->setText("");
    ui->linePublisher2->setText("");
    ui->lineEdition2->setText("");
    ui->linePubYear2->setText("");
}

void MainLibraryWindow::on_refreshButton_clicked() //clears the Page
{
    ui->lineBookID->setText("");
    ui->lineBookName->setText("");
    ui->lineAuthor->setText("");
    ui->lineCategory->setText("");
    ui->linePublisher->setText("");
    ui->lineEdition->setText("");
    ui->linePubYear->setText("");
}
