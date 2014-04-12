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
#include <qthread.h>
#include <qmutex.h>
#include <qpixmap.h>
#include <qwidget.h>
#include <qpainter.h>
#include <qapplication.h>
#include <qmessagebox.h>
#include <qfile.h> 
#include <qdir.h> 
#include <qpngio.h> 
#include <stdlib.h>
#include <string>
#include "Iso3D.h"
#include "edit.h"

class IsoWidget : public QWidget, public QThread
{
Q_OBJECT
public:
    IsoWidget( QWidget *parent=0, const char *name=0);
   ~IsoWidget();
    void valueChanged();
    virtual void run();

protected:
    void        paintEvent( QPaintEvent * );
    void        mousePressEvent( QMouseEvent *);
    void        mouseReleaseEvent( QMouseEvent *);
    void        mouseMoveEvent( QMouseEvent *);
    void        keyPressEvent ( QKeyEvent *);

public slots:
    void IsoAnim();
    void IsoMorph();
    void start();
    void IsoMorphCompute();
    void XGridChanged (int);
    void YGridChanged (int);
    void ZGridChanged (int);
    void XYZGridChanged (int);
    void CutLineIsoSurface(int);
    void CutColonIsoSurface(int);
    void CutDepthIsoSurface(int);
    void CutIsoSurface(int);
    void MorphThreadSafe();
    void red(int);
    void blue(int);
    void green(int);
    void transparence();
    void latence_change(int);
    void step_morph(int);
    void Axes_center();
    void Axes_width(int);
    void Axes_size(int);
    void Axes_draw();

    void screenshot();
    void png();
    void jpg();
    void bmp();
    void quality(int);

    void scalex(int);
    void scaley(int);
    void scalez(int);

    void nbtwistex_changed(int);
    void coeffrayonx_changed(int);
    void nbtwistey_changed(int);
    void coeffrayony_changed(int);
    void nbtwistez_changed(int);
    void coeffrayonz_changed(int);
    void initcontrols();
    void lineOk();

public :
    int       btgauche, btdroit, btmilieu, width, height,
              morph_ok, anim_ok, latence, greenbackground,
              bluebackground, redbackground, colortype,
              oldcoeff_rayonx, oldnb_twistex,
              oldcoeff_rayony, oldnb_twistey,
              oldcoeff_rayonz, oldnb_twistez;
    int jpg_ok, png_ok, bmp_ok, quality_image;
    Iso3D   * IsoObjet;
    QPixmap * pixmap;
    QMutex mutex;
    QColor *backcolor;
    QRgb rgbcol;
};


