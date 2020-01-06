#include "DeviceConnector.hpp"

namespace communication {
    DeviceConnector::DeviceConnector(QObject* parent)
        : QObject(parent)
        , finding(false)
        , searchedName()
        , discoveryAgent(nullptr)
        , bluetoothAddress()
        , bluetoothUuid()
        , localDevice(nullptr)
        , socket(nullptr) {}

    void DeviceConnector::find(const QString &hostName) {
        if (finding) {
            throw std::runtime_error("Connector is already searching for host");
        }

        finding = true;
        searchedName = hostName;
        discoveryAgent = new QBluetoothDeviceDiscoveryAgent();
        connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &DeviceConnector::handleHostFound, Qt::QueuedConnection);
        connect(discoveryAgent, QOverload<QBluetoothDeviceDiscoveryAgent::Error>::of(&QBluetoothDeviceDiscoveryAgent::error), this, &DeviceConnector::handleDiscoveryError, Qt::QueuedConnection);

        discoveryAgent->start();
    }

    QBluetoothSocket *DeviceConnector::retrieveSocket() {
        if (socket != nullptr) {
            socket->disconnect(); // disconnect signals
        }
        return std::exchange(socket, nullptr);
    }

    void DeviceConnector::handleHostFound(const QBluetoothDeviceInfo &info) {
        if (info.name() != searchedName)
            return;
        discoveryAgent->deleteLater();
        discoveryAgent = nullptr;
        bluetoothAddress = info.address();
        bluetoothUuid = info.serviceUuids().empty() ? QBluetoothUuid() : info.serviceUuids()[0];
        localDevice = new QBluetoothLocalDevice(this);
        connect(localDevice, &QBluetoothLocalDevice::pairingFinished, this, &DeviceConnector::handlePairingFinished);
        connect(localDevice, &QBluetoothLocalDevice::error, this, &DeviceConnector::handlePairingError);
        localDevice->requestPairing(info.address(), QBluetoothLocalDevice::Paired);
    }

    void DeviceConnector::handleDiscoveryError() {
        QString message = discoveryAgent->errorString();
        discoveryAgent->stop();
        discoveryAgent->deleteLater();
        unsetParameters();
        emit errorOccurred(message);
    }

    void DeviceConnector::handlePairingFinished(const QBluetoothAddress &address) {
        assert(address == bluetoothAddress);
        localDevice->deleteLater();
        localDevice = nullptr;

        socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
        connect(socket, &QBluetoothSocket::connected, this, &DeviceConnector::handleConnected);
        connect(socket, QOverload<QBluetoothSocket::SocketError>::of(&QBluetoothSocket::error), this, &DeviceConnector::handleConnectionError);
        socket->connectToService(bluetoothAddress, bluetoothUuid);
    }

    void DeviceConnector::handlePairingError() {
        localDevice->deleteLater();
        unsetParameters();
        emit errorOccurred("Failed to pair with: " + searchedName);
    }

    void DeviceConnector::handleConnected() {
        unsetParameters();
        emit found();
    }

    void DeviceConnector::handleConnectionError() {
        QString message = socket->errorString();
        socket->deleteLater();
        unsetParameters();
        emit errorOccurred(message);
    }

    void DeviceConnector::unsetParameters() {
        finding = false;
        searchedName.clear();
        discoveryAgent = nullptr;
        bluetoothAddress.clear();
        bluetoothUuid = QBluetoothUuid();
        localDevice = nullptr;
        socket = nullptr;
    }
}