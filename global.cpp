#include "global.h"

QString Global::g_IP = 0;
std::string Global::g_DevID = "";
bool  Global::s_netState = false;
int Global::g_UnUpNum = 0;
USB_State Global::usb_state[DEVCOUNT] = {{0, 0, "", "", 0, 0, 0}};
bool  Global::s_needRestart = false;
QString Global::s_updateTime = "";

void Global::reboot()
{
    QProcess::execute("reboot");
}

void Global::setSysTime(const QString& t)
{
    if (t.isEmpty()) return;

    uint time = t.toUInt();
    QDateTime dateTime = QDateTime::fromTime_t(time);
    QString timeStr = dateTime.toString("yyyy.MM.dd-hh:mm:ss");
    QString cmd = QString("date -s %1").arg(timeStr);
    QProcess::execute(cmd);
    cmd = "hwclock -w";
    QProcess::execute(cmd);
}

string Global::encyptStr(const string& str)
{
    string result = str;
    for (size_t i = 0; i < str.length(); ++i)
    {
        result[i] = str[i] ^ ENCYPT_BIT;
    }

    return result;
}

void Global::clearApks()
{
    QStringList nameFilter;
    nameFilter.append("*.apk");
    QDir dir(APK_PATH);
    QStringList strFileLst;
    strFileLst.clear();
    if(dir.exists())
    {
        strFileLst = dir.entryList(nameFilter, QDir::Files | QDir::NoSymLinks);
        for(int i = 0; i < strFileLst.count(); i++)
        {
            QFile::remove(strFileLst[i]);
        }
    }
}

