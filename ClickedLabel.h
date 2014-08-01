#ifndef CLICKEDLABEL_H
#define CLICKEDLABEL_H

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>
#include <QApplication>

class ClickedLabel : public QLabel
{
    Q_OBJECT
signals:
    void clicked();

public:
    ClickedLabel(int size = -1, QWidget *parent=0):QLabel(parent)
    {
        if (size != -1)
        {
            QFont font = QApplication::font();
            font.setPointSize(size);
            setFont(font);
        }
    }

    ~ClickedLabel(){}
protected:
    void mousePressEvent(QMouseEvent *ev)
    {
        if(ev->button() == Qt::LeftButton )
        {
             emit clicked();
        }
    }
};

#endif // CLICKEDLABEL_H
