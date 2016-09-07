#ifndef METERMODEL_H
#define METERMODEL_H

#include <QObject>

class MeterModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(float left READ left NOTIFY leftChanged)
    Q_PROPERTY(float right READ right NOTIFY rightChanged)

public:
    explicit MeterModel(QObject* parent = 0);

    float left() const;
    void setLeft(float left);

    float right() const;
    void setRight(float right);

private:
    float _left;
    float _right;

signals:
    void rightChanged();
    void leftChanged();

};

#endif // METERMODEL_H
