#include "global.h"
#include "mainwindow.h"
#include "wenjian.h"
#include "baobiao.h"
#include "shangchuan.h"
#include "devprocess.h"
#include "help.h"
#include "usb_enum.h"
#include "touch/calibration.h"

DevWdg* MainWindow::s_devArray[DEVCOUNT] = {NULL};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
#ifdef ARM
    setWindowFlags(Qt::FramelessWindowHint);
#endif

    m_shangChun = NULL;

    //network Information
    QList<QNetworkInterface> NetInterfaceList;
    NetInterfaceList = QNetworkInterface::allInterfaces();
    foreach(QNetworkInterface net, NetInterfaceList)
    {
        if (net.name() == "eth0")
        {
            m_strDevID = net.hardwareAddress();
            break;
        }
    }
    Global::g_DevID = m_strDevID.toStdString();

    CreateLayout();

    QWidget* centralWidget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layout);
    mainLayout->addLayout(gridlayout);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    this->setFixedSize(800,480);

    CreateStatusbar();

    SetUnUpCount();

    m_fileUpLoad = FileUpload::getFileUpload();

    QTimer* netTimer = new QTimer;
    connect(netTimer, SIGNAL(timeout()), this, SLOT(onlineStateChange()));
    netTimer->start(10000);

    //if (!Global::s_netState)
    //    startUsbScan();
}

MainWindow::~MainWindow()
{
}

void MainWindow::CreateLayout()
{
    layout = new QHBoxLayout;

    QHBoxLayout* leftLayout = new QHBoxLayout;
    leftLayout->setContentsMargins(10, 0, 10, 0);
    leftLayout->setSpacing(20);

    gxin = new ClickedLabel(20);
    gxin->setText("<u>更新</u>");
    connect(gxin,SIGNAL(clicked()),this,SLOT(OnGengxin()));

    wluo = new ClickedLabel(20);
    wluo->setText("<u>网络</u>");
    wluo->setDisabled(true);

    wjian = new ClickedLabel(20);
    wjian->setText("<u>文件</u>");
    connect(wjian, SIGNAL(clicked()),this, SLOT(OnWenjian()));

    bbiao = new ClickedLabel(20);
    bbiao->setText("<u>报表</u>");
    connect(bbiao,SIGNAL(clicked()),this,SLOT(OnBaobiao()));

    fwuqi = new ClickedLabel(20);
    fwuqi->setVisible(false);
    fwuqi->setText("<u>服务器</u>");
    connect(fwuqi,SIGNAL(clicked()),this,SLOT(OnJiaoZhun()));

    cangkuid = new QLabel;
    cangkuid->setText("仓库ID:");

    devDB devDB;
    string cid;
    devDB.get(CHAN_ID, cid);
    id = new QLabel;
    id->setText(QString::fromStdString(cid));

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
    leftLayout->addWidget(gxin);
    leftLayout->addWidget(wluo);
    leftLayout->addWidget(wjian);
    leftLayout->addWidget(bbiao);
    layout->addLayout(leftLayout);

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
        s_devArray[nDevCount] = TmpDevWdg;
        //VecDev.append(TmpDevWdg);
        QString strNum = QString::number((nDevCount+1),10);
        s_devArray[nDevCount]->SetNum(strNum);
        s_devArray[nDevCount]->SetStatus(tr("空闲"));
        gridlayout->addWidget(s_devArray[nDevCount],nDevCount/6,nDevCount%6);
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
    QString str = im.toString("yyyy-MM-dd hh:mm:ss");
    time->setText(str);
    QTimer* timTm = new QTimer;
    connect(timTm,SIGNAL(timeout()),this,SLOT(TimeNow()));
    timTm->start(1000);
    jiaoshi = new ClickedLabel;
    jiaoshi->setText(tr("<u>校时</u>"));
    jiaoshi->setEnabled(false);
    m_jiaozhun = new ClickedLabel;
    m_jiaozhun->setText(tr("<u>屏幕校准</u>"));
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
    statusBar->addWidget(m_jiaozhun,6);
    statusBar->addWidget(help,7);
}

void MainWindow::startUsbScan()
{
    call();
}

void MainWindow::onlineStateChange()
{
    static bool netUp = false;
    bool bState = false;
    bool prevNetState = Global::s_netState;
    QNetworkInterface netInterface = QNetworkInterface::interfaceFromName(NET_NAME);
    //qDebug()<<netInterface;
    if (netInterface.isValid())
    {
        if (netInterface.flags().testFlag(QNetworkInterface::IsUp) && 
            netInterface.flags().testFlag(QNetworkInterface::IsRunning))
        {
            if (!netUp) 
            {
                repaint();
                netUp = true;
            }
            QHostInfo host = QHostInfo::fromName(WEB_SITE);
            if (!host.addresses().isEmpty()) 
            {
                repaint();
                Global::s_netState = true;
                bState = true;
                if (m_shangChun == NULL)
                    m_shangChun = new Shangchuan;
                m_shangChun->UploadData();
            }
            else
            {
                repaint();
                Global::s_netState = false;
                bState = false;
            }
        }
        else
        {
            repaint();
            Global::s_netState = false;
            bState = false;
            netUp = false;
        }
    }

    if(bState)
    {
        QImage NetImage(":/images/NetConn24.ico");
        this->network->setPixmap(QPixmap::fromImage(NetImage));
    }
    else
    {
        QImage NetImage(":/images/NetDisConn24.ico");
        this->network->setPixmap(QPixmap::fromImage(NetImage));
    }

    SetUnUpCount();

    if (prevNetState && !Global::s_netState)
    {
        QMessageBox::information(this, APP_NAME, 
                "网络连接断开，系统将离线运行！");
    }
}
void MainWindow::OnGengxin(bool all)
{
    static Gengxin* up = new Gengxin;
    up->setWindowModality(Qt::ApplicationModal);
    up->show();
    if (all)
        up->StartUpAll();
    else
        up->StartUpData();
    up->hide();

    m_updateState = up->getUpdateState();

    devDB devDB;
    string cid;
    devDB.get(CHAN_ID, cid);
    if (id) 
        id->setText(QString::fromStdString(cid));

    //if (m_updateState)
        startUsbScan();
}

void MainWindow::OnWenjian()
{
    static wenjian *wj = new wenjian;
    wj->UpdateContent();
    wj->exec();
}
void MainWindow::OnBaobiao()
{
    static baobiao *bb = new baobiao;
    bb->exec();
}
void MainWindow::OnFuwuqi()
{
    //static fuwuqi *fq = new fuwuqi;
    //fq->exec();
}
void MainWindow::OnShangchuan()
{
    if (m_shangChun == NULL)
        m_shangChun = new Shangchuan;

    m_shangChun->updateContents();
    m_shangChun->exec();
}
void MainWindow::OnJiaoZhun()
{
#ifdef ARM
    QFile pointercal("/etc/pointercal");
    if (pointercal.exists()) 
    {
        pointercal.copy("/etc/pointercal.bak");
        pointercal.remove();
    }
    if (!pointercal.exists() || pointercal.size() == 0)
    {
        for (;;)
        {
            Calibration cal;
            cal.exec();

            QMessageBox message(QMessageBox::Question,
                    QString::fromUtf8("提示"),
                    QString::fromUtf8("<p>请确认触摸屏已经校正完毕。</p>"
                        "<p>如果你不确认此提示消息，将在10秒钟后重新进入触摸屏设置程序。</p>"),
                    QMessageBox::Yes | QMessageBox::No);

            QTimer::singleShot(10 * 1000, &message, SLOT(reject()));
            int reply = message.exec();
            if (reply == QMessageBox::Yes)
            {
                ::sync();
                break;
            }
        }
    }
#endif
}
void MainWindow::OnHelp()
{
    static Help* HelpDoc = new Help;
    HelpDoc->exec();
}

//Scanning USB Dev On Timer 1s
void MainWindow::ScanUsbDev()
{
    for(int i =0; i < DEVCOUNT; i++)
    {
        s_devArray[i]->DevWdgPrecess(&(Global::usb_state[i]));
    }
}

void MainWindow::TimeNow()
{
    QDateTime im = QDateTime::currentDateTime();
    QString str = im.toString("yyyy-MM-dd hh:mm:ss");
    this->time->setText(str);
}

void MainWindow::setMvState(bool bState)
{
    if(bState)
        this->MvUpdate->start();
    else
        this->MvUpdate->stop();
}

void MainWindow::SetUnUpCount()
{
    reportDB rptDB;
    vector<reportInfo> rpts;
    rptDB.getUnuploadedData(rpts); 
    this->wscnum->setText(QString().setNum(rpts.size()));
}
