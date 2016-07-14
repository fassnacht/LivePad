#include "ChannleFilterProxy.h"
#include "channleadapter.h"
#include <QDebug>

ChannleFilterProxy::ChannleFilterProxy(QObject *parent) : QSortFilterProxyModel(parent),
    _filterOn(false),
    _filterColor(QColor(0,0,0))
{

}

bool ChannleFilterProxy::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex index = sourceModel()->index(source_row,0,source_parent);
        qDebug()<<"filtering";


    bool color = true;

    if(QColor(0,0,0) != _filterColor)
        if(sourceModel()->data(index,ChannleAdapter::Roles::Color).value<QColor>() == _filterColor)
            color = true;
        else
            color = false;

    bool rightType = false;

    if(sourceModel()->data(index,ChannleAdapter::Roles::Midi).toBool() && !_audioOnly)
        rightType = true;

    if(!sourceModel()->data(index,ChannleAdapter::Roles::Midi).toBool() && !_midiOnly)
        rightType = true;

    return color && rightType;
}

bool ChannleFilterProxy::audioOnly() const
{
    return _audioOnly;
}

void ChannleFilterProxy::setAudioOnly(bool audioOnly)
{
    if(_audioOnly == audioOnly)
        return;

    _audioOnly = audioOnly;
    this->setSourceModel(this->sourceModel());
}

bool ChannleFilterProxy::midiOnly() const
{
    return _midiOnly;
}

void ChannleFilterProxy::setMidiOnly(bool midiOnly)
{
    if(_midiOnly = midiOnly)
       return;

    _midiOnly = midiOnly;
    this->setSourceModel(this->sourceModel());
}

bool ChannleFilterProxy::filterOn() const
{
    return _filterOn;
}

void ChannleFilterProxy::setFilterOn(bool filterOn)
{
    _filterOn = filterOn;
}

QColor ChannleFilterProxy::filterColor() const
{
    return _filterColor;
}

void ChannleFilterProxy::setFilterColor(const QColor &filterColor)
{
    _filterColor = filterColor;
}
