#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>

#include "services/udpreceiver.h"
#include "services/udpsender.h"
#include <QQmlContext>


//Adapter
#include "models/meteradapter.h"
#include "models/ChannleFilter.h"
#include "models/settingsadapter.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView view;

    qmlRegisterType<ChannleFilter>("Helpers", 1, 0, "ChannleFilter");

    MeterAdapter * meterAdapter = new MeterAdapter(&app);
    ChannleAdapter *channleAdapter = new ChannleAdapter(&app);

    UdpReceiver *provider = new UdpReceiver(meterAdapter, channleAdapter, &app);

    UdpSender *sender = new UdpSender(&app);

    QObject::connect(provider, &UdpReceiver::refreshTrackList, [=]()
    {
        sender->send("/live/name/track");
    });

    SettingsAdapter *settingsAdapter = new SettingsAdapter(&app);

    QObject::connect(settingsAdapter, &SettingsAdapter::sig_targetPortChanged, sender, &UdpSender::setTargetPort);
    QObject::connect(settingsAdapter, &SettingsAdapter::sig_targetIpChanged, sender, &UdpSender::setTargetIp);

    view.rootContext()->setContextProperty("meters", meterAdapter);
    view.rootContext()->setContextProperty("channles", channleAdapter);
    view.rootContext()->setContextProperty("sender", sender);
    view.rootContext()->setContextProperty("settings", settingsAdapter);

    view.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    view.setResizeMode(QQuickView::SizeViewToRootObject);
    view.setWidth(1024);
    view.setHeight(768);

    view.show();

    return app.exec();
}

