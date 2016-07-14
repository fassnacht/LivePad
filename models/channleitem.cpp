#include "channleitem.h"
#include <QDebug>

ChannleItem::ChannleItem(QObject *parent) : BaseItem(parent),
    _name(""),
    _groups(""),
    _pan(0),
    _level(0),
    _mute(false),
    _solo(false),
    _record(false),
    _selected(false),
    _color(QColor(0,0,0)),
    _midi(false)
{
    for(int i = 0; i< 12; i++)
    {
        _sendLevels.append(QVariant(0.0));
    }
}

QString ChannleItem::name() const
{
    return _name;
}

void ChannleItem::setName(const QString &name)
{
    _name = name;
    Q_EMIT dataChanged();
}

QStringList ChannleItem::groups() const
{
    return _groups;
}

void ChannleItem::setGroups(const QStringList &groups)
{
    _groups = groups;
    Q_EMIT dataChanged();
}

QVariantList ChannleItem::sendLevels() const
{
    return _sendLevels;
}

void ChannleItem::setSendLevels(const QVariantList &sendLevels)
{
    _sendLevels = sendLevels;
    Q_EMIT dataChanged();
}

float ChannleItem::level() const
{
    return _level;
}

void ChannleItem::setLevel(float level)
{
    _level = level;
    Q_EMIT dataChanged();
}

bool ChannleItem::mute() const
{
    return _mute;
}

void ChannleItem::setMute(bool mute)
{
    _mute = mute;
    Q_EMIT dataChanged();
}

bool ChannleItem::solo() const
{
    return _solo;
}

void ChannleItem::setSolo(bool solo)
{
    _solo = solo;
    Q_EMIT dataChanged();
}

bool ChannleItem::record() const
{
    return _record;
}

void ChannleItem::setRecord(bool record)
{
    _record = record;
    Q_EMIT dataChanged();
}

bool ChannleItem::selected() const
{
    return _selected;
}

void ChannleItem::setSelected(bool selected)
{
    _selected = selected;
    Q_EMIT dataChanged();
}

float ChannleItem::pan() const
{
    return _pan;
}

void ChannleItem::setPan(float pan)
{
    _pan = pan;
    Q_EMIT dataChanged();
}

QColor ChannleItem::color() const
{
    return _color;
}

void ChannleItem::setColor(const QColor &color)
{
    _color = color;
    Q_EMIT dataChanged();
}

bool ChannleItem::midi() const
{
    return _midi;
}

void ChannleItem::setMidi(bool midi)
{
    _midi = midi;
    Q_EMIT dataChanged();
}

int ChannleItem::channleNumber() const
{
    return _channleNumber;
}

void ChannleItem::setChannleNumber(int channleNumber)
{
    _channleNumber = channleNumber;
    Q_EMIT dataChanged();
}

