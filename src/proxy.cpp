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

#include "proxy.hpp"

#include <QDebug>

ProxyBackend::ProxyBackend(InputBackend* backend,QWindow* window)
{
    uint32_t n=0;
    for (InputDevice* device : backend->devices()) {
        ProxyDevice* pd = new ProxyDevice(n,device->name());
        m_devices.append(pd);
        n++;
    }
    
    m_backend=backend;
    m_window=window;
}

void ProxyBackend::cancel()
{
    emit canceled();
}

void ProxyBackend::accept(quint32 id)
{
    emit accepted(id);
    
    //ToDo: safe this a little
    InputDevice* target=m_backend->devices()[id];
    
    qInfo()<<"Listening events for:"<<target->name();
    
    m_backend->listen(m_window,target);
}
