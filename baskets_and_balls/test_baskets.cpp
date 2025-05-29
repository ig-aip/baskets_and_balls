#include <QtTest>
#include "baskets.h"
#include "QVector"


class TestBaskets : public QObject
{
    Q_OBJECT

private slots:
    void testInitialization();
    void testReplaceBall();
    void testTwoBallsRemov();
    void testDefoultRemovTwoBalls();
    void testHardProcent();
    void testSetChangesFlag();
    void testRmTwoBlueBalls();
    void testRmTwoRedBalls();
    void testRmTwoMixedBalls();
    void testCycleReplaceTwo();
    void testGetCorrectRandInt();
};

void TestBaskets::testCycleReplaceTwo(){
    Baskets buffer;
    QVector<Baskets> basketVector{Baskets{20, 20}, Baskets{20, 20}, Baskets{20, 20}, Baskets{20, 20}};
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);
    buffer.replaceTwoBalls(basketVector);

    QVERIFY(buffer.allCountAllBaskets(basketVector)  == 0);
}

void TestBaskets::testInitialization()
{
    Baskets buffer;
    QVector<Baskets> basketVector{Baskets{5, 3}, Baskets{3, 5}};

    QCOMPARE(buffer.allCountAllBaskets(basketVector), 16);
    QCOMPARE(buffer.allCountBlueBalls(basketVector), 8);
    QCOMPARE(buffer.allCountRedBalls(basketVector), 8);
}

void TestBaskets::testReplaceBall()
{
    Baskets buffer;
    QVector<Baskets> basketVector{Baskets{5, 4}, Baskets{1, 2}};

    int oldFirst = basketVector[0].getAllCount();
    int oldSecond = basketVector[1].getAllCount();

    basketVector[0].replaceBall(basketVector, 0);

    QCOMPARE(basketVector[0].getAllCount() + basketVector[1].getAllCount(), (oldFirst + oldSecond));
    QVERIFY(basketVector[0].getAllCount() == oldFirst - 1 || basketVector[1].getAllCount() == oldSecond + 1);
}

void TestBaskets::testHardProcent(){
    Baskets buffer;
    QVector<Baskets> basketVector{Baskets{3, 1}, Baskets{2, 2}};

    QCOMPARE(basketVector[0].getProcentGetBlueBall(), 75);
    QCOMPARE(basketVector[1].getProcentGetRedBall(), 50);
    QCOMPARE(buffer.getAllProcentGetBlueBall(basketVector), 36);
    QCOMPARE(buffer.getAllProcentGetRedBall(basketVector), 11);
    QCOMPARE(buffer.getProcentOneRedOneBlueBalls(basketVector), 53);
}

void TestBaskets::testSetChangesFlag(){
    Baskets buffer;
    QVector<Baskets> basketVector{Baskets{0, 1}, Baskets{0, 0}, Baskets{0, 1}};

    buffer.setRandomChangesFlag(basketVector);
    QCOMPARE(buffer.getChangesFlag(), 1 << 3);

    QVector<Baskets> basketVector1{Baskets{1, 0}, Baskets{0, 0}, Baskets{1, 0}};

    buffer.setRandomChangesFlag(basketVector1);
    QCOMPARE(buffer.getChangesFlag(), 1 << 2);

    QVector<Baskets> basketVector2{Baskets{1, 0}, Baskets{0, 0}, Baskets{0 , 1}};

    buffer.setRandomChangesFlag(basketVector2);
    QCOMPARE(buffer.getChangesFlag(), 1 << 4);

    QVector<Baskets> basketVector3{Baskets{0, 1}, Baskets{0, 0}, Baskets{1 , 0}};

    buffer.setRandomChangesFlag(basketVector3);
    QCOMPARE(buffer.getChangesFlag(), 1 << 4);
}

void TestBaskets::testTwoBallsRemov(){
    Baskets buffer;
    QVector<Baskets> basketVector{Baskets{4, 4}, Baskets{4, 4}, Baskets{4, 4}};
    int initialTotal = buffer.allCountAllBaskets(basketVector);

    buffer.replaceTwoBalls(basketVector);

    QCOMPARE(initialTotal - buffer.allCountAllBaskets(basketVector), 2);
}


void TestBaskets::testDefoultRemovTwoBalls(){
    Baskets buffer;
    QVector<Baskets> basketVector{Baskets{0, 0}, Baskets{0, 0}, Baskets{0, 0}};

    buffer.replaceTwoBalls(basketVector);
    QCOMPARE(buffer.allCountAllBaskets(basketVector), 0);

    QVector<Baskets> basketVector1{Baskets{1, 0}, Baskets{0, 0}, Baskets{0, 0}, Baskets{0, 1}};

    buffer.replaceTwoBalls(basketVector1);
    QCOMPARE(buffer.allCountAllBaskets(basketVector1), 0);
}



void TestBaskets::testRmTwoBlueBalls(){
    Baskets buffer;
    QVector<Baskets> basketVector{Baskets{1, 1}, Baskets{1, 1}, Baskets{1, 1}};

    buffer.determintaeReplaceTwoBalls(basketVector, 1 << 2, basketVector.size());
    QCOMPARE(buffer.allCountBlueBalls(basketVector), 1);

    QVector<Baskets> basketVector1{Baskets{2, 1}, Baskets{2, 1}, Baskets{2, 1}};

    buffer.determintaeReplaceTwoBalls(basketVector1, 1 << 2, 0);
    QCOMPARE(buffer.allCountBlueBalls(basketVector1), 4);

    buffer.determintaeReplaceTwoBalls(basketVector1, 1 << 2, 1);
    QCOMPARE(buffer.allCountBlueBalls(basketVector1), 2);

    buffer.determintaeReplaceTwoBalls(basketVector1, 1 << 2, 2);
    QCOMPARE(buffer.allCountBlueBalls(basketVector1), 0);
}


void TestBaskets::testRmTwoRedBalls(){
    Baskets buffer;
    QVector<Baskets> basketVector{Baskets{1, 1}, Baskets{1, 1}, Baskets{1, 1}};

    buffer.determintaeReplaceTwoBalls(basketVector, 1 << 3, basketVector.size());
    QCOMPARE(buffer.allCountRedBalls(basketVector), 1);

    QVector<Baskets> basketVector1{Baskets{1, 3}, Baskets{1, 3}, Baskets{1, 3}};

    buffer.determintaeReplaceTwoBalls(basketVector1, 1 << 3, 0);
    QCOMPARE(buffer.allCountRedBalls(basketVector1), 7);

    buffer.determintaeReplaceTwoBalls(basketVector1, 1 << 3, 1);
    QCOMPARE(buffer.allCountRedBalls(basketVector1), 5);

    buffer.determintaeReplaceTwoBalls(basketVector1, 1 << 3, 2);
    QCOMPARE(buffer.allCountRedBalls(basketVector1), 3);

    buffer.determintaeReplaceTwoBalls(basketVector1, 1 << 3, 3);
    QCOMPARE(buffer.allCountRedBalls(basketVector1), 1);
}


void TestBaskets::testRmTwoMixedBalls(){
    Baskets buffer;
    QVector<Baskets> basketVector{Baskets{1, 0}, Baskets{1, 1}, Baskets{0, 1}};

    buffer.determintaeReplaceTwoBalls(basketVector, 1 << 4, 1);
    QCOMPARE(basketVector[1].getAllCount(), 0);

    QVector<Baskets> basketVector1{Baskets{2, 1}, Baskets{1, 1}, Baskets{1, 2}};

    buffer.determintaeReplaceTwoBalls(basketVector1, 1 << 4, 0);
    QCOMPARE(buffer.allCountAllBaskets(basketVector1), 6);

    buffer.determintaeReplaceTwoBalls(basketVector1, 1 << 4, 1);
    QCOMPARE(buffer.allCountAllBaskets(basketVector1), 4);

    buffer.determintaeReplaceTwoBalls(basketVector1, 1 << 4, 2);
    QCOMPARE(buffer.allCountAllBaskets(basketVector1), 2);

    buffer.determintaeReplaceTwoBalls(basketVector1, 1 << 4, 3);
    QCOMPARE(buffer.allCountAllBaskets(basketVector1), 0);
}

void TestBaskets::testGetCorrectRandInt(){
    Baskets buffer;

    QVector<Baskets> basketVector{Baskets{2, 0}, Baskets{0, 0}, Baskets{0, 0}, Baskets{0, 0}};
    buffer.setRandomChangesFlag(basketVector);
    QCOMPARE(buffer.getCorrectRandInt(basketVector), 0);

    QVector<Baskets> basketVector1{Baskets{0, 0}, Baskets{2, 0}, Baskets{0, 0}, Baskets{0, 0}};
    buffer.setRandomChangesFlag(basketVector1);
    QCOMPARE(buffer.getCorrectRandInt(basketVector1), 1);

    QVector<Baskets> basketVector2{Baskets{0, 0}, Baskets{0, 0}, Baskets{2, 0}, Baskets{0, 0}};
    buffer.setRandomChangesFlag(basketVector2);
    QCOMPARE(buffer.getCorrectRandInt(basketVector2), 2);

    QVector<Baskets> basketVector3{Baskets{0, 0}, Baskets{0, 0}, Baskets{0, 0}, Baskets{2, 0}};
    buffer.setRandomChangesFlag(basketVector3);
    QCOMPARE(buffer.getCorrectRandInt(basketVector3), 3);

    QVector<Baskets> basketVector4{Baskets{1, 0}, Baskets{0, 0}, Baskets{0, 0}, Baskets{1, 0}};
    buffer.setRandomChangesFlag(basketVector4);
    QCOMPARE(buffer.getCorrectRandInt(basketVector4), 4);
}

QTEST_APPLESS_MAIN(TestBaskets)
#include "test_baskets.moc"
