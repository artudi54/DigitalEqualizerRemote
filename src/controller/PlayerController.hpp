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

        Q_INVOKABLE void switchPlayState();
        Q_INVOKABLE void stopPlayer();
        Q_INVOKABLE void playNext();
        Q_INVOKABLE void playPrevious();

        Q_INVOKABLE void setPlayerVolume(unsigned volume);

        Q_INVOKABLE void setPlayedSource(unsigned idx);
        Q_INVOKABLE void seekPlayerPosition(double time);

        Q_INVOKABLE void setEqualizerBandValue(double value, unsigned idx);
        Q_INVOKABLE void setOverallGainValue(double value);
        Q_INVOKABLE void resetEqualizer();

        Q_INVOKABLE void errorCloseApplication();

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
