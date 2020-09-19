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

#ifndef TSC_X11_BACKEND
#define TSC_X11_BACKEND

#include "inputbackend.hpp"
#include "x11device.hpp"

#include <QList>

class X11InputBackend: public InputBackend
{
    protected:
        
    QList<X11InputDevice*> m_devices;
    
    public:
    
    X11InputBackend();
    ~X11InputBackend();
    
    void update() override;
    QList<InputDevice*> devices() override;
    void listen(QWindow* window,InputDevice* device) override;
};

class X11Factory: public BackendFactory
{
    public:
    
    X11Factory();
    InputBackend* get() override;

};

#endif
