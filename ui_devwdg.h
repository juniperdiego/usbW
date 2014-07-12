/********************************************************************************
** Form generated from reading UI file 'devwdg.ui'
**
** Created: Sat Jul 12 10:13:44 2014
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVWDG_H
#define UI_DEVWDG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DevWdg
{
public:
    QLabel *labNum;
    QLabel *labStatus;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QProgressBar *progBar_Install;
    QLabel *labPerc;

    void setupUi(QWidget *DevWdg)
    {
        if (DevWdg->objectName().isEmpty())
            DevWdg->setObjectName(QString::fromUtf8("DevWdg"));
        DevWdg->resize(100, 190);
        DevWdg->setMaximumSize(QSize(100, 190));
        labNum = new QLabel(DevWdg);
        labNum->setObjectName(QString::fromUtf8("labNum"));
        labNum->setGeometry(QRect(11, 31, 79, 24));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        labNum->setFont(font);
        labNum->setAlignment(Qt::AlignCenter);
        labStatus = new QLabel(DevWdg);
        labStatus->setObjectName(QString::fromUtf8("labStatus"));
        labStatus->setGeometry(QRect(11, 101, 79, 24));
        labStatus->setFont(font);
        labStatus->setAlignment(Qt::AlignCenter);
        layoutWidget = new QWidget(DevWdg);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(11, 150, 82, 30));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        progBar_Install = new QProgressBar(layoutWidget);
        progBar_Install->setObjectName(QString::fromUtf8("progBar_Install"));
        progBar_Install->setMinimumSize(QSize(80, 6));
        progBar_Install->setMaximumSize(QSize(80, 6));
        progBar_Install->setValue(24);
        progBar_Install->setTextVisible(true);

        verticalLayout->addWidget(progBar_Install);

        labPerc = new QLabel(layoutWidget);
        labPerc->setObjectName(QString::fromUtf8("labPerc"));
        QFont font1;
        font1.setPointSize(10);
        font1.setItalic(false);
        labPerc->setFont(font1);
        labPerc->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labPerc);


        retranslateUi(DevWdg);

        QMetaObject::connectSlotsByName(DevWdg);
    } // setupUi

    void retranslateUi(QWidget *DevWdg)
    {
        DevWdg->setWindowTitle(QApplication::translate("DevWdg", "Form", 0, QApplication::UnicodeUTF8));
        labNum->setText(QApplication::translate("DevWdg", "TextLabel", 0, QApplication::UnicodeUTF8));
        labStatus->setText(QApplication::translate("DevWdg", "TextLabel", 0, QApplication::UnicodeUTF8));
        labPerc->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DevWdg: public Ui_DevWdg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVWDG_H
