#pragma once
#include <QObject>
#include <model/EqualizerModel.hpp>
#include <model/PlayState.hpp>

namespace model {
    class PlayerModel : public QObject {
        Q_OBJECT
        Q_PROPERTY(model::PlayState       playState           READ getPlayState           NOTIFY playStateChanged)
        Q_PROPERTY(double                 currentTime         READ getCurrentTime         NOTIFY currentTimeChanged)
        Q_PROPERTY(QString                currentTimeLabel    READ getCurrentTimeLabel    NOTIFY currentTimeLabelChanged)
        Q_PROPERTY(double                 totalTime           READ getTotalTime           NOTIFY totalTimeChanged)
        Q_PROPERTY(QString                totalTimeLabel      READ getTotalTimeLabel      NOTIFY totalTimeLabelChanged)
        Q_PROPERTY(unsigned               volume              READ getVolume              NOTIFY volumeChanged)
        Q_PROPERTY(QStringList            playlist            READ getPlaylist            NOTIFY playlistChanged)
        Q_PROPERTY(int                    currentIndex        READ getCurrentIndex        NOTIFY currentIndexChanged)
        Q_PROPERTY(QString                currentMedium       READ getCurrentMedium       NOTIFY currentMediumChanged)
        Q_PROPERTY(model::EqualizerModel* equalizerParameters READ getEqualizerParameters CONSTANT)
    public:
        explicit PlayerModel(QObject* parent = nullptr);

        [[nodiscard]] PlayState getPlayState() const;
        void setPlayState(PlayState playState);

        [[nodiscard]] double getCurrentTime() const;
        [[nodiscard]] QString getCurrentTimeLabel() const;
        [[nodiscard]] double getTotalTime() const;
        [[nodiscard]] QString getTotalTimeLabel() const;
        void setTimeRange(double currentTime, double totalTime);

        [[nodiscard]] unsigned getVolume() const;
        void setVolume(unsigned volume);

        [[nodiscard]] const QStringList &getPlaylist() const;
        void setPlaylist(const QStringList &playlist);

        [[nodiscard]] bool hasValidIndex() const;
        [[nodiscard]] int getCurrentIndex() const;
        [[nodiscard]] QString getCurrentMedium() const;
        void setCurrentIndex(int currentIndex);
        void setCurrentMedium(const QString& medium);

        [[nodiscard]] EqualizerModel* getEqualizerParameters();

    signals:
        void playStateChanged();
        void currentTimeChanged();
        void currentTimeLabelChanged();
        void totalTimeChanged();
        void totalTimeLabelChanged();
        void volumeChanged();
        void playlistChanged();
        void currentIndexChanged();
        void currentMediumChanged();

    private:
        static QString formatTime(double time);

        PlayState playState;
        double currentTime;
        QString currentTimeLabel;
        double totalTime;
        QString totalTimeLabel;
        unsigned volume;
        QStringList playlist;
        int currentIndex;
        EqualizerModel* equalizerParameters;
    };
}
