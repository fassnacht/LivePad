#include "channleadapter.h"

ChannleAdapter::ChannleAdapter(QObject *parent) : ListModelBase<ChannleItem>(parent),
    _colorGroups("")
{
    _colorGroups.clear();
    _roles[Name] = "_name";
    _roles[Groups] = "_groups";
    _roles[SendLevel] = "_sendLevel";
    _roles[Level] = "_level";
    _roles[Mute] = "_mute";
    _roles[Solo] = "_solo";
    _roles[Record] = "_record";
    _roles[Selected] = "_selected";
    _roles[Pan] = "_pan";
    _roles[Color] = "_color";
    _roles[Midi] = "_midi";
    _roles[ChannleNumber] = "_channleNumber";
}

QVariant ChannleAdapter::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= m_dataList.size())
           return QVariant();

    ChannleItem* item = m_dataList.at(index.row());

    switch(role)
    {
    case Name:
        return item->name();
    case Groups:
        return item->groups();
    case SendLevel:
        return item->sendLevels();
    case Level:
        return item->level();
    case Mute:
        return item->mute();
    case Solo:
        return item->solo();
    case Record:
        return item->record();
    case Selected:
        return item->selected();
    case Pan:
        return item->pan();
    case Color:
        return item->color();
    case Midi:
        return item->midi();
    case ChannleNumber:
        return item->channleNumber();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ChannleAdapter::roleNames() const
{
    return _roles;
}

int ChannleAdapter::count() const
{
    return ListModelBase::count();
}

QStringList ChannleAdapter::colorGroups() const
{
    return _colorGroups;
}

void ChannleAdapter::setColorGroups(const QStringList &colorGroups)
{
    _colorGroups = colorGroups;
    Q_EMIT colorGroupsChanged();
}

void ChannleAdapter::clearAdapter()
{
    for(int i = 0; i <this->count(); i++)
    {
        delete this->takeRow(i);
    }
    this->clear();
    _colorGroups.clear();
}
