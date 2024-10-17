
#ifndef MYCUSTOMCLASS_H
#define MYCUSTOMCLASS_H

#include <QObject>
#include <QString>
#include <QDebug>

class MyCustomClass : public QObject
{
    Q_OBJECT
    // Exposing properties to QML
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)

public:
    explicit MyCustomClass(QObject *parent = nullptr);

    // Getter and setter for 'name' property
    QString name() const;
    void setName(const QString &name);

    // Getter and setter for 'count' property
    int count() const;
    void setCount(int count);

signals:
    // Signals exposed to QML
    void nameChanged();
    void countChanged();
    void customSignal(const QString &message);

public slots:
    // Slots exposed to QML
    void incrementCount();
    void showMessage(const QString &message);

private:
    QString m_name;
    int m_count;
};

#endif // MYCUSTOMCLASS_H
