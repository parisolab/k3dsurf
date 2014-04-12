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
#include <qgl.h>
#include <qpointarray.h>
#include <qpainter.h>
#include <qbrush.h>
#include <qstring.h>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <list>
#include "Matrix3D.h"
#include "Matrix4D.h"
#include "nd/Matrix5D.h"
#include "nd/Matrix6D.h"
#include "fparser/fparser.h"


using std::string;
using std::vector;
using std::list;



//void *  f_thread(void *);
///************* A new Class represent a poly *********///
class  Prop_poly {
public:
   QPointArray * pl;
   double valeur_z;
   double valeur_cos;
   int zbuffer_validity; // to use for drawing test
   int condition_validity; // condition verfified ?
   int Norx;
   int Nory;   
   Prop_poly (QPointArray * p=NULL,double z=0, double cos=0, int val = 1, int cond=1)
     {
        pl         = p;
        valeur_z   = z;
        valeur_cos = cos;
	    zbuffer_validity = val;
	    condition_validity = cond;
     }
                  };


/** The representation of a 3D model */
class Model3D {
public:
    double Tre2[300][100], Tre[300][100], Tre2_save[300][100],
           HL[300][100], HR[300][100], DL[300][100], DR[300][100],//to replace hidden points
           HL2[300][100], HR2[300][100], DL2[300][100], DR2[300][100], 
           HL3[300][100], HR3[300][100], DL3[300][100], DR3[300][100],
	     Nor[300][100], Nor2[300][100], Nor3[300][100],
           Tre3[300][100], shape4D[400][100], shape5D[500][100], shape6D[600][100],
           Axes_array[6][300], Axes_array2[6][300], Axes_array_projection[6][300];
    int    zbuffer[11][2*10000+300]; // +300 for 3 axes
    double rayon[2*10000+300]; // +300 for 3 axes
    int hidden_points[100][100];
    double tmp[300], tmp2[300];
    double v1[3], v2[3], Obser[3], norm[3], Oprime[3], vec[3];
    double D;

    QPointArray *CurvePoints;
    int CurvePointsXY[2][100];
    int nb_CurvePoints;

    Matrix3D mat, mat_rotation, mat_rotation_save, mat_rotation_first_save, mat_rotation_second_save,
    mat_homothetie, mat_translation, mat_inversetranslation, mat_first_obj, mat_second_obj;
    Matrix4D mat4D, mat_rotation4D, mat_rotation_save4D, mat_homothetie4D, mat_translation4D, mat_inversetranslation4D;
    Matrix5D mat5D, mat_rotation5D, mat_rotation_save5D, mat_homothetie5D, mat_translation5D, mat_inversetranslation5D;
    Matrix6D mat6D, mat_rotation6D, mat_rotation_save6D, mat_homothetie6D, mat_translation6D, mat_inversetranslation6D;

    int nb_ligne, nb_colone;
    int coupure_col, nb_licol, coupure_ligne, ligne_cube, colone_cub, showhelp,independantwindow;

    double angley, anglex, angley_rlatif, anglex_rlati, ancienx ,ancieny;
    double tetaxy, tetaxz, tetayz, tetaxw, tetayw, 
           tetazw, tetaxt, tetayt, tetazt, tetawt,
	   tetaxs, tetays, tetazs, tetaws, tetats,
	   tetaxy_ok, tetaxz_ok, tetayz_ok,tetaxw_ok, tetayw_ok, tetazw_ok, 
	   tetaxt_ok, tetayt_ok, tetazt_ok, tetawt_ok,
	   tetaxs_ok, tetays_ok, tetazs_ok, tetaws_ok, tetats_ok;	
    double teta5xy, teta5xz, teta5yz, teta5xw, teta5yw, 
           teta5zw, teta5xt, teta5yt, teta5zt, teta5wt, 
	   teta5xy_ok, teta5xz_ok, teta5yz_ok, teta5xw_ok, teta5yw_ok,
	   teta5zw_ok, teta5xt_ok, teta5yt_ok, teta5zt_ok, teta5wt_ok;

    double MINX,MINY,MINZ,MINW,MINT,MINS, 
           MAXX,MAXY,MAXZ,MAXW,MAXT,MAXS,
           DIFX,DIFY,DIFZ,DIFW,DIFT,DIFS,
	   DIFMAXIMUM;
    double minimumx,maximumx,minimumy,maximumy,minimumz,maximumz,translatex,translatey;

    FunctionParser myParser, myParserX, myParserY, myParserZ, myParserW,  myParserT, myParserS,
                   myParserX_2, myParserY_2, myParserZ_2, f1, 
		           myParser_spherical, myParser_cylindrical,
                   myParser_condition;
    QString  expression_X, expression_Y, expression_Z, expression_W, expression_T, expression_S,
             inf_u, sup_u, inf_v, sup_v, 
             expression_Z_2, expression_Y_2, expression_X_2, inf_u_2, sup_u_2, inf_v_2, sup_v_2,  
             newfct, expression_implicite, coefficient_n, keyboard, 
	         spherical_expression, cylindrical_expression,
             condition_expression,
             expression_X_save, expression_Y_save, expression_Z_save, quotient;



     double  v_inf, v_sup,u_inf,u_sup,dif_v,dif_u,
             v_inf_2, v_sup_2,u_inf_2,u_sup_2,dif_v_2,dif_u_2;

     double facteur, coefficient, tp1, tp2, tp3, tp4, tp5, tp6, 
            caa, bab, cab, baa, ba, ca;

     double r1, r2, r3, r4, maxr;

     int X_averege , Y_averege,

    X_averege1, Y_averege1,

    X_averege2, Y_averege2,

    X_averege3, Y_averege3,

    X_averege4, Y_averege4 ;

    int nb_intersection , nb_intersection1, nb_intersection2, 

        nb_intersection3, nb_intersection4 ;

    int rapport1, rapport2, rapport3, rapport4;

    int point_interior, point_interior1, 

        point_interior2, point_interior3, 

        point_interior4  ;
    int zbuffer_active_ok, zbuffer_quality;
	int there_is_condition, draw_hidden_poly_and_nonhidden, 
        draw_cond_mesh, draw_poly_normals;

    double center[3]; // to know where is the center in every time
    double  boiteenglobante[24], boiteenglobante2[24];
    double max_x,max_y,min_x,min_y,dif_x,dif_y,decalagex, decalagey,
          tmp_x,tmp_y;
    int   largeur_fenetre,hauteur_fenetre, demi_hauteur, demi_largeur, 
    two_separate_objects, moitie_colone, change_first_object, change_second_object;
    QPointArray * tableaureferences[2*(100)*(100) + 300];
    Prop_poly * tableau;
    QPointArray  poly;
    vector<Prop_poly *> vecteur_poly;
    //list<Prop_poly *> vecteur_poly; //list shows 10%CPU overhead than vectors!!!
    int mesh, box, clipping, DefineNewFct,infos,two_system, 
        fourdimshapes, fivedimshapes, sixdimshapes, 
	sphericaldef, cylindricaldef, implicitdef, supershape;
	double m1, a_1, b_1, n1_1, n2_1, n3_1,
	       m2, a_2, b_2, n1_2, n2_2, n3_2;
    QString sm1, sa_1, sb_1, sn1_1, sn2_1, sn3_1,
	        sm2, sa_2, sb_2, sn1_2, sn2_2, sn3_2;
    QString LagrangianX[100], LagrangianY[100];                 ///33333333333
    int     LagrangCoefX[100], LagrangCoefY[100]; 
    double morph_param, step, latence, coefficent_fct_implicite, coefficent_fct_implicite_parity, axe_size;
    int  frontsurfr, frontsurfg, frontsurfb,
         backsurfr, backsurfg, backsurfb,
         gridliner, gridlineg, gridlineb, 
         backgroundr, backgroundg, backgroundb, 
	 interior_surface, exterior_surface,
	 fronttrans, backtrans, there_is_hidden_points, precision, drawaxes_ok,
	 axe_width, axe_center, nb_axe_point; 
    QBrush palette_front_face[300], palette_back_face[300], palette_cond_face[300];

    double DIFX_save, DIFY_save, DIFZ_save,
           MINX_save, MINY_save, MINZ_save,
           DIFX_tmp, DIFY_tmp, DIFZ_tmp,
           MINX_tmp, MINY_tmp, MINZ_tmp;
    double newscalex, newscaley, newscalez;
    //double isosurface[150][150][150];


GLfloat NormVertexTab[50*66000];
GLuint IndexPolyTab[50*48000];
int NbVertex;
GLuint NbPolygn;
GLuint NbPolygnNbVertex[2*50];



public:
 Model3D();
 ~Model3D();
 void fct_bouton_gauche3 ();
 void fct_bouton_droit3 ();
 void fct_bouton_milieu3 ();

 void  rotation3();   // rotational 3D transformation
 void  rotation4();   // rotational 4D transformation
 void  rotation5();   // rotational 5D transformation 
 void  rotation6();   // rotational 5D transformation

 void fct_bouton_Anim3 ();
 void fct_bouton_Anim4 ();
 void fct_bouton_Anim5 ();
 void fct_bouton_Anim6 ();

 void  calcul_points3();
 void  calcul_points4();
 void  calcul_points5();
 void  calcul_points6();

 void fct_bouton_Morph3();
 void fct_calcul2 (); 
 void fct_calcul3 ();
 void  homothetie3();
 void  translation3(); 
 void initialiser_parametres3();
 void  normalisation3();

 void initialiser_parseur3();
 void calcul_objet3();
 void boite_englobante3();
 void initialiser_palette();
 int modulo (int, int);
 void tracer2(QPainter &);
 void tracer3(QPainter &);
 void tracer4(QPainter &);
 double maximum_z(double, double, double, double);
 double minimum_z(double, double, double, double);
 void fct_bouton_AnimMorph();
 void parse_expression();

 void boite_englobante4D(); // special 4D
 void project_4D_to_3D();   // special 4D

 void boite_englobante5D(); // special 5D
 void project_5D_to_4D();   // special 5D

 void boite_englobante6D(); // special 6D
 void project_6D_to_5D();   // special 6D

 double supershape_fct(double n1, double n2, double n3, double m, double a, double b, double Y); 

 void scalex(int);
 void scaley(int);
 void scalez(int);

 void twistex(double, double);
 void twistey(double, double);
 void twistez(double, double);

 void coilx(double, double);
 void coily(double, double);
 void coilz(double, double);

 void dumpx();
 void dumpy();
 void dumpz();

 void initialisecoeffscale();

 void LagrangePolynome();

/// FOR GL Window :
 void SpecialAnim_1();
 void SpecialAnim_2(GLfloat *, GLuint *);
 void SpecialAnim_3(GLfloat *, GLuint *);

 void SpecialMorph_1();
 void SpecialMorph_2(GLfloat * , GLuint *, GLuint *, int);
 void SpecialMorph_3(GLfloat *, GLuint *);
 void RunPovScript();
 void stopcalculations();
};
