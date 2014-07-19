#include "mainwindow.h"
#include "wenjian.h"
#include "fuwuqi.h"
#include "baobiao.h"
#include "shangchuan.h"
#include "devprocess.h"
#include "help.h"
#include "usb_enum.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //setWindowFlags(Qt::FramelessWindowHint);

    //network Information
    QList<QNetworkInterface> NetInterfaceList;
    NetInterfaceList = QNetworkInterface::allInterfaces();
    foreach(QNetworkInterface net, NetInterfaceList)
    {
        //qDebug()<<net;
        if (net.name() == "eth0")
        {
            m_strDevID = net.hardwareAddress();
            break;
        }
    }
    Global::g_DevID = m_strDevID.toStdString();

    //m_netConf = new QNetworkConfigurationManager;
    //connect(m_netConf, SIGNAL(onlineStateChanged(bool)), this, SLOT(onlineStateChange(bool)));


    CreateLayout();

    QWidget* centralWidget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layout);
    mainLayout->addLayout(gridlayout);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    this->setFixedSize(800,480);

    CreateStatusbar();

    //   UsbState = new USB_State;
    /*DevProcess* DevPro = new DevProcess;
      DevPro->start();
      this->connect(DevPro,SIGNAL(DevStatus(int)),this,SLOT(ScanUsbDev(int))); 线程间信号和槽*/
    //上传

    //QTimer* UnUpCount = new QTimer;
    //this->connect(UnUpCount, SIGNAL(timeout()), this, SLOT(SetUnUpCount()));
    //UnUpCount->start(PERIOD_SET_UNUPLOAD);
    SetUnUpCount();

#if 1
    m_fileUpLoad = new FileUpload;
    this->connect(m_fileUpLoad, SIGNAL(SetUpState(bool)), this, SLOT(setMvState(bool)));
    //QTimer::singleShot(10*60*1000,m_fileUpLoad,SLOT(start()));
    m_fileUpLoad->start();
#endif

}

MainWindow::~MainWindow()
{
}

void MainWindow::CreateLayout()
{
    layout = new QHBoxLayout;

    gxin = new ClickedLabel;
    gxin->setText("<u>更新</u>");
    // gxin->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    //gxin->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
    //gxin->setGeometry(QRect(1, 1, 20, 20));
    connect(gxin,SIGNAL(clicked()),this,SLOT(OnGengxin()));

    wluo = new ClickedLabel;
    wluo->setText("<u>网络</u>");
    wluo->setDisabled(true);

    wjian = new ClickedLabel;
    wjian->setText("<u>文件</u>");
    connect(wjian, SIGNAL(clicked()),this, SLOT(OnWenjian()));

    bbiao = new ClickedLabel;
    bbiao->setText("<u>报表</u>");
    connect(bbiao,SIGNAL(clicked()),this,SLOT(OnBaobiao()));

    fwuqi = new ClickedLabel;
    fwuqi->setText("<u>服务器</u>");
    connect(fwuqi,SIGNAL(clicked()),this,SLOT(OnFuwuqi()));

    cangkuid = new QLabel;
    cangkuid->setText("仓库ID:");

    id = new QLabel;
    QString strStoreID = "zb";//QString::fromStdString(sql_opt->get_stroeid());//@
    id->setText(strStoreID);

    //更新图标
    LabUpdateState = new QLabel;
    LabUpdateState->setVisible(false);
    MvUpdate = new QMovie(":/images/updating.gif");
    LabUpdateState->setMovie(MvUpdate);
    //connect(this,SIGNAL(setMvState()),MvUpdate,SLOT(ChangeMvState()));
    network = new QLabel;
    //if(m_netConf->isOnline())
    if(Global::s_netState)
    {
        QImage image1(":/images/NetConn24.ico");
        network->setPixmap(QPixmap::fromImage(image1));
    }
    else
    {
        QImage image1(":/images/NetDisConn24.ico");
        network->setPixmap(QPixmap::fromImage(image1));
    }
    //neicun = new QLabel;
    //QImage CardImage(":/images/SdCard24.ico");
    //neicun->setPixmap(QPixmap::fromImage(CardImage));

    shangchuan = new QPushButton;
    shangchuan->setText("上传");
    connect(shangchuan,SIGNAL(clicked()),this,SLOT(OnShangchuan()));

    weishangchuan = new QLabel;
    weishangchuan->setText("未上传:");

    wscnum = new QLabel;
    wscnum->setText("0");

    QSpacerItem* horizonSpacer1 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* horizonSpacer2 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    layout->addWidget(gxin);
    layout->addWidget(wluo);
    layout->addWidget(wjian);
    layout->addWidget(bbiao);
    layout->addWidget(fwuqi);
    layout->addSpacerItem(horizonSpacer1);
    layout->addWidget(cangkuid);
    layout->addWidget(id);
    layout->addSpacerItem(horizonSpacer2);
    layout->addWidget(network);
    //layout->addWidget(neicun);
    layout->addWidget(shangchuan);
    layout->addWidget(weishangchuan);
    layout->addWidget(wscnum);
    //layout->addWidget(LabUpdateState);


    gridlayout = new QGridLayout;
    for(int nDevCount = 0; nDevCount < DEVCOUNT; nDevCount++)
    {
        DevWdg* TmpDevWdg = new DevWdg;
        DevArray[nDevCount] = TmpDevWdg;
        //VecDev.append(TmpDevWdg);
        QString strNum = QString::number((nDevCount+1),10);
        DevArray[nDevCount]->SetNum(strNum);
        DevArray[nDevCount]->SetStatus(tr("空闲"));
        gridlayout->addWidget(DevArray[nDevCount],nDevCount/6,nDevCount%6);
    }
}

void MainWindow::CreateStatusbar()
{
    shebei = new QLabel;
    shebei->setText(tr("设备ID:"));
    sbid = new QLabel;
    sbid->setText(m_strDevID);
    kjl = new QLabel;
    kjl->setText(tr("      快精灵"));
    time = new QLabel;
    QDateTime im = QDateTime::currentDateTime();
    QString str = im.toString("yyyy-MM-dd hh:mm:ss ddd");
    time->setText(str);
    QTimer* timTm = new QTimer;
    connect(timTm,SIGNAL(timeout()),this,SLOT(TimeNow()));
    timTm->start(1000);
    jiaoshi = new ClickedLabel;
    jiaoshi->setText(tr("<u>校时</u>"));
    jiaoshi->setEnabled(false);
    m_jiaozhun->setText(tr("<u>屏幕校准</u>"));
    m_jiaozhun->setEnabled(false);
    connect(m_jiaozhun, SIGNAL(clicked()), this, SLOT(OnJiaoZhun()));
    help = new ClickedLabel;
    help->setText(tr("<u>帮助</u>"));
    connect(help, SIGNAL(clicked()), this, SLOT(OnHelp()));

    QStatusBar* statusBar = this->statusBar();
    statusBar->addWidget(shebei,1);
    statusBar->addWidget(sbid,2);
    statusBar->addWidget(kjl,3);
    statusBar->addWidget(time,4);
    statusBar->addWidget(jiaoshi,5);
    statusBar->addWidget(jiaoshi,6);
    statusBar->addWidget(help,7);
}

void MainWindow::startUsbScan()
{
    if (!m_updateState) return;

    call();

    m_usbScanTimer = new QTimer;
    connect(m_usbScanTimer,SIGNAL(timeout()),this,SLOT(ScanUsbDev()));
    m_usbScanTimer->start(1000);
}

void MainWindow::onlineStateChange(bool bState)
{
    if(bState)
    {
        QImage NetImage(":/NetConn24.ico");
        this->network->setPixmap(QPixmap::fromImage(NetImage));
    }
    else
    {
        QImage NetImage(":/NetDisConn24.ico");
        this->network->setPixmap(QPixmap::fromImage(NetImage));
    }
}
void MainWindow::OnGengxin(bool all)
{
    Gengxin UpLoadManual;
    UpLoadManual.show();
    UpLoadManual.StartUpdate();
    UpLoadManual.hide();

    m_updateState = UpLoadManual.getUpdateState();

    startUsbScan();
}

void MainWindow::OnWenjian()
{
    wenjian *wj = new wenjian;
    wj->show();
}
void MainWindow::OnBaobiao()
{
    baobiao *bb = new baobiao;
    bb->show();
}
void MainWindow::OnFuwuqi()
{
    fuwuqi *fq = new fuwuqi;
    fq->exec();
}
void MainWindow::OnShangchuan()
{
    //MvUpdate->start();
    Shangchuan *sh = new Shangchuan;
    sh->SetUpThread(this->m_fileUpLoad);
    sh->show();
}
void MainWindow::OnJiaoZhun()
{
}
void MainWindow::OnHelp()
{
    Help* HelpDoc = new Help;
    HelpDoc->show();
}

//Scanning USB Dev On Timer 1s
void MainWindow::ScanUsbDev()
{
    //qDebug("ScanUsbDev %d",i++);
    //    QString s = QString::number (g_i, 10);
    //    this->UsbDevHandle->SetNum(s);
    //    if(g_i%2)
    //    {
    //        this->UsbDevHandle->SetStatus(tr("占用"));
    //        this->UsbDevHandle->StartProcBar();
    //    }
    //    if( g_i >= 50)
    //        this->UsbDevHandle->StopProcBar();
    //    qDebug()<<g_i<<"\n";
    ///*    else
    //    {
    //        this->UsbDevHandle->SetStatus(tr("空闲"));
    //        this->UsbDevHandle->StopProcBar();
    //    }*/
    //    //this->UsbDevHandle->repaint();
    //    //test
    //    if( g_i== 0 )
    //    {
    //        UsbState->install_state = 0;
    //    }
    //    if( g_i >= 10 && g_i <=20)
    //    {
    //        UsbState->install_state = 1;
    //        UsbState->apk_num = (g_i -10);
    //        UsbState->apk_total = 10;
    //    }
    //    if(g_i > 20 && g_i < 25)
    //    {
    //        UsbState->install_state = 2;
    //    }
    //    if(g_i >=25 && g_i<30)
    //    {
    //        UsbState->install_state = 3;
    //    }
    //    if(g_i >= 30)
    //    {
    //        UsbState->install_state = 0;
    //    }
    //   //this->UsbDevHandle3->DevWdgPrecess(UsbState);
    //    for(int nCount = 2; nCount < DEVCOUNT; nCount++)
    //    {
    //        DevArray[nCount]->DevWdgPrecess(UsbState);
    //    }
    //    g_i++;

    for(int i =0; i < DEVCOUNT; i++)
    {
        //   Global::usb_state[i].install_state = 1;
        DevArray[i]->DevWdgPrecess(&(Global::usb_state[i]));
        if(Global::usb_state[i].install_state == 0 )
            DevArray[i]->SetStatus(tr("空闲"));
        else if(Global::usb_state[i].install_state ==1)
        {
            DevArray[i]->SetStatus(tr("安装中"));
        }
        else if(Global::usb_state[i].install_state == 2)
        {
            DevArray[i]->SetStatus(tr("完成"));
        }
        else if(Global::usb_state[i].install_state == 3)
        {
            DevArray[i]->SetStatus(tr("中断"));
        }
        else if(Global::usb_state[i].install_state == 4)
        {
            DevArray[i]->SetStatus(tr("失败"));
        }
    }
}

void MainWindow::TimeNow()
{
    QDateTime im = QDateTime::currentDateTime();
    QString str = im.toString("yyyy-MM-dd hh:mm:ss ddd");
    this->time->setText(str);
}

void MainWindow::setMvState(bool bState)
{
    if(bState)
        this->MvUpdate->start();
    else
        this->MvUpdate->stop();
}

int MainWindow::GetAllFiles()
{
    QString strPath = LOG_PATH;
    QDir dir(strPath);
    QFileInfoList FileInfoLst;
    QStringList strFileLst;
    strFileLst.clear();
    if( !dir.exists() )
    {
        return 0;
    }
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    dir.setSorting(QDir::Time);
    FileInfoLst = dir.entryInfoList();
    return FileInfoLst.count();
}
void MainWindow::SetUnUpCount()
{
    int nCount = GetAllFiles();
    this->wscnum->setText(QString::number(nCount, 10));
}
