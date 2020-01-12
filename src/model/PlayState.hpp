#pragma once
#include <QObject>

namespace model {
    Q_NAMESPACE
    enum class PlayState {
        NO_MEDIA,
        STOPPED,
        PLAYING,
        PAUSED
    };
    Q_ENUM_NS(PlayState)
}