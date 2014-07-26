#include "global.h"

class tongXin : public QObject
{
    Q_OBJECT
public:
    tongXin() {}

    static tongXin* getTongXin()
    {
        if (_self == NULL)
            _self = new tongXin;

        return _self;
    }

    void updateGui(int num)
    {
        emit updateState(num);
    }

signals:
    void updateState(int);

private:
    static tongXin* _self;
};
