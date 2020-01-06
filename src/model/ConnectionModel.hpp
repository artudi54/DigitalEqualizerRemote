#pragma once
#include <QObject>

namespace model {
    class ConnectionModel : public QObject {
        Q_OBJECT
    public:
        explicit ConnectionModel(QObject* parent = nullptr);

        void notifyStartedConnecting();
        void notifyConnected();
        void notifyErrorOccurred(const QString& message);

    signals:
        void startedConnecting();
        void connected();
        void errorOccurred(const QString& message);
    };
}
