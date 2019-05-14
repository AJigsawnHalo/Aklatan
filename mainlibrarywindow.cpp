#include "mainlibrarywindow.h"
#include "ui_mainlibrarywindow.h"
#include "dbmanager.h"
#include "loginform.h"
#include "globals.h"


MainLibraryWindow::MainLibraryWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainLibraryWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Aklatan");
    ui->stackedWidget->setCurrentIndex(0); //set stacked widget to home page

    //connections for the Home Page
    connect(ui->issueHomeButton, SIGNAL(pressed()), this, SLOT(loadHomePage()));
    connect(ui->returnHomeButton, SIGNAL(pressed()), this, SLOT(loadHomePage()));
    connect(ui->actionLibrary_Home, SIGNAL(triggered()), this, SLOT(loadHomePage()));

    //connections for the Issue Page
    connect(ui->homeIssueButton, SIGNAL(pressed()), this, SLOT(loadIssuePage()));
    connect(ui->refreshButton, SIGNAL(pressed()), this, SLOT(loadIssuePage()));
    connect(ui->actionIssue_Book, SIGNAL(triggered()), this, SLOT(loadIssuePage()));

    //connections for the Return Page
    connect(ui->homeReturnButton, SIGNAL(pressed()), this, SLOT(loadReturnPage()));
    connect(ui->refreshButton_2, SIGNAL(pressed()), this, SLOT(loadReturnPage()));
    connect(ui->actionReturn_Book, SIGNAL(triggered()), this, SLOT(loadReturnPage()));
}

MainLibraryWindow::~MainLibraryWindow()
{
    delete ui;
}
//Loading the Home Page
void MainLibraryWindow::loadHomePage(){
    ui->stackedWidget->setCurrentIndex(0);
}
//Loading the Issue Books Page
void MainLibraryWindow::loadIssuePage(){
    //loads the issue page
    ui->stackedWidget->setCurrentIndex(1);

    //initialize the line edits
    ui->lineBookID->setText("");
    ui->lineBookName->setText("");
    ui->lineAuthor->setText("");
    ui->lineCategory->setText("");
    ui->linePublisher->setText("");
    ui->lineEdition->setText("");
    ui->linePubYear->setText("");

    //initialize the table view
    QSqlQuery query;
    QSqlQueryModel * model = new QSqlQueryModel();
    query.prepare("SELECT * FROM BOOKS");
    query.exec();
    model->setQuery(query);
    ui->tableIssue->setModel(model);

    //initialize the date
    ui->dateIssued->setDate(today);
    ui->dateDue->setDate(dueDate);
}

//Loading the Return Books Page
void MainLibraryWindow::loadReturnPage(){
    //loads the return page
    ui->stackedWidget->setCurrentIndex(2);

    //initialize the line edits
    ui->lineBookID2->setText("");
    ui->lineBookName2->setText("");
    ui->lineAuthor2->setText("");
    ui->lineCategory2->setText("");
    ui->linePublisher2->setText("");
    ui->lineEdition2->setText("");
    ui->linePubYear2->setText("");

    //initialize the table view
    QSqlQuery query;
    QSqlQueryModel * model = new QSqlQueryModel();
    query.prepare("SELECT * FROM BOOKS");
    query.exec();
    model->setQuery(query);
    ui->tableReturn->setModel(model);

    //initialize the penalties
    ui->checkBox->setChecked(false);
    ui->lineLatePenalty->setText("0");
    ui->lineDamagePenalty->setText("0");

    //Temporary date initialization. Will be fixed when an issue and retrun function has been built.
    ui->dateReturn->setDate(dueDate);
}


void MainLibraryWindow::on_lineBookID_textChanged(const QString &arg1) //Queries the database for the book using the book ID
{
    dbManager db;
    QString bookID = arg1;
    QSqlQuery query; //initialize the query
    QSqlQueryModel * model = new QSqlQueryModel();
    query.prepare("SELECT * FROM BOOKS WHERE ID='"+bookID+"' ");
    if (query.exec()){
        while (query.next()){ //This sets the text to the corresponding query
            ui->lineBookName->setText(query.value(1).toString());
            ui->lineAuthor->setText(query.value(3).toString());
            ui->lineCategory->setText(query.value(2).toString());
            ui->linePublisher->setText(query.value(4).toString());
            ui->lineEdition->setText(query.value(5).toString());
            ui->linePubYear->setText(query.value(6).toString());
            model->setQuery(query);
            ui->tableIssue->setModel(model);
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
    QSqlQueryModel * model = new QSqlQueryModel();
    query.prepare("SELECT * FROM BOOKS WHERE ID='"+bookID+"' ");
    if (query.exec()){
        while (query.next()){ //This sets the text to the corresponding query
            ui->lineBookName2->setText(query.value(1).toString());
            ui->lineAuthor2->setText(query.value(3).toString());
            ui->lineCategory2->setText(query.value(2).toString());
            ui->linePublisher2->setText(query.value(4).toString());
            ui->lineEdition2->setText(query.value(5).toString());
            ui->linePubYear2->setText(query.value(6).toString());
            model->setQuery(query);
            ui->tableReturn->setModel(model);
        }

    }
    else{
        qDebug() << "Database Failed";
    }
}


void MainLibraryWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainLibraryWindow::on_pushButton_clicked()
{
    QApplication::quit();
}

void MainLibraryWindow::on_checkBox_toggled(bool checked)
{
    //retrieves the Damage Penalty value and shows it on the Returns page if applicable
    penalty.setNum(damagePenalty);
    if (checked == true){
        ui->lineDamagePenalty->setText(penalty);
    }
    else{
        ui->lineDamagePenalty->setText("0");
    }
}
