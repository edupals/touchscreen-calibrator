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

#ifndef TSC_INPUT_MANAGER
#define TSC_INPUT_MANAGER

#include <QString>
#include <QList>

class InputDevice;

class InputManager
{
    protected:
    QString m_backend;
        
    static QList<InputManager*> m_managers;
        
    InputManager();
        
    void setBackend(QString backend);
    
    static void add(InputManager* manager);
    static void remove(InputManager* manager);
    
    public:
        
    static QList<InputManager*> managers();
    
    virtual ~InputManager();
    
    QString backend();
    
    virtual QList<InputDevice*> devices()=0;
};

#endif