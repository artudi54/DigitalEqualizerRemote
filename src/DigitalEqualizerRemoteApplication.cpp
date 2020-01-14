#include "DigitalEqualizerRemoteApplication.hpp"
#include <QLoggingCategory>
#include <QQmlEngine>
#include <QQuickStyle>
#include <model/EqualizerModel.hpp>
#include <model/PlayerModel.hpp>
#include <model/PlayState.hpp>

DigitalEqualizerRemoteApplication::DigitalEqualizerRemoteApplication(int &argc, char **argv)
    : QGuiApplication(argc, argv) {
    setApplicationDetails();
    registerQmlTypes();
    configureLogging();
}

void DigitalEqualizerRemoteApplication::setApplicationDetails() {
    setApplicationName("DigitalEqualizerRemote");
    setApplicationDisplayName(applicationName());
    setApplicationVersion("1.0.0");
}

void DigitalEqualizerRemoteApplication::registerQmlTypes() {
    qmlRegisterUncreatableType<model::EqualizerBand>("Models", 1, 0, "EqualizerBand", "This type cannot be created");
    qmlRegisterUncreatableType<model::EqualizerModel>("Models", 1, 0, "EqualizerModel", "This type cannot be created");
    qmlRegisterUncreatableType<model::PlayerModel>("Models", 1, 0, "PlayerModel", "This type cannot be created");
    qmlRegisterUncreatableMetaObject(model::staticMetaObject, "Models", 1, 0, "PlayState", "This type cannot be created");
}

void DigitalEqualizerRemoteApplication::configureLogging() {
#ifndef QT_DEBUG
    QLoggingCategory::setFilterRules(QStringLiteral("qt.bluetooth* = false"));
#endif
}
