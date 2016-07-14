#ifndef CHANNLEADAPTER_H
#define CHANNLEADAPTER_H

#include "ListModelBase.h"
#include "channleitem.h"

class ChannleAdapter : public ListModelBase<ChannleItem>
{
    Q_OBJECT

    Q_PROPERTY(QList<QColor> colorGroups READ colorGroups NOTIFY colorGroupsChanged)

public:
    explicit ChannleAdapter(QObject *parent = 0);

    enum Roles
    {
        Name,
        Groups,
        SendLevel,
        Level,
        Mute,
        Solo,
        Record,
        Selected,
        Pan,
        Color,
        Midi,
        ChannleNumber
    };

    QVariant data(const QModelIndex &index, int role) const;

    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE int count() const;

    QList<QColor> colorGroups() const;
    void setColorGroups(const QList<QColor> &colorGroups);

private:
    QHash<int, QByteArray>  _roles;

    QList<QColor> _colorGroups;

signals:
    void colorGroupsChanged();

};

#endif // CHANNLEADAPTER_H
