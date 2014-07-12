/********************************************************************************
** Form generated from reading UI file 'fuwuqi.ui'
**
** Created: Sat Jul 12 10:13:44 2014
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FUWUQI_H
#define UI_FUWUQI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_fuwuqi
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *returnBtn;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label;
    QLabel *severshowLabel;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QComboBox *severcomboBox;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *okBtn;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *fuwuqi)
    {
        if (fuwuqi->objectName().isEmpty())
            fuwuqi->setObjectName(QString::fromUtf8("fuwuqi"));
        fuwuqi->resize(694, 484);
        widget = new QWidget(fuwuqi);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 23, 641, 371));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        returnBtn = new QPushButton(widget);
        returnBtn->setObjectName(QString::fromUtf8("returnBtn"));

        horizontalLayout_4->addWidget(returnBtn);

        horizontalSpacer_5 = new QSpacerItem(298, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer = new QSpacerItem(383, 55, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(38, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        severshowLabel = new QLabel(widget);
        severshowLabel->setObjectName(QString::fromUtf8("severshowLabel"));

        horizontalLayout->addWidget(severshowLabel);

        horizontalSpacer_4 = new QSpacerItem(68, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        severcomboBox = new QComboBox(widget);
        severcomboBox->setObjectName(QString::fromUtf8("severcomboBox"));

        horizontalLayout_2->addWidget(severcomboBox);

        horizontalSpacer_2 = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_6 = new QSpacerItem(128, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        okBtn = new QPushButton(widget);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));

        horizontalLayout_3->addWidget(okBtn);

        horizontalSpacer_7 = new QSpacerItem(128, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(383, 55, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        retranslateUi(fuwuqi);
        QObject::connect(returnBtn, SIGNAL(clicked()), fuwuqi, SLOT(OnReturn()));
        QObject::connect(okBtn, SIGNAL(clicked()), fuwuqi, SLOT(OnOK()));

        QMetaObject::connectSlotsByName(fuwuqi);
    } // setupUi

    void retranslateUi(QWidget *fuwuqi)
    {
        fuwuqi->setWindowTitle(QApplication::translate("fuwuqi", "Form", 0, QApplication::UnicodeUTF8));
        returnBtn->setText(QApplication::translate("fuwuqi", "\350\277\224\345\233\236", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("fuwuqi", "\346\202\250\345\275\223\345\211\215\351\200\211\346\213\251\347\232\204\346\234\215\345\212\241\345\231\250\346\230\257:", 0, QApplication::UnicodeUTF8));
        severshowLabel->setText(QApplication::translate("fuwuqi", "\347\224\265\344\277\241", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("fuwuqi", "\350\257\267\351\200\211\346\213\251\346\234\215\345\212\241\345\231\250:", 0, QApplication::UnicodeUTF8));
        okBtn->setText(QApplication::translate("fuwuqi", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class fuwuqi: public Ui_fuwuqi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FUWUQI_H
