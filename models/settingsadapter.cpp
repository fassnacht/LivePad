#include "settingsadapter.h"

#include <QHostAddress>
#include <QNetworkInterface>

SettingsAdapter::SettingsAdapter(QObject *parent) : QObject(parent),
    _targetIp("127.0.0.1"),
    _targetPort(7788)
{
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
             setOwnIp(address.toString());
    }
}

QString SettingsAdapter::targetIp() const
{
    return _targetIp;
}

void SettingsAdapter::setTargetIp(const QString &targetIp)
{
    if(_targetIp == targetIp)
        return;

    _targetIp = targetIp;
    Q_EMIT targetIpChanged();
    Q_EMIT sig_targetIpChanged(_targetIp);
}

int SettingsAdapter::targetPort() const
{
    return _targetPort;
}

void SettingsAdapter::setTargetPort(int targetPort)
{
    if(_targetPort = targetPort)
        return;

    _targetPort = targetPort;
    Q_EMIT targetPortChanged();
    Q_EMIT sig_targetPortChanged(_targetPort);
}

QString SettingsAdapter::ownIp() const
{
    return _ownIp;
}

void SettingsAdapter::setOwnIp(const QString &ownIp)
{
    _ownIp = ownIp;
    Q_EMIT ownIpChanged();
}
