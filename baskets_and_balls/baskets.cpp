#include "baskets.h"
#include "QRandomGenerator"



Baskets::Baskets() : countBlueBalls(0), countRedBalls(0), allCount(0){}

Baskets::Baskets(int blueBalls, int redBalls) : countBlueBalls(blueBalls), countRedBalls(redBalls), allCount(redBalls + blueBalls) {}


int Baskets::getCountBlueBalls() const { return countBlueBalls; }

int Baskets::getCountRedBalls() const { return countRedBalls; }

int Baskets::getAllCount() const { return allCount; }

void Baskets::setChangesFlag(const short changes) { changesFlag = changes; }

void Baskets::setRandomChangesFlag(const QVector<Baskets> & basketVec){
    int randInt = 0;
    randInt = QRandomGenerator::global()->bounded(1, 101);
    if (randInt <= getAllProcentGetBlueBall(basketVec) && (allCountBlueBalls(basketVec)) >= 2)
    {
        changesFlag =  1 << 2; //Удалить 2 синих шара
    }
    else if ((getAllProcentGetBlueBall(basketVec) < randInt) && (randInt <= (getAllProcentGetRedBall(basketVec) + getAllProcentGetBlueBall(basketVec)))
               && (allCountRedBalls(basketVec)) >= 2)
    {
        changesFlag =  1 << 3; //Удалить 2 красных шара
    }
    else if (allCountBlueBalls(basketVec) >= 1 && allCountRedBalls(basketVec) >= 1)
    {
        changesFlag =  1 << 4; //Удалить 2 смешанных шара
    }
}

short Baskets::getChangesFlag() const{
    return changesFlag;
}

int Baskets::allCountBlueBalls(const QVector<Baskets> & basketVec) const
{
    int allBlue = 0;
    for(Baskets b : basketVec){
        allBlue += b.getCountBlueBalls();
    }
    return allBlue;
}

int Baskets::allCountRedBalls(const QVector<Baskets> & basketVec) const
{
    int allRed = 0;
    for(Baskets b : basketVec){
        allRed += b.getCountRedBalls();
    }
    return allRed;
}

int Baskets::allCountAllBaskets(const QVector<Baskets> & basketVec) const
{
    int allBalls = 0;
    for(Baskets b : basketVec){
        allBalls += b.getAllCount();
    }
    return allBalls;
}

int Baskets::getCorrectRandInt(QVector<Baskets> & basketVec) const{
    int randInt = -1;

    if(changesFlag == 1 << 2)
    {
        return basketVec[0].validTwoBlueBalls(basketVec);
    }
    else if(changesFlag == 1 << 3)
    {
        return basketVec[0].validTwoRedBalls(basketVec);
    }
    else if(changesFlag == 1 << 4)
    {
        return basketVec[0].validMixedBalls(basketVec);
    }


    return randInt;
}

int Baskets::getRandomSelectBasketExcept(const QVector<Baskets> & basketVec, const int exceptIndx){
    QVector<int> validNumbers;

    for(int i = 0; i < basketVec.size(); ++i){
        if(i != exceptIndx){
            validNumbers.push_back(i);
        }
    }

    int insertIndx = QRandomGenerator::global()->bounded( validNumbers.size());
    return validNumbers[insertIndx];
}



//получение процентов

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

int Baskets::getAllProcentGetBlueBall(const QVector<Baskets> & basketVec) const
{
    if ((allCountBlueBalls(basketVec)) < 2)
    {
        return 0;
    }
    int countAllVariants = (allCountAllBaskets(basketVec)) * (allCountAllBaskets(basketVec) - 1);
    int countTwoBlueVariants = (allCountBlueBalls(basketVec)) * (allCountBlueBalls(basketVec) - 1);

    double allProcentBlueBalls =((double)countTwoBlueVariants / (double)countAllVariants) * 100;
    if ((allProcentBlueBalls - (int) allProcentBlueBalls) >= 0.5) {
        allProcentBlueBalls += 1;
    }

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

int Baskets::getAllProcentGetRedBall(const QVector<Baskets> & basketVec) const
{
    if ((allCountRedBalls(basketVec)) < 2)
    {
        return 0;
    }

    int countAllVariants = (allCountAllBaskets(basketVec)) * (allCountAllBaskets(basketVec) - 1);
    int countTwoRedVariants = (allCountRedBalls(basketVec)) * (allCountRedBalls(basketVec) - 1);

    double allProcentRedBalls =((double)countTwoRedVariants / (double)countAllVariants) * 100;
    if ((allProcentRedBalls - (int) allProcentRedBalls) >= 0.5)
    {
        allProcentRedBalls += 1;
    }

    if(allProcentRedBalls < 1){ return 1; }

    return (int) allProcentRedBalls;
}

int Baskets::getProcentOneRedOneBlueBalls(const QVector<Baskets> & basketVec) const
{
    if ((getAllProcentGetBlueBall(basketVec) + getAllProcentGetRedBall(basketVec)) == 0 && (allCountBlueBalls(basketVec) == 0) || (allCountRedBalls(basketVec) == 0))
    {
        return 0;
    }
    int procentOneRedOneBlue = 100 - (getAllProcentGetBlueBall(basketVec) + getAllProcentGetRedBall(basketVec));

    return procentOneRedOneBlue;
}

void Baskets::getValidIndxSubOneBasket(const QVector<Baskets> & basketVec,  QVector<int> validIndx, const char color, QVector<int> & vecSubOne)
{
    for(int i = 0; i < validIndx.size(); ++i){
        if(color == 'b')
        {
            if(basketVec[validIndx[i]].getCountBlueBalls() >= 2){ vecSubOne.push_back(validIndx[i]);  }
        }
        else if(color == 'r')
        {
            if(basketVec[validIndx[i]].getCountRedBalls() >= 2){ vecSubOne.push_back(validIndx[i]);  }
        }
        else if(color == 'm')
        {
            if(basketVec[validIndx[i]].getCountBlueBalls() >= 1 && basketVec[validIndx[i]].getCountRedBalls() >= 1){ vecSubOne.push_back(validIndx[i]);  }
        }
    }
}

void Baskets::getValidIndxSubTwoBasket(const QVector<Baskets> & basketVec,  QVector<int> validIndx, const char color, QVector<int> & vecSubTwo)
{
    int countBasketHaveMinBlue = 0;
    int countBasketHaveMinRed = 0;

    for(int i = 0; i < validIndx.size(); ++i){
        if(color == 'b')
        {
            if(basketVec[validIndx[i]].getCountBlueBalls() >= 1){ vecSubTwo.push_back(validIndx[i]); }
        }
        else if(color == 'r')
        {
            if(basketVec[validIndx[i]].getCountRedBalls() >= 2){ vecSubTwo.push_back(validIndx[i]);  }
        }
        else if(color == 'm')
        {
            int randInt = 0;
            if(basketVec[validIndx[i]].getCountBlueBalls() >= 1 && basketVec[validIndx[i]].getCountRedBalls() >= 1)
            {
                randInt = QRandomGenerator::global()->bounded(2);
                if(randInt == 0){ countBasketHaveMinBlue += 1; }
                else if(randInt == 1){ countBasketHaveMinRed += 1; }
            }
            else if(basketVec[validIndx[i]].getCountBlueBalls() >= 1 && basketVec[validIndx[i]].getCountRedBalls() == 0)
            {
                countBasketHaveMinBlue += 1;
            }
            else if(basketVec[validIndx[i]].getCountBlueBalls() == 0 && basketVec[validIndx[i]].getCountRedBalls() >= 1)
            {
                countBasketHaveMinRed += 1;
            }
        }
    }
    if(color == 'm'){
        vecSubTwo.push_back(countBasketHaveMinBlue);
        vecSubTwo.push_back(countBasketHaveMinRed);
    }
}

//Валидация для randInt

int Baskets::validTwoBlueBalls(QVector<Baskets> & basketVec)
{
    Baskets buffer;

    int randInt = 0;
    QVector<int> validIndx;

    for(int i = 0; i < basketVec.size(); ++i){
        if(basketVec[i].getCountBlueBalls() >= 1){
            validIndx.push_back(i);
        }
    }

    QVector<int> vecSubOne;
    QVector<int> vecSubTwo;

    buffer.getValidIndxSubOneBasket(basketVec, validIndx,'b', vecSubOne );
    buffer.getValidIndxSubTwoBasket(basketVec, validIndx,'b', vecSubTwo);

    if(vecSubOne.size() == 0 && vecSubTwo.size() > 1){ return basketVec.size();}

    if(vecSubOne.size() >= 1 && vecSubTwo.size() < 2){
        randInt = QRandomGenerator::global()->bounded(vecSubOne.size());
        return vecSubOne[randInt];
    }

    randInt = QRandomGenerator::global()->bounded(2);

    if(randInt == 0 && vecSubOne.size() >= 1){
        randInt = QRandomGenerator::global()->bounded(vecSubOne.size());
        return vecSubOne[randInt];
    }
    else{
        return basketVec.size();
    }

    return -1;
}

int Baskets::validTwoRedBalls(QVector<Baskets> & basketVec)
{
    Baskets buffer;

    int randInt = 0;
    QVector<int> validIndx;

    for(int i = 0; i < basketVec.size(); ++i){
        if(basketVec[i].getCountRedBalls() >= 1){
            validIndx.push_back(i);
        }
    }

    QVector<int> vecSubOne;
    QVector<int> vecSubTwo;

    buffer.getValidIndxSubOneBasket(basketVec, validIndx,'r', vecSubOne );
    buffer.getValidIndxSubTwoBasket(basketVec, validIndx,'r', vecSubTwo);

    if(vecSubOne.size() == 0 && vecSubTwo.size() > 1){ return basketVec.size();}

    if(vecSubOne.size() >= 1 && vecSubTwo.size() < 2){
        randInt = QRandomGenerator::global()->bounded(vecSubOne.size());
        return vecSubOne[randInt];
    }

    randInt = QRandomGenerator::global()->bounded(2);

    if(randInt == 0 && vecSubOne.size() >= 1){
        randInt = QRandomGenerator::global()->bounded(vecSubOne.size());
        return vecSubOne[randInt];
    }
    else{
        return basketVec.size();
    }

    return -1;

}

int Baskets::validMixedBalls(QVector<Baskets> & basketVec)
{
    Baskets buffer;

    int randInt = 0;
    QVector<int> validIndx;

    for(int i = 0; i < basketVec.size(); ++i){
        if(basketVec[i].getCountBlueBalls() >= 1 || basketVec[i].getCountRedBalls() >= 1){
            validIndx.push_back(i);
        }
    }

    QVector<int> vecSubOne;
    QVector<int> vecSubTwo;

    buffer.getValidIndxSubOneBasket(basketVec, validIndx,'m', vecSubOne );
    buffer.getValidIndxSubTwoBasket(basketVec, validIndx,'m', vecSubTwo);


    if(vecSubOne.size() == 0 && vecSubTwo[0] >= 1 && vecSubTwo[1] >= 1){ return basketVec.size();}
    if(vecSubOne.size() >= 1 && vecSubTwo[0] == 0 || vecSubTwo[1] == 0){
        randInt = QRandomGenerator::global()->bounded(vecSubOne.size());
        return vecSubOne[randInt];
    }

    randInt = QRandomGenerator::global()->bounded(2);

    if(randInt == 0 && vecSubOne.size() >= 1){
        randInt = QRandomGenerator::global()->bounded(vecSubOne.size());
        return vecSubOne[randInt];
    }
    else{
        return basketVec.size();
    }

    return -1;

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

void Baskets::subTwoBlueBalls(QVector<Baskets> & basketVec, int randInt){
    for(int i = 0; i <= basketVec.size(); ++i){
        if(randInt == i && i != basketVec.size())
        {
            basketVec[randInt].subBlueBall(2);
            basketVec[randInt].setChangesFlag(1 << 5);
            return;
        }
        else if(randInt == i && i == basketVec.size())
        {
            QVector<int> validIndx;
            for(int ii = 0; ii < basketVec.size(); ++ii){
                if(basketVec[ii].getCountBlueBalls() > 0){
                    validIndx.push_back(ii);
                }
            }

            if(validIndx.size() > 1){
                int randIndx = QRandomGenerator::global()->bounded(validIndx.size());
                basketVec[validIndx[randIndx]].subBlueBall(1);
                basketVec[validIndx[randIndx]].setChangesFlag(1 << 6);

                validIndx.removeAt(randIndx);
                randIndx = QRandomGenerator::global()->bounded(validIndx.size());
                basketVec[validIndx[randIndx]].subBlueBall(1);
                basketVec[validIndx[randIndx]].setChangesFlag(1 << 6);
                return;
            }
        }
    }
}

void Baskets::subTwoRedBalls(QVector<Baskets> & basketVec, int randInt){
    for(int i = 0; i <= basketVec.size(); ++i){
        if(randInt == i && i != basketVec.size())
        {
            basketVec[randInt].subRedBall(2);
            basketVec[randInt].setChangesFlag(1 << 7);
            return;
        }
        else if(randInt == i && i == basketVec.size())
        {
            QVector<int> validIndx;
            for(int i = 0; i < basketVec.size(); ++i){
                if(basketVec[i].getCountRedBalls() > 0){
                    validIndx.push_back(i);
                }
            }

            if(validIndx.size() > 1){
                int randIndx = QRandomGenerator::global()->bounded(validIndx.size());
                basketVec[validIndx[randIndx]].subRedBall(1);
                basketVec[validIndx[randIndx]].setChangesFlag(1 << 8);

                validIndx.removeAt(randIndx);
                randIndx = QRandomGenerator::global()->bounded(validIndx.size());
                basketVec[validIndx[randIndx]].subRedBall(1);
                basketVec[validIndx[randIndx]].setChangesFlag(1 << 8);
                return;
            }
        }
    }
}

void Baskets::subMixedBallsOneBasket(QVector<Baskets> & basketVec, int randInt){
    basketVec[randInt].subBlueBall(1);
    basketVec[randInt].subRedBall(1);
    basketVec[randInt].setChangesFlag(1 << 9);
}

void Baskets::subMixedBallsTwoBasket(QVector<Baskets> & basketVec, int randInt){
    QVector<int> blueIndx;
    QVector<int> redIndx;
    QVector<int> blueRedIndx;

    int randBlueIndx = 0;
    int randRedIndx = 0;

    for(int i = 0; i < basketVec.size(); ++i){
        if(basketVec[i].getAllCount() >= 1){
            if(basketVec[i].getCountBlueBalls() >= 1 && basketVec[i].getCountRedBalls() >= 1)
            {
                blueRedIndx.push_back(i);
            }
            else if(basketVec[i].getCountBlueBalls() >= 1 && basketVec[i].getCountRedBalls() == 0)
            {
                blueIndx.push_back(i);
            }
            else if(basketVec[i].getCountBlueBalls() == 0 && basketVec[i].getCountRedBalls() >= 1)
            {
                redIndx.push_back(i);
            }
        }
    }

    if(blueIndx.size() != 0 && blueRedIndx.size() != 0){
        randInt = QRandomGenerator::global()->bounded(2);
        if(randInt == 0)
        {
            randBlueIndx = QRandomGenerator::global()->bounded(blueRedIndx.size());
            basketVec[blueRedIndx[randBlueIndx]].subBlueBall(1);
            basketVec[blueRedIndx[randBlueIndx]].setChangesFlag(1 << 6);
            blueRedIndx.removeAt(randBlueIndx);
        }
        else
        {
            randBlueIndx = QRandomGenerator::global()->bounded(blueIndx.size());
            basketVec[blueIndx[randBlueIndx]].subBlueBall(1);
            basketVec[blueIndx[randBlueIndx]].setChangesFlag(1 << 6);
        }
    }
    else if( blueIndx.size() != 0 && blueRedIndx.size() == 0)
    {
        randBlueIndx = QRandomGenerator::global()->bounded(blueIndx.size());
        basketVec[blueIndx[randBlueIndx]].subBlueBall(1);
        basketVec[blueIndx[randBlueIndx]].setChangesFlag(1 << 6);
    }
    else if(blueIndx.size() == 0 && blueRedIndx.size() != 0)
    {
        randBlueIndx = QRandomGenerator::global()->bounded(blueRedIndx.size());
        basketVec[blueRedIndx[randBlueIndx]].subBlueBall(1);
        basketVec[blueRedIndx[randBlueIndx]].setChangesFlag(1 << 6);
        blueRedIndx.removeAt(randBlueIndx);
    }

    if(redIndx.size() != 0 && blueRedIndx.size() != 0){
        randInt = QRandomGenerator::global()->bounded(2);
        if(randInt == 0)
        {
            randRedIndx = QRandomGenerator::global()->bounded(blueRedIndx.size());
            basketVec[blueRedIndx[randRedIndx]].subRedBall(1);
            basketVec[blueRedIndx[randRedIndx]].setChangesFlag(1 << 6);
        }
        else
        {
            randRedIndx = QRandomGenerator::global()->bounded(redIndx.size());
            basketVec[redIndx[randRedIndx]].subRedBall(1);
            basketVec[redIndx[randRedIndx]].setChangesFlag(1 << 6);
        }
    }
    else if( redIndx.size() != 0 && blueRedIndx.size() == 0)
    {
        randRedIndx = QRandomGenerator::global()->bounded(redIndx.size());
        basketVec[redIndx[randRedIndx]].subRedBall(1);
        basketVec[redIndx[randRedIndx]].setChangesFlag(1 << 6);
    }
    else if(redIndx.size() == 0 && blueRedIndx.size() != 0)
    {
        randRedIndx = QRandomGenerator::global()->bounded(blueRedIndx.size());
        basketVec[blueRedIndx[randRedIndx]].subRedBall(1);
        basketVec[blueRedIndx[randRedIndx]].setChangesFlag(1 << 6);
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
    else if(changesFlag & 1 << 10)
    {
        return "Последнее действие: добавили синий шар";
    }
    else if(changesFlag & 1 << 11)
    {
        return "Последнее действие: добавили красный шар";
    }
    else
    {
        return "Последнее действие: none";
    }
    return "";
}


void Baskets::replaceBall(QVector<Baskets> & basketVec, int indx)
{
    int randInt = 0;
    int insertIndx = getRandomSelectBasketExcept(basketVec, indx);
    if (basketVec[indx].getCountBlueBalls() >= 1 || basketVec[indx].getCountRedBalls() >= 1)
    {
        randInt = QRandomGenerator::global()->bounded(1, 101);
        if (randInt <= basketVec[indx].getProcentGetBlueBall())
        {
            basketVec[indx].subBlueBall(1);
            basketVec[insertIndx].addBlueBall(1);
            basketVec[indx].setChangesFlag( 1 << 0);
            basketVec[insertIndx].setChangesFlag(1 << 10);
        }
        else if(randInt > basketVec[indx].getProcentGetBlueBall())
        {
            basketVec[indx].subRedBall(1);
            basketVec[insertIndx].addRedBall(1);
            basketVec[indx].setChangesFlag(1 << 1);
            basketVec[insertIndx].setChangesFlag(1 << 11);
        }
    }
}

void Baskets::processTwoBlue(QVector<Baskets> & basketVec, int randInt){
    changesFlag = changesFlag ^ (1 << 2);

    subTwoBlueBalls(basketVec, randInt);
}

void Baskets::processTwoRed(QVector<Baskets> & basketVec, int randInt){
    changesFlag = changesFlag ^ (1 << 3);

    subTwoRedBalls(basketVec, randInt);
}

void Baskets::processMixed(QVector<Baskets> & basketVec, int randInt){
    changesFlag = changesFlag ^ (1 << 4);

    if(randInt >= 0 && randInt < basketVec.size())
    {
        subMixedBallsOneBasket(basketVec, randInt);
    }
    else if(randInt == basketVec.size())
    {
        subMixedBallsTwoBasket(basketVec, randInt);
    }
}

void Baskets::replaceTwoBalls(QVector<Baskets> & basketVec)
{
    if (allCountAllBaskets(basketVec) >= 2)
    {
        setRandomChangesFlag(basketVec);

        unsigned int randInt = getCorrectRandInt(basketVec);
        //0 = вычетает 2 шара из первой корзины
        //1 = вычетает 2 шара из второй корзины
        //2 = вычетает 1 шар из первой корзины и 1 шар из второй

        if (changesFlag & 1 << 2)
        {
            processTwoBlue(basketVec, randInt);                   //вычетает 2 синих шара
        }
        else if (changesFlag & 1 << 3)
        {
            processTwoRed(basketVec, randInt);                    //вычетает 2 красных шара
        }
        else if (changesFlag & 1 << 4)
        {
            processMixed(basketVec, randInt);                     //вычетает 2 смешанных шара
        }
    }
}

void Baskets::determintaeReplaceTwoBalls(QVector<Baskets>& basketVec, short dChangesFlag, int dRandInt){
    if (dChangesFlag & 1 << 2)
    {
        processTwoBlue(basketVec, dRandInt);                   //вычетает 2 синих шара
    }
    else if (dChangesFlag & 1 << 3)
    {
        processTwoRed(basketVec, dRandInt);                    //вычетает 2 красных шара
    }
    else if (dChangesFlag & 1 << 4)
    {
        processMixed(basketVec, dRandInt);                     //вычетает 2 смешанных шара
    }
}

