#include "PlayerController.hpp"
#include <QCoreApplication>
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

    void PlayerController::switchPlayState() {
        if (!playerModel.hasValidIndex())
            return;
        if (playerModel.getPlayState() == model::PlayState::PLAYING)
            requestSender->sendPauseRequest();
        else if (playerModel.getPlayState() == model::PlayState::PAUSED || playerModel.getPlayState() == model::PlayState::STOPPED)
            requestSender->sendPlayRequest();
    }

    void PlayerController::stopPlayer() {
        if (!playerModel.hasValidIndex())
            return;
        if (playerModel.getPlayState() != model::PlayState::STOPPED)
            requestSender->sendStopRequest();
    }

    void PlayerController::playNext() {
        if (!playerModel.hasValidIndex())
            return;
        if (playerModel.getCurrentIndex() == playerModel.getPlaylist().size() - 1)
            return;
        requestSender->sendChangeMediumRequest(playerModel.getPlaylist()[playerModel.getCurrentIndex() + 1]);
        if (playerModel.getPlayState() == model::PlayState::PLAYING)
            requestSender->sendPlayRequest();
    }

    void PlayerController::playPrevious() {

    }

    void PlayerController::setPlayerVolume(unsigned volume) {
        if (volume > 100)
            return;
        if (volume == playerModel.getVolume())
            return;
        requestSender->sendChangeVolumeRequest(volume);
    }

    void PlayerController::setPlayedSource(unsigned idx) {
        qDebug() << "Selected source:" << idx;
        if (idx >= static_cast<unsigned>(playerModel.getPlaylist().size()))
            return;
        if (static_cast<int>(idx) == playerModel.getCurrentIndex())
            return;
        requestSender->sendChangeMediumRequest(playerModel.getPlaylist()[static_cast<int>(idx)]);
        qDebug() << "Selected source sent:" << idx;

    }

    void PlayerController::seekPlayerPosition(double time) {
        if (time > playerModel.getTotalTime())
            return;
        if (time == playerModel.getCurrentTime())
            return;
        requestSender->sendSeekRequest(time);
    }

    void PlayerController::setEqualizerBandValue(double value, unsigned idx) {
        QList<model::EqualizerBand*>& bands = playerModel.getEqualizerParameters()->getFrequencyDbGains();
        if (idx > static_cast<unsigned>(bands.size()))
            return;
        bands[static_cast<int>(idx)]->setValue(value);
        requestSender->sendChangeEqualizerParametersRequest(playerModel.getEqualizerParameters());
    }

    void PlayerController::setOverallGainValue(double value) {
        model::EqualizerBand* overallGainBand = playerModel.getEqualizerParameters()->getDbGain();
        overallGainBand->setValue(value);
        requestSender->sendChangeEqualizerParametersRequest(playerModel.getEqualizerParameters());
    }

    void PlayerController::resetEqualizer() {
        QList<model::EqualizerBand*>& bands = playerModel.getEqualizerParameters()->getFrequencyDbGains();
        model::EqualizerBand* overallGainBand = playerModel.getEqualizerParameters()->getDbGain();
        for (auto band : bands)
            band->setValue(0.0);
        overallGainBand->setValue(0.0);
        requestSender->sendChangeEqualizerParametersRequest(playerModel.getEqualizerParameters());
    }

    void PlayerController::errorCloseApplication() {
        QCoreApplication::exit(-1);
    }

    void PlayerController::setupConnection(QBluetoothSocket *bluetoothSocket) {
        communicationProvider = new communication::CommunicationProvider(bluetoothSocket, this);
        requestSender = new communication::RequestSender(communicationProvider, this);
        responseHandler = new communication::ResponseHandler(playerModel, this);

        connect(communicationProvider, &communication::CommunicationProvider::messageReceived, responseHandler, &communication::ResponseHandler::handleResponse);
        connect(communicationProvider, &communication::CommunicationProvider::errorOccurred, this, &PlayerController::handleFatalError);

        requestSender->sendResetRequest();
        requestSender->sendPlaylistRequest();
        connectionModel.notifyConnected();
    }

    void PlayerController::handleConnectionError(const QString &message) {
        connectionModel.notifyErrorOccurred(message);
    }

    void PlayerController::handleFatalError(const QString &message) {
        qDebug() << "Error:" << message.toStdString().c_str();
    }
}
