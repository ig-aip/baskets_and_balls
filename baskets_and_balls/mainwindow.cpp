#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "baskets.h"
#include "QLabel"
#include "QString"

Baskets first(2, 2);
Baskets second(0, 3);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    updateUI();
}

void MainWindow::updateUI() {
    ui->firstCountBalls->setText(QString("Шаров в корзине: %1").arg(first.getAllCount()));
    ui->firstCountBlueBalls->setText(QString("Синих шаров в корзине: %1").arg(first.getCountBlueBalls()));
    ui->firstCountRedBalls->setText(QString("Красных шаров в корзине: %1").arg(first.getCountRedBalls()));
    ui->firstProcentGetBlueBall->setText(QString("Вероятность достать синий шар: %1%").arg(first.getProcentGetBlueBall()));
    ui->firstProcentGetRedBall->setText(QString("Вероятность достать красный шар: %1%").arg(first.getProcentGetRedBall()));
    ui->firstLustChange->setText(first.getLustChanges());

    ui->secondCountBalls->setText(QString("Шаров в корзине: %1").arg(second.getAllCount()));
    ui->secondCountBlueBalls->setText(QString("Синих шаров в корзине: %1").arg(second.getCountBlueBalls()));
    ui->secondCountRedBalls->setText(QString("Красных шаров в корзине: %1").arg(second.getCountRedBalls()));
    ui->secondProcentGetBlueBall->setText(QString("Вероятность достать синий шар: %1%").arg(second.getProcentGetBlueBall()));
    ui->secondProcentGetRedBall->setText(QString("Вероятность достать красный шар: %1%").arg(second.getProcentGetRedBall()));
    ui->secondLustChange->setText(second.getLustChanges());

    ui->procentAllBlueBalls->setText(QString("Вероятность взять 2 синих шара: %1%").arg(first.getAllProcentGetBlueBall(second)));
    ui->procentAllRedBalls->setText(QString("Вероятность взять 2 красных шара: %1%").arg(first.getAllProcentGetRedBall(second)));
    ui->procentOneBlueOneRed->setText(QString("Вероятность взять 1 красный и 1 синий шар: %1%").arg(first.getProcentOneRedOneBlueBalls(second)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_firstReplaceBall_clicked()
{
    first.replaceBall(second);
    updateUI();
}


void MainWindow::on_secondReplaceBall_clicked()
{
    second.replaceBall(first);
    updateUI();
}


void MainWindow::on_subTwoButton_clicked()
{
    first.replaceTwoBalls(second);
    updateUI();
}

