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
#include "menubar.h"
#include "glviewer.h"
#include "filesave.xpm"
#include "fileopen.xpm"
#include "gedit.xpm"
#include "gear.xpm"
#include "snapshot.xpm"
#include "pov.xpm"
#include "tools.xpm"
#include "graphics.xpm"

void menubar::lunchabout(){
present = new presentation(0, "About", WDestructiveClose | WStyle_StaysOnTop);
present->show();
};

//=====================================//
void menubar::typecolor(int cl)
{
    ptr->isoWidget->colortype = cl;
    ptr->IsoGlWidget->colortype = cl;
    ptr->connectWidget2->colortype = cl;
    ptr->ParamGlWidget->colortype = cl;

if(ptr->tabsurf->currentPageIndex() == 1)  {
     switch(cl) {

    case 0:
col->red->setValue((int)(ptr->IsoGlWidget->LocalScene.frontcol[0]*255.)) ;
col->green->setValue((int)(ptr->IsoGlWidget->LocalScene.frontcol[1]*255.)) ;
col->blue->setValue((int)(ptr->IsoGlWidget->LocalScene.frontcol[2]*255.));
col->transparent->setValue((int)(ptr->IsoGlWidget->LocalScene.frontcol[3]*255.));

 break;
    case 1:
col->red->setValue((int)(ptr->IsoGlWidget->LocalScene.backcol[0]*255.)) ;
col->green->setValue((int)(ptr->IsoGlWidget->LocalScene.backcol[1]*255.)) ;
col->blue->setValue((int)(ptr->IsoGlWidget->LocalScene.backcol[2]*255.));
col->transparent->setValue((int)(ptr->IsoGlWidget->LocalScene.backcol[3]*255.));

 break;
    case 2:
col->red->setValue((int)(ptr->IsoGlWidget->LocalScene.gridcol[0]*255.)) ;
col->green->setValue((int)(ptr->IsoGlWidget->LocalScene.gridcol[1]*255.)) ;
col->blue->setValue((int)(ptr->IsoGlWidget->LocalScene.gridcol[2]*255.));
col->transparent->setValue((int)(ptr->IsoGlWidget->LocalScene.gridcol[3]*255.));

 break;
    case 3:
col->red->setValue((int)(ptr->IsoGlWidget->LocalScene.groundcol[0]*255.)) ;
col->green->setValue((int)(ptr->IsoGlWidget->LocalScene.groundcol[1]*255.)) ;
col->blue->setValue((int)(ptr->IsoGlWidget->LocalScene.groundcol[2]*255.));
col->transparent->setValue((int)(ptr->IsoGlWidget->LocalScene.groundcol[3]*255.));

 break;

     case 4:
col->red->setValue((int)(ptr->IsoGlWidget->LocalScene.condcol[0]*255.)) ;
col->green->setValue((int)(ptr->IsoGlWidget->LocalScene.condcol[1]*255.)) ;
col->blue->setValue((int)(ptr->IsoGlWidget->LocalScene.condcol[2]*255.));
col->transparent->setValue((int)(ptr->IsoGlWidget->LocalScene.condcol[3]*255.));

 break;

}
}
    else {

    switch(cl) {

    case 0:
col->red->setValue((int)(ptr->ParamGlWidget->LocalScene.frontcol[0]*255.)) ;
col->green->setValue((int)(ptr->ParamGlWidget->LocalScene.frontcol[1]*255.)) ;
col->blue->setValue((int)(ptr->ParamGlWidget->LocalScene.frontcol[2]*255.));
col->transparent->setValue((int)(ptr->ParamGlWidget->LocalScene.frontcol[3]*255.));

 break;
    case 1:
col->red->setValue((int)(ptr->ParamGlWidget->LocalScene.backcol[0]*255.)) ;
col->green->setValue((int)(ptr->ParamGlWidget->LocalScene.backcol[1]*255.)) ;
col->blue->setValue((int)(ptr->ParamGlWidget->LocalScene.backcol[2]*255.));
col->transparent->setValue((int)(ptr->ParamGlWidget->LocalScene.backcol[3]*255.));

 break;
    case 2:
col->red->setValue((int)(ptr->ParamGlWidget->LocalScene.gridcol[0]*255.)) ;
col->green->setValue((int)(ptr->ParamGlWidget->LocalScene.gridcol[1]*255.)) ;
col->blue->setValue((int)(ptr->ParamGlWidget->LocalScene.gridcol[2]*255.));
col->transparent->setValue((int)(ptr->ParamGlWidget->LocalScene.gridcol[3]*255.));

 break;

    case 3:
col->red->setValue((int)(ptr->ParamGlWidget->LocalScene.groundcol[0]*255.)) ;
col->green->setValue((int)(ptr->ParamGlWidget->LocalScene.groundcol[1]*255.)) ;
col->blue->setValue((int)(ptr->ParamGlWidget->LocalScene.groundcol[2]*255.));
col->transparent->setValue((int)(ptr->ParamGlWidget->LocalScene.groundcol[3]*255.));

 break;
     case 4:
col->red->setValue((int)(ptr->ParamGlWidget->LocalScene.condcol[0]*255.)) ;
col->green->setValue((int)(ptr->ParamGlWidget->LocalScene.condcol[1]*255.)) ;
col->blue->setValue((int)(ptr->ParamGlWidget->LocalScene.condcol[2]*255.));
col->transparent->setValue((int)(ptr->ParamGlWidget->LocalScene.condcol[3]*255.));

 break;
 default :  break;
};

} /// End else...
}

//==========================================//
void menubar::transparencecl() {
    /*if(ptr->tabsurf->currentPageIndex() == 1)  {
              ptr->isoWidget->transparence();
              ptr->IsoGlWidget->transparence();}
    else {  ptr->connectWidget2->transparence();
              ptr->ParamGlWidget->transparence();}*/
ptr->ParamGlWidget->transparence();
ptr->IsoGlWidget->transparence();
}

//==========================================//
void menubar::transcl(int cl) {
    if(ptr->tabsurf->currentPageIndex() == 1) {
     ptr->IsoGlWidget->transparency(cl);}
    else {
    ptr->ParamGlWidget->transparency(cl);}
}

//=========================================//
void menubar::bluecl(int cl) {
    if(ptr->tabsurf->currentPageIndex() == 1) {
     ptr->isoWidget->blue(cl);
     ptr->IsoGlWidget->blue(cl);}
    else {
    ptr->connectWidget2->blue(cl);
    ptr->ParamGlWidget->blue(cl);}
}

//========================================//
void menubar::redcl(int cl) {
    if(ptr->tabsurf->currentPageIndex() == 1)  {
    ptr->isoWidget->red(cl);
    ptr->IsoGlWidget->red(cl);}
    else {
    ptr->connectWidget2->red(cl);
    ptr->ParamGlWidget->red(cl);}
}

//=======================================//
void menubar::greencl(int cl) {
    if(ptr->tabsurf->currentPageIndex() == 1)  {
 ptr->isoWidget->green(cl);
 ptr->IsoGlWidget->green(cl);}
    else {
 ptr->connectWidget2->green(cl);
 ptr->ParamGlWidget->green(cl);}
}

//=======================================//
void menubar::tabsurfPageChanged(){
if(col == NULL) {
  QMessageBox message ;
    message.setText("No Color Control...");
    message.adjustSize();
    message.exec();
}
else typecolor(col->color->currentItem ());
};

//======================================//
void menubar::lunchcoloroptions(){
    col = new coloroptions(0, "CO", WDestructiveClose | WStyle_StaysOnTop);
    typecolor(col->color->currentItem ());
    if(ptr->IsoGlWidget->LocalScene.transparency == 1 ||
    ptr->ParamGlWidget->LocalScene.transparency == 1) col->transparence->toggle();
    connect( col->color, SIGNAL( activated(int) ), this, SLOT( typecolor(int) ) );
    connect( col->transparence, SIGNAL( clicked() ), this, SLOT( transparencecl() ) );
    connect( col->blue, SIGNAL( valueChanged(int) ), this, SLOT( bluecl(int) ) );
    connect( col->green, SIGNAL( valueChanged(int) ), this, SLOT( greencl(int) ) );
    connect( col->red, SIGNAL( valueChanged(int) ), this, SLOT( redcl(int) ) );
    connect( col->transparent, SIGNAL( valueChanged(int) ), this, SLOT( transcl(int) ) );
   //connect( ptr->tabsurf,SIGNAL(currentChanged(QWidget*)),this,SLOT(tabsurfPageChanged()));
    col->show();
};
//======================================
//++++++//
menubar::menubar(){
mainmenu = new QMenuBar(ptr);
};
//======================================//
void menubar::menupage(){
PageMenu = new QPopupMenu;
PageMenu->setCheckable(TRUE);

IsosurfaceAction = new QAction(QPixmap(""), "Isosurface", 0, ptr, "Iso" );
IsosurfaceAction->setToggleAction(TRUE);
QObject::connect( IsosurfaceAction, SIGNAL(activated()), this, SLOT(isoShow()));
IsosurfaceAction->addTo(PageMenu);
IsosurfaceAction->setOn(TRUE);
PageMenu->setItemChecked(PageMenu->idAt(0), TRUE);

ParametricAction = new QAction(QPixmap(""), "Parametric", 0, ptr, "Para" );
ParametricAction->setToggleAction(TRUE);
QObject::connect( ParametricAction, SIGNAL(activated()), this, SLOT(paraShow()));
ParametricAction->addTo(PageMenu);
ParametricAction->setOn(TRUE);
PageMenu->setItemChecked(PageMenu->idAt(1), TRUE);

ToolsAction = new QAction(QPixmap(""), "Tools", 0, ptr, "Tools" );
ToolsAction->setToggleAction(TRUE);
QObject::connect( ToolsAction, SIGNAL(activated()), this, SLOT(toolsShow()));
ToolsAction->addTo(PageMenu);
ToolsAction->setOn(TRUE);
PageMenu->setItemChecked(PageMenu->idAt(2), TRUE);

HallAction = new QAction(QPixmap(""), "Hall", 0, ptr, "Hall" );
HallAction->setToggleAction(TRUE);
QObject::connect( HallAction, SIGNAL(activated()), this, SLOT(hallShow()));
HallAction->addTo(PageMenu);
HallAction->setOn(TRUE);
PageMenu->setItemChecked(PageMenu->idAt(3), TRUE);

NDAction = new QAction(QPixmap(""), "ND", 0, ptr, "ND" );
NDAction->setToggleAction(TRUE);
QObject::connect( NDAction, SIGNAL(activated()), this, SLOT(ndShow()));
NDAction->addTo(PageMenu);
NDAction->setOn(TRUE);
PageMenu->setItemChecked(PageMenu->idAt(4), TRUE);

mainmenu->insertItem( "PageView",  PageMenu);

IsosurfaceWidget = ptr->isopage->page(0);
ParametricWidget = ptr->isopage->page(1);
ToolsWidget      = ptr->isopage->page(2);
HallWidget       = ptr->isopage->page(3);
NDWidget         = ptr->isopage->page(4);
};

//======================================//
static int showiso = 1;
void menubar::isoShow(){
showiso  *= -1;
(showiso == 1) ? ptr->isopage->insertTab ( IsosurfaceWidget, "IsoSurface", 0 ):
ptr->isopage->removePage(IsosurfaceWidget);
};

//======================================//
static int showpara = 1;
void menubar::paraShow(){
showpara  *= -1;
(showpara == 1) ? ptr->isopage->insertTab ( ParametricWidget, "Parametric", 1 ):
ptr->isopage->removePage(ParametricWidget);
};

//======================================//
static int showtools = 1;
void menubar::toolsShow(){
showtools  *= -1;
(showtools == 1) ? ptr->isopage->insertTab ( ToolsWidget, "Tools", 2 ):
ptr->isopage->removePage(ToolsWidget);
};

//======================================//
static int showhall = 1;
void menubar::hallShow(){
showhall  *= -1;
(showhall == 1) ? ptr->isopage->insertTab ( HallWidget, "Hall", 3 ):
ptr->isopage->removePage(HallWidget);
};

//======================================//
static int shownd = 1;
void menubar::ndShow(){
shownd  *= -1;
(shownd == 1) ? ptr->isopage->insertTab ( NDWidget, "ND", 4 ):
ptr->isopage->removePage(NDWidget);
};

//======================================//
void menubar::opentestpov(){
    QFile file( "test.pov" );
    if ( file.open( IO_ReadOnly ) ) {
        QTextStream stream( &file );
        QString line;
        editeur * edit = new editeur();
        edit->e->setText(stream.read ());
        edit->show();
        file.close();
    }
}

//======================================//
void menubar::openmeshpov(){
    QFile file( "Mesh.inc" );
    if ( file.open( IO_ReadOnly ) ) {
        QTextStream stream( &file );
        editeur * edit = new editeur();
        edit->e->setText(stream.read ());
        edit->show();
        file.close();
    }
};

//======================================//
void menubar::loadConfig(){
QString line, filename;

if ( QFile::exists("K3DSurfConfig") ) {filename = "K3DSurfConfig";}
else if ( QFile::exists(".K3DSurfConfig") )  { filename = ".K3DSurfConfig";}
else {/*
  QMessageBox message ;
    message.setText("No Config file \".K3DSurfConfig\" or \"K3DSurfConfig\" ");
    message.adjustSize();
    message.exec();*/
    return;
}

QString red, green, blue, trans;
int i;
QFile file(filename);
 if ( file.open( IO_ReadOnly ) ) {
        QTextStream stream( &file );
        while ( !stream.atEnd() ) {
            line = (stream.readLine()).simplifyWhiteSpace(); // line of text excluding '\n'
if (!line.contains("#")) {  //currentfunction = 0;
if (line.contains("ISOMAXPOINTS=")) ptr->isomaxpt->setText(line.remove("ISOMAXPOINTS="));
else if (line.contains("ISOMAXTRIANG=")) ptr->isomaxtr->setText(line.remove("ISOMAXTRIANG="));
else if (line.contains("ISOMAXGRID=")) ptr->isomaxgrid->setText(line.remove("ISOMAXGRID="));

//Isosurfaces Colors:
else if (line.contains("GridIsoColor=")) {
line.remove("GridIsoColor=");
i     = line.find(",");
red   = line.mid(0,i);
line.remove( 0, i+1 );
i     = line.find(",");
green = line.mid(0,i);
line.remove( 0, i+1 );
i     = line.find(",");
blue  = line.mid(0,i);
line.remove( 0, i+1 );
trans = line;
ptr->IsoGlWidget->setGridColor(red.toFloat()/255., green.toFloat()/255., blue.toFloat()/255., trans.toFloat()/255.);
}
else if (line.contains("FrontIsoColor=")) {
line.remove("FrontIsoColor=");
i     = line.find(",");
red   = line.mid(0,i);
line.remove( 0, i+1 );
i     = line.find(",");
green = line.mid(0,i);
line.remove( 0, i+1 );
i     = line.find(",");
blue  = line.mid(0,i);
line.remove( 0, i+1 );
trans = line;
ptr->IsoGlWidget->setFrontColor(red.toFloat()/255., green.toFloat()/255., blue.toFloat()/255., trans.toFloat()/255.);
}
else if (line.contains("BackIsoColor=")) {
line.remove("BackIsoColor=");
i     = line.find(",");
red   = line.mid(0,i);
line.remove( 0, i+1 );
i     = line.find(",");
green = line.mid(0,i);
line.remove( 0, i+1 );
i     = line.find(",");
blue  = line.mid(0,i);
line.remove( 0, i+1 );
trans = line;
ptr->IsoGlWidget->setBackColor(red.toFloat()/255., green.toFloat()/255., blue.toFloat()/255., trans.toFloat()/255.);
}
else if (line.contains("GroundIsoColor=")) {
line.remove("GroundIsoColor=");
i     = line.find(",");
red   = line.mid(0,i);
line.remove( 0, i+1 );
i     = line.find(",");
green = line.mid(0,i);
line.remove( 0, i+1 );
i     = line.find(",");
blue  = line.mid(0,i);
line.remove( 0, i+1 );
trans = line;
ptr->IsoGlWidget->setGroundColor(red.toFloat()/255., green.toFloat()/255., blue.toFloat()/255., trans.toFloat()/255.);
}
//Parametric Surfaces Colors:
else if (line.contains("GridParaColor=")) {
line.remove("GridParaColor=");
i     = line.find(",");
red   = line.mid(0,i);
line.remove( 0, i+1 );
i     = line.find(",");
green = line.mid(0,i);
line.remove( 0, i+1 );
i     = line.find(",");
blue  = line.mid(0,i);
line.remove( 0, i+1 );
trans = line;

ptr->ParamGlWidget->setGridColor(red.toFloat()/255., green.toFloat()/255., blue.toFloat()/255., trans.toFloat()/255.);
}
else if (line.contains("FrontParaColor=")) {
line.remove("FrontParaColor=");
i     = line.find(",");
red   = line.mid(0,i);
line.remove( 0, i+1 );
i     = line.find(",");
green = line.mid(0,i);
line.remove( 0, i+1 );
i     = line.find(",");
blue  = line.mid(0,i);
line.remove( 0, i+1 );
trans = line;
ptr->ParamGlWidget->setFrontColor(red.toFloat()/255., green.toFloat()/255., blue.toFloat()/255., trans.toFloat()/255.);
}
else if (line.contains("BackParaColor=")) {
line.remove("BackParaColor=");
i     = line.find(",");
red   = line.mid(0,i);
line.remove( 0, i+1 );
i     = line.find(",");
green = line.mid(0,i);
line.remove( 0, i+1 );
i     = line.find(",");
blue  = line.mid(0,i);
line.remove( 0, i+1 );
trans = line;
ptr->ParamGlWidget->setBackColor(red.toFloat()/255., green.toFloat()/255., blue.toFloat()/255., trans.toFloat()/255.);
}
else if (line.contains("GroundParaColor=")) {
line.remove("GroundParaColor=");
i     = line.find(",");
red   = line.mid(0,i);
line.remove( 0, i+1 );
i     = line.find(",");
green = line.mid(0,i);
line.remove( 0, i+1 );
i     = line.find(",");
blue  = line.mid(0,i);
line.remove( 0, i+1 );
trans = line;
ptr->ParamGlWidget->setGroundColor(red.toFloat()/255., green.toFloat()/255., blue.toFloat()/255., trans.toFloat()/255.);
}
ptr->IsoGlWidget->update();
}
                      }
     file.close();
      ptr->pushButton71_2_clicked();
      ptr->pushButton71_clicked();
    }
};

//======================================//
void menubar::runpov(){
 PovConfig *pvconfig = new PovConfig(ptr);
 int current_page = ptr->tabsurf->currentPageIndex();
    if(current_page == 0) ptr->ParamGlWidget->RunPovscript(1);
    else ptr->IsoGlWidget->RunPovscript(1);
 pvconfig->runpovray();
};
//======================================
void menubar::povconfig(){
 PovConfig *pvconfig = new PovConfig(ptr);
 pvconfig->connectcontrols();
 pvconfig->show();
}
//======================================
void menubar::SaveConfig(){

QFile file( "K3DSurfConfig" );
   if ( file.open( IO_WriteOnly ) ) {
//file.open( IO_WriteOnly );
QTextStream * stream  = new QTextStream(&file);

*(stream) << "\n\
# Comments start with \"#\"\n";
if(GridAction->isOn() == TRUE) {
*(stream) << "#+++++++++++++++ Points & Triangles ++++++++++++++++\n\
# The values of ISOMAXTRIANG and ISOMAXPOINTS should be between 0 and 10\n\
# ISOMaxPOINTS and ISOMAXTRIANG are expressed in Millions(ie: 0.41 = 410.000 triangles)\n\
# Memory requirements :\n\
# 1 Millions Points    => 88 MegRAM\n\
# 1 Millions Triangles => 50 MegRAM\n\
# Example: ISOMAXPOINTS = 0.42 => 0.42x88 = 36.96 MegRAM\n";
*(stream) << "ISOMAXPOINTS= "+ptr->isomaxpt->text()+"\n";
*(stream) << "ISOMAXTRIANG= "+ptr->isomaxtr->text()+"\n\n";
}
if(PtTrAction->isOn() == TRUE) {
*(stream) << "#+++++++++++++++ Grid ++++++++++++++++\n";
*(stream) << "# ISOMAXGRID is : 4 < ISOMAXGRID < 500\n\
# Grid of 100x100x100  => 61 MegRAM\n\
# Example: ISOMAXGRID = 200 => (200x200x200/100x100x100)*61 = 8*61 = 488 MegRAM\n";
*(stream) << "ISOMAXGRID= "+ptr->isomaxgrid->text()+"\n\n";
 }

// Iso Colors:
*(stream) << "#+++++++++++++++ Colors ++++++++++++++++\n";
*(stream) << "# Colors Values C : 0 < C <255\n\n";
if(IsoFrontColorAction->isOn()  == TRUE) 
*(stream) << "FrontIsoColor= " 
          << (int)(ptr->IsoGlWidget->LocalScene.frontcol[0]*255)  << ", "
          << (int)(ptr->IsoGlWidget->LocalScene.frontcol[1]*255)  << ", "
          << (int)(ptr->IsoGlWidget->LocalScene.frontcol[2]*255)  << ", "
          << (int)(ptr->IsoGlWidget->LocalScene.frontcol[3]*255)  << "\n";
if(IsoBackColorAction->isOn()   == TRUE) 
*(stream) << "BackIsoColor= " 
          << (int)(ptr->IsoGlWidget->LocalScene.backcol[0]*255)  << ", "
          << (int)(ptr->IsoGlWidget->LocalScene.backcol[1]*255)  << ", "
          << (int)(ptr->IsoGlWidget->LocalScene.backcol[2]*255)  << ", "
          << (int)(ptr->IsoGlWidget->LocalScene.backcol[3]*255)  << "\n";
if(IsoGridColorAction->isOn()   == TRUE)
*(stream) << "GridIsoColor= " 
          << (int)(ptr->IsoGlWidget->LocalScene.gridcol[0]*255)  << ", "
          << (int)(ptr->IsoGlWidget->LocalScene.gridcol[1]*255)  << ", "
          << (int)(ptr->IsoGlWidget->LocalScene.gridcol[2]*255)  << ", "
          << (int)(ptr->IsoGlWidget->LocalScene.gridcol[3]*255)  << "\n";
if(IsoGroundColorAction->isOn() == TRUE)
*(stream) << "GroundIsoColor= " 
          << (int)(ptr->IsoGlWidget->LocalScene.groundcol[0]*255) << ", "
          << (int)(ptr->IsoGlWidget->LocalScene.groundcol[1]*255) << ", "
          << (int)(ptr->IsoGlWidget->LocalScene.groundcol[2]*255) << ", "
          << (int)(ptr->IsoGlWidget->LocalScene.groundcol[3]*255) << "\n";
if(IsoCndColorAction->isOn()    == TRUE)
*(stream) << "CndIsoColor= " 
          << (int)(ptr->IsoGlWidget->LocalScene.condcol[0]*255)   << ", "
          << (int)(ptr->IsoGlWidget->LocalScene.condcol[1]*255)   << ", "
          << (int)(ptr->IsoGlWidget->LocalScene.condcol[2]*255)   << ", "
          << (int)(ptr->IsoGlWidget->LocalScene.condcol[3]*255)   << "\n";

// Parametric Colors:
if(ParaFrontColorAction->isOn()  == TRUE) 
*(stream) << "FrontParaColor= " 
          << (int)(ptr->ParamGlWidget->LocalScene.frontcol[0]*255) << ", "
          << (int)(ptr->ParamGlWidget->LocalScene.frontcol[1]*255) << ", "
          << (int)(ptr->ParamGlWidget->LocalScene.frontcol[2]*255) << ", "
          << (int)(ptr->ParamGlWidget->LocalScene.frontcol[3]*255) << "\n";
if(ParaBackColorAction->isOn()   == TRUE) 
*(stream) << "BackParaColor= " 
          << (int)(ptr->ParamGlWidget->LocalScene.backcol[0]*255) << ", "
          << (int)(ptr->ParamGlWidget->LocalScene.backcol[1]*255) << ", "
          << (int)(ptr->ParamGlWidget->LocalScene.backcol[2]*255) << ", "
          << (int)(ptr->ParamGlWidget->LocalScene.backcol[3]*255) << "\n";
if(ParaGridColorAction->isOn()   == TRUE)
*(stream) << "GridParaColor= " 
          << (int)(ptr->ParamGlWidget->LocalScene.gridcol[0]*255) << ", "
          << (int)(ptr->ParamGlWidget->LocalScene.gridcol[1]*255) << ", "
          << (int)(ptr->ParamGlWidget->LocalScene.gridcol[2]*255) << ", "
          << (int)(ptr->ParamGlWidget->LocalScene.gridcol[3]*255) << "\n";
if(ParaGroundColorAction->isOn() == TRUE)
*(stream) << "GroundParaColor= " 
          << (int)(ptr->ParamGlWidget->LocalScene.groundcol[0]*255) << ", "
          << (int)(ptr->ParamGlWidget->LocalScene.groundcol[1]*255) << ", "
          << (int)(ptr->ParamGlWidget->LocalScene.groundcol[2]*255) << ", "
          << (int)(ptr->ParamGlWidget->LocalScene.groundcol[3]*255) << "\n";
if(ParaCndColorAction->isOn()    == TRUE)
*(stream) << "CndParaColor= " 
          << (int)(ptr->ParamGlWidget->LocalScene.condcol[0]*255) << ", "
          << (int)(ptr->ParamGlWidget->LocalScene.condcol[1]*255) << ", "
          << (int)(ptr->ParamGlWidget->LocalScene.condcol[2]*255) << ", "
          << (int)(ptr->ParamGlWidget->LocalScene.condcol[3]*255) << "\n";
file.close();
}
};


//++++++//
menubar::menubar(k3dsurface * pointertowindow, QApplication * ptrapplication){
root = ptrapplication;
ptr = pointertowindow;
mainmenu = new QMenuBar(ptr);
tools    = new QToolBar(ptr, "Tools");
tools->setLabel( ("Tools") );
};

//++++++//
menubar::~menubar(){
delete(mainmenu);
};

//++++++//
void menubar::controlcenter(){
drawingoptions *newpanl = new drawingoptions(0, "CC", WDestructiveClose | WStyle_StaysOnTop);
/// IsoSurface Page :
connect( newpanl->xyzg, SIGNAL( valueChanged(int) ), ptr, SLOT(xyzg_valueChanged(int)));
connect( newpanl->xg, SIGNAL( valueChanged(int) ), ptr, SLOT(xg_valueChanged(int)));
connect( newpanl->yg, SIGNAL( valueChanged(int) ), ptr, SLOT(yg_valueChanged(int)));
connect( newpanl->zg, SIGNAL( valueChanged(int) ), ptr, SLOT(zg_valueChanged(int)));

connect( newpanl->xyzg_2, SIGNAL( valueChanged(int) ), ptr, SLOT(xyzg_2_valueChanged(int)));
connect( newpanl->xg_2, SIGNAL( valueChanged(int) ), ptr, SLOT(xg_2_valueChanged(int)));
connect( newpanl->yg_2, SIGNAL( valueChanged(int) ), ptr, SLOT(yg_2_valueChanged(int)));
connect( newpanl->zg_2, SIGNAL( valueChanged(int) ), ptr, SLOT(zg_2_valueChanged(int)));
connect( newpanl->comboBox18_3, SIGNAL(activated(int) ), ptr, SLOT(comboBox18_3_activated(int)));

/// Parametric Page :
connect( newpanl->cutline, SIGNAL( valueChanged(int) ), ptr, SLOT(cutline_valueChanged(int)));
connect( newpanl->cutcolumn, SIGNAL( valueChanged(int) ), ptr, SLOT(cutcolumn_valueChanged(int)));
connect( newpanl->linecolumn, SIGNAL( valueChanged(int) ), ptr, SLOT(linecolumn_valueChanged(int)));
connect( newpanl->comboBox18_2, SIGNAL(activated(int) ), ptr, SLOT(comboBox18_2_activated(int)));

/// Color/OpenGL :
/*
connect( newpanl->color, SIGNAL( activated(int) ), ptr, SLOT(typecolor(int)));
connect( newpanl->red, SIGNAL( valueChanged(int) ), ptr, SLOT(redcl(int)));
connect( newpanl->green, SIGNAL( valueChanged(int) ), ptr, SLOT(greencl(int)));
connect( newpanl->blue, SIGNAL( valueChanged(int) ), ptr, SLOT(bluecl(int)));
connect( newpanl->transparence, SIGNAL( clicked() ), ptr, SLOT(transparencecl()));
connect( newpanl->transparence, SIGNAL( clicked() ), ptr, SLOT(transparence->toggle()));
*/
connect( newpanl->comboBox18, SIGNAL( activated(int) ), ptr, SLOT(comboBox18_activated(int)));

/// Lunch the Panel :
newpanl->show();
};

//++++++//
void menubar::gotoweb(){
        QDate d = QDate::currentDate();
        editeur * ed = new editeur();
        ed->e->setText("");
        //ed->e->setText(d.toString("ddd MMMM d yyyy"));
        ed->show();
};

//++++++//
void menubar::toolbar(){
    QPixmap openIcon = QPixmap( gedit_xpm );
    QToolButton * fileOpen;
    fileOpen = new QToolButton( openIcon, ("Small Editor"), QString::null,
                           this, SLOT(lunchedit()), tools, "Editor" );


    QPixmap ControlIcon = QPixmap( gear_xpm );
    QToolButton * ControlCenter;
    ControlCenter = new QToolButton( ControlIcon, ("Control Center"), QString::null,
                           this, SLOT(controlcenter()), tools, "ControlCenter" );
    ControlCenter->setTextLabel ("Controls");


    QPixmap SnapshotIcon = QPixmap( snapshot_xpm );
    QToolButton * SnapShot;
    SnapShot    = new QToolButton( SnapshotIcon, ("Control Center"), QString::null,
                           ptr, SLOT(videoplay()), tools, "ControlCenter" );
    SnapShot->setTextLabel ("Image");

    //tools->addSeparator ();
    QPixmap ColorsIcon = QPixmap( graphics_xpm );
    QToolButton * Colors;
    Colors    = new QToolButton( ColorsIcon, ("Colors Options"), QString::null,
                           //this, SLOT(lunchabout()), tools, "Colors Options" );
                           this, SLOT(lunchcoloroptions()), tools, "Colors Options" );
/*
    QPixmap PovIcon = QPixmap( pov_xpm );
    QToolButton * PovShot;
    PovShot    = new QToolButton( PovIcon, ("POV"), QString::null,
                           this, SLOT(lunchabout()), tools, "Colors Options" );
                           //this, SLOT(runpov()), tools, "PovRay" );
*/
};

//+++++++++++  menuabout()  ++++++++++++++//
void menubar::menuabout(){
aboutMenu = new QPopupMenu;
aboutMenu->insertItem("About", this, SLOT(lunchabout()),  0);
mainmenu->insertItem( "About", aboutMenu );
};

//++++++//
void menubar::lunchedit(){
QDateTime d = QDateTime::currentDateTime();
editeur * edit = new editeur();
edit->e->setText("#   Date:"+d.toString("ddd MMMM d yyyy")+"\n#  Time: "+(d.time()).toString("hh:mm:ss"));

edit->e->setText("#################################\n\
#                      K3DSurf Project\n\
#           "+d.toString("ddd MMMM d yyyy")+" ## "+(d.time()).toString("hh:mm:ss")+"\n\
#################################\n");
edit->show();
};

//+++++++++++  menufile()  ++++++++++++++//
void menubar::menupov(){
povMenu = new QPopupMenu;
QPixmap openIcon = QPixmap( fileopen );
QPixmap toolsIcon = QPixmap( tools_xpm );
QPixmap PovIcon = QPixmap( pov_xpm );
povMenu->insertItem(PovIcon, "Run", this, SLOT(runpov()),  Qt::Key_F9);
povMenu->insertItem(openIcon, ("Edit \"test.pov\""), this, SLOT(opentestpov()), 0);
povMenu->insertItem(openIcon, "Edit \"Mesh.inc\"", this, SLOT(openmeshpov()), 0);
povMenu->insertSeparator(3);
povMenu->insertItem(toolsIcon, "POV-Ray Options", this, SLOT(povconfig()), 0);
mainmenu->insertItem( "POV-Ray", povMenu );
};

//+++++++++++  menufile()  ++++++++++++++//
void menubar::menufile(){
fileMenu = new QPopupMenu;
QPixmap openIcon = QPixmap( fileopen );
fileMenu->insertItem("&New", this, SLOT(lunchedit()),  Qt::CTRL+Qt::Key_N);
fileMenu->insertItem(openIcon, ("&Open"), &edit, SLOT(choose()), Qt::CTRL+Qt::Key_O);
fileMenu->insertItem("&Exit", root, SLOT(quit()), Qt::CTRL+Qt::Key_E);
mainmenu->insertItem( "&Project", fileMenu );
};

//+++++++++++  menuinfos()  ++++++++++++++//
void menubar::menuinfos(){
infosMenu = new QPopupMenu;
infosMenu->setCheckable(TRUE);
// Grid:
GridsAction = new QAction(QPixmap(""), "Grig", Qt::CTRL+Qt::Key_S, ptr, "Grid" );
GridsAction->setToggleAction(TRUE);
QObject::connect( GridsAction, SIGNAL(activated()), ptr, SLOT(checkBox240_clicked()));
GridsAction->addTo(infosMenu);
GridsAction->setOn(TRUE);
infosMenu->setItemChecked(infosMenu->idAt(0), TRUE);

// Polys:
PolysAction = new QAction(QPixmap(""), "Polygons", Qt::CTRL+Qt::Key_L, ptr, "Polys" );
PolysAction->setToggleAction(TRUE);
QObject::connect( PolysAction, SIGNAL(activated()), ptr, SLOT(checkBox241_clicked()));
PolysAction->addTo(infosMenu);
PolysAction->setOn(TRUE);
infosMenu->setItemChecked(infosMenu->idAt(1), TRUE);

// Vertices:
VerticeAction = new QAction(QPixmap(""), "Vertices", Qt::CTRL+Qt::Key_P, ptr, "Vert" );
VerticeAction->setToggleAction(TRUE);
QObject::connect( VerticeAction, SIGNAL(activated()), ptr, SLOT(PlanBox_clicked()));
VerticeAction->addTo(infosMenu);
VerticeAction->setOn(TRUE);
infosMenu->setItemChecked(infosMenu->idAt(2), TRUE);
mainmenu->insertItem( "Infos", infosMenu );
};

//+++++++++++  menugl()  ++++++++++++++//
void menubar::menugl(){
fileMenuGL = new QPopupMenu;
fileMenuGL->setCheckable(TRUE);
SmoothPolyAction = new QAction(QPixmap(""), "&Smouth Poly", Qt::CTRL+Qt::Key_S, ptr, "Polys" );
SmoothPolyAction->setToggleAction(TRUE);
QObject::connect( SmoothPolyAction, SIGNAL(activated()), ptr, SLOT(checkBox240_clicked()));
SmoothPolyAction->addTo(fileMenuGL);
SmoothPolyAction->setOn(TRUE);
fileMenuGL->setItemChecked(fileMenuGL->idAt(0), TRUE);

// Smooth Lines:
SmoothLinesAction = new QAction(QPixmap(""), "&Smouth Line", Qt::CTRL+Qt::Key_L, ptr, "Lines" );
SmoothLinesAction->setToggleAction(TRUE);
QObject::connect( SmoothLinesAction, SIGNAL(activated()), ptr,
SLOT(checkBox241_clicked()));
SmoothLinesAction->addTo(fileMenuGL);

// Plan:
PlanAction = new QAction(QPixmap(""), "Draw &Plan", Qt::CTRL+Qt::Key_P, ptr, "Plan" );
PlanAction->setToggleAction(TRUE);
QObject::connect( PlanAction, SIGNAL(activated()), ptr, SLOT(PlanBox_clicked()));
PlanAction->addTo(fileMenuGL);
PlanAction->setOn(TRUE);
fileMenuGL->setItemChecked(fileMenuGL->idAt(2), TRUE);

mainmenu->insertItem( "&OpenGL", fileMenuGL );
};

//+++++++++++  menuconfig()  ++++++++++++++//
void menubar::menuconfig(){
fileMenuConf = new QPopupMenu;
QPixmap openIcon = QPixmap( fileopen );
QPixmap saveIcon = QPixmap( filesave );
fileMenuConf->insertItem(openIcon, "&Open Configure file", ptr, SLOT(OpenConfig()), 0);
fileMenuConf->insertItem("&Load (execute)", this, SLOT(loadConfig()), 0);
fileMenuConf->insertItem(saveIcon, "&Save Config file", this, SLOT(SaveConfig()), 0);
fileMenuConf->insertSeparator(3);

QPopupMenu *fieldMenu    = new QPopupMenu;
// Resolution:
QPopupMenu *ResolutionMenu    = new QPopupMenu;
// All:
AllResoAction = new QAction(QPixmap(""), "Save All", 0, this, "All" );
AllResoAction->setToggleAction(TRUE);

AllResoAction->setOn(TRUE);
AllResoAction->addTo(ResolutionMenu);
ResolutionMenu->insertSeparator(1);

// Max Grid:
GridAction = new QAction(QPixmap(""), "Maximum &Grid ("+ptr->isomaxgrid->text()+")", 0, ptr, "Grid" );
GridAction->setToggleAction(TRUE);
GridAction->setOn(TRUE);
GridAction->addTo(ResolutionMenu);

// Max Triangles and Points:
PtTrAction = new QAction(QPixmap(""), "Maximum Points ("+ptr->isomaxpt->text()+" Millions) And & Triangles ("+ptr->isomaxtr->text()+" Millions)", 0, ptr, "PtTr" );
PtTrAction->setToggleAction(TRUE);
PtTrAction->setOn(TRUE);
PtTrAction->addTo(ResolutionMenu);

fieldMenu->insertItem("Resolution", ResolutionMenu);
QObject::connect(AllResoAction, SIGNAL(toggled(bool)), GridAction, SLOT(setOn(bool)));
QObject::connect(AllResoAction, SIGNAL(toggled(bool)), PtTrAction, SLOT(setOn(bool)));

// Colors:
QPopupMenu *colorMenu    = new QPopupMenu;

// All:
AllColorAction = new QAction(QPixmap(""), "Save All", 0, this, "AllColor" );
AllColorAction->setToggleAction(TRUE);
AllColorAction->setOn(TRUE);
AllColorAction->addTo(colorMenu);
colorMenu->insertSeparator(1);

// Isosurfaces:
IsoFrontColorAction = new QAction(QPixmap(""), "&Isosurfaces Front Colors", 0, this, "IsoFrontColor" );
IsoFrontColorAction->setToggleAction(TRUE);
IsoFrontColorAction->setOn(TRUE);
IsoFrontColorAction->addTo(colorMenu);

IsoBackColorAction = new QAction(QPixmap(""), "&Isosurfaces  Back Colors", 0, this, "IsoBackColor" );
IsoBackColorAction->setToggleAction(TRUE);
IsoBackColorAction->setOn(TRUE);
IsoBackColorAction->addTo(colorMenu);

IsoGridColorAction = new QAction(QPixmap(""), "&Isosurfaces Grid Colors", 0, this, "IsoGridColor" );
IsoGridColorAction->setToggleAction(TRUE);
IsoGridColorAction->setOn(TRUE);
IsoGridColorAction->addTo(colorMenu);

IsoGroundColorAction = new QAction(QPixmap(""), "&Isosurfaces Ground Colors", 0, this, "IsoGroundColor" );
IsoGroundColorAction->setToggleAction(TRUE);
IsoGroundColorAction->setOn(TRUE);
IsoGroundColorAction->addTo(colorMenu);

IsoCndColorAction = new QAction(QPixmap(""), "&Isosurfaces Cnd Colors", 0, this, "IsoCndColor" );
IsoCndColorAction->setToggleAction(TRUE);
IsoCndColorAction->setOn(TRUE);
IsoCndColorAction->addTo(colorMenu);


//Parametric:
ParaFrontColorAction = new QAction(QPixmap(""), "&Parasurfaces Front Colors", 0, this, "ParaFrontColor" );
ParaFrontColorAction->setToggleAction(TRUE);
ParaFrontColorAction->setOn(TRUE);
ParaFrontColorAction->addTo(colorMenu);

ParaBackColorAction = new QAction(QPixmap(""), "&Parasurfaces  Back Colors", 0, this, "ParaBackColor" );
ParaBackColorAction->setToggleAction(TRUE);
ParaBackColorAction->setOn(TRUE);
ParaBackColorAction->addTo(colorMenu);

ParaGridColorAction = new QAction(QPixmap(""), "&Parasurfaces Grid Colors", 0, this, "ParaGridColor" );
ParaGridColorAction->setToggleAction(TRUE);
ParaGridColorAction->setOn(TRUE);
ParaGridColorAction->addTo(colorMenu);

ParaGroundColorAction = new QAction(QPixmap(""), "&Parasurfaces Ground Colors", 0, this, "ParaGroundColor" );
ParaGroundColorAction->setToggleAction(TRUE);
ParaGroundColorAction->setOn(TRUE);
ParaGroundColorAction->addTo(colorMenu);

ParaCndColorAction = new QAction(QPixmap(""), "&Parasurfaces Cnd Colors", 0, this, "ParaCndColor" );
ParaCndColorAction->setToggleAction(TRUE);
ParaCndColorAction->setOn(TRUE);
ParaCndColorAction->addTo(colorMenu);


fieldMenu->insertSeparator(2);
fieldMenu->insertItem("Colors", colorMenu);
fileMenuConf->insertItem("&Fields To Save", fieldMenu);

QObject::connect( AllColorAction, SIGNAL(toggled(bool)), IsoFrontColorAction,  SLOT(setOn(bool)));
QObject::connect( AllColorAction, SIGNAL(toggled(bool)), IsoBackColorAction,  SLOT(setOn(bool)));
QObject::connect( AllColorAction, SIGNAL(toggled(bool)), IsoGridColorAction,  SLOT(setOn(bool)));
QObject::connect( AllColorAction, SIGNAL(toggled(bool)), IsoGroundColorAction,  SLOT(setOn(bool)));
QObject::connect( AllColorAction, SIGNAL(toggled(bool)), IsoCndColorAction,  SLOT(setOn(bool)));

QObject::connect( AllColorAction, SIGNAL(toggled(bool)), ParaFrontColorAction,  SLOT(setOn(bool)));
QObject::connect( AllColorAction, SIGNAL(toggled(bool)), ParaBackColorAction,  SLOT(setOn(bool)));
QObject::connect( AllColorAction, SIGNAL(toggled(bool)), ParaGridColorAction,  SLOT(setOn(bool)));
QObject::connect( AllColorAction, SIGNAL(toggled(bool)), ParaGroundColorAction,  SLOT(setOn(bool)));
QObject::connect( AllColorAction, SIGNAL(toggled(bool)), ParaCndColorAction,  SLOT(setOn(bool)));

mainmenu->insertItem( "&Config", fileMenuConf );
};



void menubar::constructmenubar(){
menufile();
menugl();
menuconfig();
menupov();
menupage();
menuabout();
toolbar();
};

void menubar::activateallcolor(){

};
