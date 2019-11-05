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

#ifndef TSC_X11_BACKEND
#define TSC_X11_BACKEND

#include "inputmanager.hpp"
#include "inputdevice.hpp"

#include <QList>
#include <QDebug>

#include <X11/extensions/XInput.h>

class X11InputDevice: public InputDevice
{
    protected:
        
    XID m_deviceid;
    
    public:
        
    X11InputDevice(InputManager* manager, XID deviceid);
    
};

class X11InputManager: public InputManager
{
    protected:
        
    QList<X11InputDevice> m_devices;
    
    void update();
    
    public:
    
    X11InputManager();
    ~X11InputManager();
    
    QList<InputDevice*> devices() override;
};

#endif