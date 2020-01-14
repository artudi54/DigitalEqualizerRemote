#include "RequestSender.hpp"
#include <player_protocol/request/ChangeMediumRequest.hpp>
#include <player_protocol/request/ChangeVolumeRequest.hpp>
#include <player_protocol/request/PauseRequest.hpp>
#include <player_protocol/request/PlaylistRequest.hpp>
#include <player_protocol/request/PlayRequest.hpp>
#include <player_protocol/request/SeekRequest.hpp>
#include <player_protocol/request/StopRequest.hpp>

namespace communication {
    RequestSender::RequestSender(CommunicationProvider* communicationProvider, QObject* parent)
        : QObject(parent)
        , communicationProvider(communicationProvider)
    {}

    void RequestSender::sendChangeMediumRequest(const QString &newMedium) {
        qDebug() << "MediumRequest: " << newMedium;
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

    void RequestSender::sendSeekRequest(double position) {
        communicationProvider->sendMessage(player_protocol::request::SeekRequest(static_cast<float>(position)));
    }

    void RequestSender::sendStopRequest() {
        communicationProvider->sendMessage(player_protocol::request::StopRequest());
    }

}