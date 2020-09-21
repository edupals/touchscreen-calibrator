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

#ifndef TSC_X11_LISTENER
#define TSC_X11_LISTENER

#include <QThread>
#include <QWindow>

#include "x11device.hpp"

class X11Listener : public QThread
{
    Q_OBJECT
    
    private:
    
    WId targetWindow;
    X11InputDevice* targetDevice;
    
    public:
    
    X11Listener(WId window,InputDevice* device);
    
    void run() override;
    
    signals:
    
    void buttonPressed(int x,int y);
    void buttonReleased(int x,int y);
};

#endif
