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

#include <QObject>

#include <X11/extensions/XInput2.h>

#include <iostream>

#define TSC_X11_BACKEND_NAME "x11.xinput.xlib"

using namespace std;

X11InputBackend::X11InputBackend()
{
    
    setName(TSC_X11_BACKEND_NAME);
    
}

X11InputBackend::~X11InputBackend()
{
    
}

void X11InputBackend::update()
{
    //TODO: delete device pointers
    
    m_devices.clear();
    
    XDeviceInfo* devices;
    
    Display* display = XOpenDisplay(0);
    
    int num_devices;
    devices = XListInputDevices(display, &num_devices);
    
    for (int n=0;n<num_devices;n++) {
        
        XAnyClassPtr p = devices[n].inputclassinfo;
        for (int c=0;c<devices[n].num_classes;c++) {
            
            if (p->c_class==ValuatorClass) {
                XValuatorInfo* info=(XValuatorInfo*)p;
                
                if (info->mode==Absolute) {
                    /*
                    XDevice* dev = XOpenDevice(dpy,devices[n].id);
                    int num_props;
                    Atom* props=XListDeviceProperties(dpy,dev,&num_props);
                    
                    for (int i=0;i<num_props;i++) {
                        cout<<"            "<<XGetAtomName(dpy,props[i])<<endl;
                    }
                    */
                    
                    X11InputDevice* x11device = new X11InputDevice(devices[n].id,devices[n].name);
                    m_devices.push_back(x11device);
                }
                
            }
            
            p=(XAnyClassPtr)((char*)p+p->length);
        }
    }
    
    XFreeDeviceList(devices);
}

QList<InputDevice*> X11InputBackend::devices()
{
    QList<InputDevice*> ret;
    
    for (size_t n=0;n<m_devices.count();n++) {
        ret.push_back(m_devices[n]);
    }
    
    return ret;
}

void X11InputBackend::listen(QWindow* window,InputDevice* device)
{
    listener = new X11Listener(window->winId(),device);
    connect(listener,&X11Listener::buttonPressed,this,&InputBackend::buttonPressed);
    connect(listener,&X11Listener::buttonReleased,this,&InputBackend::buttonReleased);

    listener->start();
    clog<<"launched listener"<<endl;
}

void X11InputBackend::listen()
{
    listener = new X11Listener();
    connect(listener,&X11Listener::devicesChanged,this,&InputBackend::devicesChanged);
    
    listener->start();
}

X11Factory::X11Factory()
{
    BackendFactory::m_factories[TSC_X11_BACKEND_NAME]=this;
    m_backend=nullptr;
}

InputBackend* X11Factory::get()
{
    if (!m_backend) {
        m_backend = new X11InputBackend();
    }
    
    return m_backend;
}
