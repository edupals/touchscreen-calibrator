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

#ifndef TSC_SERVER
#define TSC_SERVER

#include "inputbackend.hpp"
#include "inputdevice.hpp"

#include <QObject>

class Server: public QObject
{
    Q_OBJECT
    
    protected:
    InputBackend* m_backend;
    
    public:
    
    Server(InputBackend* backend);
};

#endif
