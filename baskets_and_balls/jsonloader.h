#include "QObject"
#include "QVector"
#include "baskets.h"

#ifndef JSONLOADER_H
#define JSONLOADER_H

class JsonLoader : public QObject
{
    Q_OBJECT
public:

    JsonLoader(QObject * parent = nullptr);

    QVector<Baskets> loaderBasketes(const QString& filePath);

    QJsonObject parseJson(const QString& filePath);
};

#endif // JSONLOADER_H
