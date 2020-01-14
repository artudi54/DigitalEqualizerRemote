#include "PlayerModel.hpp"
#include <sstream>
#include <cmath>
#include <iomanip>

namespace model {
    PlayerModel::PlayerModel(QObject* parent)
        : QObject(parent)
        , playState(PlayState::STOPPED)
        , currentTime(0.0)
        , currentTimeLabel("00:00")
        , totalTime(0.0)
        , totalTimeLabel("00:00")
        , volume(100)
        , playlist()
        , currentIndex(-1)
        , equalizerParameters(new EqualizerModel(this)){}

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


    QString PlayerModel::getCurrentTimeLabel() const {
        return currentTimeLabel;
    }

    double PlayerModel::getTotalTime() const {
        return totalTime;
    }

    QString PlayerModel::getTotalTimeLabel() const {
        return totalTimeLabel;
    }

    void PlayerModel::setTimeRange(double currentTime, double totalTime) {
        if (currentTime == this->currentTime && totalTime == this->totalTime)
            return;
        if (currentTime > totalTime)
            throw std::invalid_argument("Invalid time range: " + std::to_string(currentTime) + ":" + std::to_string(totalTime));
        this->currentTime = currentTime;
        this->currentTimeLabel = formatTime(currentTime);
        this->totalTime = totalTime;
        this->totalTimeLabel = formatTime(totalTime);
        emit currentTimeChanged();
        emit currentTimeLabelChanged();
        emit totalTimeChanged();
        emit totalTimeLabelChanged();
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
        if (medium.isEmpty())
            setCurrentIndex(-1);
        auto it = std::find(playlist.begin(), playlist.end(), medium);
        if (it == playlist.end()) {
            throw std::invalid_argument("Medium: " + medium.toStdString() + " not found in playlist");
        }
        setCurrentIndex(static_cast<int>(it - playlist.begin()));
    }

    EqualizerModel* PlayerModel::getEqualizerParameters() {
        return equalizerParameters;
    }

    QString PlayerModel::formatTime(double time) {
        unsigned minutes = static_cast<unsigned>(time / 60.0);
        unsigned seconds = static_cast<unsigned>(std::fmod(time, 60.0));
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') <<  minutes << ":"
           << std::setw(2) << std::setfill('0') << seconds;
        return QString::fromStdString(ss.str());
    }
}
