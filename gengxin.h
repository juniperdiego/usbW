#ifndef GENGXIN_H
#define GENGXIN_H
#include <QDialog>
#include <QCloseEvent>
#include <QMovie>
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
    void StartUpdate();
    void StartUpSoft();
    void StopUpdate();
    bool getUpdateState();

private:
    DataUpdate* m_dataUp;
    QMovie* MvLoading;
    bool m_updateState;

public slots:
    void OnOk();
    void UpDone();
    void OnCancle();
    void OnTerm();
    void updateStartVersion();
    void updateVersion();

private:
    Ui::Gengxin *ui;
};

#endif // DIALOG_H
