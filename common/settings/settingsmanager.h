#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QMainWindow>
#include <QSettings>
#include <QDate>

namespace Ui {
class SettingsManager;
}

class SettingsManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit SettingsManager(QWidget *parent = nullptr);
    ~SettingsManager();

private:
    Ui::SettingsManager *ui;
    QString dbName;
    float damagePenalty;
    float latePenalty;
    QString lpenalty;
    QString dpenalty;
    QDate today;
    QDate dueDate;
    int daysDue;
    void saveSettings(const QString &key, const QVariant &value, const QString &group);
    QVariant loadSettings(const QString &key, const QVariant &defaultValue, const QString &group);

};

#endif // SETTINGSMANAGER_H
