#include "networkmanager.h"
#include "expensemanager.h"

NetworkManager::NetworkManager(QObject* parent)
    : QObject (parent){
}


void NetworkManager::onExpenseManagerRequestsPublish(void){
    // This function will either establish a TCP connection and send the data over HTTPS
    // Or it will use that already existing connection to send it.
    // It will then wait for a response, such as a final ACK that the server has successfully stored it.
    // And if it does nto send an ACK within a certain time period, we assume it has failled.
    // In either case, we set the _isSendingSuccessful.

    // For now this function is not fully implemented and just returns a success every time.
    _SetIsSendingSuccessful(true);
    emit SendingFinished(IsSendingSuccessful());
}

bool NetworkManager::IsSendingSuccessful(void){
    return _isSendingSuccessful;
}
