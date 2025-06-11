#include "QFile"
#include "QTextStream"
#include "QDateTime"
#include <QDebug>

#ifndef LOGCREATER_H
#define LOGCREATER_H


class logCreater
{
private:
    QFile file;
    char mod;
public:

    explicit logCreater(const QString &fileName, char mod);

    ~logCreater();

    QStringList dateTimeSort(QDateTime& from, QDateTime& to, const QString& fileName);

    void message(QString str);
};

#endif // LOGCREATER_H
