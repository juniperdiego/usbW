#include"mainwindow.h"
#include "global.h"
#include <QApplication>
#include <QtGui>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef ARM
    //font
    QFont font;
    font.setPointSize(16);
    //font.setFamily(("wqyzh"));
    //font.setBold(false);
    a.setFont(font);
#endif

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
    int time = 6;
    while(time)
    {
        QHostInfo host = QHostInfo::fromName(WEB_SITE);
        if (!host.addresses().isEmpty()) 
        {
            Global::s_netState = true;
            break;
        }
        sleep(5);
        --time;
    }

    if (!Global::s_netState)
    {
        QMessageBox::information(NULL, APP_NAME, "没有发现网络连接，无法更新软件数据，系统将离线运行！");
    }

    MainWindow w;
    w.setWindowTitle("Welcome");
    w.show();

    if (Global::s_netState)
    {
        Gengxin gengXin(true);
        gengXin.show();
        gengXin.StartUpSoft();
#if 0
        if (Global::s_needRestart)
        {
            QString exePath = qApp->applicationFilePath();
            QString cmd = "unzip ";
            cmd += UPDATE_FILE_NAME;
            QFile::remove(exePath);
            QProcess::execute(cmd);
#ifdef ARM
            Global::reboot();
#else
            QProcess::startDetached(exePath, QStringList());
#endif
            return 0;
        }
#endif
        gengXin.hide();
        w.OnGengxin(false);
    }

    return a.exec();
}

