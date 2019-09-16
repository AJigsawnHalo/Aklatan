#include "setupmanager.h"
#include "ui_setupmanager.h"

SetupManager::SetupManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetupManager)
{
    ui->setupUi(this);
}

SetupManager::~SetupManager()
{
    delete ui;
}
