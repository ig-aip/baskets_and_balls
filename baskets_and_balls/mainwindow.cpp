#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "baskets.h"
#include "QLabel"
#include "QString"
#include "QGridLayout"
#include "jsonloader.h"
#include "logcreater.h"

logCreater logLustTime("logLustTime.log");
logCreater logAllTime("logAllTime.log", 'a');

JsonLoader loader;
QVector<Baskets> basketVec = loader.loaderBasketes("parametrs.json");
Baskets buffer;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if(basketVec.size() < 2 || basketVec.size() > 4){ qFatal("error count baskets");}

    buffer.startSettingsLog(basketVec, logLustTime, logAllTime);
    createBasketsWidgets();
    updateUI();
}


void MainWindow::createBasketsWidgets(){
    QHBoxLayout* container = findChild<QHBoxLayout*>("basketsContainer");

    if (!container) {
        qFatal("Не найден basketsContainer в .ui!");
        return;
    }

    basketsLayOut = container->layout();

    for(int i = 0; i  < basketVec.size(); ++i){
        QGroupBox* groupBox = new QGroupBox(QString("%1-я корзина").arg(i + 1), this);
        QGridLayout* layout = new QGridLayout(groupBox);

        QLabel* countBalls = new QLabel(QString("Шаров в корзине: "), groupBox);
        QLabel* countBlueBalls = new QLabel(QString("Синих шаров в корзине: "), groupBox);
        QLabel* countRedBalls = new QLabel(QString("Красных шаров в корзине: "), groupBox);
        QLabel* procentGetBlueBalls = new QLabel(QString("Вероятность достать синий шар: "), groupBox);
        QLabel* procentGetRedBalls = new QLabel(QString("Вероятность достать красный шар: "), groupBox);
        QLabel* lustChange = new QLabel(QString("Последнее изменение: "), groupBox);
        QPushButton* btn = new QPushButton(QString("Переложить в случайную коробку"), this);
        GUIBasket* guiBasket = new GUIBasket(this);


        connect(btn, &QPushButton::clicked, this, &MainWindow::on_replaceBall_clicked);

        layout->addWidget(countBalls, 0 ,0);
        layout->addWidget(countBlueBalls, 1, 0);
        layout->addWidget(countRedBalls, 2, 0);
        layout->addWidget(procentGetBlueBalls, 3, 0);
        layout->addWidget(procentGetRedBalls, 4, 0);
        layout->addWidget(lustChange, 5, 0);

        basketLabels.push_back(groupBox);
        countAllLabels.push_back(countBalls);
        countBlueLabels.push_back(countBlueBalls);
        countRedLabels.push_back(countRedBalls);
        procentBlueLabels.push_back(procentGetBlueBalls);
        procentRedLabels.push_back(procentGetRedBalls);
        lustChangesLabels.push_back(lustChange);
        replaceOneBallButtons.push_back(btn);
        guiBaskets.push_back(guiBasket);

        QVBoxLayout* boxLayout = new QVBoxLayout();
        boxLayout->addWidget(groupBox);
        boxLayout->addWidget(btn);
        boxLayout->addWidget(guiBasket);

        QWidget* wrapper = new QWidget();
        wrapper->setLayout(boxLayout);


        basketsLayOut->addWidget(wrapper);
    }
}


void MainWindow::updateUI() {
    for(int i = 0; i < basketLabels.size(); ++i){
        countAllLabels[i]->setText(QString("Шаров в корзине: %1").arg(basketVec[i].getAllCount()));
        countBlueLabels[i]->setText(QString("Синих шаров в корзине %1").arg(basketVec[i].getCountBlueBalls()));
        countRedLabels[i]->setText(QString("Красных шаров в корзине: %1").arg(basketVec[i].getCountRedBalls()));
        procentBlueLabels[i]->setText(QString("Вероятность достать синий шар: %1%").arg(basketVec[i].getProcentGetBlueBall()));
        procentRedLabels[i]->setText(QString("Вероятность достать красный шар: %1%").arg(basketVec[i].getProcentGetRedBall()));
        guiBaskets[i]->setPercent(basketVec[i].getProcentGetBlueBall(), basketVec[i].getProcentGetRedBall());
        lustChangesLabels[i]->setText(basketVec[i].getLustChanges());
    }

    ui->procentAllBlueBalls->setText(QString("Вероятность взять 2 синих шара: %1%").arg(buffer.getAllProcentGetBlueBall(basketVec)));
    ui->procentAllRedBalls->setText(QString("Вероятность взять 2 красных шара: %1%").arg(buffer.getAllProcentGetRedBall(basketVec)));
    ui->procentOneBlueOneRed->setText(QString("Вероятность взять 1 красный и 1 синий шар: %1%").arg(buffer.getProcentOneRedOneBlueBalls(basketVec)));

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_replaceBall_clicked()
{
    QPushButton* senderBtn = qobject_cast<QPushButton*>(sender());
    if(!senderBtn){ qFatal("error with buttons"); }

    int indx = replaceOneBallButtons.indexOf(senderBtn);

    buffer.replaceBall(basketVec, indx);
    buffer.setLogOneBall(logLustTime, logAllTime);
    updateUI();
}

void MainWindow::on_subTwoButton_clicked()
{
    buffer.replaceTwoBalls(basketVec);
    buffer.setLogTwoBall(logLustTime, logAllTime);
    updateUI();
}



