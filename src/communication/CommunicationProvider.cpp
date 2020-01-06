#include "CommunicationProvider.hpp"
#include <player_protocol/MessageSerializer.hpp>

namespace communication {
    std::array<char, 1024> CommunicationProvider::dataBuffer{};

    CommunicationProvider::CommunicationProvider(QBluetoothSocket* socket, QObject* parent)
        : QObject(parent)
        , socket(socket)
        , nextMessageSize(0)
        , lastMessage(nullptr) {
        socket->setParent(this);
        connect(socket, &QBluetoothSocket::readyRead, this, &CommunicationProvider::handleNewData);
    }

    void CommunicationProvider::sendMessage(const player_protocol::Message &message) {
        std::uint32_t size = player_protocol::MessageSerializer::serialize(message, dataBuffer.data());
        if (socket->write(reinterpret_cast<char*>(&size), sizeof(std::uint32_t)) != sizeof(std::uint32_t)) {
            emitFailedToSend();
            return;
        }
        if (socket->write(dataBuffer.data(), size) != size) {
            emitFailedToSend();
            return;
        }
    }

    void CommunicationProvider::handleNewData() {
        if (nextMessageSize == 0) {
            if (static_cast<std::size_t>(socket->bytesAvailable()) < sizeof(std::uint32_t))
                return;
            if (socket->read(reinterpret_cast<char *>(&nextMessageSize), sizeof(std::uint32_t)) !=
                sizeof(std::uint32_t)) {
                emitFailedToRead();
                return;
            }
        }

        if (static_cast<std::size_t>(socket->bytesAvailable()) < nextMessageSize)
            return;
        if (socket->read(dataBuffer.data(), static_cast<qint64>(nextMessageSize)) !=
            static_cast<qint64>(nextMessageSize)) {
            emitFailedToRead();
            return;
        }

        try {
            lastMessage = player_protocol::MessageSerializer::deserialize(dataBuffer.data());
        }
        catch (std::exception& exc) {
            emit errorOccurred(exc.what());
            return;
        }

        emit messageReceived(*lastMessage);
        nextMessageSize = 0;
        handleNewData();
    }

    void CommunicationProvider::emitFailedToRead() {
        emit errorOccurred("Failed to read message from remote host");

    }

    void CommunicationProvider::emitFailedToSend() {
        emit errorOccurred("Failed to send message to remote host");
    }
}
