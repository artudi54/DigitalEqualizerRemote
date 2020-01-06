#include <DigitalEqualizerRemoteApplication.hpp>
#include <communication/DeviceConnector.hpp>
#include <communication/ResponseHandler.hpp>
#include <model/PlayerModel.hpp>
using namespace std::literals;


void printError(const QString& message) {
    qDebug() << "Error:" << message.toStdString().c_str();
}

int main(int argc, char** argv) {
    DigitalEqualizerRemoteApplication app(argc, argv);
    model::PlayerModel model;
    communication::ResponseHandler responseHandler(model);

    communication::DeviceConnector connector;

    QObject::connect(&connector, &communication::DeviceConnector::found, [&] {
        QBluetoothSocket* socket = connector.retrieveSocket();
        qDebug() << "Connected: " <<  socket->peerAddress();
    });
    QObject::connect(&connector, &communication::DeviceConnector::errorOccurred, &printError);

    connector.find("DigitalEqualizer");
    return app.exec();
}
