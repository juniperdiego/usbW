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

private:
    DataUpdate* m_dataUp;
    QMovie* MvLoading;
    bool m_updateState;

public slots:
    void OnOk();
    void OnCancle();
    void OnTerm();
    void upSoftDone();
    void upDataDone();

private:
    Ui::Gengxin *ui;
};

#endif // DIALOG_H
