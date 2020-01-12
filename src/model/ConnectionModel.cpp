#include "ConnectionModel.hpp"
#include <QDebug>

namespace model {
    ConnectionModel::ConnectionModel(QObject *parent)
        : QObject(parent) {}

    void ConnectionModel::notifyStartedConnecting() {
        qDebug() << "Connecting";
        emit startedConnecting();
    }

    void ConnectionModel::notifyConnected() {
        qDebug() << "Connected";
        emit connected();
    }

    void ConnectionModel::notifyErrorOccurred(const QString &message) {
        emit errorOccurred(message);
    }
}