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
#include "Model3D.h"
#include "edit.h"





using std::string;
//
// ConnectWidget - draws connected lines
//


class ConnectWidget : public QWidget, public QThread
{
Q_OBJECT
public:
    ConnectWidget( QWidget *parent=0, const char *name=0);
   ~ConnectWidget();
    void valueChanged();
    void valueChanged_2(); /// the same than "valueChanged" but without drawing
    virtual void run();
protected:
    void	paintEvent( QPaintEvent * );
    void	mousePressEvent( QMouseEvent *);
    void	mouseReleaseEvent( QMouseEvent *);
    void	mouseMoveEvent( QMouseEvent *);
    void        keyPressEvent ( QKeyEvent *);
public slots:
    void newFile();
    void setFunction(int);
    void cutline(int);
    void cutcolumn(int);
    void linecolumn(int);
    void boxok();
    void anim();
    void addcondt();
    void meshcondt();

    void anim4xy();  //4D rotation
    void anim4xz();  //4D rotation
    void anim4yz();  //4D rotation
    void anim4xw();  //4D rotation
    void anim4yw();  //4D rotation
    void anim4zw();  //4D rotation

    void anglexy(int);  //4D rotation
    void anglexz(int);  //4D rotation
    void angleyz(int);  //4D rotation
    void anglexw(int);  //4D rotation
    void angleyw(int);  //4D rotation
    void anglezw(int);  //4D rotation
    void anglext(int);  //5D rotation
    void angleyt(int);  //5D rotation
    void anglezt(int);  //5D rotation
    void anglewt(int);  //5D rotation
    void anglexs(int);  //6D rotation
    void angleys(int);  //6D rotation
    void anglezs(int);  //6D rotation
    void anglews(int);  //6D rotation
    void anglets(int);  //6D rotation

    void anim5xy();  //5D rotation
    void anim5xt();  //5D rotation
    void anim5xz();  //5D rotation
    void anim5yz();  //5D rotation
    void anim5xw();  //5D rotation
    void anim5yw();  //5D rotation
    void anim5zw();  //5D rotation
    void anim5yt();  //5D rotation
    void anim5zt();  //5D rotation
    void anim5wt();  //5D rotation

    void anim6xs();  //6D rotation
    void anim6ys();  //6D rotation
    void anim6zs();  //6D rotation
    void anim6ws();  //6D rotation
    void anim6ts();  //6D rotation

    void animND(int );  // Multi purpose fct for rotational plans
    void help();
    void morph();
    void start();
    void clipok();
    void infosok();
    void latence_change(int);
    void step_morph(int);
    void red(int);
    void green(int);
    void blue(int);
    void transparence();
    void interior();
    void exterior();
    void videorecord();
    void screenshot();
    void jpg();
    void bmp();
    void png();
    void quality(int);
    void jpg2();
    void bmp2();
    void png2();
    void quality2(int);
    void activate_frame();
    void frame_name_short();
    void frame_name_big();
    void zbuffer_activate();
    void zbuffer_quality_change(int);

    void scalex(int);
    void scaley(int);
    void scalez(int);
    void activescalex();
    void activescaley();
    void activescalez();

    void nbtwistez_changed(int);
    void coeffrayonz_changed(int);

    void nbtwistey_changed(int);
    void coeffrayony_changed(int);

    void nbtwistex_changed(int);
    void coeffrayonx_changed(int);


    void nbcoilz_changed(int);
    void coeffrayon_coilz_changed(int);

    void nbcoily_changed(int);
    void coeffrayon_coily_changed(int);

    void nbcoilx_changed(int);
    void coeffrayon_coilx_changed(int);

    void save_changes();
    void Draw_Normals();
    void Axes_draw();
    void Axes_center();
    void Axes_width(int);
    void Axes_size(int);

public:
    QPoint     *points;// point array
    QColor     *colors;// color array
    int count, anim_ok, anim4_ok, anim5_ok, morph_ok, taillechanged;// count = number of points
    bool	down;   // TRUE if mouse down
    Model3D    *objet;
    QPixmap * pixmap;
    int btgauche, btdroit, btmilieu, width, height, latence, colortype, video_ok;
    QPixmap * alpha;
    int png_ok, jpg_ok, bmp_ok,
        png2_ok, jpg2_ok, bmp2_ok,
        quality_image, quality_image2, 
        counter, frames_ok, short_names, big_names,
        oldScale_x, oldScale_y, oldScale_z, 
        scalexactivated, scaleyactivated, scalezactivated,
        twistezactivated,
        coeff_rayonz, nb_twistez, oldcoeff_rayonz, oldnb_twistez,
        coeff_rayony, nb_twistey, oldcoeff_rayony, oldnb_twistey,
        coeff_rayonx, nb_twistex, oldcoeff_rayonx, oldnb_twistex,
        coeff_rayon_coilz, nb_coilz, oldcoeff_rayon_coilz, oldnb_coilz,
        coeff_rayon_coily, nb_coily, oldcoeff_rayon_coily, oldnb_coily,
        coeff_rayon_coilx, nb_coilx, oldcoeff_rayon_coilx, oldnb_coilx,
        draw_poly_normals,
        greenbackground, bluebackground, redbackground;
    QColor *backcolor;
    QRgb rgbcol;
    QFile *f;
    //QPNGImagePacker *pngfile;
    QString directory;
    int condition_mesh, add_condition;
    QRegion  *r;    //MAKE IT GLOBAL VARIABLE
    QPaintEvent *me;
};

