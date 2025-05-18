#include "jsonloader.h"
#include "QJsonObject"
#include "QJsonArray"
#include "QJsonDocument"
#include "QFile"

JsonLoader::JsonLoader(QObject * parent) : QObject(parent) {}

QVector<Baskets> JsonLoader::loaderBasketes(const QString& filePath)
{
    QVector<Baskets> basketVec;

    QJsonObject root = parseJson(filePath);

    QJsonArray basketsArr = root["baskets"].toArray();

    for(const QJsonValue& basketValue : basketsArr ){
        QJsonObject basketObj = basketValue.toObject();

        int blue = basketObj["blue"].toInt();
        int red = basketObj["red"].toInt();

        basketVec.push_back(Baskets(blue, red));
    }

    return basketVec;
}

QJsonObject JsonLoader::parseJson(const QString& filePath){
    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly))
    {
        throw std::runtime_error("Cannot open file: " + filePath.toStdString());
    }

    QByteArray data = file.readAll();
    QJsonParseError parseError;

    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

    if(parseError.error != QJsonParseError::NoError){
        throw std::runtime_error("Json parese error" + parseError.errorString().toStdString());
    }

    return doc.object();
}


