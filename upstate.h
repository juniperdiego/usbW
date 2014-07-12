#ifndef UPSTATE_H
#define UPSTATE_H

#include <QDialog>

namespace Ui {
class UpState;
}

class UpState : public QDialog
{
    Q_OBJECT

public:
    explicit UpState(QWidget *parent = 0);
    ~UpState();

private:
    bool bDevState;
    bool bPkgState;
    bool bApkState;
public:
    void SetState(bool bDevStateIn, bool bPkgStateIn, bool bApkStateIn);

private:
    Ui::UpState *ui;
private slots:
    void OnConfirm();
};

#endif // UPSTATE_H
