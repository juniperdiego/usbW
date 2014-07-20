#include "global.h"

QString Global::g_IP = 0;
std::string Global::g_DevID = "";
bool  Global::s_netState = false;
int Global::g_UnUpNum = 0;
USB_State Global::usb_state[USB_COUNT] = {0};
bool  Global::s_needRestart = false;

void Global::reboot()
{
    QProcess::execute("reboot");
}

void Global::setSysTime(const QString& t)
{
    uint time = t.toUInt();
    QDateTime dateTime = QDateTime::fromTime_t(time);
    QString timeStr = dateTime.toString("yyyy.MM.dd-hh:mm:ss");
    QString cmd = QString("date -s %1").arg(timeStr);
    QProcess::execute(cmd);
}

