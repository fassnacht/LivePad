#ifndef ChannleFilterProxy_H
#define ChannleFilterProxy_H

#include <QSortFilterProxyModel>
#include <QColor>

class ChannleFilterProxy : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit ChannleFilterProxy(QObject* parent = 0);

    QColor filterColor() const;
    void setFilterColor(const QColor &filterColor);

    bool filterOn() const;
    void setFilterOn(bool filterOn);

    bool midiOnly() const;
    void setMidiOnly(bool midiOnly);

    bool audioOnly() const;
    void setAudioOnly(bool audioOnly);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

private:
    QColor              _filterColor;
    bool                _filterOn;
    bool                _midiOnly;
    bool                _audioOnly;

};

#endif // ChannleFilterProxy_H
