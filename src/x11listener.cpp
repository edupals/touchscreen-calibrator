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

#include <QDebug>

#include "x11listener.hpp"
#include "x11device.hpp"

#include <X11/Xlib.h>
#include <X11/extensions/XInput.h>

X11Listener::X11Listener(WId window,InputDevice* device)
{
    this->targetWindow=window;
    this->targetDevice=static_cast<X11InputDevice*>(device);
    
}

void X11Listener::run()
{
    Display *display = XOpenDisplay(0);
    XEvent event;
    
    XDevice* device = XOpenDevice(display,targetDevice->xid());
    XEventClass cls;
    int buttonPress;
    DeviceButtonPress(device,buttonPress,cls);
    XSelectExtensionEvent(display,targetWindow,&cls,1);
    
    while (!isFinished()) {
        
        XNextEvent(display,&event);
        
        if (event.type==buttonPress) {
            XDeviceButtonPressedEvent* eventPress = reinterpret_cast<XDeviceButtonPressedEvent*> (&event);
            
            qDebug()<<"coords:"<<eventPress->x<<","<<eventPress->y;
        }
    }
}
