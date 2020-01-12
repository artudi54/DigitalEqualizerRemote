#include "PlayerModel.hpp"

namespace model {
    PlayerModel::PlayerModel(QObject* parent)
        : QObject(parent)
        , playState(PlayState::STOPPED)
        , currentTime(0.0)
        , totalTime(0.0)
        , volume(100)
        , playlist()
        , currentIndex(-1) {}

    PlayState PlayerModel::getPlayState() const {
        return playState;
    }

    void PlayerModel::setPlayState(PlayState playState) {
        if (playState == this->playState)
            return;
        this->playState = playState;
        emit playStateChanged();
    }

    double PlayerModel::getCurrentTime() const {
        return currentTime;
    }

    double PlayerModel::getTotalTime() const {
        return totalTime;
    }

    void PlayerModel::setTimeRange(double currentTime, double totalTime) {
        if (currentTime == this->currentTime && totalTime == this->totalTime)
            return;
        if (currentTime > totalTime)
            throw std::invalid_argument("Invalid time range: " + std::to_string(currentTime) + ":" + std::to_string(totalTime));
        this->currentTime = currentTime;
        this->totalTime = totalTime;
        emit currentTimeChanged();
        emit totalTimeChanged();
    }

    unsigned PlayerModel::getVolume() const {
        return volume;
    }

    void PlayerModel::setVolume(unsigned volume) {
        if (this->volume == volume)
            return;
        if (volume > 100)
            throw std::invalid_argument("Invalid volume value: " + std::to_string(volume));
        this->volume = volume;
        emit volumeChanged();
    }

    const QStringList &PlayerModel::getPlaylist() const {
        return playlist;
    }

    void PlayerModel::setPlaylist(const QStringList &playlist) {
        if (playlist == this->playlist)
            return;
        this->playlist = playlist;
        emit playlistChanged();
    }

    bool PlayerModel::hasValidIndex() const {
        return currentIndex != -1;
    }

    int PlayerModel::getCurrentIndex() const {
        return currentIndex;
    }

    QString PlayerModel::getCurrentMedium() const {
        if (currentIndex == -1)
            return QString();
        return playlist[currentIndex];
    }

    void PlayerModel::setCurrentIndex(int currentIndex) {
        if (currentIndex == this->currentIndex)
            return;
        if (currentIndex < -1 || currentIndex >= playlist.size())
            throw std::invalid_argument("Index: " + std::to_string(currentIndex) + " not found in playlist");
        this->currentIndex = currentIndex;
        emit currentIndexChanged();
        emit currentMediumChanged();
    }

    void PlayerModel::setCurrentMedium(const QString &medium) {
        auto it = std::find(playlist.begin(), playlist.end(), medium);
        if (it == playlist.end()) {
            throw std::invalid_argument("Medium: " + medium.toStdString() + " not found in playlist");
        }
        setCurrentIndex(static_cast<int>(it - playlist.begin()));
    }
}
