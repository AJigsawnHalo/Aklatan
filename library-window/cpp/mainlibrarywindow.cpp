#include "library-window/headers/mainlibrarywindow.h"
#include "library-window/ui/ui_mainlibrarywindow.h"
#include "common/headers/dbmanager.h"
#include "library-window/headers/loginform.h"
#include "common/headers/globals.h"


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
    connect(ui->regHomeButton, SIGNAL(pressed()), this, SLOT(loadHomePage()));

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

    //connections for the Register Page
    connect(ui->homeAdd, SIGNAL(pressed()), this, SLOT(passRegisterBook()));
    connect(ui->actionAdd_Book, SIGNAL(triggered()), this, SLOT(passRegisterBook()));
    connect(ui->actionAdd_User, SIGNAL(triggered()), this, SLOT(passRegisterUser()));


}

MainLibraryWindow::~MainLibraryWindow()
{
    delete ui;
}

/*void MainLibraryWindow::loadStatus()
{
    QSqlQuery stat,dam,all;
    QString iss,dama,total;
    int rIss,rDam,rAll;

    stat.exec("select * from issued");
    stat.last();
    rIss = stat.at() + 1;
    iss = QString::number(rIss);
    ui->labelIssued->setText(iss + " Books Currently Issued");

    all.exec("select * from books");
    all.last();
    rAll = all.at() + 1;
    total = QString::number(rAll);
    ui->labelAll->setText("There are "+total+" books in the Library");

    dam.exec("select * from damagedBooks");
    dam.last();
    rDam = dam.at() + 1;
    dama = QString::number(rDam);
    ui->labelDamage->setText("There are " + dama + " Damaged Books");

}*/
//Loading the Home Page
void MainLibraryWindow::loadHomePage(){
    ui->stackedWidget->setCurrentIndex(0);
    loadStatus();
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

    //Temporary date initialization.
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

void MainLibraryWindow::passRegisterBook()
{
    MainLibraryWindow::loadRegisterPage(0);
}

void MainLibraryWindow::passRegisterUser()
{
    MainLibraryWindow::loadRegisterPage(1);
}

void MainLibraryWindow::loadRegisterPage(const int &arg)
{
    ui->stackedWidget->setCurrentIndex(4);
    //load tab
    ui->tabWidAdd->setCurrentIndex(arg);

    //initialize the Register page
    ui->lineRegBookID->setText("");
    ui->lineRegBookName->setText("");
    ui->lineRegCategory->setText("");
    ui->lineRegAuthor->setText("");
    ui->lineRegPublisher->setText("");
    ui->lineRegEdition->setText("");
    ui->lineRegPubYear->setText("");
    ui->spinQuantity->setValue(1);
    ui->lineRegStatus->setText("Not Available");
    ui->lineRegUserID->setText("");
    ui->lineRegUserName->setText("");
    ui->lineRegAddress->setText("");
    ui->lineRegContact->setText("");
    ui->comboUserType->setCurrentIndex(0);

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
        //check if the book is returned late
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
            //check if the book is returned late
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
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Quit", "Would You like to exit?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {

        QApplication::quit();
      }
}

void MainLibraryWindow::on_pushButton_clicked()
{
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Quit", "Would You like to exit?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {

        QApplication::quit();
      }
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


//Issue Function
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


        if (qnty == 1){ //The last book cannot be issued.
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

            //update the books database with the new quantity
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

//Return Function
void MainLibraryWindow::on_returnButton_clicked()
{
    //initialize the variables
    QSqlQuery query,del,book,upd;
    QString bookID,userID,transNum,quantity,late,damage,pen,bookName;
    int totalPenalty, qnty;
    bookID = ui->lineBookID2->text();
    userID = ui->lineUserID2->text();
    late = ui->lineLatePenalty->text();
    damage = ui->lineDamagePenalty->text();

    //calculate the amount of penalties incurred
    totalPenalty = late.toInt() + damage.toInt();
    pen.setNum(totalPenalty);
    //setup the query
    query.prepare("select * from issued where BookID='"+bookID+"' and UserID='"+userID+"'");
    if (query.exec()){
        int count = 0;
        while (query.next()){
            count ++;
            transNum = query.value(7).toString();
            }
        //look for the specific book borrowed. If it's not found, show an error
        if (count == 0){
            QMessageBox::about(this, "Error", "No matching issued book.");
        }
        else if (count == 1){
            //exec query
            book.exec("select * from books where BookID='"+bookID+"'");
            while (book.next()){
                QSqlRecord record  = book.record(); //Record query values
                quantity = record.value("Quantity").toString();
                qnty = quantity.toInt();
                qnty++;
                quantity = QString::number(qnty);
                bookName = record.value("BookName").toString();

                //Check if the book is damaged or not, then run the main query
                if (ui->checkBox->checkState() == false){
                    QMessageBox::about(this, "Penalties", "Total Penalties: '"+pen+"'");
                    del.exec("Delete from issued where TransactionNum='"+transNum+"'");
                    QMessageBox::about(this, "Book Returned", "Book has been returned successfully.");
                    upd.exec("update books set Status='Available', Quantity='"+quantity+"' where BookID='"+bookID+"'"); //update the quantity

                    //show Message then clear the page
                    ui->statusbar->showMessage("Book Returned", 3000);
                    loadReturnPage();
                }
                else {
                    QMessageBox::about(this, "Penalties", "Total Penalties: '"+pen+"'");
                    del.exec("Delete from issued where TransactionNum='"+transNum+"'");
                    QMessageBox::about(this, "Book Returned", "Book has been added to Damaged Books.");
                    upd.exec("insert into damagedBooks (BookID,BookName) values ('"+bookID+"', '"+bookName+"')"); //add the book to damaged books

                    //show Message then clear the page
                    ui->statusbar->showMessage("Book added to Damaged books", 3000);
                    loadReturnPage();
                }

            }

        }

    }

}

void MainLibraryWindow::on_spinQuantity_valueChanged(int arg1)
{
    if (arg1 > 1){
        ui->lineRegStatus->setText("Available");

    }
    else if (arg1 < 1){
        QMessageBox::about(this, "Error", "Cannot have less than one book.");
        ui->spinQuantity->setValue(1);

    }
    else {
        ui->lineRegStatus->setText("Not Available");
    }
}

//Register Function
void MainLibraryWindow::on_regRegButton_clicked()
{
    //initialize variables
    int arg = ui->tabWidAdd->currentIndex();
    QSqlQuery query,check,add;
    QString arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;

    //Checks if it's registering a book or a user
    if (arg == 0){  //if registering a book

        //set lineEdit values to QString variables
        arg1 = ui->lineRegBookID->text();
        arg2 = ui->lineRegBookName->text();
        arg3 = ui->lineRegCategory->text();
        arg4 = ui->lineRegAuthor->text();
        arg5 = ui->lineRegPublisher->text();
        arg6 = ui->lineRegEdition->text();
        arg7 = ui->lineRegPubYear->text();
        arg8 = ui->spinQuantity->text();
        arg9 = ui->lineRegStatus->text();

        //check if there's a duplicate book using the book ID
        if (check.exec("select BookID from books where BookID='"+arg1+"'")){
            int count = 0;
            while (check.next()){
                count++;
            }
            //if there's no duplicate,
            if (count == 0){
                add.exec("insert into books (BookID,BookName,Category,Author,Publisher,Edition,PublishingYear,Quantity,Status) values ('"+arg1+"','"+arg2+"','"+arg3+"','"+arg4+"','"+arg5+"','"+arg6+"','"+arg7+"','"+arg8+"','"+arg9+"')");
                QMessageBox::about(this, "Book Registered","Book registered successfully.");
               passRegisterBook();
            }
             //if there's a duplicate,
            else {
                QMessageBox::StandardButton reply;

                //ask if they would like to update the existing user instead
                  reply = QMessageBox::question(this, "Warning.", "A book with the same ID has been found. Would you like to update it instead?",
                                                QMessageBox::Yes|QMessageBox::No);
                  if (reply == QMessageBox::Yes) {
                    query.exec("update books set BookID='"+arg1+"',BookName='"+arg2+"', Category='"+arg3+"', Author='"+arg4+"', Publisher='"+arg5+"', Edition='"+arg6+"', PublishingYear='"+arg7+"', Quantity='"+arg8+"', Status='"+arg9+"' where BookID='"+arg1+"'");
                    passRegisterBook();
                  }
                  else {
                    QMessageBox::about(this, "", "Book not registered.");
                  }
            }
        }

    }
    else if (arg == 1){ //if registering a user
        //set lineEdit values to QString variables
        arg1 = ui->lineRegUserID->text();
        arg2 = ui->lineRegUserName->text();
        arg3 = ui->lineRegAddress->text();
        arg4 = ui->lineRegContact->text();
        arg5 = ui->comboUserType->currentText();

        //check if there's a duplicate book using the User ID
        if (check.exec("select UserID from users where UserID='"+arg1+"'")){
            int count = 0;
            while (check.next()){
                count++;
            }
            //if there's no duplicate,
            if (count == 0){
                add.exec("insert into users (UserID, UserName, UserAddress, UserContactNumber, UserType) values ('"+arg1+"', '"+arg2+"', '"+arg3+"', '"+arg4+"', '"+arg5+"')");
                QMessageBox::about(this, "User Registered","User registered successfully.");
                passRegisterUser();
            }
           //if there's a duplicate,
            else {
                QMessageBox::StandardButton reply;

                //ask if they would like to update the existing user instead
                  reply = QMessageBox::question(this, "Warning.", "A user with the same ID has been found. Would you like to update it instead?",
                                                QMessageBox::Yes|QMessageBox::No);
                  if (reply == QMessageBox::Yes) {
                    query.exec("update users set UserID='"+arg1+"',UserName='"+arg2+"', UserAddress='"+arg3+"', UserContactNumber='"+arg4+"', UserType='"+arg5+"' where UserID='"+arg1+"'");
                    QMessageBox::about(this, "User Registered", "User details Updated.");
                    passRegisterUser();
                  }
                  else {
                    QMessageBox::about(this, "", "User not registered.");
                  }
            }
        }


    }
}

void MainLibraryWindow::on_regClear_clicked()
{
    int arg = ui->tabWidAdd->currentIndex();
    if (arg == 0){
        passRegisterBook();
    }
    else if (arg == 1) {
        passRegisterUser();
    }
}
