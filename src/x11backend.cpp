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

#include "x11backend.hpp"

X11InputManager::X11InputManager()
{
    
    setBackend("x11.xinput.xlib");
    
    //fake some devices
    for (int n=0;n<6;n++) {
        X11InputDevice dev(this,n);
        
        m_devices.push_back(dev);
    }
    
    InputManager::add(this);
}

X11InputManager::~X11InputManager()
{
    
    InputManager::remove(this);
}

void X11InputManager::update()
{
    m_devices.clear();
    
    XDeviceInfo *devices;
    
    Display *display = XOpenDisplay(0);
    
    int num_devices;
    devices = XListInputDevices(display, &num_devices);
    
    
    XFreeDeviceList(devices);
}

QList<InputDevice*> X11InputManager::devices()
{
    QList<InputDevice*> ret;
    
    for (size_t n=0;n<m_devices.count();n++) {
        ret.push_back(m_devices[n]);
    }
    
    return ret;
}
