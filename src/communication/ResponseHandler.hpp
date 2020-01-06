#pragma once
#include <QObject>
#include <player_protocol/MessageVisitor.hpp>
#include <model/PlayerModel.hpp>

namespace communication {
    class ResponseHandler : public QObject , private player_protocol::MessageClientVisitor {
        Q_OBJECT
    public:
        explicit ResponseHandler(model::PlayerModel& playerModel, QObject* parent = nullptr);
        void handleResponse(const player_protocol::Message& message);

    signals:
        void errorOccurred(const QString& message);

    private:
        void handleMessage(const player_protocol::changed::MediumChangedMessage &message) override;
        void handleMessage(const player_protocol::changed::TimeChangedMessage &message) override;
        void handleMessage(const player_protocol::changed::VolumeChangedMessage &message) override;

        void handleMessage(const player_protocol::response::ErrorResponse &message) override;
        void handleMessage(const player_protocol::response::OkResponse &message) override;
        void handleMessage(const player_protocol::response::PlaylistResponse &message) override;

        void handleInvalidMessage(const player_protocol::Message &message) override;

        model::PlayerModel& playerModel;
    };
}