/*
    touchscreen-calibrator

    Copyright (C) 2020  Enrique Medina Gremaldos <quiqueiii@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TSC_PROXY
#define TSC_PROXY

#include "inputbackend.hpp"
#include "inputdevice.hpp"

#include <QObject>

class ProxyDevice: public QObject
{
    Q_OBJECT
    
    Q_PROPERTY(QString name MEMBER m_name READ name NOTIFY nameChanged)
    Q_PROPERTY(qint32 id MEMBER m_id READ id NOTIFY idChanged)
    
    public:
    
    QString m_name;
    quint32 m_id;
    
    ProxyDevice(quint32 id,QString name): m_id(id),m_name(name) {}
    
    QString name()
    {
        return m_name;
    }
    
    quint32 id()
    {
        return m_id;
    }
    
    signals:
    
    void nameChanged();
    void idChanged();
};

class ProxyBackend: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QObject*> devices MEMBER m_devices NOTIFY devicesChanged)
    
    protected:
    
    InputBackend* m_backend;
    
    public:
    
    QList<QObject*> m_devices;
    ProxyBackend(InputBackend* backend);
    
    Q_INVOKABLE void cancel();
    Q_INVOKABLE void accept(quint32 value);
    
    signals:
    
    void devicesChanged();
    void canceled();
    void accepted(quint32 id);
};

#endif
