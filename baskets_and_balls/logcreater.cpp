#include "logcreater.h"

logCreater::logCreater(const QString &fileName) {
    file.setFileName(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    message("------Старт программы------");


    if(!file.isOpen()){
        qWarning("File not open");
    }
}

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


void logCreater::message(QString msg){
    if(!file.isOpen()){ return; }

    QTextStream out(&file);
    QString timeMoment =  QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    out << '[' << timeMoment <<"] " << msg <<"\n";

    out.flush();
}

