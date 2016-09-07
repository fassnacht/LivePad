#include "udpreceiver.h"
#include <QByteArray>

#include <models/channleitem.h>

UdpReceiver::UdpReceiver(MeterAdapter *meterAdapter, ChannleAdapter *channleAdapter, QObject *parent) : QObject(parent),
    _meterAdapter(meterAdapter),
    _channleAdapter(channleAdapter)
{
    _socket = new QUdpSocket(this);
    qDebug()<<"success: "<<_socket->bind(QHostAddress::AnyIPv4, 7799);

    connect(_socket, &QUdpSocket::readyRead, [=]()
    {
        QByteArray datagram;
        datagram.resize(_socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        _socket->readDatagram(datagram.data(), datagram.size(),
                              &sender, &senderPort);

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
        _channleAdapter->clearAdapter();
        _meterAdapter->clearChannleMeters();
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

    if("/live/track/meter" == first)
    {
        _meterAdapter->updateChannleMeter(data.at(2).toInt(), data.at(3).toInt(), data.at(4).toFloat());
    }
    else if("/live/return/meter" == first)
    {
        _meterAdapter->updateReturnMeter(data.at(2).toInt(), data.at(3).toInt(), data.at(4).toFloat());
    }
    else if("/live/master/meter" == first)
    {
        if(data.at(2) == "0")
            _meterAdapter->setLeftMasterMeter(data.at(3).toFloat());
        else
            _meterAdapter->setRightMasterMeter(data.at(3).toFloat());
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

    QColor color;
    if(!data.isEmpty())
    {
        int value= data.takeFirst().toInt();
        int one = (value >> 16) & 0xFF;
        int two = (value >> 8) & 0xFF;
        int three = value & 0xFF;
        color = QColor(one,two,three);
    }
    ChannleItem *item = new ChannleItem();
    item->setName(name);
    item->setColor(color);
    item->setChannleNumber(channle);
    item->setMidi(midi);

    if(_channleAdapter->count() < channle+1)
    {
        _channleAdapter->insertRow(channle, item);
    }
    else
    {
        _channleAdapter->takeRow(channle);
        _channleAdapter->insertRow(channle, item);
    }

    if(_meterAdapter->channleMetersModel().length() <= channle)
    {
        MeterModel *meter = new MeterModel();
        //_meterAdapter->channleMetersModel().append(meter);
        _meterAdapter->appendMeter(meter);

    }

    //add color to group list
    QStringList colors = _channleAdapter->colorGroups();
    if(!colors.contains(color.name()))
    {
        colors.append(color.name());
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
            int send = data.takeFirst().toInt();
            float value = data.takeFirst().toFloat();

            list.takeAt(send);
            list.insert(send, value);
        }

        _channleAdapter->at(channle)->setSendLevels(list);
    }
}
