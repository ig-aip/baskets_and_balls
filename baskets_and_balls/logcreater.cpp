#include "logcreater.h"

logCreater::logCreater(const QString &fileName, char mod){
    if(mod == 't')
    {
        file.setFileName(fileName);
        file.open(QIODevice::WriteOnly | QIODevice::Truncate);
        message("------Старт программы------");
    }
    else if(mod == 'a')
    {
        file.setFileName(fileName);
        file.open(QIODevice::Append);
        message("------Старт программы------");
    }
    if(!file.isOpen()){
        qWarning("File not open");
    }
}

logCreater::~logCreater(){
    if(file.isOpen()){
        message("------Завершение программы------");
        file.close();
    }
}


QStringList logCreater::dateTimeSort(QDateTime& from, QDateTime& to, const QString& fileName ){
    QStringList list;



    QFile fileRead(fileName);
    fileRead.open(QIODevice::ReadOnly);
    QTextStream reader(&fileRead);

    while(!reader.atEnd()){
        QString line = reader.readLine();

        QString timeString = line.mid(1, 19);
        QDateTime nowTime = QDateTime::fromString(timeString, "yyyy-MM-dd HH:mm:ss");

        if(nowTime.isValid() && nowTime >= from && nowTime <= to){
            list.append(line);
        }
    }
    fileRead.close();
    return list;
}


void logCreater::message(QString msg){
    if(!file.isOpen()){ return; }

    QTextStream out(&file);
    QString timeMoment =  QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    out << '[' << timeMoment <<"] " << msg <<"\n";

    out.flush();
}

