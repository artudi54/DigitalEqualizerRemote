#include "DigitalEqualizerRemote.hpp"
#include <QQmlContext>

DigitalEqualizerRemote::DigitalEqualizerRemote()
    : engine(new QQmlApplicationEngine())
    , window(nullptr)
    , connectionModel(new model::ConnectionModel(engine))
    , playerModel(new model::PlayerModel(engine))
    , playerController(new controller::PlayerController(*connectionModel, *playerModel, engine)) {
    setViewProperties();
    engine->load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    window = getMainWindow(engine);
}

DigitalEqualizerRemote::~DigitalEqualizerRemote() {
    delete engine;
}

void DigitalEqualizerRemote::startConnecting() {
    playerController->connectToHost();
}

void DigitalEqualizerRemote::show() {
    window->show();

}

QQuickWindow *DigitalEqualizerRemote::getMainWindow(const QQmlApplicationEngine *engine) {
    QObject *window = engine->rootObjects().value(0);
    return qobject_cast<QQuickWindow*>(window);
}

void DigitalEqualizerRemote::setViewProperties() {
    QQmlContext *context = engine->rootContext();
    context->setContextProperty("connectionModel", connectionModel);
    context->setContextProperty("playerModel", playerModel);
    context->setContextProperty("playerController", playerController);
}
