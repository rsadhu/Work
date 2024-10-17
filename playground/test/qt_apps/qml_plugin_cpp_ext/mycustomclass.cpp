#include "MyCustomClass.h"


MyCustomClass::MyCustomClass(QObject *parent)
    : QObject(parent), m_name("Default"), m_count(0) {}

QString MyCustomClass::name() const
{
    return m_name;
}

void MyCustomClass::setName(const QString &name)
{
    if (m_name != name) {
        m_name = name;
        emit nameChanged();  // Emit signal when name changes
    }
}

int MyCustomClass::count() const
{
    return m_count;
}

void MyCustomClass::setCount(int count)
{
    if (m_count != count) {
        m_count = count;
        emit countChanged();  // Emit signal when count changes
    }
}

void MyCustomClass::incrementCount()
{
    setCount(m_count + 1);  // Increment and update the count
}

void MyCustomClass::showMessage(const QString &message)
{
    emit customSignal(message);  // Emit custom signal to display message
    qDebug() << "Message from QML: " << message;
}
