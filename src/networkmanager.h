#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H
#include "QObject"

class NetworkManager: public QObject{
    Q_OBJECT
public slots:
    void onExpenseManagerRequestsPublish(void);

signals:
    void SendingFinished(bool isSuccessful);

public:
    NetworkManager(QObject* parent);
    bool IsSendingSuccessful(void);

private:
    bool _isSendingSuccessful = false;

    void _SetIsSendingSuccessful(bool set){
        _isSendingSuccessful = set;
    }
};

#endif // NETWORKMANAGER_H
