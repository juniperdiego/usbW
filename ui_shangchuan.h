/********************************************************************************
** Form generated from reading UI file 'shangchuan.ui'
**
** Created: Sat Jul 12 10:13:44 2014
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHANGCHUAN_H
#define UI_SHANGCHUAN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDateEdit>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Shangchuan
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *returnbtn;
    QLabel *label;
    QDateEdit *FromDataEdt;
    QLabel *label_2;
    QDateEdit *ToDataEdt;
    QPushButton *searchBtn;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *UpdateBtn;
    QTableWidget *ResTabWid;

    void setupUi(QWidget *Shangchuan)
    {
        if (Shangchuan->objectName().isEmpty())
            Shangchuan->setObjectName(QString::fromUtf8("Shangchuan"));
        Shangchuan->resize(800, 480);
        Shangchuan->setMinimumSize(QSize(800, 480));
        Shangchuan->setMaximumSize(QSize(800, 480));
        layoutWidget = new QWidget(Shangchuan);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 20, 741, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        returnbtn = new QPushButton(layoutWidget);
        returnbtn->setObjectName(QString::fromUtf8("returnbtn"));

        horizontalLayout->addWidget(returnbtn);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        FromDataEdt = new QDateEdit(layoutWidget);
        FromDataEdt->setObjectName(QString::fromUtf8("FromDataEdt"));

        horizontalLayout->addWidget(FromDataEdt);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        ToDataEdt = new QDateEdit(layoutWidget);
        ToDataEdt->setObjectName(QString::fromUtf8("ToDataEdt"));

        horizontalLayout->addWidget(ToDataEdt);

        searchBtn = new QPushButton(layoutWidget);
        searchBtn->setObjectName(QString::fromUtf8("searchBtn"));

        horizontalLayout->addWidget(searchBtn);

        horizontalSpacer_2 = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        UpdateBtn = new QPushButton(layoutWidget);
        UpdateBtn->setObjectName(QString::fromUtf8("UpdateBtn"));

        horizontalLayout->addWidget(UpdateBtn);

        ResTabWid = new QTableWidget(Shangchuan);
        if (ResTabWid->columnCount() < 3)
            ResTabWid->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        ResTabWid->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        ResTabWid->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        ResTabWid->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        ResTabWid->setObjectName(QString::fromUtf8("ResTabWid"));
        ResTabWid->setGeometry(QRect(20, 60, 740, 400));
        ResTabWid->setMinimumSize(QSize(720, 400));
        ResTabWid->setMaximumSize(QSize(750, 400));
        ResTabWid->setContextMenuPolicy(Qt::NoContextMenu);
        ResTabWid->setLayoutDirection(Qt::LeftToRight);

        retranslateUi(Shangchuan);
        QObject::connect(returnbtn, SIGNAL(clicked()), Shangchuan, SLOT(Return()));
        QObject::connect(searchBtn, SIGNAL(clicked()), Shangchuan, SLOT(Search()));
        QObject::connect(UpdateBtn, SIGNAL(clicked()), Shangchuan, SLOT(Upload()));

        QMetaObject::connectSlotsByName(Shangchuan);
    } // setupUi

    void retranslateUi(QWidget *Shangchuan)
    {
        Shangchuan->setWindowTitle(QApplication::translate("Shangchuan", "Form", 0, QApplication::UnicodeUTF8));
        returnbtn->setText(QApplication::translate("Shangchuan", "\350\277\224\345\233\236", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Shangchuan", "\344\273\216", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Shangchuan", "\345\210\260", 0, QApplication::UnicodeUTF8));
        searchBtn->setText(QApplication::translate("Shangchuan", "\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        UpdateBtn->setText(QApplication::translate("Shangchuan", "\344\270\212\344\274\240", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = ResTabWid->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Shangchuan", "\346\227\245\346\234\237", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = ResTabWid->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Shangchuan", "\344\270\212\344\274\240\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = ResTabWid->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("Shangchuan", "\344\270\212\344\274\240\347\273\223\346\236\234", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Shangchuan: public Ui_Shangchuan {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHANGCHUAN_H
