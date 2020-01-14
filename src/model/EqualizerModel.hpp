#pragma once
#include <QObject>

namespace model {
    class EqualizerBand : public QObject {
        Q_OBJECT
        Q_PROPERTY(double  frequency READ getFrequency CONSTANT)
        Q_PROPERTY(QString name      READ getName      CONSTANT)
        Q_PROPERTY(double  value     READ getValue     NOTIFY valueChanged)
    public:
        explicit EqualizerBand(double frequency, double value = 0.0, QObject* parent = nullptr);

        [[nodiscard]] double getFrequency() const;
        [[nodiscard]] QString getName() const;

        [[nodiscard]] double getValue() const;
        void setValue(double value);

    signals:
        void valueChanged();

    private:
        double frequency;
        double value;
    };

    class EqualizerModel : public QObject {
        Q_OBJECT
        Q_PROPERTY(EqualizerBand*  dbGain           READ getDbGain              CONSTANT)
        Q_PROPERTY(QList<QObject*> frequencyDbGains READ getFrequencyDbGainsObj CONSTANT)
    public:
        explicit EqualizerModel(QObject* parent = nullptr);

        [[nodiscard]] EqualizerBand* getDbGain();
        [[nodiscard]] const EqualizerBand* getDbGain() const;

        [[nodiscard]] QList<EqualizerBand*>& getFrequencyDbGains();
        [[nodiscard]] const QList<EqualizerBand*>& getFrequencyDbGains() const;
        [[nodiscard]] QList<QObject*> getFrequencyDbGainsObj();

    private:
        EqualizerBand* dbGain;
        QList<EqualizerBand*> frequencyDbGains;
        QList<QObject*> frequencyDbGainsObj;
    };
}
