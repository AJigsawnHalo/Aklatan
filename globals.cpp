#include "globals.h"

QString dbName = "aklatan.db";
float damagePenalty = 150.0;
float latePenalty = 150.0;
QString penalty = "0.0";
QDate today = QDate::currentDate();
int daysDue = 3;
QDate dueDate = today.addDays(daysDue);
