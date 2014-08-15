#ifndef WENJIAN_H
#define WENJIAN_H

#include "global.h"
#include <QProcess>

namespace Ui {
class wenjian;
}

class wenjian : public QDialog
{
    Q_OBJECT

public:
    explicit wenjian(QWidget *parent = 0);
    ~wenjian();

    void UpdateContent();

private slots:
    void onreturn();
    void onPkgChanged(int);
    void setFreeSpace1(int);

private:
    void setFreeSpace();
    void setUpdatetime();
    void setUpdatenum();

private:
    vector<pkgInfo> m_pkgInfos;
    apkDB m_apkDB;
    pkgDB m_pkgDB;

    Ui::wenjian *ui;
    QProcess*   m_process;
};

#endif // WENJIAN_H
