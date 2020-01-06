#include "PlayerController.hpp"
#include <communication/DeviceConnector.hpp>

namespace controller {
    PlayerController::PlayerController(model::ConnectionModel &connectionModel, model::PlayerModel &playerModel, QObject *parent)
        : QObject(parent)
        , connectionModel(connectionModel)
        , playerModel(playerModel) {

    }

    void PlayerController::connectToHost() {
        auto* connector = new communication::DeviceConnector(this);
        connect(connector, &communication::DeviceConnector::found, this, [this, connector] {
            setupConnection(connector->retrieveSocket());
        });
        connect(connector, &communication::DeviceConnector::errorOccurred, this, &PlayerController::handleConnectionError);

        connector->find("DigitalEqualizer");
        connectionModel.notifyStartedConnecting();
    }

    void PlayerController::setupConnection(QBluetoothSocket *bluetoothSocket) {
        communicationProvider = new communication::CommunicationProvider(bluetoothSocket, this);
        requestSender = new communication::RequestSender(communicationProvider, this);
        responseHandler = new communication::ResponseHandler(playerModel, this);

        connect(communicationProvider, &communication::CommunicationProvider::messageReceived, responseHandler, &communication::ResponseHandler::handleResponse);
        connect(communicationProvider, &communication::CommunicationProvider::errorOccurred, this, &PlayerController::handleFatalError);

        requestSender->sendPlaylistRequest();
        connectionModel.notifyConnected();
    }

    void PlayerController::handleConnectionError(const QString &message) {
        connectionModel.notifyErrorOccurred(message);
    }

    void PlayerController::handleFatalError(const QString &message) {
        // todo
    }
}
