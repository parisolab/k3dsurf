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
#include <qapplication.h>
#include <qmainwindow.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qfiledialog.h>
#include <qstatusbar.h>
#include <qmessagebox.h>
#include <qaccel.h>
#include <qevent.h>
#include <qmenudata.h>
#include <qcursor.h>
#include <qkeysequence.h>
#include <qcombobox.h>
#include <qaction.h>
#include <qfile.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qtoolbox.h>
#include <qmessagebox.h>
#include <qtextedit.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qpicture.h>
#include <qhttp.h>
#include <qnetworkprotocol.h>
#include <qnetwork.h>
#include <qdatetime.h>


#include "edit.h"
#include "k3dsurf.h"
#include "PovConfig.h"
#include "coloroptions.h"
#include "drawingoptions.h"
#include "presentation.h"

#include "GlWindow.h"
#include "panel.h"
#include "IsoPanel.h"
/*
#include "filesave.xpm"
#include "fileopen.xpm"
#include "gedit.xpm"
#include "gear.xpm"
#include "snapshot.xpm"
#include "pov.xpm"
#include "tools.xpm"
#include "graphics.xpm"
*/


class menubar: public QObject{
    Q_OBJECT
public:
QMenuBar * mainmenu;
QToolBar * tools;
k3dsurface * ptr;
QApplication * root;
editeur edit;
PovConfig *pvconfig;

// OpenGL menu:
QAction * SmoothPolyAction;
QAction * SmoothLinesAction;
QAction * PlanAction;
// Config Menu:
QAction * AllResoAction;
QAction * GridAction;
QAction * PtTrAction;
//  Iso colors;
QAction * AllColorAction;
QAction * IsoFrontColorAction;
QAction * IsoBackColorAction;
QAction * IsoGridColorAction;
QAction * IsoGroundColorAction;
QAction * IsoCndColorAction;
//Para Colors:
QAction * ParaFrontColorAction;
QAction * ParaBackColorAction;
QAction * ParaGridColorAction;
QAction * ParaGroundColorAction;
QAction * ParaCndColorAction;

QAction *PolysAction;
QAction *VerticeAction;
QAction *GridsAction;

QAction *ParametricAction;
QAction *IsosurfaceAction;
QAction *ToolsAction;
QAction *HallAction;
QAction *NDAction;

QPopupMenu *fileMenu;
QPopupMenu *fileMenuGL;
QPopupMenu *fileMenuConf;
QPopupMenu *povMenu;
QPopupMenu *infosMenu;
QPopupMenu *aboutMenu;
QPopupMenu *PageMenu;

coloroptions  *col;
presentation *present;
QWidget *ParametricWidget;
QWidget *IsosurfaceWidget;
QWidget *ToolsWidget;
QWidget *HallWidget;
QWidget *NDWidget;

public :
menubar();
menubar(k3dsurface *, QApplication *);
~menubar();
public slots:
void activateallcolor();
void constructmenubar();
void menufile();
void menugl();
void menupov();
void menuinfos();
void menuconfig();
void lunchedit();
void toolbar();
void SaveConfig();
void povconfig();
void runpov();
void loadConfig();
void opentestpov();
void openmeshpov();
void lunchcoloroptions();
void controlcenter();
void typecolor(int);
void transparencecl();
void transcl(int);
void bluecl(int);
void redcl(int);
void greencl(int);
void lunchabout();
void menuabout();
void tabsurfPageChanged();
void menupage();
void paraShow();
void isoShow();
void toolsShow();
void hallShow();
void ndShow();
void gotoweb();
};


