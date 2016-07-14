#include "ChannleFilter.h"
#include "QDebug"

ChannleFilter::ChannleFilter(QObject *parent) : QObject(parent),
    _unfilteredChannles(0),
    _filterOn(false),
    _filterProxy(0)
{
    _filterProxy = new ChannleFilterProxy(this);
}

ChannleAdapter *ChannleFilter::unfilteredChannles() const
{
    return _unfilteredChannles;
}

void ChannleFilter::setUnfilteredChannles(ChannleAdapter *unfilteredChannles)
{
    if(!unfilteredChannles)
        return;

    _unfilteredChannles = unfilteredChannles;
    Q_EMIT unfilteredChannlesChanged();

    qDebug()<<"pointer "<<_unfilteredChannles;
    _filterProxy->setSourceModel(_unfilteredChannles);
}


QObject *ChannleFilter::filteredList() const
{
    return _filterProxy;
}

QColor ChannleFilter::filterColor() const
{
    return _filterColor;
}

void ChannleFilter::setFilterColor(const QColor &filterColor)
{
    _filterColor = filterColor;
    _filterProxy->setFilterColor(filterColor);
    Q_EMIT filterColorChanged();
}

bool ChannleFilter::filterOn() const
{
    return _filterOn;
}

void ChannleFilter::setFilterOn(bool filterOn)
{
    _filterOn = filterOn;

    _filterProxy->setFilterOn(filterOn);
    Q_EMIT filterOnChanged();
}

bool ChannleFilter::midiOnly() const
{
    return _midiOnly;
}

void ChannleFilter::setMidiOnly(bool midiOnly)
{
    _midiOnly = midiOnly;
    _filterProxy->setMidiOnly(midiOnly);
    Q_EMIT midiOnlyChanged();
}

bool ChannleFilter::audioOnly() const
{
    return _audioOnly;
}

void ChannleFilter::setAudioOnly(bool audioOnly)
{
    _audioOnly = audioOnly;
    _filterProxy->setAudioOnly(audioOnly);
    Q_EMIT audioOnlyChanged();
}
