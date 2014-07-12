/********************************************************************************
** Form generated from reading UI file 'gengxin.ui'
**
** Created: Sat Jul 12 10:13:44 2014
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENGXIN_H
#define UI_GENGXIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Gengxin
{
public:
    QLabel *labUp;
    QLabel *labMv;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *ConfirmBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *CancleBtn;
    QPushButton *pushBtnTerm;

    void setupUi(QDialog *Gengxin)
    {
        if (Gengxin->objectName().isEmpty())
            Gengxin->setObjectName(QString::fromUtf8("Gengxin"));
        Gengxin->resize(400, 240);
        Gengxin->setMinimumSize(QSize(400, 240));
        Gengxin->setMaximumSize(QSize(400, 240));
        labUp = new QLabel(Gengxin);
        labUp->setObjectName(QString::fromUtf8("labUp"));
        labUp->setGeometry(QRect(20, 90, 361, 41));
        labUp->setAlignment(Qt::AlignCenter);
        labMv = new QLabel(Gengxin);
        labMv->setObjectName(QString::fromUtf8("labMv"));
        labMv->setGeometry(QRect(100, 40, 200, 20));
        labMv->setMinimumSize(QSize(200, 20));
        labMv->setMaximumSize(QSize(200, 20));
        labMv->setAlignment(Qt::AlignCenter);
        layoutWidget = new QWidget(Gengxin);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(60, 150, 281, 32));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        ConfirmBtn = new QPushButton(layoutWidget);
        ConfirmBtn->setObjectName(QString::fromUtf8("ConfirmBtn"));

        horizontalLayout->addWidget(ConfirmBtn);

        horizontalSpacer = new QSpacerItem(68, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        CancleBtn = new QPushButton(layoutWidget);
        CancleBtn->setObjectName(QString::fromUtf8("CancleBtn"));

        horizontalLayout->addWidget(CancleBtn);

        pushBtnTerm = new QPushButton(Gengxin);
        pushBtnTerm->setObjectName(QString::fromUtf8("pushBtnTerm"));
        pushBtnTerm->setGeometry(QRect(130, 200, 141, 29));

        retranslateUi(Gengxin);
        QObject::connect(ConfirmBtn, SIGNAL(clicked()), Gengxin, SLOT(OnOk()));
        QObject::connect(CancleBtn, SIGNAL(clicked()), Gengxin, SLOT(OnCancle()));
        QObject::connect(pushBtnTerm, SIGNAL(clicked()), Gengxin, SLOT(OnTerm()));

        QMetaObject::connectSlotsByName(Gengxin);
    } // setupUi

    void retranslateUi(QDialog *Gengxin)
    {
        Gengxin->setWindowTitle(QApplication::translate("Gengxin", "Form", 0, QApplication::UnicodeUTF8));
        labUp->setText(QApplication::translate("Gengxin", "TextLabel ", 0, QApplication::UnicodeUTF8));
        labMv->setText(QApplication::translate("Gengxin", "TextLabel", 0, QApplication::UnicodeUTF8));
        ConfirmBtn->setText(QApplication::translate("Gengxin", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        CancleBtn->setText(QApplication::translate("Gengxin", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        pushBtnTerm->setText(QApplication::translate("Gengxin", "\345\274\272\345\210\266\347\273\210\346\255\242\346\233\264\346\226\260", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Gengxin: public Ui_Gengxin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENGXIN_H
