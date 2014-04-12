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

#include "IsoPanel.h"

void IsoWidget::png(){png_ok*=-1;}
void IsoWidget::jpg(){jpg_ok*=-1;}
void IsoWidget::bmp(){bmp_ok*=-1;}
void IsoWidget::quality(int c){quality_image = c;}
void IsoWidget::screenshot(){
if(jpg_ok == 1) pixmap->save("ISOscreenshot.jpg", "JPEG", quality_image);
if(png_ok == 1) pixmap->save("ISOscreenshot.png", "PNG" , quality_image);
if(bmp_ok == 1) pixmap->save("ISOscreenshot.bmp", "BMP" , quality_image);
}

///++++++++++++++++++++++++++++++++++++++++++++///
    void IsoWidget::lineOk(){
    IsoObjet->gridtransparent *=-1;
    update();
    }

///++++++++++++++++++++++++++++++++++++++++++++///
void IsoWidget::nbtwistex_changed(int n)
{   oldnb_twistex = n;
    IsoObjet->twistex((double)n/10, (double)oldcoeff_rayonx/10);
    //update();
}

///++++++++++++++++++++++++++++++++++++++++++++///
void IsoWidget::coeffrayonx_changed(int n)
{   oldcoeff_rayonx = n;
    IsoObjet->twistex((double)oldnb_twistex/10, (double)n/10);
    update();
}

///++++++++++++++++++++++++++++++++++++++++++++///
void IsoWidget::nbtwistey_changed(int n)
{   oldnb_twistey = n;
    IsoObjet->twistey((double)n/10, (double)oldcoeff_rayony/10);
    //update();
}

///++++++++++++++++++++++++++++++++++++++++++++///
void IsoWidget::coeffrayony_changed(int n)
{   oldcoeff_rayony = n;
    IsoObjet->twistex((double)oldnb_twistey/10, (double)n/10);
    update();
}

///++++++++++++++++++++++++++++++++++++++++++++///
void IsoWidget::nbtwistez_changed(int n)
{   oldnb_twistez = n;
    IsoObjet->twistez((double)n/10, (double)oldcoeff_rayonz/10);
    //update();
}

///++++++++++++++++++++++++++++++++++++++++++++///
void IsoWidget::coeffrayonz_changed(int n)
{   oldcoeff_rayonz = n;
    IsoObjet->twistez((double)oldnb_twistez/10, (double)n/10);
    update();
}

///++++++++++++++++++++++++++++++++++++++++++++///
void IsoWidget::scalex(int n)
{
    IsoObjet->scalex(n);
    update();
}

///++++++++++++++++++++++++++++++++++++++++++++///
void IsoWidget::scaley(int n)
{
    IsoObjet->scaley(n);
    update();
}

///++++++++++++++++++++++++++++++++++++++++++++///
void IsoWidget::scalez(int n)
{
    IsoObjet->scalez(n);
    update();
}

///++++++++++++++++++++++++++++++++++++++++++++///
void IsoWidget::Axes_draw(){
/*IsoObjet->DrawAxe_Ok *= -1 ;
if(IsoObjet->DrawAxe_Ok == 1) valueChanged();
else update();*/
}

///++++++++++++++++++++++++++++++++++++++++++++///
void  IsoWidget::Axes_center(){
/*IsoObjet->axe_center *= -1 ;
valueChanged();*/
}

///++++++++++++++++++++++++++++++++++++++++++++///
void  IsoWidget::Axes_width(int ){
/*IsoObjet->axe_width = n ;
update();*/
}

///++++++++++++++++++++++++++++++++++++++++++++///
void  IsoWidget::Axes_size(int ){
/*IsoObjet->axe_size = ((double)n)/10. ;
valueChanged();*/
}

///++++++++++++++++++++++++++++++++++++++++++++///
void  IsoWidget::valueChanged(){
/*    IsoObjet->ComputeIsoMap();
    update();*/
}

///++++++++++++++++++++++++++++++++++++++++++++///
void IsoWidget::blue(int cl)
{   switch(colortype) {

    case 0:  IsoObjet->frontsurfb = cl;IsoObjet->PaletteInit();
             update();break;
    case 1:  IsoObjet->backsurfb= cl; IsoObjet->PaletteInit();
             update();break;
    case 4:  IsoObjet->CNDsurfb= cl; IsoObjet->PaletteInit();
             update();break;
    case 2:  IsoObjet->gridb = cl;IsoObjet->PaletteInit();
             update();break;
    case 3:  bluebackground = cl; delete backcolor;
             backcolor = new QColor(redbackground, greenbackground, bluebackground);
             rgbcol =   backcolor->rgb();
             update();break;
};
}

///++++++++++++++++++++++++++++++++++++++++++++///
void IsoWidget::red(int cl)
{   switch(colortype) {

    case 0:  IsoObjet->frontsurfr = cl;IsoObjet->PaletteInit();
             update();break;
    case 1:  IsoObjet->backsurfr= cl; IsoObjet->PaletteInit();
             update();break;
    case 4:  IsoObjet->CNDsurfr= cl; IsoObjet->PaletteInit();
             update();break;
    case 2:  IsoObjet->gridr = cl;IsoObjet->PaletteInit();
             update();break;
    case 3:  redbackground = cl; delete backcolor;
             backcolor = new QColor(redbackground, greenbackground, bluebackground);
             rgbcol =   backcolor->rgb();
             update();break;
};
}

///++++++++++++++++++++++++++++++++++++++++++++///
void IsoWidget::green(int cl)
{   switch(colortype) {

    case 0:  IsoObjet->frontsurfg = cl;IsoObjet->PaletteInit();
             update();break;
    case 1:  IsoObjet->backsurfg= cl; IsoObjet->PaletteInit();
             update();break;
    case 4:  IsoObjet->CNDsurfg= cl; IsoObjet->PaletteInit();
             update();break;
    case 2:  IsoObjet->gridg = cl;IsoObjet->PaletteInit();
             update();break;
    case 3:  greenbackground = cl; delete backcolor;
             backcolor = new QColor(redbackground, greenbackground, bluebackground);
             rgbcol =   backcolor->rgb();
             update();break;
};
}

///++++++++++++++++++++++++++++++++++++++++++++///
void IsoWidget::transparence()
{
      switch(colortype) {
    case 0:  IsoObjet->fronttrans *= -1;IsoObjet->PaletteInit();
             update();break;
    case 1:  IsoObjet->backtrans  *= -1;IsoObjet->PaletteInit();
             update();break;
    case 4:  IsoObjet->CNDtrans   *= -1;IsoObjet->PaletteInit();
             update();break;
    case 2:  IsoObjet->gridtransparent  *= -1;
             update();break;
};
}

///+++++++++++++++++++++++++++++++++++++++++++++
void  IsoWidget::IsoAnim(){
anim_ok *=-1;
if(anim_ok == 1) if( morph_ok != 1) start();
else   if( morph_ok !=1)  wait();

};

///+++++++++++++++++++++++++++++++++++++++++++++
void  IsoWidget::IsoMorph(){
morph_ok *=-1;
if(morph_ok == 1)  if( anim_ok != 1) start();
else   if( anim_ok !=1)  wait();
};

///+++++++++++++++++++++++++++++++++++++++++++++
void  IsoWidget::start(){
QThread::start();
};

///+++++++++++++++++++++++++++++++++++++++++++++
void IsoWidget::run(){

        while( anim_ok == 1 || morph_ok == 1 ) {
        msleep(latence);
        if(anim_ok  == 1) {
           if(morph_ok == 1) IsoObjet->AnimMorph();/// The two of them
           else IsoObjet->RotateIsoMap(); /// Only rotation
                          }
        else    IsoObjet->ComputeIsoMap(); /// Only morph
        update();
        }
}

///+++++++++++++++++++++++++++++++++++++++++++++++
void IsoWidget::step_morph(int cl)
{   IsoObjet->step = (double)1/(double)cl;
    update();
}

///+++++++++++++++++++++++++++++++++++++++++++++++
void IsoWidget::latence_change(int cl)
{   latence = cl;
    update();
}
///+++++++++++++++++++++++++++++++++++++++++++++++
/// The use of mutex doesn't help to fix the crash problems...
void IsoWidget::MorphThreadSafe(){
        mutex.lock();
        IsoObjet->AnimMorph();update();
        mutex.unlock();
};

///+++++++++++++++++++++++++++++++++++++++++++++++
void IsoWidget::CutLineIsoSurface(int cl){
    IsoObjet->CutLigne = cl;
    IsoObjet->CutIsoSurface();
    update();
};

///+++++++++++++++++++++++++++++++++++++++++++++++
void IsoWidget::CutColonIsoSurface(int cl){
    IsoObjet->CutColon = cl;
    IsoObjet->CutIsoSurface();
    update();
};

///+++++++++++++++++++++++++++++++++++++++++++++++
void IsoWidget::CutDepthIsoSurface(int cl){
    IsoObjet->CutDepth = cl;
    IsoObjet->CutIsoSurface();
    update();
};

///+++++++++++++++++++++++++++++++++++++++++++++++
void IsoWidget::CutIsoSurface(int cl){
    IsoObjet->CutDepth = IsoObjet->CutColon = IsoObjet->CutLigne = cl;
    IsoObjet->CutIsoSurface();
    update();
};

///+++++++++++++++++++++++++++++++++++++++++++++++
void IsoWidget::XGridChanged(int cl)
{
    IsoObjet->nb_ligne = cl;
    IsoObjet->ComputeIsoMap();
    update();
}

///+++++++++++++++++++++++++++++++++++++++++++++++
void IsoWidget::YGridChanged(int cl)
{
    IsoObjet->nb_colon = cl;
    IsoObjet->ComputeIsoMap();
    update();
}

///+++++++++++++++++++++++++++++++++++++++++++++++
void IsoWidget::ZGridChanged(int cl)
{
    IsoObjet->nb_depth = cl;
    IsoObjet->ComputeIsoMap();
    update();
}

///+++++++++++++++++++++++++++++++++++++++++++++++
void IsoWidget::XYZGridChanged(int cl)
{
    IsoObjet->nb_depth = IsoObjet->nb_colon = IsoObjet->nb_ligne = cl;
    IsoObjet->ComputeIsoMap();
    update();
}
///+++++++++++++++++++++++++++++++++++++++++++++++
void IsoWidget::IsoMorphCompute(){

IsoObjet->ComputeIsoMap();
update();

};
void IsoWidget::initcontrols() {
    oldcoeff_rayonz = 10; oldnb_twistez = 0;
    oldcoeff_rayony = 10; oldnb_twistey = 0;
    oldcoeff_rayonx = 10; oldnb_twistex = 0;
}
///+++++++++++++++++++++++++++++++++++++++++++++++
IsoWidget::IsoWidget(QWidget *parent, const char *name)
    : QWidget( parent, name, WNoAutoErase)
{   width = 650;
    height = 650;
    latence = 50;
    oldcoeff_rayonz = 10; oldnb_twistez = 0;
    oldcoeff_rayony = 10; oldnb_twistey = 0;
    oldcoeff_rayonx = 10; oldnb_twistex = 0;
    anim_ok = morph_ok = -1;
    setWindowOpacity (0);
    pixmap = new QPixmap(650,650);
    setFixedSize ( width, height);
    IsoObjet = new Iso3D();
    greenbackground=0; bluebackground=0; redbackground=0;
    backcolor = new QColor(redbackground, greenbackground, bluebackground);
    rgbcol = backcolor->rgb();
    colortype = 0;
    png_ok = 1; jpg_ok = bmp_ok = -1; quality_image = 50;
    //ThreadStoped = -1;
};

///+++++++++++++++++++++++++++++++++++++++++++++++
IsoWidget::~IsoWidget(){
delete IsoObjet;
delete pixmap;
}

///+++++++++++++ Mousse Events +++++++++++++++++++
///+++++++++++++++++++++++++++++++++++++++++++++++
void IsoWidget::paintEvent(QPaintEvent*)
{   pixmap->fill(rgbcol);
    QPainter painter(pixmap, this);
    painter.setClipRect(0, 0, width, height);
    IsoObjet->DrawIsoMap(painter);
    bitBlt(this, 0, 0, pixmap, 0, 0, width, height);
}

///+++++++++++++++++++++++++++++++++++++++++++++++
void IsoWidget::mousePressEvent( QMouseEvent * e)
{
    if ( e->button() == QMouseEvent::LeftButton ) btgauche = 1;
    else btgauche = 0;
    if ( e->button() == QMouseEvent::RightButton ) btdroit = 1;
    else btdroit = 0;
    if ( e->button() == QMouseEvent::MidButton ) btmilieu = 1;
    else btmilieu = 0;

    IsoObjet->ancienx = e->y();
    IsoObjet->ancieny = e->x();
}

///+++++++++++++++++++++++++++++++++++++++++++++++
void IsoWidget::mouseReleaseEvent( QMouseEvent *)
{

}

///+++++++++++++++++++++++++++++++++++++++++++++++
void IsoWidget::mouseMoveEvent( QMouseEvent *e )
{
     IsoObjet->anglex = (IsoObjet->ancienx - (double)e->y());
     IsoObjet->angley = (IsoObjet->ancieny - (double)e->x()) ;

     IsoObjet->ancienx = (double)e->y();
     IsoObjet->ancieny = (double)e->x();

  if(btgauche==1) IsoObjet->RotateIsoMap();

  if(btdroit==1)  {
     if(IsoObjet->anglex > 0 ) IsoObjet->ScalCoeff = 1.1f;
     else  IsoObjet->ScalCoeff = 0.90f;
     IsoObjet->ScaleIsoMap();
                  }

   update();
}

///+++++++++++++++++++++++++++++++++++++++++++++++
void IsoWidget::keyPressEvent ( QKeyEvent *) {
/*
if(morph_ok == 1 || anim_ok ==1)  {
ThreadStoped *= -1;
wait();
}
*/
}

///+++++++++++++++++++++++++++++++++++++++++++++++
/*void IsoWidget::keyReleaseEvent ( QKeyEvent *) {

if(ThreadStoped == 1) {
ThreadStoped *= -1;
start();
};

}
*/
