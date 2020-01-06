#pragma once
#include <array>
#include <memory>
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
        void emitFailedToRead();
        void emitFailedToSend();

        static std::array<char, 1024> dataBuffer;

        QBluetoothSocket* socket;
        std::size_t nextMessageSize;
        std::unique_ptr<player_protocol::Message> lastMessage;
    };
}