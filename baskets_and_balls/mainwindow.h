#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include "guibasket.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_replaceBall_clicked();

    void on_subTwoButton_clicked();

private:
    void createBasketsWidgets();
    void updateUI();

    Ui::MainWindow *ui;
    QVector<QGroupBox*> basketLabels;
    QVector<QLabel*> countAllLabels;
    QVector<QLabel*> countBlueLabels;
    QVector<QLabel*> countRedLabels;
    QVector<QLabel*> procentBlueLabels;
    QVector<QLabel*> procentRedLabels;
    QVector<QLabel*> lustChangesLabels;
    QVector<QPushButton*> replaceOneBallButtons;
    QVector<GUIBasket*> guiBaskets;

    QLayout* basketsLayOut = nullptr;
};
#endif // MAINWINDOW_H
