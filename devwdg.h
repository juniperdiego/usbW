#ifndef DEVWDG_H
#define DEVWDG_H

#include <QWidget>
#include <QTimer>
#include "global.h"

namespace Ui {
class DevWdg;
}

class DevWdg : public QWidget
{
    Q_OBJECT
    
public:
    explicit DevWdg(QWidget *parent = 0);
    ~DevWdg();
    
public:
    void SetNum(QString strNum);
    void SetStatus(QString strStatus);
    void StartProcBar();
    void StopProcBar();
    void setApkNum(int nIns, int nTotal);
    void StartPercLab();
    void StopPercLab();
    void DevWdgPrecess(USB_State* usbState);
    void setPaletteWithStatus();

private:
    Ui::DevWdg *ui;
    QString strStatus;
    int nTotalApk;
    int nInsApk;
    USB_State* usbState;

public slots:
    void progRun();
    void percRun();
    void onUpdateState(int);
};

#endif // DEVWDG_H
