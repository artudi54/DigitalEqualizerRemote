#pragma once
#include <QObject>
#include <model/PlayState.hpp>

namespace model {
    class PlayerModel : public QObject {
        Q_OBJECT
        Q_PROPERTY(PlayState     playState     READ getPlayState     NOTIFY playStateChanged)
        Q_PROPERTY(double        currentTime   READ getCurrentTime   NOTIFY currentTimeChanged)
        Q_PROPERTY(double        totalTime     READ getTotalTime     NOTIFY totalTimeChanged)
        Q_PROPERTY(std::uint32_t volume        READ getVolume        NOTIFY volumeChanged)
        Q_PROPERTY(QStringList   playlist      READ getPlaylist      NOTIFY playlistChanged)
        Q_PROPERTY(int           currentIndex  READ getCurrentIndex  NOTIFY currentIndexChanged)
        Q_PROPERTY(QString       currentMedium READ getCurrentMedium NOTIFY currentMediumChanged)
    public:
        explicit PlayerModel(QObject* parent = nullptr);

        [[nodiscard]] PlayState getPlayState() const;
        void setPlayState(PlayState playState);

        [[nodiscard]] double getCurrentTime() const;
        [[nodiscard]] double getTotalTime() const;
        void setTimeRange(double currentTime, double totalTime);

        [[nodiscard]] std::uint32_t getVolume() const;
        void setVolume(std::uint32_t volume);

        [[nodiscard]] const QStringList &getPlaylist() const;
        void setPlaylist(const QStringList &playlist);

        [[nodiscard]] int getCurrentIndex() const;
        [[nodiscard]] QString getCurrentMedium() const;
        void setCurrentIndex(int currentIndex);
        void setCurrentMedium(const QString& medium);

    signals:
        void playStateChanged();
        void currentTimeChanged();
        void totalTimeChanged();
        void volumeChanged();
        void playlistChanged();
        void currentIndexChanged();
        void currentMediumChanged();

    private:
        PlayState playState;
        double currentTime;
        double totalTime;
        std::uint32_t volume;
        QStringList playlist;
        int currentIndex;
    };
}