#include "udpsender.h"

UdpSender::UdpSender(QObject *parent) : QObject(parent)
{
    _sender = new QUdpSocket(this);
}

void UdpSender::send(QString data)
{
    qDebug()<<"Sending: "<<_sender->writeDatagram(data.toUtf8(),QHostAddress::LocalHost, 7788);
}
