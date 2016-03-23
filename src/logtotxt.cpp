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

#include "logtotxt.h"

LogToTxt::LogToTxt(QString filename)
{
    filename.replace(".log", "");
    output.setFileName(filename + ".txt");
    output.open(QIODevice::WriteOnly);
    process(filename);
    output.close();
    exit(0);
}

LogToTxt::~LogToTxt()
{
    
}

void LogToTxt::process(QString filename)
{
    STOxs_Logfile log;
    QString logHeader;
    QByteArray data;
    QFile file(filename + ".log");
    if(file.open(QIODevice::ReadOnly))
    {
	QDataStream in(&file);
	in >> logHeader;
	
	if(logHeader == "STOxs_Logfile2")
	{
	    unsigned long nTotalBytes = file.size();
	    unsigned long nBytes = 0;
	    
	    log.Clear();
	    in >> data;
	    int k=0;
	    while(!data.isEmpty())
	    {
		nBytes += data.size();
		STOxs_LogfileFrame *frame = log.add_frame();
		frame->ParseFromArray(data.data(), data.size());
		in >> data;
		QString str;
		str.sprintf("%d %f %f %f %f %f %f %f %f\n", k, log.frame(k).world().tcapture(), log.frame(k).world().stoxs().robot(0).pos().x(), log.frame(k).world().stoxs().robot(0).pos().y(), log.frame(k).world().stoxs().robot(0).w(), log.frame(k).world().stoxs().robot(0).speed(), log.frame(k).world().stoxs().robot(0).vel().vx(), log.frame(k).world().stoxs().robot(0).vel().vy(), log.frame(k).world().stoxs().robot(0).vel().vw());
		output.write(str.toStdString().c_str());
		printf("[%3d%c] Converting File %s.log\n", (int)(((double)(nBytes)/(double)(nTotalBytes))*100), 37, filename.toStdString().c_str());
		k++;
	    }
	    printf("[%3d%c] Converting File %s.log\n", 100, 37, filename.toStdString().c_str());
	    printf("File Converted %d frames\n", log.frame_size());
	    
	}
	else
	{
	    printf("File %s.log: Format not supported!\n", filename.toStdString().c_str());
	}
	file.close();
	data.clear();
    }
    else
    {
	printf("File %s.log can't open\n", filename.toStdString().c_str());
    }
}