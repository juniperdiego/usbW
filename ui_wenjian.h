/********************************************************************************
** Form generated from reading UI file 'wenjian.ui'
**
** Created: Sat Jul 12 10:13:44 2014
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WENJIAN_H
#define UI_WENJIAN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wenjian
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *returnBtn;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QComboBox *comboBox;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_2;
    QLabel *cardspaceLabel;
    QLabel *ldateLabel;
    QLabel *updatenumLabel;
    QLabel *label_7;

    void setupUi(QWidget *wenjian)
    {
        if (wenjian->objectName().isEmpty())
            wenjian->setObjectName(QString::fromUtf8("wenjian"));
        wenjian->resize(491, 316);
        layoutWidget = new QWidget(wenjian);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(51, 21, 361, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        returnBtn = new QPushButton(layoutWidget);
        returnBtn->setObjectName(QString::fromUtf8("returnBtn"));

        horizontalLayout->addWidget(returnBtn);

        horizontalSpacer = new QSpacerItem(78, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(layoutWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);

        layoutWidget1 = new QWidget(wenjian);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(50, 110, 361, 101));
        gridLayout = new QGridLayout(layoutWidget1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 3, 1, 1);

        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 2);

        cardspaceLabel = new QLabel(layoutWidget1);
        cardspaceLabel->setObjectName(QString::fromUtf8("cardspaceLabel"));

        gridLayout->addWidget(cardspaceLabel, 0, 2, 1, 1);

        ldateLabel = new QLabel(layoutWidget1);
        ldateLabel->setObjectName(QString::fromUtf8("ldateLabel"));

        gridLayout->addWidget(ldateLabel, 1, 1, 1, 2);

        updatenumLabel = new QLabel(layoutWidget1);
        updatenumLabel->setObjectName(QString::fromUtf8("updatenumLabel"));

        gridLayout->addWidget(updatenumLabel, 1, 4, 1, 1);

        label_7 = new QLabel(layoutWidget1);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 1, 3, 1, 1);


        retranslateUi(wenjian);
        QObject::connect(returnBtn, SIGNAL(clicked()), wenjian, SLOT(onreturn()));

        QMetaObject::connectSlotsByName(wenjian);
    } // setupUi

    void retranslateUi(QWidget *wenjian)
    {
        wenjian->setWindowTitle(QApplication::translate("wenjian", "Form", 0, QApplication::UnicodeUTF8));
        returnBtn->setText(QApplication::translate("wenjian", "\350\277\224\345\233\236", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("wenjian", "\346\226\207\344\273\266\346\225\260\351\207\217(1)", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("wenjian", "G", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("wenjian", "\346\233\264\346\226\260\346\227\266\351\227\264:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("wenjian", "SD\345\215\241\345\217\257\347\224\250\347\251\272\351\227\264:", 0, QApplication::UnicodeUTF8));
        cardspaceLabel->setText(QApplication::translate("wenjian", "14.54", 0, QApplication::UnicodeUTF8));
        ldateLabel->setText(QApplication::translate("wenjian", "2014-05-14", 0, QApplication::UnicodeUTF8));
        updatenumLabel->setText(QApplication::translate("wenjian", "17", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("wenjian", "\346\233\264\346\226\260\346\225\260\351\207\217:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class wenjian: public Ui_wenjian {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WENJIAN_H
