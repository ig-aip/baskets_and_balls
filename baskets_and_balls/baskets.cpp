#include "baskets.h"
#include "QRandomGenerator"


Baskets::Baskets() : countBlueBalls(0), countRedBalls(0), allCount(0){}

Baskets::Baskets(int blueBalls, int redBalls) : countBlueBalls(blueBalls), countRedBalls(redBalls), allCount(redBalls + blueBalls) {}


int Baskets::getCountBlueBalls() const { return countBlueBalls; }

int Baskets::getCountRedBalls() const { return countRedBalls; }

int Baskets::getAllCount() const { return allCount; }

void Baskets::setChangesFlag(const short changes) { changesFlag = changes; }

void Baskets::setRandomChangesFlag(const Baskets & second){
    int randInt = 0;
    randInt = QRandomGenerator::global()->bounded(1, 101);
    if (randInt <= getAllProcentGetBlueBall(second) && (AllCountBlueBalls(second)) >= 2)
    {
        changesFlag = changesFlag | 1 << 2; //Удалить 2 синих шара
    }
    else if ((getAllProcentGetBlueBall(second) < randInt) && (randInt <= (getAllProcentGetRedBall(second) + getAllProcentGetBlueBall(second)))
               && (AllCountRedBalls(second)) >= 2)
    {
        changesFlag = changesFlag | 1 << 3; //Удалить 2 красных шара
    }
    else if (AllCountBlueBalls(second) >= 1 && AllCountRedBalls(second) >= 1)
    {
        changesFlag = changesFlag | 1 << 4; //Удалить 2 смешанных шара
    }
}

short Baskets::getChangesFlag() const{
    return changesFlag;
}

int Baskets::AllCountBlueBalls(const Baskets &second) const
{
    return getCountBlueBalls() + second.getCountBlueBalls();
}

int Baskets::AllCountRedBalls(const Baskets &second) const
{
    return getCountRedBalls() + second.getCountRedBalls();
}

int Baskets::getCorrectRandInt(const Baskets& second) const{
    int randInt = QRandomGenerator::global()->bounded(3);

    if (second.getAllCount() == 0)
    {
        return 0;
    }
    else if (allCount == 0)
    {
        return 1;
    }
    else if (allCount == 1 && second.getAllCount() == 1)
    {
        return 2;
    }

    return randInt;
}


int Baskets::getProcentGetBlueBall() const
{
    if (countBlueBalls == 0)
    {
        return 0;
    }

    double procent = (((double) countBlueBalls / (double) allCount)) * 100;
    if ((procent - (int) procent) >= 0.5)
    {
        return (int) procent + 1;
    }
    return (int) procent;
}

int Baskets::getAllProcentGetBlueBall(const Baskets &second) const
{
    if ((countBlueBalls + second.countBlueBalls) < 2)
    {
        return 0;
    }

    double allProcentBlueBalls = ((double) (AllCountBlueBalls(second))/ (double) (allCount + second.allCount)) * 100;
    if ((allProcentBlueBalls - (int) allProcentBlueBalls) >= 0.5) {
        allProcentBlueBalls += 1;
    }
    allProcentBlueBalls = ((int) allProcentBlueBalls * (int) allProcentBlueBalls) / 100;

    if(allProcentBlueBalls < 1){ return 1; }
    return (int) allProcentBlueBalls;
}

int Baskets::getProcentGetRedBall() const
{
    if (countRedBalls == 0)
    {
        return 0;
    }

    double procent = (((double) countRedBalls / (double) allCount)) * 100;
    if ((procent - (int) procent) >= 0.5)
    {
        return (int) procent + 1;
    }
    return (int) procent;
}

int Baskets::getAllProcentGetRedBall(const Baskets &second) const
{
    if ((AllCountRedBalls(second)) < 2)
    {
        return 0;
    }

    double allProcentRedBalls = ((double) (AllCountRedBalls(second)) / (double) (allCount + second.allCount)) * 100;
    if ((allProcentRedBalls - (int) allProcentRedBalls) >= 0.5)
    {
        allProcentRedBalls += 1;
    }
    allProcentRedBalls = (allProcentRedBalls *  allProcentRedBalls) / 100;

    if(allProcentRedBalls < 1){ return 1; }

    return (int) allProcentRedBalls;
}

int Baskets::getProcentOneRedOneBlueBalls(const Baskets &second) const
{
    if ((getAllProcentGetBlueBall(second) + getAllProcentGetRedBall(second)) == 0)
    {
        return 0;
    }
    int procentOneRedOneBlue = 100 - (getAllProcentGetBlueBall(second) + getAllProcentGetRedBall(second));

    return procentOneRedOneBlue;
}


void Baskets::addBlueBall(const int countBalls)
{
    countBlueBalls = countBlueBalls + countBalls;
    allCount += countBalls;
}
void Baskets::subBlueBall(const int countBalls)
{
    countBlueBalls = countBlueBalls - countBalls;
    allCount -= countBalls;
}

void Baskets::addRedBall(const int countBalls)
{
    countRedBalls = countRedBalls + countBalls;
    allCount += countBalls;
}
void Baskets::subRedBall(const int countBalls)
{
    countRedBalls = countRedBalls - countBalls;
    allCount -= countBalls;
}

void Baskets::subTwoBlueBalls(Baskets & second, int randInt){
    if (randInt == 0 && (getCountBlueBalls() >= 2))
    {
        subBlueBall(2);
        changesFlag = 1 << 5;
    }
    else if (randInt == 1 && (second.getCountBlueBalls() >= 2))
    {
        second.subBlueBall(2);
        second.setChangesFlag(1 << 5);
    }
    else if (randInt == 2 && (getCountBlueBalls() >= 1) && (second.getCountBlueBalls() >= 1))
    {
        subBlueBall(1);
        second.subBlueBall(1);
        changesFlag = 1 << 6;
        second.setChangesFlag(1 << 6);
    }
}

void Baskets::subTwoRedBalls(Baskets& second, int randInt){
    if (randInt == 0 && (countRedBalls >= 2))
    {
        subRedBall(2);
        changesFlag = 1 << 7;
    }
    else if (randInt == 1 && (second.getCountRedBalls() >= 2))
    {
        second.subRedBall(2);
        second.setChangesFlag(1 << 7);
    }
    else if (randInt == 2 && (countRedBalls >= 1) && (second.getCountRedBalls() >= 1))
    {
        subRedBall(1);
        second.subRedBall(1);
        changesFlag = 1 << 8;
        second.setChangesFlag(1 << 8);
    }
}

void Baskets::subOneBlueOneRedFirstBasket(Baskets& second, int randInt){
    if (countBlueBalls > 0 && countRedBalls > 0) {
        subBlueBall(1);
        subRedBall(1);
        changesFlag = 1 << 9;
    }
    else
    {
        if (countBlueBalls == 0 && countRedBalls == 0)
        {
            second.subBlueBall(1);
            second.subRedBall(1);
            second.setChangesFlag(1 << 9);
        }
        else if (countBlueBalls == 0)
        {
            subRedBall(1);
            second.subBlueBall(1);
            changesFlag = 1 << 8;
            second.setChangesFlag(1 << 6);
        }
        else if (countRedBalls == 0)
        {
            subBlueBall(1);
            second.subRedBall(1);
            changesFlag = 1 << 6;
            second.setChangesFlag(1 << 8);
        }
    }
}

void Baskets::subOneBlueOneRedSecondBasket(Baskets& second, int randInt){
    if (second.getCountBlueBalls() > 0 && second.getCountRedBalls() > 0)
    {
        second.subBlueBall(1); //sub 1 blue, 1 red ball in second basket
        second.subRedBall(1);
        second.setChangesFlag(1 << 9);
    }
    else
    {
        if (second.getCountBlueBalls() == 0 && second.getCountRedBalls() == 0)
        {
            subBlueBall(1);
            subRedBall(1);
            changesFlag = 1 << 9;
        }
        else if (second.getCountBlueBalls() == 0)
        {
            second.subRedBall(1);
            subBlueBall(1);
            second.setChangesFlag(1 << 8);
            changesFlag = 1 << 6;
        }
        else if (second.getCountRedBalls() == 0)
        {
            second.subBlueBall(1);
            subRedBall(1);
            second.setChangesFlag(1 << 6);
            changesFlag = 1 << 8;
        }
    }
}
void Baskets::subOneBlueOneRedMixedBaskets(Baskets& second, int randInt){
    if ((countBlueBalls >= 1 && second.countRedBalls >= 1)
        || (countRedBalls >= 1 && second.countBlueBalls >= 1))
    {
        if ((countBlueBalls >= 1 && second.countRedBalls >= 1)
            && (countRedBalls >= 1 && second.countBlueBalls >= 1))
        {
            if (QRandomGenerator::global()->bounded(2) == 1)
            {
                subBlueBall(1);
                second.subRedBall(1);
                changesFlag = 1 << 6;
                second.setChangesFlag(1 << 8);
            }
            else
            {
                subRedBall(1);
                second.subBlueBall(1);
                changesFlag = 1 << 8;
                second.setChangesFlag(1 << 6);
            }
        }
        else if (countBlueBalls >= 1 && second.countRedBalls >= 1)
        {
            subBlueBall(1);
            second.subRedBall(1);
            changesFlag = 1 << 6;
            second.setChangesFlag(1 << 8);
        }
        else if (countRedBalls >= 1 && second.countBlueBalls >= 1)
        {
            subRedBall(1);
            second.subBlueBall(1);
            changesFlag = 1 << 8;
            second.setChangesFlag(1 << 6);
        }
        else if (countBlueBalls == 0 || second.countRedBalls == 0)
        {
            if (countBlueBalls == 0 && second.getCountRedBalls() == 0)
            {
                second.subBlueBall(1);
                subRedBall(1);
                second.setChangesFlag(1 << 6);
                changesFlag = 1 << 8;
            }
            else if (countBlueBalls == 0 && second.getCountRedBalls() >= 1)
            {
                second.subBlueBall(1);
                second.subRedBall(1);
                second.setChangesFlag(1 << 9);
            }
            else if (countBlueBalls >= 1 && second.getCountRedBalls() == 0) {
                subBlueBall(1);
                subRedBall(1);
                changesFlag = 1 << 9;
            }
        }
        else if (countRedBalls == 0 || second.getCountBlueBalls() == 0)
        {
            if (countRedBalls == 0 && second.getCountBlueBalls() == 0)
            {
                second.subRedBall(1);
                subBlueBall(1);
                second.setChangesFlag(1 << 8);
                changesFlag = 1 << 6;
            }
            else if (countRedBalls == 0 && second.getCountBlueBalls() >= 1)
            {
                second.subBlueBall(1);
                second.subRedBall(1);
                second.setChangesFlag(1 << 9);
            }
            else if (countRedBalls >= 1 && second.getCountBlueBalls() == 0)
            {
                subBlueBall(1);
                subRedBall(1);
                changesFlag = 1 << 9;
            }
        }
    }
}

const char *Baskets::getLustChanges() const
{
    if (changesFlag & 1 << 0)
    {
        return "Последнее действие: извлекли синий шар";
    }
    else if (changesFlag & 1 << 1)
    {
        return "Последнее действие: извлекли красный шар";
    }
    else if (changesFlag & 1 << 5)
    {
        return "Последнее действие: извлекли 2 синих шара";
    }
    else if (changesFlag & 1 << 6)
    {
        return "Последнее действие: извлекли 1 синий шар";
    }
    else if (changesFlag & 1 << 7)
    {
        return "Последнее действие: извлекли 2 красных шара";
    }
    else if (changesFlag & 1 << 8)
    {
        return "Последнее действие: извлекли 1 красный шар";
    }
    else if (changesFlag & 1 << 9)
    {
        return "Последнее действие: извлекли 1 синий и 1 красный шар";
    }
    else
    {
        return "Последнее действие: none";
    }
    return "";
}


void Baskets::replaceBall(Baskets &second)
{
    int randInt = 0;

    if ((countBlueBalls || countRedBalls) != 0)
    {
        randInt = QRandomGenerator::global()->bounded(1, 101);
        if (randInt <= getProcentGetBlueBall())
        {
            subBlueBall(1);
            second.addBlueBall(1);
            changesFlag = 1 << 0;
        }
        else
        {
            subRedBall(1);
            second.addRedBall(1);
            changesFlag = 1 << 1;
        }
    }
}

void Baskets::processTwoBlue(Baskets& second, int randInt){
    changesFlag = changesFlag ^ (1 << 2);

    if (randInt == 0 && (getCountBlueBalls() <= 2))
    {
        if (getCountBlueBalls() == 0)
        {
            randInt = 1;
        }
        if (getCountBlueBalls() == 1)
        {
            randInt = 2;
        }
    }
    else if (randInt == 1 && second.getCountBlueBalls() <= 2)
    {
        if (second.getCountBlueBalls() == 0)
        {
            randInt = 0;
        }
        if (second.getCountBlueBalls() == 1)
        {
            randInt = 2;
        }
    }
    else if (randInt == 2 && (getCountBlueBalls() == 0 || second.getCountBlueBalls() == 0))
    {
        if (getCountBlueBalls() == 0) {
            randInt = 1;
        }
        else {
            randInt = 0;
        }
    }

    subTwoBlueBalls(second, randInt);
}

void Baskets::processTwoRed(Baskets& second, int randInt){
    changesFlag = changesFlag ^ (1 << 3);
    if (randInt == 0 && (countRedBalls <= 2))
    {
        if (countRedBalls == 0) {
            randInt = 1;
        }
        if (countRedBalls == 1) {
            randInt = 2;
        }
    }
    else if (randInt == 1 && second.getCountRedBalls() <= 2)
    {
        if (second.getCountRedBalls() == 0)
        {
            randInt = 0;
        }
        if (second.getCountRedBalls() == 1)
        {
            randInt = 2;
        }
    }
    else if (randInt == 2 && (countRedBalls == 0 || second.getCountRedBalls() == 0))
    {
        if (countRedBalls == 0)
        {
            randInt = 1;
        }
        else
        {
            randInt = 0;
        }
    }

    subTwoRedBalls(second, randInt);
}

void Baskets::processMixed(Baskets& second, int randInt){
    changesFlag = changesFlag ^ (1 << 4);

    if(randInt == 0)
    {
        subOneBlueOneRedFirstBasket(second, randInt);
    }
    else if(randInt == 1)
    {
        subOneBlueOneRedSecondBasket(second, randInt);
    }
    else if(randInt == 2)
    {
        subOneBlueOneRedMixedBaskets(second, randInt);
    }
}

void Baskets::replaceTwoBalls(Baskets &second)
{
    if ((getAllCount() + second.getAllCount()) >= 2)
    {
        setRandomChangesFlag(second);

        unsigned int randInt = getCorrectRandInt(second);
        //0 = вычетает 2 шара из первой корзины
        //1 = вычетает 2 шара из второй корзины
        //2 = вычетает 1 шар из первой корзины и 1 шар из второй


        if (changesFlag & 1 << 2)
        {
            processTwoBlue(second, randInt);                   //вычетает 2 синих шара
        }
        else if (changesFlag & 1 << 3)
        {
            processTwoRed(second, randInt);                    //вычетает 2 красных шара
        }
        else if (changesFlag & 1 << 4)
        {
            processMixed(second, randInt);                     //вычетает 2 смешанных шара
        }
    }
}

void Baskets::determintaeReplaceTwoBalls(Baskets& second, short dChangesFlag, int dRandInt){
    if ((getAllCount() + second.getAllCount()) >= 2)
    {
        changesFlag = dChangesFlag;

        unsigned int randInt = setDeterminateCorrectRandInt(second, dRandInt);
        //0 = вычетает 2 шара из первой корзины
        //1 = вычетает 2 шара из второй корзины
        //2 = вычетает 1 шар из первой корзины и 1 шар из второй


        if (changesFlag & 1 << 2)
        {
            processTwoBlue(second, randInt);
        }
        else if (changesFlag & 1 << 3)
        {
            processTwoRed(second, randInt);
        }
        else if (changesFlag & 1 << 4)
        {
            processMixed(second, randInt);
        }
    }
}

int Baskets::setDeterminateCorrectRandInt(const Baskets& second, int dRandInt) const{
    int randInt = dRandInt;

    if (second.getAllCount() == 0)
    {
        return 0;
    }
    else if (allCount == 0)
    {
        return 1;
    }
    else if (allCount == 1 && second.getAllCount() == 1) {
        return 2;
    }

    return randInt;
}


