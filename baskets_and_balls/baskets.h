#ifndef BASKETS_H
#define BASKETS_H
#include "QRandomGenerator"
#include "QVector"
#include "logcreater.h"


enum changesFlagsNames : short{
    None                  = 0,        // ничего
    MoveBlue              = 1 << 0,   // перемещение синего шара
    MoveRed               = 1 << 1,   // перемещение красного шара
    RemoveTwoBlueMode     = 1 << 2,   // режим удаления 2 синих шаров
    RemoveTwoRedMode      = 1 << 3,   // режим удаления 2 красных шаров
    RemoveMixedMode       = 1 << 4,   // режим удаления 1 синего + 1 красного шара

    MesgTwoBlueRemoved    = 1 << 5,   // сообщение об удалении 2 синих
    MesgOneBlueRemoved    = 1 << 6,   // сообщение об удалении 1 синего
    MesgTwoRedRemoved     = 1 << 7,   // сообщение об удалении 2 красных
    MesgOneRedRemoved     = 1 << 8,   // сообщение об удалении 1 красного
    MesgMixedRemoved      = 1 << 9,   // сообщение об удалении 1 синего + 1 красного

    MesgBlueAdded         = 1 << 10,  // сообщение об добавлении синего
    MesgRedAdded          = 1 << 11,  // сообщение об добавлении красного
    MesgTwoMixedRemoved   = 1 << 12,  // вычетание 2 смешанных шаров из разных корзин ( для логов )



};

static std::pair<int , int> indxForDo{-1 , -1};

class Baskets
{
private:
    int countBlueBalls;
    int countRedBalls;
    int allCount;
    short changesFlag = 0;
    //(0)       00000000 00000000 ничего
    //(1 << 0)  10000000 00000000 перемещение синего шара
    //(1 << 1)  01000000 00000000 перемещение красного шара
    //(1 << 2)  00100000 00000000 режим удаления 2 синих шаров
    //(1 << 3)  00010000 00000000 режим удаления 2 красных шаров
    //(1 << 4)  00001000 00000000 режим удаления 1 синего и 1 красного шара
    //(1 << 5)  00000100 00000000 сообщение об удалении 2 синих шаров
    //(1 << 6)  00000010 00000000 сообщение об удалении 1 синего шара
    //(1 << 7)  00000001 00000000 сообщение об удалении 2 красных шаров
    //(1 << 8)  00000000 10000000 сообщение об удалении 1 красного шара
    //(1 << 9)  00000000 01000000 сооьщение об удалении 1 синего и 1 красного шара
    //(1 << 10) 00000000 00100000 сообщение об добавлении синего шара
    //(1 << 11) 00000000 00010000 сообщение об добавлении красного шара
    //(1 << 12) 00000000 00001000 сообщение об удалении смешанных цветов из разнык корзин( для логов )

public:
    Baskets();

    Baskets(int blueBalls, int redBalls);


    //геттеры и сеттеры
    int getCountBlueBalls() const;

    int getCountRedBalls() const;

    int getAllCount() const;

    void setChangesFlag(const short changes);

    void setRandomChangesFlag(const QVector<Baskets> & basketVec);

    short getChangesFlag() const;

    int allCountBlueBalls(const QVector<Baskets> & basketVec) const;

    int allCountRedBalls(const QVector<Baskets> & basketVec) const;

    int allCountAllBaskets(const QVector<Baskets> & basketVec) const;

    int getCorrectRandInt(QVector<Baskets> & basketVec) const;

    int getRandomSelectBasketExcept(const QVector<Baskets> & basketVec, const int exceptIndx);


    //Получение процентов
    int getProcentGetBlueBall() const;

    int getAllProcentGetBlueBall(const QVector<Baskets> & basketVec) const;

    int getProcentGetRedBall() const;

    int getAllProcentGetRedBall(const QVector<Baskets> & basketVec) const;

    int getProcentOneRedOneBlueBalls(const QVector<Baskets> & basketVec) const;


    //Валидация для randInt
    int validTwoBlueBalls(QVector<Baskets> & basketVec);

    int validTwoRedBalls(QVector<Baskets> & basketVec);

    int validMixedBalls(QVector<Baskets> & basketVec);

    void getValidIndxSubOneBasket(const QVector<Baskets> & basketVec,  QVector<int> validIndx, const char color, QVector<int> & vecSubOne);

    void getValidIndxSubTwoBasket(const QVector<Baskets> & basketVec,  QVector<int> validIndx, const char color, QVector<int> & vecSubOne);


    //Добавить/Убавить
    void addBlueBall(const int countBalls);

    void subBlueBall(const int countBalls);

    void addRedBall(const int countBalls);

    void subRedBall(const int countBalls);

    void subTwoBlueBalls(QVector<Baskets> & basketVec, int randInt);

    void subTwoRedBalls(QVector<Baskets> & basketVec, int randInt);

    void subMixedBallsOneBasket(QVector<Baskets> & basketVec, int randInt);

    void subMixedBallsTwoBasket(QVector<Baskets> & basketVec, int randInt);


    //Получение последних изменений
    const char *getLustChanges() const;


    //Логи
    void setLogOneBall(logCreater & logLustTime, logCreater & logAllTime);

    void setLogTwoBall(logCreater & logLustTime, logCreater & logAllTime);

    void startSettingsLog(QVector<Baskets> & basketVec, logCreater & logLustTime, logCreater & logAllTime);


    //вспомогательные методы для удаления двух шаров
    void processTwoBlue(QVector<Baskets> & basketVec, int randInt);

    void processTwoRed(QVector<Baskets> & basketVec, int randInt);

    void processMixed(QVector<Baskets> & basketVec, int randInt);


    //перемещение и удаление шаров
    void replaceBall(QVector<Baskets> &basketVec, int indx);

    void replaceTwoBalls(QVector<Baskets> &basketVec);



    //детерминированный вариант методов, для тестов
    void determintaeReplaceTwoBalls(QVector<Baskets>& basketVec, short dChangesFlag, int dRandInt);

    int setDeterminateCorrectRandInt(const QVector<Baskets>& basketVec, int dRandInt) const;

};

#endif // BASKETS_H
