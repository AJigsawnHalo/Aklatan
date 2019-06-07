#include "settingsmanager.h"
#include "ui_settingsmanager.h"

#include "common/headers/globals.h"
#include <QtDebug>
SettingsManager::SettingsManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingsManager)
{
    ui->setupUi(this);
}

SettingsManager::~SettingsManager()
{
    delete ui;
}

QString dbName = "aklatan.db";
float damagePenalty = 150.0;
float latePenalty = 150.0;
QString lpenalty;
QString dpenalty;
QDate today = QDate::currentDate();
int daysDue = 3;
QDate dueDate = today.addDays(daysDue);


void saveSettings(const QString &key, const QVariant &value, const QString &group)
{
    QSettings settings;
    settings.beginGroup(group);
    settings.setValue(key, value);
    settings.endGroup();
}


QVariant loadSettings(const QString &key, const QString &group, const QVariant &defaultValue = QVariant())
{
    QSettings settings;
    settings.beginGroup(group);
    QVariant value = settings.value(key, defaultValue);
    qDebug() << settings.fileName();
    settings.endGroup();
    return value;
}
