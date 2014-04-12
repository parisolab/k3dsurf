/***************************************************************************
 *   Copyright (C) 2007 by Abderrahman Taha                                *
 *                                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA            *
 ***************************************************************************/
/*
#ifndef videoplayer_H
#define videoplayer_H
*/
#include <qmainwindow.h>
#include <qmovie.h>
#include <qlabel.h>
#include <qimage.h>
#include <qlineedit.h>
#include <qfiledialog.h>
#include <qpicture.h>
#include <qbutton.h>
#include <qcheckbox.h>
#include <qpushbutton.h>
#include <qgroupbox.h>
#include <qscrollbar.h>

class videoplayer: public QMainWindow
{
    Q_OBJECT

public:
    videoplayer(QImage);
    ~videoplayer();
public slots:
    void connectcontrols();
    void saveas();
    void f_1(int);
    void f_2();
    void f_3();
    void f_4();
    void f_5();
public:
    QMovie *m;
    QLabel *l;
    QGroupBox * groupBox ;
    QScrollBar * scrollBar55;
    QCheckBox * pngcheckBox;
    QCheckBox * jpgcheckBox;
    QCheckBox * bmpcheckBox;
    QPushButton * pushScreenshot;
    QImage buf;
    int image_quality;
};
//#endif
