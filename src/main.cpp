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
#include "selectionwindow.hpp"
#include "x11listener.hpp"
#include "inputbackend.hpp"
#include "inputdevice.hpp"

#include <QApplication>
#include <QString>
#include <X11/extensions/XInput.h>

#include <iostream>
#include <map>

using namespace std;

int main(int argc,char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc,argv);
    
    map<QString,BackendFactory*> backends = BackendFactory::factories();
    
    for (auto b : backends) {
        qDebug()<<"* backend:"<<b.first;
    }
    
    InputBackend* backend = backends["x11.xinput.xlib"]->get();
    backend->update();
    
    qDebug()<<"devices:";
    
    for (InputDevice* device:backend->devices()) {
        qDebug()<<"-"<<device->name();
    }
    
    //SelectionWindow* swindow = new SelectionWindow(backend);
    //swindow->exec();
    
    CalibrationWindow* cw=new CalibrationWindow(backend);
    //X11Listener listener(cw->winId());
    //listener.start();
    
    app.exec();
    
    //listener.terminate();
    //listener.wait();
    
    return 0;
}
