#include"mainwindow.h"
#include <QApplication>
#include <QtGui>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");  

    QTextCodec::setCodecForLocale(codec);  
    QTextCodec::setCodecForCStrings(codec);  
    QTextCodec::setCodecForTr(codec);

    //create dir for update
    QDir appDir;
    appDir.mkpath(TMP_PATH);
    appDir.mkpath(APK_PATH);
    appDir.mkpath(LOG_PATH);

    //test network
    QHostInfo host = QHostInfo::fromName("www.baidu.com");
    if (!host.addresses().isEmpty()) Global::s_netState = true;

    MainWindow w;
    w.setWindowTitle("Welcome");
    w.show();

    if (Global::s_netState)
    {
        Gengxin gengXin(true);
        gengXin.show();
        gengXin.StartUpSoft();

        if (Global::s_needRestart)
        {
            QString exePath = qApp->applicationFilePath();
            QString cmd = "unzip ";
            cmd += UPDATE_FILE_NAME;
            QFile::remove(exePath);
            QProcess::execute(cmd);
            QProcess::startDetached(exePath, QStringList());
            return 0;
        }
    }

    return a.exec();
}

