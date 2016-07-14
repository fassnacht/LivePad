#include "meteradapter.h"

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
    if(pan == 0) //left
    {
        Q_EMIT sig_leftChannleMeterUpdated(channle, value);
    }
    else if(pan ==1) //right
    {
        Q_EMIT sig_rightChannleMeterUpdated(channle, value);
    }
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

