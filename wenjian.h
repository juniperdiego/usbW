#ifndef WENJIAN_H
#define WENJIAN_H

#include <QDialog>
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

private slots:
    void onreturn();
    void onPkgChanged(int);
    void setFreeSpace1(int);

private:
    void UpdateContent();
    void setFreeSpace();
    void setUpdatetime();
    void setUpdatenum();

private:
    Ui::wenjian *ui;
    QProcess*   m_process;
};

#endif // WENJIAN_H
