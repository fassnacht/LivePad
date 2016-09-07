#include "meteradapter.h"
#include "metermodel.h"
#include <QDebug>

MeterAdapter::MeterAdapter(QObject *parent) : QObject(parent),
    _leftMasterMeter(0),
    _rightMasterMeter(0)
{

}

float MeterAdapter::leftMasterMeter() const
{
    return _leftMasterMeter;
}

void MeterAdapter::setLeftMasterMeter(float leftMasterMeter)
{
    _leftMasterMeter = leftMasterMeter;
    Q_EMIT leftMasterMeterChanged();
}

float MeterAdapter::rightMasterMeter() const
{
    return _rightMasterMeter;
}

void MeterAdapter::setRightMasterMeter(float rightMasterMeter)
{
    _rightMasterMeter = rightMasterMeter;
    Q_EMIT rightMasterMeterChanged();
}

void MeterAdapter::updateChannleMeter(int channle, int pan, float value)
{
//    if(pan == 0) //left
//    {
//        Q_EMIT sig_leftChannleMeterUpdated(channle, value);
//    }
//    else if(pan ==1) //right
//    {
//        Q_EMIT sig_rightChannleMeterUpdated(channle, value);
//    }

    if(channle >= _channleMeters.length())
        return;

    if(pan == 0)
        _channleMeters.at(channle)->setLeft(value);
    else
        _channleMeters.at(channle)->setRight(value);

}

void MeterAdapter::updateReturnMeter(int returnChannle, int pan, float value)
{
    if(pan == 0) //left
    {
        Q_EMIT sig_leftReturnMeterUpdated(returnChannle, value);
    }
    else if(pan ==1) //right
    {
        Q_EMIT sig_rightReturnMeterUpdated(returnChannle, value);
    }
}

QList<QObject *> MeterAdapter::channleMeters() const
{
    QList<QObject*> obj;

    for(MeterModel* meter : _channleMeters)
    {
        obj << meter;
    }

    return obj;
}

QVector<MeterModel *> MeterAdapter::channleMetersModel() const
{
    return _channleMeters;
}

void MeterAdapter::appendMeter(MeterModel *meter)
{
    if(!meter)
        return;
    meter->moveToThread(this->thread());
    _channleMeters.append(meter);
    Q_EMIT channleMetersChanged();
}

void MeterAdapter::clearChannleMeters()
{
    foreach (MeterModel* meter, _channleMeters) {
        delete meter;
    }
    _channleMeters.clear();
}

