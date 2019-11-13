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

#ifndef TSC_INPUT_BACKEND
#define TSC_INPUT_BACKEND

#include <QString>

class InputDevice;

class InputBackend
{
    protected:
    
    QString m_name;
    
    void setName(QString name);
    
    public:
    
    InputBackend();
    virtual ~InputBackend();
    
    QString name() const;
    
    virtual void update()=0;
    virtual QList<InputDevice*> devices()=0;
    
};

#endif
