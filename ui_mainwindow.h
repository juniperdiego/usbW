/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat Jul 12 10:13:44 2014
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *WidTest;
    QLabel *lab1;
    QLabel *lab2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(624, 468);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        WidTest = new QWidget(centralwidget);
        WidTest->setObjectName(QString::fromUtf8("WidTest"));
        WidTest->setGeometry(QRect(10, 60, 101, 151));
        lab1 = new QLabel(WidTest);
        lab1->setObjectName(QString::fromUtf8("lab1"));
        lab1->setGeometry(QRect(10, 30, 72, 19));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        lab1->setFont(font);
        lab1->setAutoFillBackground(false);
        lab1->setTextFormat(Qt::RichText);
        lab1->setScaledContents(false);
        lab1->setAlignment(Qt::AlignCenter);
        lab2 = new QLabel(WidTest);
        lab2->setObjectName(QString::fromUtf8("lab2"));
        lab2->setGeometry(QRect(10, 110, 72, 19));
        lab2->setFont(font);
        lab2->setAlignment(Qt::AlignCenter);
        lab2->raise();
        lab1->raise();
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 624, 27));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        lab1->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        lab2->setText(QApplication::translate("MainWindow", "\347\251\272\351\227\262", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
