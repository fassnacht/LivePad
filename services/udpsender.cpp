#include "udpsender.h"

UdpSender::UdpSender(QObject *parent) : QObject(parent),
    _targetPort(7788),
    _targetIp("127.0.0.1")
{
    _sender = new QUdpSocket();
}

void UdpSender::send(QString data)
{
    /*qDebug()<<"Sending: "<<_targetIp<<*/_sender->writeDatagram(data.toUtf8(),QHostAddress(_targetIp), _targetPort);
}

int UdpSender::targetPort() const
{
    return _targetPort;
}

void UdpSender::setTargetPort(int targetPort)
{
    _targetPort = targetPort;
}

QString UdpSender::targetIp() const
{
    return _targetIp;
}

void UdpSender::setTargetIp(const QString &targetIp)
{
    _targetIp = targetIp;
    qDebug()<<targetIp;
}
