#include "CommunicationProvider.hpp"

namespace communication {
    CommunicationProvider::CommunicationProvider(QBluetoothSocket* socket, QObject* parent)
        : QObject(parent)
        , socket(socket)
        , currentData()
        , remainingToRead(0) {
        socket->setParent(this);
    }

    void CommunicationProvider::sendMessage(const player_protocol::Message &message) {

    }

    void CommunicationProvider::handleNewData() {

    }
}
