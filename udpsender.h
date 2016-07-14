#ifndef UDPSENDER_H
#define UDPSENDER_H

#include <QObject>
#include <QUdpSocket>

class UdpSender : public QObject
{
    Q_OBJECT

public:
    explicit UdpSender(QObject *parent = 0);

    Q_INVOKABLE void send(QString);

private:
    QUdpSocket *_sender;

};

#endif // UDPSENDER_H
