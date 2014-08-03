#ifndef GENGXIN_H
#define GENGXIN_H
#include "dataupdate.h"

namespace Ui {
class Gengxin;
}

class Gengxin : public QDialog
{
    Q_OBJECT

public:
    explicit Gengxin(bool start = false, QWidget *parent = 0);
    ~Gengxin();

protected:
    void closeEvent(QCloseEvent*);

public:
    void SetBtnInvis();
    void StartUpAll();
    void StartUpSoft();
    void StartUpData();
    bool getUpdateState();
    bool getUpdateDevState();

private:
    DataUpdate* m_dataUp;
    QMovie* MvLoading;
    bool m_updateState;
    bool m_updateDevState;

public slots:
    void OnTerm();
    void upSoftDone();
    void upDataDone();
    void onProgress(int, int);

private:
    Ui::Gengxin *ui;
};

#endif // DIALOG_H
