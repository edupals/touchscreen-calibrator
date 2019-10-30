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

#include "calibrationwindow.hpp"

#include <QApplication>
#include <X11/extensions/XInput.h>

#include <iostream>

using namespace std;


int main(int argc,char* argv[])
{
    
    XDeviceInfo *devices;
    
    Display *dpy = XOpenDisplay(0);
    
    int num_devices;
    devices = XListInputDevices(dpy, &num_devices);
    
    for (int n=0;n<num_devices;n++) {
        clog<<"["<<devices[n].id<<"] "<<devices[n].name<<endl;
        
        int num_classes=devices[n].num_classes;
        int c=0;
        
        if (num_classes>0) {
            clog<<"classes: "<<num_classes<<endl;
        }
        
        XAnyClassPtr p = devices[n].inputclassinfo;
        
        while (c<num_classes) {
            clog<<"    class "<<p->c_class<<endl;
            clog<<"    length "<<p->length<<endl;
            
            if (p->c_class==ValuatorClass) {
                XValuatorInfo* info=(XValuatorInfo*)p;
                
                clog<<"        num axis: "<<(int)info->num_axes<<endl;
                clog<<"        mode: "<<(int)info->mode<<endl;
                
                if (info->mode==Absolute) {
                    XDevice* dev = XOpenDevice(dpy,devices[n].id);
                    int num_props;
                    Atom* props=XListDeviceProperties(dpy,dev,&num_props);
                    
                    for (int i=0;i<num_props;i++) {
                        cout<<"            "<<XGetAtomName(dpy,props[i])<<endl;
                    }
                }
            }
            
            p=(XAnyClassPtr)((char*)p+p->length);
            c++;
        }
        
    }
    
    XFreeDeviceList(devices);
     
     
    QApplication app(argc,argv);
    
    CalibrationWindow* cw=new CalibrationWindow();
    
    return app.exec();
}
