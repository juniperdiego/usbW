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

    void uploadRealData(const QString& data, const QString& id)
    {
        emit uploadData(data, id);
    }

signals:
    void updateState(int);
    void uploadData(const QString&, const QString& id);

private:
    static tongXin* _self;
};
