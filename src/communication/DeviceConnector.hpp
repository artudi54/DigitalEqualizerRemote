#pragma once
#include <chrono>
#include <QObject>
#include <QBluetoothSocket>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothLocalDevice>
#include <QThread>
#include <QTimer>

namespace communication {
    class DeviceConnector : public QObject {
        Q_OBJECT
    public:
        explicit DeviceConnector(QObject* parent = nullptr);

        void find(const QString& hostName);
        QBluetoothSocket* retrieveSocket();

    signals:
        void found();
        void errorOccurred(const QString& message);

    private:
        void handleHostFound(const QBluetoothDeviceInfo &info);
        void handleDiscoveryError();

        void handlePairingFinished(const QBluetoothAddress &address);
        void handlePairingError();

        void handleConnected();
        void handleConnectionError();

        void unsetParameters();

        bool finding;
        QString searchedName;
        QBluetoothDeviceDiscoveryAgent* discoveryAgent;
        QBluetoothAddress bluetoothAddress;
        QBluetoothUuid bluetoothUuid;
        QBluetoothLocalDevice* localDevice;
        QBluetoothSocket* socket;
    };
}