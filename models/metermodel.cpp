#include "metermodel.h"
#include <QDebug>

MeterModel::MeterModel(QObject *parent) : QObject(parent),
    _left(0),
    _right(0)
{

}

float MeterModel::left() const
{
    return _left;
}

void MeterModel::setLeft(float left)
{
    _left = left;
    Q_EMIT leftChanged();
}

float MeterModel::right() const
{
    return _right;
}

void MeterModel::setRight(float right)
{
    _right = right;
    Q_EMIT rightChanged();
}
