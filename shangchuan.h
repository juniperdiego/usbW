#ifndef SHANGCHUAN_H
#define SHANGCHUAN_H

#include <QDialog>
#include "global.h"
#include "fileupload.h"

namespace Ui {
class Shangchuan;
}

class Shangchuan : public QDialog
{
    Q_OBJECT

public:
    explicit Shangchuan(QWidget *parent = 0);
    ~Shangchuan();
    void SetUpThread(FileUpload* File_Up);
    void updateContents();

public slots:
    void Return();
    void Search();
    void Upload();
    void UploadData();

private:
    logDB m_logDB;    
    reportDB m_rptDB;

private:
    Ui::Shangchuan *ui;

    QLabel* LabUpdateState;
    QMovie* MvUpdate;
};

#endif // SHANGCHUAN_H
