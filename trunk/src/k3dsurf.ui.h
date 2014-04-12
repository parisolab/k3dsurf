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
 *   You should have received a cop::y of the GNU General Public License   *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor,Boston, MA 02110-1301 USA             *
 ***************************************************************************/

 
#include <qmainwindow.h>
#include <qtabwidget.h>
#include <qwidget.h>
#include <qgroupbox.h>
#include <qlayout.h>
#include <qfile.h>
#include <qfiledialog.h>
#include <iostream>
#include <qlineedit.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <qpushbutton.h>
#include <qlistview.h>
#include <qspinbox.h>
#include <qcombobox.h>
#include <qheader.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qevent.h>
#include <qmessagebox.h>
#include <qscrollbar.h>
#include <qstatusbar.h>
#include <qcheckbox.h>
#include <qmovie.h>

#include "GlWindow.h"
#include "newwindow2.h"
#include "IsoWindow.h"
//#include "drawingoptions.h"
#include "ParisoMathObject.h"
#include "videoplayer.h"
#include "PovConfig.h"

int xyzactivated = 1;
int  smooth_triangle =1, mesh_parametric =1, 

     continu = -1, drawvista = -1, 
     
     implicite_fct = -1, parametrique_ok = 1,
     fourdimshapes = -1, fivedimshapes = -1, sixdimshapes = -1,
     separatecheckogjects = -1, tria_nas = -1, inverse_condition = -1,
     activate_cd = -1, activate_isocd = -1, activate_supershape = -1, add_condition = -1 , condition_mesh = 1,
     draw_poly_normals = -1, activate_tools = -1, axechoice = 1, objfile_triangle = -1, isomesh =-1, activateiso = -1, inverse_isocondition = -1;

int spheric_fct = -1, cylindric_fct = -1;
int implicit_param = 1, implicit_spheric = -1, implicit_cylindric = -1;
int NbStep =30;
int paramwidgetstack = 1, isowidgetstack =1;
QString     xterm="", 
            Width="+W400", Height="+H400", 
            Start_RowEdit="", End_RowEdit="", 
            Start_ColumnEdit="", End_ColumnEdit="", 
            Test_Abort_CountEdit="X50",
            Pause_When_Done = "+P",
            Continue ="", 
            Output_File_NameEdit="+Oscene", FileExtension=".tga  +FT ",
            Input_File_NameEdit="+Itest.pov",
            OutPutBuffer="", IncludeHeaderFile="", LibraryPath="";
ParisoMathObject RootObjet;
Iso3D   * IndependantIsoObjet;/// = new Iso3D();

///+++++++++++++++++++++++++++++///
void k3dsurface::Axes_center() {
//if(activateiso == 1) isoWidget->Axes_center();
    if(tabsurf->currentPageIndex() == 1) isoWidget->Axes_center();
    else connectWidget2->Axes_center();
}
///+++++++++++++++++++++++++++++///
void k3dsurface::Axes_draw() {
//if(activateiso == 1) isoWidget->Axes_draw();

 if(tabsurf->currentPageIndex() == 1)  isoWidget->Axes_draw();
else connectWidget2->Axes_draw();
}

///+++++++++++++++++++++++++++++///
void k3dsurface::Axes_width (int cl) {
//if(activateiso == 1) isoWidget->Axes_width(cl);
    if(tabsurf->currentPageIndex() == 1)  isoWidget->Axes_width(cl);
    else connectWidget2->Axes_width(cl);
}

///+++++++++++++++++++++++++++++///
void k3dsurface::Axes_size (int cl) {
    if(tabsurf->currentPageIndex() == 1) isoWidget->Axes_size(cl);
    else connectWidget2->Axes_size(cl);
}


///+++++++++++++++++++++++++++++///

void k3dsurface::iso_Fct_activated(){
activateiso *= -1;
}

//====================================

void k3dsurface::iso_mesh()
{
 isomesh *=-1; ///To use for deactivating some components in the interface
 isoWidget->IsoObjet->IsoMesh*= -1;
 IsoGlWidget->meshOk();

/// Update Iso page :
    IsoPageUpdate();
}
//====================================

void k3dsurface::iso_infos()
{
 isoWidget->IsoObjet->IsoInfos*= -1;
 IsoGlWidget->infosOk();
/// Update Iso page :
    IsoPageUpdate();

}
//====================================

void k3dsurface::trianglemesh_clicked()
{
objfile_triangle *= -1;
}
//====================================
void k3dsurface::axex_choice(){
 axechoice = 0;
}
//====================================
void k3dsurface::axey_choice(){
 axechoice = 1;
}
//====================================
void k3dsurface::axez_choice(){
 axechoice = 2;
}
//====================================
/*
void k3dsurface::Draw_Normals(){

    draw_poly_normals *= -1;
     connectWidget2->objet->draw_poly_normals = draw_poly_normals;
    connectWidget2->update();

}
*/
//====================================

void k3dsurface::addcondt(){
     add_condition*= -1;
     connectWidget2->objet->draw_hidden_poly_and_nonhidden = add_condition;
    connectWidget2->update();
}

//====================================

void k3dsurface::meshcondt(){
    condition_mesh *= -1;
    connectWidget2->objet->draw_cond_mesh = condition_mesh;
}

//====================================

void k3dsurface::inverse_cond(){

    inverse_condition  *= -1;
    if(inverse_condition  == 1) 
 connectWidget2->objet->condition_expression = QString("("+condition->text()+") = 0");
    else  connectWidget2->objet->condition_expression  = condition->text();

    perform();
   //connectWidget2->update();
}
//====================================

void k3dsurface::inverse_isocond(){

    inverse_isocondition  *= -1;
    if(inverse_isocondition  == 1) 
    isoWidget->IsoObjet->IsoCondition = QString("("+Isocondition->text()+") = 0");
    else  isoWidget->IsoObjet->IsoCondition  = Isocondition->text();

    PerformNewImplicitFunct();
}
//====================================
void k3dsurface::activate_cond(){
QMessageBox     message;
        if( paramwidgetstack == 1)
    { 
    message.setText(tr(QString("Not yet supported by the OpenGL viewer\n Turn OFF OpenGL to see the result")));
    message.adjustSize () ;
    message.exec();
    activ_cond->toggle();
    return ;
    }

    activate_cd *= -1;
    if(activate_cd == 1) {
      groupBox25_2->setEnabled(TRUE);
      condition->setEnabled(TRUE);
      inverse_condt->setEnabled(TRUE);
       connectWidget2->objet->there_is_condition *= -1;
           if(inverse_condition  == 1) 
 connectWidget2->objet->condition_expression = QString("("+condition->text()+") = 0");
    else  connectWidget2->objet->condition_expression  = condition->text();
    }
    else {
       groupBox25_2->setEnabled(FALSE);
       //condition->setEnabled(FALSE);
       //inverse_condt->setEnabled(FALSE);
       connectWidget2->objet->there_is_condition *= -1; 
    }
    perform();
    //connectWidget2->update();
}
//====================================
void k3dsurface::activate_isocond(){
   /*  QMessageBox     message;

        if( isowidgetstack == 1)
    {
    message.setText(tr(QString("Not yet supported by the OpenGL viewer\n Turn OFF OpenGL to see the result")));
    message.adjustSize () ;
    message.exec();
    Isoactiv_cond->toggle();
    return ;
    }
   */
    activate_isocd *= -1;
    if(activate_isocd == 1) {
       IsogroupBox->setEnabled(TRUE);
       Isocondition->setEnabled(TRUE); /// TO FORCE ENABLE!!!
       //cndmesh_2->setEnabled(TRUE); /// TO FORCE ENABLE!!!
       isoWidget->IsoObjet->IsoConditionRequired *= -1;
       IsoGlWidget->conditionok();
       isoWidget->IsoObjet->IsoCondition = Isocondition->text();
    }
    else {
       //Isocondition->setEnabled(FALSE);
       IsogroupBox->setEnabled(FALSE);
       isoWidget->IsoObjet->IsoConditionRequired *= -1;
       IsoGlWidget->conditionok();
    }
    PerformNewImplicitFunct();
}
//========================================
void k3dsurface::activate_frame(){
/*
QMessageBox message ;
QDir dir(Input_Dir_NameEdit->text());
if( !dir.exists()) {
    message.setText(tr(QString(Input_Dir_NameEdit->text()+" Directory doesn't exists. \
    Create it or chose another one. ")));
    message.adjustSize () ;
    message.exec();
    return;
}

connectWidget2->frames_ok *= -1;
connectWidget2->counter = 0;
if(connectWidget2->frames_ok == 1) {
frames->setText("Frames :\n Stop");
}
else frames->setText("Frames :\n Start");
*/
}
//====================================
void k3dsurface::sixdimshape_activate()
{
sixdimshapes *= -1;
if(sixdimshapes == 1) {
scft_5->setEnabled(TRUE);
sfct_5->setEnabled(TRUE);
rotational6d->setEnabled(TRUE);
connectWidget2->objet->sixdimshapes = 1;
}
else {
scft_5->setEnabled(FALSE);
sfct_5->setEnabled(FALSE);
rotational6d->setEnabled(FALSE);
connectWidget2->objet->sixdimshapes = -1;
}
perform_fivedim();
}

//========================================//
//
// Handles mouse move events for the connect widget.
//

void k3dsurface::keyPressEvent ( QKeyEvent * e ) {

///std::cout << e->text();
connectWidget2->objet->keyboard = e->text();
connectWidget2->update();
}


//====================================

void k3dsurface::videorecord(){
/*
    connectWidget2->video_ok *= -1;
    if(connectWidget2->video_ok == 1) video->setText("Video: \n Stop");
    else  video->setText("Video: \n Start");
    connectWidget2->videorecord();
*/
}
//======================================
void k3dsurface::videoplay(){
QImage buf;
 int current_pag = tabsurf->currentPageIndex();
    if(current_pag == 0) buf = ParamGlWidget->Copyscreenshot();
    else if (current_pag == 1) buf = IsoGlWidget->Copyscreenshot();
 videoplayer *player = new videoplayer(buf);
 player->connectcontrols();
 player->show();

}

//====================================
void k3dsurface::loadPov()
{
        editeur *ed = new editeur();
        ed->load("test.pov");
        ed->show();
}
//====================================

void k3dsurface::separateCheckBoxtoggled(){

    separatecheckogjects *= -1;
   if(separatecheckogjects == 1) {
   groupobjects->setEnabled(TRUE);
   firstobj->setEnabled(TRUE) ; //don't know whay it doesn't enable automaticly...
   secondobj->setEnabled(TRUE); //don't know whay it doesn't enable automaticly...


   if(activate_cd == 1) {
      activ_cond->toggle();
      condition->setEnabled(FALSE);
      inverse_condt->setEnabled(FALSE);
       connectWidget2->objet->there_is_condition *= -1;
       activate_cd = -1;
   }

   }
   else groupobjects->setEnabled(FALSE);

   connectWidget2->objet->two_separate_objects *= -1;
   connectWidget2->valueChanged(); 
}
//====================================
void k3dsurface::firstobjtoggled(){

    connectWidget2->objet->change_first_object *= -1;
    if(connectWidget2->objet->change_first_object == 1) {
    connectWidget2->objet->mat = connectWidget2->objet->mat_first_obj;
    connectWidget2->objet->mat_rotation_save = connectWidget2->objet->mat_rotation_first_save;
    }
    else {
    connectWidget2->objet->mat_first_obj           = connectWidget2->objet->mat;
    connectWidget2->objet->mat_rotation_first_save = connectWidget2->objet->mat_rotation_save;
    }
}
//====================================
void k3dsurface::secondobjtoggled(){

    connectWidget2->objet->change_second_object *= -1;
    if(connectWidget2->objet->change_second_object == 1) {
    connectWidget2->objet->mat               = connectWidget2->objet->mat_second_obj;
    connectWidget2->objet->mat_rotation_save = connectWidget2->objet->mat_rotation_second_save;
    }
    else {
    connectWidget2->objet->mat_second_obj           = connectWidget2->objet->mat;
    connectWidget2->objet->mat_rotation_second_save = connectWidget2->objet->mat_rotation_save;
    }

};
//====================================

void k3dsurface::resizeEvent( QResizeEvent  *e ) {
 ///For Windows
 if (connectWidget2->anim5_ok != 1 && connectWidget2->anim4_ok != 1 &&
 connectWidget2->anim_ok != 1 && connectWidget2->morph_ok != 1) {
  QSize qs = e->size();QSize qsold = e->oldSize();
  double ancien_hauteur = (double)connectWidget2->objet->demi_hauteur;
  double ancien_largeur = (double)connectWidget2->objet->demi_largeur;
  if(qs.width() > 365) {
   connectWidget2->width  = isoWidget->width  = (qs.width() - 355);
   connectWidget2->height = isoWidget->height  = (qs.height() - 100);

   connectWidget2->setFixedSize (qs.width() - 355, qs.height() - 100);
   isoWidget->setFixedSize (qs.width() - 355, qs.height() - 100);

   ParamGlWidget->setFixedSize (qs.width() - 355, qs.height() - 100);
   IsoGlWidget->setFixedSize (qs.width() - 355, qs.height() - 100);

   ParaWidgetStack->setFixedSize (qs.width() - 355, qs.height() - 100);
   IsoWidgetStack->setFixedSize (qs.width() - 355, qs.height() - 100);

   delete connectWidget2->pixmap;
   delete isoWidget->pixmap;

   connectWidget2->pixmap = new QPixmap(qs.width()- 355, qs.height() - 100);
   isoWidget->pixmap = new QPixmap(qs.width()- 355, qs.height() - 100);

   connectWidget2->objet->demi_hauteur = (qs.width() -355)/2;
   connectWidget2->objet->demi_largeur = (qs.height() - 100)/2;
   isoWidget->IsoObjet->demi_hauteur = (qs.width() -355)/2;
   isoWidget->IsoObjet->demi_largeur = (qs.height() - 100)/2;

/// Parametric Window
   if(connectWidget2->objet->demi_hauteur < connectWidget2->objet->demi_largeur)
     connectWidget2->objet->coefficient = connectWidget2->objet->demi_hauteur/(double)ancien_hauteur;
   else connectWidget2->objet->coefficient = connectWidget2->objet->demi_largeur/(double)ancien_largeur;
   connectWidget2->objet->fct_bouton_droit3();

/// Iso Window
   if(isoWidget->IsoObjet->demi_hauteur < isoWidget->IsoObjet->demi_largeur)
     isoWidget->IsoObjet->ScalCoeff = isoWidget->IsoObjet->demi_hauteur/(double)ancien_hauteur;
   else isoWidget->IsoObjet->ScalCoeff = isoWidget->IsoObjet->demi_largeur/(double)ancien_largeur;
   isoWidget->IsoObjet->ScaleIsoMap();

/// OpenGL Window
   if(isoWidget->IsoObjet->demi_hauteur < isoWidget->IsoObjet->demi_largeur)
     ParamGlWidget->scalcoeff(isoWidget->IsoObjet->demi_hauteur/(double)ancien_hauteur);
   else ParamGlWidget->scalcoeff(isoWidget->IsoObjet->demi_largeur/(double)ancien_largeur);

   if(isoWidget->IsoObjet->demi_hauteur < isoWidget->IsoObjet->demi_largeur)
     IsoGlWidget->scalcoeff(isoWidget->IsoObjet->demi_hauteur/(double)ancien_hauteur);
   else IsoGlWidget->scalcoeff(isoWidget->IsoObjet->demi_largeur/(double)ancien_largeur);
   }
 }
else {
    QMessageBox message ;
    message.setText(tr(QString("Stop Anim/Morph before Resizing")));
    message.adjustSize () ;
    message.exec();
        return ;
    update();
     }
};


//====================================

void k3dsurface::File_Extension_Changed(int choice){
switch(choice) {
case 0 : FileExtension = ".tga  +FC"; break;
case 1 : FileExtension = ".png  +FN8"; break;
case 2 : FileExtension = ".ppm  +FP"; break;
case 3 : FileExtension = ".ss  +FS"; break;
case 4 : FileExtension = ".tga  +FT"; break;
}
}



//====================================
void k3dsurface::AnimIso(){
  int current_pag = tabsurf->currentPageIndex();

  if(current_pag != 1) tabsurf->setCurrentPage(1);

  if( isowidgetstack != 1)   ParaWidgetStack->raiseWidget ( 0 );     
      IsoGlWidget->anim();
}
//====================================
void k3dsurface::anim_verify_rot4d(){
int current_pag = tabsurf->currentPageIndex();
  if(connectWidget2->anim4_ok == 1)  anim->toggle();

  if(current_pag != 0) tabsurf->setCurrentPage(0);

  if( paramwidgetstack == 1)   ParamGlWidget->anim();
  else  connectWidget2->anim();
}

//====================================
void k3dsurface::morph_verify_rot4d(){
int current_pag = tabsurf->currentPageIndex();
  if(connectWidget2->anim4_ok == 1)  morph->toggle();

  if(current_pag != 0) tabsurf->setCurrentPage(0);

  if(paramwidgetstack == 1) {
connectWidget2->objet->SpecialMorph_2(ParamGlWidget->LocalScene.ArrayNorVer_localPt, ParamGlWidget->PolyIndices_local, ParamGlWidget->NbPolygnNbVertex, NbStep);
ParamGlWidget->PolyNumber = connectWidget2->objet->NbPolygn;
ParamGlWidget->InitGlMorph();
ParamGlWidget->morph();
}
  else  connectWidget2->morph();
}

//====================================
void k3dsurface::IsoMorph(){
 int current_pag = tabsurf->currentPageIndex();
  if(current_pag != 1) tabsurf->setCurrentPage(1);
  if( isowidgetstack != 1) IsoWidgetStack->raiseWidget ( 0 );
  if(IsoGlWidget->LocalScene.isobox == 1) {
  isobox->toggle();
  IsoGlWidget->isoboxOk();
  UpdateActivatedWin();
  }
isoWidget->IsoObjet->SpecialMorph_2(
               IsoGlWidget->LocalScene.ArrayNorVer_localPt,
               IsoGlWidget->PolyIndices_local,
               IsoGlWidget->NbPolygnNbVertex,
               IsoGlWidget->TypeIsoSurfaceTriangleListeCND,
               &(IsoGlWidget->VertexNumber),
               NbStep,
               IsoGlWidget->LocalScene.PolyIndices_localPtMin,
               &(IsoGlWidget->LocalScene.NbPolygnNbVertexPtMin));
   IsoGlWidget->PolyNumber = connectWidget2->objet->NbPolygn;
   IsoGlWidget->InitGlMorph();  
   IsoGlWidget->morph();

}
//====================================
void k3dsurface::animxy_verify_rot3d(){
if(connectWidget2->anim_ok == 1 || connectWidget2->morph_ok == 1)  xybox->toggle();
}

//====================================
void k3dsurface::animxz_verify_rot3d(){
if(connectWidget2->anim_ok == 1 || connectWidget2->morph_ok == 1)  xzbox->toggle();
}

//====================================
void k3dsurface::animyz_verify_rot3d(){
if(connectWidget2->anim_ok == 1 || connectWidget2->morph_ok == 1)  yzbox->toggle();
}

//====================================
void k3dsurface::animxw_verify_rot3d(){
if(connectWidget2->anim_ok == 1 || connectWidget2->morph_ok == 1)  xwbox->toggle();
}

//====================================
void k3dsurface::animyw_verify_rot3d(){
if(connectWidget2->anim_ok == 1 || connectWidget2->morph_ok == 1)  ywbox->toggle();
}

//====================================
void k3dsurface::animzw_verify_rot3d(){
if(connectWidget2->anim_ok == 1 || connectWidget2->morph_ok == 1)  zwbox->toggle();
}

//====================================
void k3dsurface::newdrawwindow(){

    if(paramwidgetstack == -1) {

newwindow2 * nouvellefenetre = new newwindow2();
*(nouvellefenetre->newwindow->objet) = *(connectWidget2->objet);
nouvellefenetre->newwindow->objet->independantwindow = 1; // to show message h= help
nouvellefenetre->show();

if(connectWidget2->anim_ok == 1 || connectWidget2->morph_ok == 1){
nouvellefenetre->newwindow->anim_ok = connectWidget2->anim_ok ;
nouvellefenetre->newwindow->morph_ok = connectWidget2->morph_ok ;
nouvellefenetre->newwindow->start();
}
else if(connectWidget2->anim4_ok == 1 ) {
         nouvellefenetre->newwindow->anim4_ok = 1;
         nouvellefenetre->newwindow->start();
                                        }
     else if(connectWidget2->anim5_ok == 1 ) {
         nouvellefenetre->newwindow->anim5_ok = 1;
         nouvellefenetre->newwindow->start();
                                        };
 }  /// End of if(current_pag == 0)
    else  {
GlWindow *NewGlWindow = new GlWindow(0, "CO", WDestructiveClose | WStyle_StaysOnTop);

NewGlWindow->glWidget->PolyNumber = ParamGlWidget->PolyNumber ;
NewGlWindow->glWidget->LocalScene = ParamGlWidget->LocalScene;
NewGlWindow->glWidget->LocalScene.infos = -1;

/// Copy in one pass :
memcpy(NewGlWindow->glWidget->LocalScene.ArrayNorVer_localPt ,
             ParamGlWidget->LocalScene.ArrayNorVer_localPt ,
             6*100000*sizeof(GLfloat));
memcpy(NewGlWindow->glWidget->PolyIndices_local,
             ParamGlWidget->PolyIndices_local,
             3*200000*sizeof(GLuint));
memcpy(NewGlWindow->glWidget->LocalScene.PolyIndices_localPtMin,
             ParamGlWidget->LocalScene.PolyIndices_localPtMin,
             3*200000*sizeof(GLuint));
memcpy(NewGlWindow->glWidget->NbPolygnNbVertex,
             ParamGlWidget->NbPolygnNbVertex,
             100*sizeof(GLuint));

NewGlWindow->show();
    }
}

//====================================
void k3dsurface::isodrawwindow(){
int   MaximumNumberPoints     = IsoGlWidget->MaximumNumberPoints,
      MaximumNumberTriangles = IsoGlWidget->MaximumNumberTriangles;

GlWindow *NewGlWindow = new GlWindow(0, "IsoWin", WDestructiveClose | WStyle_StaysOnTop);
NewGlWindow->glWidget->PolyNumber = IsoGlWidget->PolyNumber ;
//NewGlWindow->glWidget->LocalScene = IsoGlWidget->LocalScene;

    NewGlWindow->glWidget->LocalScene.border     = IsoGlWidget->LocalScene.border;
    NewGlWindow->glWidget->LocalScene.cndmesh    = IsoGlWidget->LocalScene.cndmesh;
    NewGlWindow->glWidget->LocalScene.drawcnd    = IsoGlWidget->LocalScene.drawcnd;
    NewGlWindow->glWidget->LocalScene.mesh       = IsoGlWidget->LocalScene.mesh;
    NewGlWindow->glWidget->LocalScene.line       = IsoGlWidget->LocalScene.line;
    NewGlWindow->glWidget->LocalScene.infos      = IsoGlWidget->LocalScene.infos;
    NewGlWindow->glWidget->LocalScene.axe        = IsoGlWidget->LocalScene.axe;
    NewGlWindow->glWidget->LocalScene.box        = IsoGlWidget->LocalScene.box;
    NewGlWindow->glWidget->LocalScene.isobox     = IsoGlWidget->LocalScene.isobox;
    NewGlWindow->glWidget->LocalScene.typedrawing= IsoGlWidget->LocalScene.typedrawing;
    NewGlWindow->glWidget->LocalScene.smoothpoly = IsoGlWidget->LocalScene.smoothpoly;
    NewGlWindow->glWidget->LocalScene.smoothline = IsoGlWidget->LocalScene.smoothline;
    NewGlWindow->glWidget->LocalScene.anim       = IsoGlWidget->LocalScene.anim;
    NewGlWindow->glWidget->LocalScene.morph      = IsoGlWidget->LocalScene.morph;
    NewGlWindow->glWidget->LocalScene.norm       = IsoGlWidget->LocalScene.norm;
    NewGlWindow->glWidget->LocalScene.plan       = IsoGlWidget->LocalScene.plan;
    NewGlWindow->glWidget->LocalScene.front      = IsoGlWidget->LocalScene.front;
    NewGlWindow->glWidget->LocalScene.back       = IsoGlWidget->LocalScene.back;
    NewGlWindow->glWidget->LocalScene.condition  = IsoGlWidget->LocalScene.condition;
memcpy(NewGlWindow->glWidget->LocalScene.frontcol,
             IsoGlWidget->LocalScene.frontcol,
             4*sizeof(GLfloat));
memcpy(NewGlWindow->glWidget->LocalScene.backcol,
             IsoGlWidget->LocalScene.backcol,
             4*sizeof(GLfloat));
memcpy(NewGlWindow->glWidget->LocalScene.gridcol,
             IsoGlWidget->LocalScene.gridcol,
             4*sizeof(GLfloat));
memcpy(NewGlWindow->glWidget->LocalScene.groundcol,
             IsoGlWidget->LocalScene.groundcol,
             4*sizeof(GLfloat));
memcpy(NewGlWindow->glWidget->LocalScene.condcol,
             IsoGlWidget->LocalScene.condcol,
             4*sizeof(GLfloat));
    //NewGlWindow->glWidget->LocalScene = IsoGlWidget->LocalScene;

    NewGlWindow->glWidget->LocalScene.NbPolygnNbVertexPtMin = IsoGlWidget->LocalScene.NbPolygnNbVertexPtMin;

    NewGlWindow->glWidget->LocalScene.infos = -1;

    delete (NewGlWindow->glWidget->LocalScene.ArrayNorVer_localPt);
    delete (NewGlWindow->glWidget->PolyIndices_local);
    delete (NewGlWindow->glWidget->LocalScene.PolyIndices_localPtMin);
    delete (NewGlWindow->glWidget->TypeIsoSurfaceTriangleListeCND);

    NewGlWindow->glWidget->LocalScene.ArrayNorVer_localPt = new GLfloat[6*MaximumNumberPoints];
    NewGlWindow->glWidget->LocalScene.PolyIndices_localPt =
    NewGlWindow->glWidget->PolyIndices_local              = new GLuint [3*MaximumNumberTriangles];
    NewGlWindow->glWidget->LocalScene.PolyIndices_localPtMin  = new GLuint [3*MaximumNumberTriangles];
    NewGlWindow->glWidget->TypeIsoSurfaceTriangleListeCND     = new int [MaximumNumberTriangles];

/// Copy in one pass :
memcpy(NewGlWindow->glWidget->LocalScene.ArrayNorVer_localPt,
             IsoGlWidget->LocalScene.ArrayNorVer_localPt,
             6*MaximumNumberPoints*sizeof(GLfloat));
memcpy(NewGlWindow->glWidget->LocalScene.PolyIndices_localPt,
             IsoGlWidget->LocalScene.PolyIndices_localPt,
             3*MaximumNumberTriangles*sizeof(GLuint));
memcpy(NewGlWindow->glWidget->LocalScene.PolyIndices_localPtMin,
             IsoGlWidget->LocalScene.PolyIndices_localPtMin,
             3*MaximumNumberTriangles*sizeof(GLuint));
memcpy(NewGlWindow->glWidget->TypeIsoSurfaceTriangleListeCND,
             IsoGlWidget->TypeIsoSurfaceTriangleListeCND,
             MaximumNumberTriangles*sizeof(int));
memcpy(NewGlWindow->glWidget->NbPolygnNbVertex,
             IsoGlWidget->NbPolygnNbVertex,
             100*sizeof(GLuint));

if(IsoGlWidget->LocalScene.condition == 1){
int border,verifycnd;
border = NewGlWindow->glWidget->LocalScene.PolyNumberBorderCND = IsoGlWidget->LocalScene.PolyNumberBorderCND;

verifycnd = NewGlWindow->glWidget->LocalScene.PolyNumberVerifyCND = IsoGlWidget->LocalScene.PolyNumberVerifyCND;

NewGlWindow->glWidget->LocalScene.PolyNumberNotVerifyCND = IsoGlWidget->LocalScene.PolyNumberNotVerifyCND;

NewGlWindow->glWidget->LocalScene.PolyIndices_localBorderCND = &NewGlWindow->glWidget->LocalScene.PolyIndices_localPt[0];
NewGlWindow->glWidget->LocalScene.PolyIndices_localVerifyCND = &NewGlWindow->glWidget->LocalScene.PolyIndices_localPt[border];
NewGlWindow->glWidget->LocalScene.PolyIndices_localNotVerifyCND = &NewGlWindow->glWidget->LocalScene.PolyIndices_localPt[border+verifycnd];
}

NewGlWindow->show();
}

///====================================
void k3dsurface::NewIsoDrawWindow(){
IsoWindow * newisowin = new IsoWindow();
*(newisowin->isoWidget->IsoObjet) = *(isoWidget->IsoObjet);
newisowin->show();
/*
if(connectWidget2->anim_ok == 1 || connectWidget2->morph_ok == 1){
nouvellefenetre->newwindow->anim_ok = connectWidget2->anim_ok ;
nouvellefenetre->newwindow->morph_ok = connectWidget2->morph_ok ;
nouvellefenetre->newwindow->start();
}
else if(connectWidget2->anim4_ok == 1 ) {
         nouvellefenetre->newwindow->anim4_ok = 1;
         nouvellefenetre->newwindow->start();
                                        }
     else if(connectWidget2->anim5_ok == 1 ) {
         nouvellefenetre->newwindow->anim5_ok = 1;
         nouvellefenetre->newwindow->start();
                                        };
*/
}

//====================================
void k3dsurface::newgldrawwindow(){
//newglwindow::newglwindow * glfenetre = new newglwindow::newglwindow();
//glfenetre->gldrawWidget->objet = new Model3D();//connectWidget2->objet;
//glfenetre->show();
}

//====================================
void k3dsurface::param_toggled(){
/*
    parametrique_ok *= -1;
    if(parametrique_ok == 1) toolBox2->setItemEnabled(0,TRUE);
    else toolBox2->setItemEnabled(0,FALSE);
*/
}

 //====================================
void k3dsurface::cylindric_Fct_activated(){
  QMessageBox message ;

    if(activate_tools == 1) {
    message.setText(tr(QString("Deactivate Tools")));
    message.adjustSize () ;
    message.exec();
    sfactivate->toggle();
        return ;
    }

    if(fourdimshapes == 1 )
    {
    message.setText(tr(QString("Deactivate 4D shapes")));
    message.adjustSize () ;
    message.exec();
    cylindrical->toggle();
        return ; 
    }

    if(implicite_fct  == 1 )
    {
    message.setText(tr(QString("Deactivate Implicit Function")));
    message.adjustSize () ;
    message.exec();
    cylindrical->toggle();
        return ;
    }

    if(spheric_fct  == 1 )
    {
    message.setText(tr(QString("Deactivate Spheric Function")));
    message.adjustSize () ;
    message.exec();
    cylindrical->toggle();
        return ;
    }

    // Deactivate condition
   if(activate_cd == 1) {
      activ_cond->toggle();
      condition->setEnabled(FALSE);
      inverse_condt->setEnabled(FALSE);
       connectWidget2->objet->there_is_condition *= -1;
       activate_cd = -1;
   }
    cylindric_fct *= -1;

    if(cylindric_fct == 1) {
    connectWidget2->objet->cylindricaldef = 1;
    cylindreBox->setEnabled(TRUE);
    inverse_condt->setEnabled(FALSE);
    page1->setEnabled(FALSE);
    page2->setEnabled(FALSE);
    perform_cylindre();
    }
    else {
    connectWidget2->objet->cylindricaldef = -1;
    cylindreBox->setEnabled(FALSE);
    inverse_condt->setEnabled(TRUE);
    page1->setEnabled(TRUE);
    page2->setEnabled(TRUE);
    }
}

 //====================================
void k3dsurface::perform_cylindre()
{  double vals=0;//[1] = {0};
   QMessageBox message ;
   FunctionParser f1, fp, fp2; 

    fp.AddConstant("pi", 3.14159265);
    int ret;

    ret = fp2.Parse(puissance_c_val->text(), "youpi");
    if(fmod(fp2.Eval(&vals), 2) == 0) {

    message.setText(tr("n mod 2 = 0 !!!!"));
    message.adjustSize () ;
    message.exec();
        return ;
    };

    ret = fp.Parse(fctdefc->text(), "u,z,t");
    if(ret >= 0) 
    {

    message.setText(tr(QString("Implicit equation : F(u,z,t)--> At col:")+
        QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

  connectWidget2->objet->cylindricaldef = 1;
  connectWidget2->objet->cylindrical_expression = fctdefc->text();
  connectWidget2->objet->coefficient_n = puissance_c_val->text();

  connectWidget2->objet->inf_u = umin_3_2_2_2->text();
  connectWidget2->objet->sup_u = umax_3_2_2_2->text();
  connectWidget2->objet->inf_v = vmin_3_2_2_2->text();
  connectWidget2->objet->sup_v = vmax_3_2_2_2->text();

  //Process the new surface :
ParametricSurfaceProcess();
}
//====================================
void k3dsurface::cylindre_fct_changed( const QString & choix )
{
      if(choix == QString("Star_1")) {
  puissance_c_val->setText("1") ;
  fctdefc->setText("(1-0.25*z*z)*(1+0.5*sin(1.5*pi*z) +0.3*cos(5*u))") ;
  umin_3_2_2_2->setText("-pi") ;
  umax_3_2_2_2->setText("pi") ;
  vmin_3_2_2_2->setText("-2") ;
  vmax_3_2_2_2->setText("2") ;
  perform_cylindre();   // process the new surface  
  return;
    }

      if(choix == QString("Cup")) {
  puissance_c_val->setText("1") ;
  fctdefc->setText("sin(z*pi)*sin(z*pi) +cos(z*pi+0.9)");
  umin_3_2_2_2->setText("-pi") ;
  umax_3_2_2_2->setText("pi") ;
  vmin_3_2_2_2->setText("0.08") ;
  vmax_3_2_2_2->setText("0.71") ;
  perform_cylindre();   // process the new surface
  return;
    }

      if(choix == QString("Star_2")) {
  puissance_c_val->setText("1") ;
  fctdefc->setText("sin(z^2)*(1+0.5*sin(1.5*pi*z) +0.3*cos(5*u))") ;
  umin_3_2_2_2->setText("-pi") ;
  umax_3_2_2_2->setText("pi") ;
  vmin_3_2_2_2->setText("0") ;
  vmax_3_2_2_2->setText("1.773") ;
  perform_cylindre();   // process the new surface  
  return;
    }
       if(choix == QString("Height")) {
  puissance_c_val->setText("1") ;
  fctdefc->setText("sin(sin(z*pi))") ;
  umin_3_2_2_2->setText("-pi") ;
  umax_3_2_2_2->setText("pi") ;
  vmin_3_2_2_2->setText("-1") ;
  vmax_3_2_2_2->setText("1") ;
  perform_cylindre();   // process the new surface  
  return;
    }
  }
 //====================================


void k3dsurface::spheric_Fct_activated(){
   QMessageBox message ;
if(activate_tools == 1) {
    message.setText(tr(QString("Deactivate Tools")));
    message.adjustSize () ;
    message.exec();
    sfactivate->toggle();
        return ;
    }
    if(fourdimshapes == 1 )
    {
    message.setText(tr(QString("Deactivate 4D shapes")));
    message.adjustSize () ;
    message.exec();
    fct_spherical->toggle();
        return ;
    }

    if(implicite_fct  == 1 )
    {
    message.setText(tr(QString("Deactivate Implicit Function")));
    message.adjustSize () ;
    message.exec();
    fct_spherical->toggle();
        return ;
    }

    if(cylindric_fct  == 1 )
    {
    message.setText(tr(QString("Deactivate Cylindric Function")));
    message.adjustSize () ;
    message.exec();
    fct_spherical->toggle();
        return ;
    }

           // Deactivate condition
   if(activate_cd == 1) {
      activ_cond->toggle();
      condition->setEnabled(FALSE);
      inverse_condt->setEnabled(FALSE);
       connectWidget2->objet->there_is_condition *= -1;
       activate_cd = -1;
   }

    spheric_fct *= -1;
    if(spheric_fct == 1) {
    connectWidget2->objet->sphericaldef = 1;
    groupBox22->setEnabled(TRUE);
    groupBox22->setEnabled(TRUE);
    inverse_condt->setEnabled(FALSE);
    page1->setEnabled(FALSE);
    page2->setEnabled(FALSE);
    /*
    umin_3_2_2->setText("-pi/2");
    umax_3_2_2->setText("pi/2");
    vmin_3_2_2->setText("-pi");
    vmax_3_2_2->setText("pi");
    */
    perform_sphere(); 
    }
    else {
    connectWidget2->objet->sphericaldef = -1;
    groupBox22->setEnabled(FALSE);
   inverse_condt->setEnabled(TRUE);
    page1->setEnabled(TRUE);
    page2->setEnabled(TRUE);
    }
}

 //====================================
void k3dsurface::perform_sphere()
{  double vals=0;//[1] = {0};
   QMessageBox message ;
   FunctionParser f1, fp, fp2;
    fp.AddConstant("pi", 3.14159265);
    int ret;

    ret = fp2.Parse(puissance_r_val->text(), "youpi");
    if(fmod(fp2.Eval(&vals), 2) == 0) {
    message.setText(tr("n mod 2 = 0 !!!!"));
    message.adjustSize () ;
    message.exec();
        return ;
    };

    ret = fp.Parse(fctdefr->text(), "u,v,t");
    if(ret >= 0) 
    {
    message.setText(tr(QString("Implicit equation : f(u,v,t)--> At col:")+
    QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

  connectWidget2->objet->sphericaldef = 1;
  connectWidget2->objet->spherical_expression = fctdefr->text();
  connectWidget2->objet->coefficient_n = puissance_r_val->text();

  connectWidget2->objet->inf_u = umin_3_2_2->text();
  connectWidget2->objet->sup_u = umax_3_2_2->text();
  connectWidget2->objet->inf_v = vmin_3_2_2->text();
  connectWidget2->objet->sup_v = vmax_3_2_2->text();

  //Process the new surface :
ParametricSurfaceProcess();
}
 //====================================

void k3dsurface::explicit_Fct_activated(){
   QMessageBox message ;
  if(activate_tools == 1) {
    message.setText(tr(QString("Deactivate Tools")));
    message.adjustSize () ;
    message.exec();
    sfactivate->toggle();
        return ;
    }

    if(fourdimshapes == 1 )
    {
    message.setText(tr(QString("Deactivate 4D shapes")));
    message.adjustSize () ;
    message.exec();
    fct_explicit->toggle();
        return ;
    }

    if(cylindric_fct  == 1 )
    {
    message.setText(tr(QString("Deactivate Cylindric Function")));
    message.adjustSize () ;
    message.exec();
    fct_explicit->toggle();
        return ;
    }

    if(spheric_fct  == 1 )
    {
    message.setText(tr(QString("Deactivate Spheric Function")));
    message.adjustSize () ;
    message.exec();
    fct_explicit->toggle();
        return ;
    }

           // Deactivate condition
   if(activate_cd == 1) {
      activ_cond->toggle();
      condition->setEnabled(FALSE);
      inverse_condt->setEnabled(FALSE);
       connectWidget2->objet->there_is_condition *= -1;
       activate_cd = -1;
   }

    implicite_fct *= -1;
    if(implicite_fct == 1) {
    connectWidget2->objet->implicitdef = 1;
    parametric_box->setEnabled(TRUE);
    inverse_condt->setEnabled(FALSE);
    //fourdims_box->setEnabled(FALSE);
    page1->setEnabled(FALSE);
    page2->setEnabled(FALSE);
    umin_3_2->setText("-pi");
    umax_3_2->setText("pi");
    vmin_3_2->setText("-pi");
    vmax_3_2->setText("pi");
    perform2();
    }
    else {
    connectWidget2->objet->implicitdef = -1;
    parametric_box->setEnabled(FALSE);
    inverse_condt->setEnabled(TRUE);
    //fourdims_box->setEnabled(TRUE);
    page1->setEnabled(TRUE);
    page2->setEnabled(TRUE);
    }
}

 //====================================

void k3dsurface::supershape_Fct_activated(){
   QMessageBox message ;

if(activate_tools == 1) {
    message.setText(tr(QString("Deactivate Tools")));
    message.adjustSize () ;
    message.exec();
    sfactivate->toggle();
        return ;
    }

       if(fivedimshapes == 1 )
    {
    message.setText(tr(QString("Deactivate ND shapes")));
    message.adjustSize () ;
    message.exec();
    sfactivate->toggle();
        return ; 
    }
    if(fourdimshapes == 1 )
    {
    message.setText(tr(QString("Deactivate 4D shapes")));
    message.adjustSize () ;
    message.exec();
    sfactivate->toggle();
        return ; 
    }

    if(cylindric_fct  == 1 )
    {
    message.setText(tr(QString("Deactivate Cylindric Function")));
    message.adjustSize () ;
    message.exec();
    sfactivate->toggle();
        return ;
    }

    if(spheric_fct  == 1 )
    {
    message.setText(tr(QString("Deactivate Spheric Function")));
    message.adjustSize () ;
    message.exec();
    sfactivate->toggle();
        return ;
    }

    if(implicite_fct  == 1 )
    {
    message.setText(tr(QString("Deactivate Implicit Function")));
    message.adjustSize () ;
    message.exec();
    sfactivate->toggle();
        return ;
    }

   /// Set the right Window for drawing :
    tabsurf->setCurrentPage(0);

 
    activate_supershape *= -1;
    if(activate_supershape == 1) {
    connectWidget2->objet->supershape = 1;
    //sftoolpage->setEnabled(TRUE);
    sfgroupBox->setEnabled(TRUE);
    toolBox2->setEnabled(FALSE);
    inverse_condt->setEnabled(FALSE);
    perform_supershape();
    }
    else {
    connectWidget2->objet->supershape = -1;
    //sftoolpage->setEnabled(FALSE);
    sfgroupBox->setEnabled(FALSE);
    toolBox2->setEnabled(TRUE);
    inverse_condt->setEnabled(TRUE);
    }

}

//====================================
void k3dsurface::Fourdim_Shapes(){
   QMessageBox message ;
  if(activate_tools == 1) {
    message.setText(tr(QString("Deactivate Tools")));
    message.adjustSize () ;
    message.exec();
    sfactivate->toggle();
        return ;
    }

    if(implicite_fct == 1 )
    {
    message.setText(tr(QString("Deactivate Implicite function Z^n = F(x,y,t)")));
    message.adjustSize () ;
    message.exec();
    activate_fourdim->toggle();
        return ;
    }

    if(spheric_fct == 1 )
    {
    message.setText(tr(QString("Deactivate Spheric function ")));
    message.adjustSize () ;
    message.exec();
    activate_fourdim->toggle();
        return ;
    }

    if(cylindric_fct == 1 ) 
    {
    message.setText(tr(QString("Deactivate Cylindric function ")));
    message.adjustSize () ;
    message.exec();
    activate_fourdim->toggle();
        return ;
    }


       // Deactivate condition
   if(activate_cd == 1) {
      activ_cond->toggle();
      condition->setEnabled(FALSE);
      inverse_condt->setEnabled(FALSE);
       connectWidget2->objet->there_is_condition *= -1;
       activate_cd = -1;
   }


    fourdimshapes *= -1;
   if( fourdimshapes == 1) {
    connectWidget2->objet->fourdimshapes = 1;
    fourdims_box->setEnabled(TRUE);
    rotational4d->setEnabled(TRUE);
    inverse_condt->setEnabled(FALSE);
    //parametric_box->setEnabled(FALSE);
    page1->setEnabled(FALSE);
    page2->setEnabled(FALSE);
    perform2();
    }
    else {
    connectWidget2->objet->fourdimshapes = -1;
    fourdims_box->setEnabled(FALSE);
    rotational4d->setEnabled(FALSE);
    inverse_condt->setEnabled(TRUE);
    //parametric_box->setEnabled(TRUE);
    page1->setEnabled(TRUE);
    page2->setEnabled(TRUE);

    }

}

//====================================
void k3dsurface::Fivedim_Shapes(){
  QMessageBox message;

  if(activate_tools == 1) {
    message.setText(tr(QString("Deactivate Tools")));
    message.adjustSize () ;
    message.exec();
    sfactivate->toggle();
        return ;
    }


if(connectWidget2->anim_ok  == 1 ||
   connectWidget2->morph_ok == 1 ||
   connectWidget2->anim4_ok == 1) {
    message.setText(tr(QString("Deactivate 3D/4D  Rotation/Morph")));
    message.adjustSize () ;
    message.exec();
    activate5d->toggle();
        return ;
}
if( connectWidget2->anim5_ok == 1) {
    message.setText(tr(QString("Deactivate 5D  Rotation")));
    message.adjustSize () ;
    message.exec();
    activate5d->toggle();
        return ;
}


     if(activate_supershape  == 1 )
    {
    message.setText(tr(QString("Deactivate Hall")));
    message.adjustSize () ;
    message.exec();
    activate5d->toggle();
        return ;
    }

    if(fourdimshapes == 1 ) 
    {
    message.setText(tr(QString("Deactivate 4D shapes")));
    message.adjustSize () ;
    message.exec();
    activate5d->toggle();
        return ;
    }

    if(implicite_fct  == 1 ) 
    {
    message.setText(tr(QString("Deactivate Implicit Function")));
    message.adjustSize () ;
    message.exec();
    activate5d->toggle();
        return ;
    }

    if(spheric_fct  == 1 ) 
    {
    message.setText(tr(QString("Deactivate Spheric Function")));
    message.adjustSize () ;
    message.exec();
    activate5d->toggle();
        return ;
    }

    if(cylindric_fct  == 1 )
    {
    message.setText(tr(QString("Deactivate Cylindric Function")));
    message.adjustSize () ;
    message.exec();
    activate5d->toggle();
        return ;
    } 
    // Set the right window for drawing:   
 tabsurf->setCurrentPage(0);
 if(paramwidgetstack == 1) glboxclicked();
         // Deactivate condition
   if(activate_cd == 1) {
      activ_cond->toggle();
      condition->setEnabled(FALSE);
      inverse_condt->setEnabled(FALSE);
       connectWidget2->objet->there_is_condition *= -1;
       activate_cd = -1;
   }

    fivedimshapes *= -1;
   if( fivedimshapes == 1) {
    connectWidget2->objet->fivedimshapes = 1;
    //sometimes I'm stuck with 4D!!! Must be changed
    connectWidget2->objet->fourdimshapes = fourdimshapes;
    fivedim_frame->setEnabled(TRUE);
    rotational5d->setEnabled(TRUE);
    toolBox2->setEnabled(FALSE);
    groupBox15->setEnabled(FALSE);
    inverse_condt->setEnabled(FALSE);
    perform_fivedim();
    }
    else {
    connectWidget2->objet->fivedimshapes = -1;
    //sometimes I'm stuck with 4D!!! Must be changed
    if(connectWidget2->objet->sixdimshapes == 1) {
    //connectWidget2->objet->fivedimshapes = -1;
    sixdimactivate->toggle();
    sixdimshape_activate();
    inverse_condt->setEnabled(TRUE);
    };
    connectWidget2->objet->fourdimshapes = fourdimshapes;
    fivedim_frame->setEnabled(FALSE);
    rotational5d->setEnabled(FALSE);
    toolBox2->setEnabled(TRUE);
    groupBox15->setEnabled(TRUE);
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++//
//++++++++++++++++++++++++++++++++++++++++++++++++++++//
//++++++++++++++++++++++++++++++++++++++++++++++++++++//
//++++++++++++++++++++++++++++++++++++++++++++++++++++//
//++++++++++++++++++++++++++++++++++++++++++++++++++++//
//====================================
//static int ToolActivatedpage = 1; //Parametric == 1

void k3dsurface::activatetools(){
  QMessageBox message;

if(connectWidget2->anim_ok  == 1 ||
   connectWidget2->morph_ok == 1 ||
   connectWidget2->anim4_ok == 1) {
    message.setText(tr(QString("Deactivate 3D/4D  Rotation/Morph")));
    message.adjustSize () ;
    message.exec();
    toolcheckBox->toggle();
        return ;
}
if( connectWidget2->anim5_ok == 1) {
    message.setText(tr(QString("Deactivate 5D  Rotation")));
    message.adjustSize () ;
    message.exec();
    toolcheckBox->toggle();
        return ;
}

     if(activate_supershape  == 1 )
    {
    message.setText(tr(QString("Deactivate Hall")));
    message.adjustSize () ;
    message.exec();
    toolcheckBox->toggle();
        return ;
    }

    if(fourdimshapes == 1 )
    {
    message.setText(tr(QString("Deactivate 4D shapes")));
    message.adjustSize () ;
    message.exec();
    toolcheckBox->toggle();
        return ;
    }

    if(implicite_fct  == 1 )
    {
    message.setText(tr(QString("Deactivate Implicit Function")));
    message.adjustSize () ;
    message.exec();
    toolcheckBox->toggle();
        return ;
    }

    if(spheric_fct  == 1 )
    {
    message.setText(tr(QString("Deactivate Spheric Function")));
    message.adjustSize () ;
    message.exec();
    toolcheckBox->toggle();
        return ;
    }

    if(cylindric_fct  == 1 )
    {
    message.setText(tr(QString("Deactivate Cylindric Function")));
    message.adjustSize () ;
    message.exec();
    toolcheckBox->toggle();
        return ;
    }

    if( fivedimshapes  == 1 )
    {
    message.setText(tr(QString("Deactivate ND")));
    message.adjustSize () ;
    message.exec();
    toolcheckBox->toggle();
        return ; 
    }

int current_pag = tabWidget7->currentPageIndex();    

if(current_pag == 0) {   tabsurf->setCurrentPage(0);
// if(paramwidgetstack == 1) glboxclicked();
    }
else { tabsurf->setCurrentPage(1);
// if(isowidgetstack == 1) isogl_clicked();
    }

         // Deactivate condition
   if(activate_cd == 1) {
      activ_cond->toggle();
      condition->setEnabled(FALSE);
      inverse_condt->setEnabled(FALSE);
       connectWidget2->objet->there_is_condition *= -1;
       activate_cd = -1;
   }

    activate_tools *= -1;

if(activate_tools == 1) {
    grouptools->setEnabled(TRUE);
    groupBox41->setEnabled(TRUE);
   // deformerstab->setEnabled(TRUE);
    //toolBox4->setEnabled(TRUE);
    toolBox2->setEnabled(FALSE);
    //groupBox15->setEnabled(FALSE);
    inverse_condt->setEnabled(FALSE);
       connectWidget2->objet->two_system = -1;     //just in case...
    perform_tools(); 
     //(connectWidget2->objet->Tre2_save) * = (connectWidget2->objet->Tre2) *
    }
else {
    grouptools->setEnabled(FALSE);
    groupBox41->setEnabled(FALSE);
    inverse_condt->setEnabled(TRUE);
    toolBox2->setEnabled(TRUE);
    //groupBox15->setEnabled(TRUE);
   // deformerstab->setEnabled(FALSE);
// toolBox4->setEnabled(FALSE);
}
}

//====================================
void k3dsurface::perform_tools()
{
    FunctionParser fp,f1;
    QMessageBox message ;

    fp.AddConstant("pi", 3.14159265);
    int ret;
/*
        if(connectWidget2->objet->DefineNewFct ==1)
    {
    ret = fp.Parse(fctdef->text(), "u,v,t,x,y");
    if(ret >= 0)
    {
   message.setText(tr(QString("k(u,v,t,x,y)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();

        return ;
    }

     f1.Parse(fctdef->text(), "u,v,t");
     fp.AddFunction("k", f1);
    }
*/
    ret = fp.Parse(xtool->text(), "u,v,t");
    if(ret >= 0)
    {

    message.setText(tr(QString("X=g(u,v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();

        return ;
    }

    ret = fp.Parse(ytool->text(), "u,v,t");
    if(ret >= 0)
    {

    message.setText(tr(QString("Y=g(u,v)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();

        return ;
    }

     ret = fp.Parse(ztool->text(), "u,v,t");
    if(ret >= 0) 
    {

    message.setText(tr(QString("Z=h(u,v)--> At col:")+
        QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();

        return ;
    }



  connectWidget2->objet->expression_X =
  connectWidget2->objet->expression_X_save =
  xtool->text();

  connectWidget2->objet->expression_Y =
  connectWidget2->objet->expression_Y_save =
  ytool->text();

  connectWidget2->objet->expression_Z =
  connectWidget2->objet->expression_Z_save =
  ztool->text();


  connectWidget2->objet->inf_u = umin_tools->text();
  connectWidget2->objet->sup_u = umax_tools->text();
  connectWidget2->objet->inf_v = vmin_tools->text();
  connectWidget2->objet->sup_v = vmax_tools->text();
/*
  // process the new surface
  connectWidget2->valueChanged();
*/
    // process the new surface
ParametricSurfaceProcess();













  connectWidget2->objet->MINX_save =   connectWidget2->objet->MINX_tmp;
  connectWidget2->objet->DIFX_save =   connectWidget2->objet->DIFX_tmp;

  connectWidget2->objet->MINY_save =   connectWidget2->objet->MINY_tmp;
  connectWidget2->objet->DIFY_save =   connectWidget2->objet->DIFY_tmp;

  connectWidget2->objet->MINZ_save =   connectWidget2->objet->MINZ_tmp;
  connectWidget2->objet->DIFZ_save =   connectWidget2->objet->DIFZ_tmp;

//initialise the controls widgets 
scalexvalue->setValue(10) ;
scaleyvalue->setValue(10) ;
scalezvalue->setValue(10) ;
scrollBar81->setValue(0) ;
scrollBar20->setValue(10) ;
scrollBar81_2->setValue(0) ;
scrollBar20_2->setValue(10) ;
scrollBar81_3->setValue(0) ;
scrollBar20_3->setValue(10) ;

 connectWidget2->oldcoeff_rayonz = 10; 
 connectWidget2->oldnb_twistez = 0;   
 connectWidget2->oldcoeff_rayony = 10; 
 connectWidget2->oldnb_twistey = 0;
 connectWidget2->oldcoeff_rayonx = 10; 
 connectWidget2->oldnb_twistex = 0; 

 connectWidget2->objet->initialisecoeffscale();
}
//========================================//
void k3dsurface::reset_changes()
{
perform_tools();
perform_tools(); //!!!!  Must be change
}
//========================================//
void k3dsurface::save_changes()
{
 /*
connectWidget2->objet->expression_X_save = connectWidget2->objet->expression_X;
connectWidget2->objet->expression_Y_save = connectWidget2->objet->expression_Y;
connectWidget2->objet->expression_Z_save = connectWidget2->objet->expression_Z;

xtool->setText(connectWidget2->objet->expression_X_save);
ytool->setText(connectWidget2->objet->expression_Y_save);
ztool->setText(connectWidget2->objet->expression_Z_save);

//initialise the controls widgets 
scalexvalue->setValue(10) ;
scaleyvalue->setValue(10) ;
scalezvalue->setValue(10) ;
scrollBar81->setValue(0) ;
scrollBar20->setValue(10) ;
  // process the new surface
  connectWidget2->valueChanged(); 

connectWidget2->objet->MINX_save = connectWidget2->objet->MINX_tmp;
connectWidget2->objet->DIFX_save = connectWidget2->objet->DIFX_tmp;

connectWidget2->objet->MINY_save = connectWidget2->objet->MINY_tmp;
connectWidget2->objet->DIFY_save = connectWidget2->objet->DIFY_tmp;

connectWidget2->objet->MINZ_save = connectWidget2->objet->MINZ_tmp;
connectWidget2->objet->DIFZ_save = connectWidget2->objet->DIFZ_tmp;

 connectWidget2->objet->initialisecoeffscale();
 */

xtool->setText(connectWidget2->objet->expression_X);
ytool->setText(connectWidget2->objet->expression_Y);
ztool->setText(connectWidget2->objet->expression_Z);

perform_tools();
perform_tools(); //!!!!  Must be change

}

//========================================//
void k3dsurface::save_isochanges()
{ 
implicitfunct_2->setText(isoWidget->IsoObjet->ImplicitFunction);

minxlimit_2->setText(isoWidget->IsoObjet->XlimitInf);
minylimit_2->setText(isoWidget->IsoObjet->YlimitInf);
minzlimit_2->setText(isoWidget->IsoObjet->ZlimitInf);

maxxlimit_2->setText(isoWidget->IsoObjet->XlimitSup);
maxylimit_2->setText(isoWidget->IsoObjet->YlimitSup);
maxzlimit_2->setText(isoWidget->IsoObjet->ZlimitSup);

///
isoWidget->IsoObjet->ImplicitFunction_save = isoWidget->IsoObjet->ImplicitFunction;

isoWidget->IsoObjet->XlimitInf_save = isoWidget->IsoObjet->XlimitInf;
isoWidget->IsoObjet->YlimitInf_save = isoWidget->IsoObjet->YlimitInf;
isoWidget->IsoObjet->ZlimitInf_save = isoWidget->IsoObjet->ZlimitInf;

isoWidget->IsoObjet->XlimitSup_save = isoWidget->IsoObjet->XlimitSup;
isoWidget->IsoObjet->YlimitSup_save = isoWidget->IsoObjet->YlimitSup;
isoWidget->IsoObjet->ZlimitSup_save = isoWidget->IsoObjet->ZlimitSup;



/// Scale Controls :
scalexvalue_2->setValue(10) ;
scaleyvalue_2->setValue(10) ;
scalezvalue_2->setValue(10) ;
/// Twist controls :

//scrollBar20_3_2->setValue(10) ;
//scrollBar20_2_2->setValue(10) ;
//scrollBar20_4->setValue(10) ;
scrollBar81_3_2->setValue(0) ;
scrollBar81_2_2->setValue(0) ;
scrollBar81_4->setValue(0) ;

isoWidget->initcontrols();

}
//==========================================
void k3dsurface::reset_isochanges()
{

isoWidget->IsoObjet->ImplicitFunction = isoWidget->IsoObjet->ImplicitFunction_save;
isoWidget->IsoObjet->XlimitInf = isoWidget->IsoObjet->XlimitInf_save;
isoWidget->IsoObjet->YlimitInf = isoWidget->IsoObjet->YlimitInf_save;
isoWidget->IsoObjet->ZlimitInf = isoWidget->IsoObjet->ZlimitInf_save;
isoWidget->IsoObjet->XlimitSup = isoWidget->IsoObjet->XlimitSup_save;
isoWidget->IsoObjet->YlimitSup = isoWidget->IsoObjet->YlimitSup_save;
isoWidget->IsoObjet->ZlimitSup = isoWidget->IsoObjet->ZlimitSup_save;

/// Scale Controls :
scalexvalue_2->setValue(10) ;
scaleyvalue_2->setValue(10) ;
scalezvalue_2->setValue(10) ;
/// Twist controls :

//scrollBar20_3_2->setValue(10) ;
//scrollBar20_2_2->setValue(10) ;
//scrollBar20_4->setValue(10) ;

scrollBar81_3_2->setValue(0) ;
scrollBar81_2_2->setValue(0) ;
scrollBar81_4->setValue(0) ;

//isoWidget->IsoMorphCompute();
   ProcessNewIsoSurface( );
}
//====================================
void k3dsurface::ImplicitFunChanged( const QString & choix )
{
  RootObjet.LookForIsosurfaceEquation(choix);
  implicitfunct->setText(RootObjet.Isosurface[0]);
  minxlimit->setText(RootObjet.Isosurface[1]);
  minylimit->setText(RootObjet.Isosurface[2]);
  minzlimit->setText(RootObjet.Isosurface[3]);
  maxxlimit->setText(RootObjet.Isosurface[4]);
  maxylimit->setText(RootObjet.Isosurface[5]);
  maxzlimit->setText(RootObjet.Isosurface[6]);

 ///Process New Surface :
 PerformNewImplicitFunct();
}

//====================================
void k3dsurface::ToolsImplicitFunChanged( const QString & choix )
{
  RootObjet.LookForIsosurfaceEquation(choix);
  implicitfunct_2->setText(RootObjet.Isosurface[0]);
  minxlimit_2->setText(RootObjet.Isosurface[1]);
  minylimit_2->setText(RootObjet.Isosurface[2]);
  minzlimit_2->setText(RootObjet.Isosurface[3]);
  maxxlimit_2->setText(RootObjet.Isosurface[4]);
  maxylimit_2->setText(RootObjet.Isosurface[5]);
  maxzlimit_2->setText(RootObjet.Isosurface[6]);


 PerformNewToolsImplicitFunct_2();
}
//====================================
void k3dsurface::PerformNewToolsImplicitFunct()
{
    FunctionParser fp,f1;
    QMessageBox message ;

    fp.AddConstant("pi", 3.14159265);
    int ret;


    ret = fp.Parse(implicitfunct_2->text(), "x,y,z,t");
    if(ret >= 0)
    {

    message.setText(tr(QString("F(x,y,z) = --> At col:")+
    QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();

        return ;
    }
    ///Activaste IsoDrawing Area...
    tabsurf->setCurrentPage(1);
  isoWidget->IsoObjet->ImplicitFunction = implicitfunct_2->text();
  isoWidget->IsoObjet->XlimitSup = maxxlimit_2->text();
  isoWidget->IsoObjet->YlimitSup = maxylimit_2->text();
  isoWidget->IsoObjet->ZlimitSup = maxzlimit_2->text();

  isoWidget->IsoObjet->XlimitInf = minxlimit_2->text();
  isoWidget->IsoObjet->YlimitInf = minylimit_2->text();
  isoWidget->IsoObjet->ZlimitInf = minzlimit_2->text();
/*
  // process the new curve
  isoWidget->IsoMorphCompute();
*/
  ///Process New Surface :
 PerformNewImplicitFunct();
}
//====================================
void k3dsurface::PerformNewToolsImplicitFunct_2()
{
    FunctionParser fp,f1;
    QMessageBox message ;

    fp.AddConstant("pi", 3.14159265);
    int ret;

    ret = fp.Parse(implicitfunct_2->text(), "x,y,z,t");
    if(ret >= 0)
    {
    message.setText(tr(QString("F(x,y,z) = --> At col:")+
    QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

    ///Activaste IsoDrawing Area...
    tabsurf->setCurrentPage(1);

  isoWidget->IsoObjet->ImplicitFunction = implicitfunct_2->text();

  isoWidget->IsoObjet->XlimitSup = maxxlimit_2->text();
  isoWidget->IsoObjet->YlimitSup = maxylimit_2->text();
  isoWidget->IsoObjet->ZlimitSup = maxzlimit_2->text();

  isoWidget->IsoObjet->XlimitInf = minxlimit_2->text();
  isoWidget->IsoObjet->YlimitInf = minylimit_2->text();
  isoWidget->IsoObjet->ZlimitInf = minzlimit_2->text();

  ///Save theses equations :
    isoWidget->IsoObjet->ImplicitFunction_save = implicitfunct_2->text();

  isoWidget->IsoObjet->XlimitSup_save = maxxlimit_2->text();
  isoWidget->IsoObjet->YlimitSup_save = maxylimit_2->text();
  isoWidget->IsoObjet->ZlimitSup_save = maxzlimit_2->text();

  isoWidget->IsoObjet->XlimitInf_save = minxlimit_2->text();
  isoWidget->IsoObjet->YlimitInf_save = minylimit_2->text();
  isoWidget->IsoObjet->ZlimitInf_save = minzlimit_2->text();
  ///Update the Tools controls
  /// Scale Controls :
scalexvalue_2->setValue(10) ;
scaleyvalue_2->setValue(10) ;
scalezvalue_2->setValue(10) ;
/// Twist controls :

scrollBar81_3_2->setValue(0) ;
scrollBar81_2_2->setValue(0) ;
scrollBar81_4->setValue(0) ;
     // process the new surface
   ProcessNewIsoSurface( );
}

int startcompute = -1;
//====================================
void k3dsurface::PerformNewImplicitFunct()
{
    FunctionParser fp;
    QMessageBox message ;
    QString resultequation;
    int ret;

    resultequation =    RootObjet.ChangeScript(implicitfunct->text());
    //resultequation = implicitfunct->text();

    //if(implicit_param == 1) {
    ret = isoWidget->IsoObjet->Parse(resultequation);
    if(ret >= 0)
    {
    message.setText(tr(QString("F(x,y,z) = "+resultequation+"--> At col:")+
    QString::number(ret)+ QString("--> \n")+ isoWidget->IsoObjet->ImplicitFunctionParser.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }
 
if(activate_isocd ==1 ) {
        ret = fp.Parse(Isocondition->text(), "x,y,z,t");
    if(ret >= 0)
    {

    message.setText(tr(QString("CND(x,y,z,t) = --> At col:")+
    QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();

        return ;
    }

    else {
    if(inverse_isocondition  == 1) 
    isoWidget->IsoObjet->IsoCondition = QString("("+Isocondition->text()+") = 0");
    else  isoWidget->IsoObjet->IsoCondition  = Isocondition->text(); 
    }
}
    /// Acivate the Iso Drawing Area...
   //  tabsurf->setCurrentPage(1);

  isoWidget->IsoObjet->ImplicitFunction = resultequation;

  isoWidget->IsoObjet->XlimitSup = maxxlimit->text();
  isoWidget->IsoObjet->YlimitSup = maxylimit->text();
  isoWidget->IsoObjet->ZlimitSup = maxzlimit->text();

  isoWidget->IsoObjet->XlimitInf = minxlimit->text();
  isoWidget->IsoObjet->YlimitInf = minylimit->text();
  isoWidget->IsoObjet->ZlimitInf = minzlimit->text();


    // process the new surface
   ProcessNewIsoSurface( );
}


//====================================
void k3dsurface::ProcessNewIsoSurface( )
{
    // process the new surface
int current_pag = tabsurf->currentPageIndex();
if(current_pag != 1) tabsurf->setCurrentPage(1);

if(isowidgetstack == 1)  {
isoWidget->IsoObjet->SpecialMorph_2(
         IsoGlWidget->LocalScene.ArrayNorVer_localPt,
         IsoGlWidget->PolyIndices_local,
         IsoGlWidget->NbPolygnNbVertex,
         IsoGlWidget->TypeIsoSurfaceTriangleListeCND,
         &(IsoGlWidget->VertexNumber),
         1,
         IsoGlWidget->LocalScene.PolyIndices_localPtMin,
         &(IsoGlWidget->LocalScene.NbPolygnNbVertexPtMin));
IsoGlWidget->initializeGL();
IsoGlWidget->PolyNumber  = 3*isoWidget->IsoObjet->NbTriangleIsoSurface;
IsoGlWidget->LocalScene.typedrawing = 1;
IsoGlWidget->updateGL();
/// Make button available for another process:
//computeIso->setText("Compute");
//startcompute = -1;
}
 else  isoWidget->IsoMorphCompute();
}

//====================================
void k3dsurface::tools_extrude1_changed( const QString & choix )
{

  if(choix == QString("Cosinus")) {  
  xtool_2_2->setText("cos(u)"); 
  ytool_2_2->setText("u");
  ztool_2_2->setText("1");
  umin_2_2->setText("0") ;
  umax_2_2->setText("2*pi") ;
    } 

  if(choix == QString("Sinus")) {
  xtool_2_2->setText("sin(u)");
  ytool_2_2->setText("u");
  ztool_2_2->setText("1");
  umin_2_2->setText("0") ;
  umax_2_2->setText("2*pi") ;
    }

  if(choix == QString("Helix")) {
  xtool_2_2->setText("u*sin(u)");
  ytool_2_2->setText("u*cos(u)");
  ztool_2_2->setText("1");
  umin_2_2->setText("0") ;
  umax_2_2->setText("4*pi") ;
    }

 perform_extrude1_tools();

}


//====================================
void k3dsurface::perform_extrude1_tools()
{
    FunctionParser fp,f1;
    QMessageBox message ;

    fp.AddConstant("pi", 3.14159265);
    int ret;


    ret = fp.Parse(xtool_2_2->text(), "u,t"); 
    if(ret >= 0)
    {

    message.setText(tr(QString("X=f(u)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

    ret = fp.Parse(ytool_2_2->text(), "u,t");
    if(ret >= 0) 
    {

    message.setText(tr(QString("Y=g(u)--> At col:")+
    QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

    ret = fp.Parse(ztool_2_2->text(), "u,t");
    if(ret >= 0)
    {
    message.setText(tr(QString("Z=h(u)--> At col:")+
    QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
    return ;
    }

  connectWidget2->objet->expression_X = xtool_2_2->text();
  connectWidget2->objet->expression_Y = ytool_2_2->text();
  connectWidget2->objet->expression_Z = ztool_2_2->text();
  connectWidget2->objet->inf_u = umin_2_2->text();
  connectWidget2->objet->sup_u = umax_2_2->text();
  connectWidget2->objet->inf_v = "0";
  connectWidget2->objet->sup_v = "2*pi";
/*
  // process the new curve
  connectWidget2->valueChanged();
*/
    // process the new surface
ParametricSurfaceProcess();
  
}


//====================================
void k3dsurface::tools_extrude2_changed( const QString & choix )
{

  if(choix == QString("Cosinus")) {  
  xtool_2_3->setText("cos(v)"); 
  ytool_2_3->setText("1");
  ztool_2_3->setText("v"); 
  umin_2_3->setText("0") ; 
  umax_2_3->setText("2*pi") ; 
    } 

  if(choix == QString("Sinus")) {  
  xtool_2_3->setText("sin(v)"); 
  ytool_2_3->setText("1");
  ztool_2_3->setText("v");
  umin_2_3->setText("0") ; 
  umax_2_3->setText("2*pi") ; 
    }

  if(choix == QString("Helix")) {  
  xtool_2_3->setText("v*sin(v)"); 
  ytool_2_3->setText("1");
  ztool_2_3->setText("v*cos(v)"); 
  umin_2_3->setText("0") ; 
  umax_2_3->setText("4*pi") ; 
    }
 perform_extrude2_tools();
}

//====================================
void k3dsurface::perform_extrude2_tools()
{
    FunctionParser fp,f1;
    QMessageBox message ;
    fp.AddConstant("pi", 3.14159265);
    int ret;
    ret = fp.Parse(xtool_2_3->text(), "v,t"); 
    if(ret >= 0) 
    { 

    message.setText(tr(QString("X=f(v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }
    ret = fp.Parse(ytool_2_3->text(), "v,t");
    if(ret >= 0) 
    {
    message.setText(tr(QString("Y=g(v)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

    ret = fp.Parse(ztool_2_3->text(), "v,t");
    if(ret >= 0) 
    { 

    message.setText(tr(QString("Z=h(v)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }
  connectWidget2->objet->expression_X = xtool_2_3->text();
  connectWidget2->objet->expression_Y = ytool_2_3->text();
  connectWidget2->objet->expression_Z = ztool_2_3->text();
  connectWidget2->objet->inf_u = "0";
  connectWidget2->objet->sup_u = "2*pi";
  connectWidget2->objet->inf_v = umin_2_3->text();
  connectWidget2->objet->sup_v = umax_2_3->text();
/*
  // process the new curve
  connectWidget2->valueChanged(); 
*/
    // process the new surface
ParametricSurfaceProcess();
}

//====================================
void k3dsurface::perform_3Dextrude_tools()
{
    FunctionParser fp,f1;
    QMessageBox message ;
    fp.AddConstant("pi", 3.14159265);
    int ret;
    ret = fp.Parse(xtool_2_2->text(), "u,t"); 
    if(ret >= 0) 
    {message.setText(tr(QString("X=f(u)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize ();
    message.exec();
        return ;
    }
    ret = fp.Parse(ytool_2_2->text(), "u,t");
    if(ret >= 0) 
    {message.setText(tr(QString("Y=g(u)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }
    ret = fp.Parse(ztool_2_2->text(), "u,t");
    if(ret >= 0) 
    {message.setText(tr(QString("Z=h(u)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }
    ret = fp.Parse(xtool_2_3->text(), "v,t"); 
    if(ret >= 0) 
    {message.setText(tr(QString("X=f(v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }
    ret = fp.Parse(ytool_2_3->text(), "v,t");
    if(ret >= 0) 
    {message.setText(tr(QString("Y=g(v)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }
    ret = fp.Parse(ztool_2_3->text(), "v,t");
    if(ret >= 0) 
    {message.setText(tr(QString("Z=h(v)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

  connectWidget2->objet->expression_X = xtool_2_2->text()+" + "+xtool_2_3->text();
  connectWidget2->objet->expression_Y = ytool_2_2->text()+" + "+ytool_2_3->text();    
  connectWidget2->objet->expression_Z = ztool_2_2->text()+" + "+ztool_2_3->text();

  connectWidget2->objet->inf_u = umin_2_2->text();
  connectWidget2->objet->sup_u = umax_2_2->text();
  connectWidget2->objet->inf_v = umin_2_3->text();
  connectWidget2->objet->sup_v = umax_2_3->text();

  // Show equations
  connectWidget2->objet->two_system = -1;
  xtool->setText(connectWidget2->objet->expression_X);
  ytool->setText(connectWidget2->objet->expression_Y);
  ztool->setText(connectWidget2->objet->expression_Z);

  umin_tools->setText(connectWidget2->objet->inf_u);
  umax_tools->setText(connectWidget2->objet->sup_u);
  vmin_tools->setText(connectWidget2->objet->inf_v);
  vmax_tools->setText(connectWidget2->objet->sup_v);
  perform_tools();
}


//====================================
void k3dsurface::tools_loft1_changed( const QString & choix )
{

  if(choix == QString("Cosinus")) {
  xtool_2_4->setText("cos(u)");
  ytool_2_4->setText("u");
  ztool_2_4->setText("1");
  umin_2_4->setText("0") ;
  umax_2_4->setText("2*pi") ;
    }

  if(choix == QString("Sinus")) {
  xtool_2_4->setText("sin(u)");
  ytool_2_4->setText("u");
  ztool_2_4->setText("1");
  umin_2_4->setText("0") ;
  umax_2_4->setText("2*pi") ;
    }

  if(choix == QString("Helix")) {
  xtool_2_4->setText("u*sin(u)");
  ytool_2_4->setText("u*cos(u)");
  ztool_2_4->setText("1");
  umin_2_4->setText("0") ;
  umax_2_4->setText("4*pi") ;
    }

 perform_loft1_tools();
}
//====================================
void k3dsurface::perform_loft1_tools()
{
    FunctionParser fp,f1;
    QMessageBox message ;
    fp.AddConstant("pi", 3.14159265);
    int ret;
    ret = fp.Parse(xtool_2_4->text(), "u,t"); 
    if(ret >= 0) 
    {
    message.setText(tr(QString("X=f(u)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize();
    message.exec();
        return ;
    }
    ret = fp.Parse(ytool_2_4->text(), "u,t");
    if(ret >= 0) 
    {
    message.setText(tr(QString("Y=g(u)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }
    ret = fp.Parse(ztool_2_4->text(), "u,t");
    if(ret >= 0) 
    {
    message.setText(tr(QString("Z=h(u)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

  connectWidget2->objet->expression_X = xtool_2_4->text();
  connectWidget2->objet->expression_Y = ytool_2_4->text();
  connectWidget2->objet->expression_Z = ztool_2_4->text();
  connectWidget2->objet->inf_u = umin_2_4->text();
  connectWidget2->objet->sup_u = umax_2_4->text();
  connectWidget2->objet->inf_v = "0";
  connectWidget2->objet->sup_v = "2*pi";
  // process the new surface
  ParametricSurfaceProcess();
}

//====================================
void k3dsurface::tools_loft2_changed( const QString & choix )
{
  if(choix == QString("Cosinus")) {
  xtool_2_5->setText("cos(v)");
  ytool_2_5->setText("1");
  ztool_2_5->setText("v");
  umin_2_5->setText("0") ;
  umax_2_5->setText("2*pi") ;
    }

  if(choix == QString("Sinus")) {
  xtool_2_5->setText("sin(v)");
  ytool_2_5->setText("1");
  ztool_2_5->setText("v");
  umin_2_5->setText("0") ;
  umax_2_5->setText("2*pi") ;
    }

  if(choix == QString("Helix")) {
  xtool_2_5->setText("v*sin(v)");
  ytool_2_5->setText("1");
  ztool_2_5->setText("v*cos(v)");
  umin_2_5->setText("0") ;
  umax_2_5->setText("4*pi") ;
    }
 perform_loft2_tools();
}
//====================================
void k3dsurface::perform_loft2_tools()
{
    FunctionParser fp,f1;
    QMessageBox message ;
    fp.AddConstant("pi", 3.14159265);
    int ret;

    ret = fp.Parse(xtool_2_5->text(), "v,t"); 
    if(ret >= 0) 
    {
    message.setText(tr(QString("X=f(v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }
    ret = fp.Parse(ytool_2_5->text(), "v,t");
    if(ret >= 0) 
    {
    message.setText(tr(QString("Y=g(v)--> At col:")+
    QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }
    ret = fp.Parse(ztool_2_5->text(), "v,t");
    if(ret >= 0) 
    {
    message.setText(tr(QString("Z=h(v)--> At col:")+
    QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize ();
    message.exec();
        return ;
    }
  connectWidget2->objet->expression_X = xtool_2_5->text();
  connectWidget2->objet->expression_Y = ytool_2_5->text();
  connectWidget2->objet->expression_Z = ztool_2_5->text();
  connectWidget2->objet->inf_u = "0";
  connectWidget2->objet->sup_u = "2*pi";
  connectWidget2->objet->inf_v = umin_2_5->text();
  connectWidget2->objet->sup_v = umax_2_5->text();

  // process the new surface
ParametricSurfaceProcess();
}

//====================================
void k3dsurface::perform_3Dloft_tools()
{
    FunctionParser fp,f1;
    QMessageBox message ;
     
    fp.AddConstant("pi", 3.14159265);
    int ret;
    
    ret = fp.Parse(xtool_2_4->text(), "u,t"); 
    if(ret >= 0) 
    {message.setText(tr(QString("X=f(u)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();  
 
        return ; 
    } 

    ret = fp.Parse(ytool_2_4->text(), "u,t");
    if(ret >= 0) 
    {message.setText(tr(QString("Y=g(u)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 

        return ; 
    } 

    ret = fp.Parse(ztool_2_4->text(), "u,t");
    if(ret >= 0) 
    {message.setText(tr(QString("Z=h(u)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 

        return ; 
    } 


    ret = fp.Parse(xtool_2_5->text(), "v,t"); 
    if(ret >= 0) 
    {message.setText(tr(QString("X=f(v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();  
 
        return ; 
    } 
    
    ret = fp.Parse(ytool_2_5->text(), "v,t");
    if(ret >= 0) 
    {message.setText(tr(QString("Y=g(v)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 

        return ; 
    } 

    
    ret = fp.Parse(ztool_2_5->text(), "v,t");
    if(ret >= 0) 
    {message.setText(tr(QString("Z=h(v)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 

        return ; 
    } 

QString alfa1 = "("+umax_2_5->text()+" - v)/("+
                umax_2_5->text()+" - "+umin_2_5->text()+") * ";

QString alfa2 = "(u - "+umin_2_4->text()+")/("+
                umax_2_4->text()+" - "+umin_2_4->text()+") * ";
                
  connectWidget2->objet->expression_X = 
  alfa1+xtool_2_4->text()+" + "+alfa2+xtool_2_5->text();
  
  connectWidget2->objet->expression_Y = 
  alfa1+ytool_2_4->text()+" + "+alfa2+ytool_2_5->text();
     
  connectWidget2->objet->expression_Z = 
  alfa1+ztool_2_4->text()+" + "+alfa2+ztool_2_5->text();
  
   
  connectWidget2->objet->inf_u = umin_2_4->text();
  connectWidget2->objet->sup_u = umax_2_4->text();
  connectWidget2->objet->inf_v = umin_2_5->text();
  connectWidget2->objet->sup_v = umax_2_5->text();
  
  // Show equations
  connectWidget2->objet->two_system = -1;
  xtool->setText(connectWidget2->objet->expression_X);
  ytool->setText(connectWidget2->objet->expression_Y);
  ztool->setText(connectWidget2->objet->expression_Z);
  
  umin_tools->setText(connectWidget2->objet->inf_u);
  umax_tools->setText(connectWidget2->objet->sup_u);
  vmin_tools->setText(connectWidget2->objet->inf_v);
  vmax_tools->setText(connectWidget2->objet->sup_v);
  
  perform_tools();
}

//====================================
void k3dsurface::tools_curve_changed( const QString & choix )
{

  if(choix == QString("Cosinus")) {  
  rotcurvex->setText("cos(u)"); 
  rotcurvey->setText("u");
  rotcurvez->setText("1"); 
  umin_tools_2->setText("0") ; 
  umax_tools_2->setText("2*pi") ; 
    } 

  if(choix == QString("Sinus")) {  
  rotcurvex->setText("sin(u)"); 
  rotcurvey->setText("u");
  rotcurvez->setText("1");
  umin_tools_2->setText("0") ; 
  umax_tools_2->setText("2*pi") ; 
    }

  if(choix == QString("Helix")) {  
  rotcurvex->setText("u*sin(u)"); 
  rotcurvey->setText("u*cos(u)");
  rotcurvez->setText("1"); 
  umin_tools_2->setText("0") ; 
  umax_tools_2->setText("4*pi") ; 
    }
 
 perform_curve_tools();
 
}
//====================================
void k3dsurface::perform_curve_tools()
{    
    FunctionParser fp,f1;
    QMessageBox message ;
     
    fp.AddConstant("pi", 3.14159265);
    int ret;
    
    

    
    ret = fp.Parse(rotcurvex->text(), "u,t"); 
    if(ret >= 0) 
    { 

    message.setText(tr(QString("X=f(u)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();  
 
        return ; 
    } 
    
    ret = fp.Parse(rotcurvey->text(), "u,t");
    if(ret >= 0) 
    { 

    message.setText(tr(QString("Y=g(u)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 

        return ; 
    } 

    ret = fp.Parse(rotcurvez->text(), "u,t");
    if(ret >= 0) 
    { 

    message.setText(tr(QString("Z=h(u)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 

        return ; 
    } 

  connectWidget2->objet->expression_X = rotcurvex->text();
  connectWidget2->objet->expression_Y = rotcurvey->text();    
  connectWidget2->objet->expression_Z = rotcurvez->text(); 
  connectWidget2->objet->inf_u = umin_tools_2->text();
  connectWidget2->objet->sup_u = umax_tools_2->text();
  connectWidget2->objet->inf_v = "0";
  connectWidget2->objet->sup_v = "2*pi";
/*
  // process the new curve
  connectWidget2->valueChanged(); 
*/
    // process the new surface
ParametricSurfaceProcess();
}

//====================================
void k3dsurface::perform_3Dcurve_tools()
{
    FunctionParser fp,f1;
    QMessageBox message ;

    fp.AddConstant("pi", 3.14159265);
    int ret;
    ret = fp.Parse(rotcurvex->text(), "u,t"); 
    if(ret >= 0) 
    {message.setText(tr(QString("X=f(u)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }
    ret = fp.Parse(rotcurvey->text(), "u,t");
    if(ret >= 0) 
    {message.setText(tr(QString("Y=g(u)--> At col:")+
    QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

    ret = fp.Parse(rotcurvez->text(), "u,t");
    if(ret >= 0) 
    {message.setText(tr(QString("Z=h(u)--> At col:")+
    QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

        if(axechoice == 0) {
  QString Axe_distance = "sqrt(("+rotcurvey->text()+
                         ")^2 + ("+rotcurvez->text()+")^2)";

  connectWidget2->objet->expression_X = rotcurvex->text();
  connectWidget2->objet->expression_Y = Axe_distance+"*sin(v)";
  connectWidget2->objet->expression_Z = Axe_distance+"*cos(v)";
}
else if(axechoice == 1) {
  QString Axe_distance = "sqrt(("+rotcurvex->text()+
                         ")^2 + ("+rotcurvez->text()+")^2)";

  connectWidget2->objet->expression_X = Axe_distance+"*sin(v)";
  connectWidget2->objet->expression_Y = rotcurvey->text();    
  connectWidget2->objet->expression_Z = Axe_distance+"*cos(v)";
}

else {
  QString Axe_distance = "sqrt(("+rotcurvex->text()+
                         ")^2 + ("+rotcurvey->text()+")^2)";

  connectWidget2->objet->expression_X = Axe_distance+"*sin(v)";
  connectWidget2->objet->expression_Y =  Axe_distance+"*cos(v)";
  connectWidget2->objet->expression_Z =  rotcurvez->text(); 
}

  connectWidget2->objet->inf_u = umin_tools_2->text();
  connectWidget2->objet->sup_u = umax_tools_2->text();
  connectWidget2->objet->inf_v = "0";
  connectWidget2->objet->sup_v = "2*pi";

  // process the new curve
  //connectWidget2->valueChanged();  // was replaced by "perform_tools()"

  // Show equations
  connectWidget2->objet->two_system = -1;
  xtool->setText(connectWidget2->objet->expression_X);
  ytool->setText(connectWidget2->objet->expression_Y);
  ztool->setText(connectWidget2->objet->expression_Z);

  umin_tools->setText(connectWidget2->objet->inf_u);
  umax_tools->setText(connectWidget2->objet->sup_u);
  vmin_tools->setText(connectWidget2->objet->inf_v);
  vmax_tools->setText(connectWidget2->objet->sup_v);

  perform_tools();
}
//====================================
void k3dsurface::tools_changed( const QString & choix )
{
  connectWidget2->objet->two_system = -1;
  RootObjet.LookForParametricEquation(choix);
  xtool->setText(RootObjet.Parametric[0]);
  ytool->setText(RootObjet.Parametric[1]);
  ztool->setText(RootObjet.Parametric[2]);

  umin_tools->setText(RootObjet.Parametric[3]);
  umax_tools->setText(RootObjet.Parametric[4]);
  vmin_tools->setText(RootObjet.Parametric[5]);
  vmax_tools->setText(RootObjet.Parametric[6]);
// process the new surface
  perform_tools() ;
}

//====================================
void k3dsurface::perform_fivedim()
{
    FunctionParser fp,f1;
    QMessageBox message ;

    fp.AddConstant("pi", 3.14159265);
    int ret;
/*
        if(connectWidget2->objet->DefineNewFct ==1)
    {
    ret = fp.Parse(fctdef->text(), "u,v,t,x,y");
    if(ret >= 0)
    { 
   message.setText(tr(QString("k(u,v,t,x,y)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

     f1.Parse(fctdef->text(), "u,v,t");
     fp.AddFunction("k", f1);
    }
*/
    ret = fp.Parse(xcft_5->text(), "u,v,t");
    if(ret >= 0)
    {
    message.setText(tr(QString("X=g(u,v)--> At col:")+
    QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize();
    message.exec();
        return ;
    }

    ret = fp.Parse(ycft_5->text(), "u,v,t");
    if(ret >= 0)
    {
    message.setText(tr(QString("Y=g(u,v)--> At col:")+
    QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

     ret = fp.Parse(zcft_5->text(), "u,v,t");
    if(ret >= 0)
    {
    message.setText(tr(QString("Z=h(u,v)--> At col:")+
    QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

     ret = fp.Parse(wcft_5->text(), "u,v,t");
    if(ret >= 0)
    {
    message.setText(tr(QString("W=h(u,v)--> At col:")+
    QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

      ret = fp.Parse(tcft_5->text(), "u,v,t");
    if(ret >= 0)
    {
    message.setText(tr(QString("T=h(u,v)--> At col:")+
    QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }


  //connectWidget2->objet->fivedimshapes = 1;
  connectWidget2->objet->expression_X = ycft_5->text(); ///ToReverse Axes
  connectWidget2->objet->expression_Y = xcft_5->text(); ///ToReverse Axes
  connectWidget2->objet->expression_Z = zcft_5->text();
  connectWidget2->objet->expression_W = wcft_5->text();
  connectWidget2->objet->expression_T = tcft_5->text();

  connectWidget2->objet->inf_u = umin_5->text();
  connectWidget2->objet->sup_u = umax_5->text();
  connectWidget2->objet->inf_v = vmin_5->text();
  connectWidget2->objet->sup_v = vmax_5->text();

  if(sixdimshapes == 1 ) connectWidget2->objet->expression_S = scft_5->text();

   /// Set the right Window for drawing :
 tabsurf->setCurrentPage(0);
 if(paramwidgetstack == 1) glboxclicked();
  //Process the new surface :
ParametricSurfaceProcess();
   }

//====================================
void k3dsurface::FivedimShapes(){

}

//====================================

void k3dsurface::IconBox()
{

    QMessageBox message ;
    //message.setIconPixmap(QPixmap("agoujime.jpg"));
    message.setText(tr("          K3DSurf 0.6 \
                         \nBy: Abderrahman Taha\
                         \n taha_ab@yahoo.fr "));
    message.adjustSize () ;
    message.exec();

}

//====================================
void k3dsurface::loadMesh()
{
        editeur *ed = new editeur();
        ed->load("Mesh.inc");
        ed->show();
}
//====================================
void k3dsurface::loadVrml()
{

}
//====================================
//====================================
void k3dsurface::loadObj()
{
    int i,cl, nb1,nb2,nb3,nb4;
    Model3D  * lien_objet;
    //Iso3D  *iso_objet;
    int nb_ligne, nb_colone, coupure_ligne, coupure_colone;
    //int nbisopt, nbisotriangle, index;
    QString text1;

         nb_ligne = connectWidget2->objet->nb_ligne ,
         nb_colone = connectWidget2->objet->nb_colone,
         coupure_ligne = connectWidget2->objet->coupure_ligne,
         coupure_colone = connectWidget2->objet->coupure_col;
         lien_objet = connectWidget2->objet;

        connectWidget2->valueChanged();  // Not always necessery but for we don't generate .obj file all the time...

     for(i=0;i<nb_ligne - coupure_ligne; i++)
          for(cl=0; cl<nb_colone - coupure_colone; cl++)
      text1 += "v "+QString::number(lien_objet->Tre[i*3][cl])+" \
              "+QString::number(lien_objet->Tre[i*3+1][cl])+" \
              "+QString::number(lien_objet->Tre[i*3+2][cl])+"\n" ;


// Begining to define faces:
for(i=0;i<nb_ligne -1 -coupure_ligne; i++)
  for(cl=0; cl<nb_colone -1 -coupure_colone; cl++) {
          nb1 = i*(nb_colone- coupure_colone)+ cl +1;
          nb2 = (i+1)*(nb_colone- coupure_colone)+ cl +1;
          nb3 = (i+1)*(nb_colone- coupure_colone)+ (cl+1) +1;
          nb4 = i*(nb_colone- coupure_colone)+ (cl+1) +1;
if( objfile_triangle == 1){
text1 += "f "+QString::number(nb1)+" "+QString::number(nb2)+" "+QString::number(nb3)+"\n";        text1 += "f "+QString::number(nb3)+" "+QString::number(nb4)+" "+QString::number(nb1)+"\n";
}
else text1 += "f "+QString::number(nb1)+" "+QString::number(nb2)+" "+QString::number(nb3)+" "+QString::number(nb4)+"\n";
                                                    }


        saveScript(text1, "test.obj");
        editeur *ed = new editeur();
        ed->load("test.obj");
        ed->show();
}
//====================================
void k3dsurface::activate_tria_nas(){
 tria_nas *= -1 ;
}
//====================================
void k3dsurface::loadNas()
{

}
//====================================
void k3dsurface::saveScript(QString &text, QString name)
{
      QFile f( name );
    if ( !f.open( IO_WriteOnly ) ) {
 statusBar()->message( tr("Could not write to %1").arg(name),
         2000 );
 return;
    }

    QTextStream t( &f );
    t << text;
    f.close();
}
//====================================
void k3dsurface::smooth_ok()
{
smooth_triangle=1;
}
//====================================
void k3dsurface::triangle_ok()
{
smooth_triangle=-1;
}
//====================================
void k3dsurface::mesh_ok()
{
mesh_parametric = 1;
}
//====================================
void k3dsurface::parameter_ok()
{
mesh_parametric = -1;
}

//====================================
void k3dsurface::NewIsoScript()
{

 }


//====================================
void k3dsurface::newScriptRun()
{
}

//====================================
void k3dsurface::newDocIso()
{
    editeur *ed = new editeur();
    ed->setCaption(tr("Qt Example - Application"));
    QString text, conditiontext, Limits[6],DefinedVar[6];

    Limits[0] = minxlimit->text();
    Limits[1] = maxxlimit->text();
    Limits[2] = minylimit->text();
    Limits[3] = maxylimit->text();
    Limits[4] = minzlimit->text();
    Limits[5] = maxzlimit->text();

    // User Defined Variables:
    if(isoWidget->IsoObjet->ActivateHeightSpeedCalculations  == 1) {
(isoWidget->IsoObjet->U1  == 1) ? DefinedVar[0]=unaryfct_1->text() : DefinedVar[0]="";
(isoWidget->IsoObjet->U2  == 1) ? DefinedVar[1]=unaryfct_2->text() : DefinedVar[1]="";
(isoWidget->IsoObjet->U3  == 1) ? DefinedVar[2]=unaryfct_3->text() : DefinedVar[2]="";

(isoWidget->IsoObjet->B1  == 1) ? DefinedVar[3]=binaryfct_1->text() : DefinedVar[3]="";
(isoWidget->IsoObjet->B2  == 1) ? DefinedVar[4]=binaryfct_2->text() : DefinedVar[4]="";
(isoWidget->IsoObjet->B3  == 1) ? DefinedVar[5]=binaryfct_3->text() : DefinedVar[5]="";
    }

    // Condition:
    (activate_isocd == 1) ? conditiontext=Isocondition->text() : conditiontext=QString("");
    // Final text:
    text = RootObjet.ChangeScript(
           implicitfunct->text(),
           IsoImplicitBox->currentText(),
           conditiontext,
           Limits,
           DefinedVar
           );
    ed->settext(text);
    ed->show();
}

//====================================
void k3dsurface::newDocToolsIso()
{   editeur *ed = new editeur();
    ed->setCaption(tr("Isosurface : "+IsoImplicitBox->currentText()));
    QString text;
    text  = "Name: "+IsoImplicitBox->currentText();
    text += "\nF():";
    text += implicitfunct_2->text();
    text += "\n[x]:";
    text += minxlimit_2->text();
    text += ",  ";
    text += maxxlimit_2->text();
    text += "\n[y]:";
    text += minylimit_2->text();
    text += ",  ";
    text += maxylimit_2->text();
    text += "\n[z]:";
    text += minzlimit_2->text();
    text += ",  ";
    text += maxzlimit_2->text();
    text += "\n ;";
    ed->settext(text);
    ed->show();
}

//==============================
void k3dsurface::newDoc()
{
    editeur *ed = new editeur();
    ed->setCaption(tr("Qt Example - Application"));
    QString text;

    if(activate_tools == 1)  {
    text   = "X(): ";
    text +=   xtool->text();
    text += "\nY(): ";
    text +=   ytool->text();
    text += "\nZ(): ";
    text +=   ztool->text();
    text += "\n[u]: ";
    text +=   umin_tools->text();
    text += ",  ";
    text +=   umax_tools->text();
    text += "\n[v]: ";
    text +=   vmin_tools->text();
    text += ",  ";
    text +=   vmax_tools->text();
    text += "\n\n";
  }
  else
  if(cylindric_fct == 1) {
    text = "R^";
    text += puissance_c_val->text();
    text += " = ";
    text += fctdefc->text();
    text += "\n With   U[ ";
    text +=   umin_3_2_2_2->text();
    text += ",  ";
    text +=   umax_3_2_2_2->text();
    text += "] And V[  ";
    text +=   vmin_3_2_2_2->text();
    text += ",  ";
    text +=   vmax_3_2_2_2->text();
    text += "] \n";
 }

 else  if(spheric_fct == 1) {
    text = "R^";
    text += puissance_r_val->text();
    text += " = ";
    text += fctdefr->text();
    text += "\n With   U[ ";
    text +=   umin_3_2_2->text();
    text += ",  ";
    text +=   umax_3_2_2->text();
    text += "] And V[  ";
    text +=   vmin_3_2_2->text();
    text += ",  ";
    text +=   vmax_3_2_2->text();
    text += "] \n";
 }
else
if(sixdimshapes == 1) {
    text = "X = ";
    text +=   xcft_5->text();
    text += "\nY = ";
    text +=   ycft_5->text();
    text += "\nZ = ";
    text +=   zcft_5->text();
    text += "\nW = ";
    text +=   wcft_5->text();
    text += "\nT = ";
    text +=   tcft_5->text();
    text += "\nS = ";
    text +=   scft_5->text();

    text += "\n With   U[ "; 
    text +=   umin_5->text();
    text += ",  ";
    text +=   umax_5->text();
    text += "] And V[  ";
    text +=   vmin_5->text();
    text += ",  ";
    text +=   vmax_5->text();
    text += "] \n\n";

}
else

if(fivedimshapes == 1) {
    text = "X = ";
    text +=   xcft_5->text();
    text += "\nY = ";
    text +=   ycft_5->text();
    text += "\nZ = ";
    text +=   zcft_5->text();
    text += "\nW = ";
    text +=   wcft_5->text();
    text += "\nT = ";
    text +=   tcft_5->text();

    text += "\n With   U[ ";
    text +=   umin_5->text();
    text += ",  ";
    text +=   umax_5->text();
    text += "] And V[  ";
    text +=   vmin_5->text();
    text += ",  ";
    text +=   vmax_5->text();
    text += "] \n\n";

}
else
if(fourdimshapes == 1) {
    text = "X = ";
    text +=   xcft_2->text();
    text += "\nY = ";
    text +=   ycft_2->text();
    text += "\nZ = ";
    text +=   zcft_2->text();
    text += "\nW = ";
    text +=   wcft_2->text();
    text += "\n With   U[ ";
    text +=   umin_2->text();
    text += ",  ";
    text +=   umax_2->text();
    text += "] And V[  ";
    text +=   vmin_2->text();
    text += ",  ";
    text +=   vmax_2->text();
    text += "] \n\n";

}
else
if( connectWidget2->objet->implicitdef == -1) {
    text   = "X():";
    text +=   xcft->text();
    text += "\nY():";
    text +=   ycft->text();
    text += "\nZ():";
    text +=   zcft->text();
    text += "\n[u]:";
    text +=   umin->text();
    text += ",  ";
    text +=   umax->text();
    text += "\n[v]:";
    text +=   vmin->text();
    text += ",  ";
    text +=   vmax->text();
    text += "\n\n";
  if(connectWidget2->objet->two_system == 1) {
    text += "X_2 = ";
    text +=   xcft_3->text();
    text += "\nY_2 = ";
    text +=   ycft_3->text();
    text += "\nZ_2 = ";
    text +=   zcft_3->text();
    text += "\n With   U[ ";
    text +=   umin_3->text();
    text += ",  ";
    text +=   umax_3->text();
    text += "] And V[  ";
    text +=   vmin_3->text();
    text += ",  ";
    text +=   vmax_3->text();
    text += "] \n\n";
   }
 }
 else {
     text = "Z^";
    text +=   puissance_val_2->text();
    text += " = ";
    text += fctdefz_val_2->text();
    text += "\n With   U[ ";
    text +=   umin_3_2->text();
    text += ",  ";
    text +=   umax_3_2->text();
    text += "] And V[  ";
    text +=   vmin_3_2->text();
    text += ",  ";
    text +=   vmax_3_2->text();
    text += "] \n";
 }
    ed->settext(text);
    ed->show();

}

//====================================

void k3dsurface::newfct_ok(  )
{
  ////+++++++++++++++++++++
  QString Intermediate;/// To reverse the Axes
//  Intermediate = fctdef->text();/// To reverse the Axes
  Intermediate.replace(QChar('x'), "W");/// To reverse the Axes
  Intermediate.replace(QChar('y'), "x");/// To reverse the Axes
  Intermediate.replace(QChar('W'), "y");  /// To reverse the Axes 

     connectWidget2->objet->newfct = Intermediate;
     connectWidget2->objet->DefineNewFct *=-1;
}
//====================================
void k3dsurface::spheric_fct_changed( const QString & choix )
{
      if(choix == QString("Blob_1")) {
  puissance_r_val->setText("1") ;
  fctdefr->setText("3*cos(u)*cos(v)*sin(u)*sin(u+v)+0.8") ;
  umin_3_2_2->setText("-pi/2") ;
  umax_3_2_2->setText("pi/2") ;
  vmin_3_2_2->setText("-pi") ;
  vmax_3_2_2->setText("pi") ;
  perform_sphere();   // process the new surface  
  return;
    }
      else
       if(choix == QString("Blob_2")) {
  puissance_r_val->setText("1") ;
  fctdefr->setText("3*sin(u)*sin(u)+0.8") ;
  umin_3_2_2->setText("-pi/2") ; 
  umax_3_2_2->setText("pi/2") ; 
  vmin_3_2_2->setText("-pi") ; 
  vmax_3_2_2->setText("pi") ;
  perform_sphere();  // process the new surface   
  return;
    }    
        if(choix == QString("Blob_3")) {
  puissance_r_val->setText("1") ;
  fctdefr->setText("3*cos(u)*cos(v)*sin(u)+0.8") ;
  umin_3_2_2->setText("-pi/2") ;
  umax_3_2_2->setText("pi/2") ;
  vmin_3_2_2->setText("-pi") ;
  vmax_3_2_2->setText("pi") ;
  perform_sphere();   // process the new surface 
  return;
    }
          if(choix == QString("Blob_4")) {
  puissance_r_val->setText("1") ;
  fctdefr->setText("3*sin(u)*cos(u)+0.8") ;
  umin_3_2_2->setText("-pi/2") ;
  umax_3_2_2->setText("pi/2") ;
  vmin_3_2_2->setText("-pi") ;
  vmax_3_2_2->setText("pi") ;
  perform_sphere();  // process the new surface
  return;
    }
            if(choix == QString("Blob_5")) {
  puissance_r_val->setText("1") ;
  fctdefr->setText("3*cos(u)*sin(v)*sin(v)+0.8") ;
  umin_3_2_2->setText("-pi/2") ;
  umax_3_2_2->setText("pi/2") ;
  vmin_3_2_2->setText("-pi") ;
  vmax_3_2_2->setText("pi") ;
  perform_sphere();   // process the new surface 
  return;
    }
             if(choix == QString("Blob_6")) {
  puissance_r_val->setText("1") ;
  fctdefr->setText("sin(v)*cos(v)") ;
  umin_3_2_2->setText("-pi/2") ; 
  umax_3_2_2->setText("pi/2") ; 
  vmin_3_2_2->setText("-pi") ; 
  vmax_3_2_2->setText("pi") ; 
  perform_sphere();   // process the new surface 
  return;
    }
             if(choix == QString("Blob_7")) {
  puissance_r_val->setText("1") ;
  fctdefr->setText("cos(u)*cos(u)") ;
  umin_3_2_2->setText("-pi/2") ;
  umax_3_2_2->setText("pi/2") ;
  vmin_3_2_2->setText("-pi") ;
  vmax_3_2_2->setText("pi") ;
  perform_sphere();  // process the new surface 
  return;
    }
              if(choix == QString("Blob_8")) {
  puissance_r_val->setText("1") ;
  fctdefr->setText("cos(u)+cos(u)*cos(v) +0.8") ;
  umin_3_2_2->setText("-pi/2") ; 
  umax_3_2_2->setText("pi/2") ; 
  vmin_3_2_2->setText("-pi") ; 
  vmax_3_2_2->setText("pi") ; 
  perform_sphere();   // process the new surface 
  return;
    }
              if(choix == QString("Blob_9")) {
  puissance_r_val->setText("1") ;
  fctdefr->setText("(abs(cos(7*u/4))^1.7 + abs(sin(7*u/4))^1.7)^(-1/0.2)") ;
  umin_3_2_2->setText("-pi/2") ;
  umax_3_2_2->setText("pi/2") ;
  vmin_3_2_2->setText("-pi") ;
  vmax_3_2_2->setText("pi") ;
  perform_sphere();   // process the new surface 
  return;
    }
               if(choix == QString("Blob_10")) {
  puissance_r_val->setText("1") ;
  fctdefr->setText("abs(3*x)*cos(u)*sin(v)*sin(u)*sin(u+v)+0.8") ;
  umin_3_2_2->setText("-pi/2") ;
  umax_3_2_2->setText("pi/2") ;
  vmin_3_2_2->setText("-pi") ;
  vmax_3_2_2->setText("pi") ;
  perform_sphere(); // process the new surface 
  return;
    }
  }
//====================================
void k3dsurface::implicit_fct_changed( const QString & choix )
{
      if(choix == QString("Wave")) {
  puissance_val_2->setText("1") ;
  fctdefz_val_2->setText("2*cos(x)*sin(y)") ;
  umin_3_2->setText("-pi") ;
  umax_3_2->setText("pi") ;
  vmin_3_2->setText("-pi");
  vmax_3_2->setText("pi");
   // return;
    }
      if(choix == QString("Selle")) {
  puissance_val_2->setText("1") ;
  fctdefz_val_2->setText("cos(x)*y") ;
  umin_3_2->setText("-pi");
  umax_3_2->setText("pi");
  vmin_3_2->setText("-pi");
  vmax_3_2->setText("pi");
   // return;
    }
       if(choix == QString("Cone")) {
  puissance_val_2->setText("1") ;
  fctdefz_val_2->setText("1 - (x^2 + y^2)") ;
  umin_3_2->setText("-1");
  umax_3_2->setText("1");
  vmin_3_2->setText("-1");
  vmax_3_2->setText("1");
    }
        if(choix == QString("x*exp(-x^2-y^2)")) {
  puissance_val_2->setText("1") ;
  fctdefz_val_2->setText("4*x*exp(-x^2-y^2)") ;
  umin_3_2->setText("-2");
  umax_3_2->setText("2");
  vmin_3_2->setText("-2");
  vmax_3_2->setText("2");
    }
      if(choix == QString("cos(x*y)")) {
  puissance_val_2->setText("1") ;
  fctdefz_val_2->setText("cos(x*y)") ;
  umin_3_2->setText("-pi");
  umax_3_2->setText("pi");
  vmin_3_2->setText("-pi");
  vmax_3_2->setText("pi");
    }
      if(choix == QString("cos(x*x-y*y)")) {
  puissance_val_2->setText("1") ;
  fctdefz_val_2->setText("cos(x*x - y*y)/2") ;
  umin_3_2->setText("-pi");
  umax_3_2->setText("pi");
  vmin_3_2->setText("-pi");
  vmax_3_2->setText("pi");
    }
  // process the new surface
 perform2();
  }

//====================================
void k3dsurface::choice4D_changed( const QString & choix )
{
  RootObjet.Look4DParametricEquation(choix);

  connectWidget2->objet->two_system = -1;
  connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText(RootObjet.Parametric[0]);
  ycft_2->setText(RootObjet.Parametric[1]);
  zcft_2->setText(RootObjet.Parametric[2]);
  wcft_2->setText(RootObjet.Parametric[3]);
  umin_2->setText(RootObjet.Parametric[4]);
  umax_2->setText(RootObjet.Parametric[5]);
  vmin_2->setText(RootObjet.Parametric[6]);
  vmax_2->setText(RootObjet.Parametric[7]);
// copy the first system
  connectWidget2->objet->expression_X = xcft_2->text();
  connectWidget2->objet->expression_Y = ycft_2->text();
  connectWidget2->objet->expression_Z = zcft_2->text();
  connectWidget2->objet->expression_W = wcft_2->text();

  connectWidget2->objet->inf_u = umin_2->text();
  connectWidget2->objet->sup_u = umax_2->text();
  connectWidget2->objet->inf_v = vmin_2->text();
  connectWidget2->objet->sup_v = vmax_2->text();

  //Process the new surface :
ParametricSurfaceProcess();

}

//====================================
void k3dsurface::choice_changed( const QString & choix )
{
  RootObjet.LookForParametricEquation(choix);
  connectWidget2->objet->two_system = -1;

  xcft->setText(RootObjet.Parametric[0]);
  zcft->setText(RootObjet.Parametric[1]);
  ycft->setText(RootObjet.Parametric[2]);
  umin->setText(RootObjet.Parametric[3]);
  umax->setText(RootObjet.Parametric[4]);
  vmin->setText(RootObjet.Parametric[5]);
  vmax->setText(RootObjet.Parametric[6]);

  xcft_3->setText("");
  zcft_3->setText("");
  ycft_3->setText("");
  umin_3->setText("");
  umax_3->setText("");
  vmin_3->setText("");
  vmax_3->setText("");

  connectWidget2->objet->expression_X = RootObjet.Parametric[0];
  connectWidget2->objet->expression_Y = RootObjet.Parametric[1];
  connectWidget2->objet->expression_Z = RootObjet.Parametric[2];

  connectWidget2->objet->inf_u = RootObjet.Parametric[3];
  connectWidget2->objet->sup_u = RootObjet.Parametric[4];
  connectWidget2->objet->inf_v = RootObjet.Parametric[5];
  connectWidget2->objet->sup_v = RootObjet.Parametric[6];

  // copy the second system
  if(connectWidget2->objet->two_system == 1) {

  connectWidget2->objet->expression_X_2 = xcft_3->text();
  connectWidget2->objet->expression_Y_2 = ycft_3->text();
  connectWidget2->objet->expression_Z_2 = zcft_3->text();

  connectWidget2->objet->inf_u_2 = umin_3->text();
  connectWidget2->objet->sup_u_2 = umax_3->text();
  connectWidget2->objet->inf_v_2 = vmin_3->text();
  connectWidget2->objet->sup_v_2 = vmax_3->text();
   }
else {
  // for more security...
  connectWidget2->objet->expression_X_2 = "";
  connectWidget2->objet->expression_Y_2 = "";
  connectWidget2->objet->expression_Z_2 = "";
  connectWidget2->objet->inf_u_2 = "";
  connectWidget2->objet->sup_u_2 = "";
  connectWidget2->objet->inf_v_2 = "";
  connectWidget2->objet->sup_v_2 = "";
  }

  // process the new surface
 ParametricSurfaceProcess();

}


//====================================
void k3dsurface::deffct_desactiver() {

}
//====================================
void k3dsurface::secondsys_desactiver() {
 //  if(connectWidget2->objet->two_system ==1)     secondsystem->toggle(); 
 //   connectWidget2->objet->two_system = -1;
}

//====================================
void k3dsurface::perform_supershape()
{
    FunctionParser fp;
    QMessageBox message ;
     
    fp.AddConstant("pi", 3.14159265);
    int ret;

    ret = fp.Parse(m1->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("M(u)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(m2->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("M(v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(a_1->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("a(u)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(a_2->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("a(v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(b_1->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("b(u)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(b_2->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("b(v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(n1_1->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("N1(u)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(n1_2->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("N1(v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(n2_1->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("N2(u)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(n2_2->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("N2(v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(n3_1->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("N3(u)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(n3_2->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("N3(v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(sfumin->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("Umin--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(sfumax->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("Umax--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(sfvmin->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("Vmin--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(sfvmax->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("Vmax--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }



    connectWidget2->objet->sm1   = m1->text();
    connectWidget2->objet->sa_1  = a_1->text();
    connectWidget2->objet->sb_1  = b_1->text();
    connectWidget2->objet->sn1_1 = n1_1->text();
    connectWidget2->objet->sn2_1 = n2_1->text();
    connectWidget2->objet->sn3_1 = n3_1->text();

    connectWidget2->objet->sm2   = m2->text();
    connectWidget2->objet->sa_2  = a_2->text();
    connectWidget2->objet->sb_2  = b_2->text();
    connectWidget2->objet->sn1_2 = n1_2->text();
    connectWidget2->objet->sn2_2 = n2_2->text();
    connectWidget2->objet->sn3_2 = n3_2->text();


    connectWidget2->objet->inf_u = sfumin->text();
    connectWidget2->objet->sup_u = sfumax->text();
    connectWidget2->objet->inf_v = sfvmin->text();
    connectWidget2->objet->sup_v = sfvmax->text();

   /// Set the right Window for drawing :
    tabsurf->setCurrentPage(0);
    
  //Process the new surface :
    ParametricSurfaceProcess();
}
//====================================
void k3dsurface::choicesf_changed( const QString & choix )
{        
 if(choix == QString("SuperShape_1")) { 
  m1->setText("0"); a_1->setText("1"); b_1->setText("1"); 
  n1_1->setText("0.48"); n2_1->setText("30.25"); n3_1->setText("0.35");
  
  m2->setText("5"); a_2->setText("1"); b_2->setText("1"); 
  n1_2->setText("15.44"); n2_2->setText("-0.45"); n3_2->setText("87");  
  
  sfumin->setText("-pi"); sfumax->setText("pi");
  sfvmin->setText("-pi/2"); sfvmax->setText("pi/2");
}

 if(choix == QString("SuperShape_2")) { 
  m1->setText("0.2"); a_1->setText("1"); b_1->setText("1"); 
  n1_1->setText("0.1"); n2_1->setText("1.7"); n3_1->setText("1.7");
  
  m2->setText("0.2"); a_2->setText("1"); b_2->setText("1"); 
  n1_2->setText("0.5"); n2_2->setText("0.2"); n3_2->setText("0.2");    
  
   sfumin->setText("-pi"); sfumax->setText("pi");
  sfvmin->setText("-pi/2"); sfvmax->setText("pi/2");
}

 if(choix == QString("SuperShape_3")) { 
  m1->setText("2"); a_1->setText("1"); b_1->setText("1"); 
  n1_1->setText("1"); n2_1->setText("1"); n3_1->setText("1");
  
  m2->setText("4"); a_2->setText("1"); b_2->setText("1"); 
  n1_2->setText("1"); n2_2->setText("1"); n3_2->setText("1");  
  
  sfumin->setText("-pi"); sfumax->setText("pi");
  sfvmin->setText("-pi/2"); sfvmax->setText("pi/2");  
}

 if(choix == QString("SuperShape_4")) { 
  m1->setText("5.7"); a_1->setText("1"); b_1->setText("1"); 
  n1_1->setText("0.5"); n2_1->setText("1"); n3_1->setText("2.5");
  
  m2->setText("10"); a_2->setText("1"); b_2->setText("1"); 
  n1_2->setText("3"); n2_2->setText("0.2"); n3_2->setText("1");  
  
  sfumin->setText("-pi"); sfumax->setText("pi");
  sfvmin->setText("-pi/2"); sfvmax->setText("pi/2");  
} 
 
 if(choix == QString("SuperShape_5")) { 
  m1->setText("6"); a_1->setText("1"); b_1->setText("1"); 
  n1_1->setText("60"); n2_1->setText("55"); n3_1->setText("1000");
  
  m2->setText("6"); a_2->setText("1"); b_2->setText("1"); 
  n1_2->setText("250"); n2_2->setText("100"); n3_2->setText("100");
  
  sfumin->setText("-pi"); sfumax->setText("pi");
  sfvmin->setText("-pi/2"); sfvmax->setText("pi/2");  
} 

 if(choix == QString("SuperShape_6")) { 
  m1->setText("2"); a_1->setText("1"); b_1->setText("1"); 
  n1_1->setText("0.99"); n2_1->setText("97.67"); n3_1->setText("-0.439");
  
  m2->setText("7"); a_2->setText("1"); b_2->setText("1"); 
  n1_2->setText("-8.11"); n2_2->setText("-0.0807"); n3_2->setText("93");  
  
  sfumin->setText("-pi"); sfumax->setText("pi");
  sfvmin->setText("-pi/2"); sfvmax->setText("pi/2");  
} 

 if(choix == QString("SuperShape_7")) { 
  m1->setText("6"); a_1->setText("1"); b_1->setText("1"); 
  n1_1->setText("0.709889"); n2_1->setText("46.82"); n3_1->setText("-0.80");
  
  m2->setText("7"); a_2->setText("1"); b_2->setText("1"); 
  n1_2->setText("-31.9083"); n2_2->setText("-0.19"); n3_2->setText("97"); 
  
  sfumin->setText("-pi"); sfumax->setText("pi");
  sfvmin->setText("-pi/2"); sfvmax->setText("pi/2");  
}
 if(choix == QString("SuperShape_8")) { 
  m1->setText("7"); a_1->setText("1"); b_1->setText("1"); 
  n1_1->setText("0.2"); n2_1->setText("1.7"); n3_1->setText("1.7");
  
  m2->setText("7"); a_2->setText("1"); b_2->setText("1"); 
  n1_2->setText("0.2"); n2_2->setText("1.7"); n3_2->setText("1.7");  
  
  sfumin->setText("-pi"); sfumax->setText("pi");
  sfvmin->setText("-pi/2"); sfvmax->setText("pi/2");  
}
 if(choix == QString("SuperShape_9")) { 
  m1->setText("3"); a_1->setText("1"); b_1->setText("1"); 
  n1_1->setText("1"); n2_1->setText("1"); n3_1->setText("1");
  
  m2->setText("6"); a_2->setText("2"); b_2->setText("1"); 
  n1_2->setText("2"); n2_2->setText("1"); n3_2->setText("1"); 
  
  sfumin->setText("-pi"); sfumax->setText("pi");
  sfvmin->setText("-pi/2"); sfvmax->setText("pi/2");  
}
 if(choix == QString("SuperShape_10")) { 
  m1->setText("6"); a_1->setText("1"); b_1->setText("1"); 
  n1_1->setText("3000"); n2_1->setText("1000"); n3_1->setText("1000");
  
  m2->setText("6"); a_2->setText("1"); b_2->setText("1"); 
  n1_2->setText("250"); n2_2->setText("100"); n3_2->setText("100");  
  
  sfumin->setText("-pi"); sfumax->setText("pi");
  sfvmin->setText("-pi/2"); sfvmax->setText("pi/2");  
}

  // process the new surface
    connectWidget2->objet->sm1   = m1->text();
    connectWidget2->objet->sa_1  = a_1->text();
    connectWidget2->objet->sb_1  = b_1->text();
    connectWidget2->objet->sn1_1 = n1_1->text();
    connectWidget2->objet->sn2_1 = n2_1->text();
    connectWidget2->objet->sn3_1 = n3_1->text();

    connectWidget2->objet->sm2   = m2->text();
    connectWidget2->objet->sa_2  = a_2->text();
    connectWidget2->objet->sb_2  = b_2->text();
    connectWidget2->objet->sn1_2 = n1_2->text();
    connectWidget2->objet->sn2_2 = n2_2->text();
    connectWidget2->objet->sn3_2 = n3_2->text();


    connectWidget2->objet->inf_u = sfumin->text();
    connectWidget2->objet->sup_u = sfumax->text();
    connectWidget2->objet->inf_v = sfvmin->text();
    connectWidget2->objet->sup_v = sfvmax->text();

   /// Set the right Window for drawing :
    tabsurf->setCurrentPage(0);
    
  //Process the new surface :
ParametricSurfaceProcess();
}
//====================================
void k3dsurface::perform()
{
    FunctionParser fp,f1;
    QMessageBox message ;
     
    fp.AddConstant("pi", 3.14159265);
    int ret;
    
    /*
        if(connectWidget2->objet->DefineNewFct ==1) 
    {          
    ret = fp.Parse(fctdef->text(), "u,v,t,x,y"); 
    if(ret >= 0) 
    {
    message.setText(tr(QString("k(u,v,t,x,y)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 

        return ; 
    }      
          
     f1.Parse(fctdef->text(), "u,v,t,x,y");
     fp.AddFunction("k", f1);
    }
    */
    ret = fp.Parse(xcft->text(), "u,v,t"); 
    if(ret >= 0) 
    { 

    message.setText(tr(QString("X=g(u,v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();  
  
  
   
        return ; 
    } 
    
    ret = fp.Parse(ycft->text(), "u,v,t,x");
    if(ret >= 0) 
    { 

    message.setText(tr(QString("Y=g(u,v)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
 
 
 
 
        return ; 
    } 
    
     ret = fp.Parse(zcft->text(), "u,v,t,x,y");
    if(ret >= 0) 
    { 
    message.setText(tr(QString("Z=h(u,v)--> At col:")+
        QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
        return ; 
    }

// verifiy that a condition exists  

 if(activate_cd == 1) {
     ret = fp.Parse(condition->text(), "u,v,t,x,y,z");
    if(ret >= 0)
    {
    message.setText(tr(QString("CND --> At col:")+
        QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

  if(inverse_condition  == 1) 
     connectWidget2->objet->condition_expression = QString("("+condition->text()+") = 0");
  else connectWidget2->objet->condition_expression  = condition->text();

} // End if(activate_cd == 1)

  connectWidget2->objet->expression_X = xcft->text(); ///Reverse the Axes
  connectWidget2->objet->expression_Y = ycft->text(); ///Reverse the Axes
  connectWidget2->objet->expression_Z = zcft->text();

  connectWidget2->objet->inf_u = umin->text();
  connectWidget2->objet->sup_u = umax->text();
  connectWidget2->objet->inf_v = vmin->text();
  connectWidget2->objet->sup_v = vmax->text();

// Now we look in the second system if something wrong with it...

if (
(xcft_3->text() != "") && 
(ycft_3->text() != "") &&
(zcft_3->text() != "") &&
(umin_3->text() != "") &&
(umax_3->text() != "") &&
(vmin_3->text() != "") &&
(vmax_3->text() != "")  ) 

{
  connectWidget2->objet->expression_X_2 = xcft_3->text(); ///Reverse the Axes
  connectWidget2->objet->expression_Y_2 = ycft_3->text(); ///Reverse the Axes
  connectWidget2->objet->expression_Z_2 = zcft_3->text();
  connectWidget2->objet->inf_u_2 = umin_3->text();
  connectWidget2->objet->sup_u_2 = umax_3->text();
  connectWidget2->objet->sup_v_2 = vmax_3->text();
  connectWidget2->objet->inf_v_2 = vmin_3->text();

    ret = fp.Parse(xcft_3->text(), "u,v,t");
    if(ret >= 0)
    {
    message.setText(tr(QString("Second System : X=l(u,v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
   connectWidget2->objet->two_system = -1 ;
        return ;
    }

    ret = fp.Parse(ycft_3->text(), "u,v,t");
    if(ret >= 0) 
    {

    message.setText(tr(QString("Second System : Y=r(u,v)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();

 connectWidget2->objet->two_system = -1;
        return ;
    }
     ret = fp.Parse(zcft_3->text(), "u,v,t");
    if(ret >= 0) 
    {
    message.setText(tr(QString("Second System : Z=s(u,v)--> At col:")+
        QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();

 connectWidget2->objet->two_system = -1 ;
        return ;
    }

   // Now we give the authorisation to use two systems...
   connectWidget2->objet->two_system = 1 ; 

}

  // process the new surface
ParametricSurfaceProcess();
}

//====================================
void k3dsurface::ParametricSurfaceProcess()
{
  // process the new surface
int current_pag = tabsurf->currentPageIndex();


if( paramwidgetstack == 1)  {
connectWidget2->objet->SpecialMorph_2(ParamGlWidget->LocalScene.ArrayNorVer_localPt, ParamGlWidget->PolyIndices_local, ParamGlWidget->NbPolygnNbVertex, 1);
ParamGlWidget->PolyNumber = connectWidget2->objet->NbPolygn;
      ParamGlWidget->initializeGL();
      ParamGlWidget->updateGL();
}
 else  connectWidget2->valueChanged();

if(current_pag != 0) tabsurf->setCurrentPage(0);
}
//====================================
void k3dsurface::Initparametricpage(){
      ParamGlWidget->LocalScene.typedrawing = -1;
      ParamGlWidget->LocalScene.line = 1;
}
//====================================
void k3dsurface::Initisopage(){
      IsoGlWidget->LocalScene.typedrawing = 1;
      IsoGlWidget->LocalScene.line = -1;
      IsoGlWidget->LocalScene.box = -1;
}


//====================================
void k3dsurface::perform2()
{  //double vals=0;//[1] = {0};
   QMessageBox message ;
   FunctionParser f1, fp, fp2; 
  
  
  if(fourdimshapes == -1) {
   
    fp.AddConstant("pi", 3.14159265);
    int ret;
/*    
    ret = fp2.Parse(puissance_val_2->text(), "youpi");
    if(fmod(fp2.Eval(&vals), 2) == 0) {
    
    message.setText(tr("n mod 2 = 0 !!!!"));
    message.adjustSize () ;
    message.exec(); 
        return ;        
    };
*/
    ret = fp.Parse(fctdefz_val_2->text(), "x,y,t"); 
    if(ret >= 0) 
    { 

    message.setText(tr(QString("Implicit equation : f(x,y,t)--> At col:")+
        QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
 
        return ; 
    } 
    
    
      connectWidget2->objet->implicitdef = 1;
      connectWidget2->objet->expression_implicite = fctdefz_val_2->text();


  connectWidget2->objet->coefficient_n = puissance_val_2->text();

  connectWidget2->objet->inf_u = umin_3_2->text();
  connectWidget2->objet->sup_u = umax_3_2->text();
  connectWidget2->objet->inf_v = vmin_3_2->text();
  connectWidget2->objet->sup_v = vmax_3_2->text();

  // process the new surface
ParametricSurfaceProcess();

}
else {

    fp.AddConstant("pi", 3.14159265);
    int ret;
/*
        if(connectWidget2->objet->DefineNewFct ==1)
    {
    ret = fp.Parse(fctdef->text(), "u,v,t,x,y");
    if(ret >= 0) 
    {

    message.setText(tr(QString("k(u,v,t,x,y)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

     f1.Parse(fctdef->text(), "u,v,t,x,y");
     fp.AddFunction("k", f1);
    }
*/
    ret = fp.Parse(xcft_2->text(), "u,v,t"); 
    if(ret >= 0) 
    {
    message.setText(tr(QString("X=g(u,v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

    ret = fp.Parse(ycft_2->text(), "u,v,t");
    if(ret >= 0) 
    {
    message.setText(tr(QString("Y=g(u,v)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }


     ret = fp.Parse(zcft_2->text(), "u,v,t");
    if(ret >= 0) 
    {message.setText(tr(QString("Z=h(u,v)--> At col:")+
        QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
    return ;
    }


     ret = fp.Parse(wcft_2->text(), "u,v,t");
    if(ret >= 0) 
    {message.setText(tr(QString("W=l(u,v)--> At col:")+
        QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
    return ;
    }



  connectWidget2->objet->fourdimshapes = 1;

  connectWidget2->objet->expression_X = xcft_2->text(); /// To reverse the Axes
  connectWidget2->objet->expression_Y = ycft_2->text(); /// To reverse the Axes
  connectWidget2->objet->expression_Z = zcft_2->text();
  connectWidget2->objet->expression_W = wcft_2->text();

  connectWidget2->objet->inf_u = umin_2->text();
  connectWidget2->objet->sup_u = umax_2->text();
  connectWidget2->objet->inf_v = vmin_2->text();
  connectWidget2->objet->sup_v = vmax_2->text();

   // process the new surface
ParametricSurfaceProcess();
     }

}

//====================================
void k3dsurface::choice5D_changed( const QString & choix )
{

                        if(choix == QString("Flower")) {

  xcft_5->setText("v *cos(u) -0.5*v^2*cos(2*u)");
  ycft_5->setText("-v*sin(u) -0.5*v^2*sin(2*u)");
  zcft_5->setText("4* v^1.5 *cos(3* u / 2) / 3") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;

  umin_5->setText("0") ;
  umax_5->setText("4*pi") ;
  vmin_5->setText("0") ;
  vmax_5->setText("1") ;

    }
    else if(choix == QString("Cosinus")) {

  xcft_5->setText("u");
  ycft_5->setText("v");
  zcft_5->setText("sin(pi*((u)^2+(v)^2))/2") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ; 
  umin_5->setText("-1") ; 
  umax_5->setText("1") ; 
  vmin_5->setText("-1") ;
  vmax_5->setText("1") ;

    }
      else if(choix == QString("Shell")) {

  xcft_5->setText("1.2^v*(sin(u)^2 *sin(v))");
  ycft_5->setText("1.2^v*(sin(u)^2 *cos(v))");
  zcft_5->setText("1.2^v*(sin(u)*cos(u))") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ;
  umax_5->setText("pi") ;
  vmin_5->setText("-pi/4") ;
  vmax_5->setText("5*pi/2") ;

    }
           else if(choix == QString("Sphere")) {

  xcft_5->setText("cos(u)*cos(v)");
  ycft_5->setText("cos(u)*sin(v)");
  zcft_5->setText("sin(u)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-pi/2") ;
  umax_5->setText("pi/2") ;
  vmin_5->setText("0") ;
  vmax_5->setText("2*pi") ;

    }
              else if(choix == QString("Steiner")) {

  xcft_5->setText("(sin(2 * u) * cos(v) * cos(v))");
  ycft_5->setText("(sin(u) * sin(2 * v))");
  zcft_5->setText("(cos(u) * sin(2 * v))") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-pi/2") ;
  umax_5->setText("pi/2") ;
  vmin_5->setText("-pi/2") ;
  vmax_5->setText("pi/2") ;
    }
              else if(choix == QString("Cross_cap")) {

  xcft_5->setText("(sin(u) * sin(2 * v) / 2)");
  ycft_5->setText("(sin(2 * u) * cos(v) * cos(v))");
  zcft_5->setText("(cos(2 * u) * cos(v) * cos(v))") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-pi/2") ;
  umax_5->setText("pi/2") ;
  vmin_5->setText("-pi/2") ;
  vmax_5->setText("pi/2") ;

    }
               else if(choix == QString("Boys")) {

  xcft_5->setText("(2/3)*(cos(u)*cos(2*v)+sqrt(2)*sin(u)*cos(v))*cos(u) /(sqrt(2) - sin(2*u)*sin(3*v))");
  ycft_5->setText("(2/3)*(cos(u)*sin(2*v)-sqrt(2)*sin(u)*sin(v))*cos(u) /(sqrt(2)-sin(2*u)*sin(3*v))");
  zcft_5->setText("sqrt(2)*cos(u)^2 / (sqrt(2) - sin(2*u)*sin(2*v))") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-pi/2") ;
  umax_5->setText("pi/2") ;
  vmin_5->setText("-pi/2") ;
  vmax_5->setText("pi/2") ;

    }
      else if(choix == QString("Torus")) {

  xcft_5->setText("(1+ 0.5*cos(u))*cos(v)");
  ycft_5->setText("(1+ 0.5*cos(u))*sin(v)");
  zcft_5->setText("0.5*sin(u)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ;
  umax_5->setText("2*pi");
  vmin_5->setText("0") ;
  vmax_5->setText("2*pi") ;
    }
      else if(choix == QString("Klein")) {
   connectWidget2->objet->two_system = -1;   
   connectWidget2->objet->fourdimshapes = 1;
  xcft_5->setText("(3*(1+sin(v)) + 2*(1-cos(v)/2)*cos(u))*cos(v)") ;
  ycft_5->setText("(4+2*(1-cos(v)/2)*cos(u))*sin(v)");
  zcft_5->setText("-2*(1-cos(v)/2) * sin(u)");
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ;
  umax_5->setText("2*pi") ;
  vmin_5->setText("0") ;
  vmax_5->setText("2*pi") ;
    }
       else if(choix == QString("Moebius")) {

  xcft_5->setText("cos(v)+u*cos(v/2)*cos(v)");
  ycft_5->setText("sin(v)+u*cos(v/2)*sin(v)");
  zcft_5->setText("u*sin(v/2)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-0.4") ;
  umax_5->setText("0.4") ;
  vmin_5->setText("0") ;
  vmax_5->setText("2*pi") ;

    }
          else if(choix == QString("Riemann")) {

  xcft_5->setText("u*v");
  ycft_5->setText("v^2 - u^2");
  zcft_5->setText("30*u") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-6") ;
  umax_5->setText("6") ;
  vmin_5->setText("-25") ;
  vmax_5->setText("25") ;

    }

          else if(choix == QString("Klein_2")) {

  xcft_5->setText("(2 + cos(v/2)* sin(u) - sin(v/2)* sin(2 *u))* cos(v)");
  ycft_5->setText("(2 + cos(v/2)* sin(u) - sin(v/2)* sin(2 *u))* sin(v)");
  zcft_5->setText("sin(v/2)* sin(u) + cos(v/2) *sin(2* u)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ;
  umax_5->setText("2*pi") ;
  vmin_5->setText("0") ;
  vmax_5->setText("2*pi") ;

    }
           else if(choix == QString("Henneberg")) {

  xcft_5->setText("2*sinh(u)*cos(v) -(2/3)*sinh(3*u)*cos(3*v)");
  ycft_5->setText("2*sinh(u)*sin(v) +(2/3)*sinh(3*u)*sin(3*v)");
  zcft_5->setText("2*cosh(2*u)*cos(2*v)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-1") ;
  umax_5->setText("1") ;
  vmin_5->setText("-pi/2") ;
  vmax_5->setText("pi/2") ;
    }

          else if(choix == QString("Enneper")) {

  xcft_5->setText("u -u^3/3  + u*v^2");
  ycft_5->setText("v -v^3/3  + v*u^2");
  zcft_5->setText("u^2 - v^2") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-2") ;
  umax_5->setText("2") ;
  vmin_5->setText("-2") ;
  vmax_5->setText("2") ;
    }
            else if(choix == QString("Helix")) {

  xcft_5->setText("(1-0.1*cos(v))*cos(u)");
  ycft_5->setText("(1-0.1*cos(v))*sin(u)");
  zcft_5->setText("0.1*(sin(v) + u/1.7 -10)");
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ;
  umax_5->setText("4*pi") ;
  vmin_5->setText("0") ;
  vmax_5->setText("2*pi") ;

    }
           else if(choix == QString("Hexaedron")) {

  xcft_5->setText("cos(v)^3*cos(u)^3");
  ycft_5->setText("sin(v)^3*cos(u)^3");
  zcft_5->setText("sin(u)^3") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-1.3") ;
  umax_5->setText("1.3") ;
  vmin_5->setText("0") ;
  vmax_5->setText("2*pi") ;
    }

           else if(choix == QString("Sphere_1")) {

  xcft_5->setText("cos(u)*cos(v)");
  ycft_5->setText("cos(u)*sin(v)");
  zcft_5->setText("sin(u)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-pi/2") ;
  umax_5->setText("pi/2") ;
  vmin_5->setText("0") ;
  vmax_5->setText("2*pi") ;

    }

             else if(choix == QString("Catalan")) {

  xcft_5->setText("u-sin(u)*cosh(v)");
  ycft_5->setText("1-cos(u)*cosh(v)");
  zcft_5->setText("4*sin(1/2*u)*sinh(v/2)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-pi") ;
  umax_5->setText("3*pi") ;
  vmin_5->setText("-2") ;
  vmax_5->setText("2") ;
    }

             else if(choix == QString("Toupie")) {

  xcft_5->setText("(abs(u)-1)^2 * cos(v)");
  ycft_5->setText("(abs(u)-1)^2 * sin(v)");
  zcft_5->setText("u") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-1") ;
  umax_5->setText("1") ;
  vmin_5->setText("0") ;
  vmax_5->setText("2*pi") ;

    }
              else if(choix == QString("Bonbon")) {

  xcft_5->setText("u");
  ycft_5->setText("cos (u)*cos (v)");
  zcft_5->setText("cos (u)*sin (v)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ;
  umax_5->setText("2*pi") ;
  vmin_5->setText("0") ;
  vmax_5->setText("2*pi") ;

    }
              else if(choix == QString("Curve")) {

  xcft_5->setText("cos(2*u)");
  ycft_5->setText("sin(3*u)");
  zcft_5->setText("cos(u)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ;
  umax_5->setText("2*pi") ;
  vmin_5->setText("0") ;
  vmax_5->setText("0") ;
    }
                 else if(choix == QString("Trumpet")) {

  xcft_5->setText("cos(u)*sin(v)");
  ycft_5->setText("sin(u)*sin(v)");
  zcft_5->setText("(cos(v)+log(tan(1/2*v)))") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ; 
  umax_5->setText("2*pi") ;
  vmin_5->setText("0.03") ;
  vmax_5->setText("2") ;

    }

                 else if(choix == QString("Helice_Curve")) {

  xcft_5->setText("sin(u)");
  ycft_5->setText("cos(u)");
  zcft_5->setText("(u^2)/100") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ;
  umax_5->setText("6*pi") ;
  vmin_5->setText("0") ;
  vmax_5->setText("0") ;

    }
                  else  if(choix == QString("Cresent")) {

  xcft_5->setText("(2 + sin(2* pi* u) *sin(2 *pi* v)) *sin(3* pi *v)");
  ycft_5->setText("(2 + sin(2* pi *u) *sin(2 *pi *v)) *cos(3* pi *v)");
  zcft_5->setText("cos(2* pi *u) *sin(2* pi* v) + 4 *v - 2") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ; 
  umax_5->setText("1") ; 
  vmin_5->setText("0") ; 
  vmax_5->setText("1") ; 

    }

                  else if(choix == QString("Shoe")) {

  xcft_5->setText("u");
  ycft_5->setText("v");
  zcft_5->setText("1/3*u^3  - 1/2*v^2") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-2") ;
  umax_5->setText("2") ;
  vmin_5->setText("-2") ;
  vmax_5->setText("2") ;

    }
                else if(choix == QString("Snake")) {

  xcft_5->setText("1.2*(1 -v/(2*pi))*cos(3*v)*(1 + cos(u)) + 3*cos(3*v)");
  ycft_5->setText("1.2*(1 -v/(2*pi))*sin(3*v)*(1 + cos(u)) + 3*sin(3*v)");
  zcft_5->setText("9*v/(2*pi) + 1.2*(1 - v/(2*pi))*sin(u)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ;
  umax_5->setText("2*pi") ;
  vmin_5->setText("0") ;
  vmax_5->setText("2*pi") ;

    }

                  else if(choix == QString("Roman")) {

  xcft_5->setText("1/2*sin(2*u)*sin(v)^2");
  ycft_5->setText("1/2*sin(u)*cos(2*v)");
  zcft_5->setText("1/2*cos(u)*sin(2*v)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ; 
  umax_5->setText("pi") ; 
  vmin_5->setText("-pi/2") ; 
  vmax_5->setText("pi/2") ; 

    } 
    
                    else if(choix == QString("Hyperhelicoidal")) {

  xcft_5->setText("(sinh(v)*cos(3*u))/(1+cosh(u)*cosh(v))");
  ycft_5->setText("(sinh(v)*sin(3*u))/(1+cosh(u)*cosh(v))");
  zcft_5->setText("(cosh(v)*sinh(u))/(1+cosh(u)*cosh(v))") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-pi") ; 
  umax_5->setText("pi") ; 
  vmin_5->setText("-pi") ; 
  vmax_5->setText("pi") ; 
  
    }
    

  
                    else if(choix == QString("Horn")) {

  xcft_5->setText("(2 + u*cos(v))*sin(2*pi*u)");
  ycft_5->setText("(2 + u*cos(v))*cos(2*pi*u) + 2*u");
  zcft_5->setText("u *sin(v)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ; 
  umax_5->setText("1") ; 
  vmin_5->setText("0") ; 
  vmax_5->setText("2*pi") ; 

    }
  
  
    
                   else if(choix == QString("Helicoidal")) {

  xcft_5->setText("sinh(v)*sin(u)");
  ycft_5->setText("-sinh(v)*cos(u)");
  zcft_5->setText("3*u") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-pi") ; 
  umax_5->setText("pi") ; 
  vmin_5->setText("-pi") ; 
  vmax_5->setText("pi") ; 
  
    }   
                    else if(choix == QString("Catenoid")) {

  xcft_5->setText("2*cosh(v/2)*cos(u)");
  ycft_5->setText("2*cosh(v/2)*sin(u)");
  zcft_5->setText("v") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-pi") ; 
  umax_5->setText("pi") ; 
  vmin_5->setText("-pi") ; 
  vmax_5->setText("pi") ; 
  
    }  
                   else if(choix == QString("Kuen")) {

  xcft_5->setText("(2*(cos(u) + u*sin(u))*sin(v))/(1+ u^2*sin(v)^2)");
  ycft_5->setText("(2*(sin(u) - u*cos(u))*sin(v))/(1+ u^2*sin(v)^2)");
  zcft_5->setText("log(tan(1/2 *v)) + (2*cos(v))/(1+ u^2*sin(v)^2)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ; 
  umax_5->setText("2*pi") ; 
  vmin_5->setText("0.01") ; 
  vmax_5->setText("pi-0.01") ; 
    }   


                    else if(choix == QString("Hellipticparaboloid")) {

  xcft_5->setText("v*2*cos(u)");
  ycft_5->setText("v*sin(u)");
  zcft_5->setText("v^2") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ; 
  umax_5->setText("2*pi") ; 
  vmin_5->setText("0") ; 
  vmax_5->setText("2") ; 
    }


                    else if(choix == QString("Enneper_2")) {

  xcft_5->setText("u*cos(v)-u^3/3*cos(3*v)");
  ycft_5->setText("-u*sin(v)-u^(3)/3*sin(3*v)");
  zcft_5->setText("u^2*cos(2*v)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ; 
  umax_5->setText("1.2") ; 
  vmin_5->setText("-pi") ; 
  vmax_5->setText("pi") ; 
    } 
   
                    else if(choix == QString("Stereosphere")) {

  xcft_5->setText("2.*u/(u*u+v*v+1.)");
  ycft_5->setText("2.*v/(u*u+v*v+1.)");
  zcft_5->setText("(u*u+v*v-1.)/(u*u+v*v+1.)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-2") ; 
  umax_5->setText("2") ; 
  vmin_5->setText("-2") ; 
  vmax_5->setText("2") ; 

    }

                    else if(choix == QString("Cliffordtorus")) {

  xcft_5->setText("cos(u+v)/(sqrt(2.)+cos(v-u))");
  ycft_5->setText("sin(u+v)/(sqrt(2.)+cos(v-u))");
  zcft_5->setText("sin(v-u)/(sqrt(2.)+cos(v-u))");
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ; 
  umax_5->setText("pi") ; 
  vmin_5->setText("0") ; 
  vmax_5->setText("2*pi") ; 

    }   

  
 
                    else if(choix == QString("Fresnel_1")) {

  xcft_5->setText("cos(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)+pi)/3.)+0.8)");
  ycft_5->setText("sin(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)+pi)/3.)+0.8)");
  zcft_5->setText("sin(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)+pi)/3.)+0.8)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ;
  umax_5->setText("2*pi") ;
  vmin_5->setText("-pi/2") ;
  vmax_5->setText("pi/2") ;

    }

                    else if(choix == QString("Fresnel_2")) {

  xcft_5->setText("cos(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)-pi)/3.)+0.8)");
  ycft_5->setText("sin(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)-pi)/3.)+0.8)");
  zcft_5->setText("sin(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)-pi)/3.)+0.8)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ;
  umax_5->setText("2*pi") ;
  vmin_5->setText("-pi/2") ;
  vmax_5->setText("pi/2") ;

    }

  connectWidget2->objet->fivedimshapes = 1;

  connectWidget2->objet->expression_X = xcft_5->text();
  connectWidget2->objet->expression_Y = ycft_5->text();
  connectWidget2->objet->expression_Z = zcft_5->text();
  connectWidget2->objet->expression_W = wcft_5->text();
  connectWidget2->objet->expression_T = tcft_5->text();

  connectWidget2->objet->inf_u = umin_5->text();
  connectWidget2->objet->sup_u = umax_5->text();
  connectWidget2->objet->inf_v = vmin_5->text();
  connectWidget2->objet->sup_v = vmax_5->text();
 
  /// Set the right Window for drawing :
 tabsurf->setCurrentPage(0);
 if(paramwidgetstack == 1) glboxclicked();
 
  //Process the new surface :
ParametricSurfaceProcess();

}







//====================================
void k3dsurface::isopage_selected( const QString & choice )
{
int current_pag = tabsurf->currentPageIndex();

if (choice =="Parametric")  { 
    if(tabsurf->currentPageIndex() == 1) {
    ParametricSurfaceProcess();
    ParametricSurfaceProcess(); }}   //that's a bug...
else if (choice =="IsoSurface") {
    if(tabsurf->currentPageIndex() != 1) {    
    ProcessNewIsoSurface( );
    ProcessNewIsoSurface( ); }}  //that's a bug...
else if(choice =="ND") {
      if(current_pag != 0)    tabsurf->setCurrentPage(0);
      if(paramwidgetstack == 1) glboxclicked();
    }
	/*
 else if(choice == "Options") {
   typecolor(color->currentItem ());
    }*/
}

//====================================
void k3dsurface::tabWidget7_selected( const QString & )
{ int current_pag = tabWidget7->currentPageIndex();

if(current_pag == 0) {   tabsurf->setCurrentPage(0);
 if(paramwidgetstack != 1) glboxclicked();
    }
else { tabsurf->setCurrentPage(1);
 if(isowidgetstack != 1) isogl_clicked();
    }
}

//====================================
void k3dsurface::add_condt_clicked()
{
 isoWidget->IsoObjet->CNDDraw*= -1;
 IsoGlWidget->cnd();
 IsoPageUpdate();
}

//====================================
void k3dsurface::cndmesh_clicked()
{
 isoWidget->IsoObjet->CNDMesh*= -1;
 IsoGlWidget->cndmesh();
 IsoPageUpdate();
}

//====================================
void k3dsurface::border_clicked()
{
 isoWidget->IsoObjet->BorderDraw*= -1;
 IsoGlWidget->drawborder();
 IsoPageUpdate();
}

//====================================
void k3dsurface::parametrics_clicked()
{
implicit_param = 1; implicit_spheric = -1; implicit_cylindric = -1;
//implicit->setText("F(x,y,z,t) =");
}

//====================================
void k3dsurface::spherics_clicked()
{
implicit_param = -1; implicit_spheric = 1; implicit_cylindric = -1;
//implicit->setText("F(R,u,v,t) =");
}

///====================================///
void k3dsurface::sylindrics_clicked()
{
implicit_param = -1; implicit_spheric = -1; implicit_cylindric = 1;
//implicit->setText("F(R,Z,u,t) =");
}

///====================================///
void k3dsurface::tabsurf_selected( const QString &  )
{
}

///====================================///

int nb_lig=24, nb_col=24, old_nb_lig=0,
    old_nb_col=0, coupure_lig=0, coupure_col=0,
    old_coupure_lig=0, old_coupure_col=0;
///====================================///
void k3dsurface::MakeACopy() {
    int i, j, k, l;

    nb_lig = ParamGlWidget->nb_ligne = connectWidget2->objet->nb_ligne;
    nb_col = ParamGlWidget->nb_colone = connectWidget2->objet->nb_colone;
    coupure_col = ParamGlWidget->coupure_col = connectWidget2->objet->coupure_col;
    coupure_lig = ParamGlWidget->coupure_ligne = connectWidget2->objet->coupure_ligne;
   ParamGlWidget->PolyNumber    = 4*(nb_lig - coupure_lig -1)*(nb_col -coupure_col -1);
   ParamGlWidget->VertexNumber = 6*nb_col*nb_lig;
/// generation of the Normals-Vertex Array :
    l=0;
    for (i=0; i< nb_lig; i++)
      for (j=0; j< nb_col; j++) {
     ParamGlWidget->LocalScene.ArrayNorVer_localPt[l  ] = connectWidget2->objet->Nor2[3*i  ][j];
     ParamGlWidget->LocalScene.ArrayNorVer_localPt[l+1] = connectWidget2->objet->Nor2[3*i+1][j];
     ParamGlWidget->LocalScene.ArrayNorVer_localPt[l+2] = connectWidget2->objet->Nor2[3*i+2][j];
     ParamGlWidget->LocalScene.ArrayNorVer_localPt[l+3] = connectWidget2->objet->Tre2[3*i  ][j];
     ParamGlWidget->LocalScene.ArrayNorVer_localPt[l+4] = connectWidget2->objet->Tre2[3*i+1][j];
     ParamGlWidget->LocalScene.ArrayNorVer_localPt[l+5] = connectWidget2->objet->Tre2[3*i+2][j];
     l+=6;
    }
/// generation of the Index Array :
   k=0;
   for (i=0; i< nb_lig - coupure_lig -1; i++)
      for (j=0; j< nb_col - coupure_col -1; j++) {
     ParamGlWidget->PolyIndices_local[k  ] = i*nb_col+ j;
     ParamGlWidget->PolyIndices_local[k+1] = (i+1)*nb_col + j;
     ParamGlWidget->PolyIndices_local[k+2] = (i+1)*nb_col + (j+1);
     ParamGlWidget->PolyIndices_local[k+3] = i*nb_col + (j+1);
     k+=4;
    }
}

///====================================///
void k3dsurface::tabsurf_currentChanged( QWidget * /*glw*/ )
{/*
static int previousWindow = 0; //Parametric Window

    QString name = glw->name();
    if(name == QString("GLPage")) {
 if(previousWindow == 0){
connectWidget2->objet->SpecialMorph_2(ParamGlWidget->ArrayNorVer_local, ParamGlWidget->PolyIndices_local, ParamGlWidget->NbPolygnNbVertex, 1);
ParamGlWidget->PolyNumber = connectWidget2->objet->NbPolygn;
      ParamGlWidget->initializeGL();
      ParamGlWidget->TypeTriangle = -1;
 }
 else if(previousWindow ==1){
isoWidget->IsoObjet->SpecialMorph_2(ParamGlWidget->ArrayNorVer_local, ParamGlWidget->PolyIndices_local, ParamGlWidget->NbPolygnNbVertex, 1);
ParamGlWidget->initializeGL();
ParamGlWidget->PolyNumber  = 3*isoWidget->IsoObjet->NbTriangleIsoSurface;
ParamGlWidget->TypeTriangle = 1;
 }

ParamGlWidget->updateGL();}
    else if(name == QString("IsoPage")) {previousWindow =1; isoWidget->IsoMorphCompute();}
    else if(name == QString("ParaPage")) {previousWindow =0; connectWidget2->valueChanged();}*/
}

///====================================///
void k3dsurface::DrawInOpenGlArea() {
      MakeACopy();
      ParamGlWidget->initializeGL();
      ParamGlWidget->updateGL();
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::UpdateActivatedWin()
{
if( paramwidgetstack == 1) ParamGlWidget->updateGL();
 else connectWidget2->update();
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::cutline_valueChanged(int ctline )
{
  connectWidget2->objet->coupure_ligne = ParamGlWidget->coupure_ligne = ctline;
  ParamGlWidget->CutLineIndex(ctline);
  UpdateActivatedWin();
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::cutcolumn_valueChanged( int ctcl)
{
  connectWidget2->objet->coupure_col = ParamGlWidget->coupure_col = ctcl;
  ParamGlWidget->CutColIndex(ctcl);
  UpdateActivatedWin();
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::mesh_clicked()
{
  connectWidget2->objet->mesh *= -1;
  ParamGlWidget->meshOk();
  UpdateActivatedWin();
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::box_clicked()
{
  connectWidget2->objet->box *= -1;
  ParamGlWidget->boxOk();
  UpdateActivatedWin();
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::infos_clicked()
{
  connectWidget2->objet->infos  *= -1;
  ParamGlWidget->infosOk();
  UpdateActivatedWin();
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::inter_clicked()
{
  connectWidget2->objet->interior_surface  *= -1;
  ParamGlWidget->backSurf();
  UpdateActivatedWin();  
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::exter_clicked()
{
  connectWidget2->objet->exterior_surface  *= -1;
  ParamGlWidget->frontSurf();
  UpdateActivatedWin();
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::Axes_ok_clicked()
{
  connectWidget2->objet->drawaxes_ok  *= -1;
  ParamGlWidget->axeOk();
    UpdateActivatedWin();
int current_pag = tabsurf->currentPageIndex();
if(current_pag != 0) tabsurf->setCurrentPage(0);
if( paramwidgetstack == 1) ParamGlWidget->updateGL();
 else   connectWidget2->valueChanged();
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::draw_norm_clicked()
{
  connectWidget2->objet->draw_poly_normals  *= -1;
  ParamGlWidget->normOk();
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::linecolumn_valueChanged( int cl)
{
    connectWidget2->objet->nb_licol = cl;
    connectWidget2->objet->nb_colone  = ParamGlWidget->nb_colone = cl;
    connectWidget2->objet->nb_ligne  = ParamGlWidget->nb_ligne = cl;

    /// process the new surface only if Gl window is active
    ParametricSurfaceProcess();
/*    
     if(current_pag ==2){
connectWidget2->objet->SpecialMorph_2(ParamGlWidget->ArrayNorVer_local, ParamGlWidget->PolyIndices_local, ParamGlWidget->NbPolygnNbVertex, 1);
      ParamGlWidget->initializeGL();
      ParamGlWidget->TypeTriangle = -1;
      ParamGlWidget->updateGL();
      }
      else if(current_pag == 0) {
      connectWidget2->objet->fct_bouton_Morph3();
      connectWidget2->update();
      }
*/
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::latency2_valueChanged( int lat)
{
 connectWidget2->objet->latence = connectWidget2->latence = lat;
 ParamGlWidget->restarttimer(lat);
 IsoGlWidget->restarttimer(lat);
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::xg_valueChanged( int cl)
{
isoWidget->IsoObjet->nb_ligne  = cl;
IsoGlWidget->isoline = cl;
    // process the new surface
   ProcessNewIsoSurface( );
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::yg_valueChanged( int cl)
{
isoWidget->IsoObjet->nb_colon  = cl;
IsoGlWidget->isocolumn = cl;
    // process the new surface
   ProcessNewIsoSurface( );
}
///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::zg_valueChanged( int cl)
{
isoWidget->IsoObjet->nb_depth  = cl;
IsoGlWidget->isodepth = cl;
    // process the new surface
   ProcessNewIsoSurface( );
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::DrawIso( )
{  int current_pag = tabsurf->currentPageIndex();

if(current_pag == 2)  {
isoWidget->IsoObjet->SpecialMorph_2(
         IsoGlWidget->LocalScene.ArrayNorVer_localPt,
         IsoGlWidget->PolyIndices_local,
         IsoGlWidget->NbPolygnNbVertex,
         IsoGlWidget->TypeIsoSurfaceTriangleListeCND,
         &(IsoGlWidget->VertexNumber),
         1,
         IsoGlWidget->LocalScene.PolyIndices_localPtMin,
         &(IsoGlWidget->LocalScene.NbPolygnNbVertexPtMin));
ParamGlWidget->initializeGL();
ParamGlWidget->PolyNumber  = 3*isoWidget->IsoObjet->NbTriangleIsoSurface;
ParamGlWidget->updateGL();
}
else  if(current_pag == 1) {
    isoWidget->IsoMorphCompute();
    isoWidget->update();
}
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::isogl_clicked(){
   isowidgetstack *=-1;
isowidgetstack   == 1 ? IsoWidgetStack->raiseWidget ( 0 ) : IsoWidgetStack->raiseWidget ( 1 );
if(isowidgetstack   == 1 ) {
  //glisobutton->setText("OpenGL \n (ON)") ;
  tabsurf->setTabLabel (IsoPage, "IsoSurface (OpenGL ON)");
  morphanimgroupBox->setEnabled(TRUE); }
else {
  //glisobutton->setText("OpenGL \n (OFF)");
 tabsurf->setTabLabel (IsoPage, "IsoSurface (OpenGL OFF)");
 morphanimgroupBox->setEnabled(FALSE); 
if (isoWidget->IsoObjet->nb_depth >29 ||
    isoWidget->IsoObjet->nb_colon >29 ||
    isoWidget->IsoObjet->nb_ligne >29 )
isoWidget->IsoObjet->nb_depth = isoWidget->IsoObjet->nb_colon = isoWidget->IsoObjet->nb_ligne = 26;
xyzg->setValue(26);
}
   // process the new surface:
   //ProcessNewIsoSurface( );
   //ProcessNewIsoSurface( ); // That's a bug...
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::IsoPageUpdate()
{   int current_pag = tabsurf->currentPageIndex();
    if(current_pag !=1) tabsurf->setCurrentPage(1);

    if(isowidgetstack == 1) IsoGlWidget->updateGL();
    else  isoWidget->update();
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::IsoLine_clicked()
{
    IsoGlWidget->lineOk();
    isoWidget->lineOk();
/// Update Iso page :
    IsoPageUpdate();
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::isoaxe_clicked()
{
IsoGlWidget->axeOk();
isoWidget->Axes_draw();
/// Update Iso page :
    IsoPageUpdate();
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::glboxclicked()
{  paramwidgetstack *= -1;
    paramwidgetstack == 1 ? ParaWidgetStack->raiseWidget ( 0 ) : ParaWidgetStack->raiseWidget ( 1 );
    if(paramwidgetstack   == 1) {
     glparbutton->setText("OpenGL\n(ON)") ;
     ParaPage->setCaption("Parametric (OpenGL ON)") ;
     tabsurf->setTabLabel (ParaPage, "Parametric (OpenGL ON)");
    }
    else {
      glparbutton->setText("OpenGL\n(OFF)");
      tabsurf->setTabLabel (ParaPage, "Parametric (OpenGL OFF)");
    }
     // process the new surface
ParametricSurfaceProcess();
ParametricSurfaceProcess();  // That's a bug...
}

//========================================//
void k3dsurface::step_morph(int cl)
{
 /*   
QMessageBox message ;

if(ParamGlWidget->timeractif()) {
    message.setText("Stop Parametric OpenGl Animation");
    message.adjustSize () ;
    message.exec();
    tstep->setValue(NbStep);
    return;
}

if(IsoGlWidget->timeractif()) {
    message.setText("Stop Isosurface OpenGl Animation");
    message.adjustSize () ;
    message.exec();
    tstep->setValue(NbStep);
    return;
}
*/
NbStep =cl;
connectWidget2->step_morph(cl);

}

//========================================/
void k3dsurface::secondsystativation_clicked()
{
connectWidget2->objet->two_system *= -1;
}

//========================================/
void k3dsurface::checkBox240_clicked()
{
 int current_pag = tabsurf->currentPageIndex();
    if(current_pag == 0) ParamGlWidget->smoothpoly();
    else if (current_pag == 1) IsoGlWidget->smoothpoly();
}

//========================================/
void k3dsurface::checkBox241_clicked()
{
 int current_pag = tabsurf->currentPageIndex();
    if(current_pag == 0) ParamGlWidget->smoothline();
    else if (current_pag == 1) IsoGlWidget->smoothline();
}

//========================================/
void k3dsurface::FogBox_clicked()
{
 int current_pag = tabsurf->currentPageIndex();
    if(current_pag == 0) ParamGlWidget->fog();
    else if (current_pag == 1) IsoGlWidget->fog();
}
//========================================/
void k3dsurface::PlanBox_clicked()
{
 int current_pag = tabsurf->currentPageIndex();
    if(current_pag == 0) ParamGlWidget->plan();
    else if (current_pag == 1) IsoGlWidget->plan();
}
//========================================/
void k3dsurface::comboBox18_activated( int ch )
{
           if ( ch ==0) checkBox240_clicked();
    else if (ch == 1) checkBox241_clicked();
    else if (ch == 2) PlanBox_clicked();
    else if (ch == 3) FogBox_clicked();
}




//========================================/
void k3dsurface::screenshot_clicked()
{ int current_pag = tabsurf->currentPageIndex();
  if(current_pag == 0) 
 paramwidgetstack == 1 ? ParamGlWidget->screenshot() : connectWidget2->screenshot();
  else if(current_pag == 1) 
  isowidgetstack == 1 ? IsoGlWidget->screenshot() : isoWidget->screenshot();
}

//========================================/
void k3dsurface::quality_valueChanged( int cl)
{
    IsoGlWidget->quality(cl);
    ParamGlWidget->quality(cl);
    isoWidget->quality(cl);
     connectWidget2->quality(cl);
}

//========================================/
void k3dsurface::png_clicked()
{
    IsoGlWidget->png();
    ParamGlWidget->png();
    isoWidget->png();
    connectWidget2->png();
}

//========================================/
void k3dsurface::bmp_clicked()
{
    IsoGlWidget->bmp();
    ParamGlWidget->bmp();
    isoWidget->bmp();
    connectWidget2->bmp();
}

//========================================/
void k3dsurface::jpg_clicked()
{
    IsoGlWidget->jpg();
    ParamGlWidget->jpg();
    isoWidget->jpg();
    connectWidget2->jpg();
}
///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::UpdateIsoWin()
{
if( isowidgetstack == 1) IsoGlWidget->updateGL();
 else isoWidget->update();
}
//========================================/
void k3dsurface::xyzg_valueChanged( int cl)
{
if(isowidgetstack == -1) {
    if( cl < 30) {
isoWidget->IsoObjet->nb_depth = isoWidget->IsoObjet->nb_colon = isoWidget->IsoObjet->nb_ligne = cl;
IsoGlWidget->isoline = IsoGlWidget->isocolumn = IsoGlWidget->isodepth = cl;

    // process the new surface
if(xyzactivated  == 1)   ProcessNewIsoSurface( );

    }

}
else {
isoWidget->IsoObjet->nb_depth = isoWidget->IsoObjet->nb_colon = isoWidget->IsoObjet->nb_ligne = cl;
IsoGlWidget->isoline = IsoGlWidget->isocolumn = IsoGlWidget->isodepth = cl;
    // process the new surface
if(xyzactivated  == 1)  ProcessNewIsoSurface( );
else IsoGlWidget->updateGL();
}
}
//========================================/
void k3dsurface::xyzg_2_valueChanged( int cl)
{
    isoWidget->IsoObjet->CutDepth = isoWidget->IsoObjet->CutColon = isoWidget->IsoObjet->CutLigne = cl;
    IsoGlWidget->cpisoline = IsoGlWidget->cpisocolumn = IsoGlWidget->cpisodepth = cl;
    // process the new surface
   ProcessNewIsoSurface( );
}

//========================================/
void k3dsurface::xg_2_valueChanged( int cl)
{
     isoWidget->IsoObjet->CutLigne = cl;
     IsoGlWidget->cpisoline = cl;
    // process the new surface
   ProcessNewIsoSurface( );
}

//========================================/
void k3dsurface::yg_2_valueChanged( int cl)
{
    isoWidget->IsoObjet->CutColon = cl;
    IsoGlWidget->cpisocolumn = cl;
    // process the new surface
   ProcessNewIsoSurface( );
}

//========================================/
void k3dsurface::zg_2_valueChanged( int cl)
{
    isoWidget->IsoObjet->CutDepth = cl;
    IsoGlWidget->cpisodepth = cl;
    // process the new surface
   ProcessNewIsoSurface( );
}

//========================================/
void k3dsurface::scalexvalue_valueChanged( int n)
{
connectWidget2->objet->scalex(n);
//UpdateActivatedWin();
ParametricSurfaceProcess();
}

//========================================/
void k3dsurface::scaleyvalue_valueChanged( int n)
{
connectWidget2->objet->scaley(n);
//UpdateActivatedWin();
ParametricSurfaceProcess();
}

//========================================/
void k3dsurface::scalezvalue_valueChanged( int n)
{
connectWidget2->objet->scalez(n);
//UpdateActivatedWin();
ParametricSurfaceProcess();
}


//========================================/
void k3dsurface::scrollBar81_3_valueChanged( int n)
{
    connectWidget2->nbtwistex_changed(n);
   //UpdateActivatedWin();
   ParametricSurfaceProcess();
}

//========================================/
void k3dsurface::scrollBar20_3_valueChanged( int n)
{
    connectWidget2->coeffrayonx_changed(n);
   //UpdateActivatedWin();
   ParametricSurfaceProcess();
}


//========================================/
void k3dsurface::scrollBar81_2_valueChanged( int n)
{
    connectWidget2->nbtwistey_changed(n);
   //UpdateActivatedWin();
   ParametricSurfaceProcess();
}

//========================================/
void k3dsurface::scrollBar20_2_valueChanged( int n)
{
    connectWidget2->coeffrayony_changed(n);
   //UpdateActivatedWin();
   ParametricSurfaceProcess();
}

//========================================/
void k3dsurface::scrollBar81_valueChanged( int n)
{
    connectWidget2->nbtwistez_changed(n);
   //UpdateActivatedWin();
   ParametricSurfaceProcess();
}

//========================================/
void k3dsurface::scrollBar20_valueChanged( int n)
{
    connectWidget2->coeffrayonz_changed(n);
   //UpdateActivatedWin();
   ParametricSurfaceProcess();
}

//========================================/
void k3dsurface::scalexvalue_2_valueChanged( int  n)
{
   isoWidget->IsoObjet->scalex(n);
   //IsoPageUpdate();
   ProcessNewIsoSurface( );
}

//========================================/
void k3dsurface::scaleyvalue_2_valueChanged( int  n)
{
   isoWidget->IsoObjet->scaley(n);
   //IsoPageUpdate();
   ProcessNewIsoSurface( );
}

//========================================/
void k3dsurface::scalezvalue_2_valueChanged( int  n)
{
   isoWidget->IsoObjet->scalez(n);
   //IsoPageUpdate();
   ProcessNewIsoSurface( );
}

//========================================/
void k3dsurface::scrollBar81_3_2_valueChanged( int n)
{
   isoWidget->nbtwistex_changed(n);
   ProcessNewIsoSurface( );
}

//========================================/
void k3dsurface::scrollBar81_2_2_valueChanged( int n)
{
   isoWidget->nbtwistey_changed(n);
   ProcessNewIsoSurface( );
}

//========================================/
void k3dsurface::scrollBar81_4_valueChanged( int n)
{
   isoWidget->nbtwistez_changed(n);
   ProcessNewIsoSurface( );
}
//========================================/
void k3dsurface::scrollBar81_4_valueChanged2( )
{
   ProcessNewIsoSurface( );
}
//========================================/
void k3dsurface::anim_2_toggle()
{ 
anim_2->toggle();
}

void k3dsurface::morph_2_toggle(){morph_2->toggle();};
void k3dsurface::Isomesh_toggle(){Isomesh->toggle();};
void k3dsurface::IsoLine_toggle(){IsoLine->toggle();};
void k3dsurface::isoinfos_toggle(){isoinfos->toggle();};
void k3dsurface::isoaxe_toggle(){isoaxe->toggle();};
void k3dsurface::mesh_toggle(){mesh->toggle();};
void k3dsurface::Axes_ok_toggle(){Axes_ok->toggle();};
void k3dsurface::box_toggle(){box->toggle();};
void k3dsurface::infos_toggle(){infos->toggle();};
void k3dsurface::draw_norm_toggle(){draw_norm->toggle();};
void k3dsurface::anim_toggle(){anim->toggle();};
void k3dsurface::morph_toggle(){morph->toggle();};
void k3dsurface::exter_toggle(){exter->toggle();};
///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::pushButton69_clicked()
{
/*
/// IsoSurface Page :
drawingoptions *newpanl = new drawingoptions();
connect( newpanl->xyzg, SIGNAL( valueChanged(int) ), this, SLOT(xyzg_valueChanged(int)));
connect( newpanl->xg, SIGNAL( valueChanged(int) ), this, SLOT(xg_valueChanged(int)));
connect( newpanl->yg, SIGNAL( valueChanged(int) ), this, SLOT(yg_valueChanged(int)));
connect( newpanl->zg, SIGNAL( valueChanged(int) ), this, SLOT(zg_valueChanged(int)));

connect( newpanl->xyzg_2, SIGNAL( valueChanged(int) ), this, SLOT(xyzg_2_valueChanged(int)));
connect( newpanl->xg_2, SIGNAL( valueChanged(int) ), this, SLOT(xg_2_valueChanged(int)));
connect( newpanl->yg_2, SIGNAL( valueChanged(int) ), this, SLOT(yg_2_valueChanged(int)));
connect( newpanl->zg_2, SIGNAL( valueChanged(int) ), this, SLOT(zg_2_valueChanged(int)));
connect( newpanl->comboBox18_3, SIGNAL(activated(int) ), this, SLOT(comboBox18_3_activated(int)));

/// Parametric Page :
connect( newpanl->cutline, SIGNAL( valueChanged(int) ), this, SLOT(cutline_valueChanged(int)));
connect( newpanl->cutcolumn, SIGNAL( valueChanged(int) ), this, SLOT(cutcolumn_valueChanged(int)));
connect( newpanl->linecolumn, SIGNAL( valueChanged(int) ), this, SLOT(linecolumn_valueChanged(int)));
connect( newpanl->comboBox18_2, SIGNAL(activated(int) ), this, SLOT(comboBox18_2_activated(int)));

/// Color/OpenGL :
connect( newpanl->color, SIGNAL( activated(int) ), this, SLOT(typecolor(int)));
connect( newpanl->red, SIGNAL( valueChanged(int) ), this, SLOT(redcl(int)));
connect( newpanl->green, SIGNAL( valueChanged(int) ), this, SLOT(greencl(int)));
connect( newpanl->blue, SIGNAL( valueChanged(int) ), this, SLOT(bluecl(int)));
connect( newpanl->transparence, SIGNAL( clicked() ), this, SLOT(transparencecl()));
connect( newpanl->transparence, SIGNAL( clicked() ), this, SLOT(transparence->toggle()));
connect( newpanl->comboBox18, SIGNAL( activated(int) ), this, SLOT(comboBox18_activated(int)));

/// Lunch the Panel :
newpanl->show();
*/
}

//==================================================/
void k3dsurface::comboBox18_2_activated( int ch )
{
         if (ch == 0)  {mesh_clicked(); mesh->toggle();}
    else if (ch == 1) {Axes_ok_clicked(); Axes_ok->toggle();}
    else if (ch == 2) {box_clicked(); box->toggle();}
    else if (ch == 3) {infos_clicked(); infos->toggle();}
    else if (ch == 4) {draw_norm_clicked(); draw_norm->toggle();}
    else if (ch == 5) {exter_clicked(); exter->toggle();}
    else if (ch == 6) {anim_verify_rot4d(); anim->toggle();}
    else if (ch == 7) {morph_verify_rot4d(); morph->toggle();}
}

//==================================================/
void k3dsurface::comboBox18_3_activated( int ch )
{
         if (ch == 0) {iso_mesh(); Isomesh->toggle();}
    else if (ch == 1) {IsoLine_clicked(); IsoLine->toggle();}
    else if (ch == 2) {iso_infos(); isoinfos->toggle();}
    else if (ch == 3) {isoaxe_clicked(); isoaxe->toggle();}
    else if (ch == 4) {AnimIso(); anim_2->toggle();}
    else if (ch == 5) {IsoMorph(); morph_2->toggle();}
}

//==================================================/
void k3dsurface::checkBox73_pressed()
{
xyzactivated *= -1;

if(xyzactivated  == 1)   ProcessNewIsoSurface( );
}

//==================================================/
void k3dsurface::Drawiso( ) {
 int nb_equations = RootObjet.pariso.EquationsNumber, i;
 QStringList listeEquations;
 static int start_equations = 0;

for(i =start_equations; i<nb_equations; i++) listeEquations << RootObjet.pariso.FunctionsNames[i];
IsoImplicitBox->insertStringList(listeEquations, IsoImplicitBox->currentItem());

implicitfunct->setText(RootObjet.pariso.FunctionsEquations[start_equations]);

if(RootObjet.pariso.FunctionsConditions[start_equations] != "") Isocondition->setText(RootObjet.pariso.FunctionsConditions[start_equations]);

minxlimit->setText(RootObjet.pariso.xlimitinfsup[0][start_equations]);
minylimit->setText(RootObjet.pariso.ylimitinfsup[0][start_equations]);
minzlimit->setText(RootObjet.pariso.zlimitinfsup[0][start_equations]);

maxxlimit->setText(RootObjet.pariso.xlimitinfsup[1][start_equations]);
maxylimit->setText(RootObjet.pariso.ylimitinfsup[1][start_equations]);
maxzlimit->setText(RootObjet.pariso.zlimitinfsup[1][start_equations]);
start_equations = nb_equations;
textLabel1_14_4->setText("Examples ("+QString::number(IsoImplicitBox->count() + 1)+")");
  ///Process New Surface :
 PerformNewImplicitFunct();
}

//==================================================/
void k3dsurface::DrawisoTool( ) {
implicitfunct_2->setText(RootObjet.pariso.FunctionsEquations[0]);
minxlimit_2->setText(RootObjet.pariso.xlimitinfsup[0][0]);
minylimit_2->setText(RootObjet.pariso.ylimitinfsup[0][0]);
minzlimit_2->setText(RootObjet.pariso.zlimitinfsup[0][0]);

maxxlimit_2->setText(RootObjet.pariso.xlimitinfsup[1][0]);
maxylimit_2->setText(RootObjet.pariso.ylimitinfsup[1][0]);
maxzlimit_2->setText(RootObjet.pariso.zlimitinfsup[1][0]);

  ///Process New Surface :
 PerformNewToolsImplicitFunct_2();
}

//==================================================/
void k3dsurface::isoloadbutton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
            "",
            tr("k3dsurf files (*.k3ds)"),
            this,
            "open file dialog",
            tr("Please choose the k3dsurf script") );
    if (filename.length()){
       RootObjet.LoadScript(filename, 1);
       Drawiso();
    }
}

//==================================================/
void k3dsurface::LoadIso_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
            "",
            tr("k3dsurf files (*.k3ds)"),
            this,
            "open file dialog",
            tr("Please choose the k3dsurf script") );
    if (filename.length()){
       RootObjet.LoadScript(filename, 1);
       DrawisoTool();
    }
}
//==================================================/
void k3dsurface::cleanbutton_clicked()
{
xcft->setText("");
ycft->setText("");
zcft->setText("");

umin->setText("");
vmin->setText("");

umax->setText("");
vmax->setText("");
}

//==================================================/
void k3dsurface::Drawparam ( ) {
xcft->setText(RootObjet.pariso.XFunctionsEquations[0]);
ycft->setText(RootObjet.pariso.YFunctionsEquations[0]);
zcft->setText(RootObjet.pariso.ZFunctionsEquations[0]);

umin->setText(RootObjet.pariso.ulimitinfsup[0][0]);
vmin->setText(RootObjet.pariso.vlimitinfsup[0][0]);

umax->setText(RootObjet.pariso.ulimitinfsup[1][0]);
vmax->setText(RootObjet.pariso.vlimitinfsup[1][0]);

  // process the new surface
perform();
}

//==================================================/
void k3dsurface::Drawtoolparam( ) {
xtool->setText(RootObjet.pariso.XFunctionsEquations[0]);
ytool->setText(RootObjet.pariso.YFunctionsEquations[0]);
ztool->setText(RootObjet.pariso.ZFunctionsEquations[0]);

umin_tools->setText(RootObjet.pariso.ulimitinfsup[0][0]);
vmin_tools->setText(RootObjet.pariso.vlimitinfsup[0][0]);

umax_tools->setText(RootObjet.pariso.ulimitinfsup[1][0]);
vmax_tools->setText(RootObjet.pariso.vlimitinfsup[1][0]);

  ///Process New Surface :
 reset_changes();
}

//==================================================/
void k3dsurface::cleanpara_clicked()
{
xtool->setText("");
ytool->setText("");
ztool->setText("");

umin_tools->setText("");
vmin_tools->setText("");

umax_tools->setText("");
vmax_tools->setText("");
}

//==================================================/
void k3dsurface::paraloadbutton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
            "",
            tr("k3dsurf files (*.k3ds)"),
            this,
            "open file dialog",
            tr("Please choose the k3dsurf script") );
    if (filename.length()){
       RootObjet.LoadScript(filename, 2);
       Drawparam();
    }
}

//==================================================/
void k3dsurface::loadpara_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
            "",
            tr("k3dsurf files (*.k3ds)"),
            this,
            "open file dialog",
            tr("Please choose the k3dsurf script") );
    if (filename.length()){
       RootObjet.LoadScript(filename, 2);
       Drawtoolparam();
    }
}

//==================================================/
 int IsoMeshOption = 0;
void k3dsurface::checkBox74_clicked()
{  
    isoWidget->IsoObjet->SetMiniMmeshStructStream(isomeshgridname->text(), IsoMeshOption);
}

//==================================================/
void k3dsurface::checkBox75_clicked()
{ /* double maxgr = (isomaxgrid_2->text()).toDouble();
    isoWidget->IsoObjet->SetMinimuMmeshSize(maxgr);*/
}
//==================================================/
void k3dsurface::radioButton8_clicked()
{
IsoMeshOption = 0;
}
//==================================================/
void k3dsurface::radioButton9_clicked()
{
IsoMeshOption = 1;
}
//==================================================/
void k3dsurface::radioButton10_clicked()
{
IsoMeshOption = 2;
}
//==================================================/
void k3dsurface::radioButton11_clicked()
{
IsoMeshOption = 3;
}
//==================================================/
void k3dsurface::isobox_clicked()
{
  IsoGlWidget->isoboxOk();
  UpdateActivatedWin();
}
//==================================================/
void k3dsurface::activate_heightspeed_clicked()
{
    isoWidget->IsoObjet->ActivateHeightSpeedCalculations  *= -1;
    if(isoWidget->IsoObjet->ActivateHeightSpeedCalculations  == 1) 
 groupBox47->setEnabled(TRUE);
    else groupBox47->setEnabled(FALSE);
}

//==================================================/
void k3dsurface::pushButton71_clicked()
{     QMessageBox message ;
    int maxgr = (isomaxgrid->text()).toInt();
    if( maxgr > 500 || maxgr <4) {
    message.setText(tr(QString("Resolution should be  4 < R < 500")));
    message.adjustSize ();
    message.exec();
    }
    else {
 isoWidget->IsoObjet->setmaxgridto(maxgr);
 xyzg->setMaxValue(maxgr);
 isoWidget->IsoObjet->SpecialMorph_3(
         IsoGlWidget->LocalScene.ArrayNorVer_localPt,
         IsoGlWidget->PolyIndices_local,
         IsoGlWidget->NbPolygnNbVertex,
         IsoGlWidget->TypeIsoSurfaceTriangleListeCND,
         &(IsoGlWidget->VertexNumber),
         1);
IsoGlWidget->initializeGL();
IsoGlWidget->PolyNumber  = 3*isoWidget->IsoObjet->NbTriangleIsoSurface;
IsoGlWidget->LocalScene.typedrawing = 1;
IsoGlWidget->updateGL();
    }
}

//==================================================/
void k3dsurface::pushButton71_2_clicked() {
    QMessageBox message ;
    double maxtr = (isomaxtr->text()).toDouble(); maxtr *= 1000000.;
    double maxpt = (isomaxpt->text()).toDouble(); maxpt *= 1000000.;
    if(maxtr > 10000000. || maxpt > 10000000.) {
    message.setText(tr(QString("Resolution should be < 10M")));
    message.adjustSize ();
    message.exec();
    }
    else {
   isoWidget->IsoObjet->ChangeMaxResolution((int)maxtr, (int)maxpt);
   IsoGlWidget->ChangeMaxResolution((int)maxtr, (int)maxpt);
    }
}

//==================================================/
void k3dsurface::SetResolutionTo(int maxgrid, double maxtr1, double maxpt1) {
    QMessageBox message ;
    if(maxgrid >500) {
    message.setText(tr(QString("Resolution should be < 10M")));
    message.adjustSize ();
    message.exec();
    return;
    }

    double maxtr = maxtr1 * 1000000.;
    double maxpt = maxpt1 * 1000000.;
    if(maxtr > 10000000. || maxpt > 10000000.) {
    message.setText(tr(QString("Resolution should be < 10M")));
    message.adjustSize ();
    message.exec();
    }
    else {
   isoWidget->IsoObjet->ChangeMaxResolution((int)maxtr, (int)maxpt);
   IsoGlWidget->ChangeMaxResolution((int)maxtr, (int)maxpt);
   IsoGlWidget->updateGL();
    }
}
//==================================================/
void k3dsurface::SetColorsTo(int *ColorsArray) {
   IsoGlWidget->setColorsTo(ColorsArray);
   ParamGlWidget->setColorsTo(&ColorsArray[12]);
}

//==================================================/
void k3dsurface::f_1_clicked()
{
    FunctionParser fp;
    QMessageBox message ;
    fp.AddConstant("pi", 3.14159265);
    int ret;
    ret = fp.Parse(unaryfct_1->text(), "u");
    if(ret >= 0)
    {
    message.setText(tr(QString("U1(u)--> At col:")+
    QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
    f_1->toggle();
        return ;
    }
    isoWidget->IsoObjet->U1  *= -1;
   isoWidget->IsoObjet->UnaryU1 = unaryfct_1->text();
}

//==================================================/
void k3dsurface::f_2_clicked()
{
    FunctionParser fp;
    QMessageBox message ;
    fp.AddConstant("pi", 3.14159265);
    int ret;
    ret = fp.Parse(unaryfct_2->text(), "u");
    if(ret >= 0)
    {
    message.setText(tr(QString("U2(u)--> At col:")+
    QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
    f_2->toggle();
        return ;
    }
    isoWidget->IsoObjet->U2 *= -1;
   isoWidget->IsoObjet->UnaryU2 = unaryfct_2->text();
}

//==================================================/
void k3dsurface::f_3_clicked()
{
    FunctionParser fp;
    QMessageBox message ;
    fp.AddConstant("pi", 3.14159265);
    int ret;
    ret = fp.Parse(unaryfct_3->text(), "u");
    if(ret >= 0)
    {
    message.setText(tr(QString("U3(u)--> At col:")+
    QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
    f_3->toggle();
        return ;
    }
   isoWidget->IsoObjet->U3 *= -1;
   isoWidget->IsoObjet->UnaryU3 = unaryfct_3->text();
}

//==================================================/
void k3dsurface::f_4_clicked()
{
    FunctionParser fp;
    QMessageBox message ;
    fp.AddConstant("pi", 3.14159265);
    int ret;
    ret = fp.Parse(binaryfct_1->text(), "u,v");
    if(ret >= 0)
    {
    message.setText(tr(QString("B1(u,v)--> At col:")+
    QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
    f_4->toggle();
        return ;
    }
   isoWidget->IsoObjet->B1 *= -1;
   isoWidget->IsoObjet->BinaryB1 = binaryfct_1->text();
}

//==================================================/
void k3dsurface::f_5_clicked()
{
    FunctionParser fp;
    QMessageBox message ;
    fp.AddConstant("pi", 3.14159265);
    int ret;
    ret = fp.Parse(binaryfct_2->text(), "u,v");
    if(ret >= 0)
    {
    message.setText(tr(QString("B2(u,v)--> At col:")+
    QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
    f_5->toggle();
        return ;
    }
   isoWidget->IsoObjet->B2 *= -1;
   isoWidget->IsoObjet->BinaryB2 = binaryfct_2->text();
}


//==================================================/
void k3dsurface::f_6_clicked()
{ 
    FunctionParser fp;
    QMessageBox message ;
    fp.AddConstant("pi", 3.14159265);
    int ret;
    ret = fp.Parse(binaryfct_3->text(), "u,v");
    if(ret >= 0)
    {
    message.setText(tr(QString("B3(u,v)--> At col:")+
    QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
    f_6->toggle();
        return ;
    }
   isoWidget->IsoObjet->B3 *= -1;
   isoWidget->IsoObjet->BinaryB3 = binaryfct_3->text();
}

//==================================================/
void k3dsurface::unaryfct_1_textChanged( const QString & )
{
    if( isoWidget->IsoObjet->U1 == 1) {  isoWidget->IsoObjet->U1 *= -1; f_1->toggle();}
}

//==================================================/
void k3dsurface::unaryfct_2_textChanged( const QString & )
{
    if( isoWidget->IsoObjet->U2 == 1) {  isoWidget->IsoObjet->U2 *= -1; f_2->toggle();}
}

//==================================================/
void k3dsurface::unaryfct_3_textChanged( const QString & )
{
    if( isoWidget->IsoObjet->U3 == 1) {  isoWidget->IsoObjet->U3 *= -1; f_3->toggle();}
}

//==================================================/
void k3dsurface::binaryfct_1_textChanged( const QString & )
{
    if( isoWidget->IsoObjet->B1 == 1) {  isoWidget->IsoObjet->B1 *= -1; f_4->toggle();}
}

//==================================================/
void k3dsurface::binaryfct_2_textChanged( const QString & )
{
    if( isoWidget->IsoObjet->B2 == 1) {  isoWidget->IsoObjet->B2 *= -1; f_5->toggle();}
}

//==================================================/
void k3dsurface::binaryfct_3_textChanged( const QString & )
{
    if( isoWidget->IsoObjet->B3 == 1) {  isoWidget->IsoObjet->B3 *= -1; f_6->toggle();}
}

//==================================================/
void k3dsurface::cleanbutton_2_clicked()
{
implicitfunct->setText("");
}

//==================================================/
void k3dsurface::stoprun_clicked()
{
isoWidget->IsoObjet->stopcalculations();
}

//==================================================/
void k3dsurface::loadtexture_clicked()
{/*
    QString filename = QFileDialog::getOpenFileName(
            "",
            tr("k3dsurf files (*.bmp)"),
            this,
            "open file dialog",
            tr("Please choose the Image file") );
    if (filename.length()){
    int current_pag = tabsurf->currentPageIndex();
    imagename->setText(filename);
    current_pag == 0 ? ParamGlWidget->LoadImage(filename): IsoGlWidget->LoadImage(filename);
       }
*/
}

//==================================================/
void k3dsurface::checkBox83_clicked()
{
    int current_pag = tabsurf->currentPageIndex();
    current_pag == 0 ? ParamGlWidget->ActivateTexture() : IsoGlWidget->ActivateTexture();
}

//==================================================/
void k3dsurface::isonorm_clicked()
{
  IsoGlWidget->normOk();
}

//==================================================/
void k3dsurface::LoadConfig()
{
QString line;
QFile file( "K3DSurfConfig" );

 if ( file.open( IO_ReadOnly ) ) {
        QTextStream stream( &file );
        while ( !stream.atEnd() ) {
            line = stream.readLine(); // line of text excluding '\n'
     if (!line.contains("#")) {
     if (line.contains("ISOMAXPOINTS=")) isomaxpt->setText(line.remove("ISOMAXPOINTS="));
else if (line.contains("ISOMAXTRIANG=")) isomaxtr->setText(line.remove("ISOMAXTRIANG="));
else if (line.contains("ISOMAXGRID="))   isomaxgrid->setText(line.remove("ISOMAXGRID="));
}
                      }
     file.close();
      pushButton71_2_clicked();
      pushButton71_clicked();
    }
else {
  QMessageBox message ;
    message.setText("No Config file...");
    message.adjustSize();
    message.exec();
}
}

//==================================================/
void k3dsurface::OpenConfig()
{
QString line;
QString lines;
    QFile file( "K3DSurfConfig" );
    if ( file.open( IO_ReadOnly ) ) {
        QTextStream stream( &file );
        QString line;
        while ( !stream.atEnd() ) {
            line = stream.readLine(); // line of text excluding '\n'
            lines += line+"\n";
        }
        file.close();
    }
  else {
    QString filename = QFileDialog::getOpenFileName( QString::null, QString::null, this);
    if (filename.length()){
     QFile file( filename );
    if ( file.open( IO_ReadOnly ) ) {
        QTextStream stream( &file );
        while ( !stream.atEnd() ) {
            line = stream.readLine(); // line of text excluding '\n'
            lines += line+"\n";
        }
        file.close();
    }
  }
}

    editeur *ed = new editeur();
    ed->setCaption(tr("Config File"));
    ed->settext(lines);
    ed->show();
}

//==================================================/
void k3dsurface::pushButton80_pressed()
{QString CurrentEquationName;
static QString StaticNames;
static int staticnames =0;
if(staticnames == 0){
StaticNames.append(";Icosahedron;");
StaticNames.append(";pseudo_Duplin;");
StaticNames.append(";pseudo_Torus;");
StaticNames.append(";Bugs;");
StaticNames.append(";DifferenceSpheres;");
StaticNames.append(";BlendSpheres;");
StaticNames.append(";Holes;");
StaticNames.append(";Gyroid;");
StaticNames.append(";Diamand;");
StaticNames.append(";Tetrahedral;");
StaticNames.append(";DuplinCyclides;");
StaticNames.append(";Hyperboloid;");
StaticNames.append(";Hyperbolic;");
StaticNames.append(";Sinus;");	
StaticNames.append(";Octahedron;");
StaticNames.append(";UnionSpheres;");
StaticNames.append(";IntersectSpheres;");
StaticNames.append(";Blobs;");
StaticNames.append(";Virus;");
StaticNames.append(";BlobySchwartz;");
StaticNames.append(";Blobs_2;");
StaticNames.append(";OrthoCircle;");	
StaticNames.append(";CubeSphere;");
StaticNames.append(";CubeSphere_2;");	
StaticNames.append(";Holes_2;");
StaticNames.append(";Virus;");	
StaticNames.append(";Schwartz;");
StaticNames.append(";Schwartz_Morph;");	
StaticNames.append(";Blob_Morph;");
StaticNames.append(";Torus;");	
StaticNames.append(";TwoCylinderBlend;");
StaticNames.append(";BlendThreeCylinder;");	
StaticNames.append(";Sphere;");
StaticNames.append(";RoundCube;");	
StaticNames.append(";Toupie;");
StaticNames.append(";Chmutov;");	
StaticNames.append(";Chmutov_2;");
StaticNames.append(";Clebsch;");
StaticNames.append(";DingDong;");	
StaticNames.append(";Trap;");
StaticNames.append(";Cube;");
StaticNames.append(";Drope;");	
StaticNames.append(";Leminescape;");
StaticNames.append(";Klein;");
StaticNames.append(";Chain;");
StaticNames.append(";Chain_2;");

staticnames = 1;
}

int Currentindex = IsoImplicitBox->currentItem ();
CurrentEquationName = IsoImplicitBox->currentText ();
if(StaticNames.contains( ";"+CurrentEquationName+";") == 0) { RootObjet.EquationsNames.remove(";"+CurrentEquationName+";");
IsoImplicitBox->removeItem (Currentindex);
textLabel1_14_4->setText("Examples ("+QString::number(IsoImplicitBox->count() + 1)+")");
// Update the Isosurface Viewer:
ImplicitFunChanged(IsoImplicitBox->currentText ());
}
}
