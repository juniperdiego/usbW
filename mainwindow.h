#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "global.h"
#include "ClickedLabel.h"
#include "devwdg.h"
#include "record.h"
#include "fileupload.h"
#include "shangchuan.h"
#include "gengxin.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void CreateLayout();
    void CreateStatusbar();
    
    void startUsbScan();

public slots:
    void OnGengxin(bool = true);
    void OnWenjian();
    void OnBaobiao();
    void OnFuwuqi();
    void OnShangchuan();
    void OnJiaoZhun();
    void OnHelp();
    void ScanUsbDev();
    void TimeNow();
    void onlineStateChange();
    void setMvState(bool bState);   //change Mv State
    void SetUnUpCount();

public:
    static DevWdg* s_devArray[DEVCOUNT];

private:

    QString m_strDevID;
    //QNetworkConfigurationManager* m_netConf;

    bool m_updateState;

    QTimer* m_usbScanTimer;

    FileUpload* m_fileUpLoad;
    Shangchuan* m_shangChun;

    //USB_State* UsbState[DEVCOUNT];

    ClickedLabel *gxin;
    ClickedLabel *wluo;
    ClickedLabel *wjian;
    ClickedLabel *bbiao;
    ClickedLabel *fwuqi;
    QLabel *cangkuid;
    QLabel *id;
    QLabel *network;
    //QLabel *neicun;
    QPushButton *shangchuan;
    QLabel *weishangchuan;
    QLabel *wscnum;
    QLabel* LabUpdateState;
    QMovie *MvUpdate;

    QHBoxLayout *layout ;

    QGridLayout *gridlayout;

    QLabel *shebei;
    QLabel *sbid;
    QLabel *kjl;
    QLabel *time;
    ClickedLabel* jiaoshi;
    ClickedLabel* m_jiaozhun;
    ClickedLabel *help;
    QHBoxLayout *statusbox;
};

#endif // MAINWINDOW_H
