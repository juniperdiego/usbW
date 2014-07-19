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
