#ifndef ChannleFilter_H
#define ChannleFilter_H

#include <QObject>
#include "channleadapter.h"
#include "ChannleFilterProxy.h"

class ChannleFilter : public QObject
{
    Q_OBJECT

public:
    explicit ChannleFilter(QObject* parent = 0);

    Q_PROPERTY(ChannleAdapter* unfilteredChannles READ unfilteredChannles WRITE setUnfilteredChannles NOTIFY unfilteredChannlesChanged)
    Q_PROPERTY(QObject* filteredList READ filteredList NOTIFY filteredListChanged)

    Q_PROPERTY(bool midiOnly READ midiOnly WRITE setMidiOnly NOTIFY midiOnlyChanged)
    Q_PROPERTY(bool audioOnly READ audioOnly WRITE setAudioOnly NOTIFY audioOnlyChanged)
    Q_PROPERTY(QColor filterColor READ filterColor WRITE setFilterColor NOTIFY filterColorChanged)

    Q_PROPERTY(bool filterOn READ filterOn WRITE setFilterOn NOTIFY filterOnChanged)

    ChannleAdapter *unfilteredChannles() const;
    void setUnfilteredChannles(ChannleAdapter *unfilteredChannles);

    QObject* filteredList() const;

    bool isMidi() const;
    void setIsMidi(bool isMidi);

    QColor filterColor() const;
    void setFilterColor(const QColor &filterColor);

    bool filterOn() const;
    void setFilterOn(bool filterOn);

    bool midiOnly() const;
    void setMidiOnly(bool midiOnly);

    bool audioOnly() const;
    void setAudioOnly(bool audioOnly);

private:
    ChannleAdapter*     _unfilteredChannles;
    ChannleFilterProxy* _filterProxy;
    QColor              _filterColor;
    bool                _filterOn;
    bool                _midiOnly;
    bool                _audioOnly;

signals:
    void unfilteredChannlesChanged();
    void filteredListChanged();
    void midiOnlyChanged();
    void audioOnlyChanged();
    void filterColorChanged();
    void filterOnChanged();

};

#endif // ChannleFilter_H
