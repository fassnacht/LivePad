#ifndef CHANNLEADAPTER_H
#define CHANNLEADAPTER_H

#include "bases/ListModelBase.h"
#include "channleitem.h"

class ChannleAdapter : public ListModelBase<ChannleItem>
{
    Q_OBJECT

    Q_PROPERTY(QStringList colorGroups READ colorGroups NOTIFY colorGroupsChanged)

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

    QStringList colorGroups() const;
    void setColorGroups(const QStringList &colorGroups);

    void clearAdapter();

private:
    QHash<int, QByteArray>  _roles;

    QStringList _colorGroups;

signals:
    void colorGroupsChanged();

};

#endif // CHANNLEADAPTER_H
