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
 *   51 Franklin Street, Fifth Floor,Boston, MA 02110-1301 USA             *
 ***************************************************************************/
#include <qapplication.h>
#include <qmainwindow.h>
#include <qfiledialog.h>
#include <qcombobox.h>
#include <qaction.h>
#include <qfile.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <qtextedit.h>
#include "menubar.h"
#include "glviewer.h"



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
int main( int argc, char **argv )
{
    QApplication a( argc, argv );
    k3dsurface  mainwindow;
#ifndef QT_NO_WIDGET_TOPEXTRA   // for Qt/Embedded minimal build

#endif
mainwindow.setGeometry(6, 30, 990, 724);
a.setMainWidget( &mainwindow );

menubar *  newmenu = new menubar(&mainwindow, &a);
newmenu->constructmenubar();
// Init Parametric Page:
//mainwindow.ParametricSurfaceProcess();
// Init Iso page:
mainwindow.Initisopage();

/*
mainwindow.setCaption("K3DSurf v0.6.1.5-Dev: Math for Fun");
mainwindow.mesh->toggle();
mainwindow.mesh->setText("Fill");
mainwindow.box->setEnabled(TRUE);
mainwindow.box->setText("Lines");
mainwindow.IsoImplicitBox->insertItem("Chain");
mainwindow.IsoImplicitBox->insertItem("Chain_2");
mainwindow.textLabel1_14_4->setText("Examples (44)");
*/
//mainwindow.implicitfunct->setTextFormat(Qt::RichText);
mainwindow.show();
newmenu->loadConfig();
return (a.exec());
}
