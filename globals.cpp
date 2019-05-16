#include "globals.h"

QString dbName = "aklatan.db";
float damagePenalty = 150.0;
float latePenalty = 150.0;
QString lpenalty;
QString dpenalty;
QDate today = QDate::currentDate();
int daysDue = 3;
QDate dueDate = today.addDays(daysDue);
