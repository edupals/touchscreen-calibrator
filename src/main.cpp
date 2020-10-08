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
#include "x11listener.hpp"
#include "inputbackend.hpp"
#include "inputdevice.hpp"

#include <QApplication>
#include <QString>
#include <QCommandLineParser>
#include <X11/extensions/XInput.h>

#include <iostream>
#include <map>

using namespace std;

int main(int argc,char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc,argv);
    QApplication::setApplicationName("Touchscreen calibrator");
    QApplication::setApplicationVersion("1.0");
    
    QCommandLineParser parser;
    parser.setApplicationDescription("Touchscreen calibration tools");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("mode", "gui,server");
    
    parser.process(app);
    
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
    
    const QStringList args = parser.positionalArguments();
    if (args.size()<2) {
        parser.showHelp(0);
    }
    
    const QString mode = args[0];
    
    if (mode=="gui") {
        CalibrationWindow* cw=new CalibrationWindow(backend);
        return app.exec();
    }
    
    parser.showHelp(0);
    
    return 0;
}
