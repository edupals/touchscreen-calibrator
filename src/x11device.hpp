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

#ifndef TSC_X11_DEVICE
#define TSC_X11_DEVICE

#include "inputdevice.hpp"

#include <X11/extensions/XInput.h>

#include <QString>

class X11InputDevice: public InputDevice
{
    
    protected:
    
    XID m_id;
    QMatrix3x3 m_oldMatrix;
    
    public:
    
    X11InputDevice(XID id, QString name);
    virtual ~X11InputDevice();
    
    XID xid();
    
    void resetMatrix() override;
    void restoreMatrix() override;
    void setMatrix(QMatrix3x3& m) override;
    QMatrix3x3 getMatrix() override;
    void calibrate(QList<qreal>& points) override;
};

#endif
