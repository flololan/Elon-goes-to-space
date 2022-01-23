/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *draggableItem;
    QLabel *scene;
    QPushButton *startButton;
    QPushButton *exitButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1024, 768);
        MainWindow->setMinimumSize(QSize(1024, 768));
        MainWindow->setMaximumSize(QSize(1024, 768));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        draggableItem = new QLabel(centralWidget);
        draggableItem->setObjectName(QStringLiteral("draggableItem"));
        draggableItem->setGeometry(QRect(20, 620, 101, 111));
        draggableItem->setPixmap(QPixmap(QString::fromUtf8("assets/draggableItems/asset_tiny_elon.png")));
        draggableItem->setScaledContents(true);
        scene = new QLabel(centralWidget);
        scene->setObjectName(QStringLiteral("scene"));
        scene->setGeometry(QRect(0, 0, 1024, 768));
        scene->setPixmap(QPixmap(QString::fromUtf8(":/assets/scenesimages/scene_start.png")));
        scene->setScaledContents(true);
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setGeometry(QRect(70, 560, 101, 51));
        startButton->setFlat(false);
        exitButton = new QPushButton(centralWidget);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setGeometry(QRect(920, 740, 101, 23));
        MainWindow->setCentralWidget(centralWidget);
        scene->raise();
        draggableItem->raise();
        startButton->raise();
        exitButton->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Elon dans l'espace", 0));
        draggableItem->setText(QString());
        scene->setText(QString());
        startButton->setText(QApplication::translate("MainWindow", "Commencer", 0));
        exitButton->setText(QApplication::translate("MainWindow", "Revenir sur Terre", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
