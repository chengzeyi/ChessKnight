/********************************************************************************
** Form generated from reading UI file 'ChessKnight.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHESSKNIGHT_H
#define UI_CHESSKNIGHT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChessKnightClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ChessKnightClass)
    {
        if (ChessKnightClass->objectName().isEmpty())
            ChessKnightClass->setObjectName(QStringLiteral("ChessKnightClass"));
        ChessKnightClass->resize(600, 400);
        menuBar = new QMenuBar(ChessKnightClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        ChessKnightClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ChessKnightClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ChessKnightClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ChessKnightClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ChessKnightClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ChessKnightClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ChessKnightClass->setStatusBar(statusBar);

        retranslateUi(ChessKnightClass);

        QMetaObject::connectSlotsByName(ChessKnightClass);
    } // setupUi

    void retranslateUi(QMainWindow *ChessKnightClass)
    {
        ChessKnightClass->setWindowTitle(QApplication::translate("ChessKnightClass", "ChessKnight", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChessKnightClass: public Ui_ChessKnightClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHESSKNIGHT_H
