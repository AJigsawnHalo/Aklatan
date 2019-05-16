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
    connect(ui->reportHomeButton, SIGNAL(pressed()), this, SLOT(loadHomePage()));

    //connections for the Issue Page
    connect(ui->homeIssueButton, SIGNAL(pressed()), this, SLOT(loadIssuePage()));
    connect(ui->refreshButton, SIGNAL(pressed()), this, SLOT(loadIssuePage()));
    connect(ui->actionIssue_Book, SIGNAL(triggered()), this, SLOT(loadIssuePage()));

    //connections for the Return Page
    connect(ui->homeReturnButton, SIGNAL(pressed()), this, SLOT(loadReturnPage()));
    connect(ui->refreshButton_2, SIGNAL(pressed()), this, SLOT(loadReturnPage()));
    connect(ui->actionReturn_Book, SIGNAL(triggered()), this, SLOT(loadReturnPage()));

    //connections for the Book Report Page
    connect(ui->homeReportButton, SIGNAL(pressed()), this, SLOT(passReportLoadAll()));
    connect(ui->actionAll_Books, SIGNAL(triggered()), this, SLOT(passReportLoadAll()));
    connect(ui->actionIssued_Books, SIGNAL(triggered()), this, SLOT(passReportLoadIss()));
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
    ui->lineUserID->setText("");
    ui->lineUserName->setText("");
    ui->lineUserType->setText("");

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

void MainLibraryWindow::passReportLoadAll()
{
    MainLibraryWindow::loadReportPage(0);
}

void MainLibraryWindow::passReportLoadIss()
{
    MainLibraryWindow::loadReportPage(1);
}

void MainLibraryWindow::loadReportPage(const int &arg)
{
    ui->stackedWidget->setCurrentIndex(3);
    //load appropriate tab
    ui->tabWidReport->setCurrentIndex(arg);

    //setup Queries
    QSqlQuery query,iss;
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQueryModel * modiss= new QSqlQueryModel();

    query.prepare("SELECT * FROM BOOKS");
    iss.prepare("SELECT * FROM issued");

    //exec query for all books
    query.exec();
    model->setQuery(query);

    ui->tableAll->setModel(model);
    ui->tableAll->repaint();

    //exec query for issued books
    iss.exec();
    modiss->setQuery(iss);

    ui->tableIssued->setModel(modiss);
    ui->tableIssued->repaint();

    //set specific column widths
    ui->tableAll->setColumnWidth(1, 200);
    ui->tableIssued->setColumnWidth(1, 200);


}

void MainLibraryWindow::on_lineBookID_textChanged(const QString &arg1) //Queries the database for the book using the book ID
{
    QString bookID = arg1;
    QSqlQuery query; //initialize the query
    QSqlQueryModel * model = new QSqlQueryModel();
    query.prepare("SELECT * FROM BOOKS WHERE BookID='"+bookID+"' ");
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

void MainLibraryWindow::on_lineUserID_textChanged(const QString &arg1)
{
    QString ID = arg1;
    QSqlQuery query; //initialize the query
    query.prepare("SELECT * FROM USERS WHERE UserID='"+ID+"' ");
    if (query.exec()){
        while (query.next()){ //This sets the text to the corresponding query
            ui->lineUserName->setText(query.value(1).toString());
            ui->lineUserType->setText(query.value(4).toString());

        }

    }
    else{
        qDebug() << "Database Failed";
    }
}

void MainLibraryWindow::on_lineBookID2_textChanged(const QString &arg1) //Queries the database for the book using the book ID
{

    QString bookID = arg1;
    QSqlQuery query; //initialize the query
    QSqlQueryModel * model = new QSqlQueryModel();
    query.prepare("SELECT * FROM BOOKS WHERE BookID='"+bookID+"' ");
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

void MainLibraryWindow::on_refreshButton_2_clicked()
{
    ui->statusbar->showMessage("Cleared", 3000);
}

void MainLibraryWindow::on_refreshButton_clicked()
{
    ui->statusbar->showMessage("Cleared", 3000);
}



void MainLibraryWindow::on_issueButton_clicked()
{
    QSqlQuery query,bk; //initialize the variables
    QString bookID,bookName,userID,userName,category,dateIss,dateDue,qry;
    bookID = ui->lineBookID->text();
    bookName = ui->lineBookName->text();
    userID = ui->lineUserID->text();
    userName = ui->lineUserName->text();
    category = ui->lineCategory->text();
    dateIss = ui->dateIssued->text();
    dateDue = ui->dateReturn->text();
    qry = "insert into issued (BookID,BookName,UserID,UserName,Category,dateIssued,dateDue) values ('"+bookID+"', '"+bookName+"', '"+userID+"', '"+userName+"', '"+category+"', '"+dateIss+"', '"+dateIss+"')";

    //execute the query
    query.prepare(qry);
    query.exec();

    //show Message then clear the page
    ui->statusbar->showMessage("Book Issued", 3000);
    loadIssuePage();
}
