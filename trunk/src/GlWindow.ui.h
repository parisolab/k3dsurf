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
#include <qevent.h>


void GlWindow::keyPressEvent ( QKeyEvent * e ) {
int key = e->key();
switch(key) {
case Qt::Key_A : glWidget->anim();break;
case Qt::Key_P : glWidget->morph();break;
}
glWidget->update();
       }
///*****************************************************************///
void GlWindow::resizeEvent( QResizeEvent  *e )
{
  QSize qs = e->size();
  QSize qsold = e->oldSize();
  double ancien_hauteur = (double)glWidget->height;
  double ancien_largeur = (double)glWidget->width;

   glWidget->width  = qs.width();
   glWidget->height = qs.height();
   glWidget->setFixedSize (qs.width() , qs.height());

   if(ancien_hauteur < ancien_largeur)
     glWidget->scalcoeff(glWidget->height/(double)ancien_hauteur);
   else glWidget->scalcoeff(glWidget->width/(double)ancien_largeur);
   //isoWidget->IsoObjet->ScaleIsoMap();

   glWidget->update();
   //update();
        };

