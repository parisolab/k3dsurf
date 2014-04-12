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

#include "panel.h"


//========================================//
void ConnectWidget::nbcoilz_changed(int n)
{   oldnb_coilz = n;
//if ( coilzactivated == 1){
    //objet->coilz((double)n/10, (double)oldcoeff_rayon_coilz/10);
    objet->twistez((double)n/10, (double)oldcoeff_rayon_coilz/10);
 //   if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1)
 update();
//}
}
//========================================//
void ConnectWidget::coeffrayon_coilz_changed(int n)
{   oldcoeff_rayon_coilz = n;
//if ( coilzactivated == 1){
    //objet->coilz((double)oldnb_coilz/10, (double)n/10);
    objet->twistez((double)oldnb_coilz/10, (double)n/10);
  //  if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1)
  update();
//}
}


//========================================//
void ConnectWidget::nbcoily_changed(int n)
{   oldnb_coily = n;
//if ( coilzactivated == 1){
    //objet->coily((double)n/10, (double)oldcoeff_rayon_coily/10);
    objet->twistey((double)n/10, (double)oldcoeff_rayon_coily/10);
   // if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1)
   update();
//}
}
//========================================//
void ConnectWidget::coeffrayon_coily_changed(int n)
{   oldcoeff_rayon_coily = n;
//if ( coilzactivated == 1){
    //objet->coily((double)oldnb_coily/10, (double)n/10);
    objet->twistey((double)oldnb_coily/10, (double)n/10);
   // if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
   update();
//}
}

//========================================//
void ConnectWidget::nbcoilx_changed(int n)
{   oldnb_coilx = n;
//if ( coilzactivated == 1){
    //objet->coilx((double)n/10, (double)oldcoeff_rayon_coilx/10);
    objet->twistex((double)n/10, (double)oldcoeff_rayon_coilx/10);
    if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
    update();
//}
}
//========================================//
void ConnectWidget::coeffrayon_coilx_changed(int n)
{   oldcoeff_rayon_coilx = n;
//if ( coilzactivated == 1){
    //objet->coilx((double)oldnb_coilx/10, (double)n/10);
    objet->twistex((double)oldnb_coilx/10, (double)n/10);
    if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1)
    update();
//}
}


//======================================//
void ConnectWidget::Draw_Normals(){
  draw_poly_normals *= -1;
  objet->draw_poly_normals = draw_poly_normals;
if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
  update();
}

//======================================//
void ConnectWidget::Axes_draw(){
objet->drawaxes_ok *= -1 ;
if(objet->drawaxes_ok == 1) valueChanged();
else update();
}

//======================================//
void  ConnectWidget::Axes_center(){
objet->axe_center *= -1 ;
if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
valueChanged(); 
//update();// not necessery because of valuechanged() update already...
}

//======================================//
void  ConnectWidget::Axes_width(int n){
objet->axe_width = n ;
if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
update();
}

//======================================//
void  ConnectWidget::Axes_size(int n){
objet->axe_size = ((double)n)/10. ;
if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
valueChanged(); 
//update(); // not necessery because of valuechanged() update already...
}
















//========================================//
void ConnectWidget::save_changes()
{
objet->expression_X_save = objet->expression_X;
objet->expression_Y_save = objet->expression_Y;
objet->expression_Z_save = objet->expression_Z;



objet->MINX_save = objet->MINX;
objet->DIFX_save = objet->DIFX;

objet->MINY_save = objet->MINY;
objet->DIFY_save = objet->DIFY;

objet->MINZ_save = objet->MINZ;
objet->DIFZ_save = objet->DIFZ;

}
//========================================//
void ConnectWidget::nbtwistez_changed(int n)
{   oldnb_twistez = n;
//if ( twistezactivated == 1){
    objet->twistez((double)n/10, (double)oldcoeff_rayonz/10);
 //   if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) update();
//}
}
//========================================//
void ConnectWidget::coeffrayonz_changed(int n)
{   oldcoeff_rayonz = n;
//if ( twistezactivated == 1){     
    objet->twistez((double)oldnb_twistez/10, (double)n/10);    
  //  if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) update();
//}
}


//========================================//
void ConnectWidget::nbtwistey_changed(int n)
{   oldnb_twistey = n;
//if ( twistezactivated == 1){
    objet->twistey((double)n/10, (double)oldcoeff_rayony/10);
   // if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) update();
//}
}
//========================================//
void ConnectWidget::coeffrayony_changed(int n)
{   oldcoeff_rayony = n;
//if ( twistezactivated == 1){
    objet->twistey((double)oldnb_twistey/10, (double)n/10);
   // if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) update();
//}
}


//========================================//
void ConnectWidget::nbtwistex_changed(int n)
{   oldnb_twistex = n;
//if ( twistezactivated == 1){
    objet->twistex((double)n/10, (double)oldcoeff_rayonx/10);
    //if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) update();
//}
}
//========================================//
void ConnectWidget::coeffrayonx_changed(int n)
{   oldcoeff_rayonx = n;
//if ( twistezactivated == 1){
    objet->twistex((double)oldnb_twistex/10, (double)n/10);
    //if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) update();
//}
}

//========================================//
void ConnectWidget::scalex(int n)
{
//if ( scalexactivated == 1){
    objet->scalex(n);
    //oldScale_x = n;
    if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
    update();
//}
}
//========================================//
void ConnectWidget::scaley(int n)
{
//if (scaleyactivated == 1){
    objet->scaley(n);
    //oldScale_y = n;
    if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
    update();
//}
}
//========================================//
void ConnectWidget::scalez(int n)
{
//if (scalezactivated == 1){
    objet->scalez(n);
    //oldScale_z = n;
    if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
    update();
//}
}

//========================================//
void ConnectWidget::activescalex()
{
scalexactivated *= -1;
}

//========================================//
void ConnectWidget::activescaley()
{
scaleyactivated *= -1;
}

//========================================//
void ConnectWidget::activescalez()
{
scalezactivated *= -1;
}

//====================================
void ConnectWidget::addcondt(){

     add_condition*= -1;
     objet->draw_hidden_poly_and_nonhidden = add_condition;
if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
update();

}

//====================================

void ConnectWidget::meshcondt(){

    condition_mesh *= -1;
    objet->draw_cond_mesh = condition_mesh;
if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
update();

}
//========================================//
void ConnectWidget::help(){
objet->showhelp *= -1;
if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
update();
}
//========================================//
void ConnectWidget::start(){

QThread::start();

}

//========================================//
// This is for Windows
void ConnectWidget::run(){

        while( anim_ok == 1 || morph_ok == 1 || anim4_ok == 1 || anim5_ok == 1 ) {
        msleep(latence);
	if(anim5_ok  == 1) {
	if(objet->sixdimshapes ==1) objet->fct_bouton_Anim6 ();
	else objet->fct_bouton_Anim5 ();
	}	 
	else 
	if(anim4_ok  == 1) objet->fct_bouton_Anim4 ();
	else 
	if(anim_ok  == 1)  if(morph_ok == 1) objet->fct_bouton_AnimMorph();
                            else objet->fct_bouton_Anim3();
        else    objet->fct_bouton_Morph3();
        QApplication::sendEvent(this,me);
         //  update();
        }
}

//========================================//
ConnectWidget::ConnectWidget( QWidget *parent, const char *name)
    : QWidget( parent, name, WNoAutoErase)
{   width = 650;
    height = 650;
    //setBackgroundColor( black );    // black background

    setWindowOpacity ( 0);
    pixmap = new QPixmap(650,650);
    setFixedSize ( width, height);
    objet = new Model3D();
    taillechanged = -1;
    anim_ok  = -1;
    anim4_ok = -1;
    anim5_ok = -1;
    morph_ok = -1;
    latence = 30;
    colortype = 0;
    video_ok = -1;

    counter = 0;

    png_ok =  1;
    jpg_ok = -1;
    bmp_ok = -1;
    quality_image = 50;

    jpg2_ok =  1;
    png2_ok = -1;
    bmp2_ok = -1;
    quality_image2 = 50;
    frames_ok   = -1;
    short_names = -1;
    big_names   =  1;
    directory = "frames";
    condition_mesh = 1;
    add_condition  =-1;

    r = new QRegion(0,0,4,4) ;    //MAKE IT GLOBAL VARIABLE
    me = new QPaintEvent(*r, TRUE);

    oldScale_x = oldScale_y = oldScale_z = 10;
    scalexactivated = -1; scaleyactivated = -1; scalezactivated = -1;
    twistezactivated = -1;
    coeff_rayonz = 10; nb_twistez = 0; oldcoeff_rayonz = 10; oldnb_twistez = 0;
    coeff_rayony = 10; nb_twistey = 0; oldcoeff_rayony = 10; oldnb_twistey = 0;
    coeff_rayonx = 10; nb_twistex = 0; oldcoeff_rayonx = 10; oldnb_twistex = 0;
    draw_poly_normals = -1;
    greenbackground=0; bluebackground=0; redbackground=0;
    backcolor = new QColor(redbackground, greenbackground, bluebackground);
    rgbcol = backcolor->rgb();
}

//========================================//
ConnectWidget::~ConnectWidget()
{
delete objet;
delete pixmap;
}
//========================================//
void ConnectWidget::morph(){
if(anim4_ok == 1) {
   QMessageBox message ;
    message.setText(tr(QString("Deactivate 4D Rotation")));
    message.adjustSize () ;
    message.exec();
        return ;

}
else {
morph_ok *=-1;
if(morph_ok == 1)  if( anim_ok != 1) start();
else   if( anim_ok !=1)  wait();
}
}
//========================================//
void ConnectWidget::anim(){
if(anim4_ok == 1) {
    QMessageBox message ;
    message.setText(tr(QString("Deactivate 4D Rotation")));
    message.adjustSize () ;
    message.exec();
        return ;
}
else {
anim_ok *=-1;
if(anim_ok == 1)  if( morph_ok != 1) start();
else   if( morph_ok !=1)  wait();
}
}

//========================================//
void ConnectWidget::anim4xy(){

if(anim_ok == 1 || morph_ok == 1) {
    QMessageBox message ;
    message.setText(tr(QString("Deactivate 3D Rotation/Morph")));
    message.adjustSize () ;
    message.exec();
        return ;
}
else {
if(anim4_ok == -1) {
anim4_ok = 1;
objet->tetaxy_ok *= -1;
start();
}
else {
objet->tetaxy_ok *= -1;
if(objet->tetaxy_ok == -1 &&
   objet->tetaxz_ok == -1 &&
   objet->tetayz_ok == -1 &&
   objet->tetaxw_ok == -1 &&
   objet->tetayw_ok == -1 &&
   objet->tetazw_ok == -1) { anim4_ok = -1; wait();}
}
}

}

//========================================//
void ConnectWidget::anim4xz(){

if(anim_ok == 1 || morph_ok == 1) {
    QMessageBox message ;
    message.setText(tr(QString("Deactivate 3D Rotation/Morph")));
    message.adjustSize () ;
    message.exec();
        return ;
}
else {
if(anim4_ok == -1) {
anim4_ok = 1;
objet->tetaxz_ok *= -1;
start();
}
else {
objet->tetaxz_ok *= -1;
if(objet->tetaxy_ok == -1 && 
   objet->tetaxz_ok == -1 && 
   objet->tetayz_ok == -1 &&

   objet->tetaxw_ok == -1 &&
   objet->tetayw_ok == -1 &&
   objet->tetazw_ok == -1) { anim4_ok = -1; wait();}
}
}
}
//========================================//
void ConnectWidget::anim4yz(){

if(anim_ok == 1 || morph_ok == 1) {
    QMessageBox message ;
    message.setText(tr(QString("Deactivate 3D Rotation/Morph")));
    message.adjustSize () ;
    message.exec();
        return ;
}
else {
if(anim4_ok == -1) {
anim4_ok = 1;
objet->tetayz_ok *= -1;
start();
}
else {
objet->tetayz_ok *= -1;
if(objet->tetaxy_ok == -1 && 
   objet->tetaxz_ok == -1 && 
   objet->tetayz_ok == -1 &&  

   objet->tetaxw_ok == -1 && 
   objet->tetayw_ok == -1 && 
   objet->tetazw_ok == -1) { anim4_ok = -1; wait();}
}
}
}
//========================================//
void ConnectWidget::anim4xw(){

if(anim_ok == 1 || morph_ok == 1) {
    QMessageBox message ;
    message.setText(tr(QString("Deactivate 3D Rotation/Morph")));
    message.adjustSize () ;
    message.exec();
        return ;
}
else {

if(anim4_ok == -1) {
anim4_ok = 1;
objet->tetaxw_ok *= -1;
start();
}
else {
objet->tetaxw_ok *= -1;
if(objet->tetaxy_ok == -1 && 
   objet->tetaxz_ok == -1 && 
   objet->tetayz_ok == -1 &&

   objet->tetaxw_ok == -1 && 
   objet->tetayw_ok == -1 && 
   objet->tetazw_ok == -1
   ) { anim4_ok = -1; wait();}
}
}
}
//========================================//
void ConnectWidget::anim4yw(){

if(anim_ok == 1 || morph_ok == 1) {
    QMessageBox message ;
    message.setText(tr(QString("Deactivate 3D Rotation/Morph")));
    message.adjustSize () ;
    message.exec();
        return ;
}
else {
if(anim4_ok == -1) {
anim4_ok = 1;
objet->tetayw_ok *= -1;
start();
}
else {
objet->tetayw_ok *= -1;
if(objet->tetaxy_ok == -1 && 
   objet->tetaxz_ok == -1 && 
   objet->tetayz_ok == -1 &&

   objet->tetaxw_ok == -1 && 
   objet->tetayw_ok == -1 && 
   objet->tetazw_ok == -1
   ) { anim4_ok = -1; wait();}
}
}
}
//========================================//
void ConnectWidget::anim4zw(){

if(anim_ok == 1 || morph_ok == 1) {
    QMessageBox message ;
    message.setText(tr(QString("Deactivate 3D Rotation/Morph")));
    message.adjustSize () ;
    message.exec();
        return ;
}
else {
if(anim4_ok == -1) {
anim4_ok = 1;
objet->tetazw_ok *= -1;
start();
}
else {
objet->tetazw_ok *= -1;
if(objet->tetaxy_ok == -1 && 
   objet->tetaxz_ok == -1 && 
   objet->tetayz_ok == -1 &&

   objet->tetaxw_ok == -1 && 
   objet->tetayw_ok == -1 && 
   objet->tetazw_ok == -1
   ) { anim4_ok = -1; wait();}
}
}
}



//============= xy 5D rotations ===============//
void ConnectWidget::anim5xy(){

if(anim_ok == 1 || morph_ok == 1 || anim4_ok == 1) {
    QMessageBox message ;
    message.setText(tr(QString("Deactivate 3D/4D  Rotation/Morph")));
    message.adjustSize () ;
    message.exec();
        return ;
}
else {
if(anim5_ok == -1) {
anim5_ok = 1;
objet->tetaxy_ok *= -1;
start();
}
else {
objet->tetaxy_ok *= -1;
if(objet->tetaxy_ok == -1 && 
   objet->tetaxz_ok == -1 && 
   objet->tetayz_ok == -1 && 
   objet->tetaxw_ok == -1 && 
   objet->tetayw_ok == -1 && 
   objet->tetazw_ok == -1 &&
   objet->tetaxt_ok == -1 &&
   objet->tetayt_ok == -1 &&
   objet->tetazt_ok == -1 &&
   objet->tetawt_ok == -1 && 
   objet->tetaxs_ok == -1 &&
   objet->tetays_ok == -1 &&
   objet->tetazs_ok == -1 &&
   objet->tetaws_ok == -1 &&
   objet->tetats_ok == -1 ) { anim5_ok = -1; wait();}
}
}

}
//============= xz 5D rotations ===============//
void ConnectWidget::anim5xz(){

if(anim_ok == 1 || morph_ok == 1 || anim4_ok == 1) {
    QMessageBox message ;
    message.setText(tr(QString("Deactivate 3D/4D  Rotation/Morph")));
    message.adjustSize () ;
    message.exec();
        return ;
}
else {
if(anim5_ok == -1) {
anim5_ok = 1;
objet->tetaxz_ok *= -1;
start();
}
else {
objet->tetaxz_ok *= -1;
if(objet->tetaxy_ok == -1 &&
   objet->tetaxz_ok == -1 &&
   objet->tetayz_ok == -1 &&
   objet->tetaxw_ok == -1 &&
   objet->tetayw_ok == -1 &&
   objet->tetazw_ok == -1 &&
   objet->tetaxt_ok == -1 &&
   objet->tetayt_ok == -1 &&
   objet->tetazt_ok == -1 &&
   objet->tetawt_ok == -1 &&
   objet->tetaxs_ok == -1 &&
   objet->tetays_ok == -1 &&
   objet->tetazs_ok == -1 &&
   objet->tetaws_ok == -1 &&
   objet->tetats_ok == -1 ) { anim5_ok = -1; wait();}
}
}

}
//============= xw 5D rotations ===============//
void ConnectWidget::anim5xw(){

if(anim_ok == 1 || morph_ok == 1 || anim4_ok == 1) {
    QMessageBox message ;
    message.setText(tr(QString("Deactivate 3D/4D  Rotation/Morph")));
    message.adjustSize () ;
    message.exec();
        return ;
}
else {
if(anim5_ok == -1) {
anim5_ok = 1;
objet->tetaxw_ok *= -1;
start();
}
else {
objet->tetaxw_ok *= -1;
if(objet->tetaxy_ok == -1 && 
   objet->tetaxz_ok == -1 &&
   objet->tetayz_ok == -1 &&
   objet->tetaxw_ok == -1 &&
   objet->tetayw_ok == -1 &&
   objet->tetazw_ok == -1 &&
   objet->tetaxt_ok == -1 &&
   objet->tetayt_ok == -1 &&
   objet->tetazt_ok == -1 &&
   objet->tetawt_ok == -1 &&
   objet->tetaxs_ok == -1 &&
   objet->tetays_ok == -1 &&
   objet->tetazs_ok == -1 &&
   objet->tetaws_ok == -1 &&
   objet->tetats_ok == -1 ) { anim5_ok = -1; wait();}
}
}

}
//============= xt 5D rotations ===============//
void ConnectWidget::anim5xt(){

if(anim_ok == 1 || morph_ok == 1 || anim4_ok == 1) {
    QMessageBox message ;
    message.setText(tr(QString("Deactivate 3D/4D  Rotation/Morph")));
    message.adjustSize () ;
    message.exec();
        return ;
}
else {
if(anim5_ok == -1) {
anim5_ok = 1;
objet->tetaxt_ok *= -1;
start();
}
else {
objet->tetaxt_ok *= -1;
if(objet->tetaxy_ok == -1 && 
   objet->tetaxz_ok == -1 && 
   objet->tetayz_ok == -1 &&
   objet->tetaxw_ok == -1 &&
   objet->tetayw_ok == -1 &&
   objet->tetazw_ok == -1 &&
   objet->tetaxt_ok == -1 &&
   objet->tetayt_ok == -1 &&
   objet->tetazt_ok == -1 &&
   objet->tetawt_ok == -1 &&
   objet->tetaxs_ok == -1 &&
   objet->tetays_ok == -1 &&
   objet->tetazs_ok == -1 &&
   objet->tetaws_ok == -1 &&
   objet->tetats_ok == -1 ) { anim5_ok = -1; wait();}
}
}

}


//============= yz 5D rotations ===============//
void ConnectWidget::anim5yz(){

if(anim_ok == 1 || morph_ok == 1 || anim4_ok == 1) {
    QMessageBox message ;
    message.setText(tr(QString("Deactivate 3D/4D  Rotation/Morph")));
    message.adjustSize () ;
    message.exec();
        return ;
}
else {
if(anim5_ok == -1) {
anim5_ok = 1;
objet->tetayz_ok *= -1;
start();
}
else {
objet->tetayz_ok *= -1;
if(objet->tetaxy_ok == -1 && 
   objet->tetaxz_ok == -1 && 
   objet->tetayz_ok == -1 &&
   objet->tetaxw_ok == -1 &&
   objet->tetayw_ok == -1 &&
   objet->tetazw_ok == -1 &&
   objet->tetaxt_ok == -1 &&
   objet->tetayt_ok == -1 &&
   objet->tetazt_ok == -1 &&
   objet->tetawt_ok == -1 &&
   objet->tetaxs_ok == -1 &&
   objet->tetays_ok == -1 &&
   objet->tetazs_ok == -1 &&
   objet->tetaws_ok == -1 &&
   objet->tetats_ok == -1 ) { anim5_ok = -1; wait();}
}
}
}

//============= yw 5D rotations ===============//
void ConnectWidget::anim5yw(){

if(anim_ok == 1 || morph_ok == 1 || anim4_ok == 1) {
    QMessageBox message ;
    message.setText(tr(QString("Deactivate 3D/4D  Rotation/Morph")));
    message.adjustSize () ;
    message.exec();
        return ;
}
else {
if(anim5_ok == -1) {
anim5_ok = 1;
objet->tetayw_ok *= -1;
start();
}
else {
objet->tetayw_ok *= -1;
if(objet->tetaxy_ok == -1 &&
   objet->tetaxz_ok == -1 &&
   objet->tetayz_ok == -1 &&
   objet->tetaxw_ok == -1 &&
   objet->tetayw_ok == -1 &&
   objet->tetazw_ok == -1 &&
   objet->tetaxt_ok == -1 &&
   objet->tetayt_ok == -1 &&
   objet->tetazt_ok == -1 &&
   objet->tetawt_ok == -1 &&
   objet->tetaxs_ok == -1 &&
   objet->tetays_ok == -1 &&
   objet->tetazs_ok == -1 &&
   objet->tetaws_ok == -1 &&
   objet->tetats_ok == -1 ) { anim5_ok = -1; wait();}
}
}
}

//============= yt 5D rotations ===============//
void ConnectWidget::anim5yt(){

if(anim_ok == 1 || morph_ok == 1 || anim4_ok == 1) {
    QMessageBox message ;
    message.setText(tr(QString("Deactivate 3D/4D  Rotation/Morph")));
    message.adjustSize () ;
    message.exec();
        return ;
}
else {
if(anim5_ok == -1) {
anim5_ok = 1;
objet->tetayt_ok *= -1;
start();
}
else {
objet->tetayt_ok *= -1;
if(objet->tetaxy_ok == -1 &&
   objet->tetaxz_ok == -1 &&
   objet->tetayz_ok == -1 &&
   objet->tetaxw_ok == -1 &&
   objet->tetayw_ok == -1 &&
   objet->tetazw_ok == -1 &&
   objet->tetaxt_ok == -1 &&
   objet->tetayt_ok == -1 &&
   objet->tetazt_ok == -1 &&
   objet->tetawt_ok == -1 &&
   objet->tetaxs_ok == -1 &&
   objet->tetays_ok == -1 &&
   objet->tetazs_ok == -1 &&
   objet->tetaws_ok == -1 &&
   objet->tetats_ok == -1 ) { anim5_ok = -1; wait();}
}
}
}

//============= zw 5D rotations ===============//
void ConnectWidget::anim5zw(){

if(anim_ok == 1 || morph_ok == 1 || anim4_ok == 1) {
    QMessageBox message ;
    message.setText(tr(QString("Deactivate 3D/4D  Rotation/Morph")));
    message.adjustSize () ;
    message.exec();
        return ;
}
else {
if(anim5_ok == -1) {
anim5_ok = 1;
objet->tetazw_ok *= -1;
start();
}
else {
objet->tetazw_ok *= -1;
if(objet->tetaxy_ok == -1 && 
   objet->tetaxz_ok == -1 && 
   objet->tetayz_ok == -1 &&
   objet->tetaxw_ok == -1 &&
   objet->tetayw_ok == -1 &&
   objet->tetazw_ok == -1 &&
   objet->tetaxt_ok == -1 &&
   objet->tetayt_ok == -1 &&
   objet->tetazt_ok == -1 &&
   objet->tetawt_ok == -1 &&
   objet->tetaxs_ok == -1 &&
   objet->tetays_ok == -1 &&
   objet->tetazs_ok == -1 &&
   objet->tetaws_ok == -1 &&
   objet->tetats_ok == -1 ) { anim5_ok = -1; wait();}
}
}
}

//============= zt 5D rotations ===============//
void ConnectWidget::anim5zt(){

if(anim_ok == 1 || morph_ok == 1 || anim4_ok == 1) {
    QMessageBox message ;
    message.setText(tr(QString("Deactivate 3D/4D  Rotation/Morph")));
    message.adjustSize () ;
    message.exec();
        return ;
}
else {
if(anim5_ok == -1) {
anim5_ok = 1;
objet->tetazt_ok *= -1;
start();
}
else {
objet->tetazt_ok *= -1;
if(objet->tetaxy_ok == -1 && 
   objet->tetaxz_ok == -1 && 
   objet->tetayz_ok == -1 &&  
   objet->tetaxw_ok == -1 && 
   objet->tetayw_ok == -1 && 
   objet->tetazw_ok == -1 &&
   objet->tetaxt_ok == -1 &&
   objet->tetayt_ok == -1 &&
   objet->tetazt_ok == -1 &&
   objet->tetawt_ok == -1 && 
   objet->tetaxs_ok == -1 &&
   objet->tetays_ok == -1 &&
   objet->tetazs_ok == -1 &&
   objet->tetaws_ok == -1 &&
   objet->tetats_ok == -1 ) { anim5_ok = -1; wait();}
}
}
}
//============= zt 5D rotations ===============//
void ConnectWidget::anim5wt(){

if(anim_ok == 1 || morph_ok == 1 || anim4_ok == 1) {
    QMessageBox message ;  
    message.setText(tr(QString("Deactivate 3D/4D  Rotation/Morph")));
    message.adjustSize () ;
    message.exec();   
        return ; 
}
else {
if(anim5_ok == -1) {
anim5_ok = 1;
objet->tetawt_ok *= -1;
start();
}
else {
objet->tetawt_ok *= -1;
if(objet->tetaxy_ok == -1 && 
   objet->tetaxz_ok == -1 && 
   objet->tetayz_ok == -1 &&  
   objet->tetaxw_ok == -1 && 
   objet->tetayw_ok == -1 && 
   objet->tetazw_ok == -1 &&
   objet->tetaxt_ok == -1 &&
   objet->tetayt_ok == -1 &&
   objet->tetazt_ok == -1 &&
   objet->tetawt_ok == -1 && 
   objet->tetaxs_ok == -1 &&
   objet->tetays_ok == -1 &&
   objet->tetazs_ok == -1 &&
   objet->tetaws_ok == -1 &&
   objet->tetats_ok == -1 ) { anim5_ok = -1; wait();}
}
}
}


//============= zt 5D rotations ===============//
void ConnectWidget::animND(int n){

if(anim_ok == 1 || morph_ok == 1 || anim4_ok == 1) {
    QMessageBox message ;  
    message.setText(tr(QString("Deactivate 3D/4D  Rotation/Morph")));
    message.adjustSize () ;
    message.exec();   
        return ; 
}
else {

switch(n)  {
case 1  : objet->tetaxy_ok *= -1;break;
case 2  : objet->tetaxy_ok *= -1;break;
case 3  : objet->tetaxz_ok *= -1;break;
case 4  : objet->tetaxw_ok *= -1;break;
case 5  : objet->tetayw_ok *= -1;break;
case 6  : objet->tetazw_ok *= -1;break;
case 7  : objet->tetaxt_ok *= -1;break;
case 8  : objet->tetayt_ok *= -1;break;
case 9  : objet->tetazt_ok *= -1;break;
case 10 : objet->tetawt_ok *= -1;break;
case 11 : objet->tetaxs_ok *= -1;break;
case 12 : objet->tetays_ok *= -1;break;
case 13 : objet->tetazs_ok *= -1;break;
case 14 : objet->tetaws_ok *= -1;break;
case 15 : objet->tetats_ok *= -1;break;
}
if(anim5_ok == -1) {
anim5_ok = 1;
start();
}
else {

if(objet->tetaxy_ok == -1 && 
   objet->tetaxz_ok == -1 && 
   objet->tetayz_ok == -1 &&  
   objet->tetaxw_ok == -1 && 
   objet->tetayw_ok == -1 && 
   objet->tetazw_ok == -1 &&
   objet->tetaxt_ok == -1 &&
   objet->tetayt_ok == -1 &&
   objet->tetazt_ok == -1 &&
   objet->tetawt_ok == -1 && 
   objet->tetaxs_ok == -1 &&
   objet->tetays_ok == -1 &&
   objet->tetazs_ok == -1 &&
   objet->tetaws_ok == -1 &&
   objet->tetats_ok == -1 ) { anim5_ok = -1; wait();}
}
}
}


void ConnectWidget::anim6xs(){
animND(11);
}
void ConnectWidget::anim6ys(){
animND(12);
}
void ConnectWidget::anim6zs(){
animND(13);
}
void ConnectWidget::anim6ws(){
animND(14);
}
void ConnectWidget::anim6ts(){
animND(15);
}










//========================================//
void ConnectWidget::anglexy(int cl)
{   
    objet->tetaxy = cl;

    //update();
}
//========================================//
void ConnectWidget::anglexz(int cl)
{   
    objet->tetaxz = cl;

    //update();
}

//========================================//
void ConnectWidget::angleyz(int cl)
{   
    objet->tetayz = cl;

    //update();
}
//========================================//
void ConnectWidget::anglexw(int cl)
{   
    objet->tetaxw = cl;

    //update();
}
//========================================//
void ConnectWidget::angleyw(int cl)
{   
    objet->tetayw = cl;

    //update();
}
//========================================//
void ConnectWidget::anglezw(int cl)
{   
    objet->tetazw = cl;

    //update();
}



// special 5D
//========================================//
void ConnectWidget::anglext(int cl)
{   
    objet->tetaxt = cl;

    //update();
}
//========================================//
void ConnectWidget::angleyt(int cl)
{   
    objet->tetayt = cl;

    //update();
}
//========================================//
void ConnectWidget::anglezt(int cl)
{   
    objet->tetazt = cl;

    //update();
}
//========================================//
void ConnectWidget::anglewt(int cl)
{   
    objet->tetawt = cl;

    //update();
}

//========================================//
void ConnectWidget::anglexs(int cl)
{   
    objet->tetaxs = cl;

    //update();
}
//========================================//
void ConnectWidget::angleys(int cl)
{   
    objet->tetays = cl;

    //update();
}
//========================================//
void ConnectWidget::anglezs(int cl)
{   
    objet->tetazs = cl;

    //update();
}
//========================================//
void ConnectWidget::anglews(int cl)
{
    objet->tetaws = cl;

    //update();
}
//========================================//
void ConnectWidget::anglets(int cl)
{
    objet->tetats = cl;

    //update();
}

//========================================//
void ConnectWidget::cutline(int cl)
{
    objet->coupure_ligne = cl;

   if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1)
   update();
}
//========================================//
void ConnectWidget::step_morph(int cl)
{
    objet->step = (double)1/(double)cl;
    if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
    update();
}

//========================================//
void ConnectWidget::latence_change(int cl)
{
    latence = cl;
    objet->latence = cl;
    if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1)    
    update();
}
//========================================//
void ConnectWidget::zbuffer_quality_change(int cl)
{
    objet->zbuffer_quality = cl;
    if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1)
    update();
}
//========================================//
void ConnectWidget::zbuffer_activate()
{
    objet->zbuffer_active_ok  *= -1;
    if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1)
    update();
}
//========================================//
void ConnectWidget::linecolumn(int cl)
{
    objet->nb_licol = cl;
    objet->nb_colone = cl;
    objet->nb_ligne = cl;
    objet->fct_bouton_Morph3();
    if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1)
    update();
}
//========================================//
void ConnectWidget::cutcolumn(int cl)
{   objet->coupure_col = cl;
    if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1)
    update();
}
//========================================//
void ConnectWidget::red(int cl)
{   switch(colortype) {

    case 0:  objet->frontsurfr = cl;objet->initialiser_palette();
        if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
        update();break;
    case 1:  objet->backsurfr = cl;objet->initialiser_palette();    
        if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
        update();break;
    case 2:  objet->gridliner = cl;objet->initialiser_palette();
        if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
        update();break;
    /*case 3:  objet->backgroundr = cl;objet->initialiser_palette();
        if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
        update();break;*/
    case 3:  redbackground = cl; delete backcolor; 
        backcolor = new QColor(redbackground, greenbackground, bluebackground);
        rgbcol =   backcolor->rgb();
        if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
        update();break;
};

}

//========================================//
void ConnectWidget::green(int cl)
{   switch(colortype) {

    case 0:  objet->frontsurfg = cl;objet->initialiser_palette();
        if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
	update();break;
    case 1:  objet->backsurfg= cl;objet->initialiser_palette();
        if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
	update();break;
    case 2:  objet->gridlineg = cl; objet->initialiser_palette();
        if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
	update();break;
    /*case 3:  objet->backgroundg = cl; objet->initialiser_palette();
        if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
	update();break;*/
    case 3:  greenbackground = cl; delete backcolor; 
        backcolor = new QColor(redbackground, greenbackground, bluebackground);
        rgbcol =   backcolor->rgb();
        if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1)
        update();break;
};

}
//========================================//
void ConnectWidget::blue(int cl)
{   switch(colortype) {

    case 0:  objet->frontsurfb = cl;objet->initialiser_palette();
        if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
             update();break;
    case 1:  objet->backsurfb= cl; objet->initialiser_palette();
        if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
             update();break;
    case 2:  objet->gridlineb = cl;objet->initialiser_palette();
        if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
             update();break;
    /*case 3:  objet->backgroundb = cl;objet->initialiser_palette();
        if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
       update();break;*/
    case 3:  bluebackground = cl; delete backcolor; 
        backcolor = new QColor(redbackground, greenbackground, bluebackground);
        rgbcol =   backcolor->rgb();
        if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1)
        update();break;
};

}
//========================================//
void ConnectWidget::transparence()
{
      switch(colortype) {
    case 0:  objet->fronttrans *= -1;objet->initialiser_palette();
        if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
             update();break;
    case 1:  objet->backtrans  *= -1;objet->initialiser_palette();
        if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
             update();break;
};

}
//========================================//
void ConnectWidget::valueChanged_2() {
objet->fct_calcul2();
}
//========================================//
void ConnectWidget::valueChanged() {
objet->fct_calcul3();

    if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
    update();

}
//========================================//
void ConnectWidget::newFile()
{
    objet->mesh *= -1;
    if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
    update();
}
//========================================//
void ConnectWidget::boxok()
{
    objet->box *= -1;
    if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
    update();
}

//====================================

void ConnectWidget::interior(){

    objet->interior_surface *= -1;
    if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
    update();
}
//====================================

void ConnectWidget::exterior(){

    objet->exterior_surface *= -1;
    if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
    update();
}

//========================================//
void ConnectWidget::infosok()
{
    objet->infos *= -1;
    if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
    update();
}
//========================================//
void ConnectWidget::clipok()
{
    objet->clipping *= -1;
    if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
    update();
}

//========================================//
void ConnectWidget::setFunction(int fct) {


if(fct == 0 ) {
objet->two_system = 1;

objet->expression_X = "(3*(1+sin(v)) + 2*(1-cos(v)/2)*cos(u))*cos(v)"; 
objet->expression_Y = "(4+2*(1-cos(v)/2)*cos(u))*sin(v)"; 
objet->expression_Z = "-2*(1-cos(v)/2) * sin(u)"; 
objet->inf_u = "0"; 
objet->sup_u = "2*pi"; 
objet->inf_v = "0"; 
objet->sup_v = "pi";

objet->expression_X_2 = "3*(1+sin(v))*cos(v) - 2*(1-cos(v)/2)*cos(u)"; 
objet->expression_Y_2 = "4*sin(v)"; 
objet->expression_Z_2 = "-2*(1-cos(v)/2)* sin(u)"; 
objet->inf_u_2 = "0"; 
objet->sup_u_2 = "2*pi"; 
objet->inf_v_2 = "pi"; 
objet->sup_v_2 = "2*pi";

}


objet->fct_calcul3();

    if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
    update();

}

//========================================//
void ConnectWidget::videorecord(){
/*
    if(video_ok == 1) {
    counter = 0;
    f  = new QFile("movie.png" );
    f->open(IO_WriteOnly;
    pngfile = new QPNGImagePacker( f, 8,8) ;
    }
    else {
    video_ok = -1; // to stop video recording.
    f->close();
    }
*/
}
//========================================//

void ConnectWidget::screenshot(){

if(jpg_ok == 1) pixmap->save("PARscreenshot.jpg", "JPEG", quality_image);
if(png_ok == 1) pixmap->save("PARscreenshot.png", "PNG" , quality_image);
if(bmp_ok == 1) pixmap->save("PARscreenshot.bmp", "BMP" , quality_image);
}

//========================================//
void ConnectWidget::png(){
png_ok*=-1;
}
//========================================//
void ConnectWidget::jpg(){
jpg_ok*=-1;
}
//========================================//
void ConnectWidget::bmp(){
bmp_ok*=-1;
}

//========================================//
void ConnectWidget::quality(int c){
quality_image = c;
}

//========================================//
void ConnectWidget::png2(){
png2_ok*=-1;
}

//========================================//
void ConnectWidget::jpg2(){
jpg2_ok*=-1;
}

//========================================//
void ConnectWidget::bmp2(){
bmp2_ok*=-1;
QString commande;
/*
QMessageBox message ;
QDir dir("frames");
if( !dir.exists()) {
    message.setText(tr(QString("Creation of the directory: frames")));
    message.adjustSize () ;
    message.exec();

system("mkdir "+Input_Dir_NameEdit->text());
if(dir.mkdir("frames", TRUE)) {
    message.setText(tr(QString("SUcces")));
    message.adjustSize () ;
    message.exec();

};

}

*/

/*

QMessageBox message ;
QDir dir(directory);
if( !dir.exists()) { 
    message.setText(tr(QString("Creation of the directory: "+directory)));
    message.adjustSize () ;
    message.exec(); 
//system("mkdir "+Input_Dir_NameEdit->text());
dir.mkdir(directory, TRUE);
}

*/
}

//========================================//
void ConnectWidget::quality2(int c){
quality_image2 = c;
}

//========================================//
void ConnectWidget::activate_frame(){
frames_ok *= -1;
}

//========================================//
void ConnectWidget::frame_name_short(){
short_names *= -1;
}

//========================================//
void ConnectWidget::frame_name_big(){
big_names *= -1;
}

//========================================//
//
// Handles paint events for the connect widget.
//

void ConnectWidget::paintEvent(QPaintEvent* e)
{

if (e-> spontaneous() == TRUE && (anim5_ok == 1 || anim4_ok == 1 || anim_ok == 1 || morph_ok == 1) ) {}
else {

pixmap->fill(rgbcol);
QPainter painter(pixmap, this); 

painter.setClipRect(0, 0, width, height);

objet->tracer3(painter);



if((video_ok == 1 || frames_ok == 1 ) && counter < 100){

// this part is for the set of Frames

if(frames_ok == 1) {

if(short_names == 1) {
if(jpg2_ok == 1 )pixmap->save(directory+"/Frame"+QString::number(counter)+".jpg", "JPEG", quality_image2);
if(png2_ok == 1 )pixmap->save(directory+"/Frame"+QString::number(counter)+".png", "PNG", quality_image2);
if(bmp2_ok == 1 )pixmap->save(directory+"/Frame"+QString::number(counter)+".bmp", "BMP", quality_image2);
                     }

if(big_names == 1) {

        if(counter<10) {
if(jpg2_ok == 1) pixmap->save(directory+"/Frame0"+QString::number(counter)+".jpg", "JPEG", quality_image2);
if(png2_ok == 1) pixmap->save(directory+"/Frame0"+QString::number(counter)+".png", "PNG", quality_image2);
if(bmp2_ok == 1) pixmap->save(directory+"/Frame0"+QString::number(counter)+".bmp", "BMP", quality_image2);
                       }

        else {
if(jpg2_ok == 1) pixmap->save(directory+"/Frame"+QString::number(counter)+".jpg", "JPEG", quality_image2);
if(png2_ok == 1) pixmap->save(directory+"/Frame"+QString::number(counter)+".png", "PNG", quality_image2);
if(bmp2_ok == 1) pixmap->save(directory+"/Frame"+QString::number(counter)+".bmp", "BMP", quality_image2);
             }

}

}

//this part is for PNG movies
/*
if(video_ok == 1) {

pngfile->packImage(pixmap->convertToImage());

}
*/
// this is just for security to prevent hardrive saturation

counter++;
}

bitBlt(this, 0, 0, pixmap, 0, 0, width, height);

}





}


//========================================//
//
// Handles mouse press events for the connect widget.
//

void ConnectWidget::mousePressEvent( QMouseEvent * e)
{
    if ( e->button() == QMouseEvent::LeftButton ) btgauche = 1;
    else btgauche = 0;
    if ( e->button() == QMouseEvent::RightButton ) btdroit = 1;
    else btdroit = 0;
    if ( e->button() == QMouseEvent::MidButton ) btmilieu = 1;
    else btmilieu = 0;

    objet->ancienx = e->y();
    objet->ancieny = e->x();
/*
    objet->nb_CurvePoints++;
    objet->CurvePointsXY[0][objet->nb_CurvePoints] = e->x();
    objet->CurvePointsXY[1][objet->nb_CurvePoints] = e->y();
*/
}


//========================================//
//
// Handles mouse release events for the connect widget.
//

void ConnectWidget::mouseReleaseEvent( QMouseEvent * )
{

}

//========================================//
//
// Handles mouse move events for the connect widget.
//

void ConnectWidget::mouseMoveEvent( QMouseEvent *e )
{

     objet->anglex = (objet->ancienx - (double)e->y());
     objet->angley = (objet->ancieny - (double)e->x()) ;

     objet->ancienx = (double)e->y();
     objet->ancieny = (double)e->x();

 if(btgauche==1) objet->fct_bouton_gauche3();

  if(btdroit==1)  {
     if(objet->anglex > 0 ) objet->coefficient = 1.1f;

     else  objet->coefficient = 0.90f;

     objet->fct_bouton_droit3();
                  }

  if(btmilieu == 1) objet->fct_bouton_milieu3();
   if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
   update();
}

//========================================//
//
// Handles mouse move events for the connect widget.
//

void ConnectWidget::keyPressEvent ( QKeyEvent * e ) {

//std::cout << e->text();
objet->keyboard = e->text();
   if (anim5_ok != 1 && anim4_ok != 1 && anim_ok != 1 && morph_ok != 1) 
   update();

}


