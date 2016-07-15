#ifndef SETTINGSADAPTER_H
#define SETTINGSADAPTER_H

#include <QObject>

class SettingsAdapter : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString targetIp READ targetIp WRITE setTargetIp NOTIFY targetIpChanged)
    Q_PROPERTY(int targetPort READ targetPort WRITE setTargetPort NOTIFY targetPortChanged)
    Q_PROPERTY(QString ownIp READ ownIp NOTIFY ownIpChanged)

public:
    explicit SettingsAdapter(QObject *parent = 0);

    QString targetIp() const;
    void setTargetIp(const QString &targetIp);

    int targetPort() const;
    void setTargetPort(int targetPort);

    QString ownIp() const;
    void setOwnIp(const QString &ownIp);

private:
    QString _targetIp;
    int     _targetPort;
    QString _ownIp;

signals:
    void targetIpChanged();
    void targetPortChanged();
    void ownIpChanged();

    void sig_targetIpChanged(QString ip);
    void sig_targetPortChanged(int port);
};

#endif // SETTINGSADAPTER_H
