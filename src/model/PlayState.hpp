#pragma once
#include <QObject>

namespace model {
    Q_NAMESPACE
    enum class PlayState {
        STOPPED,
        PLAYING,
        PAUSED
    };
    Q_ENUM_NS(PlayState)
}