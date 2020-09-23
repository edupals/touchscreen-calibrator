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

#ifndef TSC_INPUT_DEVICE
#define TSC_INPUT_DEVICE

#include <QString>
#include <QGenericMatrix>
#include <QList>

class InputDevice
{
    protected:
    QString m_name;
    
    void setName(const QString& name);
    
    public:
    
    InputDevice();
    virtual ~InputDevice();
    
    QString name() const;
    
    virtual void resetMatrix() = 0;
    virtual void restoreMatrix() = 0;
    virtual void setMatrix(QMatrix3x3& m) = 0;
    virtual QMatrix3x3 getMatrix() = 0;
    virtual void calibrate(QList<qreal>& points) = 0;
};

#endif
