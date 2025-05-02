#include <QtTest>
#include "baskets.h"

class TestBaskets : public QObject
{
    Q_OBJECT

private slots:
    void testInitialization();
    void testReplaceBall();
    void testTwoBallsRemov();
    void testDefoultRemovTwoBalls();
    void testHardProcentBlue();
    void testHardProcentRed();
    void testSetChangesFlag();
    void testRmTwoBlueBalls();
    void testRmTwoRedBalls();
    void testRmTwoMixedBalls();
};

void TestBaskets::testInitialization()
{
    Baskets first(5, 3);
    QCOMPARE(first.getCountBlueBalls(), 5);
    QCOMPARE(first.getCountRedBalls(), 3);
    QCOMPARE(first.getAllCount(), 8);
}

void TestBaskets::testReplaceBall()
{
    Baskets first(10, 5);
    Baskets second(2, 3);
    int oldFirst = first.getAllCount();
    int oldSecond = second.getAllCount();

    first.replaceBall(second);

    QCOMPARE(first.getAllCount() + second.getAllCount(), (oldFirst + oldSecond));
    QVERIFY(first.getAllCount() == oldFirst - 1 || second.getAllCount() == oldSecond + 1);
}

void TestBaskets::testHardProcentBlue(){
    Baskets first(3, 1);
    Baskets second(2, 2);

    QCOMPARE(first.getProcentGetBlueBall(), 75);
    QCOMPARE(second.getProcentGetRedBall(), 50);
    QCOMPARE(first.getAllProcentGetBlueBall(second), 39);
}

void TestBaskets::testHardProcentRed(){
    Baskets first(3, 1);
    Baskets second(2, 2);

    QCOMPARE(first.getProcentGetBlueBall(), 75);
    QCOMPARE(second.getProcentGetRedBall(), 50);
    QCOMPARE(first.getAllProcentGetRedBall(second), 14);
}

void TestBaskets::testSetChangesFlag(){
    Baskets first(0, 1);
    Baskets second(0, 1);

    first.setRandomChangesFlag(second);
    QCOMPARE(first.getChangesFlag(), 1 << 3);

    Baskets third(1, 0);
    Baskets fourth(1, 0);

    third.setRandomChangesFlag(fourth);
    QCOMPARE(third.getChangesFlag(), 1 << 2);

    Baskets fifth(1, 0);
    Baskets sixth(0, 1);

    fifth.setRandomChangesFlag(sixth);
    QCOMPARE(fifth.getChangesFlag(), 1 << 4);
}

void TestBaskets::testTwoBallsRemov(){
    Baskets first(4, 4);
    Baskets second(4, 4);
    int initialTotal = first.getAllCount() + second.getAllCount();

    first.replaceTwoBalls(second);

    QCOMPARE(initialTotal - (first.getAllCount() + second.getAllCount()), 2);
}


void TestBaskets::testDefoultRemovTwoBalls(){
    Baskets first;
    Baskets second;
    first.replaceTwoBalls(second);
    QCOMPARE(first.getAllCount() + second.getAllCount(), 0);

    Baskets third(1, 0);
    Baskets fourth(0, 1);
    third.replaceTwoBalls(fourth);
    QCOMPARE(third.getAllCount() + fourth.getAllCount(), 0);
}


//проверка на вычитание двух синих шаров при случайно не возможном выборе из корзин
void TestBaskets::testRmTwoBlueBalls(){
    Baskets first(1, 0);
    Baskets second(1, 0);

    first.determintaeReplaceTwoBalls(second, 1 << 2, 0);
    QCOMPARE(first.getCountBlueBalls() + second.getCountBlueBalls(), 0);

    Baskets third(1, 0);
    Baskets fourth(1, 0);

    third.determintaeReplaceTwoBalls(fourth, 1 << 2, 1);
    QCOMPARE(third.getCountBlueBalls() + fourth.getCountRedBalls(), 0);

    Baskets fifth(2, 0);
    Baskets sixth(0, 0);

    fifth.determintaeReplaceTwoBalls(sixth, 1 << 2, 2);
    QCOMPARE(fifth.getCountBlueBalls(), 0);
}

//проерка навычетание двух красных шаров при случайно не возможном выборе из корзин
void TestBaskets::testRmTwoRedBalls(){
    Baskets first(0, 1);
    Baskets second(0, 1);

    first.determintaeReplaceTwoBalls(second, 1 << 3, 0);
    QCOMPARE(first.getCountRedBalls() + second.getCountRedBalls(), 0);

    Baskets third(0, 1);
    Baskets fourth(0, 1);

    third.determintaeReplaceTwoBalls(fourth, 1 << 3, 1);
    QCOMPARE(third.getCountRedBalls() + fourth.getCountRedBalls(), 0);

    Baskets fifth(0, 0);
    Baskets sixth(2, 0);

    fifth.determintaeReplaceTwoBalls(sixth, 1 << 3, 2);
    QCOMPARE(fifth.getCountRedBalls(), 0);
}

//проерка навычетание двух смешанных шаров при случайно не возможном выборе из корзин
void TestBaskets::testRmTwoMixedBalls(){
    Baskets first(0, 0);
    Baskets second(1, 1);

    first.determintaeReplaceTwoBalls(second, 1 << 4, 0);
    QCOMPARE(second.getCountBlueBalls() + second.getCountRedBalls(), 0);

    Baskets third(1, 1);
    Baskets fourth(0, 0);

    third.determintaeReplaceTwoBalls(fourth, 1 << 4, 1);
    QCOMPARE(third.getCountBlueBalls() + third.getCountRedBalls(), 0);

    Baskets fifth(1, 1);
    Baskets sixth(0 , 0);

    fifth.determintaeReplaceTwoBalls(sixth, 1 << 4, 2);
    QCOMPARE(fifth.getCountBlueBalls() + fifth.getCountRedBalls(), 0);
}

QTEST_APPLESS_MAIN(TestBaskets)
#include "test_baskets.moc"
