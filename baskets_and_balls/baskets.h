#ifndef BASKETS_H
#define BASKETS_H
#include "QRandomGenerator"
class Baskets
{
private:
    int countBlueBalls;
    int countRedBalls;
    int allCount;
    short changesFlag = 0;
    //00000000 00000000 ничего
    //10000000 00000000 перемещение синего шара
    //01000000 00000000 перемещение красного шара
    //00100000 00000000 режим удаления 2 синих шаров
    //00010000 00000000 режим удаления 2 красных шаров
    //00001000 00000000 режим удаления 1 синего и 1 красного шара
    //00000100 00000000 сообщение об удалении 2 синих шаров
    //00000010 00000000 сообщение об удалении 1 синего шара
    //00000001 00000000 сообщение об удалении 2 красных шаров
    //00000000 10000000 сообщение об удалении 1 красного шара
    //00000000 01000000 сооьщение об удалении 1 синего и 1 красного шара

public:
    Baskets();

    Baskets(int blueBalls, int redBalls);


    //геттеры и сеттеры
    int getCountBlueBalls() const;

    int getCountRedBalls() const;

    int getAllCount() const;

    void setChangesFlag(const short changes);

    void setRandomChangesFlag(const Baskets & second);

    short getChangesFlag() const;

    int AllCountBlueBalls(const Baskets &second) const;

    int AllCountRedBalls(const Baskets &second) const;

    int getCorrectRandInt(const Baskets& second) const;


    //Получение процентов
    int getProcentGetBlueBall() const;

    int getAllProcentGetBlueBall(const Baskets &second) const;

    int getProcentGetRedBall() const;

    int getAllProcentGetRedBall(const Baskets &second) const;

    int getProcentOneRedOneBlueBalls(const Baskets &second) const;


    //Добавить/Убавить
    void addBlueBall(const int countBalls);

    void subBlueBall(const int countBalls);

    void addRedBall(const int countBalls);

    void subRedBall(const int countBalls);

    void subTwoBlueBalls(Baskets& second, int randInt);

    void subTwoRedBalls(Baskets& second, int randInt);

    void subOneBlueOneRedFirstBasket(Baskets& second, int randInt);

    void subOneBlueOneRedSecondBasket(Baskets& second, int randInt);

    void subOneBlueOneRedMixedBaskets(Baskets& second, int randInt);


    //Получение последних изменений
    const char *getLustChanges() const;


    void processTwoBlue(Baskets& second, int randInt);

    void processTwoRed(Baskets& second, int randInt);

    void processMixed(Baskets& second, int randInt);


    //перемещение и удаление шаров
    void replaceBall(Baskets &second);

    void replaceTwoBalls(Baskets &second);


    //детерминированный вариант методов, для тестов
    void determintaeReplaceTwoBalls(Baskets& second, short dChangesFlag, int dRandInt);

    int setDeterminateCorrectRandInt(const Baskets& second, int dRandInt) const;

};

#endif // BASKETS_H
