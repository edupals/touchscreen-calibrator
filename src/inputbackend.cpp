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

#include "inputbackend.hpp"
#include "inputdevice.hpp"

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QGenericMatrix>

using namespace std;

map<QString,BackendFactory*> BackendFactory::m_factories;

void InputBackend::setName(QString name)
{
    m_name=name;
}

InputBackend::InputBackend()
{
}

InputBackend::~InputBackend()
{
}

QString InputBackend::name() const
{
    return m_name;
}

bool InputBackend::loadCalibration(InputDevice* device)
{
    qDebug()<<"loading calibration...";
    
    QFile cfg(QDir::homePath()+"/.config/touchscreen-calibrator/calibration.cfg");
    
    if (!cfg.exists()) {
        qDebug()<<"no calibration file";
        return false;
    }
    
    cfg.open(QIODevice::ReadWrite);
    QByteArray raw = cfg.readAll();
    cfg.close();

    QJsonDocument json=QJsonDocument::fromJson(raw);
    QJsonObject obj=json.object();
    
    QJsonValue vBackend=obj[m_name];
    
    if (!vBackend.isObject()) {
        return false;
    }
    
    QJsonValue vDevice=vBackend.toObject()[device->name()];
    if (!vDevice.isArray()) {
        qDebug()<<"oh no!";
    }
    
    float m[9];
    
    QJsonArray vMatrix = vDevice.toArray();
    
    for (int n=0;n<9;n++) {
        m[n]=vMatrix[n].toDouble();
    }
    
    QMatrix3x3 matrix(m);
    
    qDebug()<<matrix;
    
    device->setMatrix(matrix);
    
    return true;
}

void InputBackend::saveCalibration(InputDevice* device)
{
    QDir cfgdir = QDir::homePath()+"/.config/touchscreen-calibrator/";
    qDebug()<<"saving calibration...";
    
    if (!cfgdir.exists()) {
        qDebug()<<"creating path...";
        if(!QDir::home().mkpath(".config/touchscreen-calibrator/")) {
            qDebug()<<"Error";
            return;
        }
    }
    
    QFile cfg(cfgdir.path()+"/calibration.cfg");
    
    cfg.open(QIODevice::ReadWrite);
    QByteArray raw = cfg.readAll();
    cfg.close();

    QJsonDocument json=QJsonDocument::fromJson(raw);
    QJsonObject obj=json.object();
    
    QJsonArray vMatrix;
    QMatrix3x3 matrix = device->getMatrix();
    for (int n=0;n<9;n++) {
        vMatrix.append(matrix.data()[n]);
    }
    
    QJsonObject backend=obj[m_name].toObject();
    
    backend.insert(device->name(),vMatrix);
    qDebug()<<backend;
    
    obj.insert(m_name,backend);
    json.setObject(obj);
    
    cfg.open(QIODevice::WriteOnly | QIODevice::Truncate);
    cfg.write(json.toJson());
    cfg.close();
}
