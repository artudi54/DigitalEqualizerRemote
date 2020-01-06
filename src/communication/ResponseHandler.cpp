#include "ResponseHandler.hpp"
#include <algorithm>
#include <player_protocol/changed/MediumChangedMessage.hpp>
#include <player_protocol/changed/TimeChangedMessage.hpp>
#include <player_protocol/changed/VolumeChangedMessage.hpp>

#include <player_protocol/response/ErrorResponse.hpp>
#include <player_protocol/response/OkResponse.hpp>
#include <player_protocol/response/PlaylistResponse.hpp>

namespace communication {
    ResponseHandler::ResponseHandler(model::PlayerModel& playerModel, QObject *parent)
        : QObject(parent)
        , playerModel(playerModel) {}

    void ResponseHandler::handleResponse(const player_protocol::Message &message) {
        message.visit(*this);
    }

    void ResponseHandler::handleMessage(const player_protocol::changed::MediumChangedMessage &message) {
        try {
            playerModel.setCurrentMedium(QString::fromStdString(message.getMedium()));
        }
        catch (std::invalid_argument& exc) {
            emit errorOccurred(QString::fromUtf8(exc.what()));
        }
    }

    void ResponseHandler::handleMessage(const player_protocol::changed::TimeChangedMessage &message) {
        try {
            playerModel.setTimeRange(message.getCurrentTime(), message.getTotalTime());
        }
        catch (std::invalid_argument& exc) {
            emit errorOccurred(QString::fromUtf8(exc.what()));
        }
    }

    void ResponseHandler::handleMessage(const player_protocol::changed::VolumeChangedMessage &message) {
        try {
            playerModel.setVolume(message.getVolume());
        }
        catch (std::invalid_argument& exc) {
            emit errorOccurred(QString::fromUtf8(exc.what()));
        }
    }

    void ResponseHandler::handleMessage(const player_protocol::response::ErrorResponse &message) {
        emit errorOccurred(QString::fromStdString("Received error from server: " + message.getErrorMessage()));
    }

    void ResponseHandler::handleMessage(const player_protocol::response::OkResponse &message) {
        (void)message;
    }

    void ResponseHandler::handleMessage(const player_protocol::response::PlaylistResponse &message) {
        QStringList list;
        for (auto& file : message.getFiles())
            list.push_back(QString::fromStdString(file));
        try {
            playerModel.setPlaylist(list);
        }
        catch (std::invalid_argument& exc) {
            emit errorOccurred(QString::fromUtf8(exc.what()));
        }
    }

    void ResponseHandler::handleInvalidMessage(const player_protocol::Message &message) {
        (void)message;
        emit errorOccurred("Received unknown message");
    }
}
