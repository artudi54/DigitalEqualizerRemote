#include "ConnectionModel.hpp"

namespace model {

    ConnectionModel::ConnectionModel(QObject *parent)
        : QObject(parent) {}

    void ConnectionModel::notifyStartedConnecting() {
        emit startedConnecting();
    }

    void ConnectionModel::notifyConnected() {
        emit connected();
    }

    void ConnectionModel::notifyErrorOccurred(const QString &message) {
        emit errorOccurred(message);
    }
}