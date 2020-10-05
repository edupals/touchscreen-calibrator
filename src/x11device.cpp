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

#include "x11device.hpp"

#include <QTransform>

#include <X11/Xatom.h>
#include <X11/extensions/XInput2.h>

#include <iostream>
#include <exception>

using namespace std;

X11InputDevice::X11InputDevice(XID id, QString name)
{
    m_id=id;
    setName(name);
}

X11InputDevice::~X11InputDevice()
{
}

XID X11InputDevice::xid()
{
    return m_id;
}

void X11InputDevice::resetMatrix()
{
    QMatrix3x3 identity;
    
    setMatrix(identity);
}

void X11InputDevice::restoreMatrix()
{
    setMatrix(m_oldMatrix);
}

void X11InputDevice::setMatrix(QMatrix3x3& m)
{
    m_oldMatrix=getMatrix();
    
    Atom propMatrix;
    Atom reqType;
    int format;
    
    Display* display = XOpenDisplay(0);
    
    propMatrix=XInternAtom (display, "Coordinate Transformation Matrix", False);
    reqType=XInternAtom (display, "FLOAT", False);
    
    XIChangeProperty(display, m_id, 
        propMatrix, reqType,
        32, PropModeReplace,
        (unsigned char*)m.data(), 9);
    
    XCloseDisplay(display);
}

QMatrix3x3 X11InputDevice::getMatrix()
{
    QMatrix3x3 matrix;
    Atom propMatrix;
    Atom realType;
    Atom reqType;
    int realFormat;
    unsigned long nitems;
    unsigned long bytesafter;
    unsigned char* property;
    
    Display* display = XOpenDisplay(0);
    
    propMatrix=XInternAtom (display, "Coordinate Transformation Matrix", False);
    reqType=XInternAtom (display, "FLOAT", False);
    
    Status status = XIGetProperty(display,m_id,
        propMatrix,
        0,9,
        False,
        AnyPropertyType,
        &realType,
        &realFormat,
        &nitems,
        &bytesafter,
        &property
    );
    
    if (status!=Success) {
        throw runtime_error("Failed to get transformation matrix from device");
    }
    
    if (realType!=reqType or realFormat!=32) {
        throw runtime_error("Unexpected read from transformation matrix");
    }
    
    matrix = QMatrix3x3((float*)property);
    
    XFree(property);
    XCloseDisplay(display);
    
    return matrix;
}

void X11InputDevice::calibrate(QList<qreal>& points)
{
    if (points.size()<8) {
        throw runtime_error("No enough calibration points");
    }
    
    QPolygonF source;
    QPolygonF dest;
    
    source<<QPointF(0.1,0.1)<<QPointF(0.9,0.1)<<QPointF(0.9,0.9)<<QPointF(0.1,0.9);
    dest<<QPointF(points[0],points[1])<<QPointF(points[2],points[3])<<QPointF(points[4],points[5])<<QPointF(points[6],points[7]);
    
    QTransform quad;
    QTransform::quadToQuad(dest,source,quad);
    
    float m[9];
    m[0]=quad.m11();
    m[1]=quad.m12();
    m[2]=quad.m13();
    
    m[3]=quad.m21();
    m[4]=quad.m22();
    m[5]=quad.m23();
    
    m[6]=quad.m31();
    m[7]=quad.m32();
    m[8]=quad.m33();
    
    QMatrix3x3 matrix(m);
    
    setMatrix(matrix);
    qInfo()<<matrix;
    
}
