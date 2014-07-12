/********************************************************************************
** Form generated from reading UI file 'help.ui'
**
** Created: Sat Jul 12 10:13:44 2014
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELP_H
#define UI_HELP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextBrowser>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Help
{
public:
    QTextBrowser *textHelp;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *retBtn;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *Help)
    {
        if (Help->objectName().isEmpty())
            Help->setObjectName(QString::fromUtf8("Help"));
        Help->resize(800, 480);
        Help->setMinimumSize(QSize(800, 480));
        Help->setMaximumSize(QSize(800, 480));
        textHelp = new QTextBrowser(Help);
        textHelp->setObjectName(QString::fromUtf8("textHelp"));
        textHelp->setGeometry(QRect(20, 60, 761, 411));
        widget = new QWidget(Help);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(21, 11, 751, 31));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        retBtn = new QPushButton(widget);
        retBtn->setObjectName(QString::fromUtf8("retBtn"));

        horizontalLayout->addWidget(retBtn);

        horizontalSpacer = new QSpacerItem(78, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        retranslateUi(Help);

        QMetaObject::connectSlotsByName(Help);
    } // setupUi

    void retranslateUi(QWidget *Help)
    {
        Help->setWindowTitle(QApplication::translate("Help", "\345\270\256\345\212\251", 0, QApplication::UnicodeUTF8));
        retBtn->setText(QApplication::translate("Help", "\350\277\224\345\233\236", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Help", "\345\270\256\345\212\251", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Help: public Ui_Help {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELP_H
