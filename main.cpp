#include"mainwindow.h"
#include "global.h"
#include "usb_enum.h"
#include <QApplication>
#include <QtGui>
#include <QtDebug>
#include <QFile>
#include <QTextStream>

void customMessageHandler(QtMsgType type, const char *msg)
{
	QString txt;
	switch (type) {
	case QtDebugMsg:
		txt = QString("Debug: %1").arg(msg);
		break;
 
	case QtWarningMsg:
		txt = QString("Warning: %1").arg(msg);
	break;
	case QtCriticalMsg:
		txt = QString("Critical: %1").arg(msg);
	break;
	case QtFatalMsg:
		txt = QString("Fatal: %1").arg(msg);
		abort();
	}
 
	QFile outFile(LOG_FILE_NAME);
    if (outFile.size() >= LOG_FILE_SIZE)
	    outFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
    else
	    outFile.open(QIODevice::WriteOnly | QIODevice::Append);

	QTextStream ts(&outFile);
	ts << txt << endl;
}
 
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	qInstallMsgHandler(customMessageHandler);	

#ifdef ARM
    //font
    QFont font;
    font.setPointSize(16);
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
    appDir.mkpath(ENCYPT_LOG_PATH);

#if 1
    //init usb device
    if (!initUsbDevices())
    {
        QMessageBox::critical(NULL, APP_NAME, "USB端口初始化失败，系统无法正常工作！");
    }
#endif

    //test network
    int time = 2;
    while(time)
    {
        QNetworkInterface netInterface = QNetworkInterface::interfaceFromName(NET_NAME);
        if (netInterface.isValid())
        {
            if (netInterface.flags().testFlag(QNetworkInterface::IsUp))
            {
                QHostInfo host = QHostInfo::fromName(WEB_SITE);
                if (!host.addresses().isEmpty()) 
                {
                    Global::s_netState = true;
                    break;
                }
            }
        }
        sleep(5);
        --time;
    }

    //msgBox.hide();

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
        if (gengXin.getUpdateDevState())
            w.OnGengxin(false);
        else
            w.startUsbScan();
    }

    return a.exec();
}

