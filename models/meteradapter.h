#ifndef METERADAPTER_H
#define METERADAPTER_H

#include <QObject>
#include "metermodel.h"
#include <QVector>

class MeterAdapter : public QObject
{
    Q_OBJECT

    Q_PROPERTY(float leftMasterMeter READ leftMasterMeter NOTIFY leftMasterMeterChanged)
    Q_PROPERTY(float rightMasterMeter READ rightMasterMeter NOTIFY rightMasterMeterChanged)

    Q_PROPERTY(QList<QObject*> channleMeters READ channleMeters NOTIFY channleMetersChanged)

public:
    explicit MeterAdapter(QObject *parent = 0);

    float leftMasterMeter() const;
    void setLeftMasterMeter(float leftMasterMeter);

    float rightMasterMeter() const;
    void setRightMasterMeter(float rightMasterMeter);

    void updateChannleMeter(int channle, int pan, float value);
    void updateReturnMeter(int returnChannle, int pan, float value);

    QList<QObject *> channleMeters() const;
    QVector<MeterModel *> channleMetersModel() const;

    void appendMeter(MeterModel* meter);

    void clearChannleMeters();

private:
    float _leftMasterMeter;
    float _rightMasterMeter;

    QVector<MeterModel*> _channleMeters;

signals:
    void sig_leftChannleMeterUpdated(int channle, float value);
    void sig_rightChannleMeterUpdated(int channle, float value);

    void sig_leftReturnMeterUpdated(int returnChannle, float value);
    void sig_rightReturnMeterUpdated(int returnChannle, float value);

    void rightMasterMeterChanged();
    void leftMasterMeterChanged();

    void channleMetersChanged();
};

#endif // METERADAPTER_H
