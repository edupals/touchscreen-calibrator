/*
    touchscreen-calibrator

    Copyright (C) 2020  Enrique Medina Gremaldos <quiqueiii@gmail.com>

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

#include "server.hpp"

#include <QDebug>

Server::Server(InputBackend* backend) : m_backend(backend)
{
    qInfo()<<"server mode";
    
    //perform an initial calibration
    OnDevicesChanged();

    connect(m_backend,&InputBackend::devicesChanged,this,&Server::OnDevicesChanged);
    m_backend->listen();
}

void Server::OnDevicesChanged()
{
    m_backend->update();
    
    qInfo()<<"Found input devices:";
    
    for (InputDevice* device : m_backend->devices()) {
        qInfo()<<"--"<<device->name();
        
        bool calibrated = m_backend->loadCalibration(device);
        
        qDebug()<<"loaded calibration: "<<calibrated;
    }
}
