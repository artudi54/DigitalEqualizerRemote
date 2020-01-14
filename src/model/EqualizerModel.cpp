#include "EqualizerModel.hpp"

namespace model {
    EqualizerBand::EqualizerBand(double frequency, double value, QObject* parent)
        : QObject(parent)
        , frequency(frequency)
        , value(0.0) {
        if (frequency < -1 || frequency > 20000)
            throw std::invalid_argument("Invalid frequency value: " + std::to_string(frequency));
        setValue(value);
    }

    double EqualizerBand::getFrequency() const {
        return frequency;
    }

    QString EqualizerBand::getName() const {
        if (frequency == -1)
            return "Overall gain";
        if (frequency < 1000)
            return QString::number(frequency) + "Hz";
        return QString::number(frequency / 1000) + "KHz";
    }

    double EqualizerBand::getValue() const {
        return value;
    }

    void EqualizerBand::setValue(double value) {
        if (value == this->value)
            return;
        if (value < -20.0 || value > 20.0)
            throw std::invalid_argument("Invalid gain value: " + std::to_string(value));
        this->value = value;
        emit valueChanged();
    }

    EqualizerModel::EqualizerModel(QObject* parent)
        : QObject(parent)
        , dbGain(new EqualizerBand(-1, 0.0, this))
        , frequencyDbGains({
            new EqualizerBand(31.5, 0.0, this),
            new EqualizerBand(63, 0.0, this),
            new EqualizerBand(125, 0.0, this),
            new EqualizerBand(250, 0.0, this),
            new EqualizerBand(500, 0.0, this),
            new EqualizerBand(1000, 0.0, this),
            new EqualizerBand(2000, 0.0, this),
            new EqualizerBand(4000, 0.0, this),
            new EqualizerBand(8000, 0.0, this),
            new EqualizerBand(16000, 0.0, this),
        })
        , frequencyDbGainsObj() {
        for (auto obj : frequencyDbGains)
            frequencyDbGainsObj.push_back(obj);
    }

    EqualizerBand* EqualizerModel::getDbGain() {
        return dbGain;
    }

    QList<EqualizerBand*>& EqualizerModel::getFrequencyDbGains() {
        return frequencyDbGains;
    }

    QList<QObject*> EqualizerModel::getFrequencyDbGainsObj() {
        return frequencyDbGainsObj;
    }
}