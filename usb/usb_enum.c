#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <stdbool.h>  
#include <string.h>  
#include <pthread.h>  
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

#define USB_DEVICE_FILE "/etc/flashbot-port.conf"
#define BUFFER_SIZE 512

#define USB_DEVICE_NUM 12

const char *usb_device_list[USB_DEVICE_NUM] = {
    "/sys/devices/platform/sw-ehci.1/usb1/1-1/1-1.2/1-1.2.1/",
    "/sys/devices/platform/sw-ehci.1/usb1/1-1/1-1.3/",
    "/sys/devices/platform/sw-ehci.1/usb1/1-1/1-1.4/",
    "/sys/devices/platform/sw-ehci.2/usb3/3-1/3-1.2/3-1.2.1/",
    "/sys/devices/platform/sw-ehci.2/usb3/3-1/3-1.3/",
    "/sys/devices/platform/sw-ehci.2/usb3/3-1/3-1.4/",

    "/sys/devices/platform/sw-ehci.1/usb1/1-1/1-1.1/",
    "/sys/devices/platform/sw-ehci.1/usb1/1-1/1-1.2/1-1.2.2/",
    "/sys/devices/platform/sw-ehci.1/usb1/1-1/1-1.2/1-1.2.3/",
    "/sys/devices/platform/sw-ehci.2/usb3/3-1/3-1.1/",
    "/sys/devices/platform/sw-ehci.2/usb3/3-1/3-1.2/3-1.2.2/",
    "/sys/devices/platform/sw-ehci.2/usb3/3-1/3-1.2/3-1.2.3/"
};

//#define USB_DEVICE_NUM (sizeof(usb_device_list) / sizeof(usb_device_list[0]))

typedef void (* remove_usb_device_callback)(int num);
typedef void (* add_usb_device_callback)(int num, const char *serial);

typedef struct usb_device_monitor_t {
    pthread_t ptid[USB_DEVICE_NUM];
    volatile bool monitor_exit;

    add_usb_device_callback add_cb;
    remove_usb_device_callback rm_cb;
} usb_device_montor_t;

usb_device_montor_t usb_device_montor;

static void usb_device_monitor_init(void)
{
    memset(&usb_device_montor, 0, sizeof(usb_device_montor));
    usb_device_montor.monitor_exit = false;
}

void register_usb_device_callback(add_usb_device_callback add_cb, 
        remove_usb_device_callback rm_cb)
{
    usb_device_monitor_init();

    usb_device_montor.add_cb = add_cb;
    usb_device_montor.rm_cb = rm_cb;
}

void notify_usb_device_monitor_exit(void)
{
    usb_device_montor.monitor_exit = true;
}

static bool usb_device_path_exist(const char *path)
{
    if (access(path, F_OK) != 0) {
        return false;
    }

    return true;
}

static void read_usb_device_serial(int idx, const char *path, char *serial, int size)
{
    int fd;
    ssize_t rn;
    char buf[128];

    snprintf(buf, sizeof(buf), "%sserial", path);

    fd = open(buf, O_RDONLY);
    if (fd == -1) {
        serial[0] = 0;
        printf("Usb Num: %d read %s failed.\n", idx, buf);
        return;
    }

    rn = read(fd, serial, size);

    if (rn <= 0) {
        printf("Usb Num: %d read serial failed.\n", idx);
        serial[0] = 0;
        return;
    }

    serial[rn-1] = 0;

    close(fd);
}

static void * do_usb_device_enum_thread(void *args)
{
    int idx;
    //char save_serial[64] = {0};
    bool devExist = false;
    bool firstExist = true;

    idx = (int) (args);

    while(! usb_device_montor.monitor_exit) {
        if (usb_device_path_exist(usb_device_list[idx])) {

            char serial[64];
            read_usb_device_serial(idx, usb_device_list[idx], serial, sizeof(serial));
            devExist = true;

            if (firstExist == true) 
            {
                firstExist = false;
                if (usb_device_montor.add_cb) {
                    usb_device_montor.add_cb(idx, serial);
                }
            }
        } else {
            firstExist = true;
            if(devExist == true)
            {
                devExist = false;
                if (usb_device_montor.add_cb) 
                {
                    usb_device_montor.rm_cb(idx);
                }
            }
        }

        usleep(10 * 1000);
    }

    return NULL;
}

static bool check_callback(void)
{
    if (usb_device_montor.rm_cb == NULL ||
            usb_device_montor.add_cb == NULL) {
        return false;
    }

    return true;
}

void start_usb_device_monitor(void)
{  
    int i, ret;

    //usb_device_monitor_init();

    if (! check_callback()) {
        printf("ERROR: do not found callback function.\n");
        return;
    }

    for (i = 0; i < USB_DEVICE_NUM; i ++) {
        ret = pthread_create(&usb_device_montor.ptid[i], NULL, do_usb_device_enum_thread, (void *)i);
        if (ret != 0) {
            printf("thread id: %d create failed.\n", i);
        } else {
            printf("thread id: %d create success.\n", i);
        }
    }

    for (i = 0; i < USB_DEVICE_NUM; i ++) {
        //pthread_join(usb_device_montor.ptid[i], NULL);
    }
} 

bool getSerialNumInPort(int idx, char* serial)
{
    if(usb_device_path_exist(usb_device_list[idx]))
    {
        char serialInPort[64];
        read_usb_device_serial(idx, usb_device_list[idx], serialInPort, sizeof(serialInPort));

        strcpy(serial, serialInPort);

        printf("serialInPort\t:%s\n",serialInPort);
        return true;
    }
    return false;
}

bool serialNumExistInPort(int idx, const char* serial)
{
    if(usb_device_path_exist(usb_device_list[idx]))
    {
        char serialInPort[64];
        read_usb_device_serial(idx, usb_device_list[idx], serialInPort, sizeof(serialInPort));

        if(strcmp(serial, serialInPort) == 0)
            return true;
        else
            return false;
    }
    return false;
}

static bool trimStr(char* buf)
{
    const char* chSet = " \t\n\r";
    int i = 0;

    //trim start
    while (buf[i] && strchr(chSet, buf[i])) i++;
    memmove(buf, &buf[i], strlen(buf)-i+1);

    if (buf[0] == 0x0) return false;

    //trim end
    int len = strlen(buf);
    while (len >= 0 && strchr(chSet, buf[len])) len--;
    buf[len+1] = '\0';

    if (buf[len] != '/')
    {
        buf[len+1] = '/';
        buf[len+2] = '\0';
    }

    return true;
}

bool initUsbDevices()
{
    FILE* fp = fopen(USB_DEVICE_FILE, "r");
    if(fp == NULL)
    {
        printf("open usb device file failed, errno.%02d is: %s\n", errno, strerror(errno));
        return false;
    }

    char read_buff[BUFFER_SIZE];
    int num = 0;

    do
    {
        memset(read_buff, 0, BUFFER_SIZE);
        if (fgets(read_buff, BUFFER_SIZE, fp) == NULL)
            break;
        if (!trimStr(read_buff)) continue;
        printf("usb devices file:%s\n", read_buff);
        usb_device_list[num] = read_buff;
        ++num;

        if (num == USB_DEVICE_NUM)
            break;
    } while (1);

    fclose(fp);

    return (num == USB_DEVICE_NUM);
}
