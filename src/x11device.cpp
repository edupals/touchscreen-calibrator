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
    /*
    clog<<"status:"<<status<<endl;
    clog<<nitems<<","<<bytesafter<<endl;
    clog<<realFormat<<endl;
    clog<<XGetAtomName(display,realType)<<endl;
    
    for (int n=0;n<9;n++) {
        clog<<matrix[n]<<endl;
    }
    */
    
    XFree(property);
    XCloseDisplay(display);
    
    return matrix;
}

void X11InputDevice::calibrate(QList<qreal>& points)
{
    if (points.size()<8) {
        throw runtime_error("No enough calibration points");
    }
    
    float m[9];
    
    float x0=points[0];
    float x1=points[2];
    float x2=points[6];
    float x3=points[4];
    
    float y0=points[1];
    float y1=points[3];
    float y2=points[7];
    float y3=points[5];
    
    float dx1 = x1 - x2, dy1 = y1 - y2;
    float dx2 = x3 - x2, dy2 = y3 - y2;
    float sx = x0 - x1 + x2 - x3;
    float sy = y0 - y1 + y2 - y3;
    float g = (sx * dy2 - dx2 * sy) / (dx1 * dy2 - dx2 * dy1);
    float h = (dx1 * sy - sx * dy1) / (dx1 * dy2 - dx2 * dy1);
    
    float A0 = 0.1 * x0 * g;
    float A1 = 0.1 * x0 * h;
    float A2 = 0.1 * y0 * g;
    float A3 = 0.1 * y0 * h;
    
    float A4 = 0.9 * x1 * g;
    float A5 = 0.1 * x1 * h;
    float A6 = 0.9 * y1 * g;
    float A7 = 0.1 * y1 * h;
    
    float A12 = 0.1 * x3 * g;
    float A13 = 0.9 * x3 * h;
    float A14 = 0.1 * y3 * g;
    float A15 = 0.9 * y3 * h;
    
    float a = (x1-x0-A0-A1+A4+A5)/0.8;
    float d = (y1-y0-A2-A3+A6+A7)/0.8;
    float b = (x3-x0-A0-A1+A12+A13)/0.8;
    float e = (y3-y0-A2-A3+A14+A15)/0.8;
    float c = -0.1*a-0.9*b+x3+A12+A13;
    float f = -0.1*d -0.9*e+y3+A14+A15;
    
    float A =     e - f * h;
    float B = c * h - b;
    float C = b * f - c * e;
    float D = f * g - d;
    float E =     a - c * g;
    float F = c * d - a * f;
    float G = d * h - e * g;
    float H = b * g - a * h;
    float I = a * e - b * d;
    
    m[0]=A;
    m[1]=B;
    m[2]=C;
    
    m[3]=D;
    m[4]=E;
    m[5]=F;
    
    m[6]=G;
    m[7]=H;
    m[8]=I;
    
    QMatrix3x3 matrix(m);
    
    setMatrix(matrix);
    //qInfo()<<matrix;
    
    for (int n=0;n<9;n++) {
        qInfo()<<" "<<m[n];
    }
}
