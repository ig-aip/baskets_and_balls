#include "iostream"
#ifndef BASKETS_H
#define BASKETS_H
#include "QRandomGenerator"
class Baskets
{
private:
    int countBlueBalls;
    int countRedBalls;
    int allCount;
    int procentBlueBall;
    int procentRedBall;
    short changesFlag = 0;
    //00000000 00000000 none
    //10000000 00000000 blue ball
    //01000000 00000000 red ball
    //00100000 00000000 mode sub 2 blue balls
    //00010000 00000000 mode sub 2 red balls
    //00001000 00000000 mode sub 1 blue and 1 red balls
    //00000100 00000000 message sub 2 blue ball in first basket
    //00000010 00000000 message sub 1 blue ball in first and 1 blue ball in second basket
    //00000001 00000000 message sub 2 red ball  int first basket
    //00000000 10000000 message sub 1 red in first 1 red in second

public:
    Baskets()
        : countBlueBalls(0)
        , countRedBalls(0)
        , allCount(0)
    {}

    Baskets(int blueBalls, int redBalls)
        : countBlueBalls(blueBalls)
        , countRedBalls(redBalls)
        , allCount(redBalls + blueBalls)
    {}

    int getCountBlueBalls() const { return countBlueBalls; }

    int getCountRedBalls() const { return countRedBalls; }

    int getAllCount() const { return allCount; }

    void setChangesFlag(short changes) { changesFlag = changes; }

    int AllCountBlueBalls(Baskets &second) const
    {
        return getCountBlueBalls() + second.getCountBlueBalls();
    }

    int AllCountRedBalls(Baskets &second) const
    {
        return getCountRedBalls() + second.getCountRedBalls();
    }

    //получение процентов в корзине
    int getProcentGetBlueBall() const
    {
        if (countBlueBalls == 0) {
            return 0;
        }

        double procent = (((double) countBlueBalls / (double) allCount)) * 100;
        if ((procent - (int) procent) >= 0.5) {
            return (int) procent + 1;
        }
        return (int) procent;
    }
    int getAllProcentGetBlueBall(Baskets &second) const
    {
        if ((countBlueBalls + second.countBlueBalls) < 2) {
            return 0;
        }

        double allProcentBlueBalls = ((double) (AllCountBlueBalls(second))
                                      / (double) (allCount + second.allCount))
                                     * 100;
        if ((allProcentBlueBalls - (int) allProcentBlueBalls) >= 0.5) {
            allProcentBlueBalls += 1;
        }
        allProcentBlueBalls = ((int) allProcentBlueBalls * (int) allProcentBlueBalls) / 100;

        return (int) allProcentBlueBalls;
    }

    int getProcentGetRedBall() const
    {
        if (countRedBalls == 0) {
            return 0;
        }

        double procent = (((double) countRedBalls / (double) allCount)) * 100;
        if ((procent - (int) procent) >= 0.5) {
            return (int) procent + 1;
        }
        return (int) procent;
    }
    int getAllProcentGetRedBall(Baskets &second) const
    {
        if ((AllCountRedBalls(second)) < 2) {
            return 0;
        }

        double allProcentRedBalls = ((double) (AllCountRedBalls(second))
                                     / (double) (allCount + second.allCount))
                                    * 100;
        if ((allProcentRedBalls - (int) allProcentRedBalls) >= 0.5) {
            allProcentRedBalls += 1;
        }
        allProcentRedBalls = ((int) allProcentRedBalls * (int) allProcentRedBalls) / 100;

        return (int) allProcentRedBalls;
    }

    int getProcentOneRedOneBlueBalls(Baskets &second) const
    {
        if ((getAllProcentGetBlueBall(second) + getAllProcentGetRedBall(second)) == 0) {
            return 0;
        }
        int procentOneRedOneBlue = 100
                                   - (getAllProcentGetBlueBall(second)
                                      + getAllProcentGetRedBall(second));

        return procentOneRedOneBlue;
    }

    //базовые добавить убавить количество шаров без проверки
    void addBlueBall(int countBalls)
    {
        countBlueBalls = countBlueBalls + countBalls;
        allCount += countBalls;
    }
    void subBlueBall(int countBalls)
    {
        countBlueBalls = countBlueBalls - countBalls;
        allCount -= countBalls;
    }

    void addRedBall(int countBalls)
    {
        countRedBalls = countRedBalls + countBalls;
        allCount += countBalls;
    }
    void subRedBall(int countBalls)
    {
        countRedBalls = countRedBalls - countBalls;
        allCount -= countBalls;
    }

    void replaceBall(Baskets &second)
    {
        int randInt = 0;

        if ((countBlueBalls || countRedBalls) != 0) {
            randInt = QRandomGenerator::global()->bounded(1, 101);
            if (randInt <= getProcentGetBlueBall()) {
                subBlueBall(1);
                second.addBlueBall(1);
                changesFlag = 1 << 0;
            } else {
                subRedBall(1);
                second.addRedBall(1);
                changesFlag = 1 << 1;
            }
        }
    }

    const char *getLustChanges() const
    {
        if (changesFlag & 1 << 0) {
            return "Последнее действие: извлекли синий шар";
        } else if (changesFlag & 1 << 1) {
            return "Последнее действие: извлекли красный шар";
        } else if (changesFlag & 1 << 5) {
            return "Последнее действие: извлекли 2 синих шара";
        } else if (changesFlag & 1 << 6) {
            return "Последнее действие: извлекли 1 синий шар";
        } else if (changesFlag & 1 << 7) {
            return "Последнее действие: извлекли 2 красных шара";

        } else if (changesFlag & 1 << 8) {
            return "Последнее действие: извлекли 1 красный шар";

        } else if (changesFlag & 1 << 9) {
            return "Последнее действие: извлекли 1 синий и 1 красный шар";
        } else {
            std::cout << changesFlag << std::endl;
            return "Последнее действие: none";
        }
        return "";
    }

    void replaceTwoBalls(Baskets &second)
    {
        if ((getAllCount() + second.getAllCount()) > 1) {
            int randInt = 0;
            randInt = QRandomGenerator::global()->bounded(1, 101);
            if (randInt <= getAllProcentGetBlueBall(second) && (AllCountBlueBalls(second)) >= 2) {
                changesFlag = changesFlag | 1 << 2; //sub 2 blue balls

            } else if ((getAllProcentGetBlueBall(second) < randInt)
                       && (randInt
                           <= (getAllProcentGetRedBall(second) + getAllProcentGetBlueBall(second)))
                       && (AllCountRedBalls(second)) >= 2) {
                changesFlag = changesFlag | 1 << 3; //sub 2 red balls
            } else if (AllCountBlueBalls(second) >= 1 && AllCountRedBalls(second) >= 1) {
                changesFlag = changesFlag | 1 << 4; //sub 1 blue 1 red balls
            }

            randInt = QRandomGenerator::global()->bounded(3);
            //0 = sub 2 balls in first basket
            //1 = sub 2 balls in second basket
            //2 = sub 1 ball in first basket and 1 ball in second
            if (second.getAllCount() == 0) {
                randInt = 0;
            } else if (getAllCount() == 0) {
                randInt = 1;
            } else if (getAllCount() == 1 && second.getAllCount() == 1) {
                randInt = 2;
            }

            if (changesFlag & 1 << 2) {
                changesFlag = changesFlag ^ (1 << 2);
                randInt = QRandomGenerator::global()->bounded(3);
                if (randInt == 0 && (getCountBlueBalls() <= 2)) {
                    if (getCountBlueBalls() == 0) {
                        randInt = 1;
                    }
                    if (getCountBlueBalls() == 1) {
                        randInt = 2;
                    }
                } else if (randInt == 1 && second.getCountBlueBalls() <= 2) {
                    if (second.getCountBlueBalls() == 0) {
                        randInt = 0;
                    }
                    if (second.getCountBlueBalls() == 1) {
                        randInt = 2;
                    }
                } else if (randInt == 2
                           && (getCountBlueBalls() == 0 || second.getCountBlueBalls() == 0)) {
                    if (getCountBlueBalls() == 0) {
                        randInt = 1;
                    } else {
                        randInt = 0;
                    }
                }

                if (randInt == 0 && (getCountBlueBalls() >= 2)) {
                    subBlueBall(2); //sub 2 blue ball in first basket
                    changesFlag = 1 << 5;
                } else if (randInt == 1 && (second.getCountBlueBalls() >= 2)) {
                    second.subBlueBall(2); //sub 2 blue ball in second basket
                    second.setChangesFlag(1 << 5);
                } else if (randInt == 2 && (getCountBlueBalls() >= 1)
                           && (second.getCountBlueBalls() >= 1)) {
                    subBlueBall(1); //sub 1 blue ball in first and 1 blue ball in second basket
                    second.subBlueBall(1);
                    changesFlag = 1 << 6;
                    second.setChangesFlag(1 << 6);
                }
            } else if (changesFlag & 1 << 3) {
                changesFlag = changesFlag ^ (1 << 3);
                if (randInt == 0 && (countRedBalls <= 2)) {
                    if (countRedBalls == 0) {
                        randInt = 1;
                    }
                    if (countRedBalls == 1) {
                        randInt = 2;
                    }
                } else if (randInt == 1 && second.getCountRedBalls() <= 2) {
                    if (second.getCountRedBalls() == 0) {
                        randInt = 0;
                    }
                    if (second.getCountRedBalls() == 1) {
                        randInt = 2;
                    }
                } else if (randInt == 2 && (countRedBalls == 0 || second.getCountRedBalls() == 0)) {
                    if (countRedBalls == 0) {
                        randInt = 1;
                    } else {
                        randInt = 0;
                    }
                }

                if (randInt == 0 && (countRedBalls >= 2)) {
                    subRedBall(2); //sub 2 red ball in first basket
                    changesFlag = 1 << 7;

                } else if (randInt == 1 && (second.getCountRedBalls() >= 2)) {
                    second.subRedBall(2); //sub 2 red ball in second basket
                    second.setChangesFlag(1 << 7);

                } else if (randInt == 2 && (countRedBalls >= 1)
                           && (second.getCountRedBalls() >= 1)) {
                    subRedBall(1); //sub 1 red ball in first and 1 red ball in second basket
                    second.subRedBall(1);
                    changesFlag = 1 << 8;
                    second.setChangesFlag(1 << 8);
                }
            } else if (changesFlag & 1 << 4) {
                changesFlag = changesFlag ^ (1 << 4);

                if (second.getAllCount() == 0)
                    randInt = 0;
                else if (getAllCount() == 0)
                    randInt = 1;
                else if (getAllCount() == 1 && second.getAllCount() == 1)
                    randInt = 2;
                else
                    randInt = QRandomGenerator::global()->bounded(3);

                if (randInt == 0) {
                    if (countBlueBalls > 0 && countRedBalls > 0) {
                        subBlueBall(1); //sub 1 blue, 1 red ball in first basket
                        subRedBall(1);
                        changesFlag = 1 << 9;
                    } else {
                        if (countBlueBalls == 0 && countRedBalls == 0) {
                            second.subBlueBall(1);
                            second.subRedBall(1);
                            second.setChangesFlag(1 << 9);
                        } else if (countBlueBalls == 0) {
                            subRedBall(1);
                            second.subBlueBall(1);
                            changesFlag = 1 << 8;
                            second.setChangesFlag(1 << 6);
                        } else if (countRedBalls == 0) {
                            subBlueBall(1);
                            second.subRedBall(1);
                            changesFlag = 1 << 6;
                            second.setChangesFlag(1 << 8);
                        }
                    }
                }
                if (randInt == 1) {
                    if (second.getCountBlueBalls() > 0 && second.getCountRedBalls() > 0) {
                        second.subBlueBall(1); //sub 1 blue, 1 red ball in second basket
                        second.subRedBall(1);
                        second.setChangesFlag(1 << 9);
                    } else {
                        if (second.getCountBlueBalls() == 0 && second.getCountRedBalls() == 0) {
                            subBlueBall(1);
                            subRedBall(1);
                            changesFlag = 1 << 9;
                        } else if (second.getCountBlueBalls() == 0) {
                            second.subRedBall(1);
                            subBlueBall(1);
                            second.setChangesFlag(1 << 8);
                            changesFlag = 1 << 6;
                        } else if (second.getCountRedBalls() == 0) {
                            second.subBlueBall(1);
                            subRedBall(1);
                            second.setChangesFlag(1 << 6);
                            changesFlag = 1 << 8;
                        }
                    }
                }
                if (randInt == 2) {
                    if ((countBlueBalls >= 1 && second.countRedBalls >= 1)
                        || (countRedBalls >= 1 && second.countBlueBalls >= 1)) {
                        if ((countBlueBalls >= 1 && second.countRedBalls >= 1)
                            && (countRedBalls >= 1 && second.countBlueBalls >= 1)) {
                            if (QRandomGenerator::global()->bounded(2) == 1) {
                                subBlueBall(1);
                                second.subRedBall(1);
                                changesFlag = 1 << 6;
                                second.setChangesFlag(1 << 8);
                            } else {
                                subRedBall(1);
                                second.subBlueBall(1);
                                changesFlag = 1 << 8;
                                second.setChangesFlag(1 << 6);
                            }
                        } else if (countBlueBalls >= 1 && second.countRedBalls >= 1) {
                            subBlueBall(1);
                            second.subRedBall(1);
                            changesFlag = 1 << 6;
                            second.setChangesFlag(1 << 8);
                        } else if (countRedBalls >= 1 && second.countBlueBalls >= 1) {
                            subRedBall(1);
                            second.subBlueBall(1);
                            changesFlag = 1 << 8;
                            second.setChangesFlag(1 << 6);
                        } else if (countBlueBalls == 0 || second.countRedBalls == 0) {
                            if (countBlueBalls == 0 && second.getCountRedBalls() == 0) {
                                second.subBlueBall(1);
                                subRedBall(1);
                                second.setChangesFlag(1 << 6);
                                changesFlag = 1 << 8;
                            } else if (countBlueBalls == 0 && second.getCountRedBalls() >= 1) {
                                second.subBlueBall(1);
                                second.subRedBall(1);
                                second.setChangesFlag(1 << 9);
                            } else if (countBlueBalls >= 1 && second.getCountRedBalls() == 0) {
                                subBlueBall(1);
                                subRedBall(1);
                                changesFlag = 1 << 9;
                            }
                        } else if (countRedBalls == 0 || second.getCountBlueBalls() == 0) {
                            if (countRedBalls == 0 && second.getCountBlueBalls() == 0) {
                                second.subRedBall(1);
                                subBlueBall(1);
                                second.setChangesFlag(1 << 8);
                                changesFlag = 1 << 6;
                            } else if (countRedBalls == 0 && second.getCountBlueBalls() >= 1) {
                                second.subBlueBall(1);
                                second.subRedBall(1);
                                second.setChangesFlag(1 << 9);
                            } else if (countRedBalls >= 1 && second.getCountBlueBalls() == 0) {
                                subBlueBall(1);
                                subRedBall(1);
                                changesFlag = 1 << 9;
                            }
                        }
                    }
                }
            }
        }
    }
};

#endif // BASKETS_H
