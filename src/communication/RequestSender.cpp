#include "RequestSender.hpp"
#include <player_protocol/request/ChangeEqualizerParametersRequest.hpp>
#include <player_protocol/request/ChangeMediumRequest.hpp>
#include <player_protocol/request/ChangeVolumeRequest.hpp>
#include <player_protocol/request/PauseRequest.hpp>
#include <player_protocol/request/PlaylistRequest.hpp>
#include <player_protocol/request/PlayRequest.hpp>
#include <player_protocol/request/ResetRequest.hpp>
#include <player_protocol/request/SeekRequest.hpp>
#include <player_protocol/request/StopRequest.hpp>

namespace communication {
    RequestSender::RequestSender(CommunicationProvider* communicationProvider, QObject* parent)
        : QObject(parent)
        , communicationProvider(communicationProvider)
    {}

    void RequestSender::sendChangeEqualizerParametersRequest(const model::EqualizerModel *equalizerModel) {
        qDebug() << "send EqualizerRequest: ";
        player_protocol::EqualizerParameters equalizerParameters;
        equalizerParameters.setGainDb(static_cast<float>(equalizerModel->getDbGain()->getValue()));
        for (std::size_t i = 0; i < 10; ++i)
            equalizerParameters.setGainDbAt(i, static_cast<float>(equalizerModel->getFrequencyDbGains()[static_cast<int>(i)]->getValue()));
        communicationProvider->sendMessage(player_protocol::request::ChangeEqualizerParametersRequest(equalizerParameters));
    }

    void RequestSender::sendChangeMediumRequest(const QString &newMedium) {
        qDebug() << "send MediumRequest: " << newMedium;
        communicationProvider->sendMessage(player_protocol::request::ChangeMediumRequest(newMedium.toStdString()));
    }

    void RequestSender::sendChangeVolumeRequest(std::uint32_t newVolume) {
        communicationProvider->sendMessage(player_protocol::request::ChangeVolumeRequest(newVolume));
    }

    void RequestSender::sendPauseRequest() {
        communicationProvider->sendMessage(player_protocol::request::PauseRequest());
    }

    void RequestSender::sendPlaylistRequest() {
        communicationProvider->sendMessage(player_protocol::request::PlaylistRequest());
    }

    void RequestSender::sendPlayRequest() {
        communicationProvider->sendMessage(player_protocol::request::PlayRequest());
    }

    void RequestSender::sendResetRequest() {
        communicationProvider->sendMessage(player_protocol::request::ResetRequest());
    }

    void RequestSender::sendSeekRequest(double position) {
        communicationProvider->sendMessage(player_protocol::request::SeekRequest(static_cast<float>(position)));
    }

    void RequestSender::sendStopRequest() {
        communicationProvider->sendMessage(player_protocol::request::StopRequest());
    }

}