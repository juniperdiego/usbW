#include"mainwindow.h"
#include <QApplication>
#include <QtGui>
//#include "dataupdate.h"
#include "threadcontrol.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");  

    QTextCodec::setCodecForLocale(codec);  
    QTextCodec::setCodecForCStrings(codec);  
    QTextCodec::setCodecForTr(codec);

#if 0
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
#endif



//    FILE_CTL *record = new FILE_CTL;
//    record->init();
//    record->log_deal();
//        DataUpdate* Up = new DataUpdate;
//        Up->ApkFinish();
////        Up->mk_filedir("/tmp/test/test/tmp.apk");
//    Up->PkgFinish();
    //    QString file1 = "/home/zb/DATA/1.apk";
//    qDebug()<< Up->getFileMd5( file1);
//    QString premd5="3b802deb55136e43aabe26785da8166d";
//    if ( Up->MD5_Check(file1, premd5)){
//        qDebug()<< premd5;
//    }
//    qDebug()<< Up->getFileMd5("/home/zb/DATA/2.apk");
//    qDebug()<< Up->getFileMd5("/home/zb/DATA/3.apk");


    MainWindow w;
    w.setWindowTitle("Welcome");
    w.show();
    w.OnGengxin();

    return a.exec();
}

