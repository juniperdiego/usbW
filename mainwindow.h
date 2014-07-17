#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "global.h"
#include "ClickedLabel.h"
#include "devwdg.h"
#include "record.h"
#include "fileupload.h"
#include "gengxin.h"

#define DEVCOUNT 12

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void CreateLayout();
    void CreateStatusbar();
    
private:
    int  GetAllFiles();
    void startUsbScan();

public slots:
    void OnGengxin();
    void OnWenjian();
    void OnBaobiao();
    void OnFuwuqi();
    void OnShangchuan();
    void OnHelp();
    void ScanUsbDev();
    void TimeNow();
    void onlineStateChange(bool bState);
    void setMvState(bool bState);   //change Mv State
    void SetUnUpCount();

private:
    Ui::MainWindow *ui;

    QString m_strDevID;
    QNetworkConfigurationManager* m_netConf;

    bool m_updateState;

    QTimer* m_usbScanTimer;

    FileUpload* m_fileUpLoad;

    DevWdg* DevArray[DEVCOUNT];
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
    QSpacerItem *horizonSpacer1;

    QHBoxLayout *layout ;

    QGridLayout *gridlayout;

    QLabel  *label1;
    QLabel  *label2;
    QLabel  *label3;
    QLabel  *label4;
    QLabel  *label5;
    QLabel  *label6;
    QLabel  *label7;
    QLabel  *label8;
    QLabel  *label9;
    QLabel  *label10;
    QLabel  *label11;
    QLabel  *label12;


    QLabel *shebei;
    QLabel *sbid;
    QLabel *kjl;
    QLabel *time;
    QLabel *jiaoshi;
    ClickedLabel *help;
    QHBoxLayout *statusbox;
};

#endif // MAINWINDOW_H
