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
    
    //force an identity matrix before reading raw coords
    targetDevice->resetMatrix();
    
    XDevice* device = XOpenDevice(display,targetDevice->xid());
    XEventClass cls[2];
    int buttonPressEvent;
    int buttonReleaseEvent;
    
    DeviceButtonPress(device,buttonPressEvent,cls[0]);
    DeviceButtonRelease(device,buttonReleaseEvent,cls[1]);
    
    XSelectExtensionEvent(display,targetWindow,cls,2);
    
    while (!isFinished()) {
        
        XNextEvent(display,&event);
        
        if (event.type==buttonPressEvent) {
            XDeviceButtonPressedEvent* eventPress = reinterpret_cast<XDeviceButtonPressedEvent*> (&event);
            
            qDebug()<<"button down:"<<eventPress->x<<","<<eventPress->y;
            qDebug()<<eventPress->axis_data[0]<<","<<eventPress->axis_data[1];
            emit buttonPressed(eventPress->x,eventPress->y);
        }
        
        if (event.type==buttonReleaseEvent) {
            XDeviceButtonReleasedEvent* eventRelease = reinterpret_cast<XDeviceButtonReleasedEvent*> (&event);
            
            qDebug()<<"button up:"<<eventRelease->x<<","<<eventRelease->y;
            emit buttonReleased(eventRelease->x,eventRelease->y);
        }
    }
}
