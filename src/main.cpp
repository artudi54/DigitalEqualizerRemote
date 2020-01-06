#include <DigitalEqualizerRemoteApplication.hpp>
#include <controller/PlayerController.hpp>
#include <model/ConnectionModel.hpp>
#include <model/PlayerModel.hpp>

void handleStartedConnecting() {
    qDebug() << "Started connecting";
}

void handleConnected() {
    qDebug() << "Connected";
}

void handleError(const QString& message) {
    qDebug() << "Error:" << message.toStdString().c_str();
}

int main(int argc, char** argv) {
    DigitalEqualizerRemoteApplication app(argc, argv);

    model::ConnectionModel connectionModel;
    model::PlayerModel playerModel;
    controller::PlayerController playerController(connectionModel, playerModel);

    QObject::connect(&connectionModel, &model::ConnectionModel::startedConnecting, &handleStartedConnecting);
    QObject::connect(&connectionModel, &model::ConnectionModel::connected, &handleConnected);
    QObject::connect(&connectionModel, &model::ConnectionModel::errorOccurred, &handleError);

    playerController.connectToHost();

    return app.exec();
}
