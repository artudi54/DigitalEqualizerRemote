#include "ResponseHandler.hpp"
#include <algorithm>
#include <player_protocol/changed/MediumChangedMessage.hpp>
#include <player_protocol/changed/PlayerStateChangedMessage.hpp>
#include <player_protocol/changed/TimeChangedMessage.hpp>
#include <player_protocol/changed/VolumeChangedMessage.hpp>

#include <player_protocol/response/ErrorResponse.hpp>
#include <player_protocol/response/OkResponse.hpp>
#include <player_protocol/response/PlaylistResponse.hpp>
#include <QDebug>

namespace communication {
    ResponseHandler::ResponseHandler(model::PlayerModel& playerModel, QObject *parent)
        : QObject(parent)
        , playerModel(playerModel) {}

    void ResponseHandler::handleResponse(const player_protocol::Message &message) {
        message.visit(*this);
    }

    void ResponseHandler::handleMessage(const player_protocol::changed::MediumChangedMessage &message) {
        qDebug() << "new medium:" << message.getMedium().c_str();
        try {
            playerModel.setCurrentMedium(QString::fromStdString(message.getMedium()));
        }
        catch (std::invalid_argument& exc) {
            emit errorOccurred(QString::fromUtf8(exc.what()));
        }
    }

    void ResponseHandler::handleMessage(const player_protocol::changed::PlayerStateChangedMessage &message) {
        auto playState = static_cast<model::PlayState>(message.getPlayerState());
        try {
            playerModel.setPlayState(playState);
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
            qDebug() << "Volume:" << message.getVolume();
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
            qDebug() << "Playlist:" << list;
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
