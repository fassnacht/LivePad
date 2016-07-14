#ifndef METERADAPTER_H
#define METERADAPTER_H

#include <QObject>

class MeterAdapter : public QObject
{
    Q_OBJECT

    Q_PROPERTY(float leftMasterMeter READ leftMasterMeter NOTIFY leftMasterMeterChanged)
    Q_PROPERTY(float rightMasterMeter READ rightMasterMeter NOTIFY rightMasterMeterChanged)
public:
    explicit MeterAdapter(QObject *parent = 0);

    float leftMasterMeter() const;
    void setLeftMasterMeter(float leftMasterMeter);

    float rightMasterMeter() const;
    void setRightMasterMeter(float rightMasterMeter);

    void updateChannleMeter(int channle, int pan, float value);
    void updateReturnMeter(int returnChannle, int pan, float value);

private:
    float _leftMasterMeter;
    float _rightMasterMeter;

signals:
    void sig_leftChannleMeterUpdated(int channle, float value);
    void sig_rightChannleMeterUpdated(int channle, float value);

    void sig_leftReturnMeterUpdated(int returnChannle, float value);
    void sig_rightReturnMeterUpdated(int returnChannle, float value);

    void rightMasterMeterChanged();
    void leftMasterMeterChanged();
};

#endif // METERADAPTER_H
