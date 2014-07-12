/********************************************************************************
** Form generated from reading UI file 'baobiao.ui'
**
** Created: Sat Jul 12 10:13:44 2014
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BAOBIAO_H
#define UI_BAOBIAO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDateEdit>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_baobiao
{
public:
    QGridLayout *gridLayout_2;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *returnBtn;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QDateEdit *FromdateEdit;
    QLabel *label_2;
    QDateEdit *TodateEdit;
    QPushButton *searchBtn;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QTableWidget *JixingTab;
    QWidget *tab_2;
    QGridLayout *gridLayout;
    QTableWidget *UsbTab;

    void setupUi(QWidget *baobiao)
    {
        if (baobiao->objectName().isEmpty())
            baobiao->setObjectName(QString::fromUtf8("baobiao"));
        baobiao->resize(599, 413);
        gridLayout_2 = new QGridLayout(baobiao);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        splitter = new QSplitter(baobiao);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        returnBtn = new QPushButton(layoutWidget);
        returnBtn->setObjectName(QString::fromUtf8("returnBtn"));

        horizontalLayout->addWidget(returnBtn);

        horizontalSpacer = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        FromdateEdit = new QDateEdit(layoutWidget);
        FromdateEdit->setObjectName(QString::fromUtf8("FromdateEdit"));

        horizontalLayout->addWidget(FromdateEdit);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        TodateEdit = new QDateEdit(layoutWidget);
        TodateEdit->setObjectName(QString::fromUtf8("TodateEdit"));

        horizontalLayout->addWidget(TodateEdit);

        searchBtn = new QPushButton(layoutWidget);
        searchBtn->setObjectName(QString::fromUtf8("searchBtn"));

        horizontalLayout->addWidget(searchBtn);

        splitter->addWidget(layoutWidget);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        JixingTab = new QTableWidget(tab);
        if (JixingTab->columnCount() < 3)
            JixingTab->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        JixingTab->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        JixingTab->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        JixingTab->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        JixingTab->setObjectName(QString::fromUtf8("JixingTab"));

        gridLayout_3->addWidget(JixingTab, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout = new QGridLayout(tab_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        UsbTab = new QTableWidget(tab_2);
        if (UsbTab->columnCount() < 3)
            UsbTab->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        UsbTab->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        UsbTab->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        UsbTab->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        UsbTab->setObjectName(QString::fromUtf8("UsbTab"));

        gridLayout->addWidget(UsbTab, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        splitter->addWidget(tabWidget);

        gridLayout_2->addWidget(splitter, 0, 0, 1, 1);


        retranslateUi(baobiao);
        QObject::connect(returnBtn, SIGNAL(clicked()), baobiao, SLOT(OnReturn()));
        QObject::connect(searchBtn, SIGNAL(clicked()), baobiao, SLOT(OnSearchData()));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(baobiao);
    } // setupUi

    void retranslateUi(QWidget *baobiao)
    {
        baobiao->setWindowTitle(QApplication::translate("baobiao", "Form", 0, QApplication::UnicodeUTF8));
        returnBtn->setText(QApplication::translate("baobiao", "\350\277\224\345\233\236", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("baobiao", "\344\273\216", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("baobiao", "\345\210\260", 0, QApplication::UnicodeUTF8));
        searchBtn->setText(QApplication::translate("baobiao", "\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = JixingTab->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("baobiao", "\346\227\245\346\234\237", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = JixingTab->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("baobiao", "\346\234\272\345\236\213", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = JixingTab->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("baobiao", "\345\256\211\350\243\205\346\225\260\351\207\217", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("baobiao", "\346\234\272\345\236\213", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = UsbTab->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("baobiao", "\346\227\245\346\234\237", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = UsbTab->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("baobiao", "USB\345\217\243", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = UsbTab->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QApplication::translate("baobiao", "\345\256\211\350\243\205\346\225\260\351\207\217", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("baobiao", "usb\345\217\243", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class baobiao: public Ui_baobiao {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BAOBIAO_H
