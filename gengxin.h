#ifndef GENGXIN_H
#define GENGXIN_H
#include <QDialog>
#include <QMovie>
#include "dataupdate.h"

namespace Ui {
class Gengxin;
}

class Gengxin : public QDialog
{
    Q_OBJECT

public:
    explicit Gengxin(QWidget *parent = 0);
    ~Gengxin();

public:
    void SetBtnInvis();
    void StartUpdate();
    void StopUpdate();
    bool getUpdateState();

private:
    DataUpdate* m_dataUp;
    QMovie* MvLoading;
    bool m_updateState;

private slots:
    void OnOk();
    void UpDone();
    void OnCancle();
    void OnTerm();
    void updateVersion();

private:
    Ui::Gengxin *ui;
};

#endif // DIALOG_H
