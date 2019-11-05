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

#include "x11listener.hpp"

#include <QDebug>

#include <X11/Xlib.h>
#include <X11/extensions/XInput.h>

X11Listener::X11Listener(WId id)
{
    this->target=id;
    qDebug()<<"Listen events for "<<id;
}

void X11Listener::run()
{
    Display *display = XOpenDisplay(0);
    Window window = target;
    XEvent event;
    
    XDevice* device = XOpenDevice(display,9);
    XEventClass cls;
    int button_press;
    DeviceButtonPress(device,button_press,cls);
    XSelectExtensionEvent(display,window,&cls,1);
    
    while (true) {
        
        XNextEvent(display,&event);
        
        if (event.type==button_press) {
            XDeviceButtonPressedEvent* event_press = reinterpret_cast<XDeviceButtonPressedEvent*> (&event);
            
            qDebug()<<"coords:"<<event_press->x<<","<<event_press->y;
        }
    }
}