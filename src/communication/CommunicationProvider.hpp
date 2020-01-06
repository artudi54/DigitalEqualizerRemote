#pragma once
#include <QObject>
#include <QBluetoothSocket>
#include <player_protocol/Message.hpp>

namespace communication {
    class CommunicationProvider : public QObject {
        Q_OBJECT
    public:
        explicit CommunicationProvider(QBluetoothSocket* socket, QObject* parent = nullptr);
        void sendMessage(const player_protocol::Message& message);

    signals:
        void messageReceived(const player_protocol::Message& message);
        void errorOccurred(const QString& message);

    private:
        void handleNewData();

        QBluetoothSocket* socket;
        QByteArray currentData;
        std::size_t remainingToRead;
    };
}