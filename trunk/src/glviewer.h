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
#ifndef gear_H
#define gear_H

#include <qthread.h>
//#include <GL/glext.h>
#include <qgl.h>
#include <qapplication.h>
#include <math.h>
#include <qthread.h>
#include <qmutex.h>
#include <qpixmap.h>
#include <qwidget.h>
#include <qpainter.h>
#include <qmessagebox.h>
#include <qfile.h>
#include <qdir.h>
#include <qpngio.h>
#include <stdlib.h>
#include <string>
#include <qtimer.h>

/* NB. OpenGL Matrices are COLUMN major. */
#define MAT(m,r,c) (m)[(c)*4+(r)]

/* Here's some shorthand converting standard (row,column) to index. */
#define m11 MAT(m,0,0)
#define m12 MAT(m,0,1)
#define m13 MAT(m,0,2)
#define m14 MAT(m,0,3)
#define m21 MAT(m,1,0)
#define m22 MAT(m,1,1)
#define m23 MAT(m,1,2)
#define m24 MAT(m,1,3)
#define m31 MAT(m,2,0)
#define m32 MAT(m,2,1)
#define m33 MAT(m,2,2)
#define m34 MAT(m,2,3)
#define m41 MAT(m,3,0)
#define m42 MAT(m,3,1)
#define m43 MAT(m,3,2)
#define m44 MAT(m,3,3)
//    static double m[16];
///************* A new Structure the scene *********///
struct  Scene {
    GLfloat * ArrayNorVer_localPt;
    GLuint  * PolyIndices_localPt;
    GLuint  * NbPolygnNbVertexPt ;
    GLuint  * PolyIndices_localPtMin;
    int       NbPolygnNbVertexPtMin ;
    GLfloat * ArrayNorVer_localPtCND;
    GLuint   *PolyIndices_localVerifyCND;
    GLuint   *PolyIndices_localNotVerifyCND;
    GLuint   *PolyIndices_localBorderCND;

    GLint    PolyNumber;
    GLint    PolyNumberBorderCND;
    GLint    PolyNumberVerifyCND;
    GLint    PolyNumberNotVerifyCND;

    GLint    border;
    GLint    cndmesh;
    GLint    drawcnd;
    GLint    anim;
    GLint    morph;
    GLint    typedrawing;
    GLint    mesh;
    GLint    front;
    GLint    back;
    GLint    smoothline;
    GLint    transparency;
    GLint    smoothpoly;
    GLint    box;
    GLint    isobox;
    GLint    interior;
    GLint    exterior;
    GLint    infos;
    GLint    infosdetails[10];
    GLint    line; ///Draw line on top of filled polygons
    GLint    axe;
    GLint    clip;
    GLint    norm;
    GLint    plan;
    GLint    condition;
    GLuint   axeliste;
    GLuint   boxliste;
    GLuint   planliste;
    GLfloat  boxlimits[18];
    GLuint   texture[100];
    GLint    ColorOrTexture[10];
    GLuint   moreliste[10];
    GLuint  *morelistept[10];
    GLfloat *morefloatpt[10];
    GLfloat  morefloat[10];
    GLfloat  frontcol[4];
    GLfloat  backcol[4];
    GLfloat  gridcol[4];
    GLfloat  groundcol[4];
    GLfloat  condcol[4];

    GLfloat RotStrength, oldRotx, oldRoty;
    GLfloat zminim, BoxLimits[3][6];
    GLint viewport[4];
    GLfloat polyfactor;
    GLfloat polyunits;
    double matrix[16];
    double matrixInverse[16];
    double axe_x, axe_y, axe_z, ScalCoeff, view_rotx, view_roty, view_rotz;
              };


class OpenGlWidget : public QGLWidget, public QThread
{
public :
    static int TransparenceVal;
    int colortype, btgauche, btdroit, btmilieu,
    width, height, latence,
    nb_ligne, nb_colone, coupure_col, coupure_ligne,
    IDGlWindow, PolyNumber, VertexNumber,
    IndiceMorphFrame, NbMorphFrame;
    int isoline, isocolumn, isodepth,
        cpisoline, cpisocolumn, cpisodepth, TypeTriangle;
    QTimer  * timer;
    GLuint  * PolyIndices_local;
    GLuint  * PolyIndicesMinimal_local;
    int     * TypeIsoSurfaceTriangleListeCND;
    int MaximumNumberPoints, MaximumNumberTriangles;
    double newbox[16];
    GLuint NbPolygnNbVertex[2*50];
    int  PolyNumberTab[50];
    double Axe_x, Axe_y, Axe_z, angle, val1, val2, val3, old_x, old_y, old_z;
    Scene  LocalScene;
    int jpg_ok, png_ok, bmp_ok, quality_image;
    QPixmap * pixmap;
    QImage tex1;

public:
    OpenGlWidget( QWidget *parent=0, const char *name=0 );
    ~OpenGlWidget();
    void initializeGL();
    void resizeGL(int, int);
    void paintGL();
    void update();
    void timerEvent( QTimerEvent * );
    void mousePressEvent( QMouseEvent *);
    void mouseMoveEvent( QMouseEvent *);
    void mouseReleaseEvent( QMouseEvent *);
    virtual   void run();
    void valueChanged();
    void InitGlParameters();
    void InitGlMorph();
public slots:
    void newFile();
    void newGear();
    void setFunction(int);
    void cutline(int);
    void cutcolumn(int);
    void linecolumn(int);
    void boxok();
    void anim();
    void morph();
    void start();
    void starttimer();
    void stoptimer();
    bool timeractif();
    void restarttimer(int);
    void cnd();
    void cndmesh();
    void drawborder();
    void PrintInfos();
    void png();
    void jpg();
    void bmp();
    void quality(int);
    void screenshot();
    void conditionok();
    void clipok();
    void infosok();
    void latence_change(int);
    void step_morph(int);
    void red(int);
    void green(int);
    void blue(int);
    void transparency(int);
    void transparence();
    void scalcoeff(double);
    void CutLineIndex(int);
    void CutColIndex(int);
    void plan();
    void fog();
    void meshOk();
    void smoothpoly();
    void smoothline();
    void frontSurf();
    void backSurf();
    void clipOk();
    void axeOk();
    void normOk();
    void infosOk();
    void boxOk();
    void isoboxOk();
    void lineOk();
    void DrawPlan();
    void ChangeMaxResolution(int, int);
    void setColorsTo(int *);
    void LoadImage(QString);
    void ActivateTexture();
    void RunPovscript(int);
    QImage Copyscreenshot();
    void fct_1(double*, int*, QString*);
    void setGridColor(GLfloat, GLfloat, GLfloat, GLfloat);
    void setGroundColor(GLfloat, GLfloat, GLfloat, GLfloat);
    void setFrontColor(GLfloat, GLfloat, GLfloat, GLfloat);
    void setBackColor(GLfloat, GLfloat, GLfloat, GLfloat);
};
#endif
