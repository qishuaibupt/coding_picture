/********************************************************************************
** Form generated from reading UI file 'player.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYER_H
#define UI_PLAYER_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_playerClass
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *load;
    QPushButton *play;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *label_2;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox_2;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBox_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *playerClass)
    {
        if (playerClass->objectName().isEmpty())
            playerClass->setObjectName(QStringLiteral("playerClass"));
        playerClass->resize(839, 654);
        centralWidget = new QWidget(playerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 640, 480));
        load = new QPushButton(centralWidget);
        load->setObjectName(QStringLiteral("load"));
        load->setGeometry(QRect(130, 560, 75, 23));
        play = new QPushButton(centralWidget);
        play->setObjectName(QStringLiteral("play"));
        play->setGeometry(QRect(310, 560, 75, 23));
        doubleSpinBox = new QDoubleSpinBox(centralWidget);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setGeometry(QRect(150, 520, 62, 22));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(120, 520, 31, 16));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(220, 520, 41, 16));
        doubleSpinBox_2 = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_2->setObjectName(QStringLiteral("doubleSpinBox_2"));
        doubleSpinBox_2->setGeometry(QRect(240, 520, 62, 22));
        doubleSpinBox_2->setLocale(QLocale(QLocale::Chinese, QLocale::China));
        doubleSpinBox_2->setMinimum(-89);
        doubleSpinBox_2->setMaximum(89);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(320, 520, 31, 16));
        doubleSpinBox_3 = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_3->setObjectName(QStringLiteral("doubleSpinBox_3"));
        doubleSpinBox_3->setGeometry(QRect(350, 520, 62, 22));
        doubleSpinBox_3->setMinimum(-50);
        doubleSpinBox_3->setMaximum(50);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(220, 560, 75, 23));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(400, 560, 75, 23));
        playerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(playerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 839, 23));
        playerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(playerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        playerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(playerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        playerClass->setStatusBar(statusBar);

        retranslateUi(playerClass);
        QObject::connect(play, SIGNAL(clicked()), playerClass, SLOT(play_start()));
        QObject::connect(load, SIGNAL(clicked()), playerClass, SLOT(load_video()));
        QObject::connect(doubleSpinBox, SIGNAL(valueChanged(double)), playerClass, SLOT(get_value()));
        QObject::connect(doubleSpinBox_2, SIGNAL(valueChanged(double)), playerClass, SLOT(get_value()));
        QObject::connect(doubleSpinBox_3, SIGNAL(valueChanged(double)), playerClass, SLOT(get_value()));
        QObject::connect(pushButton, SIGNAL(clicked()), playerClass, SLOT(Reverse()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), playerClass, SLOT(esc()));

        QMetaObject::connectSlotsByName(playerClass);
    } // setupUi

    void retranslateUi(QMainWindow *playerClass)
    {
        playerClass->setWindowTitle(QApplication::translate("playerClass", "player", Q_NULLPTR));
        label->setText(QApplication::translate("playerClass", "\345\260\232\346\234\252\350\275\275\345\205\245", Q_NULLPTR));
        load->setText(QApplication::translate("playerClass", "\350\275\275\345\205\245\346\226\207\344\273\266", Q_NULLPTR));
        play->setText(QApplication::translate("playerClass", "\346\222\255\346\224\276", Q_NULLPTR));
        label_2->setText(QApplication::translate("playerClass", "\347\272\277\351\225\277", Q_NULLPTR));
        label_3->setText(QApplication::translate("playerClass", "\345\200\276\350\247\222", Q_NULLPTR));
        label_4->setText(QApplication::translate("playerClass", "\344\275\215\347\247\273", Q_NULLPTR));
        pushButton->setText(QApplication::translate("playerClass", "\345\217\215\350\275\254", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("playerClass", "\351\200\200\345\207\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class playerClass: public Ui_playerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYER_H
