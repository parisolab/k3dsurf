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


/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/
#include <qevent.h>

//========================================//
//
// Handles mouse move events for the connect widget.
//



void newwindow2::keyPressEvent ( QKeyEvent * e ) {
//QString key;
//newwindow->objet->keyboard = e->text();

int key = e->key();

switch(key) {
case Qt::Key_H : newwindow->help();break;
case Qt::Key_A : newwindow->anim();break;
case Qt::Key_P : newwindow->morph();break;
case Qt::Key_M : newwindow->objet->mesh *=-1;break;
case Qt::Key_B : newwindow->objet->box *=-1;break;
case Qt::Key_I : newwindow->objet->infos *=-1;break;
case Qt::Key_C : newwindow->objet->clipping *=-1;break;
case Qt::Key_Left: if(newwindow->objet->coupure_col < newwindow->objet->nb_colone)  newwindow->objet->coupure_col++ ;break;
case Qt::Key_Right: if(newwindow->objet->coupure_col >0) 
newwindow->objet->coupure_col-- ;break;

case Qt::Key_Down: if(newwindow->objet->coupure_ligne < newwindow->objet->nb_ligne)  newwindow->objet->coupure_ligne++ ;break;
case Qt::Key_Up: if(newwindow->objet->coupure_ligne >0) 
newwindow->objet->coupure_ligne-- ;break;

case Qt::Key_Prior: 
if(newwindow->objet->nb_ligne < 95){
newwindow->objet->nb_ligne++ ;
newwindow->objet->nb_colone++ ;
newwindow->objet->fct_bouton_Morph3();
}
break;

case Qt::Key_Next: 
if(newwindow->objet->nb_ligne > 0){
newwindow->objet->nb_ligne-- ;
newwindow->objet->nb_colone-- ;
newwindow->objet->fct_bouton_Morph3();
}
break;

}

newwindow->update();
}


void newwindow2::resizeEvent( QResizeEvent  *e )
{
QSize qs = e->size();QSize qsold = e->oldSize();
  double ancien_hauteur = (double)newwindow->objet->demi_hauteur;
  double ancien_largeur = (double)newwindow->objet->demi_largeur;

   newwindow->width  = qs.width();
   newwindow->height = qs.height(); 
   newwindow->setFixedSize (qs.width() , qs.height());
   //newwindow->taillechanged = 1;
   delete newwindow->pixmap;
   newwindow->pixmap = new QPixmap(qs.width(), qs.height());

   newwindow->objet->demi_hauteur = (qs.width())/2;
   newwindow->objet->demi_largeur = (qs.height())/2;

   if(newwindow->objet->demi_hauteur < newwindow->objet->demi_largeur)
     newwindow->objet->coefficient = newwindow->objet->demi_hauteur/(double)ancien_hauteur;
   else newwindow->objet->coefficient = newwindow->objet->demi_largeur/(double)ancien_largeur;
   newwindow->objet->fct_bouton_droit3();

   newwindow->update();
   //update();
}

