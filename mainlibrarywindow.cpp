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
    ui->lineUserName2->setText("");
    ui->lineUserType2->setText("");
    ui->lineUserID2->setText("");


    //initialize the table view
    QSqlQuery query;
    QSqlQueryModel * model = new QSqlQueryModel();
    query.prepare("SELECT * FROM issued");
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
    QSqlQuery query,iss; //initialize the query
    QSqlQueryModel * model = new QSqlQueryModel();
    QString ID = ui->lineUserID2->text();
    QDate due;
    query.prepare("SELECT * FROM BOOKS WHERE BookID='"+bookID+"' ");
    if (query.exec()){
        while (query.next()){ //This sets the text to the corresponding query
            ui->lineBookName2->setText(query.value(1).toString());
            ui->lineAuthor2->setText(query.value(3).toString());
            ui->lineCategory2->setText(query.value(2).toString());
            ui->linePublisher2->setText(query.value(4).toString());
            ui->lineEdition2->setText(query.value(5).toString());
            ui->linePubYear2->setText(query.value(6).toString());

        }
        iss.exec("SELECT * FROM issued WHERE UserID='"+ID+"' and BookID='"+bookID+"' ");
        while (iss.next()){
        QString dueString = iss.value("DateDue").toString();
        due = QDate::fromString(dueString, "MM/dd/yyyy");
        qint64 dateDiff = due.daysTo(today);
        if (dateDiff > 0){
            ui->lineLatePenalty->setText(lpenalty.setNum(latePenalty));
        }
        else{
            ui->lineLatePenalty->setText("0");
        }
        ui->dateReturn->setDate(due);
        model->setQuery(iss);
        ui->tableReturn->setModel(model);
        }

    }
    else{
        qDebug() << "Database Failed";
    }
}

void MainLibraryWindow::on_lineUserID2_textChanged(const QString &arg1)
{
    QString ID = arg1;
    QSqlQuery query,iss; //initialize the query
    QSqlQueryModel * model = new QSqlQueryModel;
    QString bookID = ui->lineBookID2->text();
    QDate due;
    QString dueString;
    query.prepare("SELECT * FROM issued WHERE UserID='"+ID+"' ");
    if (query.exec()){

        while (query.next()){ //This sets the text to the corresponding query

            ui->lineUserName2->setText(query.value(3).toString());
            ui->lineUserType2->setText(query.value(4).toString());
            iss.exec("SELECT * FROM issued WHERE UserID='"+ID+"' and BookID='"+bookID+"' ");

            while (iss.next()){
            dueString = iss.value(6).toString();
            due = QDate::fromString(dueString, "MM/dd/yyyy");
            qint64 dateDiff = due.daysTo(today);
            if (dateDiff > 0){
                ui->lineLatePenalty->setText(lpenalty.setNum(latePenalty));
            }
            else{
                ui->lineLatePenalty->setText("0");
            }
            ui->dateReturn->setDate(due);
            model->setQuery(iss);
            ui->tableReturn->setModel(model);
            }

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
    dpenalty.setNum(damagePenalty);
    if (checked == true){
        ui->lineDamagePenalty->setText(dpenalty);
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
    QSqlQuery query,quant,book; //initialize the variables
    QString bookID,bookName,userID,userName,category,dateIss,dateDue,qry,bk,quantity;

    int qnty;
    bookID = ui->lineBookID->text();
    bookName = ui->lineBookName->text();
    userID = ui->lineUserID->text();
    userName = ui->lineUserName->text();
    category = ui->lineUserType->text();
    dateIss = ui->dateIssued->text();
    dateDue = ui->dateDue->text();


    quant.exec("select Quantity from books where BookID='"+bookID+"'"); //get the quantity of books left
    while (quant.next()){
        QSqlRecord record = quant.record();
        quantity = record.value("Quantity").toString();
        qnty = quantity.toInt();


        if (qnty == 1){
            QMessageBox::about(this, "Cannot Issue Book.", "This is the last copy.");
        }
        else if (qnty > 1){
            qry = "insert into issued (BookID,BookName,UserID,UserName,UserType,dateIssued,dateDue) values ('"+bookID+"', '"+bookName+"', '"+userID+"', '"+userName+"', '"+category+"', '"+dateIss+"', '"+dateDue+"')";
            bk = "update books set Quantity='"+quantity+"' where BookID='"+bookID+"' ";
            qnty = qnty - 1;
            quantity = QString::number(qnty);

            //execute the query
            query.prepare(qry);
            query.exec();
            book.exec("update books set Quantity='"+quantity+"' where BookID='"+bookID+"'");

            if (qnty == 1){
                book.exec("update books set Status='Not Available' where BookID='"+bookID+"'");
            }
            else{
                book.exec("update books set Status='Available' where BookID='"+bookID+"'");
            }

            QMessageBox::about(this, "Book Issued", "Book has been issued successfully.");

            //show Message then clear the page
            ui->statusbar->showMessage("Book Issued", 3000);
            loadIssuePage();

        }
    }




}





void MainLibraryWindow::on_returnButton_clicked()
{
    QSqlQuery query,del,book,upd;
    QString bookID,userID,transNum,quantity,late,damage,pen,bookName;
    int totalPenalty, qnty;
    bookID = ui->lineBookID2->text();
    userID = ui->lineUserID2->text();
    late = ui->lineLatePenalty->text();
    damage = ui->lineDamagePenalty->text();
    totalPenalty = late.toInt() + damage.toInt();
    pen.setNum(totalPenalty);

    query.prepare("select * from issued where BookID='"+bookID+"' and UserID='"+userID+"'");
    if (query.exec()){
        int count = 0;
        while (query.next()){
            count ++;
            transNum = query.value(7).toString();
            }
        if (count == 0){
            QMessageBox::about(this, "Error", "No matching issued book.");
        }
        else if (count == 1){
            book.exec("select * from books where BookID='"+bookID+"'");
            while (book.next()){
                QSqlRecord record  = book.record();
                quantity = record.value("Quantity").toString();
                qnty = quantity.toInt();
                qnty++;
                quantity = QString::number(qnty);
                bookName = record.value("BookName").toString();
                if (ui->checkBox->checkState() == false){
                    QMessageBox::about(this, "Penalties", "Total Penalties: '"+pen+"'");
                    del.exec("Delete from issued where TransactionNum='"+transNum+"'");
                    QMessageBox::about(this, "Book Returned", "Book has been returned successfully.");
                    upd.exec("update books set Status='Available', Quantity='"+quantity+"' where BookID='"+bookID+"'");

                    //show Message then clear the page
                    ui->statusbar->showMessage("Book Returned", 3000);
                    loadReturnPage();
                }
                else {
                    QMessageBox::about(this, "Penalties", "Total Penalties: '"+pen+"'");
                    del.exec("Delete from issued where TransactionNum='"+transNum+"'");
                    QMessageBox::about(this, "Book Returned", "Book has been added to Damaged Books.");
                    upd.exec("insert into damagedBooks (BookID,BookName) values ('"+bookID+"', '"+bookName+"')");

                    //show Message then clear the page
                    ui->statusbar->showMessage("Book added to Damaged books", 3000);
                    loadReturnPage();
                }

            }

        }

    }

}
