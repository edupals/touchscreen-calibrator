/*
    touchscreen-calibrator

    Copyright (C) 2019  Enrique Medina Gremaldos <quiqueiii@gmail.com>

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

#ifndef TSC_INPUT_BACKEND
#define TSC_INPUT_BACKEND

#include <QString>
#include <QWindow>

#include <map>

class InputDevice;

class InputBackend: public QObject
{
    Q_OBJECT
    
    protected:
    
    QString m_name;
    
    void setName(QString name);
    
    public:
    
    InputBackend();
    virtual ~InputBackend();
    
    QString name() const;
    
    virtual void update()=0;
    virtual QList<InputDevice*> devices()=0;
    virtual void listen(QWindow* window,InputDevice* device)=0;
    
    signals:
    
    void buttonPressed(int x,int y);
    void buttonReleased(int x,int y);
};

class BackendFactory
{
    protected:
    
    static std::map<QString,BackendFactory*> m_factories;
    
    InputBackend* m_backend;
    
    public:
    
    BackendFactory()
    {
        m_backend=nullptr;
    }
    
    virtual ~BackendFactory()
    {
        if (m_backend) {
            delete m_backend;
        }
    }
    
    static std::map<QString,BackendFactory*> factories()
    {
        return m_factories;
    }
    
    virtual InputBackend* get()=0;
};

#endif
