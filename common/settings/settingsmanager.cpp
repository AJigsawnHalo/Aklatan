#include "settingsmanager.h"
#include "ui_settingsmanager.h"

#include <QtDebug>
#define keyDB "DatabaseName"
#define keyDamage "DamagePenalty"
#define keyLate "LatePenalty"
#define keyDue "DaysDue"


SettingsManager::SettingsManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingsManager)
{
    ui->setupUi(this);
    loadConf();
}

SettingsManager::~SettingsManager()
{
    delete ui;
}

QString dbName = "";
double damagePenalty = 0;
double latePenalty = 0;
QString lpenalty;
QString dpenalty;
QDate today = QDate::currentDate();
int daysDue = 0;
QDate dueDate = today.addDays(daysDue);

void SettingsManager::saveSettings(const QString &key, const QVariant &value, const QString &group)
{
    QSettings settings(QSettings::IniFormat,QSettings::UserScope,"Aklatan-project","Aklatan");
    settings.beginGroup(group);
    settings.setValue(key, value);
    settings.endGroup();
}


QVariant SettingsManager::loadSettings(const QString &key, const QString &group, const QVariant &defaultValue = QVariant())
{
    QSettings settings(QSettings::IniFormat,QSettings::UserScope,"Aklatan-project","Aklatan");
    settings.beginGroup(group);
    QVariant value = settings.value(key, defaultValue);
    settings.endGroup();
    return value;
}



void SettingsManager::on_saveButton_clicked()
{
    saveConf();
    setConf();
    this->hide();

}

void SettingsManager::on_loadButton_clicked()
{
    loadConf();
}
void SettingsManager::setConf()
{
    QString dbNameNew, damNew, lateNew, dueNew, value;

    QString group = "Settings";
    QString key[4] = {keyDB,keyDamage,keyLate,keyDue};
    QString conf[4] = {dbNameNew,damNew,lateNew,dueNew};
    QString def[4] = {defDbName,QString::number(defDamagePenalty),QString::number(defLatePenalty),QString::number(defDaysDue)};
    for (int i = 0; i < 4; i++){
       QString keyPass, defPass, confPass;
       keyPass = key[i];
       defPass = def[i];
       value = loadSettings(keyPass, group, defPass).toString();
       conf[i] = value;

    }

    dbName = conf[0] + ".db";
    damagePenalty = conf[1].toDouble();
    latePenalty = conf[2].toDouble();
    daysDue = conf[3].toInt();
}

void SettingsManager::loadConf()
{
    QString dbNameNew, damNew, lateNew, dueNew, value;

    QString group = "Settings";
    QString key[4] = {keyDB,keyDamage,keyLate,keyDue};
    QString conf[4] = {dbNameNew,damNew,lateNew,dueNew};
    QString def[4] = {defDbName,QString::number(defDamagePenalty),QString::number(defLatePenalty),QString::number(defDaysDue)};
    for (int i = 0; i < 4; i++){
       QString keyPass, defPass, confPass;
       keyPass = key[i];
       defPass = def[i];
       value = loadSettings(keyPass, group, defPass).toString();
       conf[i] = value;

    }
     ui->lineDbName->setText(conf[0]);
     ui->linedamagePenalty->setText(conf[1]);
     ui->lineLatePenalty->setText(conf[2]);
     ui->lineDaysDue->setText(conf[3]);
}


void SettingsManager::on_cancelButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Warning.", "Are you sure you want to cancel?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
      this->hide();
    }

}

void SettingsManager::on_applyButton_clicked()
{
    saveConf();
    setConf();
}
void SettingsManager::saveConf()
{
    QString dbNameNew, damNew, lateNew, dueNew;


    dbNameNew = ui->lineDbName->text();
    damNew = ui->linedamagePenalty->text();
    lateNew = ui->lineLatePenalty->text();
    dueNew = ui->lineDaysDue->text();

    QString group = "Settings";
    QString key[4] = {keyDB,keyDamage,keyLate,keyDue};
    QString conf[4] = {dbNameNew,damNew,lateNew,dueNew};
    QString def[4] = {defDbName,QString::number(defDamagePenalty),QString::number(defLatePenalty),QString::number(defDaysDue)};
    for (int i = 0; i < 4; i++){
       QString keyPass, confPass, defPass;
       keyPass = key[i];
       confPass = conf[i];
       defPass = def[i];
       saveSettings(keyPass, confPass, group);
    }
}
