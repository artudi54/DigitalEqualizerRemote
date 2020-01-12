#pragma once
#include <QObject>
#include <communication/CommunicationProvider.hpp>

namespace communication {
    class RequestSender : public QObject {
        Q_OBJECT
    public:
        explicit RequestSender(CommunicationProvider* communicationProvider, QObject* parent = nullptr);

        void sendChangeMediumRequest(const QString& newMedium);
        void sendChangeVolumeRequest(std::uint32_t newVolume);
        void sendPauseRequest();
        void sendPlaylistRequest();
        void sendPlayRequest();
        void sendSeekRequest(double position);
        void sendStopRequest();

    private:
        CommunicationProvider* communicationProvider;
    };
}
