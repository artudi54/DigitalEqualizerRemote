#pragma once
#include <QGuiApplication>

class DigitalEqualizerRemoteApplication : public QGuiApplication {
public:
    DigitalEqualizerRemoteApplication(int &argc, char **argv);

private:
    void setApplicationDetails();
    void registerQmlTypes();
    void configureLogging();
};
