#include "usb_enum.h"

void add_callback(int num, const char *serial)
{
    printf("Add USB num: %d, Serial: %s\n", num, serial);

    /* Place Your CODE here. */
}

void remove_callback(int num)
{
    printf("Remove USB num: %d\n", num);
    /* Place Your CODE here. */
}


int main(int argc, char *argv[])
{
    register_usb_device_callback(add_callback, remove_callback);
    start_usb_device_monitor();
    printf(" adb_push_cmd  = %d\n", adb_push_cmd("/home/xianfeng/usb_enum/net_link.txt", "/sd/net_link.txt","0123456789ABCDEF"));
    printf(" getprop = %s\n", adb_getprop_cmd("ro.build.product","0123456789ABCDEF"));
    printf("%d\n", adb_install_cmd("/home/xianfeng/Downloads/a.apk","0123456789ABCDEF"));

    //start com.android.browser/com.android.browser.BrowserActivity
    printf("start app %d \n", adb_start_app_cmd("com.android.browser/com.android.browser.BrowserActivitya", "0123456789ABCDEF"));
    return 0;
}

