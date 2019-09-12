#include "logbook.h"
#include "ui_logbook.h"

LogBook::LogBook(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogBook)
{
    ui->setupUi(this);
}

LogBook::~LogBook()
{
    delete ui;
}
