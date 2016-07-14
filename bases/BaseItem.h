#ifndef BASEITEM_H
#define BASEITEM_H
#include <QObject>

class BaseItem : public QObject
{
    Q_OBJECT

public:
    BaseItem(QObject* parent = 0);

signals:
    void dataChanged();


public slots:

};

#endif // BASEITEM_H
