#pragma once
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <controller/PlayerController.hpp>
#include <model/ConnectionModel.hpp>
#include <model/PlayerModel.hpp>


class DigitalEqualizerRemote {
public:
    DigitalEqualizerRemote();
    ~DigitalEqualizerRemote();

    void startConnecting();
    void show();

private:
    static QQuickWindow* getMainWindow(const QQmlApplicationEngine* engine);
    void setViewProperties();

    QQmlApplicationEngine* engine;
    QQuickWindow *window;
    model::ConnectionModel* connectionModel;
    model::PlayerModel* playerModel;
    controller::PlayerController* playerController;
};
