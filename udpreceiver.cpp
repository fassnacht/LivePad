#include "udpreceiver.h"
#include <QByteArray>

#include <channleitem.h>

UdpReceiver::UdpReceiver(MeterAdapter *meterAdapter, ChannleAdapter *channleAdapter, QObject *parent) : QObject(parent),
    _meterAdapter(meterAdapter),
    _channleAdapter(channleAdapter)
{
    _socket = new QUdpSocket(this);
    qDebug()<<"success: "<<_socket->bind(QHostAddress::AnyIPv4, 7799);

    //    this->setMeterAdpater(meterAdapter);
    //    this->setChannleAdapter(channleAdapter);

    connect(_socket, &QUdpSocket::readyRead, [=]()
    {
        QByteArray datagram;
        datagram.resize(_socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        _socket->readDatagram(datagram.data(), datagram.size(),
                              &sender, &senderPort);

        //        qDebug()<<QString::fromUtf8(datagram);

        this->datagramReader(QString::fromUtf8(datagram));

    });

}

void UdpReceiver::setMeterAdpater(MeterAdapter *meterAdpater)
{
    if(!meterAdpater)
        return;

    _meterAdapter = meterAdpater;
}

void UdpReceiver::setChannleAdapter(ChannleAdapter *channleAdapter)
{
    if(!channleAdapter)
        return;
    _channleAdapter = channleAdapter;
}

void UdpReceiver::datagramReader(QString datagram)
{
    QStringList data = datagram.split("%");
    QString first = data.first();

    if(first.contains("/meter"))
    {
        processMeterInfo(data);
        return;
    }

    if(first == "/live/refresh")
    {
        Q_EMIT refreshTrackList();
        _channleAdapter->clear();
        return;
    }

    if(first == "/live/name/track")
    {
        makeChannles(data);
        return;
    }

    if(first == "/live/mute")
    {
        processMute(data);
        return;
    }

    if(first == "/live/solo")
    {
        processSolo(data);
        return;
    }

    if(first == "/live/arm")
    {
        processRecord(data);
        return;
    }

    if(first == "/live/send")
    {
        processSendLevel(data);
        return;
    }
}

void UdpReceiver::processMeterInfo(QStringList data)
{
    QString first = data.first();

    if("/live/master/meter" == first)
    {
        if(data.at(2) == "0")
            _meterAdapter->setLeftMasterMeter(data.at(3).toFloat());
        else
            _meterAdapter->setRightMasterMeter(data.at(3).toFloat());
    }
    else if("/live/return/meter" == first)
    {
        _meterAdapter->updateReturnMeter(data.at(2).toInt(), data.at(3).toInt(), data.at(4).toFloat());
    }
    else if("/live/track/meter" == first)
    {
        _meterAdapter->updateChannleMeter(data.at(2).toInt(), data.at(3).toInt(), data.at(4).toFloat());
    }
}

void UdpReceiver::makeChannles(QStringList data)
{
    data.takeFirst();
    data.takeFirst();

    int channle = data.takeFirst().toInt();
    QString name = data.takeFirst();

    int midiInt = data.takeFirst().toInt();
    bool midi = false;
    if(midiInt == 1)
        midi = true;

    int value= data.takeFirst().toInt();
    int one = (value >> 16) & 0xFF;
    int two = (value >> 8) & 0xFF;
    int three = value & 0xFF;

    ChannleItem *item = new ChannleItem(_channleAdapter);
    item->setName(name);
    item->setColor(QColor(one,two,three));
    item->setChannleNumber(channle);
    item->setMidi(midi);

    qDebug()<<one<<" "<<two<<" "<<three;

    if(_channleAdapter->count() < channle+1)
    {
        _channleAdapter->insertRow(channle, item);
    }
    else
    {
        _channleAdapter->takeRow(channle);
        _channleAdapter->insertRow(channle, item);
    }

    //add color to group list
    QList<QColor> colors = _channleAdapter->colorGroups();
    if(!colors.contains(QColor(one,two,three)))
    {
        colors.append(QColor(one,two,three));
        _channleAdapter->setColorGroups(colors);
    }

}

void UdpReceiver::processMute(QStringList data)
{
    int channle = data.at(2).toInt();
    bool mute = false;
    if(data.at(3).toInt() == 1)
        mute = true;

    if(channle < _channleAdapter->count())
    {
        _channleAdapter->at(channle)->setMute(mute);
    }
}

void UdpReceiver::processSolo(QStringList data)
{
    int channle = data.at(2).toInt();
    bool solo = false;
    if(data.at(3).toInt() == 1)
        solo = true;

    if(channle < _channleAdapter->count())
    {
        _channleAdapter->at(channle)->setSolo(solo);
    }
}

void UdpReceiver::processRecord(QStringList data)
{
    int channle = data.at(2).toInt();
    bool record = false;
    if(data.at(3).toInt() == 1)
        record = true;

    if(channle < _channleAdapter->count())
    {
        _channleAdapter->at(channle)->setRecord(record);
    }
}

void UdpReceiver::processSendLevel(QStringList data)
{
    data.takeFirst();
    data.takeFirst();
    data.takeLast();
    int channle = data.takeFirst().toInt();

    if(channle < _channleAdapter->count())
    {
        QVariantList list = _channleAdapter->at(channle)->sendLevels();

        while(data.length() > 0)
        {
            qDebug()<<data;
            int send = data.takeFirst().toInt();
            float value = data.takeFirst().toFloat();

            list.takeAt(send);
            list.insert(send, value);
        }

        _channleAdapter->at(channle)->setSendLevels(list);
    }
}
