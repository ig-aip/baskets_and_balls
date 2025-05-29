#include "baskets.h"
#include "QRandomGenerator"
#include "logcreater.h"


Baskets::Baskets() :   countBlueBalls(0), countRedBalls(0), allCount(0){}

Baskets::Baskets(int blueBalls, int redBalls) :   countBlueBalls(blueBalls), countRedBalls(redBalls), allCount(redBalls + blueBalls) {}


int Baskets::getCountBlueBalls() const { return countBlueBalls; }

int Baskets::getCountRedBalls() const { return countRedBalls; }

int Baskets::getAllCount() const { return allCount; }

void Baskets::setChangesFlag(const short changes) { changesFlag = changes; }

void Baskets::setRandomChangesFlag(const QVector<Baskets> & basketVec){
    int randInt = 0;
    randInt = QRandomGenerator::global()->bounded(1, 101);
    if (randInt <= getAllProcentGetBlueBall(basketVec) && (allCountBlueBalls(basketVec)) >= 2)
    {
        changesFlag =  RemoveTwoBlueMode; //Удалить 2 синих шара
    }
    else if ((getAllProcentGetBlueBall(basketVec) < randInt) && (randInt <= (getAllProcentGetRedBall(basketVec) + getAllProcentGetBlueBall(basketVec)))
               && (allCountRedBalls(basketVec)) >= 2)
    {
        changesFlag =  RemoveTwoRedMode; //Удалить 2 красных шара
    }
    else if (allCountBlueBalls(basketVec) >= 1 && allCountRedBalls(basketVec) >= 1)
    {
        changesFlag =  RemoveMixedMode; //Удалить 2 смешанных шара
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

    if(changesFlag == RemoveTwoBlueMode)
    {
        return basketVec[0].validTwoBlueBalls(basketVec);
    }
    else if(changesFlag == RemoveTwoRedMode)
    {
        return basketVec[0].validTwoRedBalls(basketVec);
    }
    else if(changesFlag == RemoveMixedMode)
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
            basketVec[randInt].setChangesFlag(MesgTwoBlueRemoved);
            setChangesFlag(MesgTwoBlueRemoved);
            indxForDo.first = randInt;

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
                setChangesFlag(MesgOneBlueRemoved);

                int randIndx = QRandomGenerator::global()->bounded(validIndx.size());
                basketVec[validIndx[randIndx]].subBlueBall(1);
                basketVec[validIndx[randIndx]].setChangesFlag(MesgOneBlueRemoved);
                indxForDo.first = validIndx[randIndx];

                validIndx.removeAt(randIndx);
                randIndx = QRandomGenerator::global()->bounded(validIndx.size());
                basketVec[validIndx[randIndx]].subBlueBall(1);
                basketVec[validIndx[randIndx]].setChangesFlag(MesgOneBlueRemoved);
                indxForDo.second = validIndx[randIndx];

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
            basketVec[randInt].setChangesFlag(MesgTwoRedRemoved);
            setChangesFlag(MesgTwoRedRemoved);
            indxForDo.first = randInt;
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
                setChangesFlag(MesgOneRedRemoved);

                int randIndx = QRandomGenerator::global()->bounded(validIndx.size());
                basketVec[validIndx[randIndx]].subRedBall(1);
                basketVec[validIndx[randIndx]].setChangesFlag(MesgOneRedRemoved);
                indxForDo.first = validIndx[randIndx];

                validIndx.removeAt(randIndx);
                randIndx = QRandomGenerator::global()->bounded(validIndx.size());
                basketVec[validIndx[randIndx]].subRedBall(1);
                basketVec[validIndx[randIndx]].setChangesFlag(MesgOneRedRemoved);
                indxForDo.second = validIndx[randIndx];

                return;
            }
        }
    }
}

void Baskets::subMixedBallsOneBasket(QVector<Baskets> & basketVec, int randInt){
    basketVec[randInt].subBlueBall(1);
    basketVec[randInt].subRedBall(1);
    basketVec[randInt].setChangesFlag(MesgMixedRemoved);
    setChangesFlag(MesgMixedRemoved);
    indxForDo.first = randInt;
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
            setChangesFlag(MesgTwoMixedRemoved);
            randBlueIndx = QRandomGenerator::global()->bounded(blueRedIndx.size());
            basketVec[blueRedIndx[randBlueIndx]].subBlueBall(1);
            basketVec[blueRedIndx[randBlueIndx]].setChangesFlag(MesgOneBlueRemoved);
            indxForDo.first = blueRedIndx[randBlueIndx];
            blueRedIndx.removeAt(randBlueIndx);
        }
        else
        {
            setChangesFlag(MesgTwoMixedRemoved);
            randBlueIndx = QRandomGenerator::global()->bounded(blueIndx.size());
            basketVec[blueIndx[randBlueIndx]].subBlueBall(1);
            basketVec[blueIndx[randBlueIndx]].setChangesFlag(MesgOneBlueRemoved);
            indxForDo.second = blueIndx[randBlueIndx];
        }
    }
    else if( blueIndx.size() != 0 && blueRedIndx.size() == 0)
    {
        setChangesFlag(MesgTwoMixedRemoved);
        randBlueIndx = QRandomGenerator::global()->bounded(blueIndx.size());
        basketVec[blueIndx[randBlueIndx]].subBlueBall(1);
        basketVec[blueIndx[randBlueIndx]].setChangesFlag(MesgOneBlueRemoved);
        indxForDo.first = blueIndx[randBlueIndx];
    }
    else if(blueIndx.size() == 0 && blueRedIndx.size() != 0)
    {
        setChangesFlag(MesgTwoMixedRemoved);
        randBlueIndx = QRandomGenerator::global()->bounded(blueRedIndx.size());
        basketVec[blueRedIndx[randBlueIndx]].subBlueBall(1);
        basketVec[blueRedIndx[randBlueIndx]].setChangesFlag(MesgOneBlueRemoved);
        indxForDo.first = blueRedIndx[randBlueIndx];
        blueRedIndx.removeAt(randBlueIndx);
    }

    if(redIndx.size() != 0 && blueRedIndx.size() != 0){

        randInt = QRandomGenerator::global()->bounded(2);
        if(randInt == 0)
        {
            setChangesFlag(MesgTwoMixedRemoved);
            randRedIndx = QRandomGenerator::global()->bounded(blueRedIndx.size());
            basketVec[blueRedIndx[randRedIndx]].subRedBall(1);
            basketVec[blueRedIndx[randRedIndx]].setChangesFlag(MesgOneRedRemoved);
            indxForDo.second = blueRedIndx[randRedIndx];
        }
        else
        {
            setChangesFlag(MesgTwoMixedRemoved);
            randRedIndx = QRandomGenerator::global()->bounded(redIndx.size());
            basketVec[redIndx[randRedIndx]].subRedBall(1);
            basketVec[redIndx[randRedIndx]].setChangesFlag(MesgOneRedRemoved);
            indxForDo.second = redIndx[randRedIndx];
        }
    }
    else if( redIndx.size() != 0 && blueRedIndx.size() == 0)
    {
        setChangesFlag(MesgTwoMixedRemoved);
        randRedIndx = QRandomGenerator::global()->bounded(redIndx.size());
        basketVec[redIndx[randRedIndx]].subRedBall(1);
        basketVec[redIndx[randRedIndx]].setChangesFlag(MesgOneRedRemoved);
        indxForDo.second = redIndx[randRedIndx];
    }
    else if(redIndx.size() == 0 && blueRedIndx.size() != 0)
    {
        setChangesFlag(MesgTwoMixedRemoved);
        randRedIndx = QRandomGenerator::global()->bounded(blueRedIndx.size());
        basketVec[blueRedIndx[randRedIndx]].subRedBall(1);
        basketVec[blueRedIndx[randRedIndx]].setChangesFlag(MesgOneRedRemoved);
        indxForDo.second = blueRedIndx[randRedIndx];
    }
}


const char *Baskets::getLustChanges() const
{   
    if (changesFlag & MoveBlue)
    {
        return "Последнее действие: извлекли синий шар";
    }
    else if (changesFlag & MoveRed)
    {
        return "Последнее действие: извлекли красный шар";
    }
    else if (changesFlag & MesgTwoBlueRemoved)
    {
        return "Последнее действие: извлекли 2 синих шара";
    }
    else if (changesFlag & MesgOneBlueRemoved)
    {
        return "Последнее действие: извлекли 1 синий шар";
    }
    else if (changesFlag & MesgTwoRedRemoved)
    {
        return "Последнее действие: извлекли 2 красных шара";
    }
    else if (changesFlag & MesgOneRedRemoved)
    {
        return "Последнее действие: извлекли 1 красный шар";
    }
    else if (changesFlag & MesgMixedRemoved)
    {
        return "Последнее действие: извлекли 1 синий и 1 красный шар";
    }
    else if(changesFlag & MesgBlueAdded)
    {
        return "Последнее действие: добавили синий шар";
    }
    else if(changesFlag & MesgRedAdded)
    {
        return "Последнее действие: добавили красный шар";
    }
    else
    {
        return "Последнее действие: none";
    }
    return "";
}

//Логи

void Baskets::setLogOneBall(logCreater & logLustTime, logCreater & logAllTime){
    if(indxForDo.first >= 0 && indxForDo.second >= 0)
    {
        if(changesFlag == MoveBlue)
        {
            changesFlag = changesFlag ^ (MoveBlue);
            logLustTime.message(QString("Был перетащен синий шар из %1 корзины во %2 корзину").arg(indxForDo.first + 1).arg(indxForDo.second + 1));
            logAllTime.message(QString("Был перетащен синий шар из %1 корзины во %2 корзину").arg(indxForDo.first + 1).arg(indxForDo.second + 1));

            indxForDo.first = -1; indxForDo.second = -1;
        }
        else if(changesFlag == MoveRed)
        {
            changesFlag = changesFlag ^ (MoveRed);
            logLustTime.message(QString("Был перетащен крансый шар из %1 корзины во %2 корзину").arg(indxForDo.first + 1).arg(indxForDo.second + 1));
            logAllTime.message(QString("Был перетащен крансый шар из %1 корзины во %2 корзину").arg(indxForDo.first + 1).arg(indxForDo.second + 1));

            indxForDo.first = -1; indxForDo.second = -1;
        }
    }
}

void Baskets::setLogTwoBall(logCreater & logLustTime, logCreater & logAllTime){
    if(indxForDo.first >= 0 || indxForDo.second >= 0)
    {
        if(changesFlag == MesgTwoBlueRemoved){
            changesFlag = changesFlag ^ (MesgTwoBlueRemoved);
            logLustTime.message(QString("Было удалено 2 синих шара из %1 корзины.").arg(indxForDo.first + 1));
            logAllTime.message(QString("Было удалено 2 синих шара из %1 корзины.").arg(indxForDo.first + 1));

            indxForDo.first = -1; indxForDo.second = -1;
        }
        else if(changesFlag == MesgOneBlueRemoved)
        {
            changesFlag = changesFlag ^ (MesgOneBlueRemoved);
            logLustTime.message(QString("Было удалено по 1-ному синему шару из коризины %1 и из корзины %2.").arg(indxForDo.first + 1).arg(indxForDo.second + 1));
            logAllTime.message(QString("Было удалено по 1-ному синему шару из коризины %1 и из корзины %2.").arg(indxForDo.first + 1).arg(indxForDo.second + 1));

            indxForDo.first = -1; indxForDo.second = -1;
        }
        else if(changesFlag == MesgTwoRedRemoved){
            changesFlag = changesFlag ^ (MesgTwoRedRemoved);
            logLustTime.message(QString("Было удалено 2 красных шара из %1 корзины.").arg(indxForDo.first + 1));
            logAllTime.message(QString("Было удалено 2 красных шара из %1 корзины.").arg(indxForDo.first + 1));

            indxForDo.first = -1; indxForDo.second = -1;
        }
        else if(changesFlag == MesgOneRedRemoved){
            changesFlag = changesFlag ^ (MesgOneRedRemoved);
            logLustTime.message(QString("Было удалено по 1-ному красному шару из коризины %1 и из корзины %2.").arg(indxForDo.first + 1).arg(indxForDo.second + 1));
            logAllTime.message(QString("Было удалено по 1-ному красному шару из коризины %1 и из корзины %2.").arg(indxForDo.first + 1).arg(indxForDo.second + 1));

            indxForDo.first = -1; indxForDo.second = -1;
        }
        else if(changesFlag == MesgMixedRemoved){
            changesFlag = changesFlag ^ (MesgMixedRemoved);
            logLustTime.message(QString("Были удалены 1 синий 1 красный шар из %1 корзины.").arg(indxForDo.first + 1));
            logAllTime.message(QString("Были удалены 1 синий 1 красный шар из %1 корзины.").arg(indxForDo.first + 1));

            indxForDo.first = -1; indxForDo.second = -1;
        }
        else if(changesFlag == MesgTwoMixedRemoved){
            changesFlag = changesFlag ^ (MesgTwoMixedRemoved);
            logLustTime.message(QString("Был удалён синий шар из корзины %1 и красный шар из корзины %2.").arg(indxForDo.first + 1).arg(indxForDo.second + 1));
            logAllTime.message(QString("Был удалён синий шар из корзины %1 и красный шар из корзины %2.").arg(indxForDo.first + 1).arg(indxForDo.second + 1));

            indxForDo.first = -1; indxForDo.second = -1;
        }
    }
}

void Baskets::startSettingsLog(QVector<Baskets> & basketVec, logCreater & logLustTime, logCreater & logAllTime){
    QString str = "";

    for(int i = 0; i < basketVec.size(); ++i){
        str = str + QString(" { b:%1, r:%2 } ").arg(basketVec[i].getCountBlueBalls()).arg(basketVec[i].getCountRedBalls());
    }
    logLustTime.message(str);
    logAllTime.message(str);
}

void Baskets::replaceBall(QVector<Baskets> & basketVec, int indx)
{
    if(basketVec[indx].getAllCount() >= 1)
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
                basketVec[indx].setChangesFlag( MoveBlue);
                setChangesFlag(MoveBlue);
                basketVec[insertIndx].setChangesFlag(MesgBlueAdded);
                indxForDo.first = indx;
                indxForDo.second = insertIndx;
            }
            else if(randInt > basketVec[indx].getProcentGetBlueBall())
            {
                basketVec[indx].subRedBall(1);
                basketVec[insertIndx].addRedBall(1);
                basketVec[indx].setChangesFlag(MoveRed);
                setChangesFlag(MoveRed);
                basketVec[insertIndx].setChangesFlag(MesgRedAdded);
                indxForDo.first = indx;
                indxForDo.second = insertIndx;
            }
        }
    }else{
        indxForDo.first = -1;
        indxForDo.second = -1;
    }
}

void Baskets::processTwoBlue(QVector<Baskets> & basketVec, int randInt){
    changesFlag = changesFlag ^ (RemoveTwoBlueMode);

    subTwoBlueBalls(basketVec, randInt);
}

void Baskets::processTwoRed(QVector<Baskets> & basketVec, int randInt){
    changesFlag = changesFlag ^ (RemoveTwoRedMode);

    subTwoRedBalls(basketVec, randInt);
}

void Baskets::processMixed(QVector<Baskets> & basketVec, int randInt){
    changesFlag = changesFlag ^ (RemoveMixedMode);
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

        if (changesFlag & RemoveTwoBlueMode)
        {
            processTwoBlue(basketVec, randInt);                   //вычетает 2 синих шара
        }
        else if (changesFlag & RemoveTwoRedMode)
        {
            processTwoRed(basketVec, randInt);                    //вычетает 2 красных шара
        }
        else if (changesFlag & RemoveMixedMode)
        {
            processMixed(basketVec, randInt);                     //вычетает 2 смешанных шара
        }
    }
}

void Baskets::determintaeReplaceTwoBalls(QVector<Baskets>& basketVec, short dChangesFlag, int dRandInt){
    if (dChangesFlag & RemoveTwoBlueMode)
    {
        processTwoBlue(basketVec, dRandInt);                   //вычетает 2 синих шара
    }
    else if (dChangesFlag & RemoveTwoRedMode)
    {
        processTwoRed(basketVec, dRandInt);                    //вычетает 2 красных шара
    }
    else if (dChangesFlag & RemoveMixedMode)
    {
        processMixed(basketVec, dRandInt);                     //вычетает 2 смешанных шара
    }
}

