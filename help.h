#ifndef HELP_H
#define HELP_H

#include <QDialog>

namespace Ui {
class Help;
}

class Help : public QDialog
{
    Q_OBJECT
    
public:
    explicit Help(QWidget *parent = 0);
    ~Help();
    
private:
    Ui::Help *ui;

private slots:
    void OnBack();
};

#endif // HELP_H
