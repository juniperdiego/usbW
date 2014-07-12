/********************************************************************************
** Form generated from reading UI file 'upstate.ui'
**
** Created: Sat Jul 12 10:13:44 2014
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPSTATE_H
#define UI_UPSTATE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_UpState
{
public:
    QPushButton *BtnOk;
    QLabel *StateLab;

    void setupUi(QDialog *UpState)
    {
        if (UpState->objectName().isEmpty())
            UpState->setObjectName(QString::fromUtf8("UpState"));
        UpState->resize(200, 160);
        UpState->setMinimumSize(QSize(200, 160));
        UpState->setMaximumSize(QSize(200, 160));
        BtnOk = new QPushButton(UpState);
        BtnOk->setObjectName(QString::fromUtf8("BtnOk"));
        BtnOk->setGeometry(QRect(50, 120, 91, 27));
        StateLab = new QLabel(UpState);
        StateLab->setObjectName(QString::fromUtf8("StateLab"));
        StateLab->setGeometry(QRect(20, 20, 151, 71));
        StateLab->setAlignment(Qt::AlignCenter);

        retranslateUi(UpState);
        QObject::connect(BtnOk, SIGNAL(clicked()), UpState, SLOT(OnConfirm()));

        QMetaObject::connectSlotsByName(UpState);
    } // setupUi

    void retranslateUi(QDialog *UpState)
    {
        UpState->setWindowTitle(QApplication::translate("UpState", "Dialog", 0, QApplication::UnicodeUTF8));
        BtnOk->setText(QApplication::translate("UpState", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        StateLab->setText(QApplication::translate("UpState", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UpState: public Ui_UpState {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPSTATE_H
