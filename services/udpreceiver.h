#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QObject>
#include <QUdpSocket>

#include "models/meteradapter.h"
#include "models/channleadapter.h"

class UdpReceiver : public QObject
{
    Q_OBJECT

public:
    explicit UdpReceiver(MeterAdapter *meterAdapter = 0, ChannleAdapter *channleAdapter = 0, QObject *parent = 0);

    void setMeterAdpater(MeterAdapter *meterAdpater);
    void setChannleAdapter(ChannleAdapter *channleAdapter);


private:
    QUdpSocket      *_socket;
    MeterAdapter    *_meterAdapter;
    ChannleAdapter  *_channleAdapter;

    void datagramReader(QString datagram);
    void processMeterInfo(QStringList data);
    void makeChannles(QStringList data);
    void processMute(QStringList data);
    void processSolo(QStringList data);
    void processRecord(QStringList data);
    void processSendLevel(QStringList data);
    void processPan(QStringList data);
    void processVolume(QStringList data);

signals:
    void refreshTrackList();
};

#endif // UDPRECEIVER_H
