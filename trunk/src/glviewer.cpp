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
//#include <GL/glext.h>
#include <iostream>
#include "glviewer.h"
#include <qfont.h>
#include "edit.h"
#include <qtextedit.h>
#if defined(Q_CC_MSVC)
#pragma warning(disable:4305) // init: truncation from const double to float
#endif
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
GLubyte rasters[][13] = {
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x36, 0x36, 0x36},
{0x00, 0x00, 0x00, 0x66, 0x66, 0xff, 0x66, 0x66, 0xff, 0x66, 0x66, 0x00, 0x00},
{0x00, 0x00, 0x18, 0x7e, 0xff, 0x1b, 0x1f, 0x7e, 0xf8, 0xd8, 0xff, 0x7e, 0x18},
{0x00, 0x00, 0x0e, 0x1b, 0xdb, 0x6e, 0x30, 0x18, 0x0c, 0x76, 0xdb, 0xd8, 0x70},
{0x00, 0x00, 0x7f, 0xc6, 0xcf, 0xd8, 0x70, 0x70, 0xd8, 0xcc, 0xcc, 0x6c, 0x38},
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1c, 0x0c, 0x0e},
{0x00, 0x00, 0x0c, 0x18, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0c},
{0x00, 0x00, 0x30, 0x18, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x18, 0x30},
{0x00, 0x00, 0x00, 0x00, 0x99, 0x5a, 0x3c, 0xff, 0x3c, 0x5a, 0x99, 0x00, 0x00},
{0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18, 0x00, 0x00},
{0x00, 0x00, 0x30, 0x18, 0x1c, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x60, 0x60, 0x30, 0x30, 0x18, 0x18, 0x0c, 0x0c, 0x06, 0x06, 0x03, 0x03},
{0x00, 0x00, 0x3c, 0x66, 0xc3, 0xe3, 0xf3, 0xdb, 0xcf, 0xc7, 0xc3, 0x66, 0x3c},
{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x38, 0x18},
{0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0xe7, 0x7e},
{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0x07, 0x03, 0x03, 0xe7, 0x7e},
{0x00, 0x00, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0xff, 0xcc, 0x6c, 0x3c, 0x1c, 0x0c},
{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xff},
{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
{0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x03, 0x03, 0xff},
{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e},
{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x03, 0x7f, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e},
{0x00, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x30, 0x18, 0x1c, 0x1c, 0x00, 0x00, 0x1c, 0x1c, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06},
{0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60},
{0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x18, 0x0c, 0x06, 0x03, 0xc3, 0xc3, 0x7e},
{0x00, 0x00, 0x3f, 0x60, 0xcf, 0xdb, 0xd3, 0xdd, 0xc3, 0x7e, 0x00, 0x00, 0x00},
{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18},
{0x00, 0x00, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
{0x00, 0x00, 0x7e, 0xe7, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
{0x00, 0x00, 0xfc, 0xce, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xce, 0xfc},
{0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0xff},
{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xff},
{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xcf, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e},
{0x00, 0x00, 0x7c, 0xee, 0xc6, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
{0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xe0, 0xf0, 0xd8, 0xcc, 0xc6, 0xc3},
{0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0},
{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xdb, 0xff, 0xff, 0xe7, 0xc3},
{0x00, 0x00, 0xc7, 0xc7, 0xcf, 0xcf, 0xdf, 0xdb, 0xfb, 0xf3, 0xf3, 0xe3, 0xe3},
{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e},
{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
{0x00, 0x00, 0x3f, 0x6e, 0xdf, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c},
{0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0xe0, 0xc0, 0xc0, 0xe7, 0x7e},
{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff},
{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
{0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
{0x00, 0x00, 0xc3, 0xe7, 0xff, 0xff, 0xdb, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
{0x00, 0x00, 0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
{0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x7e, 0x0c, 0x06, 0x03, 0x03, 0xff},
{0x00, 0x00, 0x3c, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3c},
{0x00, 0x03, 0x03, 0x06, 0x06, 0x0c, 0x0c, 0x18, 0x18, 0x30, 0x30, 0x60, 0x60},
{0x00, 0x00, 0x3c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x3c},
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x66, 0x3c, 0x18},
{0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x38, 0x30, 0x70},
{0x00, 0x00, 0x7f, 0xc3, 0xc3, 0x7f, 0x03, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0},
{0x00, 0x00, 0x7e, 0xc3, 0xc0, 0xc0, 0xc0, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x7f, 0xc3, 0xc3, 0xc3, 0xc3, 0x7f, 0x03, 0x03, 0x03, 0x03, 0x03},
{0x00, 0x00, 0x7f, 0xc0, 0xc0, 0xfe, 0xc3, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x30, 0x33, 0x1e},
{0x7e, 0xc3, 0x03, 0x03, 0x7f, 0xc3, 0xc3, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0},
{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x18, 0x00},
{0x38, 0x6c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x0c, 0x00},
{0x00, 0x00, 0xc6, 0xcc, 0xf8, 0xf0, 0xd8, 0xcc, 0xc6, 0xc0, 0xc0, 0xc0, 0xc0},
{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78},
{0x00, 0x00, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xfe, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xfc, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00},
{0xc0, 0xc0, 0xc0, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0x00, 0x00, 0x00, 0x00},
{0x03, 0x03, 0x03, 0x7f, 0xc3, 0xc3, 0xc3, 0xc3, 0x7f, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe0, 0xfe, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0xfe, 0x03, 0x03, 0x7e, 0xc0, 0xc0, 0x7f, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x1c, 0x36, 0x30, 0x30, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x30, 0x00},
{0x00, 0x00, 0x7e, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0xc3, 0xe7, 0xff, 0xdb, 0xc3, 0xc3, 0xc3, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0xc3, 0x66, 0x3c, 0x18, 0x3c, 0x66, 0xc3, 0x00, 0x00, 0x00, 0x00},
{0xc0, 0x60, 0x60, 0x30, 0x18, 0x3c, 0x66, 0x66, 0xc3, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0xff, 0x60, 0x30, 0x18, 0x0c, 0x06, 0xff, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x0f, 0x18, 0x18, 0x18, 0x38, 0xf0, 0x38, 0x18, 0x18, 0x18, 0x0f},
{0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
{0x00, 0x00, 0xf0, 0x18, 0x18, 0x18, 0x1c, 0x0f, 0x1c, 0x18, 0x18, 0x18, 0xf0},
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x8f, 0xf1, 0x60, 0x00, 0x00, 0x00}
};
static int heightresult, widthresult;
static double anglefinal=0;
static QString nbl="", nbc, nbd;
static int CornerH, CornerW;
//static int TranspVal = -1;
static GLfloat staticcolor[20]={
//Green(Back face)
0.0,0.7,0.0,1.0,
//Gold (Front face)
249./255.,170./255.,0.0,1.0,
// grid:
0.1,0.4,0.1,1.0,
//Background:
0.0,0.0,0.0,1.0,
//Condition:
1.0,0.2,0.0,1.0
}; // greencol, goldcol,...
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::setColorsTo(int *){

};

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::RunPovscript(int){
    int i, a1, a2, a3, a4,
    NbTriangles   = (int)(LocalScene.PolyNumber/3),
	NbTriangles_2 = (int)(LocalScene.PolyNumber/4);
    float focal = asin(5./7.)*360./4.1; 
    glGetDoublev(GL_MODELVIEW_MATRIX,LocalScene.matrix);
    float M11=LocalScene.matrix[0], M21=LocalScene.matrix[1], M31=LocalScene.matrix[2],
          M12=LocalScene.matrix[4], M22=LocalScene.matrix[5], M32=LocalScene.matrix[6],
          M13=LocalScene.matrix[8], M23=LocalScene.matrix[9], M33=LocalScene.matrix[10];
    QString strstream;
    QTextStream stream(&strstream, IO_ReadWrite);

stream <<"mesh { \n";
/// In this case, we have Isosurface triangles:
if (LocalScene.typedrawing == 1)
    for(i=0;i<NbTriangles; i++) {
a1 = LocalScene.PolyIndices_localPt[3*i  ];
a2 = LocalScene.PolyIndices_localPt[3*i+1];
a3 = LocalScene.PolyIndices_localPt[3*i+2];

stream <<"smooth_triangle {<"<<LocalScene.ArrayNorVer_localPt[a1*6+3]<<", "<<LocalScene.ArrayNorVer_localPt[a1*6+4]<<", "<<LocalScene.ArrayNorVer_localPt[a1*6+5]<<">, ";
stream <<"<"<<LocalScene.ArrayNorVer_localPt[a1*6]<<", "<< LocalScene.ArrayNorVer_localPt[a1*6+1]<<", "<<LocalScene.ArrayNorVer_localPt[a1*6+2]<<">,\n";

stream <<"<"<<LocalScene.ArrayNorVer_localPt[a2*6+3]<<", "<<LocalScene.ArrayNorVer_localPt[a2*6+4]<<", "<<LocalScene.ArrayNorVer_localPt[a2*6+5]<<">, ";
stream <<"<"<<LocalScene.ArrayNorVer_localPt[a2*6]<<", "<< LocalScene.ArrayNorVer_localPt[a2*6+1]<<", "<<LocalScene.ArrayNorVer_localPt[a2*6+2]<<">,\n";

stream <<"<"<<LocalScene.ArrayNorVer_localPt[a3*6+3]<<", "<<LocalScene.ArrayNorVer_localPt[a3*6+4]<<", "<<LocalScene.ArrayNorVer_localPt[a3*6+5]<<">, ";
stream <<"<"<<LocalScene.ArrayNorVer_localPt[a3*6]<<", "<< LocalScene.ArrayNorVer_localPt[a3*6+1]<<", "<<LocalScene.ArrayNorVer_localPt[a3*6+2]<<">} \n";

}

/// In this case, we have Parametric Quads:
else 
    for(i=0;i<NbTriangles_2; i++) {
a1 = LocalScene.PolyIndices_localPt[4*i  ];
a2 = LocalScene.PolyIndices_localPt[4*i+1];
a3 = LocalScene.PolyIndices_localPt[4*i+2];
a4 = LocalScene.PolyIndices_localPt[4*i+3];

/// First Triangle:
stream <<"smooth_triangle {<"<<LocalScene.ArrayNorVer_localPt[a1*6+3]<<", "<<LocalScene.ArrayNorVer_localPt[a1*6+4]<<", "<<LocalScene.ArrayNorVer_localPt[a1*6+5]<<">, ";
stream <<"<"<<LocalScene.ArrayNorVer_localPt[a1*6]<<", "<< LocalScene.ArrayNorVer_localPt[a1*6+1]<<", "<<LocalScene.ArrayNorVer_localPt[a1*6+2]<<">,\n";

stream <<"<"<<LocalScene.ArrayNorVer_localPt[a2*6+3]<<", "<<LocalScene.ArrayNorVer_localPt[a2*6+4]<<", "<<LocalScene.ArrayNorVer_localPt[a2*6+5]<<">, ";
stream <<"<"<<LocalScene.ArrayNorVer_localPt[a2*6]<<", "<< LocalScene.ArrayNorVer_localPt[a2*6+1]<<", "<<LocalScene.ArrayNorVer_localPt[a2*6+2]<<">,\n";

stream <<"<"<<LocalScene.ArrayNorVer_localPt[a3*6+3]<<", "<<LocalScene.ArrayNorVer_localPt[a3*6+4]<<", "<<LocalScene.ArrayNorVer_localPt[a3*6+5]<<">, ";
stream <<"<"<<LocalScene.ArrayNorVer_localPt[a3*6]<<", "<< LocalScene.ArrayNorVer_localPt[a3*6+1]<<", "<<LocalScene.ArrayNorVer_localPt[a3*6+2]<<">} \n";

/// Second Triangle:
stream <<"smooth_triangle {<"<<LocalScene.ArrayNorVer_localPt[a3*6+3]<<", "<<LocalScene.ArrayNorVer_localPt[a3*6+4]<<", "<<LocalScene.ArrayNorVer_localPt[a3*6+5]<<">, ";
stream <<"<"<<LocalScene.ArrayNorVer_localPt[a3*6]<<", "<< LocalScene.ArrayNorVer_localPt[a3*6+1]<<", "<<LocalScene.ArrayNorVer_localPt[a3*6+2]<<">,\n";

stream <<"<"<<LocalScene.ArrayNorVer_localPt[a4*6+3]<<", "<<LocalScene.ArrayNorVer_localPt[a4*6+4]<<", "<<LocalScene.ArrayNorVer_localPt[a4*6+5]<<">, ";
stream <<"<"<<LocalScene.ArrayNorVer_localPt[a4*6]<<", "<< LocalScene.ArrayNorVer_localPt[a4*6+1]<<", "<<LocalScene.ArrayNorVer_localPt[a4*6+2]<<">,\n";

stream <<"<"<<LocalScene.ArrayNorVer_localPt[a1*6+3]<<", "<<LocalScene.ArrayNorVer_localPt[a1*6+4]<<", "<<LocalScene.ArrayNorVer_localPt[a1*6+5]<<">, ";
stream <<"<"<<LocalScene.ArrayNorVer_localPt[a1*6]<<", "<< LocalScene.ArrayNorVer_localPt[a1*6+1]<<", "<<LocalScene.ArrayNorVer_localPt[a1*6+2]<<">} \n";
}

stream <<" texture { FRONT_TEXTURE }\n\
 interior_texture { BACK_TEXTURE }\n\
 matrix <" <<M11<<", "<<M21<<", "<<M31<<",\n"
           <<M12<<", "<<M22<<", "<<M32<<",\n"
		   <<M13<<", "<<M23<<", "<<M33<<",\n\
0.0 , 0.0, 0.0 >\n}\n\
/*************End of 'Mesh.inc'************/ ";
/*
rotate    <"<<-LocalScene.axe_x*180 <<","
              <<-LocalScene.axe_y*180 <<","
              <<-LocalScene.axe_z*180 <<"> \n\
 */
 QFile fm("Mesh.inc");
    if ( !fm.open( IO_WriteOnly ) ) {
 return;
    }
    QTextStream tm( &fm );
    tm << strstream;
    fm.close();


//+++++++++++++ PovScript +++++++++++++++++
    QString strstream2;
    QTextStream stream2(&strstream2, IO_ReadWrite);

stream2 <<"#include \"shapes.inc\"\n\
#include \"colors.inc\"\n\
#include \"textures.inc\"\n\n";
stream2 <<"#declare FRONT_TEXTURE = texture {\n\n\
 pigment {\n\
 color red "    <<LocalScene.frontcol[0]
<<" green "<<LocalScene.frontcol[1]
<<" blue  "<<LocalScene.frontcol[2]<<"\n}\n\
 finish {\n\
 ambient 0.5\n\
 diffuse 0.4}\n}\n";
stream2 <<" #declare BACK_TEXTURE = texture {\n\n\
 pigment {\n\
 color red "<<LocalScene.backcol[0] <<
" green  " <<LocalScene.backcol[1] <<
" blue  "  <<LocalScene.backcol[2] <<"\n}\n\
 finish {\n\
 ambient 0.5\n\
 diffuse 0.4}\n}\n\
\n\
#include \"Mesh.inc\"\n\
\n\
//Plan\n\
 plane { y, -1800\n\
     pigment {\n\
        checker color Green color Yellow\n\
        scale 100\n\
    }\n\
     finish {\n\
        ambient 0.6\n\
        diffuse 0.6\n\
    }\n\
 }\n\
//camera\n\
 camera {\n\
 angle "<<focal <<"\n\
 location  <0.0, 0.0, 800.0>\n\
 right     <1, .0,  0.0>\n\
 direction <0.0, 0.0,  -1.0>\n\
 }\n\
 // Light source\n\
 light_source { <0, 0, 800> colour White\n}\n";
//Save:
      QFile fp("test.pov");
    if ( !fp.open( IO_WriteOnly ) ) {
 return;
    }
  QTextStream tp( &fp );
  tp << strstream2;
  fp.close();
};

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::ChangeMaxResolution(int NewMaximumNumberPoints, int NewMaximumNumberTriangles){
int     * NewTypeIsoSurfaceTriangleListeCND;
int     * NewTypeIsoSurfaceTriangleListeCND2;

GLuint  * NewPolyIndices_local;
GLuint  * NewPolyIndices_local2;

GLuint  * NewPolyIndices_localMin;
GLuint  * NewPolyIndices_localMin2;

GLfloat * NewArrayNorVer_local;
GLfloat * NewArrayNorVer_local2;

NewTypeIsoSurfaceTriangleListeCND = new int    [NewMaximumNumberTriangles];
NewPolyIndices_local              = new GLuint [3*NewMaximumNumberTriangles];
NewPolyIndices_localMin           = new GLuint [3*NewMaximumNumberTriangles];
NewArrayNorVer_local              = new GLfloat[6*NewMaximumNumberPoints];

if(NewMaximumNumberTriangles > MaximumNumberTriangles){
memcpy(NewTypeIsoSurfaceTriangleListeCND,
       TypeIsoSurfaceTriangleListeCND,
       MaximumNumberTriangles*sizeof(int));
memcpy(NewPolyIndices_local,
       PolyIndices_local,
       3*MaximumNumberTriangles*sizeof(GLuint));
memcpy(NewPolyIndices_localMin,
       LocalScene.PolyIndices_localPtMin,
       3*MaximumNumberTriangles*sizeof(GLuint));
}
else{
memcpy(NewTypeIsoSurfaceTriangleListeCND,
       TypeIsoSurfaceTriangleListeCND,
       NewMaximumNumberTriangles*sizeof(int));
memcpy(NewPolyIndices_local,
       PolyIndices_local,
       3*NewMaximumNumberTriangles*sizeof(GLuint));
memcpy(NewPolyIndices_localMin,
       LocalScene.PolyIndices_localPtMin,
       3*NewMaximumNumberTriangles*sizeof(GLuint));
}

if(NewMaximumNumberPoints > MaximumNumberPoints)
memcpy(NewArrayNorVer_local,
       LocalScene.ArrayNorVer_localPt,
       6*MaximumNumberPoints*sizeof(GLfloat));
else
memcpy(NewArrayNorVer_local,
       LocalScene.ArrayNorVer_localPt,
       6*NewMaximumNumberPoints*sizeof(GLfloat));

NewTypeIsoSurfaceTriangleListeCND2 = TypeIsoSurfaceTriangleListeCND;
NewArrayNorVer_local2              = LocalScene.ArrayNorVer_localPt;
NewPolyIndices_local2              = PolyIndices_local;
NewPolyIndices_localMin2           = LocalScene.PolyIndices_localPtMin;

LocalScene.ArrayNorVer_localPt              = NewArrayNorVer_local;
glInterleavedArrays (GL_N3F_V3F, 0, LocalScene.ArrayNorVer_localPt);

PolyIndices_local                 = NewPolyIndices_local;
LocalScene.PolyIndices_localPtMin = NewPolyIndices_localMin;
TypeIsoSurfaceTriangleListeCND    = NewTypeIsoSurfaceTriangleListeCND;

delete(NewTypeIsoSurfaceTriangleListeCND2);
delete(NewPolyIndices_local2);
delete(NewPolyIndices_localMin2);
delete(NewArrayNorVer_local2);

MaximumNumberPoints    = NewMaximumNumberPoints;
MaximumNumberTriangles = NewMaximumNumberTriangles;
};

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::fct_1(double*,int*,QString*){};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::ActivateTexture(){};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::cnd(){LocalScene.drawcnd *= -1;};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::cndmesh(){LocalScene.cndmesh *= -1;};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::drawborder(){LocalScene.border *= -1;};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::fog(){/*LocalScene.fog *= -1;*/};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::meshOk(){LocalScene.mesh *= -1;update();};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::backSurf(){ LocalScene.back *= -1;update();};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::clipOk(){ LocalScene.clip *= -1;};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::axeOk(){ LocalScene.axe *= -1;update();};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::normOk(){ LocalScene.norm *= -1;update();};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::infosOk(){ LocalScene.infos *= -1;update();};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::boxOk(){LocalScene.line *= -1;};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::isoboxOk(){ LocalScene.isobox *= -1;update();};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::lineOk(){ LocalScene.line *= -1;};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::plan(){LocalScene.plan *= -1; update();};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::png(){png_ok*=-1;}
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::jpg(){jpg_ok*=-1;}
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::bmp(){bmp_ok*=-1;}
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::quality(int c){quality_image = c;}
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::conditionok(){LocalScene.condition *= -1;}
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::screenshot(){
QImage image = grabFrameBuffer();
if(png_ok == 1) image.save("GLscreenshot.png", "PNG" , quality_image);
if(jpg_ok == 1) image.save("GLscreenshot.jpg", "JPEG" , quality_image);
if(bmp_ok == 1) image.save("GLscreenshot.bmp", "BMP" , quality_image);
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
QImage OpenGlWidget::Copyscreenshot(){
return(grabFrameBuffer());
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::transparency(int cl)
{   switch(colortype) {
    case 0:  LocalScene.frontcol[3] = (cl/255.);valueChanged();
             update();
             break;
    case 1:  LocalScene.backcol[3]  = (cl/255.);valueChanged();
             update();
             break;
    case 2:  LocalScene.gridcol[3] = (cl/255.);
             update();
             break;
    case 3:  LocalScene.groundcol[3] = (cl/255.);
             glClearColor(LocalScene.groundcol[0], LocalScene.groundcol[1],LocalScene.groundcol[2], LocalScene.groundcol[3]);
             update();
             break;
    case 4:  LocalScene.condcol[3] = staticcolor[19] = (cl/255.);
             update();
             break;
     };
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::red(int cl)
{   switch(colortype) {
    case 0:  LocalScene.frontcol[0] = staticcolor[0] = (cl/255.);valueChanged();
             update();
             break;
    case 1:  LocalScene.backcol[0]  = staticcolor[4] = (cl/255.);valueChanged();
             update();
             break;
    case 2:  LocalScene.gridcol[0] = staticcolor[8] = (cl/255.);
             update();
             break;
    case 3:  LocalScene.groundcol[0] = staticcolor[12] = (cl/255.);
             glClearColor(LocalScene.groundcol[0], LocalScene.groundcol[1],LocalScene.groundcol[2], LocalScene.groundcol[3]);
             update();
    case 4:  LocalScene.condcol[0] = staticcolor[16] = (cl/255.);
             update();
             break;
             break;
     };
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::green(int cl)
{   switch(colortype) {
    case 0:  LocalScene.frontcol[1] = staticcolor[1] = (cl/255.);valueChanged();
             update();
             break;
    case 1:  LocalScene.backcol[1]  = staticcolor[5] = (cl/255.);valueChanged();
             update();
             break;
    case 2:  LocalScene.gridcol[1] = staticcolor[9] = (cl/255.);
             update();
             break;
    case 3:  LocalScene.groundcol[1] = staticcolor[13] = (cl/255.);
             glClearColor(LocalScene.groundcol[0], LocalScene.groundcol[1], LocalScene.groundcol[2], LocalScene.groundcol[3]);
             update();
             break;
    case 4:  LocalScene.condcol[1] = staticcolor[17] = (cl/255.);
             update();
             break;
     };
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::blue(int cl)
{   switch(colortype) {
    case 0:  LocalScene.frontcol[2] = staticcolor[2] = (cl/255.);valueChanged();
             update();
             break;
    case 1:  LocalScene.backcol[2]  = staticcolor[6] = (cl/255.);valueChanged();
             update();
             break;
    case 2:  LocalScene.gridcol[2] = staticcolor[10] = (cl/255.);
             update();
             break;
    case 3:  LocalScene.groundcol[2] = staticcolor[14] = (cl/255.);
             glClearColor(LocalScene.groundcol[0], LocalScene.groundcol[1],LocalScene.groundcol[2], LocalScene.groundcol[3]);
             update();
             break;
    case 4:  LocalScene.condcol[2] = staticcolor[18] = (cl/255.);
             update();
             break;
     };
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::transparence()
{
   LocalScene.transparency *=-1;
   if (LocalScene.transparency == 1) {
   glEnable(GL_BLEND);
   glBlendFunc (GL_SRC_ALPHA, GL_ONE/*_MINUS_SRC_ALPHA*/);
   }
   else glDisable(GL_BLEND);
   update();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::valueChanged(){
    InitGlParameters();
     }

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
GLuint fontOffset;
void makeRasterFont(void)
{
    GLuint i;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    fontOffset = glGenLists (128);
    for (i = 30; i < 127; i++) {
        glNewList(i+fontOffset, GL_COMPILE);
            glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, rasters[i-30]);
        glEndList();
    }
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void InitFont(void)
{
    //glShadeModel (GL_FLAT);
    makeRasterFont();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
static void printString(char *s)
{
    glPushAttrib (GL_LIST_BIT);
    glListBase(fontOffset);
    glCallLists(strlen(s), GL_UNSIGNED_BYTE, (GLubyte *) s);
    glPopAttrib ();
}
*/
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::start(){
QThread::start();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::run(){
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::anim(){
    LocalScene.anim *= -1;
if(LocalScene.anim == 1) timer->start( latence, FALSE );
else if(LocalScene.morph != 1) stoptimer();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::morph(){
LocalScene.morph *= -1;
if(LocalScene.morph == 1) timer->start( latence, FALSE );
else if(LocalScene.anim != 1) stoptimer();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
bool OpenGlWidget::timeractif(){
return(LocalScene.morph == 1 || LocalScene.anim == 1);
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::stoptimer(){
timer->stop();
update();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::starttimer(){
timer->start( latence, FALSE );
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::restarttimer(int newlatence){
latence = newlatence;
if(LocalScene.morph == 1 || LocalScene.anim == 1) {
timer->stop();
timer->start( latence, FALSE );
}
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::setGridColor(GLfloat r, GLfloat g, GLfloat b, GLfloat t){
LocalScene.gridcol[0]= r; LocalScene.gridcol[1]= g;
LocalScene.gridcol[2]= b; LocalScene.gridcol[3]= t;
};

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::setFrontColor(GLfloat r, GLfloat g, GLfloat b, GLfloat t){
LocalScene.frontcol[0]= r; LocalScene.frontcol[1]= g;
LocalScene.frontcol[2]= b; LocalScene.frontcol[3]= t;
};

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::setBackColor(GLfloat r, GLfloat g, GLfloat b, GLfloat t){
LocalScene.backcol[0]= r; LocalScene.backcol[1]= g;
LocalScene.backcol[2]= b; LocalScene.backcol[3]= t; 
};

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::setGroundColor(GLfloat r, GLfloat g, GLfloat b, GLfloat t){
LocalScene.groundcol[0]= r; LocalScene.groundcol[1]= g;
LocalScene.groundcol[2]= b; LocalScene.groundcol[3]= t;
};

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::LoadImage(QString image){
   // Textue Creation:
    QImage buf;
    if ( !buf.load(image) ) {	// Load first image from file
        //qWarning( "Could not read image file, using single-color instead." );
        QImage dummy( 256, 256, 32 );
        dummy.fill( Qt::green.rgb() );
        buf = dummy;
    }
    buf  = buf.smoothScale(256, 256);
    tex1 = QGLWidget::convertToGLFormat( buf );  // flipped 32bit RGBA
    glGenTextures(1, &LocalScene.texture[0]); // Create The Texture
    glBindTexture(GL_TEXTURE_2D, LocalScene.texture[0]);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, 3, tex1.width(), tex1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex1.bits() );
    update();
};

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
OpenGlWidget::OpenGlWidget( QWidget *parent, const char *name )
     : QGLWidget( parent, name, 0, WNoAutoErase )
{
    static int NBGlWindow = 0;

    MaximumNumberPoints    = 1000000;
    MaximumNumberTriangles = 2000000;

    LocalScene.ArrayNorVer_localPt    = new GLfloat[6*MaximumNumberPoints];
    PolyIndices_local                 = new GLuint [3*MaximumNumberTriangles];
    LocalScene.PolyIndices_localPtMin = new GLuint [3*MaximumNumberTriangles];
    TypeIsoSurfaceTriangleListeCND    = new int    [MaximumNumberTriangles];
    //NbPolygnNbVertexMin = new GLuint[1];
    latence = 30;
    colortype = 0;
    LocalScene.RotStrength=0;
    LocalScene.zminim = -400.0;
    LocalScene.polyfactor = 1.0;
    LocalScene.polyunits = 1.0;
    LocalScene.ScalCoeff =1.0;
    LocalScene.view_rotx = LocalScene.view_roty = 90.0; LocalScene.view_rotz = 1.0;
    val1 = val2 = val3 = 0.0;
    nb_colone = nb_ligne = 25;
    coupure_col = coupure_ligne = 0;
    isoline = isocolumn = isodepth = 26;
    cpisoline = cpisocolumn = cpisodepth = 0;
    width = 620; height = 620;
    NbMorphFrame = 30; /// The maximum of morph sequences...
    timer = new QTimer( this );
    connect( timer, SIGNAL(timeout()), this, SLOT(updateGL()) );

    pixmap = new QPixmap(620,620);
    png_ok = 1; jpg_ok = bmp_ok = -1; quality_image = 50;

    LocalScene.gridcol[0]   = staticcolor[8];
    LocalScene.gridcol[1]   = staticcolor[9];
    LocalScene.gridcol[2]   = staticcolor[10];
    LocalScene.gridcol[3]   = 0.39;//staticcolor[11];

    LocalScene.groundcol[0] = staticcolor[12];
    LocalScene.groundcol[1] = staticcolor[13];
    LocalScene.groundcol[2] = staticcolor[14];
    LocalScene.groundcol[3] = 0.39;//staticcolor[15];

    LocalScene.backcol[0]   = staticcolor[0];
    LocalScene.backcol[1]   = staticcolor[1];
    LocalScene.backcol[2]   = staticcolor[2];
    LocalScene.backcol[3]   = 0.39;//staticcolor[3];

    LocalScene.frontcol[0]  = staticcolor[4];
    LocalScene.frontcol[1]  = staticcolor[5];
    LocalScene.frontcol[2]  = staticcolor[6];
    LocalScene.frontcol[3]  = 0.39;//staticcolor[7];

    LocalScene.condcol[0]   = staticcolor[16];
    LocalScene.condcol[1]   = staticcolor[17];
    LocalScene.condcol[2]   = staticcolor[18];
    LocalScene.condcol[3]   = 0.39;//staticcolor[19];

    LocalScene.border  = 1;
    LocalScene.cndmesh =-1;
    LocalScene.drawcnd = 1;

    LocalScene.mesh  = 1;
    LocalScene.line  = 1;
    LocalScene.infos = 1;
    LocalScene.infosdetails[0] = LocalScene.infosdetails[1] = LocalScene.infosdetails[2] = 1;
    LocalScene.axe   = 1;
    LocalScene.box   = 1;
    LocalScene.isobox= 1;
    LocalScene.typedrawing =-1;
    LocalScene.smoothpoly  = 1;
    LocalScene.smoothline  =-1;
    LocalScene.anim  =-1;
    LocalScene.morph =-1;
    LocalScene.norm  =-1;
    LocalScene.plan  = 1;
    LocalScene.front = 1;
    LocalScene.back  = 1;
    LocalScene.condition  = -1;
    LocalScene.transparency = -1;
    //LocalScene.ArrayNorVer_localPt = ArrayNorVer_local;
    LocalScene.PolyIndices_localPt = PolyIndices_local;
    //LocalScene.PolyIndices_localPtMin = PolyIndices_localMin;
    LocalScene.morelistept[9] = NbPolygnNbVertex;
    IDGlWindow = NBGlWindow;
    PolyNumber        = 0;
    VertexNumber      = 0;

    NBGlWindow++;
/*    if(NBGlWindow == 1) {
   GLfloat ambient[] = { .0, .0, .0, 1.0 };
   GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
   GLfloat local_view[] = { 1.0 };
   static GLfloat position[4] = {0.0, 0.0,1000.0, 1.0};

   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
   glLightfv(GL_LIGHT0, GL_POSITION, position);
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
   glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
   }

   // Textue Creation:
    QImage buf;
    if ( !buf.load( "../textures/gllogo.bmp" ) ) {
        // Load first image from file
        //qWarning( "Could not read image file, using single-color instead." );
        QImage dummy( 128, 128, 32 );
        dummy.fill( Qt::green.rgb() );
        buf = dummy;
    }
    tex1 = QGLWidget::convertToGLFormat( buf );  // flipped 32bit RGBA
    glGenTextures(1, &LocalScene.texture[0]); // Create The Texture
    glBindTexture(GL_TEXTURE_2D, LocalScene.texture[0]);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, 3, tex1.width(), tex1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex1.bits() );
   // Font initialisation:
    InitFont();*/
}

///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::initializeGL()
{ int i, j, k, l, mn, nbpl;
  GLuint * PolyIndices_local_tmp;
  GLuint * PolyIndices_localBorderCND_tmp;
  GLuint * PolyIndices_localVerifyCND_tmp;
  GLuint * PolyIndices_localNotVerifyCND_tmp;

  boxok();
  glInterleavedArrays (GL_N3F_V3F, 0, LocalScene.ArrayNorVer_localPt);

if(LocalScene.condition == 1){
    j = k = l = 0;
    nbpl = (int)(NbPolygnNbVertex[0]/3);
      //Count the number of different poly types:
    for(i = 0; i < nbpl; i++){
    mn = TypeIsoSurfaceTriangleListeCND[i];
         if(mn == 1) j+=3;
    else if(mn == 0) k+=3;
    else if(mn == 4) l+=3;
    }
    // Save the result:
    LocalScene.PolyNumberBorderCND = l;
    LocalScene.PolyNumberVerifyCND = k;
    LocalScene.PolyNumberNotVerifyCND = j;

// No we start treating triangles: 
PolyIndices_local_tmp = new GLuint [3*MaximumNumberTriangles];
PolyIndices_localBorderCND_tmp = &PolyIndices_local_tmp[0];
PolyIndices_localVerifyCND_tmp = &PolyIndices_local_tmp[l];
PolyIndices_localNotVerifyCND_tmp = &PolyIndices_local_tmp[l+k];
// Restart treating polygons but this time with saving them in the appropriate location:
    j = k = l = 0;
    for(i = 0; i < nbpl; i++){
    mn = TypeIsoSurfaceTriangleListeCND[i];
    if(mn == 1) {
    PolyIndices_localNotVerifyCND_tmp[j  ] = LocalScene.PolyIndices_localPt[3*i  ];
    PolyIndices_localNotVerifyCND_tmp[j+1] = LocalScene.PolyIndices_localPt[3*i+1];
    PolyIndices_localNotVerifyCND_tmp[j+2] = LocalScene.PolyIndices_localPt[3*i+2];
    j += 3;
    }
    else if(mn == 0) {
    PolyIndices_localVerifyCND_tmp[k  ] = LocalScene.PolyIndices_localPt[3*i  ];
    PolyIndices_localVerifyCND_tmp[k+1] = LocalScene.PolyIndices_localPt[3*i+1];
    PolyIndices_localVerifyCND_tmp[k+2] = LocalScene.PolyIndices_localPt[3*i+2];
    k += 3;
    }
    else if(mn == 4) {
    PolyIndices_localBorderCND_tmp[l  ] = LocalScene.PolyIndices_localPt[3*i  ];
    PolyIndices_localBorderCND_tmp[l+1] = LocalScene.PolyIndices_localPt[3*i+1];
    PolyIndices_localBorderCND_tmp[l+2] = LocalScene.PolyIndices_localPt[3*i+2];
    l += 3;
    }
    }

memcpy(LocalScene.PolyIndices_localPt,
       PolyIndices_local_tmp,
       (l+k+j)*sizeof(GLuint));
LocalScene.PolyIndices_localBorderCND = &LocalScene.PolyIndices_localPt[0];
LocalScene.PolyIndices_localVerifyCND = &LocalScene.PolyIndices_localPt[l];
LocalScene.PolyIndices_localNotVerifyCND = &LocalScene.PolyIndices_localPt[l+k];
delete(PolyIndices_local_tmp);
    }
    InitGlParameters();
    IndiceMorphFrame =0; /// To Initialise the morph effect

}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::boxok(){
GLfloat minx= 999999999, miny= 999999999, minz= 999999999,
        maxx=-999999999, maxy=-999999999, maxz=-999999999;
int i, nbvertex;
(LocalScene.typedrawing ==1) ? nbvertex = (int)NbPolygnNbVertex[0]/3 :
                               nbvertex = (int)NbPolygnNbVertex[0]/4 ;
nbvertex = VertexNumber;
for(i=0; i< VertexNumber/*nbvertex*/; i++) {
if(minx >LocalScene.ArrayNorVer_localPt[6*i+3]) minx = LocalScene.ArrayNorVer_localPt[6*i+3];
if(miny >LocalScene.ArrayNorVer_localPt[6*i+4]) miny = LocalScene.ArrayNorVer_localPt[6*i+4];
if(minz >LocalScene.ArrayNorVer_localPt[6*i+5]) minz = LocalScene.ArrayNorVer_localPt[6*i+5];

if(maxx <LocalScene.ArrayNorVer_localPt[6*i+3]) maxx = LocalScene.ArrayNorVer_localPt[6*i+3];
if(maxy <LocalScene.ArrayNorVer_localPt[6*i+4]) maxy = LocalScene.ArrayNorVer_localPt[6*i+4];
if(maxz <LocalScene.ArrayNorVer_localPt[6*i+5]) maxz = LocalScene.ArrayNorVer_localPt[6*i+5];
}

LocalScene.BoxLimits[0][0] = minx;
LocalScene.BoxLimits[1][0] = miny;
LocalScene.BoxLimits[2][0] = minz;

LocalScene.BoxLimits[0][5] = maxx;
LocalScene.BoxLimits[1][5] = maxy;
LocalScene.BoxLimits[2][5] = maxz;

glDeleteLists(LocalScene.boxliste, 1);
LocalScene.boxliste = glGenLists(1);
 glNewList(LocalScene.boxliste, GL_COMPILE );

  glLineWidth(2);
   glColor3f (1., 0.0, 0.0);
   glBegin( GL_LINES );
glVertex3f(LocalScene.BoxLimits[0][0], LocalScene.BoxLimits[1][0], LocalScene.BoxLimits[2][0]);
glVertex3f(LocalScene.BoxLimits[0][5], LocalScene.BoxLimits[1][0], LocalScene.BoxLimits[2][0]);
glVertex3f(LocalScene.BoxLimits[0][5], LocalScene.BoxLimits[1][0], LocalScene.BoxLimits[2][0]);
glVertex3f(LocalScene.BoxLimits[0][5], LocalScene.BoxLimits[1][5], LocalScene.BoxLimits[2][0]);
glVertex3f(LocalScene.BoxLimits[0][5], LocalScene.BoxLimits[1][5], LocalScene.BoxLimits[2][0]);
glVertex3f(LocalScene.BoxLimits[0][0], LocalScene.BoxLimits[1][5], LocalScene.BoxLimits[2][0]);
glVertex3f(LocalScene.BoxLimits[0][0], LocalScene.BoxLimits[1][5], LocalScene.BoxLimits[2][0]);
glVertex3f(LocalScene.BoxLimits[0][0], LocalScene.BoxLimits[1][0], LocalScene.BoxLimits[2][0]);

glVertex3f(LocalScene.BoxLimits[0][0], LocalScene.BoxLimits[1][0], LocalScene.BoxLimits[2][5]);
glVertex3f(LocalScene.BoxLimits[0][5], LocalScene.BoxLimits[1][0], LocalScene.BoxLimits[2][5]);
glVertex3f(LocalScene.BoxLimits[0][5], LocalScene.BoxLimits[1][0], LocalScene.BoxLimits[2][5]);
glVertex3f(LocalScene.BoxLimits[0][5], LocalScene.BoxLimits[1][5], LocalScene.BoxLimits[2][5]);
glVertex3f(LocalScene.BoxLimits[0][5], LocalScene.BoxLimits[1][5], LocalScene.BoxLimits[2][5]);
glVertex3f(LocalScene.BoxLimits[0][0], LocalScene.BoxLimits[1][5], LocalScene.BoxLimits[2][5]);
glVertex3f(LocalScene.BoxLimits[0][0], LocalScene.BoxLimits[1][5], LocalScene.BoxLimits[2][5]);
glVertex3f(LocalScene.BoxLimits[0][0], LocalScene.BoxLimits[1][0], LocalScene.BoxLimits[2][5]);

glColor3f (0.0, 0.0, 1.0);
glVertex3f(LocalScene.BoxLimits[0][0], LocalScene.BoxLimits[1][0], LocalScene.BoxLimits[2][0]);
glVertex3f(LocalScene.BoxLimits[0][0], LocalScene.BoxLimits[1][0], LocalScene.BoxLimits[2][5]);

glVertex3f(LocalScene.BoxLimits[0][5], LocalScene.BoxLimits[1][0], LocalScene.BoxLimits[2][0]);
glVertex3f(LocalScene.BoxLimits[0][5], LocalScene.BoxLimits[1][0], LocalScene.BoxLimits[2][5]);

glVertex3f(LocalScene.BoxLimits[0][5], LocalScene.BoxLimits[1][5], LocalScene.BoxLimits[2][0]);
glVertex3f(LocalScene.BoxLimits[0][5], LocalScene.BoxLimits[1][5], LocalScene.BoxLimits[2][5]);

glVertex3f(LocalScene.BoxLimits[0][0], LocalScene.BoxLimits[1][5], LocalScene.BoxLimits[2][0]);
glVertex3f(LocalScene.BoxLimits[0][0], LocalScene.BoxLimits[1][5], LocalScene.BoxLimits[2][5]);
   glEnd();

    glLineWidth(0.9);
   glColor3f (LocalScene.gridcol[0], LocalScene.gridcol[1], LocalScene.gridcol[3]);
 glEndList();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::CutLineIndex(int ctline){
   int i, j, k=0;
   coupure_ligne = ctline;
   PolyNumber = 4*(nb_ligne-coupure_ligne-1)*(nb_colone-coupure_col-1);
/// generation of the Index Array :
   k=0;
   for (i=0; i< nb_ligne - coupure_ligne -1; i++)
      for (j=0; j< nb_colone - coupure_col -1; j++) {
     PolyIndices_local[k  ] = i*nb_colone + j;
     PolyIndices_local[k+1] = (i+1)*nb_colone + j;
     PolyIndices_local[k+2] = (i+1)*nb_colone + (j+1);
     PolyIndices_local[k+3] = i*nb_colone + (j+1);
     k+=4;
    }
    // 1) Generate the Indices Tables for all Morph Frames :
  for(j =1; j < NbMorphFrame; j++)
    for(i =0; i < PolyNumber; i++){
    PolyIndices_local[j*PolyNumber + i] = PolyIndices_local[i] + j*nb_ligne*nb_colone;
    }
  /// 2) Nb Poly & Vertex :
 for(i =0; i < NbMorphFrame; i++) {
   NbPolygnNbVertex[2*i  ] = PolyNumber;
   NbPolygnNbVertex[2*i+1] = i*(nb_ligne-coupure_ligne)*(nb_colone-coupure_col);
   };
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::CutColIndex(int ctcol){
   int i, j, k=0;
   coupure_col = ctcol;
   PolyNumber = 4*(nb_ligne-coupure_ligne-1)*(nb_colone-coupure_col-1);
  /// generation of the Index Array :
   k=0;
   for (i=0; i< nb_ligne - coupure_ligne -1; i++)
      for (j=0; j< nb_colone - coupure_col -1; j++) {
     PolyIndices_local[k  ] = i*nb_colone + j;
     PolyIndices_local[k+1] = (i+1)*nb_colone + j;
     PolyIndices_local[k+2] = (i+1)*nb_colone + (j+1);
     PolyIndices_local[k+3] = i*nb_colone + (j+1);
     k+=4;
    }
  /// 1) Generate the Indices Tables for all Morph Frames :
  for(j =1; j < NbMorphFrame; j++)
    for(i =0; i < PolyNumber; i++){
    PolyIndices_local[j*PolyNumber + i] = PolyIndices_local[i] + j*nb_ligne*nb_colone;
    }
  /// 2) Nb Poly & Vertex :
  for(i =0; i < NbMorphFrame; i++) {
   NbPolygnNbVertex[2*i  ] = PolyNumber;
   NbPolygnNbVertex[2*i+1] = i*(nb_ligne-coupure_ligne)*(nb_colone-coupure_col);
   };

update();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::smoothpoly(){
    LocalScene.smoothpoly *= -1;
    if(LocalScene.smoothpoly == 1) glShadeModel (GL_SMOOTH);
    else glShadeModel (GL_FLAT);
    update();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::smoothline(){ LocalScene.smoothline *= -1;
   /// For drawing Lines :
   if(LocalScene.smoothline == 1) {
   glEnable (GL_LINE_SMOOTH);
   glEnable (GL_BLEND);
   glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
   }
   else {
   glDisable(GL_LINE_SMOOTH); 
   glDisable(GL_BLEND);
   };
   update();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::frontSurf(){
LocalScene.front *= -1;
    if(LocalScene.front == -1) glEnable(GL_CULL_FACE);
    else glDisable(GL_CULL_FACE);
    update();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static void makeallred(Scene *scene){
    static int redcl = 1;
    if( redcl == 1){
       /// For drawing Filled Polygones :
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_NORMALIZE);
    glFrontFace (GL_CCW);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, scene->condcol);
    glMaterialfv(GL_BACK , GL_AMBIENT_AND_DIFFUSE, scene->condcol);
    glMaterialf (GL_FRONT, GL_SHININESS, 35.0);
    glMaterialf (GL_BACK , GL_SHININESS, 35.0);
    }
   else {
      /// For drawing Filled Polygones :
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_NORMALIZE);
    glFrontFace (GL_CCW);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, scene->frontcol);
    glMaterialfv(GL_BACK , GL_AMBIENT_AND_DIFFUSE, scene->backcol);
    glMaterialf (GL_FRONT, GL_SHININESS, 35.0);
    glMaterialf (GL_BACK, GL_SHININESS, 35.0);
       }
   redcl *= -1;
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::InitGlParameters(){
/*
    //Texture initialisation :
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, 3, tex1.width(), tex1.height(), 0,
    GL_RGBA, GL_UNSIGNED_BYTE, tex1.bits() );
 */
    /// For drawing Filled Polygones :
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_NORMALIZE);
    glFrontFace (GL_CCW);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, LocalScene.frontcol);
    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, LocalScene.backcol);
    glMaterialf (GL_FRONT, GL_SHININESS, 35.0);
    glMaterialf (GL_BACK, GL_SHININESS, 35.0);

    glEnable(GL_DEPTH_TEST);
    glClearColor(LocalScene.groundcol[0], LocalScene.groundcol[1],LocalScene.groundcol[2], LocalScene.groundcol[3]);
    InitFont();

/*  /// Fog Effect:
glFogi(GL_FOG_MODE, fogMode[fogfilter]);		// Fog Mode
glFogfv(GL_FOG_COLOR, fogColor);			// Set Fog Color
glFogf(GL_FOG_DENSITY, 0.85f);				// How Dense Will The Fog Be
glHint(GL_FOG_HINT, GL_DONT_CARE);			// Fog Hint Value
glFogf(GL_FOG_START, 1.0f);				// Fog Start Depth
glFogf(GL_FOG_END, 2400.0f);				// Fog End Depth
glEnable(GL_FOG);
*/

/*
   /// For drawing Lines :
   if(LocalScene.smoothline == 1) {
   glEnable (GL_LINE_SMOOTH);
   glEnable (GL_BLEND);
   glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
   }
   else {glDisable(GL_LINE_SMOOTH); glDisable(GL_BLEND);
   }
*/

 GLUquadricObj *sphereObj;
 sphereObj = gluNewQuadric();
 LocalScene.axeliste = glGenLists(1);
    glNewList(LocalScene.axeliste, GL_COMPILE );
    glLineWidth(1);
    glBegin( GL_LINES );
    glColor3f (1., 0., 0.);
    glVertex3f( 400.0, 0.0, 0.0);
    glVertex3f(   0.0, 0.0, 0.0);
    glColor3f (0., 1., 0.);
    glVertex3f(0.0, 400.0, 0.0);
    glVertex3f(0.0,   0.0, 0.0);
    glColor3f (0., 0., 1.);
    glVertex3f(0.0, 0.0, 400.0);
    glVertex3f(0.0, 0.0,   0.0);
    glEnd();

   glBegin(GL_TRIANGLE_FAN);
   glColor3f (0.0, 0.0, 1.0);
   glVertex3f(0.0, 0.0, 400.0);
   glVertex3f(10.0, 0.0, 380.0);
   glVertex3f(0.0, 10.0, 380.0);
   glColor3f (0.0, 0.0, 0.3);
   glVertex3f(-10.0, 0.0, 380.0);
   glColor3f (0.0, 0.0, 1.0);
   glVertex3f(0.0, -10.0, 380.0);
   glColor3f (0.0, 0.0, 0.3);
   glVertex3f(10.0, 0.0, 380.0);
   glEnd();

   glBegin(GL_TRIANGLE_FAN);
   glColor3f (0.0, 1., 0.);
   glVertex3f(0.0, 400.0, 0.0);
   glVertex3f(10.0, 380.0, 0.0);
   glVertex3f(0.0, 380.0, 10.0);
   glColor3f (0.0, 0.3, 0.0);
   glVertex3f(-10.0, 380.0, 0.0);
   glColor3f (0.0, 1.0, 0.0);
   glVertex3f(.0, 380.0, -10.0);
   glColor3f (0.0, 0.3, 0.0);
   glVertex3f(10.0, 380.0, 0.0);
   glEnd();

/// Axe X :
   glBegin(GL_TRIANGLE_FAN);
   glColor3f (1.0, 0.0, 0.0);
   glVertex3f(400.0, 0.0, 0.0);
   glVertex3f(380.0, 10.0, 0.0);
   glVertex3f(380.0, 0.0, 10.0);
   glColor3f (0.3, 0.0, 0.0);
   glVertex3f(380.0, -10.0, 0.0);
   glColor3f (1.0, 0.0, 0.0);
   glVertex3f(380.0, 0.0, -10.0);
   glColor3f (0.3, 0.0, 0.0);
   glVertex3f(380.0, 10.0, 0.0);
   glEnd();

   glColor3f (1.0, 0.0, 0.0);
   glBegin(GL_LINE_LOOP);
   glVertex3f(400.0, 0.0, 0.0);
   glVertex3f(380.0, 10.0, 0.0);
   glVertex3f(380.0, 0.0, 10.0);
   glVertex3f(380.0, -10.0, 0.0);
   glVertex3f(380.0, 0.0, -10.0);
   glVertex3f(380.0, 10.0, 0.0);
   glEnd();

   glColor3f (1., 0., 0.);
   glRasterPos3i(410, 10, 10);
   glCallLists(strlen("X"),GL_UNSIGNED_BYTE,"X");

   glColor3f (0.7, 0.7, 0.7);
   glTranslatef(410.0, 4.0, 4.0);
   //gluSphere(sphereObj, .0, 16, 16);
   glTranslatef(-410.0, -4.0, -4.0);

   glColor3f (0., 1., 0.);
   glRasterPos3i(10, 410, 10);
   //printString("Y");
   glCallLists(strlen("Y"),
   GL_UNSIGNED_BYTE,
   "Y");

   glColor3f (1., 1., 0.);
   glTranslatef(4.0, 410.0, 4.0);
   //gluSphere(sphereObj, 8.0, 32, 32);
   glTranslatef(-4.0, -410.0, -4.0);

   glColor3f (0., 0., 1.);
   glRasterPos3i(10, 10, 410);
   //printString("Z");
   glCallLists(strlen("Z"),
   GL_UNSIGNED_BYTE,
   "Z");

   glColor3f (0., 0.7, 0.7);
   glTranslatef(4.0, 4.0, 410.0);
   //gluSphere(sphereObj, 10.0, 16, 16);
   glTranslatef(-4.0, -4.0, -410.0);
   glLineWidth(0.9);
  glEndList();

LocalScene.planliste = glGenLists(1);
 glNewList(LocalScene.planliste, GL_COMPILE );
  glLineWidth(1);
   glColor3f (0.8, 0., 0.7);
   glBegin( GL_LINES );
glVertex3f(-150.0, 600.0, LocalScene.zminim);
glVertex3f(-150.0,-600.0, LocalScene.zminim);
glVertex3f(0.0, 600.0, LocalScene.zminim);
glVertex3f(0.0,-600.0, LocalScene.zminim);

glVertex3f(150.0, 600.0, LocalScene.zminim);
glVertex3f(150.0,-600.0, LocalScene.zminim);
glVertex3f(600.0, -150.0, LocalScene.zminim);
glVertex3f(-600.0,-150.0, LocalScene.zminim);

glVertex3f(600.0, 0.0, LocalScene.zminim);
glVertex3f(-600.0, 0.0, LocalScene.zminim);
glVertex3f(600.0, 150.0, LocalScene.zminim);
glVertex3f(-600.0, 150.0, LocalScene.zminim);

glVertex3f(-75.0, 600.0, LocalScene.zminim);
glVertex3f(-75.0,-600.0, LocalScene.zminim);
glVertex3f(-225.0, 600.0, LocalScene.zminim);
glVertex3f(-225.0,-600.0, LocalScene.zminim);
glVertex3f(-300.0, 600.0, LocalScene.zminim);
glVertex3f(-300.0,-600.0, LocalScene.zminim);
glVertex3f(-375.0, 600.0, LocalScene.zminim);
glVertex3f(-375.0,-600.0, LocalScene.zminim);
glVertex3f(-450.0, 600.0, LocalScene.zminim);
glVertex3f(-450.0,-600.0, LocalScene.zminim);
glVertex3f(-525.0, 600.0, LocalScene.zminim);
glVertex3f(-525.0,-600.0, LocalScene.zminim);

glVertex3f(75.0, 600.0, LocalScene.zminim);
glVertex3f(75.0,-600.0, LocalScene.zminim);
glVertex3f(225.0, 600.0, LocalScene.zminim);
glVertex3f(225.0,-600.0, LocalScene.zminim);
glVertex3f(300.0, 600.0, LocalScene.zminim);
glVertex3f(300.0,-600.0, LocalScene.zminim);
glVertex3f(375.0, 600.0, LocalScene.zminim);
glVertex3f(375.0,-600.0, LocalScene.zminim);
glVertex3f(450.0, 600.0, LocalScene.zminim);
glVertex3f(450.0,-600.0, LocalScene.zminim);
glVertex3f(525.0, 600.0, LocalScene.zminim);
glVertex3f(525.0,-600.0, LocalScene.zminim);

glVertex3f(600.0,-75.0, LocalScene.zminim);
glVertex3f(-600.0,-75.0, LocalScene.zminim);
glVertex3f(600.0,-225.0, LocalScene.zminim);
glVertex3f(-600.0,-225.0, LocalScene.zminim);
glVertex3f(600.0,-300.0, LocalScene.zminim);
glVertex3f(-600.0,-300.0, LocalScene.zminim);
glVertex3f(600.0,-375.0, LocalScene.zminim);
glVertex3f(-600.0,-375.0, LocalScene.zminim);
glVertex3f(600.0,-450.0, LocalScene.zminim);
glVertex3f(-600.0,-450.0, LocalScene.zminim);
glVertex3f(600.0,-525.0, LocalScene.zminim);
glVertex3f(-600.0,-525.0, LocalScene.zminim);

glVertex3f(600.0,75.0, LocalScene.zminim);
glVertex3f(-600.0,75.0, LocalScene.zminim);
glVertex3f(600.0,225.0, LocalScene.zminim);
glVertex3f(-600.0,225.0, LocalScene.zminim);
glVertex3f(600.0,300.0, LocalScene.zminim);
glVertex3f(-600.0,300.0, LocalScene.zminim);
glVertex3f(600.0,375.0, LocalScene.zminim);
glVertex3f(-600.0,375.0, LocalScene.zminim);
glVertex3f(600.0,450.0, LocalScene.zminim);
glVertex3f(-600.0,450.0, LocalScene.zminim);
glVertex3f(600.0,525.0, LocalScene.zminim);
glVertex3f(-600.0,525.0, LocalScene.zminim);
  glEnd();
   glLineWidth(0.9);
 glEndList();

}

///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::InitGlMorph() {
    boxok();
    glInterleavedArrays (GL_N3F_V3F, 0, LocalScene.ArrayNorVer_localPt);
    InitGlParameters();
}


///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::scalcoeff(double ){
//LocalScene.ScalCoeff = coeff;
}
/*
void OpenGlWidget::writetest(QString str){
    QFont ft;
    renderText(0, 0, str, ft, 2000);
    };
*/
/*
# include <string>
using std::string;
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static string itos(int i)	// convert int to string
	{
		stringstream s;
		s << i;
		return s.str();
	}
	*/

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::infosok()
{ LocalScene.infos *= -1;
 //nblg = QString::number(LocalScene.PolyNumber);
     }

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::resizeGL( int newwidth, int newheight)
{ int tmp, starth, startw;
    //GLdouble mm[16];
    //glGetDoublev(GL_MODELVIEW_MATRIX,mm);
    CornerH = (int)(newheight/2);
    CornerW = (int)(newwidth/2);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(newwidth > newheight) {tmp = newwidth;
     starth=(newwidth-newheight)/4;startw=0;
     }
    else {tmp = newheight;
    startw = (newheight-newwidth)/4;starth=0;
    }
    glViewport(0, 0, tmp, tmp);
    glFrustum(-250+startw, 250+startw, -250+starth, 250+starth, 350.0, 3000.0 );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef( 0.0, 0.0, -800.0 );

    //glMultMatrixd(mm);

    heightresult = tmp/2; widthresult = 250+starth;
}
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::PrintInfos()
{ static int ref = heightresult-70;
(LocalScene.typedrawing == 1) ?
nbl = QString::number(isoline-cpisoline)+"x"+QString::number(isocolumn-cpisocolumn)+"x"+QString::number(isodepth-cpisodepth) :
nbl = QString::number(nb_ligne-coupure_ligne)+"x"+QString::number(nb_colone-coupure_col)+" = "+QString::number((nb_ligne-coupure_ligne)*(nb_colone-coupure_col));

glDisable(GL_DEPTH_TEST);
glMatrixMode(GL_PROJECTION);
glPushMatrix();
glLoadIdentity();

//glOrtho(-320,320,-320,320,-1,1);
glOrtho(-320, 320, -heightresult, heightresult,-1,1);
glMatrixMode(GL_MODELVIEW);
glPushMatrix();
glLoadIdentity();
if( LocalScene.infosdetails[0] ==1){
glColor3f (0., 1.0, 0.);
glRasterPos2i(-310, ref);
//glRasterPos2i(-CornerW+40,CornerH-80);
glCallLists(strlen("Grid = "),
GL_UNSIGNED_BYTE,
(GLubyte *)"Grid = ");
glColor3f (1., 0.0, 0.);
glRasterPos2i(-250, ref);
glCallLists(strlen(nbl),GL_UNSIGNED_BYTE,nbl);
}

if( LocalScene.infosdetails[1] ==1){
glColor3f (0., 1.0, 0.);
glRasterPos2i(-310, ref-20);
glCallLists(strlen("Poly = "),
GL_UNSIGNED_BYTE,
(GLubyte *)"Poly = ");
glColor3f (1., 0.0, 0.);
glRasterPos2i(-250, ref-20);
(LocalScene.typedrawing == 1) ? 
glCallLists(strlen(QString::number(NbPolygnNbVertex[0]/3)),
GL_UNSIGNED_BYTE,
QString::number(NbPolygnNbVertex[0]/3)) :
glCallLists(strlen(QString::number(NbPolygnNbVertex[0]/4)),
GL_UNSIGNED_BYTE,
QString::number(NbPolygnNbVertex[0]/4)) ;
}

if( LocalScene.infosdetails[2] ==1){
if (LocalScene.typedrawing == 1)  {
glColor3f (0., 1.0, 0.);
glRasterPos2i(-310, ref-40);
glCallLists(strlen("Vertx= "),
GL_UNSIGNED_BYTE,
(GLubyte *)"Vertx= ");
glColor3f (1., 0.0, 0.);
glRasterPos2i(-250, ref-40);

glCallLists(strlen(QString::number(VertexNumber)),
GL_UNSIGNED_BYTE,
QString::number(VertexNumber)) ;
}
}

if (LocalScene.anim == 1) {
glColor3f (0., 1.0, 0.);
glRasterPos2i(-310, ref-60);
glCallLists(strlen("Anim ="),GL_UNSIGNED_BYTE, (GLubyte *)"Anim =");
glColor3f (1., 0.0, 0.);
glRasterPos2i(-250, ref-60);
glCallLists(strlen("On"),GL_UNSIGNED_BYTE, (GLubyte *)"On");
}

if (LocalScene.morph == 1) {
glColor3f (0., 1.0, 0.);
glRasterPos2i(-310, ref-80);
glCallLists(strlen("Morf ="), GL_UNSIGNED_BYTE, (GLubyte *)"Morf =");
glColor3f (1., 0.0, 0.);
glRasterPos2i(-250, ref-80);
glCallLists(strlen("On"), GL_UNSIGNED_BYTE, (GLubyte *)"On");
}
glMatrixMode(GL_PROJECTION);
glPopMatrix();
glMatrixMode(GL_MODELVIEW);
glPopMatrix();
glEnable(GL_DEPTH_TEST);
}
static int staticaction = -1;
///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static void draw(Scene *scene){
int i, j, startpl, polysize, actualpointindice;

 glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
if(staticaction < 1) {
glRotatef(-90,1.0,0.0,0.0);
glRotatef(-135,0.0,0.0,1.0);
glRotatef(-35,1.0,-1.0,0.0);
staticaction += 1;
}

    /// Blend Effect activation:
    if(scene->transparency == 1)  {
    glDepthMask(GL_FALSE);
    //glEnable(GL_CULL_FACE);
    }
    /// Ratation (Animation):
    if(scene->anim == 1) glRotatef(scene->RotStrength,scene->axe_x,scene->axe_y,scene->axe_z);
    /// Axe Drawing :
    if(scene->axe == 1)  glCallList(scene->axeliste);
    /// Plan drawing :
    if(scene->plan == 1) glCallList(scene->planliste);
    /// Box Drawing:
    if(scene->box == 1) glCallList(scene->boxliste);

// Object Drawing :
// If No condition :
    if(scene->condition != 1) {
      if(scene->mesh == 1){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(scene->polyfactor, scene->polyunits);

    (scene->typedrawing == 1) ?
glDrawElements(GL_TRIANGLES, scene->PolyNumber, GL_UNSIGNED_INT, scene->PolyIndices_localPt)
:
glDrawElements(GL_QUADS, scene->PolyNumber, GL_UNSIGNED_INT, scene->PolyIndices_localPt);
    glDisable(GL_POLYGON_OFFSET_FILL);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
 }

 if(scene->line == 1) {
 glColor4f (scene->gridcol[0], scene->gridcol[1], scene->gridcol[2], scene->gridcol[3]);
 glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
 (scene->typedrawing == 1) ?
 glDrawElements(GL_TRIANGLES, scene->PolyNumber, GL_UNSIGNED_INT, scene->PolyIndices_localPt)
 :
 glDrawElements(GL_QUADS, scene->PolyNumber, GL_UNSIGNED_INT, scene->PolyIndices_localPt);
 glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
 }
 }
// End If No condition

//There is a condition :
    else  {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_POLYGON_OFFSET_FILL);

    if(scene->mesh == 1){
    glPolygonOffset(scene->polyfactor, scene->polyunits);
    glDrawElements(GL_TRIANGLES, scene->PolyNumberNotVerifyCND, GL_UNSIGNED_INT, scene->PolyIndices_localNotVerifyCND);
    }
    if(scene->cndmesh !=1 && scene->drawcnd == 1){
    makeallred(scene);
	//glColor3f (scene->condcol[0], scene->condcol[1], scene->condcol[2]);
    glDrawElements(GL_TRIANGLES, scene->PolyNumberVerifyCND, GL_UNSIGNED_INT, scene->PolyIndices_localVerifyCND);
    makeallred(scene);
    }

    glDisable(GL_POLYGON_OFFSET_FILL);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

 /// Draw the Mesh:
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if(scene->line == 1) {
    glColor4f (scene->gridcol[0], scene->gridcol[1], scene->gridcol[2], scene->gridcol[3]);
    glDrawElements(GL_TRIANGLES, scene->PolyNumberNotVerifyCND,
                   GL_UNSIGNED_INT,
                   scene->PolyIndices_localNotVerifyCND);
    }
    if(scene->cndmesh == 1 && scene->drawcnd == 1){
    glColor4f (scene->condcol[0], scene->condcol[1], scene->condcol[2], scene->condcol[3]);
    glDrawElements(GL_TRIANGLES, scene->PolyNumberVerifyCND, GL_UNSIGNED_INT, scene->PolyIndices_localVerifyCND);
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

 /// Draw the Border line:
    if(scene->border == 1){
    glLineWidth(4);
    glColor4f (1.0, 1.0, 1.0, 1.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, scene->PolyNumberBorderCND, GL_UNSIGNED_INT, scene->PolyIndices_localBorderCND);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glLineWidth(1);
    }
     }
 //End There is a condition :

// Minimal topology for isosurfaces:
   if (scene->typedrawing == 1 && scene->isobox == 1) {
   glColor4f (scene->gridcol[0], scene->gridcol[1], scene->gridcol[2], scene->gridcol[3]);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   startpl = 0;
   for(i = 0; i < scene->NbPolygnNbVertexPtMin; i++) {
     polysize       =  scene->PolyIndices_localPtMin[startpl++];
     glBegin(GL_POLYGON);
      for(j = 0; j < polysize; j++){
actualpointindice = scene->PolyIndices_localPtMin[startpl];
glVertex3f(scene->ArrayNorVer_localPt[6*actualpointindice+3],
           scene->ArrayNorVer_localPt[6*actualpointindice+4],
           scene->ArrayNorVer_localPt[6*actualpointindice+5]);
           startpl++;
     }
      glEnd();
       }
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   }
// End Minimal topology for isosurfaces



if(scene->norm == 1 ){
   glColor4f (0.8, 0., 0.7, 1.0);
for(i=0; i< scene->PolyNumber; i+=4) {
j = 6*scene->PolyIndices_localPt[i];
       glBegin( GL_LINES );
glVertex3f(scene->ArrayNorVer_localPt[j+3],
           scene->ArrayNorVer_localPt[j+4],
           scene->ArrayNorVer_localPt[j+5]);
glVertex3f(scene->ArrayNorVer_localPt[j+3]+40*scene->ArrayNorVer_localPt[j  ],
           scene->ArrayNorVer_localPt[j+4]+40*scene->ArrayNorVer_localPt[j+1],
           scene->ArrayNorVer_localPt[j+5]+40*scene->ArrayNorVer_localPt[j+2]);
       glEnd();
 }
 }
 
if(scene->transparency == 1)  {
 glDepthMask(GL_TRUE);
 //glDisable(GL_CULL_FACE);
}
/*
// Textured Ground :
    glColor3f (1.0, 1.0, 1.0);
    glEnable( GL_TEXTURE_2D );
	glBindTexture(GL_TEXTURE_2D, scene->texture[0]);
        glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.5f, 1.0f);
		glVertex3f(-600.0f, -600.0f,  -600.0f);
		glTexCoord2f(0.0f, 0.5f);
		glVertex3f( 600.0f, -600.0f,  -600.0f);
		glTexCoord2f(0.5f, 0.0f);
		glVertex3f( 600.0f,  600.0f,  -600.0f);
		glTexCoord2f(1.0f, 0.5f);
		glVertex3f(-600.0f,  600.0f,  -600.0f);	
        glEnd();

        glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-600.0f, -600.0f,  -600.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-600.0f, 600.0f,  -600.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-600.0f,  600.0f,  600.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-600.0f,  -600.0f,  600.0f);	
        glEnd();

        glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-600.0f, -600.0f, -600.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f( 600.0f, -600.0f, -600.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f( 600.0f, -600.0f,  600.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-600.0f, -600.0f,  600.0f);
        glEnd();

		glDisable( GL_TEXTURE_2D );
// End Textured Ground
*/
// Draw the scene:
    glFlush();
};

///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::paintGL()
{ int i;
  static int increase =1;
  LocalScene.PolyNumber = NbPolygnNbVertex[2*IndiceMorphFrame  ];
  i                     = NbPolygnNbVertex[2*IndiceMorphFrame+1];
  LocalScene.PolyIndices_localPt = &(PolyIndices_local[i]);
  if(LocalScene.morph  != 1 ) draw(&LocalScene);
  else {
  draw(&LocalScene);
  IndiceMorphFrame +=increase;
  if(IndiceMorphFrame == NbMorphFrame) {
   increase *= -1; IndiceMorphFrame +=increase;};
  if(IndiceMorphFrame < 0) {
   increase *= -1; IndiceMorphFrame +=increase;};
}
//if(LocalScene.infos == 1)  PrintInfos2(&LocalScene);
 if(LocalScene.infos == 1)  PrintInfos();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::mouseReleaseEvent( QMouseEvent *){
     };

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::mousePressEvent( QMouseEvent * e)
{
    if ( e->button() == QMouseEvent::LeftButton ) btgauche = 1;
    else btgauche = 0;
    if ( e->button() == QMouseEvent::RightButton ) btdroit = 1;
    else btdroit = 0;
    if ( e->button() == QMouseEvent::MidButton ) btmilieu = 1;
    else btmilieu = 0;

    old_y = LocalScene.oldRoty = e->y();
    old_x = LocalScene.oldRotx = e->x();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::mouseMoveEvent( QMouseEvent *e )
{  static double m[16];
   LocalScene.RotStrength = sqrt((LocalScene.oldRotx-e->x())*(LocalScene.oldRotx-e->x()) +
                       (LocalScene.oldRoty-e->y())*(LocalScene.oldRoty-e->y()))/2.;
   LocalScene.oldRoty = e->y();
   LocalScene.oldRotx = e->x();

// Scale function :
 if(btdroit ==1)  {
   if(old_y - e->y() > 0 ) LocalScene.ScalCoeff = 1.02f;
   else if( LocalScene.ScalCoeff > 0.1f ) LocalScene.ScalCoeff = 0.98f;
   glScalef(LocalScene.ScalCoeff, LocalScene.ScalCoeff, LocalScene.ScalCoeff);
   LocalScene.view_rotx = LocalScene.view_roty = 0.0;
 }
// Rotational function :
 if(btgauche ==1) {
  LocalScene.view_roty = -(old_y - e->y());
  LocalScene.view_rotx = -(old_x - e->x());
  LocalScene.ScalCoeff = 1.0;

  glGetIntegerv(GL_VIEWPORT,LocalScene.viewport);
  glGetDoublev(GL_MODELVIEW_MATRIX,LocalScene.matrix);
  memcpy(m, LocalScene.matrix, 16*sizeof(GLdouble));

  ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++///
   GLdouble det;
   GLdouble d12, d13, d23, d24, d34, d41;
   GLdouble tmp[16]; /* Allow out == in. */

   /* Inverse = adjoint / det. (See linear algebra texts.)*/
   /* pre-compute 2x2 dets for last two rows when computing */
   /* cofactors of first two rows. */
   d12 = (m31*m42-m41*m32);
   d13 = (m31*m43-m41*m33);
   d23 = (m32*m43-m42*m33);
   d24 = (m32*m44-m42*m34);
   d34 = (m33*m44-m43*m34);
   d41 = (m34*m41-m44*m31);

   tmp[0] =  (m22 * d34 - m23 * d24 + m24 * d23);
   tmp[1] = -(m21 * d34 + m23 * d41 + m24 * d13);
   tmp[2] =  (m21 * d24 + m22 * d41 + m24 * d12);
   tmp[3] = -(m21 * d23 - m22 * d13 + m23 * d12);

   /* Compute determinant as early as possible using these cofactors. */
   det = m11 * tmp[0] + m12 * tmp[1] + m13 * tmp[2] + m14 * tmp[3];

   /* Run singularity test. */
   if (det == 0.0) {
      printf("invert_matrix: Warning: Singular matrix.\n");
/*    memcpy(out,_identity,16*sizeof(double)); */
   }
   else {
      GLdouble invDet = 1.0 / det;
      /* Compute rest of inverse. */
      tmp[0] *= invDet;
      tmp[1] *= invDet;
      tmp[2] *= invDet;
      tmp[3] *= invDet;

      tmp[4] = -(m12 * d34 - m13 * d24 + m14 * d23) * invDet;
      tmp[5] =  (m11 * d34 + m13 * d41 + m14 * d13) * invDet;
      tmp[6] = -(m11 * d24 + m12 * d41 + m14 * d12) * invDet;
      tmp[7] =  (m11 * d23 - m12 * d13 + m13 * d12) * invDet;

      /* Pre-compute 2x2 dets for first two rows when computing */
      /* cofactors of last two rows. */
      d12 = m11*m22-m21*m12;
      d13 = m11*m23-m21*m13;
      d23 = m12*m23-m22*m13;
      d24 = m12*m24-m22*m14;
      d34 = m13*m24-m23*m14;
      d41 = m14*m21-m24*m11;

      tmp[8] =  (m42 * d34 - m43 * d24 + m44 * d23) * invDet;
      tmp[9] = -(m41 * d34 + m43 * d41 + m44 * d13) * invDet;
      tmp[10] =  (m41 * d24 + m42 * d41 + m44 * d12) * invDet;
      tmp[11] = -(m41 * d23 - m42 * d13 + m43 * d12) * invDet;
      tmp[12] = -(m32 * d34 - m33 * d24 + m34 * d23) * invDet;
      tmp[13] =  (m31 * d34 + m33 * d41 + m34 * d13) * invDet;
      tmp[14] = -(m31 * d24 + m32 * d41 + m34 * d12) * invDet;
      tmp[15] =  (m31 * d23 - m32 * d13 + m33 * d12) * invDet;

      memcpy(LocalScene.matrixInverse, tmp, 16*sizeof(GLdouble));
   }
            double ax,ay,az;
            ax = LocalScene.view_roty;
            ay = LocalScene.view_rotx;
            az = 0.0;
            anglefinal += (angle = sqrt(ax*ax + ay*ay)/(double)(LocalScene.viewport[2]+1)*360.0);
            /* Use inverse matrix to determine local axis of rotation */
            LocalScene.axe_x = Axe_x = LocalScene.matrixInverse[0]*ax + LocalScene.matrixInverse[4]*ay;
            LocalScene.axe_y = Axe_y = LocalScene.matrixInverse[1]*ax + LocalScene.matrixInverse[5]*ay;
            LocalScene.axe_z = Axe_z = LocalScene.matrixInverse[2]*ax + LocalScene.matrixInverse[6]*ay;
  ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++///
     glRotatef(angle,Axe_x,Axe_y,Axe_z);
 }
 old_y = e->y();
 old_x = e->x();
 updateGL();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::DrawPlan(){
   GLuint list;

 list = glGenLists(1);
 glNewList( list, GL_COMPILE );

glBegin( GL_LINE );
glVertex3f(-400.0, 0.0, -400.0);
glNormal3f(0.0, 0.0, 1.0);

glVertex3f(-400.0, 0.0, 400.0);
glNormal3f(0.0, 0.0, 1.0);

glVertex3f(400.0, 0.0, 400.0);
glNormal3f(0.0, 0.0, 1.0);

glVertex3f(400.0, 0.0, -400.0);
glNormal3f(0.0, 0.0, 1.0);
glEnd();

 glEndList();
//    return list;
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
static void draw()
{
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   if(GlLneSmooth == 1) {
   glEnable (GL_LINE_SMOOTH);
   glEnable (GL_BLEND);
   glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
   }

    //glRotatef(angle,bx,by,bz);
    //glScalef(LocalScene.ScalCoeff, LocalScene.ScalCoeff, LocalScene.ScalCoeff);

    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(scene->polyfactor, scene->polyunits);
    glDrawElements(GL_QUADS, NB_Poly , GL_UNSIGNED_INT, PolyIndices_pt);
    glDisable(GL_POLYGON_OFFSET_FILL);

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glLineWidth(0.5);
    glColor3f (0.2, 0.4, 0.2);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_QUADS, NB_Poly , GL_UNSIGNED_INT, PolyIndices_pt);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glFlush();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
GLuint OpenGlWidget::makeObject()
{
   int i, j;
   GLuint list;

 list = glGenLists(1);
 glNewList( list, GL_COMPILE );

    for (i=0; i< nb_ligne - coupure_ligne ; i++)
      for (j=0; j< nb_colone - coupure_col ; j++) {

glBegin( GL_QUADS );
glVertex3f(M3dObjet[i*3][j], M3dObjet[i*3+1][j],M3dObjet[i*3+2][j]);
glNormal3f(NorObjet[i*3][j], NorObjet[i*3+1][j], -NorObjet[i*3+2][j]);

glVertex3f(M3dObjet[(i+1)*3][j], M3dObjet[(i+1)*3 +1][j],M3dObjet[(i+1)*3+2][j]);
glNormal3f(NorObjet[(i+1)*3][j], NorObjet[(i+1)*3 +1][j], -NorObjet[(i+1)*3+2][j]);

glVertex3f(M3dObjet[(i+1)*3][j+1], M3dObjet[(i+1)*3+1][j+1],M3dObjet[(i+1)*3 +2][j+1]);
glNormal3f(NorObjet[(i+1)*3][j+1], NorObjet[(i+1)*3+1][j+1], -NorObjet[(i+1)*3 +2][j+1]);

glVertex3f(M3dObjet[i*3][j+1], M3dObjet[i*3 +1][j+1],M3dObjet[i*3+2][j+1]);
glNormal3f(NorObjet[i*3][j+1], NorObjet[i*3 +1][j+1], -NorObjet[i*3+2][j+1]);
glEnd();

}
    glEndList();
    return list;
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
GLuint OpenGlWidget::makeGrid()
{
   int i, j;
   static GLfloat ared[4] = {1.0, 0.0, 0.0, 1.0 };
   GLuint list;

    list = glGenLists( 1 );
    glNewList( list, GL_COMPILE );
    //glLineWidth( 3.0 );
    //glColor3f(255.0, 255.0, 255.0);

 for (i=0;i<nb_ligne - coupure_ligne ;i++)
    for (j=0; j<nb_colone - coupure_col ; j++)

{
glBegin(GL_LINE_LOOP);
glVertex3f(M3dObjet[i*3][j], M3dObjet[i*3+1][j],M3dObjet[i*3+2][j]);
glVertex3f(M3dObjet[(i+1)*3][j], M3dObjet[(i+1)*3 +1][j],M3dObjet[(i+1)*3+2][j]);
glVertex3f(M3dObjet[(i+1)*3][j+1], M3dObjet[(i+1)*3+1][j+1],M3dObjet[(i+1)*3 +2][j+1]);
glVertex3f(M3dObjet[i*3][j+1], M3dObjet[i*3 +1][j+1],M3dObjet[i*3+2][j+1]);
glEnd();
}
    glEndList();
    return list;
}

*/
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::timerEvent(QTimerEvent*)
{
    updateGL();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::update()
{
    updateGL();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::cutline(int){
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::step_morph(int){
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::latence_change(int){
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::linecolumn(int){
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::cutcolumn(int){
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::newFile()
{}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::clipok()
{}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::setFunction(int)
{}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::newGear()
{}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
OpenGlWidget::~OpenGlWidget()
{  delete(timer);
}
