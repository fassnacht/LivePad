#ifndef CHANNLEITEM_H
#define CHANNLEITEM_H

#include "BaseItem.h"
#include "QVariantList"
#include <QColor>

class ChannleItem : public BaseItem
{
    Q_OBJECT

public:
    explicit ChannleItem(QObject *parent = 0);

    QString name() const;
    void setName(const QString &name);

    QStringList groups() const;
    void setGroups(const QStringList &groups);

    QVariantList sendLevels() const;
    void setSendLevels(const QVariantList &sendLevels);

    float level() const;
    void setLevel(float level);

    bool mute() const;
    void setMute(bool mute);

    bool solo() const;
    void setSolo(bool solo);

    bool record() const;
    void setRecord(bool record);

    bool selected() const;
    void setSelected(bool selected);

    float pan() const;
    void setPan(float pan);

    QColor color() const;
    void setColor(const QColor &color);

    bool midi() const;
    void setMidi(bool midi);

    int channleNumber() const;
    void setChannleNumber(int channleNumber);

private:
    QString         _name;
    QStringList     _groups;
    QVariantList    _sendLevels;
    float           _pan;
    float           _level;
    bool            _mute;
    bool            _solo;
    bool            _record;
    bool            _selected;
    QColor          _color;
    bool            _midi;
    int             _channleNumber;

};

#endif // CHANNLEITEM_H
