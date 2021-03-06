//======================================================================//
//  This software is free: you can redistribute it and/or modify        //
//  it under the terms of the GNU General Public License Version 3,     //
//  as published by the Free Software Foundation.                       //
//  This software is distributed in the hope that it will be useful,    //
//  but WITHOUT ANY WARRANTY; without even the implied warranty of      //
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE..  See the      //
//  GNU General Public License for more details.                        //
//  You should have received a copy of the GNU General Public License   //
//  Version 3 in the file COPYING that came with this distribution.     //
//  If not, see <http://www.gnu.org/licenses/>                          //
//======================================================================//
//                                                                      //
//      Copyright (c) 2016 STOx's Small Size League RoboCup Team        //             
//      Universidad Santo Tomas - Bogota, Colombia                      //
//      http://www.stoxs.org/                                           //
//      small-size@stoxs.org                                            //
//                                                                      //
//======================================================================//

#ifndef LOGTOTXT_H
#define LOGTOTXT_H

#include <QtCore/QObject>
#include <QFile>
#include <QDataStream>

#include "messages_stoxs_logfile.pb.h"

class LogToTxt : public QObject
{
Q_OBJECT
public:
    LogToTxt(QString filename);
    virtual ~LogToTxt();
private:
    void process(QString filename);
    
private:
    QFile output;
 
private slots:

};

#endif // LOGTOTXT_H
