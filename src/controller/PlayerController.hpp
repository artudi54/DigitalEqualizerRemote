#pragma once
#include <QObject>
#include <communication/CommunicationProvider.hpp>
#include <communication/RequestSender.hpp>
#include <communication/ResponseHandler.hpp>
#include <model/ConnectionModel.hpp>
#include <model/PlayerModel.hpp>

namespace controller {
    class PlayerController : public QObject {
        Q_OBJECT
    public:
        PlayerController(model::ConnectionModel& connectionModel, model::PlayerModel& playerModel, QObject* parent = nullptr);

        Q_INVOKABLE void connectToHost();
    private:
        void setupConnection(QBluetoothSocket* bluetoothSocket);
        void handleConnectionError(const QString& message);

        void handleFatalError(const QString& message);

        model::ConnectionModel& connectionModel;
        model::PlayerModel& playerModel;

        communication::CommunicationProvider* communicationProvider;
        communication::RequestSender* requestSender;
        communication::ResponseHandler* responseHandler;
    };
}