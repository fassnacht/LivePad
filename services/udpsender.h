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

    int targetPort() const;
    QString targetIp() const;

public slots:
    void setTargetPort(int targetPort);
    void setTargetIp(const QString &targetIp);

private:
    QUdpSocket *_sender;
    int _targetPort;
    QString _targetIp;

};

#endif // UDPSENDER_H
