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
#include <qpixmap.h>
#include "Model3D.h"

using std::string;
using std::vector;
using std::list;

///+++++++++++++++++++++++++++++++++++++++++
void Model3D::RunPovScript(){
};

///+++++++++++++++++++++++++++++++++++++++++
void Model3D::stopcalculations(){
};

///+++++++++++++++++++++++++++++++++++++++++
void Model3D::LagrangePolynome(){
int i,j;
   /// Initialisation :
     for(i = 0; i < nb_CurvePoints; i++) {
     LagrangianX[i] = "";
     LagrangianY[i] = "";
     }
  /// Polynome construction :
   if(  nb_CurvePoints > 1) {
     for(i = 0; i < nb_CurvePoints -1; i++)
      for(j=0; j < nb_CurvePoints && j != i ; j++){
     LagrangianX[i] += "(u - "+QString::number(CurvePointsXY[0][j])+")";
     LagrangianY[i] += "(v - "+QString::number(CurvePointsXY[1][j])+")";
        if((j+1) <nb_CurvePoints && (j+1) != i) {
            LagrangianX[i] += "*";
            LagrangianY[i] += "*";
        }
     }
  /// Here we compute coefficients to use with Lagrangian Polynomes
     for(i = 0; i < nb_CurvePoints -1; i++) {
     LagrangCoefX[i] = 0 ;
     LagrangCoefY[i] = 0;
     }
   }
}



void Model3D::dumpx() {

quotient = "("+expression_X_save+" - "+ QString::number(MINX_save)+")/"+QString::number(DIFX_save) ;

    expression_Y = "("+expression_Y_save+") * "+quotient;
    expression_Z = "("+expression_Z_save+") * "+quotient;
    expression_X = expression_X_save;

    fct_calcul3();

}

void Model3D::dumpy() {

    quotient = "("+expression_Y_save+" - "+ QString::number(MINY_save)+")/"+QString::number(DIFY_save) ;

    expression_X = "("+expression_X_save+") * "+quotient;
    expression_Z = "("+expression_Z_save+") * "+quotient;
    expression_Y = expression_Y_save;

    fct_calcul3();

}


void Model3D::dumpz() {

    quotient = "("+expression_Z_save+" - "+ QString::number(MINZ_save)+")/"+QString::number(DIFZ_save) ;

    expression_X = "("+expression_X_save+") * "+quotient;
    expression_Y = "("+expression_Y_save+") * "+quotient;
    expression_Z = expression_Z_save;

    fct_calcul3();

}


void Model3D::coilx(double nb_twiste, double coeff_rayon) {
double rayonx = coeff_rayon*sqrt(DIFY_save*DIFY_save + DIFZ_save*DIFZ_save);

    expression_Y = expression_Y_save+" + "+
    QString::number(rayonx)+
    " * cos(("+expression_X_save+" - "+
    QString::number(MINX_save)+")*2*pi*"+QString::number(nb_twiste)+"/"+
    QString::number(DIFX_save)+")";

    expression_Z = expression_Z_save+" + "+
    QString::number(rayonx)+
    " * sin(("+expression_X_save+" - "+
    QString::number(MINX_save)+")*2*pi*"+QString::number(nb_twiste)+"/"+
    QString::number(DIFX_save)+")";

    expression_X = expression_X_save;

    fct_calcul3();

}

void Model3D::coily(double nb_twiste, double coeff_rayon) {
double rayony = coeff_rayon*sqrt(DIFX_save*DIFX_save + DIFZ_save*DIFZ_save);

    expression_X = expression_X_save+" + "+
    QString::number(rayony)+
    " * cos(("+expression_Y_save+" - "+
    QString::number(MINY_save)+")*2*pi*"+QString::number(nb_twiste)+"/"+
    QString::number(DIFY_save)+")";

    expression_Z = expression_Z_save+" + "+
    QString::number(rayony)+
    " * sin(("+expression_Y_save+" - "+
    QString::number(MINY_save)+")*2*pi*"+QString::number(nb_twiste)+"/"+
    QString::number(DIFY_save)+")";
    expression_Y = expression_Y_save;

    fct_calcul3();

}



void Model3D::coilz(double nb_twiste, double coeff_rayon) {
 double rayonz = coeff_rayon*sqrt(DIFX_save*DIFX_save + DIFY_save*DIFY_save);

    expression_X = expression_X_save+" + "+
    QString::number(rayonz)+
    " * cos(("+expression_Z_save+" - "+
    QString::number(MINZ_save)+")*2*pi*"+QString::number(nb_twiste)+"/"+
    QString::number(DIFZ_save)+")";

    expression_Y = expression_Y_save+" + "+
    QString::number(rayonz)+
    " * sin(("+expression_Z_save+" - "+
    QString::number(MINZ_save)+")*2*pi*"+QString::number(nb_twiste)+"/"+
    QString::number(DIFZ_save)+")";

    expression_Z = expression_Z_save;

    fct_calcul3();

}




void Model3D::twistex(double nb_twiste, double coeff_rayon) {

 double rayonx = coeff_rayon;// *sqrt(DIFY_save*DIFY_save + DIFZ_save*DIFZ_save);

    expression_Y = QString::number(rayonx)+" * ("+expression_Y_save+
    " * cos(("+expression_X_save+" - "+
    QString::number(MINX_save)+")*2*pi*"+QString::number(nb_twiste)+"/"+
    QString::number(DIFX_save)+") - "+
    expression_Z_save+" * sin(("+expression_X_save+" - "+
    QString::number(MINX_save)+")*2*pi*"+QString::number(nb_twiste)+"/"+
    QString::number(DIFX_save)+"))  ";

    expression_Z = QString::number(rayonx)+" * ("+expression_Y_save+
    " * sin(("+expression_X_save+" - "+
    QString::number(MINX_save)+")*2*pi*"+QString::number(nb_twiste)+"/"+
    QString::number(DIFX_save)+") + "+
    expression_Z_save+" * cos(("+expression_X_save+" - "+
    QString::number(MINX_save)+")*2*pi*"+QString::number(nb_twiste)+"/"+
    QString::number(DIFX_save)+"))  ";

    expression_X = expression_X_save;

    fct_calcul3();

/*


    expression_Y = expression_Y_save+" + "+
    QString::number(rayonx)+
    " * cos(("+expression_X_save+" - "+
    QString::number(MINX_save)+")*2*pi*"+QString::number(nb_twiste)+"/"+
    QString::number(DIFX_save)+")";

    expression_Z = expression_Z_save+" + "+
    QString::number(rayonx)+
    " * sin(("+expression_X_save+" - "+
    QString::number(MINX_save)+")*2*pi*"+QString::number(nb_twiste)+"/"+
    QString::number(DIFX_save)+")";

    expression_X = expression_X_save;

    fct_calcul3();
*/
}

void Model3D::twistey(double nb_twiste, double coeff_rayon) {

double rayony = coeff_rayon;// *sqrt(DIFX_save*DIFX_save + DIFZ_save*DIFZ_save);

    expression_X = QString::number(rayony)+" * ("+expression_X_save+
    " * cos(("+expression_Y_save+" - "+
    QString::number(MINY_save)+")*2*pi*"+QString::number(nb_twiste)+"/"+
    QString::number(DIFY_save)+") - "+
    expression_Z_save+" * sin(("+expression_Y_save+" - "+
    QString::number(MINY_save)+")*2*pi*"+QString::number(nb_twiste)+"/"+
    QString::number(DIFY_save)+"))  ";

    expression_Z = QString::number(rayony)+" * ("+expression_X_save+
    " * sin(("+expression_Y_save+" - "+
    QString::number(MINY_save)+")*2*pi*"+QString::number(nb_twiste)+"/"+
    QString::number(DIFY_save)+") + "+
    expression_Z_save+" * cos(("+expression_Y_save+" - "+
    QString::number(MINY_save)+")*2*pi*"+QString::number(nb_twiste)+"/"+
    QString::number(DIFY_save)+"))  ";

    expression_Y = expression_Y_save;

    fct_calcul3();

/*
double rayony = coeff_rayon*sqrt(DIFX_save*DIFX_save + DIFZ_save*DIFZ_save);

    expression_X = expression_X_save+" + "+
    QString::number(rayony)+
    " * cos(("+expression_Y_save+" - "+
    QString::number(MINY_save)+")*2*pi*"+QString::number(nb_twiste)+"/"+
    QString::number(DIFY_save)+")";

    expression_Z = expression_Z_save+" + "+
    QString::number(rayony)+
    " * sin(("+expression_Y_save+" - "+
    QString::number(MINY_save)+")*2*pi*"+QString::number(nb_twiste)+"/"+
    QString::number(DIFY_save)+")";

    expression_Y = expression_Y_save;

    fct_calcul3();
*/
}


void Model3D::twistez(double nb_twiste, double coeff_rayon) {
 double rayonz = coeff_rayon;// *sqrt(DIFX_save*DIFX_save + DIFY_save*DIFY_save);


    expression_X = QString::number(rayonz)+" * ("+expression_X_save+
    " * cos(("+expression_Z_save+" - "+
    QString::number(MINZ_save)+")*2*pi*"+QString::number(nb_twiste)+"/"+
    QString::number(DIFZ_save)+") - "+
    expression_Y_save+" * sin(("+expression_Z_save+" - "+
    QString::number(MINZ_save)+")*2*pi*"+QString::number(nb_twiste)+"/"+
    QString::number(DIFZ_save)+"))  ";

    expression_Y = QString::number(rayonz)+" * ("+expression_X_save+
    " * sin(("+expression_Z_save+" - "+
    QString::number(MINZ_save)+")*2*pi*"+QString::number(nb_twiste)+"/"+
    QString::number(DIFZ_save)+") + "+
    expression_Y_save+" * cos(("+expression_Z_save+" - "+
    QString::number(MINZ_save)+")*2*pi*"+QString::number(nb_twiste)+"/"+
    QString::number(DIFZ_save)+"))  ";

    expression_Z = expression_Z_save;

    fct_calcul3();
/*
    quotient = QString::number(coeff_rayon)+"*(("+expression_Z_save+" - "+ QString::number(MINZ_save)+")/"+QString::number(DIFZ_save)+")" ;

    expression_X = "("+expression_X_save+") * "+quotient;
    expression_Y = "("+expression_Y_save+") * "+quotient;
    expression_Z = expression_Z_save;

    fct_calcul3();
*/
}

void Model3D::scalex(int coeff) {
 newscalex = (double)coeff/(double)10; ///(double)(oldcoeff);

    if(newscalex != 1)
    expression_X = QString::number(newscalex)+"*("+expression_X_save+")";
    else expression_X = expression_X_save;

    if(newscaley != 1)
    expression_Y = QString::number(newscaley)+"*("+expression_Y_save+")";
    else expression_Y = expression_Y_save;

    if(newscalez != 1)
    expression_Z = QString::number(newscalez)+"*("+expression_Z_save+")";
    else expression_Z = expression_Z_save;

    fct_calcul3();

}

void Model3D::scaley(int coeff) {
    newscaley = (double)coeff/(double)10; ///(double)(oldcoeff);

	if(newscalex != 1)
	expression_X = QString::number(newscalex)+"*("+expression_X_save+")";
	else expression_X = expression_X_save;

	if(newscaley != 1)
    expression_Y = QString::number(newscaley)+"*("+expression_Y_save+")";
    else expression_Y = expression_Y_save;

	if(newscalez != 1)
    expression_Z = QString::number(newscalez)+"*("+expression_Z_save+")";
    else expression_Z = expression_Z_save;

     fct_calcul3();
}

void Model3D::scalez(int coeff) {
    newscalez = (double)coeff/(double)10; ///(double)(oldcoeff);

    if(newscalex != 1)
    expression_X = QString::number(newscalex)+"*("+expression_X_save+")";
    else expression_X = expression_X_save;

    if(newscaley != 1)
    expression_Y = QString::number(newscaley)+"*("+expression_Y_save+")";
    else expression_Y = expression_Y_save;

    if(newscalez != 1)
    expression_Z = QString::number(newscalez)+"*("+expression_Z_save+")";
    else expression_Z = expression_Z_save;

    fct_calcul3();
}

void Model3D::initialisecoeffscale(){
    newscalex = newscaley = newscalez = 1;
      }

/*****************************************************************************/
/*****************************************************************************/
   Model3D::~Model3D(){
delete tableau;
for (int j=0; j < 20300; j++)  {delete  tableaureferences[j];};
delete CurvePoints;
}

/*****************************************************************************/
/*****************************************************************************/
   Model3D::Model3D( )
        {
         //=========== La premiere figure " klein" a dessiner au lancement======
        nb_licol = 25;
        backtrans  = -1;
        fronttrans = -1;

        for (int j=0; j < 20300; j++)
           tableaureferences[j] = new QPointArray(4);
        tableau = new Prop_poly[2* 100 * 100 + 300];

        CurvePoints = new QPointArray(100); // Up to 100 points for the curve
        nb_CurvePoints = 0;

        expression_X = "(3*(1+sin(v)) + 2*(1-cos(v)/2)*cos(u))*cos(v)";
        expression_Y = "(4+2*(1-cos(v)/2)*cos(u))*sin(v)";
        expression_Z = "-2*(1-cos(v)/2) * sin(u)";
        inf_u        = "0";
        sup_u        = "2*pi";
        inf_v        = "0";
        sup_v        = "2*pi";

       two_system = -1;  
/*
        expression_X_2 = "4*sin(v)";
        expression_Y_2 = "3*(1+sin(v))*cos(v) - 2*(1-cos(v)/2)*cos(u)";
        expression_Z_2 = "-2*(1-cos(v)/2)* sin(u)";
        inf_u_2        = "0";
        sup_u_2        = "2*pi";
        inf_v_2        = "pi";
        sup_v_2        = "2*pi";
*/
        keyboard ="";
        coupure_ligne = coupure_col = 0;

        backsurfr = 249;
        backsurfg = 170;
        backsurfb = 0;

        frontsurfr = 0;
        frontsurfg = 210;
        frontsurfb = 0;

        anglex = 0.0;angley = 0.0;
        gridliner = 0;
        gridlineg = 100;
        gridlineb = 4;

        initialiser_palette();
        initialiser_parametres3();
        initialiser_parseur3();
        parse_expression();
        calcul_objet3();  // Utilisation du parseur..
        boite_englobante3();
        //normalisation3(); // Calcul des normales

        mat.unit(); // On applique la matrice unite a la matrice principale 3D
        mat4D.unit(); // On applique la matrice unite a la matrice principale 4D
        rotation3();      // rotation de l'objet....
        homothetie3();    // pour faire entrer l'objet ds la boite englobante..
        calcul_points3(); // On applique la rotation et l'homothetie
           }

/*****************************************************************************/
/*****************************************************************************/


void Model3D::initialiser_parametres3() {
// Incredible...gcc don't complain for "," caractere...
        nb_ligne = nb_licol;
        nb_colone = nb_licol;
        largeur_fenetre = 620;
        hauteur_fenetre = 620;
        demi_hauteur = hauteur_fenetre/2;
	demi_largeur = largeur_fenetre/2;
	//facteur = (double)1.0;
        Oprime[0]=(double)0.0;
        Oprime[1]=(double)0.0;
        Oprime[2]=(double)800.0;
        D=460;
        coefficient =  1.0f ;
	mesh = 1, box = 1; clipping =1; morph_param = 1; step = 0.1;
	DefineNewFct = -1, infos =1, latence = 30; implicitdef = -1;
	fourdimshapes = -1; fivedimshapes = -1; sixdimshapes = -1;
	sphericaldef = -1; cylindricaldef = -1;
	zbuffer_active_ok = -1;
	zbuffer_quality   = 5; //maximum

        there_is_condition = -1; // No condition imposed to the ploting
	//condition_expression = "(x^2 + y^2 + z^2) > 1";
	condition_expression = "((x^2 + y^2) > 0.05) & ((t*x+y+z) > -1) ";
	//condition_expression = "((x+y+z) > 0.004)";
	//condition_expression = "(x+y+z) > 1";
        precision = 10; //used for calculating points to replace hidden points
	                //equivalent to a grid with (nb_ligne * precision) points
	there_is_hidden_points = -1; // there is no hidden points
	draw_hidden_poly_and_nonhidden = -1;
	draw_cond_mesh = 1;
	draw_poly_normals    = -1;
	two_separate_objects = -1;  // we have one object
	change_first_object  =  1;  // draw first object
	change_second_object =  1;  // draw second object
	showhelp = -1;
	supershape  = -1;

	drawaxes_ok = -1;
	axe_width   = 2;
	axe_size    = 1;
	axe_center  = 1;// Absolute center (0,0,0)
        nb_axe_point = 25;

	center[0] = center[1] = center[2] = 0;
        exterior_surface = 1;
	interior_surface = 1;
	independantwindow = -1;
	tetaxy = 3;tetaxz = 3; tetayz = 3;
	tetaxw = 3; tetayw = 3; tetazw = 3;
	tetaxt = 3; tetayt = 3; tetazt = 3; tetawt = 3;
	tetaxs = 3; tetays = 3; tetazs = 3; tetaws = 3; tetats = 3;
	tetaxy_ok = -1; tetaxz_ok = -1; tetayz_ok = -1;
	tetaxw_ok = -1; tetayw_ok = -1; tetazw_ok = -1;
	tetaxt_ok = -1; tetayt_ok = -1; tetazt_ok = -1; tetawt_ok = -1;
	tetaxs_ok = -1; tetays_ok = -1; tetazs_ok = -1; tetaws_ok = -1; tetats_ok = -1;
	// initialisation des matrices 3D
        mat = Matrix3D();
	mat_first_obj  = Matrix3D();
	mat_second_obj = Matrix3D();
	mat_rotation_first_save   = Matrix3D();
	mat_rotation_second_save  = Matrix3D();

	mat_rotation      = Matrix3D();
        mat_rotation_save = Matrix3D();
        mat_homothetie    = Matrix3D();
        mat_translation   = Matrix3D();
        mat_inversetranslation = Matrix3D();

        // initialisation des matrices 4D
        mat4D                    = Matrix4D();
        mat_rotation4D           = Matrix4D();
        mat_rotation_save4D      = Matrix4D();
        mat_homothetie4D         = Matrix4D();
        mat_translation4D        = Matrix4D();
        mat_inversetranslation4D = Matrix4D();

        // initialisation des matrices 5D
        mat5D                    = Matrix5D();
        mat_rotation5D           = Matrix5D();
        mat_rotation_save5D      = Matrix5D();
        mat_homothetie5D         = Matrix5D();
        mat_translation5D        = Matrix5D();
        mat_inversetranslation5D = Matrix5D();

	// initialisation des matrices 6D
        mat6D                    = Matrix6D();
        mat_rotation6D           = Matrix6D();
        mat_rotation_save6D      = Matrix6D();
        mat_homothetie6D         = Matrix6D();
        mat_translation6D        = Matrix6D();
        mat_inversetranslation6D = Matrix6D();

	}

/*****************************************************************************/
/*****************************************************************************/
 void Model3D::initialiser_palette(){

 int i;

 double  coef;



 for(i=0; i<256; i++) {

 coef = (double)i/256;


 palette_front_face[i] = QBrush(QColor((int)((double)(frontsurfr)*coef), (int)((double)(frontsurfg)*coef), (int)((double)(frontsurfb)*coef)));

 palette_back_face[i] = QBrush(QColor((int)((double)(backsurfr)*coef), (int)((double)(backsurfg)*coef),(int)((double)(backsurfb)*coef)));

 palette_cond_face[i] = QBrush(QColor((int)((double)(250)*coef),0,0));

 if(fronttrans == 1)  palette_front_face[i].setStyle(Qt::HorPattern);

 if(backtrans  == 1)  palette_back_face[i].setStyle(Qt::HorPattern);

 }


 }

/*****************************************************************************/
/*****************************************************************************/


void Model3D::tracer3(QPainter & g) {
	int i, j, poly_courant, tmp, nb_poly, nb_valid_pts;
	double a4, cosinus, c4, z_tmp;
//list<Prop_poly *>::iterator itVectorData;  // List slower thant Vector !!!!!!
vector<Prop_poly *>::iterator itVectorData;

// memory reservation
vecteur_poly.reserve(nb_licol*nb_licol +1 +300);
moitie_colone = (int)(nb_colone/2);







///+++++++++++++++++++++++++++++++++++++++++++++++++++////



    for (j=0; j < nb_colone -1   ; j++)
     for (i=0; i < nb_ligne -1  ; i++) {

caa  = Tre[(i+1)*3+1][j  ] - Tre[i*3+1][j];
bab  = Tre[i*3    +2][j+1] - Tre[i*3+2][j];
cab  = Tre[(i+1)*3+2][j  ] - Tre[i*3+2][j];
baa  = Tre[i*3    +1][j+1] - Tre[i*3+1][j];
ba   = Tre[i*3      ][j+1] - Tre[i*3  ][j];
ca   = Tre[(i+1)*3  ][j  ] - Tre[i*3  ][j];

Nor[i*3  ][j] = caa*bab - cab*baa;
Nor[i*3+1][j] = cab*ba  - ca*bab;
Nor[i*3+2][j] = ca*baa  - caa*ba;


double b4 = (double)sqrt((Nor[i*3  ][j]*Nor[i*3  ][j]) +
                         (Nor[i*3+1][j]*Nor[i*3+1][j]) +
                         (Nor[i*3+2][j]*Nor[i*3+2][j])  );


// This must be changed...
if(b4 > 0.00000001) {
Nor[i*3  ][j] /=b4;
Nor[i*3+1][j] /=b4;
Nor[i*3+2][j] /=b4;
}

}


i = nb_ligne -1;
 for (j=0; j < nb_colone -1   ; j++) {
Nor[i*3  ][j] = Nor[(i-1)*3  ][j];
Nor[i*3+1][j] = Nor[(i-1)*3+1][j];
Nor[i*3+2][j] = Nor[(i-1)*3+2][j];
 }


j =nb_colone -1;
 for (i=0; i < nb_ligne -1  ; i++) {
Nor[i*3  ][j]= Nor[i*3  ][j-1];
Nor[i*3+1][j]= Nor[i*3+1][j-1];
Nor[i*3+2][j]= Nor[i*3+2][j-1];
                                       }

i = nb_ligne -1; j =nb_colone -1;
Nor[i*3  ][j]= Nor[(i-1)*3  ][j-1];
Nor[i*3+1][j]= Nor[(i-1)*3+1][j-1];
Nor[i*3+2][j]= Nor[(i-1)*3+2][j-1];

///++++++++++++++++++++++++++++++++++++++++++++++++++++++///



















if (box ==1) {

for (i=0; i<4; i++) {

c4 = D/(boiteenglobante[i*3 +2]-Oprime[2]);

tableaureferences[0]->setPoint(i,
                              (int)(c4*boiteenglobante[i*3]  +demi_hauteur),
                              (int)(c4*boiteenglobante[i*3+1]+demi_largeur));

}

g.setPen(QColor(0, 0, 250));
g.drawPolygon(*tableaureferences[0]);

/******************************************************************/


for (i=4; i<8; i++) {

c4 = D/(boiteenglobante[i*3 +2]-Oprime[2]);

tableaureferences[0]->setPoint(i-4,
                              (int)(c4*boiteenglobante[i*3] +demi_hauteur),
                              (int)(c4*boiteenglobante[i*3 + 1]+demi_largeur));

}

g.setPen(QColor(0, 0, 250));
g.drawPolygon(*tableaureferences[0]);

/******************************************************************/

for (i=0; i<2; i++) {

c4 = D/(boiteenglobante[i*3 +2]-Oprime[2]);

tableaureferences[0]->setPoint(i,
                            (int)(c4*boiteenglobante[i*3]+demi_hauteur),
                            (int)(c4*boiteenglobante[i*3+1]+demi_largeur));
}


i = 5;
c4 = D/(boiteenglobante[i*3 +2]-Oprime[2]);

tableaureferences[0]->setPoint(2,
                            (int)(c4*boiteenglobante[i*3]+demi_hauteur),
                            (int)(c4*boiteenglobante[i*3+1]+demi_largeur));



i = 4;

c4 = D/(boiteenglobante[i*3 +2]-Oprime[2]);

tableaureferences[0]->setPoint(3,
                            (int)(c4*boiteenglobante[i*3]+demi_hauteur),
                            (int)(c4*boiteenglobante[i*3+1]+demi_largeur));

g.setPen(QColor(250,0, 0));
g.drawPolygon(*tableaureferences[0]);

//================================================

g.setPen(QColor(250,250,0));
g.drawText(tableaureferences[0]->at(2).x() ,

	   tableaureferences[0]->at(2).y()+12,
           inf_u);
g.drawText(tableaureferences[0]->at(3).x(),
           tableaureferences[0]->at(3).y()+12,
           "U="+sup_u);

g.setPen(QColor(0,250,250));

g.drawText(tableaureferences[0]->at(3).x()-12,

tableaureferences[0]->at(3).y(),
           inf_v);
g.drawText(tableaureferences[0]->at(0).x()-12,
           tableaureferences[0]->at(0).y(),
           "V="+sup_v);

//================================================

for (i=2; i<4; i++) {

c4 = D/(boiteenglobante[i*3 +2]-Oprime[2]);

tableaureferences[0]->setPoint(i-2,
(int)(c4*boiteenglobante[i*3    ]  +demi_hauteur),
(int)(c4*boiteenglobante[i*3 + 1]  +demi_largeur));

}

i = 7;

c4 = D/(boiteenglobante[i*3 +2]-Oprime[2]);

tableaureferences[0]->setPoint(2,
(int)(c4*boiteenglobante[i*3]+demi_hauteur),
(int)(c4*boiteenglobante[i*3+1]+demi_largeur));

i = 6;
c4 = D/(boiteenglobante[i*3 +2]-Oprime[2]);

tableaureferences[0]->setPoint(3,
(int)(c4*boiteenglobante[i*3]+demi_hauteur),
(int)(c4*boiteenglobante[i*3+1]+demi_largeur));

g.setPen(QColor(10,200,200));
g.drawPolygon(*tableaureferences[0]);

}
// End of if(box ==1)

//=====================================================

// Map projection...

//if(mesh ==1) {


for ( i=0; i < nb_ligne - coupure_ligne; ++i)
	for ( j=0; j < nb_colone - coupure_col  ; ++j) {
c4 = D/(Tre[i*3+2][j]-Oprime[2]);
Tre3[i*3  ][j] = c4*Tre[i*3    ][j]  +demi_hauteur;
Tre3[i*3+1][j] = c4*Tre[i*3 + 1][j]  +demi_largeur;
Tre3[i*3+2][j] = Tre[i*3 + 2][j];
}
//=======================================================

if(draw_poly_normals == 1) {
for ( i=0; i < nb_ligne - coupure_ligne; ++i)
	for ( j=0; j < nb_colone - coupure_col  ; ++j) {
Nor3[i*3  ][j] = 20*Nor[i*3    ][j] + Tre[i*3    ][j];
Nor3[i*3+1][j] = 20*Nor[i*3 + 1][j] + Tre[i*3 + 1][j];
Nor3[i*3+2][j] = 20*Nor[i*3 + 2][j] + Tre[i*3 + 2][j];
}

for ( i=0; i < nb_ligne - coupure_ligne; ++i)
	for ( j=0; j < nb_colone - coupure_col  ; ++j) {
c4 = D/(Nor3[i*3+2][j]-Oprime[2]);
Nor3[i*3  ][j] = c4*Nor3[i*3    ][j]  ;
Nor3[i*3+1][j] = c4*Nor3[i*3 + 1][j]  ;
//Nor3[i*3+2][j] = Nor3[i*3 + 2][j];
}
}
//=======================================================

// We verify if there is a condition...if yes, we compute
// projections of arrays DR, DL, HR, HL
if(there_is_condition == 1) {

  for ( i=0; i < nb_ligne - coupure_ligne; ++i)
   for ( j=0; j < nb_colone - coupure_col  ; ++j)
    if(hidden_points[i][j] == 0){

//DR
c4 = D/(DR[i*3+2][j]-Oprime[2]);
DR3[i*3  ][j] = c4*DR[i*3    ][j]  +demi_hauteur;
DR3[i*3+1][j] = c4*DR[i*3 + 1][j]  +demi_largeur;
DR3[i*3+2][j] =    DR[i*3 + 2][j];

//DL
c4 = D/(DL[i*3+2][j]-Oprime[2]);
DL3[i*3  ][j] = c4*DL[i*3    ][j]  +demi_hauteur;
DL3[i*3+1][j] = c4*DL[i*3 + 1][j]  +demi_largeur;
DL3[i*3+2][j] =    DL[i*3 + 2][j];

//HR
c4 = D/(HR[i*3+2][j]-Oprime[2]);
HR3[i*3  ][j] = c4*HR[i*3    ][j]  +demi_hauteur;
HR3[i*3+1][j] = c4*HR[i*3 + 1][j]  +demi_largeur;
HR3[i*3+2][j] =    HR[i*3 + 2][j];

//HL
c4 = D/(HL[i*3+2][j]-Oprime[2]);
HL3[i*3  ][j] = c4*HL[i*3    ][j]  +demi_hauteur;
HL3[i*3+1][j] = c4*HL[i*3 + 1][j]  +demi_largeur;
HL3[i*3+2][j] =    HL[i*3 + 2][j];

}
                      } // End of if(there_is_condition == 1)...
//=================================================================

if(draw_poly_normals == 1)
for ( i=0; i < nb_ligne - 1 - coupure_ligne; ++i)
for ( j=0; j < nb_colone - 1 - coupure_col  ; ++j)
{
poly_courant = j*(nb_ligne-1 ) + i;
Nor3[i*3  ][j] = -30 * Nor[i*3    ][j]  + Tre[i*3    ][j];
Nor3[i*3+1][j] = -30 * Nor[i*3 + 1][j]  + Tre[i*3 + 1][j];
Nor3[i*3+2][j] = -30 * Nor[i*3 + 2][j]  + Tre[i*3 + 2][j];

c4 = D/(Nor3[i*3+2][j]-Oprime[2]);
Nor3[i*3  ][j] = c4*Nor3[i*3    ][j] +demi_hauteur;
Nor3[i*3+1][j] = c4*Nor3[i*3 + 1][j] +demi_largeur;

tableau[poly_courant].Norx = (int)Nor3[i*3   ][j];
tableau[poly_courant].Nory = (int)Nor3[i*3 +1][j];

tableau[poly_courant + 10000].Norx = (int)Nor3[i*3   ][j];
tableau[poly_courant + 10000].Nory = (int)Nor3[i*3 +1][j];
}

//================================================

 moitie_colone = (int)(nb_colone/2);


if(there_is_condition != 1 || implicitdef == 1) {

/// construction of polygones : first case --> No hidden points
if(there_is_hidden_points == -1) {

for ( i=0; i < nb_ligne - 1 - coupure_ligne; ++i)
for ( j=0; j < nb_colone - 1 - coupure_col  ; ++j)
 if(two_separate_objects == -1 || j != (moitie_colone -2))	///two separate shapes
if((z_tmp=Tre[i*3+2][j]+Tre[(i+1)*3+2][j]+Tre[i*3+2][j+1]+Tre[(i+1)*3+2][j+1])/4 < 460 ||
 clipping == -1 )
 {

/// Cette partie calcule le vecteur normalise qui vient de l'observateur

a4= (double)sqrt(
     (Oprime[0]-Tre[i*3  ][j] )*(Oprime[0]-Tre[i*3  ][j] )
    +(Oprime[1]-Tre[i*3+1][j] )*(Oprime[1]-Tre[i*3+1][j] )
    +(Oprime[2]-Tre[i*3+2][j] )*(Oprime[2]-Tre[i*3+2][j] ));

/// Just in case...must be changed
if( a4 > 0.00000001) {
Obser[0]=(Oprime[0]-Tre[i*3  ][j] )/a4;
Obser[1]=(Oprime[1]-Tre[i*3+1][j] )/a4;
Obser[2]=(Oprime[2]-Tre[i*3+2][j] )/a4;
}







/*

///+++++++++++++ This part must be eliminated +++++++++++++++++++///
/// to eliminate some gliches in the drawing area...
a5= (double)sqrt(
     (Nor[i*3  ][j])*(Nor[i*3  ][j])
    +(Nor[i*3+1][j])*(Nor[i*3+1][j])
    +(Nor[i*3+2][j])*(Nor[i*3+2][j]));


if( a5 > 0.00000001) {
Nor[i*3  ][j]/=a5;
Nor[i*3+1][j]/=a5;
Nor[i*3+2][j]/=a5;
}
///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++///

*/




cosinus=(((Obser[0]*Nor[i*3  ][j])+(Obser[1]*Nor[i*3+1][j])+(Obser[2]*Nor[i*3+2][j])));
/// Just in case...must be changed
if(cosinus >1 ) cosinus = 1;
if(cosinus < -1) cosinus = -1;

/*
tableau[poly_courant].Norx = (int)Nor3[i*3  ][j];
tableau[poly_courant].Nory = (int)Nor3[i*3+1][j];
*/
///                      TRIAGE des POLYGONES
///========== triage des polygone selon leurs veleurs Z et creation d'une liste
///========== de polygones TRIES qu'on utilisera apres pour l'affichage final.


poly_courant = j*(nb_ligne-1 ) + i;

tableaureferences[poly_courant]->setPoint(0,
                                         (int)(Tre3[i*3   ][j]),
                                         (int)(Tre3[i*3 +1][j]));

tableaureferences[poly_courant]->setPoint(1,
                                         (int)(Tre3[(i+1)*3][j]),
                                         (int)(Tre3[(i+1)*3 +1][j]));

tableaureferences[poly_courant]->setPoint(2,
                                         (int)(Tre3[(i+1)*3][j+1]),
                                         (int)(Tre3[(i+1)*3 +1][j+1]));

tableaureferences[poly_courant]->setPoint(3,
                                         (int)(Tre3[i*3][j+1]),
                                         (int)(Tre3[i*3 +1][j+1]));

///=============  Triage des polygones selon la valeurs de leurs profondeurs Z====

 itVectorData = vecteur_poly.begin();
 tmp=0;

 nb_poly = vecteur_poly.size();
if( nb_poly > 0)
{
           while( tmp < nb_poly) {

               if( z_tmp < vecteur_poly[tmp]->valeur_z )
  {

  tableau[poly_courant].pl = tableaureferences[poly_courant];
  tableau[poly_courant].valeur_z = z_tmp;
  tableau[poly_courant].valeur_cos = cosinus;

  vecteur_poly.insert(itVectorData, &tableau[poly_courant]);
  tmp = nb_poly ;

  }

  else   {
      if( tmp==(nb_poly -1)) {

  tableau[poly_courant].pl = tableaureferences[poly_courant];
  tableau[poly_courant].valeur_z = z_tmp;
  tableau[poly_courant].valeur_cos = cosinus;


  vecteur_poly.push_back(&tableau[poly_courant]);
  tmp = nb_poly ;
                             }
      else    {
      tmp++ ;
      itVectorData++;
      }

                      }
                      }

}
else {
  tableau[poly_courant].pl = tableaureferences[poly_courant];
  tableau[poly_courant].valeur_z = z_tmp;
  tableau[poly_courant].valeur_cos = cosinus;
  vecteur_poly.push_back(&tableau[poly_courant]);
}
                }
} /// End of if(there_is_hidden_points == -1)


/// here we have some hidden points to deal with...
else {

for ( i=0; i < nb_ligne - 1 - coupure_ligne; ++i)
for ( j=0; j < nb_colone - 1 - coupure_col  ; ++j)
      if( (nb_valid_pts =
         (hidden_points[i][j]     +
          hidden_points[i+1][j]   +
	  hidden_points[i+1][j+1] +
	  hidden_points[i][j+1])  )  >=3)

    if(two_separate_objects == -1 || j != (moitie_colone -2))	///two separate shapes

if((z_tmp=Tre[i*3+2][j]+Tre[(i+1)*3+2][j]+Tre[i*3+2][j+1]+Tre[(i+1)*3+2][j+1])/4 < 460 ||
 clipping == -1 )
 {

/// Cette partie calcule le vecteur normalise qui vient de l'observateur

a4= (double)sqrt(
     (Oprime[0]-Tre[i*3  ][j] )*(Oprime[0]-Tre[i*3  ][j] )
    +(Oprime[1]-Tre[i*3+1][j] )*(Oprime[1]-Tre[i*3+1][j] )
    +(Oprime[2]-Tre[i*3+2][j] )*(Oprime[2]-Tre[i*3+2][j] ));

/// Just in case...must be changed
if( a4 > 0.00000001) {
Obser[0]=(Oprime[0]-Tre[i*3  ][j] )/a4;
Obser[1]=(Oprime[1]-Tre[i*3+1][j] )/a4;
Obser[2]=(Oprime[2]-Tre[i*3+2][j] )/a4;
}











/*
///+++++++++++++ This part must be eliminated +++++++++++++++++++///
/// to eliminate some gliches in the drawing area...
a4= (double)sqrt(
     (Nor[i*3  ][j])*(Nor[i*3  ][j])
    +(Nor[i*3+1][j])*(Nor[i*3+1][j])
    +(Nor[i*3+2][j])*(Nor[i*3+2][j]));


if( a4 > 0.00000001) {
Nor[i*3  ][j]/=a4;
Nor[i*3+1][j]/=a4;
Nor[i*3+2][j]/=a4;
}
///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++///
*/





















cosinus=(((Obser[0]*Nor[i*3  ][j])+(Obser[1]*Nor[i*3+1][j])+(Obser[2]*Nor[i*3+2][j]))/(1));
/// Just in case...must be changed
if(cosinus >1 ) cosinus = 1;
if(cosinus < -1) cosinus = -1;
/*
tableau[poly_courant].Norx = (int)Nor3[i*3  ][j];
tableau[poly_courant].Nory = (int)Nor3[i*3+1][j];
*/
///                      TRIAGE des POLYGONES
///========== triage des polygone selon leurs veleurs Z et creation d'une liste
///========== de polygones TRIES qu'on utilisera apres pour l'affichage final.


poly_courant = j*(nb_ligne-1 ) + i;

if(nb_valid_pts == 4){
tableaureferences[poly_courant]->setPoint(0,
                                         (int)(Tre3[i*3   ][j]),
                                         (int)(Tre3[i*3 +1][j]));

tableaureferences[poly_courant]->setPoint(1,
                                         (int)(Tre3[(i+1)*3][j]),
                                         (int)(Tre3[(i+1)*3 +1][j]));

tableaureferences[poly_courant]->setPoint(2,
                                         (int)(Tre3[(i+1)*3][j+1]),
                                         (int)(Tre3[(i+1)*3 +1][j+1]));

tableaureferences[poly_courant]->setPoint(3,
                                         (int)(Tre3[i*3][j+1]),
                                         (int)(Tre3[i*3 +1][j+1]));

} else {

if(hidden_points[i][j] == 0) {

tableaureferences[poly_courant]->setPoint(0,
                                         (int)((Tre3[i*3   ][j+1]+Tre3[(i+1)*3   ][j])/2),
                                         (int)((Tre3[i*3 +1][j+1] + Tre3[(i+1)*3 +1][j])/2));

tableaureferences[poly_courant]->setPoint(1,
                                         (int)(Tre3[(i+1)*3][j]),
                                         (int)(Tre3[(i+1)*3 +1][j]));

tableaureferences[poly_courant]->setPoint(2,
                                         (int)(Tre3[(i+1)*3][j+1]),
                                         (int)(Tre3[(i+1)*3 +1][j+1]));

tableaureferences[poly_courant]->setPoint(3,
                                         (int)(Tre3[i*3][j+1]),
                                         (int)(Tre3[i*3 +1][j+1]));

}

else if(hidden_points[i+1][j] == 0) {
tableaureferences[poly_courant]->setPoint(0,
                                         (int)(Tre3[i*3   ][j]),
                                         (int)(Tre3[i*3 +1][j]));
tableaureferences[poly_courant]->setPoint(1,
                                         (int)(  (Tre3[i*3][j] + Tre3[(i+1)*3][j+1] )/2),
                                         (int)(  (Tre3[i*3 +1][j] + Tre3[(i+1)*3 +1][j+1])/2));
tableaureferences[poly_courant]->setPoint(2,
                                         (int)(Tre3[(i+1)*3][j+1]),
                                         (int)(Tre3[(i+1)*3 +1][j+1]));
tableaureferences[poly_courant]->setPoint(3,
                                         (int)(Tre3[i*3][j+1]),
                                         (int)(Tre3[i*3 +1][j+1]));
     }

else if(hidden_points[i+1][j+1] == 0) {

tableaureferences[poly_courant]->setPoint(0,
                                         (int)(Tre3[i*3   ][j]),
                                         (int)(Tre3[i*3 +1][j]));
tableaureferences[poly_courant]->setPoint(1,
                                         (int)(Tre3[(i+1)*3][j]),
                                         (int)(Tre3[(i+1)*3 +1][j]));
tableaureferences[poly_courant]->setPoint(2,
                                         (int)((Tre3[(i+1)*3][j] +Tre3[i*3][j+1] )/2),
                                         (int)((Tre3[(i+1)*3 +1][j] + Tre3[i*3 +1][j+1])/2));
tableaureferences[poly_courant]->setPoint(3,
                                         (int)(Tre3[i*3][j+1]),
                                         (int)(Tre3[i*3 +1][j+1]));

}

else {

tableaureferences[poly_courant]->setPoint(0,
                                         (int)(Tre3[i*3   ][j]),
                                         (int)(Tre3[i*3 +1][j]));
tableaureferences[poly_courant]->setPoint(1,
                                         (int)(Tre3[(i+1)*3][j]),
                                         (int)(Tre3[(i+1)*3 +1][j]));
tableaureferences[poly_courant]->setPoint(2,
                                         (int)(Tre3[(i+1)*3][j+1]),
                                         (int)(Tre3[(i+1)*3 +1][j+1]));
tableaureferences[poly_courant]->setPoint(3,
                                         (int)((Tre3[(i+1)*3][j+1] + Tre3[i*3][j])/2),
                                         (int)((Tre3[(i+1)*3 +1][j+1] +Tre3[i*3 +1][j] )/2));
}

}


//=============  Triage des polygones selon la valeurs de leurs profondeurs Z====

 tmp=0;
 itVectorData = vecteur_poly.begin();

 nb_poly = vecteur_poly.size();
if( nb_poly > 0)
{  /// z_tmp= Tre[i*3+2][j]+ Tre[(i+1)*3+2][j]+ Tre[i*3+2][j+1]+ Tre[(i+1)*3+2][j+1];
           while( tmp < nb_poly) {

               if( z_tmp < vecteur_poly[tmp]->valeur_z )
               //if( z_tmp < (*itVectorData)->valeur_z )
  {
  tableau[poly_courant].pl = tableaureferences[poly_courant];
  tableau[poly_courant].valeur_z = z_tmp;
  tableau[poly_courant].valeur_cos = cosinus;

  vecteur_poly.insert(itVectorData, &tableau[poly_courant]);
  tmp = nb_poly ;
  }
  else   {
      if( tmp==(nb_poly -1)) {

  tableau[poly_courant].pl = tableaureferences[poly_courant];
  tableau[poly_courant].valeur_z = z_tmp;
  tableau[poly_courant].valeur_cos = cosinus;

  vecteur_poly.push_back(&tableau[poly_courant]);
  tmp = nb_poly ;
                             }
      else    {
      tmp++ ;
      itVectorData++;
      }
                      }
                      }
}
else {
//
  tableau[poly_courant].pl = tableaureferences[poly_courant];
  tableau[poly_courant].valeur_z = z_tmp;
  tableau[poly_courant].valeur_cos = cosinus;

  vecteur_poly.push_back(&tableau[poly_courant]);
}
}
}

} // End of if(there_is_condition != 1)....
/// Fin de la construction du vecteur de polygones tri�.



/// cette partie doit etre changee pour fusionner avec ce qui vient en bas (
/// quant ca va etre test�et optimiser.

else {

/*
//=================================================================

if(draw_poly_normals == 1)
for ( i=0; i < nb_ligne - 1 - coupure_ligne; ++i)
for ( j=0; j < nb_colone - 1 - coupure_col  ; ++j)
{
poly_courant = j*(nb_ligne-1 ) + i;
Nor3[i*3  ][j] = -30 * Nor[i*3    ][j]  + Tre[i*3    ][j];
Nor3[i*3+1][j] = -30 * Nor[i*3 + 1][j]  + Tre[i*3 + 1][j];
Nor3[i*3+2][j] = -30 * Nor[i*3 + 2][j]  + Tre[i*3 + 2][j];

c4 = D/(Nor3[i*3+2][j]-Oprime[2]);
Nor3[i*3  ][j] = c4*Nor3[i*3    ][j] +demi_hauteur;
Nor3[i*3+1][j] = c4*Nor3[i*3 + 1][j] +demi_largeur;

tableau[poly_courant].Norx = (int)Nor3[i*3   ][j];
tableau[poly_courant].Nory = (int)Nor3[i*3 +1][j];

tableau[poly_courant + 10000].Norx = (int)Nor3[i*3   ][j];
tableau[poly_courant + 10000].Nory = (int)Nor3[i*3 +1][j];
}

//=================================================================
*/

for ( i=0; i < nb_ligne - 1 - coupure_ligne; ++i)
for ( j=0; j < nb_colone - 1 - coupure_col  ; ++j)
      if( (nb_valid_pts =
         (hidden_points[i  ][j  ] +
          hidden_points[i+1][j  ] +
          hidden_points[i+1][j+1] +
          hidden_points[i  ][j+1]  )) >=2)
       {
    if(two_separate_objects == -1 || j != (moitie_colone -2))	///two separate shapes

if((z_tmp=Tre[i*3+2][j]+Tre[(i+1)*3+2][j]+Tre[i*3+2][j+1]+Tre[(i+1)*3+2][j+1])/4 < 460 ||
 clipping == -1 )
 {

/// Cette partie calcule le vecteur normalise qui vient de l'observateur

a4= (double)sqrt(
     (Oprime[0]-Tre[i*3  ][j] )*(Oprime[0]-Tre[i*3  ][j] )
    +(Oprime[1]-Tre[i*3+1][j] )*(Oprime[1]-Tre[i*3+1][j] )
    +(Oprime[2]-Tre[i*3+2][j] )*(Oprime[2]-Tre[i*3+2][j] ));

/// Just in case...must be changed
if( a4 > 0.00000001) {
Obser[0]=(Oprime[0]-Tre[i*3  ][j] )/a4;
Obser[1]=(Oprime[1]-Tre[i*3+1][j] )/a4;
Obser[2]=(Oprime[2]-Tre[i*3+2][j] )/a4;
}











/*
///+++++++++++++ This part must be eliminated +++++++++++++++++++///
/// to eliminate some gliches in the drawing area...
a4= (double)sqrt(
     (Nor[i*3  ][j])*(Nor[i*3  ][j])
    +(Nor[i*3+1][j])*(Nor[i*3+1][j])
    +(Nor[i*3+2][j])*(Nor[i*3+2][j]));


if( a4 > 0.00000001) {
Nor[i*3  ][j]/=a4;
Nor[i*3+1][j]/=a4;
Nor[i*3+2][j]/=a4;
}
///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++///
*/


























cosinus=(((Obser[0]*Nor[i*3  ][j])+(Obser[1]*Nor[i*3+1][j])+(Obser[2]*Nor[i*3+2][j]))/(1));
/// Just in case...must be changed
if(cosinus >1 ) cosinus = 1;
if(cosinus < -1) cosinus = -1;

/*
//=================================================================

if(draw_poly_normals == 1){
poly_courant = j*(nb_ligne-1 ) + i;
Nor3[i*3  ][j] = -30 * Nor[i*3    ][j]  + Tre[i*3    ][j];
Nor3[i*3+1][j] = -30 * Nor[i*3 + 1][j]  + Tre[i*3 + 1][j];
Nor3[i*3+2][j] = -30 * Nor[i*3 + 2][j]  + Tre[i*3 + 2][j];

c4 = D/(Nor3[i*3+2][j]-Oprime[2]);
Nor3[i*3  ][j] = c4*Nor3[i*3    ][j] +demi_hauteur;
Nor3[i*3+1][j] = c4*Nor3[i*3 + 1][j] +demi_largeur;

tableau[poly_courant].Norx = (int)Nor3[i*3   ][j];
tableau[poly_courant].Nory = (int)Nor3[i*3 +1][j];

tableau[poly_courant + 10000].Norx = (int)Nor3[i*3   ][j];
tableau[poly_courant + 10000].Nory = (int)Nor3[i*3 +1][j];
}

//=================================================================
*/

///                      TRIAGE des POLYGONES
///========== triage des polygone selon leurs veleurs Z et creation d'une liste
///========== de polygones TRIES qu'on utilisera apres pour l'affichage final.

poly_courant = j*(nb_ligne-1 ) + i;
if(nb_valid_pts == 4){
tableaureferences[poly_courant]->setPoint(0,
                                         (int)(Tre3[i*3   ][j]),
                                         (int)(Tre3[i*3 +1][j]));

tableaureferences[poly_courant]->setPoint(1,
                                         (int)(Tre3[(i+1)*3   ][j]),
                                         (int)(Tre3[(i+1)*3 +1][j]));

tableaureferences[poly_courant]->setPoint(2,
                                         (int)(Tre3[(i+1)*3   ][j+1]),
                                         (int)(Tre3[(i+1)*3 +1][j+1]));

tableaureferences[poly_courant]->setPoint(3,
                                         (int)(Tre3[i*3   ][j+1]),
                                         (int)(Tre3[i*3 +1][j+1]));
} // End if(nb_valid_pts == 4)

else if(nb_valid_pts == 3 ){

  if(  draw_hidden_poly_and_nonhidden == 1 ) {
poly_courant = j*(nb_ligne-1 ) + i ;

tableaureferences[poly_courant + 10000]->setPoint(0,
                                         (int)(Tre3[i*3   ][j]),
                                         (int)(Tre3[i*3 +1][j]));

tableaureferences[poly_courant + 10000]->setPoint(1,
                                         (int)(Tre3[(i+1)*3][j]),
                                         (int)(Tre3[(i+1)*3 +1][j]));

tableaureferences[poly_courant + 10000]->setPoint(2,
                                         (int)(Tre3[(i+1)*3][j+1]),
                                         (int)(Tre3[(i+1)*3 +1][j+1]));

tableaureferences[poly_courant + 10000]->setPoint(3,
                                         (int)(Tre3[i*3][j+1]),
                                         (int)(Tre3[i*3 +1][j+1]));

      }

if(hidden_points[i][j] == 0) {

tableaureferences[poly_courant]->setPoint(0,
                                         (int)(DL3[(i)*3   ][j]  ),
                                         (int)(DL3[(i)*3 +1][j]  ));

tableaureferences[poly_courant]->setPoint(1,
                                         (int)(Tre3[(i+1)*3][j]),
                                         (int)(Tre3[(i+1)*3 +1][j]));

tableaureferences[poly_courant]->setPoint(2,
                                         (int)(Tre3[(i+1)*3][j+1]),
                                         (int)(Tre3[(i+1)*3 +1][j+1]));

tableaureferences[poly_courant]->setPoint(3,
                                         (int)(Tre3[i*3][j+1]),
                                         (int)(Tre3[i*3 +1][j+1]));
}

else if(hidden_points[i+1][j] == 0) {
tableaureferences[poly_courant]->setPoint(0,
                                         (int)(Tre3[i*3   ][j]),
                                         (int)(Tre3[i*3 +1][j]));
tableaureferences[poly_courant]->setPoint(1,
                                         (int)(HL3[(i+1)*3   ][j]),
                                         (int)(HL3[(i+1)*3 +1][j]));

tableaureferences[poly_courant]->setPoint(2,
                                         (int)(Tre3[(i+1)*3][j+1]),
                                         (int)(Tre3[(i+1)*3 +1][j+1]));

tableaureferences[poly_courant]->setPoint(3,
                                         (int)(Tre3[i*3][j+1]),
                                         (int)(Tre3[i*3 +1][j+1]));
     }

else if(hidden_points[i+1][j+1] == 0) {

tableaureferences[poly_courant]->setPoint(0,
                                         (int)(Tre3[i*3   ][j]),
                                         (int)(Tre3[i*3 +1][j]));

tableaureferences[poly_courant]->setPoint(1,
                                         (int)(Tre3[(i+1)*3   ][j]),
                                         (int)(Tre3[(i+1)*3 +1][j]));

tableaureferences[poly_courant]->setPoint(2,
                                         (int)(HR3[(i+1)*3   ][j+1]),
                                         (int)(HR3[(i+1)*3 +1][j+1]));

tableaureferences[poly_courant]->setPoint(3,
                                         (int)(Tre3[i*3   ][j+1]),
                                         (int)(Tre3[i*3 +1][j+1]));
}

else {

tableaureferences[poly_courant]->setPoint(0,
                                         (int)(Tre3[i*3   ][j]),
                                         (int)(Tre3[i*3 +1][j]));

tableaureferences[poly_courant]->setPoint(1,
                                         (int)(Tre3[(i+1)*3][j]),
                                         (int)(Tre3[(i+1)*3 +1][j]));

tableaureferences[poly_courant]->setPoint(2,
                                         (int)(Tre3[(i+1)*3][j+1]),
                                         (int)(Tre3[(i+1)*3 +1][j+1]));

tableaureferences[poly_courant]->setPoint(3,
                                         (int)(DR3[i*3   ][j+1]),
                                         (int)(DR3[i*3 +1][j+1]));
}

} // End if(nb_valid_pts == 3 )


else if(nb_valid_pts == 2 ){
poly_courant = j*(nb_ligne-1 ) + i;

  if(  draw_hidden_poly_and_nonhidden == 1 ) {


tableaureferences[poly_courant + 10000]->setPoint(0,
                                         (int)(Tre3[i*3   ][j]),
                                         (int)(Tre3[i*3 +1][j]));

tableaureferences[poly_courant + 10000]->setPoint(1,
                                         (int)(Tre3[(i+1)*3][j]),
                                         (int)(Tre3[(i+1)*3 +1][j]));

tableaureferences[poly_courant + 10000]->setPoint(2,
                                         (int)(Tre3[(i+1)*3][j+1]),
                                         (int)(Tre3[(i+1)*3 +1][j+1]));

tableaureferences[poly_courant + 10000]->setPoint(3,
                                         (int)(Tre3[i*3][j+1]),
                                         (int)(Tre3[i*3 +1][j+1]));
      }

     if(hidden_points[i][j+1] == 0 && hidden_points[i][j] == 0) {
tableaureferences[poly_courant]->setPoint(0,
                                         (int)(DL3[i*3   ][j]),
                                         (int)(DL3[i*3 +1][j]));
tableaureferences[poly_courant]->setPoint(1,
                                         (int)(Tre3[(i+1)*3][j]),
                                         (int)(Tre3[(i+1)*3 +1][j]));
tableaureferences[poly_courant]->setPoint(2,
                                         (int)(Tre3[(i+1)*3][j+1]),
                                         (int)(Tre3[(i+1)*3 +1][j+1]));
tableaureferences[poly_courant]->setPoint(3,
                                         (int)(DR3[i*3   ][j+1]),
                                         (int)(DR3[i*3 +1][j+1]));
                              }
     else if (hidden_points[i][j] == 0 && hidden_points[i+1][j] == 0){
tableaureferences[poly_courant]->setPoint(0,
                                         (int)(DL3[i*3   ][j]),
                                         (int)(DL3[i*3 +1][j]));
tableaureferences[poly_courant]->setPoint(1,
                                         (int)(HL3[(i+1)*3][j]),
                                         (int)(HL3[(i+1)*3 +1][j]));
tableaureferences[poly_courant]->setPoint(2,
                                         (int)(Tre3[(i+1)*3][j+1]),
                                         (int)(Tre3[(i+1)*3 +1][j+1]));
tableaureferences[poly_courant]->setPoint(3,
                                         (int)(Tre3[i*3   ][j+1]),
                                         (int)(Tre3[i*3 +1][j+1]));
          }
     else if(hidden_points[i+1][j] == 0 && hidden_points[i+1][j+1] == 0){
tableaureferences[poly_courant]->setPoint(0,
                                         (int)(Tre3[i*3   ][j]),
                                         (int)(Tre3[i*3 +1][j]));
tableaureferences[poly_courant]->setPoint(1,
                                         (int)(HL3[(i+1)*3][j]),
                                         (int)(HL3[(i+1)*3 +1][j]));
tableaureferences[poly_courant]->setPoint(2,
                                         (int)(HR3[(i+1)*3][j+1]),
                                         (int)(HR3[(i+1)*3 +1][j+1]));
tableaureferences[poly_courant]->setPoint(3,
                                         (int)(Tre3[i*3   ][j+1]),
                                         (int)(Tre3[i*3 +1][j+1]));
          }
     else if(hidden_points[i+1][j+1] == 0 && hidden_points[i][j+1] == 0){
tableaureferences[poly_courant]->setPoint(0,
                                         (int)(Tre3[i*3   ][j]),
                                         (int)(Tre3[i*3 +1][j]));
tableaureferences[poly_courant]->setPoint(1,
                                         (int)(Tre3[(i+1)*3][j]),
                                         (int)(Tre3[(i+1)*3 +1][j]));
tableaureferences[poly_courant]->setPoint(2,
                                         (int)(HR3[(i+1)*3][j+1]),
                                         (int)(HR3[(i+1)*3 +1][j+1]));
tableaureferences[poly_courant]->setPoint(3,
                                         (int)(DR3[i*3   ][j+1]),
                                         (int)(DR3[i*3 +1][j+1]));
          }
// if we have to draw the shape along with the Hidden polygon

else {
/*  if(  draw_hidden_poly_and_nonhidden == 1 ) */ {
poly_courant = j*(nb_ligne-1 ) + i;

tableaureferences[poly_courant  ]->setPoint(0,
                                         (int)(Tre3[i*3   ][j]),
                                         (int)(Tre3[i*3 +1][j]));
tableaureferences[poly_courant ]->setPoint(1,
                                         (int)(Tre3[i*3   ][j]),
                                         (int)(Tre3[i*3 +1][j]));
tableaureferences[poly_courant ]->setPoint(2,
                                         (int)(Tre3[i*3   ][j]),
                                         (int)(Tre3[i*3 +1][j]));
tableaureferences[poly_courant ]->setPoint(3,
                                         (int)(Tre3[i*3   ][j]),
                                         (int)(Tre3[i*3 +1][j]));
      }
     }

// END of : if we have to draw the shape along with the Hidden polygon

     } // End if(nb_valid_pts == 2 )

//=============  Triage des polygones selon la valeurs de leurs profondeurs Z====

 tmp=0;
 itVectorData = vecteur_poly.begin();

 nb_poly = vecteur_poly.size();
if( nb_poly > 0)
{  /// z_tmp= Tre[i*3+2][j]+ Tre[(i+1)*3+2][j]+ Tre[i*3+2][j+1]+ Tre[(i+1)*3+2][j+1];
           while( tmp < nb_poly) {
               if( z_tmp < vecteur_poly[tmp]->valeur_z )
               //if( z_tmp < (*itVectorData)->valeur_z )
  {
  tableau[poly_courant].pl = tableaureferences[poly_courant];
  tableau[poly_courant].valeur_z = z_tmp;
  tableau[poly_courant].valeur_cos = cosinus;

  vecteur_poly.insert(itVectorData, &tableau[poly_courant]);

if(  draw_hidden_poly_and_nonhidden == 1 && (nb_valid_pts == 3 || nb_valid_pts == 2) )  {

  tableau[poly_courant + 10000].pl = tableaureferences[poly_courant + 10000];
  tableau[poly_courant + 10000].valeur_z = z_tmp;
  tableau[poly_courant + 10000].valeur_cos = cosinus;
  tableau[poly_courant + 10000].condition_validity = -1;

vecteur_poly.insert(itVectorData, &tableau[poly_courant + 10000]);
}
  tmp = nb_poly ;
  }

  else   {
      if( tmp==(nb_poly -1)) {

if(  draw_hidden_poly_and_nonhidden == 1 && (nb_valid_pts == 3 || nb_valid_pts == 2) ) {

  tableau[poly_courant + 10000].pl = tableaureferences[poly_courant + 10000];
  tableau[poly_courant + 10000].valeur_z = z_tmp;
  tableau[poly_courant + 10000].valeur_cos = cosinus;
  tableau[poly_courant + 10000].condition_validity = -1;

  vecteur_poly.push_back(&tableau[poly_courant + 10000]);
}
  tableau[poly_courant].pl = tableaureferences[poly_courant];
  tableau[poly_courant].valeur_z = z_tmp;
  tableau[poly_courant].valeur_cos = cosinus;
  vecteur_poly.push_back(&tableau[poly_courant]);

  tmp = nb_poly ;
                             }
      else    {
      tmp++ ;
      itVectorData++;
      }
                      }

                      }

}
else {

if(  draw_hidden_poly_and_nonhidden == 1 && (nb_valid_pts == 3 || nb_valid_pts == 2) ) {
  tableau[poly_courant + 10000].pl = tableaureferences[poly_courant + 10000];
  tableau[poly_courant + 10000].valeur_z = z_tmp;
  tableau[poly_courant + 10000].valeur_cos = cosinus;
  tableau[poly_courant + 10000].condition_validity = -1;
  vecteur_poly.push_back(&tableau[poly_courant + 10000]);
}

  tableau[poly_courant].pl = tableaureferences[poly_courant];
  tableau[poly_courant].valeur_z = z_tmp;
  tableau[poly_courant].valeur_cos = cosinus;
  vecteur_poly.push_back(&tableau[poly_courant]);

}

}
} // End if(HP[][] +... >=2 )


// Here we are going to store the hidden polygone
// only if it's needed by user : draw_hidden_poly_and_nonhidden == 1
else
{
 // ==========================================================================
  if(  draw_hidden_poly_and_nonhidden == 1 )
    if(two_separate_objects == -1 || j != (moitie_colone -2))	///two separate shapes

if((z_tmp=Tre[i*3+2][j]+Tre[(i+1)*3+2][j]+Tre[i*3+2][j+1]+Tre[(i+1)*3+2][j+1])/4 < 460 ||
 clipping == -1 )
 {
/// Cette partie calcule le vecteur normalise qui vient de l'observateur
a4= (double)sqrt(
     (Oprime[0]-Tre[i*3  ][j] )*(Oprime[0]-Tre[i*3  ][j] )
    +(Oprime[1]-Tre[i*3+1][j] )*(Oprime[1]-Tre[i*3+1][j] )
    +(Oprime[2]-Tre[i*3+2][j] )*(Oprime[2]-Tre[i*3+2][j] ));

/// Just in case...must be changed
if( a4 > 0.00000001) {
Obser[0]=(Oprime[0]-Tre[i*3  ][j] )/a4;
Obser[1]=(Oprime[1]-Tre[i*3+1][j] )/a4;
Obser[2]=(Oprime[2]-Tre[i*3+2][j] )/a4;
}



/*
///+++++++++++++ This part must be eliminated +++++++++++++++++++///
/// to eliminate some gliches in the drawing area...
a4= (double)sqrt(
     (Nor[i*3  ][j])*(Nor[i*3  ][j])
    +(Nor[i*3+1][j])*(Nor[i*3+1][j])
    +(Nor[i*3+2][j])*(Nor[i*3+2][j]));


if( a4 > 0.00000001) {
Nor[i*3  ][j]/=a4;
Nor[i*3+1][j]/=a4;
Nor[i*3+2][j]/=a4;
}
///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++///
*/



















cosinus=(((Obser[0]*Nor[i*3  ][j])+(Obser[1]*Nor[i*3+1][j])+(Obser[2]*Nor[i*3+2][j]))/(1));
/// Just in case...must be changed
if(cosinus >1 ) cosinus = 1;
if(cosinus < -1) cosinus = -1;


poly_courant = j*(nb_ligne-1 ) + i + 10000;

tableaureferences[poly_courant]->setPoint(0,
                                         (int)(Tre3[i*3   ][j]),
                                         (int)(Tre3[i*3 +1][j]));

tableaureferences[poly_courant]->setPoint(1,
                                         (int)(Tre3[(i+1)*3][j]),
                                         (int)(Tre3[(i+1)*3 +1][j]));

tableaureferences[poly_courant]->setPoint(2,
                                         (int)(Tre3[(i+1)*3][j+1]),
                                         (int)(Tre3[(i+1)*3 +1][j+1]));

tableaureferences[poly_courant]->setPoint(3,
                                         (int)(Tre3[i*3][j+1]),
                                         (int)(Tre3[i*3 +1][j+1]));

///=============  Triage des polygones selon la valeurs de leurs profondeurs Z====

 itVectorData = vecteur_poly.begin();
 tmp=0;

 nb_poly = vecteur_poly.size();
if( nb_poly > 0)
{
           while( tmp < nb_poly) {

               if( z_tmp < vecteur_poly[tmp]->valeur_z )
  {

  tableau[poly_courant].pl = tableaureferences[poly_courant];
  tableau[poly_courant].valeur_z = z_tmp;
  tableau[poly_courant].valeur_cos = cosinus;
  tableau[poly_courant].condition_validity = -1;

  vecteur_poly.insert(itVectorData, &tableau[poly_courant]);
  tmp = nb_poly ;

  }

  else   {
      if( tmp==(nb_poly -1)) {

  tableau[poly_courant].pl = tableaureferences[poly_courant];
  tableau[poly_courant].valeur_z = z_tmp;
  tableau[poly_courant].valeur_cos = cosinus;
  tableau[poly_courant].condition_validity = -1;

  vecteur_poly.push_back(&tableau[poly_courant]);
  tmp = nb_poly ;
                             }
      else    {
      tmp++ ;
      itVectorData++;
      }
                      }
                      }
}
else {
  tableau[poly_courant].pl = tableaureferences[poly_courant];
  tableau[poly_courant].valeur_z = z_tmp;
  tableau[poly_courant].valeur_cos = cosinus;
  tableau[poly_courant].condition_validity = -1;
  vecteur_poly.push_back(&tableau[poly_courant]);
}
}
 // ==========================================================================

} // End else
} // End else...(there is a condition)



/// =======================================================




///                      Fin du triage des polygones
///=============================================================================


///==============================================================================

/// Optimisation: Trying to eliminate some polygons with the Zbuffer algorithm

///==============================================================================



double cs;

Prop_poly * prop_poly;

QPointArray * p;

itVectorData = vecteur_poly.begin();

nb_poly = vecteur_poly.size();



if(zbuffer_active_ok == 1)  {


for (j=0; j < nb_poly   ; j++) {

prop_poly = vecteur_poly.at(j);

p = prop_poly->pl;

prop_poly->zbuffer_validity = 1;

p->point(0, &zbuffer[0][j], &zbuffer[1][j]);
p->point(1, &zbuffer[2][j], &zbuffer[3][j]);
p->point(2, &zbuffer[4][j], &zbuffer[5][j]);
p->point(3, &zbuffer[6][j], &zbuffer[7][j]);

// Polygon center

zbuffer[8][j] = (zbuffer[0][j]+zbuffer[2][j]+zbuffer[4][j]+zbuffer[6][j])/4;

zbuffer[9][j] = (zbuffer[1][j]+zbuffer[3][j]+zbuffer[5][j]+zbuffer[7][j])/4;

// Recherche du rayon du cerle engloban le polygon

r1 = sqrt((zbuffer[8][j]-zbuffer[0][j])*(zbuffer[8][j]-zbuffer[0][j]) +

          (zbuffer[9][j]-zbuffer[1][j])*(zbuffer[9][j]-zbuffer[1][j]));



r2 = sqrt((zbuffer[8][j]-zbuffer[2][j])*(zbuffer[8][j]-zbuffer[2][j]) +

          (zbuffer[9][j]-zbuffer[3][j])*(zbuffer[9][j]-zbuffer[3][j]));



r3 = sqrt((zbuffer[8][j]-zbuffer[4][j])*(zbuffer[8][j]-zbuffer[4][j]) +

          (zbuffer[9][j]-zbuffer[5][j])*(zbuffer[9][j]-zbuffer[5][j]));



r4 = sqrt((zbuffer[8][j]-zbuffer[6][j])*(zbuffer[8][j]-zbuffer[6][j]) +

          (zbuffer[9][j]-zbuffer[7][j])*(zbuffer[9][j]-zbuffer[7][j]));

maxr = r1;

if(maxr<r2) maxr = r2;

if(maxr<r3) maxr = r3;

if(maxr<r4) maxr = r4;

rayon[j] = maxr;  // rayon du cerle engloban le polygon

if(rayon[j] < 4) zbuffer[10][j] =  1; //Polygon too small
else zbuffer[10][j] =  -1 ;

itVectorData++;

}


///==============================================================================


for (j=0; j < nb_poly   ; j++) {

X_averege1  = 6*(zbuffer[0][j]-zbuffer[4][j])/7 + zbuffer[4][j];

Y_averege1  = 6*(zbuffer[1][j]-zbuffer[5][j])/7 + zbuffer[5][j];


X_averege2 =  (zbuffer[0][j]-zbuffer[4][j])/7 + zbuffer[4][j];

Y_averege2 =  (zbuffer[1][j]-zbuffer[5][j])/7 + zbuffer[5][j];


X_averege3 =  6*(zbuffer[2][j]-zbuffer[6][j])/7 + zbuffer[6][j];

Y_averege3 =  6*(zbuffer[3][j]-zbuffer[7][j])/7 + zbuffer[7][j];


X_averege4 =  (zbuffer[2][j]-zbuffer[6][j])/7 + zbuffer[6][j];

Y_averege4 =  (zbuffer[3][j]-zbuffer[7][j])/7 + zbuffer[7][j];


X_averege = zbuffer[8][j];

Y_averege = zbuffer[9][j];


// we are going to test if one of the remaining poly has

// the point(X_averege,Y_averege) in it's interior.



point_interior  = -1;

point_interior1 = -1;

point_interior2 = -1;

point_interior3 = -1;

point_interior4 = -1;



nb_intersection  = -1;

nb_intersection1 = -1;

nb_intersection2 = -1;

nb_intersection3 = -1;

nb_intersection4 = -1;



for(i = nb_poly -1; i > j ; i--) {



// Compute distance between the two polygons centers

r1 = sqrt((zbuffer[8][i]-zbuffer[8][j])*(zbuffer[8][i]-zbuffer[8][j]) +

          (zbuffer[9][i]-zbuffer[9][j])*(zbuffer[9][i]-zbuffer[9][j]));



// Perform calculation only if two cercls intersect

//if( r1 < (zbuffer[10][i] + zbuffer[10][j]))  {

if( r1 < (rayon[i] + rayon[j]))  {

if(point_interior  == -1) nb_intersection  = -1;

if(point_interior1 == -1) nb_intersection1 = -1;

if(point_interior2 == -1) nb_intersection2 = -1;

if(point_interior3 == -1) nb_intersection3 = -1;

if(point_interior4 == -1) nb_intersection4 = -1;





//=================== We work with the first point ==========================

if( (zbuffer_quality == 1 || zbuffer_quality == 5 ) && point_interior  == -1/*nb_intersection == -1*/ ){

        if ((((zbuffer[1][i]<=Y_averege) && (Y_averege<zbuffer[7][i])) ||

             ((zbuffer[7][i]<=Y_averege) && (Y_averege<zbuffer[1][i]))) &&

            (X_averege <  (zbuffer[6][i] - zbuffer[0][i]) * (Y_averege - zbuffer[1][i])/(zbuffer[7][i] - zbuffer[1][i]) + zbuffer[0][i]))

                  nb_intersection*=-1;





        if ((((zbuffer[3][i]<=Y_averege) && (Y_averege<zbuffer[1][i])) ||

             ((zbuffer[1][i]<=Y_averege) && (Y_averege<zbuffer[3][i]))) &&

            (X_averege <  (zbuffer[0][i] - zbuffer[2][i]) * (Y_averege - zbuffer[3][i])/(zbuffer[1][i] - zbuffer[3][i]) + zbuffer[2][i]))

                  nb_intersection*=-1;



        if ((((zbuffer[5][i]<=Y_averege) && (Y_averege<zbuffer[3][i])) ||

             ((zbuffer[3][i]<=Y_averege) && (Y_averege<zbuffer[5][i]))) &&

            (X_averege <  (zbuffer[2][i] - zbuffer[4][i]) * (Y_averege - zbuffer[5][i])/(zbuffer[3][i] - zbuffer[5][i])  + zbuffer[4][i]))

                  nb_intersection*=-1;





        if ((((zbuffer[7][i]<=Y_averege) && (Y_averege<zbuffer[5][i])) ||

             ((zbuffer[5][i]<=Y_averege) && (Y_averege<zbuffer[7][i]))) &&

            (X_averege <  (zbuffer[4][i] - zbuffer[6][i]) * (Y_averege - zbuffer[7][i])/(zbuffer[5][i] - zbuffer[7][i]) + zbuffer[6][i]))

                  nb_intersection*=-1;



if(nb_intersection == 1 ) {
   point_interior = 1;
   /*
   if(zbuffer[10][i] == 1) {
     nb_intersection1 =
     nb_intersection2 =
     nb_intersection3 =
     nb_intersection4 = 1;  // if Poly too small, we stop looking for another intersections

     point_interior1 =
     point_interior2 =
     point_interior3 =
     point_interior4 = 1;
                     }
     */
                 } // end of if(nb_intersection == 1 )



}
else point_interior  = 1;


//End of  if( nb_intersection == -1 )...

//=================== We work with the second point =========================





if(zbuffer_quality > 1  && point_interior1  == -1 /*nb_intersection1 == -1*/ ){

        if ((((zbuffer[1][i]<=Y_averege1) && (Y_averege1<zbuffer[7][i])) ||

             ((zbuffer[7][i]<=Y_averege1) && (Y_averege1<zbuffer[1][i]))) &&

            (X_averege1 < (zbuffer[6][i] - zbuffer[0][i]) * (Y_averege1 - zbuffer[1][i])/(zbuffer[7][i] - zbuffer[1][i]) + zbuffer[0][i]))

                  nb_intersection1*=-1;





        if ((((zbuffer[3][i]<=Y_averege1) && (Y_averege1<zbuffer[1][i])) ||

             ((zbuffer[1][i]<=Y_averege1) && (Y_averege1<zbuffer[3][i]))) &&

            (X_averege1 < (zbuffer[0][i] - zbuffer[2][i]) * (Y_averege1 - zbuffer[3][i])/(zbuffer[1][i] - zbuffer[3][i]) + zbuffer[2][i]))

                  nb_intersection1*=-1;



        if ((((zbuffer[5][i]<=Y_averege1) && (Y_averege1<zbuffer[3][i])) ||

             ((zbuffer[3][i]<=Y_averege1) && (Y_averege1<zbuffer[5][i]))) &&

            (X_averege1 < (zbuffer[2][i] - zbuffer[4][i]) * (Y_averege1 - zbuffer[5][i])/(zbuffer[3][i] - zbuffer[5][i])  + zbuffer[4][i]))

                  nb_intersection1*=-1;





        if ((((zbuffer[7][i]<=Y_averege1) && (Y_averege1<zbuffer[5][i])) ||

             ((zbuffer[5][i]<=Y_averege1) && (Y_averege1<zbuffer[7][i]))) &&

            (X_averege1 < (zbuffer[4][i] - zbuffer[6][i]) * (Y_averege1 - zbuffer[7][i])/(zbuffer[5][i] - zbuffer[7][i]) + zbuffer[6][i]))

                  nb_intersection1*=-1;



if(nb_intersection1 == 1 ) {

point_interior1 = 1;
/*
   if(zbuffer[10][i] == 1) {
     nb_intersection  =
     nb_intersection2 =
     nb_intersection3 =
     nb_intersection4 = 1;  // if Poly too small, we stop looking for another intersections

     point_interior  =
     point_interior2 =
     point_interior3 =
     point_interior4 = 1;
                         }
*/
}

}
else point_interior1 = 1; //End of  if( nb_intersection1 == -1 )...

//===================== We work with the third point ========================



if((zbuffer_quality > 1 ) &&  point_interior2  == -1 /*nb_intersection2 == -1*/ ){

        if ((((zbuffer[1][i]<=Y_averege2) && (Y_averege2<zbuffer[7][i])) ||

             ((zbuffer[7][i]<=Y_averege2) && (Y_averege2<zbuffer[1][i]))) &&

            (X_averege2 < (zbuffer[6][i] - zbuffer[0][i]) * (Y_averege2 - zbuffer[1][i])/(zbuffer[7][i] - zbuffer[1][i]) + zbuffer[0][i]))

                  nb_intersection2*=-1;


        if ((((zbuffer[3][i]<=Y_averege2) && (Y_averege2<zbuffer[1][i])) ||

             ((zbuffer[1][i]<=Y_averege2) && (Y_averege2<zbuffer[3][i]))) &&

            (X_averege2 < (zbuffer[0][i] - zbuffer[2][i]) * (Y_averege2 - zbuffer[3][i])/(zbuffer[1][i] - zbuffer[3][i]) + zbuffer[2][i]))

                  nb_intersection2*=-1;



        if ((((zbuffer[5][i]<=Y_averege2) && (Y_averege2<zbuffer[3][i])) ||

             ((zbuffer[3][i]<=Y_averege2) && (Y_averege2<zbuffer[5][i]))) &&

            (X_averege2 <  (zbuffer[2][i] - zbuffer[4][i]) * (Y_averege2 - zbuffer[5][i])/(zbuffer[3][i] - zbuffer[5][i])  + zbuffer[4][i]))

                  nb_intersection2*=-1;


        if ((((zbuffer[7][i]<=Y_averege2) && (Y_averege2<zbuffer[5][i])) ||

             ((zbuffer[5][i]<=Y_averege2) && (Y_averege2<zbuffer[7][i]))) &&

            (X_averege2 < (zbuffer[4][i] - zbuffer[6][i]) * (Y_averege2 - zbuffer[7][i])/(zbuffer[5][i] - zbuffer[7][i]) + zbuffer[6][i]))

                  nb_intersection2*=-1;



if(nb_intersection2 == 1 ) {

point_interior2 = 1;
/*
   if(zbuffer[10][i] == 1) {
     nb_intersection =
     nb_intersection1 =
     nb_intersection3 =
     nb_intersection4 = 1;  // if Poly too small, we stop looking for another intersections

     point_interior =
     point_interior1 =
     point_interior3 =
     point_interior4 = 1;
                           }
*/
}

}


else point_interior2 = 1 ; //End of  if( nb_intersection == -1 )...




//===================== We work with the fourth point ========================



if( (zbuffer_quality > 2 ) && point_interior3  == -1 /*nb_intersection3 == -1*/ ){
        if ((((zbuffer[1][i]<=Y_averege3) && (Y_averege3<zbuffer[7][i])) ||

             ((zbuffer[7][i]<=Y_averege3) && (Y_averege3<zbuffer[1][i]))) &&

            (X_averege3 <  (zbuffer[6][i] - zbuffer[0][i]) * (Y_averege3 - zbuffer[1][i])/(zbuffer[7][i] - zbuffer[1][i]) + zbuffer[0][i]))

                  nb_intersection3*=-1;


        if ((((zbuffer[3][i]<=Y_averege3) && (Y_averege3<zbuffer[1][i])) ||

             ((zbuffer[1][i]<=Y_averege3) && (Y_averege3<zbuffer[3][i]))) &&

            (X_averege3 < (zbuffer[0][i] - zbuffer[2][i]) * (Y_averege3 - zbuffer[3][i])/(zbuffer[1][i] - zbuffer[3][i]) + zbuffer[2][i]))

                  nb_intersection3*=-1;



        if ((((zbuffer[5][i]<=Y_averege3) && (Y_averege3<zbuffer[3][i])) ||

             ((zbuffer[3][i]<=Y_averege3) && (Y_averege3<zbuffer[5][i]))) &&

            (X_averege3 <  (zbuffer[2][i] - zbuffer[4][i]) * (Y_averege3 - zbuffer[5][i])/(zbuffer[3][i] - zbuffer[5][i])  + zbuffer[4][i]))

                  nb_intersection3*=-1;


        if ((((zbuffer[7][i]<=Y_averege3) && (Y_averege3<zbuffer[5][i])) ||

             ((zbuffer[5][i]<=Y_averege3) && (Y_averege3<zbuffer[7][i]))) &&

            (X_averege3 < (zbuffer[4][i] - zbuffer[6][i]) * (Y_averege3 - zbuffer[7][i])/(zbuffer[5][i] - zbuffer[7][i]) + zbuffer[6][i]))

                  nb_intersection3*=-1;



if(nb_intersection3 == 1 ) {

point_interior3 = 1;
/*
   if(zbuffer[10][i] == 1) {
     nb_intersection  =
     nb_intersection1 =
     nb_intersection2 =
     nb_intersection4 = 1;  // if Poly too small, we stop looking for another intersections

     point_interior  =
     point_interior1 =
     point_interior2 =
     point_interior4 = 1;
                           }
*/
}

} //End of  if( nb_intersection == -1 )...



else  point_interior3 = 1;

//===================== We work with the fifth point ========================



if( zbuffer_quality > 3  && point_interior4  == -1  /*nb_intersection4 == -1*/ ){

        if ((((zbuffer[1][i]<=Y_averege4) && (Y_averege4<zbuffer[7][i])) ||

             ((zbuffer[7][i]<=Y_averege4) && (Y_averege4<zbuffer[1][i]))) &&

            (X_averege4 <  ((zbuffer[6][i] - zbuffer[0][i]) * (Y_averege4 - zbuffer[1][i])+(zbuffer[7][i] - zbuffer[1][i])*zbuffer[0][i])/(zbuffer[7][i] - zbuffer[1][i])))

                  nb_intersection4*=-1;


        if ((((zbuffer[3][i]<=Y_averege4) && (Y_averege4<zbuffer[1][i])) ||

             ((zbuffer[1][i]<=Y_averege4) && (Y_averege4<zbuffer[3][i]))) &&

            (X_averege4 < ((zbuffer[0][i] - zbuffer[2][i]) * (Y_averege4 - zbuffer[3][i])+ (zbuffer[1][i] - zbuffer[3][i])*zbuffer[2][i])/(zbuffer[1][i] - zbuffer[3][i])))

                  nb_intersection4*=-1;



        if ((((zbuffer[5][i]<=Y_averege4) && (Y_averege4<zbuffer[3][i])) ||

             ((zbuffer[3][i]<=Y_averege4) && (Y_averege4<zbuffer[5][i]))) &&

            (X_averege4 < ((zbuffer[2][i] - zbuffer[4][i]) * (Y_averege4 - zbuffer[5][i])+(zbuffer[3][i] - zbuffer[5][i])*zbuffer[4][i])/(zbuffer[3][i] - zbuffer[5][i])))

                  nb_intersection4*=-1;


        if ((((zbuffer[7][i]<=Y_averege4) && (Y_averege4<zbuffer[5][i])) ||

             ((zbuffer[5][i]<=Y_averege4) && (Y_averege4<zbuffer[7][i]))) &&

            (X_averege4 < ((zbuffer[4][i] - zbuffer[6][i])*(Y_averege4 - zbuffer[7][i])+(zbuffer[5][i] - zbuffer[7][i])*zbuffer[6][i])/(zbuffer[5][i] - zbuffer[7][i])))

                  nb_intersection4*=-1;



if(nb_intersection4 == 1 ) {

point_interior4 = 1;
/*
   if(zbuffer[10][i] == 1) {
     nb_intersection  =
     nb_intersection1 =
     nb_intersection2 =
     nb_intersection3 = 1;  // if Poly too small, we stop looking for another intersections

     point_interior  =
     point_interior1 =
     point_interior2 =
     point_interior3 = 1;
                           }
*/
}

}
else  point_interior4 = 1;

//End of  if( nb_intersection == -1 )...


//===================== We test if ALL points are hidden =====================



if( point_interior  == 1 &&
    point_interior1 == 1 &&
    point_interior2 == 1 &&
    point_interior3 == 1 &&
    point_interior4 == 1   ){

prop_poly = vecteur_poly.at(j);

i = j;

prop_poly->zbuffer_validity = 0;

                            }

 } // End of if( r1 < (zbuffer[10][i] + zbuffer[10][j]))

      } // End of for(i = nb_poly -1; i > j ; i--)



itVectorData++;

}



}

///==============================================================================

/// Optimisation's End
///==============================================================================



/// +++++++++++++++++++++++++++++++++++++++++++++++++
/// here, we are going to compute all 3 Axes points
/// +++++++++++++++++++++++++++++++++++++++++++++++++

if(drawaxes_ok == 1) {

/// Axes points construction :

for(i=0; i< nb_licol ; i++){
//X
c4 = D/(Axes_array[0][i*3+2]-Oprime[2]);
 Axes_array_projection[0][i*3  ] = c4*Axes_array[0][i*3  ] + demi_hauteur;
 Axes_array_projection[0][i*3+1] = c4*Axes_array[0][i*3+1] + demi_largeur;
 //Axes_array_projection[0][i*3+2] = Axes_array[0][i*3+2];
//Y
c4 = D/(Axes_array[1][i*3+2]-Oprime[2]);
 Axes_array_projection[1][i*3  ] = c4*Axes_array[1][i*3  ] + demi_hauteur;
 Axes_array_projection[1][i*3+1] = c4*Axes_array[1][i*3+1] + demi_largeur;
 //Axes_array_projection[1][i*3+2] = Axes_array[1][i*3+2];
//Z
c4 = D/(Axes_array[2][i*3+2]-Oprime[2]);
 Axes_array_projection[2][i*3  ] = c4*Axes_array[2][i*3  ] + demi_hauteur;
 Axes_array_projection[2][i*3+1] = c4*Axes_array[2][i*3+1] + demi_largeur;
 //Axes_array_projection[2][i*3+2] = Axes_array[2][i*3+2];

}

/// Axes points projection construction :



///++++++++++++++++++++++++  TRIAGE des POLYGONES de l'axe X ++++++++++++++++++++++++

for(i=0; i< nb_licol -1 ; i++){
poly_courant = 20000 +i;

if((z_tmp = (Axes_array[0][i*3+2] + Axes_array[0][(i+1)*3+2]))/2 < 460 || clipping == -1 ) {
tableaureferences[poly_courant]->setPoint(0,
                                         (int)(Axes_array_projection[0][i*3  ]),
                                         (int)(Axes_array_projection[0][i*3+1]));
tableaureferences[poly_courant]->setPoint(1,
                                         (int)(Axes_array_projection[0][i*3  ]),
                                         (int)(Axes_array_projection[0][i*3+1]));
tableaureferences[poly_courant]->setPoint(2,
                                         (int)(Axes_array_projection[0][(i+1)*3  ]),
                                         (int)(Axes_array_projection[0][(i+1)*3+1]));
tableaureferences[poly_courant]->setPoint(3,
                                         (int)(Axes_array_projection[0][(i+1)*3  ]),
                                         (int)(Axes_array_projection[0][(i+1)*3+1]));
//z_tmp = (Axes_array[0][i*3+2] + Axes_array[0][(i+1)*3+2])/2;
///=============  Triage des polygones selon la valeurs de leurs profondeurs Z====

 itVectorData = vecteur_poly.begin();
 tmp=0;
 nb_poly = vecteur_poly.size();

if( nb_poly > 0)
{
           while( tmp < nb_poly) {
               if( z_tmp < vecteur_poly[tmp]->valeur_z )
  {
  tableau[poly_courant].pl = tableaureferences[poly_courant];
  tableau[poly_courant].valeur_z = z_tmp;
  tableau[poly_courant].valeur_cos = 0.1357; //this value	can help us to know if this poly belong to an axe X

  vecteur_poly.insert(itVectorData, &tableau[poly_courant]);
  tmp = nb_poly ;
  }

  else   {
      if( tmp==(nb_poly -1)) {
  tableau[poly_courant].pl = tableaureferences[poly_courant];
  tableau[poly_courant].valeur_z = z_tmp;
  tableau[poly_courant].valeur_cos = 0.1357;

  vecteur_poly.push_back(&tableau[poly_courant]);
  tmp = nb_poly ;
                             }
      else    {
      tmp++ ;
      itVectorData++;
              }
          }
                                 }
}
else {
  tableau[poly_courant].pl = tableaureferences[poly_courant];
  tableau[poly_courant].valeur_z = z_tmp;
  tableau[poly_courant].valeur_cos = 0.1357; //this value can help us to know if this poly belong to an axe X
  vecteur_poly.push_back(&tableau[poly_courant]);
}
}
}

///++++++++++++++++++++++++  TRIAGE des POLYGONES de l'axe Y ++++++++++++++++++++++++

for(i=0; i< nb_licol -1 ; i++){
poly_courant = 20100 + i;
if((z_tmp = (Axes_array[1][i*3+2] + Axes_array[1][(i+1)*3+2]))/2 < 460 || clipping == -1 ) {

tableaureferences[poly_courant]->setPoint(0,
                                         (int)(Axes_array_projection[1][i*3  ]),
                                         (int)(Axes_array_projection[1][i*3+1]));
tableaureferences[poly_courant]->setPoint(1,
                                         (int)(Axes_array_projection[1][i*3  ]),
                                         (int)(Axes_array_projection[1][i*3+1]));
tableaureferences[poly_courant]->setPoint(2,
                                         (int)(Axes_array_projection[1][(i+1)*3  ]),
                                         (int)(Axes_array_projection[1][(i+1)*3+1]));
tableaureferences[poly_courant]->setPoint(3,
                                         (int)(Axes_array_projection[1][(i+1)*3  ]),
                                         (int)(Axes_array_projection[1][(i+1)*3+1]));

//z_tmp = (Axes_array[1][i*3+2] + Axes_array[1][(i+1)*3+2])/2;
///=============  Triage des polygones selon la valeurs de leurs profondeurs Z====

 itVectorData = vecteur_poly.begin();
 tmp=0;

 nb_poly = vecteur_poly.size();
if( nb_poly > 0)
{
           while( tmp < nb_poly) {
               if( z_tmp < vecteur_poly[tmp]->valeur_z )
  {
  tableau[poly_courant].pl = tableaureferences[poly_courant];
  tableau[poly_courant].valeur_z = z_tmp;
  tableau[poly_courant].valeur_cos = 0.2357; //this value can help us to know if this poly belong to an axe Y

  vecteur_poly.insert(itVectorData, &tableau[poly_courant]);
  tmp = nb_poly ;
  }

  else   {
      if( tmp==(nb_poly -1)) {

  tableau[poly_courant].pl = tableaureferences[poly_courant];
  tableau[poly_courant].valeur_z = z_tmp;
  tableau[poly_courant].valeur_cos = 0.2357;

  vecteur_poly.push_back(&tableau[poly_courant]);
  tmp = nb_poly ;
                             }
      else    {
      tmp++ ;
      itVectorData++;
              }
         }
                                   }
}
else {
  tableau[poly_courant].pl = tableaureferences[poly_courant];
  tableau[poly_courant].valeur_z = z_tmp;
  tableau[poly_courant].valeur_cos = 0.2357; //this value	can help us to know if this poly belong to an axe Y
  vecteur_poly.push_back(&tableau[poly_courant]);
     }
}
}

///++++++++++++++++++++++++ TRIAGE des POLYGONES de l'axe Z ++++++++++++++++++++++++

for(i=0; i< nb_licol -1 ; i++){
poly_courant = 20200 + i;

if((z_tmp = (Axes_array[2][i*3+2] + Axes_array[2][(i+1)*3+2]))/2 < 460 || clipping == -1 ) {

tableaureferences[poly_courant]->setPoint(0,
                                         (int)(Axes_array_projection[2][i*3  ]),
                                         (int)(Axes_array_projection[2][i*3+1]));

tableaureferences[poly_courant]->setPoint(1,
                                         (int)(Axes_array_projection[2][i*3  ]),
                                         (int)(Axes_array_projection[2][i*3+1]));

tableaureferences[poly_courant]->setPoint(2,
                                         (int)(Axes_array_projection[2][(i+1)*3  ]),
                                         (int)(Axes_array_projection[2][(i+1)*3+1]));

tableaureferences[poly_courant]->setPoint(3,
                                         (int)(Axes_array_projection[2][(i+1)*3  ]),
                                         (int)(Axes_array_projection[2][(i+1)*3+1]));

// z_tmp = (Axes_array[2][i*3+2] + Axes_array[2][(i+1)*3+2])/2.;

///=============  Triage des polygones selon la valeurs de leurs profondeurs Z====

 itVectorData = vecteur_poly.begin();
 tmp=0;

 nb_poly = vecteur_poly.size();
if( nb_poly > 0)
{
           while( tmp < nb_poly) {
               if( z_tmp < vecteur_poly[tmp]->valeur_z )
  {
  tableau[poly_courant].pl = tableaureferences[poly_courant];
  tableau[poly_courant].valeur_z = z_tmp;
  tableau[poly_courant].valeur_cos = 0.3357; //this value	can help us to know if this poly belong to an axe Z

  vecteur_poly.insert(itVectorData, &tableau[poly_courant]);
  tmp = nb_poly ;
  }
  else   {
      if( tmp==(nb_poly -1)) {

  tableau[poly_courant].pl = tableaureferences[poly_courant];
  tableau[poly_courant].valeur_z = z_tmp;
  tableau[poly_courant].valeur_cos = 0.3357;

  vecteur_poly.push_back(&tableau[poly_courant]);
  tmp = nb_poly ;
                             }
      else    {
      tmp++ ;
      itVectorData++;
      }
                      }
                      }
}
else {
  tableau[poly_courant].pl = tableaureferences[poly_courant];
  tableau[poly_courant].valeur_z = z_tmp;
  tableau[poly_courant].valeur_cos = 0.3357; //this value	can help us to know if this poly belong to an axe Z
  vecteur_poly.push_back(&tableau[poly_courant]);
}
}
}// End of if((z_tmp=(Axes_array[2][i*3+2] + Axes_array[2][(i+1)*3+2])/2.)< 460 || clipping == -1 )


///=============  The last three poly that represents orrows heads====

double normale_last_pointX, normale_last_pointY;
if((i = nb_licol -1) > 1) // because we have to compute Axes_array[j][(i-1)*3  ]
 for(j=0; j< 3 ; j++){

poly_courant = 20000 + j*100 + i;

normale_last_pointX = -(Axes_array[j][(i-1)*3+1] - Axes_array[j][i*3+1]);
normale_last_pointY = Axes_array[j][(i-1)*3  ] - Axes_array[j][i*3  ];




if((z_tmp = (Axes_array[j][i*3+2] + Axes_array[j][(i-1)*3+2]))/2 < 460 || clipping == -1 ) {

tableaureferences[poly_courant]->setPoint(0,
                                         (int)(Axes_array_projection[j][i*3  ]),
                                         (int)(Axes_array_projection[j][i*3+1]));

tableaureferences[poly_courant]->setPoint(1,
                                         (int)(Axes_array_projection[j][(i-1)*3  ] + normale_last_pointX),
                                         (int)(Axes_array_projection[j][(i-1)*3+1] + normale_last_pointY));

tableaureferences[poly_courant]->setPoint(2,
                                         (int)(Axes_array_projection[j][(i-1)*3  ] - normale_last_pointX),
                                         (int)(Axes_array_projection[j][(i-1)*3+1] - normale_last_pointY));

tableaureferences[poly_courant]->setPoint(3,
                                         (int)(Axes_array_projection[j][i*3  ]),
                                         (int)(Axes_array_projection[j][i*3+1]));


// z_tmp = (Axes_array[2][i*3+2] + Axes_array[2][(i+1)*3+2])/2.;

///=============  Triage des polygones selon la valeurs de leurs profondeurs Z====

 itVectorData = vecteur_poly.begin();
 tmp=0;

 nb_poly = vecteur_poly.size();
if( nb_poly > 0)
{
           while( tmp < nb_poly) {
               if( z_tmp < vecteur_poly[tmp]->valeur_z )
  {
  tableau[poly_courant].pl = tableaureferences[poly_courant];
  tableau[poly_courant].valeur_z = z_tmp;
  tableau[poly_courant].valeur_cos = (j+1)*0.111123; // valeures aléatoires...

  vecteur_poly.insert(itVectorData, &tableau[poly_courant]);
  tmp = nb_poly ;
  }
  else   {
      if( tmp==(nb_poly -1)) {

  tableau[poly_courant].pl = tableaureferences[poly_courant];
  tableau[poly_courant].valeur_z = z_tmp;
  tableau[poly_courant].valeur_cos = (j+1)*0.111123;

  vecteur_poly.push_back(&tableau[poly_courant]);
  tmp = nb_poly ;
                             }
      else    {
      tmp++ ;
      itVectorData++;
      }
                      }
                      }
}
else {
  tableau[poly_courant].pl = tableaureferences[poly_courant];
  tableau[poly_courant].valeur_z = z_tmp;
  tableau[poly_courant].valeur_cos = (j+1)*0.111123;
  vecteur_poly.push_back(&tableau[poly_courant]);
}
}
}// End of if((z_tmp=(Axes_array[2][i*3+2] + Axes_array[2][(i+1)*3+2])/2.)< 460 || clipping == -1 )


};  //End of if(drawaxes_ok ==1)...


///=========================================================================
///                    AFFICHAGE DES POLYGONES


 nb_poly = vecteur_poly.size();
int Norx2, Nory2, positionx1, positiony1, positionx2, positiony2;
//Some useful variables
QColor redcol(255,0,0);
QColor Xaxecol(255,0,0);
QColor Yaxecol(0,255,0);
QColor Zaxecol(0,255,255);
QColor gridcol(gridliner,gridlineg,gridlineb);
QPen Xaxepen(Xaxecol, axe_width);
QPen Yaxepen(Yaxecol, axe_width);
QPen Zaxepen(Zaxecol, axe_width);


if(mesh ==1) {
g.setPen(gridcol);

if(interior_surface == 1 && exterior_surface == 1)
for (j=0; j < nb_poly   ; j++) {
prop_poly = vecteur_poly.at(j);
p         = prop_poly->pl;
cs        = prop_poly->valeur_cos;
if( (drawaxes_ok == 1) && ( cs == 0.1357 || cs == 0.2357 || cs == 0.3357 ||
                            cs == 0.111123 || cs == 0.222246 || cs == 0.333369 )) {
     if(cs == 0.1357){
               g.setPen(Xaxepen);
               g.drawLine ( p->point(0), p->point(2));
               g.setPen(gridcol);
               }
     else if(cs == 0.2357){
               g.setPen(Yaxepen);//setWidth ( uint w );
               g.drawLine ( p->point(0), p->point(2));
               g.setPen(gridcol);
               }
     else if(cs == 0.3357){
               g.setPen(Zaxepen);//setWidth ( uint w );
               g.drawLine ( p->point(0), p->point(2));
               g.setPen(gridcol);
               }
     else if(cs == 0.111123){
               g.setPen(Xaxepen);//setWidth ( uint w );
               p->point(0, &positionx1, &positiony1);
               p->point(1, &positionx2, &positiony2);
               g.drawText(positionx1+(positionx1-positionx2), positiony1+(positiony1-positiony2), "X");
               //g.setBrush(Xaxecol);
               g.drawPolygon ( *p);
               g.setPen(gridcol);
               }
     else if(cs == 0.222246){
               g.setPen(Yaxepen);//setWidth ( uint w );
               p->point(0, &positionx1, &positiony1);
               p->point(1, &positionx2, &positiony2);
               g.drawText(positionx1+(positionx1-positionx2), positiony1+(positiony1-positiony2), "Y");
               //g.setBrush(Yaxecol);
               g.drawPolygon ( *p);
               g.setPen(gridcol);
               }
     else if(cs == 0.333369){
               g.setPen(Zaxepen);//setWidth ( uint w );
               p->point(0, &positionx1, &positiony1);
               p->point(1, &positionx2, &positiony2);
               g.drawText(positionx1+(positionx1-positionx2), positiony1+(positiony1-positiony2), "Z");
               //g.setBrush(Zaxecol);
               g.drawPolygon ( *p);
               g.setPen(gridcol);
                }}
else
if( zbuffer_active_ok != 1 || prop_poly->zbuffer_validity == 1) {
if(cs >0) {

if(  draw_hidden_poly_and_nonhidden == 1 && prop_poly->condition_validity == -1) {

          if(draw_cond_mesh == 1){
               g.setPen(redcol);
               g.drawPolyline(*p);
               g.drawLine ( p->point(0), p->point(3));
               g.setPen(gridcol);}
          else {
               g.setBrush(palette_cond_face[(int)(cs*256)]);
               g.drawPolygon(*p);
               }
}
else {  g.setBrush(palette_back_face[(int)(cs*256)]);
        g.drawPolygon(*p);

}
        } // End if(  draw_hidden_poly_and_nonhidden == 1 && ....
else {


if(  draw_hidden_poly_and_nonhidden == 1 && prop_poly->condition_validity == -1){

          if(draw_cond_mesh ==1){
               g.setPen(redcol);
               g.drawPolyline(*p);
               g.drawLine ( p->point(0), p->point(3));

       if(draw_poly_normals == 1) {
               prop_poly->pl->point(0, &Norx2, &Nory2);
               g.drawLine(prop_poly->Norx, prop_poly->Nory, Norx2, Nory2);

       }
               g.setPen(gridcol);}
          else {
               g.setBrush(palette_cond_face[-(int)(cs*256)]);
               g.drawPolygon(*p);
       if(draw_poly_normals == 1) {
               prop_poly->pl->point(0, &Norx2, &Nory2);
               g.drawLine(prop_poly->Norx, prop_poly->Nory, Norx2, Nory2);

       }
               }
}
else {
    g.setBrush(palette_front_face[-(int)(cs*256)]);
    g.drawPolygon(*p);
    if(draw_poly_normals == 1) {
       prop_poly->pl->point(0, &Norx2, &Nory2);
       g.drawLine(prop_poly->Norx, prop_poly->Nory, Norx2, Nory2);
       }
     }
     }
itVectorData++;
}
} //End of if( prop_poly->zbuffer_validity == 1)
else {
if(interior_surface == 1 )
for (j=0; j < nb_poly   ; j++) {
prop_poly = vecteur_poly.at(j);
p         = prop_poly->pl;
cs        = prop_poly->valeur_cos;
if(cs >0) {

if(  draw_hidden_poly_and_nonhidden == 1 && prop_poly->condition_validity == -1)
g.setBrush(palette_cond_face[(int)(cs*256)]);
else g.setBrush(palette_back_face[(int)(cs*256)]);

        g.drawPolygon(*p);
        }
itVectorData++;
}

if(exterior_surface == 1 )
for (j=0; j < nb_poly   ; j++) {
prop_poly = vecteur_poly.at(j);
p         = prop_poly->pl;
cs        = prop_poly->valeur_cos;
if(cs <= 0) {
if(  draw_hidden_poly_and_nonhidden == 1 && prop_poly->condition_validity == -1)
g.setBrush(palette_cond_face[-(int)(cs*256)]);
else g.setBrush(palette_front_face[-(int)(cs*256)]);
g.drawPolygon(*p);
     }

itVectorData++;
}

}

} // End of if(mesh ==1)


else {
g.setPen(gridcol);

if(interior_surface == 1 && exterior_surface == 1)
for (j=0; j < nb_poly   ; j++) {
prop_poly = vecteur_poly.at(j);
p         = prop_poly->pl;
cs        = prop_poly->valeur_cos;
if( zbuffer_active_ok != 1 || prop_poly->zbuffer_validity == 1) {
/*if(cs >0) {
        g.drawPolygon(*p);
        }
else {
	g.drawPolygon(*p); //!!!!!!! the same instruction !!!
     }
     */ g.drawPolygon(*p);
itVectorData++;
}
} //End of if( prop_poly->zbuffer_validity == 1)



else {
if(interior_surface == 1 )
for (j=0; j < nb_poly   ; j++) {
prop_poly = vecteur_poly.at(j);
p         = prop_poly->pl;
cs        = prop_poly->valeur_cos;
if(cs >0) {
//g.setBrush(palette_back_face[(int)(cs*256)]);
        g.drawPolygon(*p);
        }
itVectorData++;
}

if(exterior_surface == 1 )
for (j=0; j < nb_poly   ; j++) {
prop_poly = vecteur_poly.at(j);
p         = prop_poly->pl;
cs        = prop_poly->valeur_cos;
if(cs <= 0) {
//g.setBrush(palette_front_face[-(int)(cs*256)]);
	g.drawPolygon(*p);
     }
itVectorData++;
}

}

}

// hidden surface removal (HSR)

 // Delete the vector
    vecteur_poly.clear();



if(infos ==1) {


if((i= nb_colone - 1 - coupure_col) <0) i=0;
if((j= nb_ligne - 1 - coupure_ligne) <0) j=0;

g.setPen(QColor(250,0,0));
g.drawText(5,15,"Grid = "+QString::number(i)+" x "+QString::number(j)+" = "+QString::number(i*j));

g.setPen(QColor(0,250,0));
g.drawText(5,
           15,
           "Grid = ");



g.setPen(QColor(250,0,0));
g.drawText(5,30,"Polygn = "+QString::number(nb_poly));

g.setPen(QColor(0,250,0));
g.drawText(5,
           30,
           "Polygn = ");




g.setPen(QColor(250,0,0));
g.drawText(5,45,"t_Step = "+QString::number((int)(1/step)+1));

g.setPen(QColor(0,250,0));
g.drawText(5,
           45,
           "t_Step = ");

g.setPen(QColor(250,0,0));
g.drawText(5,60,"Latency = "+QString::number(latence)+"ms");

g.setPen(QColor(0,250,0));
g.drawText(5,
           60,
           "Latency = ");

if(zbuffer_active_ok == 1 ) {
g.setPen(QColor(250,0,0));
g.drawText(5,75,"Zbuffer = "+QString::number(zbuffer_quality));

g.setPen(QColor(0,250,0));
g.drawText(5,
           75,
           "Zbuffer = ");
}


if(independantwindow == 1) {
g.setPen(QColor(250,0,0));
g.drawText(5,75,"  h=Help  ");
}
if(showhelp == 1){
g.setPen(QColor(250,0,0));
g.drawText(5,75,"\
| h=Help | a=Anim | p=Morfh | m=Mesh | b=Box | i=Infos | c=Clip |");
g.setPen(QColor(250,0,0));
g.drawText(5,95,"\
| key_left=line-- | key_right=line++ | key_up=column++ | key_down=column-- |");
g.setPen(QColor(250,0,0));
g.drawText(5,110,"\
| key_Prior=Grid++ | key_Next=Grid-- |");
}
}
  }

/*****************************************************************************/
/*****************************************************************************/
void Model3D::fct_bouton_gauche3 () {
     rotation3();
     calcul_points3();
}

/*****************************************************************************/
/*****************************************************************************/
/*
void Model3D::fct_bouton_gauche4 () {

     rotation4();
     calcul_points3();
}
*/
/*****************************************************************************/
/*****************************************************************************/
void Model3D::fct_bouton_milieu3 () {

     translation3();
     calcul_points3();
}

/*****************************************************************************/
/*****************************************************************************/
void Model3D::fct_bouton_droit3 () {

     homothetie3();
     calcul_points3();
}

/*****************************************************************************/
/*****************************************************************************/
void Model3D::fct_bouton_Anim3 () {

     rotation3();
     calcul_points3(); // On applique la rotation et l'homothetie
}

/*****************************************************************************/
/*****************************************************************************/

void Model3D::fct_bouton_Morph3() {
	initialiser_parseur3();
	calcul_objet3();  // Utilisation du parseur..
	boite_englobante3();
	//normalisation3(); // Calcul des normales
	calcul_points3(); // On applique la rotation et l'homothetie

}
/*****************************************************************************/
/*****************************************************************************/

void Model3D::fct_bouton_AnimMorph() {
	initialiser_parseur3();
        rotation3();
	calcul_objet3();  // Utilisation du parseur..
	boite_englobante3();
	//normalisation3(); // Calcul des normales
	calcul_points3(); // On applique la rotation et l'homothetie

}
/*****************************************************************************/
/*****************************************************************************/
void Model3D::fct_calcul3 () {

	initialiser_parseur3();
	parse_expression();
	calcul_objet3();  // Utilisation du parseur..
	boite_englobante3();
	//normalisation3(); // Calcul des normales
	calcul_points3(); // On applique la rotation et l'homothetie

}
/*****************************************************************************/
/*****************************************************************************/
void Model3D::fct_calcul2 () {

	//initialiser_parseur3();
	parse_expression();
	calcul_objet3();  // Utilisation du parseur..
	boite_englobante3();
	//normalisation3(); // Calcul des normales
	calcul_points3(); // On applique la rotation et l'homothetie

}
/*****************************************************************************/
/*****************************************************************************/

void  Model3D::homothetie3() {

mat_homothetie.unit();

mat_homothetie.xx = mat_homothetie.yy = mat_homothetie.zz = coefficient;

// Application a la matrice principale:

mat.mult(mat_homothetie);
}

/*****************************************************************************/
/*****************************************************************************/

void  Model3D::translation3() {

mat_translation.unit();
translatex = mat_translation.xo = angley ;
translatey = mat_translation.yo = anglex ;
mat_translation.zo = 0 ;

// Application a la matrice principale
mat.mult(mat_translation);
}

/*****************************************************************************/
/*****************************************************************************/

void  Model3D::rotation3(){

        mat_rotation.unit();

// Construction de la matrice de trnsformation
        mat_rotation.xrot(anglex );
        mat_rotation.yrot(angley );
//we have to invert the translation before applaying the rotation

mat_inversetranslation.unit();
mat_inversetranslation.xo = -center[0] ;
mat_inversetranslation.yo = -center[1] ;
mat_inversetranslation.zo = -center[2] ;

            mat.mult(mat_inversetranslation);
// On applique cette transformation a la matrice principale "mat"
mat.mult(mat_rotation);

// Now we return the object to it's first place..
mat_inversetranslation.unit();
mat_inversetranslation.xo = center[0] ;
mat_inversetranslation.yo = center[1] ;
mat_inversetranslation.zo = center[2] ;

                mat.mult(mat_inversetranslation);
		mat_rotation_save.mult(mat_rotation);


	}


/*****************************************************************************/
/*****************************************************************************/
void  Model3D::rotation4(){

        mat_rotation4D.unit();
//tetaxy = 4;tetaxz = 4;tetayz = 4;// for testing
//tetaxw = 4;tetayw = 4;tetazw = 4;// for testing

// Construction de la matrice de trnsformation
    if(tetaxy_ok == 1)    mat_rotation4D.xyrot(tetaxy);
    if(tetaxz_ok == 1)    mat_rotation4D.xzrot(tetaxz);
    if(tetayz_ok == 1)    mat_rotation4D.yzrot(tetayz);

    if(tetaxw_ok == 1)    mat_rotation4D.xwrot(tetaxw);
    if(tetayw_ok == 1)    mat_rotation4D.ywrot(tetayw);
    if(tetazw_ok == 1)    mat_rotation4D.zwrot(tetazw);


// On applique cette transformation a la matrice principale "mat"
    mat4D.mult(mat_rotation4D);

}

/*****************************************************************************/
/*****************************************************************************/
void  Model3D::rotation5(){
// Second version of 5D rotation
// here we don't use special mat_rotation5D
    if(tetaxy_ok == 1)    mat5D.xyrot(tetaxy);
    if(tetaxz_ok == 1)    mat5D.xzrot(tetaxz);
    if(tetayz_ok == 1)    mat5D.yzrot(tetayz);

    if(tetaxw_ok == 1)    mat5D.xwrot(tetaxw);
    if(tetayw_ok == 1)    mat5D.ywrot(tetayw);
    if(tetazw_ok == 1)    mat5D.zwrot(tetazw);

    if(tetaxt_ok == 1)    mat5D.xtrot(tetaxt);
    if(tetayt_ok == 1)    mat5D.ytrot(tetayt);
    if(tetazt_ok == 1)    mat5D.ztrot(tetazt);
    if(tetawt_ok == 1)    mat5D.wtrot(tetawt);

}
/*****************************************************************************/
/*****************************************************************************/
void  Model3D::rotation6(){
// Second version of 5D rotation
// here we don't use special mat_rotation5D
    if(tetaxy_ok == 1)    mat6D.xyrot(tetaxy);
    if(tetaxz_ok == 1)    mat6D.xzrot(tetaxz);
    if(tetayz_ok == 1)    mat6D.yzrot(tetayz);

    if(tetaxw_ok == 1)    mat6D.xwrot(tetaxw);
    if(tetayw_ok == 1)    mat6D.ywrot(tetayw);
    if(tetazw_ok == 1)    mat6D.zwrot(tetazw);

    if(tetaxt_ok == 1)    mat6D.xtrot(tetaxt);
    if(tetayt_ok == 1)    mat6D.ytrot(tetayt);
    if(tetazt_ok == 1)    mat6D.ztrot(tetazt);
    if(tetawt_ok == 1)    mat6D.wtrot(tetawt);

    if(tetaxs_ok == 1)    mat6D.xsrot(tetaxs);
    if(tetays_ok == 1)    mat6D.ysrot(tetays);
    if(tetazs_ok == 1)    mat6D.zsrot(tetazs);
    if(tetaws_ok == 1)    mat6D.wsrot(tetaws);
    if(tetats_ok == 1)    mat6D.tsrot(tetats);
}
/*****************************************************************************/
/*****************************************************************************/
void Model3D::fct_bouton_Anim4 () {

   rotation4();
   calcul_points4();         // On applique la rotation 4D
   //boite_englobante4D();// pas necessaire...donne resultat bizarre!!!
   project_4D_to_3D();
   boite_englobante3(); //<--try to find something else more convenient
   ////normalisation3(); // Calcul des normales...doit etre fait prochainement en 4D
   calcul_points3(); // On applique la rotation et l'homothetie
   mat4D.unit();

}

/*****************************************************************************/
/*****************************************************************************/
void Model3D::fct_bouton_Anim5 () {

   rotation5();
   calcul_points5();         // On applique la rotation 5D
   project_5D_to_4D();
   project_4D_to_3D();
   boite_englobante3(); //<--try to find something else more convenien
   calcul_points3(); // On applique la rotation et l'homothetie  (en 3D)
   mat5D.unit();
/*
   boite_englobante5D();
   project_5D_to_4D();
   //boite_englobante4D();
   project_4D_to_3D();
*/

}

/*****************************************************************************/
/*****************************************************************************/
void Model3D::fct_bouton_Anim6 () {

   rotation6();
   calcul_points6(); // On applique la rotation 5D
   project_6D_to_5D();
   project_5D_to_4D();
   project_4D_to_3D();
   boite_englobante3(); //<--try to find something else more convenien
   calcul_points3(); // On applique la rotation et l'homothetie  (en 3D)
   mat6D.unit();
/*
   boite_englobante5D();
   project_5D_to_4D();
   //boite_englobante4D();
   project_4D_to_3D();
*/

}

/*****************************************************************************/
/*****************************************************************************/



void  Model3D::calcul_points4(){
int i,j;

 // Changement de coordonnees des points selon les
 // angles angex et angley

 for (i=0; i < nb_ligne  ; i++)
   for (j=0; j < nb_colone   ; j++)
      {
        tp1 = shape4D[i*4    ][j];
        tp2 = shape4D[i*4 + 1][j];
        tp3 = shape4D[i*4 + 2][j];
        tp4 = shape4D[i*4 + 3][j];

        shape4D[i*4  ][j] = mat4D.xx*tp1 + mat4D.xy*tp2 + mat4D.xz*tp3 + mat4D.xw*tp4 + mat4D.xo;
        shape4D[i*4+1][j] = mat4D.yx*tp1 + mat4D.yy*tp2 + mat4D.yz*tp3 + mat4D.yw*tp4 + mat4D.yo;
        shape4D[i*4+2][j] = mat4D.zx*tp1 + mat4D.zy*tp2 + mat4D.zz*tp3 + mat4D.zw*tp4 + mat4D.zo;
	shape4D[i*4+3][j] = mat4D.wx*tp1 + mat4D.wy*tp2 + mat4D.wz*tp3 + mat4D.ww*tp4 + mat4D.wo;
                                 }
}

/*****************************************************************************/
/*****************************************************************************/



void  Model3D::calcul_points5(){
int i,j;

 // Changement de coordonnees des points selon les
 // angles angex et angley

 for (i=0; i < nb_ligne  ; i++)
   for (j=0; j < nb_colone   ; j++)
      {
        tp1 = shape5D[i*5    ][j];
        tp2 = shape5D[i*5 + 1][j];
        tp3 = shape5D[i*5 + 2][j];
	tp4 = shape5D[i*5 + 3][j];
	tp5 = shape5D[i*5 + 4][j];

shape5D[i*5  ][j] = mat5D.xx*tp1 + mat5D.xy*tp2 + mat5D.xz*tp3 + mat5D.xw*tp4 + mat5D.xt*tp5 + mat5D.xo;
shape5D[i*5+1][j] = mat5D.yx*tp1 + mat5D.yy*tp2 + mat5D.yz*tp3 + mat5D.yw*tp4 + mat5D.yt*tp5 + mat5D.yo;
shape5D[i*5+2][j] = mat5D.zx*tp1 + mat5D.zy*tp2 + mat5D.zz*tp3 + mat5D.zw*tp4 + mat5D.zt*tp5 + mat5D.zo;
shape5D[i*5+3][j] = mat5D.wx*tp1 + mat5D.wy*tp2 + mat5D.wz*tp3 + mat5D.ww*tp4 + mat5D.wt*tp5 + mat5D.wo;
shape5D[i*5+4][j] = mat5D.tx*tp1 + mat5D.ty*tp2 + mat5D.tz*tp3 + mat5D.tw*tp4 + mat5D.tt*tp5 + mat5D.to;
                                 }
}
/*****************************************************************************/
/*****************************************************************************/



void  Model3D::calcul_points6(){
int i,j;

 // Changement de coordonnees des points selon les
 // angles angex et angley

 for (i=0; i < nb_ligne  ; i++)
   for (j=0; j < nb_colone   ; j++)
      {
        tp1 = shape6D[i*6    ][j];
        tp2 = shape6D[i*6 + 1][j];
        tp3 = shape6D[i*6 + 2][j];
	  tp4 = shape6D[i*6 + 3][j];
	  tp5 = shape6D[i*6 + 4][j];
	  tp6 = shape6D[i*6 + 5][j];

shape6D[i*6  ][j] = mat6D.xx*tp1 + mat6D.xy*tp2 + mat6D.xz*tp3 + mat6D.xw*tp4 + mat6D.xt*tp5 + mat6D.xs*tp6 + mat6D.xo;
shape6D[i*6+1][j] = mat6D.yx*tp1 + mat6D.yy*tp2 + mat6D.yz*tp3 + mat6D.yw*tp4 + mat6D.yt*tp5 + mat6D.ys*tp6 + mat6D.yo;
shape6D[i*6+2][j] = mat6D.zx*tp1 + mat6D.zy*tp2 + mat6D.zz*tp3 + mat6D.zw*tp4 + mat6D.zt*tp5 + mat6D.zs*tp6 + mat6D.zo;
shape6D[i*6+3][j] = mat6D.wx*tp1 + mat6D.wy*tp2 + mat6D.wz*tp3 + mat6D.ww*tp4 + mat6D.wt*tp5 + mat6D.ws*tp6 + mat6D.wo;
shape6D[i*6+4][j] = mat6D.tx*tp1 + mat6D.ty*tp2 + mat6D.tz*tp3 + mat6D.tw*tp4 + mat6D.tt*tp5 + mat6D.ts*tp6 + mat6D.to;
shape6D[i*6+5][j] = mat6D.sx*tp1 + mat6D.sy*tp2 + mat6D.sz*tp3 + mat6D.sw*tp4 + mat6D.st*tp5 + mat6D.ss*tp6 + mat6D.so;
                                 }
}
/*****************************************************************************/
/*****************************************************************************/

void  Model3D::normalisation3(){
int i,j;
double b4;
// Construction des normales : (premiere methode )


    for (j=0; j < nb_colone -1   ; j++)
     for (i=0; i < nb_ligne -1  ; i++) {

caa  = Tre2[(i+1)*3+1][j  ] - Tre2[i*3+1][j];
bab  = Tre2[i*3    +2][j+1] - Tre2[i*3+2][j];
cab  = Tre2[(i+1)*3+2][j  ] - Tre2[i*3+2][j];
baa  = Tre2[i*3    +1][j+1] - Tre2[i*3+1][j];
ba   = Tre2[i*3      ][j+1] - Tre2[i*3  ][j];
ca   = Tre2[(i+1)*3  ][j  ] - Tre2[i*3  ][j];

Nor2[i*3  ][j] = caa*bab - cab*baa;
Nor2[i*3+1][j] = cab*ba  - ca*bab;
Nor2[i*3+2][j] = ca*baa  - caa*ba;


 b4 = (double)sqrt((Nor2[i*3  ][j]*Nor2[i*3  ][j]) +
                         (Nor2[i*3+1][j]*Nor2[i*3+1][j]) +
                         (Nor2[i*3+2][j]*Nor2[i*3+2][j])  );


// This must be changed...
if(b4 > 0.00000001) {
Nor[i*3  ][j]= (Nor2[i*3  ][j]/=b4);
Nor[i*3+1][j]= (Nor2[i*3+1][j]/=b4);
Nor[i*3+2][j]= (Nor2[i*3+2][j]/=b4);
}

}


i = nb_ligne -1;
 for (j=0; j < nb_colone -1   ; j++) {
Nor[i*3  ][j] = Nor2[i*3  ][j] = Nor2[(i-1)*3  ][j];
Nor[i*3+1][j] = Nor2[i*3+1][j] = Nor2[(i-1)*3+1][j];
Nor[i*3+2][j] = Nor2[i*3+2][j] = Nor2[(i-1)*3+2][j];
 }


j =nb_colone -1;
 for (i=0; i < nb_ligne -1  ; i++) {
Nor[i*3  ][j]= Nor2[i*3  ][j]= Nor2[i*3  ][j-1];
Nor[i*3+1][j]= Nor2[i*3+1][j]= Nor2[i*3+1][j-1];
Nor[i*3+2][j]= Nor2[i*3+2][j]= Nor2[i*3+2][j-1];
                                       }



	}

/*****************************************************************************/
/*****************************************************************************/



void  Model3D::calcul_points3(){
int i,j;
 // pour savoir ou se trouve le centre de l'objet

 moitie_colone = (int)(nb_colone/2);


         center[0] =  mat.xo;
         center[1] =  mat.yo;
         center[2] =  mat.zo;

 // Changement de coordonnees des points selon les
 // angles angex et angley
 if(two_separate_objects == -1 ) {
 mat_first_obj = mat_second_obj = mat;
 mat_rotation_first_save= mat_rotation_second_save = mat_rotation_save;


 for (i=0; i < nb_ligne  ; i++)
   for (j=0; j < nb_colone   ; j++){
        tp1 = Tre2[i*3    ][j];
        tp2 = Tre2[i*3 + 1][j];
        tp3 = Tre2[i*3 + 2][j];
        Tre[i*3  ][j] = mat.xx*tp1 + mat.xy*tp2 +mat.xz*tp3 + mat.xo;
        Tre[i*3+1][j] = mat.yx*tp1 + mat.yy*tp2 +mat.yz*tp3 + mat.yo;
        Tre[i*3+2][j] = mat.zx*tp1 + mat.zy*tp2 +mat.zz*tp3 + mat.zo;
                                 }

/*
 //Normales
 for (i=0; i < nb_ligne  ; i++)
 for (j=0; j < nb_colone    ; j++) {
        tp1 = Nor2[i*3    ][j];
        tp2 = Nor2[i*3 + 1][j];
        tp3 = Nor2[i*3 + 2][j];
        Nor[i*3  ][j] = mat_rotation_save.xx*tp1 + mat_rotation_save.xy*tp2 +mat_rotation_save.xz*tp3 + mat_rotation_save.xo;
        Nor[i*3+1][j] = mat_rotation_save.yx*tp1 + mat_rotation_save.yy*tp2 +mat_rotation_save.yz*tp3 + mat_rotation_save.yo;
        Nor[i*3+2][j] = mat_rotation_save.zx*tp1 + mat_rotation_save.zy*tp2 +mat_rotation_save.zz*tp3 + mat_rotation_save.zo;

    }

*/


 // here we are testing if there is much more points to transforme
 // in the case we have a conditional equation...
 if( there_is_condition == 1) {
   for (i=0; i < nb_ligne  ; i++)
   for (j=0; j < nb_colone   ; j++){
       if(hidden_points[i][j] == 0){
       //DR
        tp1 = DR2[i*3    ][j];
        tp2 = DR2[i*3 + 1][j];
        tp3 = DR2[i*3 + 2][j];
        DR[i*3  ][j] = mat.xx*tp1 + mat.xy*tp2 +mat.xz*tp3 + mat.xo;
        DR[i*3+1][j] = mat.yx*tp1 + mat.yy*tp2 +mat.yz*tp3 + mat.yo;
        DR[i*3+2][j] = mat.zx*tp1 + mat.zy*tp2 +mat.zz*tp3 + mat.zo;
       //DL
        tp1 = DL2[i*3    ][j];
        tp2 = DL2[i*3 + 1][j];
        tp3 = DL2[i*3 + 2][j];
        DL[i*3  ][j] = mat.xx*tp1 + mat.xy*tp2 +mat.xz*tp3 + mat.xo;
        DL[i*3+1][j] = mat.yx*tp1 + mat.yy*tp2 +mat.yz*tp3 + mat.yo;
        DL[i*3+2][j] = mat.zx*tp1 + mat.zy*tp2 +mat.zz*tp3 + mat.zo;
       //HR
        tp1 = HR2[i*3    ][j];
        tp2 = HR2[i*3 + 1][j];
        tp3 = HR2[i*3 + 2][j];
        HR[i*3  ][j] = mat.xx*tp1 + mat.xy*tp2 +mat.xz*tp3 + mat.xo;
        HR[i*3+1][j] = mat.yx*tp1 + mat.yy*tp2 +mat.yz*tp3 + mat.yo;
        HR[i*3+2][j] = mat.zx*tp1 + mat.zy*tp2 +mat.zz*tp3 + mat.zo;
       //HL
        tp1 = HL2[i*3    ][j];
        tp2 = HL2[i*3 + 1][j];
        tp3 = HL2[i*3 + 2][j];
        HL[i*3  ][j] = mat.xx*tp1 + mat.xy*tp2 +mat.xz*tp3 + mat.xo;
        HL[i*3+1][j] = mat.yx*tp1 + mat.yy*tp2 +mat.yz*tp3 + mat.yo;
        HL[i*3+2][j] = mat.zx*tp1 + mat.zy*tp2 +mat.zz*tp3 + mat.zo;
                                 }
     } // End if(hidden_points[i][j] == 0)...
     } // End  if( there_is_condition == 1)

/*
 //Normales
 for (i=0; i < nb_ligne  ; i++)
 for (j=0; j < nb_colone    ; j++) {
        tp1 = Nor2[i*3    ][j];
        tp2 = Nor2[i*3 + 1][j];
        tp3 = Nor2[i*3 + 2][j];
        Nor[i*3  ][j] = mat_rotation_save.xx*tp1 + mat_rotation_save.xy*tp2 +mat_rotation_save.xz*tp3 + mat_rotation_save.xo;
        Nor[i*3+1][j] = mat_rotation_save.yx*tp1 + mat_rotation_save.yy*tp2 +mat_rotation_save.yz*tp3 + mat_rotation_save.yo;
        Nor[i*3+2][j] = mat_rotation_save.zx*tp1 + mat_rotation_save.zy*tp2 +mat_rotation_save.zz*tp3 + mat_rotation_save.zo;

    }
*/
 }
 else  {
 if(change_first_object == 1) {

  for (i=0; i < nb_ligne  ; i++)
   for (j=0; j < moitie_colone -1  ; j++){
        tp1 = Tre2[i*3    ][j];
        tp2 = Tre2[i*3 + 1][j];
        tp3 = Tre2[i*3 + 2][j];
        Tre[i*3  ][j] = mat.xx*tp1 + mat.xy*tp2 +mat.xz*tp3 + mat.xo;
        Tre[i*3+1][j] = mat.yx*tp1 + mat.yy*tp2 +mat.yz*tp3 + mat.yo;
        Tre[i*3+2][j] = mat.zx*tp1 + mat.zy*tp2 +mat.zz*tp3 + mat.zo;
                                 }
/*
// Normales
for (i=0; i < nb_ligne  ; i++)
for (j=0; j < moitie_colone -1   ; j++) {
        tp1 = Nor2[i*3    ][j];
        tp2 = Nor2[i*3 + 1][j];
        tp3 = Nor2[i*3 + 2][j];
        Nor[i*3  ][j] = mat_rotation_save.xx*tp1 + mat_rotation_save.xy*tp2 +mat_rotation_save.xz*tp3 + mat_rotation_save.xo;
        Nor[i*3+1][j] = mat_rotation_save.yx*tp1 + mat_rotation_save.yy*tp2 +mat_rotation_save.yz*tp3 + mat_rotation_save.yo;
        Nor[i*3+2][j] = mat_rotation_save.zx*tp1 + mat_rotation_save.zy*tp2 +mat_rotation_save.zz*tp3 + mat_rotation_save.zo;

     }
*/
     //mat_first_obj = mat;
     //mat_rotation_first_save= mat_rotation_save;

     }
  if(change_second_object == 1){
  for (i=0; i < nb_ligne  ; i++)
   for (j=moitie_colone -1; j < nb_colone ; j++){
        tp1 = Tre2[i*3    ][j];
        tp2 = Tre2[i*3 + 1][j];
        tp3 = Tre2[i*3 + 2][j];
        Tre[i*3  ][j] = mat.xx*tp1 + mat.xy*tp2 +mat.xz*tp3 + mat.xo;
        Tre[i*3+1][j] = mat.yx*tp1 + mat.yy*tp2 +mat.yz*tp3 + mat.yo;
        Tre[i*3+2][j] = mat.zx*tp1 + mat.zy*tp2 +mat.zz*tp3 + mat.zo;
                                 }
/*
// Normales
for (i=0; i < nb_ligne  ; i++)
for (j = moitie_colone -1; j < nb_colone    ; j++) {
        tp1 = Nor2[i*3    ][j];
        tp2 = Nor2[i*3 + 1][j];
        tp3 = Nor2[i*3 + 2][j];
        Nor[i*3  ][j] = mat_rotation_save.xx*tp1 + mat_rotation_save.xy*tp2 +mat_rotation_save.xz*tp3 + mat_rotation_save.xo;
        Nor[i*3+1][j] = mat_rotation_save.yx*tp1 + mat_rotation_save.yy*tp2 +mat_rotation_save.yz*tp3 + mat_rotation_save.yo;
        Nor[i*3+2][j] = mat_rotation_save.zx*tp1 + mat_rotation_save.zy*tp2 +mat_rotation_save.zz*tp3 + mat_rotation_save.zo;
    }
*/
     //mat_second_obj = mat;
     //mat_rotation_second_save = mat_rotation_save;
    }
      }

// Boite englobante

for (i=0; i < 8  ; i++) {

        tp1 = boiteenglobante2[i*3    ];
        tp2 = boiteenglobante2[i*3 + 1];
        tp3 = boiteenglobante2[i*3 + 2];
        boiteenglobante[i*3    ] = mat.xx*tp1 + mat.xy*tp2 +mat.xz*tp3 + mat.xo;
        boiteenglobante[i*3 + 1] = mat.yx*tp1 + mat.yy*tp2 +mat.yz*tp3 + mat.yo;
        boiteenglobante[i*3 + 2] = mat.zx*tp1 + mat.zy*tp2 +mat.zz*tp3 + mat.zo;

                                      }


//+++++++++++++++++++++++++++++++++++++++++++++++++//
// here, we are going to compute all 3 Axes points
//+++++++++++++++++++++++++++++++++++++++++++++++++//

if(drawaxes_ok == 1){


for (j=0; j < 3  ; j++)
for (i=0; i < nb_licol  ; i++) {

        tp1 = Axes_array2[j][i*3    ];
        tp2 = Axes_array2[j][i*3 + 1];
        tp3 = Axes_array2[j][i*3 + 2];
        Axes_array[j][i*3    ] = mat.xx*tp1 + mat.xy*tp2 +mat.xz*tp3 + mat.xo;
        Axes_array[j][i*3 + 1] = mat.yx*tp1 + mat.yy*tp2 +mat.yz*tp3 + mat.yo;
        Axes_array[j][i*3 + 2] = mat.zx*tp1 + mat.zy*tp2 +mat.zz*tp3 + mat.zo;
                                      }

};  //End of if(drawaxes_ok ==1)...


}

/*****************************************************************************/
/*****************************************************************************/

void Model3D::initialiser_parseur3() {
    myParser.AddConstant ("pi", 3.14159265);
    myParserX.AddConstant("pi", 3.14159265);
    myParserY.AddConstant("pi", 3.14159265);
    myParserZ.AddConstant("pi", 3.14159265);
    myParserW.AddConstant("pi", 3.14159265);
    myParserT.AddConstant("pi", 3.14159265);
    myParserS.AddConstant("pi", 3.14159265);

    myParserX_2.AddConstant("pi", 3.14159265);
    myParserY_2.AddConstant("pi", 3.14159265);
    myParserZ_2.AddConstant("pi", 3.14159265);

    myParser_spherical.AddConstant("pi", 3.14159265);
    myParser_cylindrical.AddConstant("pi", 3.14159265);

    myParser_condition.AddConstant("pi", 3.14159265);
     }
/*****************************************************************************/
/** This function must be rewriten for more clarity..*************************/
/*****************************************************************************/

void  Model3D::parse_expression() {
    double vals[] = { 0,0,0,0,0,0}; // arbitrary values

if(there_is_condition == 1) {
  myParser_condition.AddFunction("k", f1);
  myParser_condition.Parse(condition_expression, "u,v,t,x,y,z");
                      }

if ( supershape == 1){
    myParser.Parse(sm1, "u,v,t,x,y,z");
    m1 = myParser.Eval(vals);

    myParser.Parse(sm2, "u,v,t,x,y,z");
    m2 = myParser.Eval(vals);

    myParser.Parse(sa_1, "u,v,t,x,y,z");
    a_1 = myParser.Eval(vals);

    myParser.Parse(sa_2, "u,v,t,x,y,z");
    a_2 = myParser.Eval(vals);

    myParser.Parse(sb_1, "u,v,t,x,y,z");
    b_1 = myParser.Eval(vals);

    myParser.Parse(sb_2, "u,v,t,x,y,z");
    b_2 = myParser.Eval(vals);

    myParser.Parse(sn1_1, "u,v,t,x,y,z");
    n1_1 = myParser.Eval(vals);

    myParser.Parse(sn1_2, "u,v,t,x,y,z");
    n1_2 = myParser.Eval(vals);

    myParser.Parse(sn2_1, "u,v,t,x,y,z");
    n2_1 = myParser.Eval(vals);

    myParser.Parse(sn2_2, "u,v,t,x,y,z");
    n2_2 = myParser.Eval(vals);

    myParser.Parse(sn3_1, "u,v,t,x,y,z");
    n3_1 = myParser.Eval(vals);

    myParser.Parse(sn3_2, "u,v,t,x,y,z");
    n3_2 = myParser.Eval(vals);

    myParser.Parse(inf_u, "u,v,t,x,y");
    u_inf = myParser.Eval(vals);
    myParser.Parse(sup_u, "u,v,t,x,y");
    u_sup = myParser.Eval(vals);
    dif_u = u_sup - u_inf;

    myParser.Parse(inf_v, "u,v,t,x,y");
    v_inf = myParser.Eval(vals);
    myParser.Parse(sup_v, "u,v,t,x,y");
    v_sup = myParser.Eval(vals);
    dif_v = v_sup - v_inf;

     }
else
 if(  implicitdef != 1 ) {
    if(DefineNewFct ==1){
    f1.Parse(newfct, "u,v,t,x,y");
    myParserX.AddFunction("k", f1);
    myParserY.AddFunction("k", f1);
    myParserZ.AddFunction("k", f1);

    myParserX_2.AddFunction("k", f1);
    myParserY_2.AddFunction("k", f1);
    myParserZ_2.AddFunction("k", f1);

    myParser_spherical.AddFunction("k", f1);
    myParser_cylindrical.AddFunction("k", f1);
                        }
    myParser.Parse(inf_u, "u,v,t,x,y");
    u_inf = myParser.Eval(vals);
    myParser.Parse(sup_u, "u,v,t,x,y");
    u_sup = myParser.Eval(vals);
    dif_u = u_sup - u_inf;

    myParser.Parse(inf_v, "u,v,t,x,y");
    v_inf = myParser.Eval(vals);
    myParser.Parse(sup_v, "u,v,t,x,y");
    v_sup = myParser.Eval(vals);
    dif_v = v_sup - v_inf;

 myParserX.Parse(expression_X, "u,v,t,x,y");
 myParserY.Parse(expression_Y, "u,v,t,x,y");
 myParserZ.Parse(expression_Z, "u,v,t,x,y");

 // if two system activated

 if(two_system == 1) {
    myParser.Parse(inf_u_2, "u,v,t,x,y");
    u_inf_2 = myParser.Eval(vals);
    myParser.Parse(sup_u_2, "u,v,t,x,y");
    u_sup_2 = myParser.Eval(vals);
    dif_u_2 = u_sup_2 - u_inf_2;

    myParser.Parse(inf_v_2, "u,v,t,x,y");
    v_inf_2 = myParser.Eval(vals);
    myParser.Parse(sup_v_2, "u,v,t,x,y");
    v_sup_2 = myParser.Eval(vals);
    dif_v_2 = v_sup_2 - v_inf_2;

 myParserX_2.Parse(expression_X_2, "u,v,t,x,y");
 myParserY_2.Parse(expression_Y_2, "u,v,t,x,y");
 myParserZ_2.Parse(expression_Z_2, "u,v,t,x,y");
 }

  // 6D shapes
 if (sixdimshapes == 1 ) {
    myParserW.AddFunction("k", f1);
    myParserW.Parse(expression_W, "u,v,t,x,y");

    myParserT.AddFunction("k", f1);
    myParserT.Parse(expression_T, "u,v,t,x,y");

    myParserS.AddFunction("k", f1);
    myParserS.Parse(expression_S, "u,v,t,x,y");
     }

 // 5D shapes
 if (fivedimshapes == 1 ) {
    myParserW.AddFunction("k", f1);
    myParserW.Parse(expression_W, "u,v,t,x,y");

    myParserT.AddFunction("k", f1);
    myParserT.Parse(expression_T, "u,v,t,x,y");
     }
 // 4D shapes
 else if (fourdimshapes == 1 ) {
    myParserW.AddFunction("k", f1);
    myParserW.Parse(expression_W, "u,v,t,x,y");
     }

 else if(sphericaldef == 1) // spherical equation  r^n = f(u,v,x,y,z)
    {
     // we are looking for the parity of the coefficient n
    myParser.Parse(coefficient_n, "u,v,t,x,y");
    coefficent_fct_implicite = myParser.Eval(vals);
    coefficent_fct_implicite_parity = fmod(coefficent_fct_implicite, 2);
    myParser_spherical.Parse(spherical_expression, "u,v,t,x,y,z"); // we have one more variable z
    }
 else if(cylindricaldef == 1) // spherical equation  r^n = f(u,v,x,y,z)
    {
     // we are looking for the parity of the coefficient n
    myParser.Parse(coefficient_n, "u,v,t,x,y");
    coefficent_fct_implicite = myParser.Eval(vals);
    coefficent_fct_implicite_parity = fmod(coefficent_fct_implicite, 2);
    myParser_cylindrical.Parse(cylindrical_expression, "u,v,t,x,y,z"); // we have one more variable z
    }

}


// this part is for the implicit equation...
else {

// We use the borders of the second system to delimite x and y
    myParser.Parse(inf_u, "u,v,t,x,y");
    u_inf = myParser.Eval(vals);
    myParser.Parse(sup_u, "u,v,t,x,y");
    u_sup = myParser.Eval(vals);
    dif_u = u_sup - u_inf;

    myParser.Parse(inf_v, "u,v,t,x,y");
    v_inf = myParser.Eval(vals);
    myParser.Parse(sup_v, "u,v,t,x,y");
    v_sup = myParser.Eval(vals);
    dif_v = v_sup - v_inf;

 // we are looking for the parity of the coefficient n
    myParser.Parse(coefficient_n, "u,v,t,x,y");
    coefficent_fct_implicite = myParser.Eval(vals);
    coefficent_fct_implicite_parity = fmod(coefficent_fct_implicite, 2);
 // we set the first and second equation to u and v

    myParserX.Parse("u", "u,v,t,x,y");
    myParserY.Parse("v", "u,v,t,x,y");
 // Now we construct the third equation for Implicit equation z^n = f(x,y)...
    expression_Z = expression_implicite;
    myParserZ.Parse(expression_Z, "u,v,t,x,y");

 // just for more security....
    two_system = -1;

}
}


///*****************************************************************************/
///*****************************************************************************/


void  Model3D:: SpecialMorph_2(GLfloat *NormVertexTabPt, GLuint *IndexPolyTabPt, GLuint *NbPolygnNbVertexPt,int NbStep) {
    double vals[] = {0,0,0,0,0,0};
    double vals2[] = {0,0,0,0,0,0};
    double iprime, jprime, valeur_de_fct_implicite, step_local;
    double spherical_val, cylindrical_val;
    int i, j, k, l=0, n, MorphDecalage;

parse_expression();

NbVertex = (nb_ligne)*(nb_colone);

morph_param = 0.0; // The starting point of the morph effect.
step_local = 1.0/(double)NbStep;
for(n=0; n<NbStep; n++) {

MorphDecalage = n*6*NbVertex;

// this is for the morph effect...
if(morph_param >= 0.0) {
 vals[2] = vals2[2] = morph_param ;
}
else {
 vals[2] = vals2[2] = -morph_param ;
}
morph_param += step_local;
if( morph_param == 1) morph_param = 0; /// We should not use this but...

//if( morph_param == 1) {step *=-1; morph_param += step;}
//if( morph_param  < 0) {step *=-1; morph_param += step;}
if ( supershape == 1){
double r1, r2;
  // Begin First case : n = 1, 3, 5.....
//  if(coefficent_fct_implicite_parity == 1)
    l=0;
    for(j=0; j < nb_ligne   ; j++) {
    jprime = (double)j/(double)(nb_ligne -1 );
    jprime = jprime * dif_u  + u_inf;
     for (i=0; i < nb_colone   ; i++)
       {
   iprime = (double)i/(double)(nb_colone -1 );
   iprime = iprime * dif_v + v_inf;
   r1 = pow(
        pow(fabs(cos(m1*jprime/4)/a_1), n2_1) +
        pow(fabs(sin(m1*jprime/4)/b_1), n3_1)
        , -1/n1_1);


   r2 = pow(
        pow(fabs(cos(m2*iprime/4)/a_2), n2_2) +
        pow(fabs(sin(m2*iprime/4)/b_2), n3_2)
        , -1/n1_2);


   NormVertexTab[l+3+MorphDecalage] = r1 * cos(jprime) * r2 * cos(iprime);
   NormVertexTab[l+4+MorphDecalage] = r1 * sin(jprime) * r2 * cos(iprime);
   NormVertexTab[l+5+MorphDecalage] = r2 * sin(iprime);
   l+=6;
  }       }
  // End of first case : n = 1, 3, 5.....
}
 else if (cylindricaldef == 1){
//  if(coefficent_fct_implicite_parity == 1)
    l =0;
    for(j=0; j < nb_ligne   ; j++) {
    jprime = (double)j/(double)(nb_ligne -1 ) ;
    jprime = jprime * dif_u  + u_inf;
  for (i=0; i < nb_colone   ; i++)
      {
   iprime = (double)i/(double)(nb_colone-1 ) ;
   iprime = iprime * dif_v + v_inf;

   vals[0]=jprime; vals[1]=iprime;   // u = jprime ; v = iprime;

   vals[3] = cos(jprime) ; // because  X = cos(u)
   vals[4] = sin(jprime);  // because  Y = sin(u)
   vals[5] = iprime  ;     // because  Z = v
   cylindrical_val = myParser_cylindrical.Eval(vals) ;

   (cylindrical_val  >= 0 ) ?
   cylindrical_val  =  pow(cylindrical_val, 1/coefficent_fct_implicite) :
   cylindrical_val  = -pow(-cylindrical_val, 1/coefficent_fct_implicite);

   NormVertexTab[l+3+MorphDecalage] = vals[3] * cylindrical_val;
   NormVertexTab[l+4+MorphDecalage] = vals[4] * cylindrical_val;
   NormVertexTab[l+5+MorphDecalage] = vals[5] ;
   l+=6;
  }      }
}
else if (sphericaldef == 1){
//  if(coefficent_fct_implicite_parity == 1)
    l=0;
    for(j=0; j < nb_ligne   ; j++) {
    jprime = (double)j/(double)(nb_ligne -1 ) ;
    jprime = jprime * dif_u  + u_inf;
     for (i=0; i < nb_colone   ; i++)
    {
   iprime = (double)i/(double)(nb_colone-1 ) ;
   iprime = iprime * dif_v + v_inf;

   vals[0]=jprime; vals[1]=iprime;   // u = jprime ; v = iprime;

   vals[3] = cos(iprime)*cos(jprime) ; // because  X = cos(v)*cos(u)
   vals[4] = sin(iprime)*cos(jprime);  // because  Y = sin(v)*cos(u)
   vals[5] = sin(jprime)  ;            // because  Z = sin(u)
   spherical_val = myParser_spherical.Eval(vals) ;

   (spherical_val  >= 0 ) ?
   spherical_val  =  pow(spherical_val, 1/coefficent_fct_implicite) :
   spherical_val  = -pow(-spherical_val, 1/coefficent_fct_implicite);

   NormVertexTab[l+3+MorphDecalage] = vals[3] * spherical_val;
   NormVertexTab[l+4+MorphDecalage] = vals[4] * spherical_val;
   NormVertexTab[l+5+MorphDecalage] = vals[5] * spherical_val;
   l+=6;
  }
}
}
else
if(fourdimshapes == 1){
  l=0;
  for(j=0; j < nb_ligne   ; j++) {
    jprime = (double)j/(double)(nb_ligne -1 ) ;
    jprime = jprime * dif_u  + u_inf;
  for (i=0; i < nb_colone   ; i++)
  {
   iprime = (double)i/(double)(nb_colone-1 ) ;
   iprime = iprime * dif_v + v_inf;

   vals[0]=jprime; vals[1]=iprime;

   vals[3] = NormVertexTab[l+3+MorphDecalage] = myParserX.Eval(vals);
   vals[4] = NormVertexTab[l+4+MorphDecalage] = myParserY.Eval(vals);
   NormVertexTab[l+5+MorphDecalage] = myParserZ.Eval(vals);
   l+=6;
  }     }
                  }
else
if(two_system == -1) {
 if(  implicitdef != 1 )    {
 // in this case we have a simple equation system...
  l=0;
  for(j=0; j < nb_ligne   ; j++) {
    jprime = (double)j/(double)(nb_ligne -1 ) ;
    jprime = jprime * dif_u  + u_inf;

  for (i=0; i < nb_colone   ; i++)
  {
   iprime = (double)i/(double)(nb_colone-1 ) ;
   iprime = iprime * dif_v + v_inf;
   vals[0]=jprime; vals[1]=iprime;

   vals[3] = NormVertexTab[l+3+MorphDecalage] = myParserX.Eval(vals);
   vals[4] = NormVertexTab[l+4+MorphDecalage] = myParserY.Eval(vals);
             NormVertexTab[l+5+MorphDecalage] = myParserZ.Eval(vals);
   l+=6;
  }
   } // End of if(there_is_condition == -1)
} // End  if(  implicitdef != 1 )
// here we are going to work with implicit equation...
 else
   {
  l=0;
  for(j=0; j < nb_ligne   ; j++) {
    jprime = (double)j/(double)(nb_ligne -1 ) ;
    jprime = jprime * dif_u  + u_inf;
  for (i=0; i < nb_colone   ; i++)
   {
   iprime = (double)i/(double)(nb_colone-1 ) ;
   iprime = iprime * dif_v + v_inf;
   vals[0]=jprime; vals[1]=iprime;
   vals[3] = NormVertexTab[l+3+MorphDecalage] = jprime; // because  X = u
   vals[4] = NormVertexTab[l+4+MorphDecalage] = iprime; // because  Y = v

   valeur_de_fct_implicite = myParserZ.Eval(vals) ;
   (valeur_de_fct_implicite  >= 0 ) ?
   NormVertexTab[l+5+MorphDecalage] = pow(valeur_de_fct_implicite, 1/coefficent_fct_implicite) :
   NormVertexTab[l+5+MorphDecalage] = -pow(-valeur_de_fct_implicite, 1/coefficent_fct_implicite);
   l+=6;
  }
}
}
}/// End if(two_system == -1)...

/// Last Case : Two parametric Systems :
///================ Begin treatement of two systemes ============
 else {
 
 
  l=0;
  for(j=0; j < nb_ligne   ; j++) {
    jprime = (double)j/(double)(nb_ligne -1 ) ;
    jprime = jprime * dif_u  + u_inf;

  for (i=0; i < nb_colone   ; i++)
  {
   iprime = (double)i/(double)(nb_colone-1 ) ;
   iprime = iprime * dif_v + v_inf;
   vals[0]=jprime; vals[1]=iprime;

   vals[3] = NormVertexTab[l+3+MorphDecalage] = myParserX.Eval(vals);
   vals[4] = NormVertexTab[l+4+MorphDecalage] = myParserY.Eval(vals);
             NormVertexTab[l+5+MorphDecalage] = myParserZ.Eval(vals);
   l+=6;
  }
   }
 
 /*
moitie_colone = nb_colone/2;
   l=0;
// We begin with half of the grid...be careful...
  for(j=0; j < nb_ligne   ; j++) {
    jprime = (double)j/(double)(nb_ligne -1 ) ;
    jprime = jprime * dif_u  + u_inf;
  for (i=0; i < moitie_colone   ; i++)
{
   iprime = (double)i/(double)(moitie_colone -1 ) ;
   iprime = iprime * dif_v + v_inf;
   vals[0]=jprime; vals[1]=iprime;
   vals[3] = NormVertexTab[l+3+MorphDecalage] = myParserX.Eval(vals);
   vals[4] = NormVertexTab[l+4+MorphDecalage] = myParserY.Eval(vals);
   vals[5] = NormVertexTab[l+5+MorphDecalage] = myParserZ.Eval(vals);
   l+=6;
 }
}
/// we finish the remaining of the grid...
  for(j=0; j < nb_ligne; j++) {
    jprime = (double)j/(double)(nb_ligne -1);
    jprime = jprime * dif_u_2  + u_inf_2;
  for (i=moitie_colone; i < nb_colone; i++){
   iprime = (double)(i - moitie_colone)/(double)(nb_colone -1 -moitie_colone);
   iprime = iprime * dif_v_2 + v_inf_2;

   vals2[0]=jprime; vals2[1]=iprime;

   vals2[3] = NormVertexTab[l+3+MorphDecalage] = myParserX_2.Eval(vals2);
   vals2[4] = NormVertexTab[l+4+MorphDecalage] = myParserY_2.Eval(vals2);
   vals2[5] = NormVertexTab[l+5+MorphDecalage] = myParserZ_2.Eval(vals2);
   l+=6;
  }
}
*/
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++///
///+++++++++ Now We have to calculate Normals ++++++++///
///+++++++++++++++++++++++++++++++++++++++++++++++++++///
int deplacement = 6*nb_colone;

  for (i=0; i < nb_ligne -1  ; i++)
   for (j=0; j < nb_colone -1  ; j++) {

caa = NormVertexTab[(i+1)*deplacement+j*6+4+MorphDecalage] - NormVertexTab[i*deplacement +j*6+4+MorphDecalage];
bab = NormVertexTab[i*deplacement+(j+1)*6+5+MorphDecalage] - NormVertexTab[i*deplacement +j*6+5+MorphDecalage];
cab = NormVertexTab[(i+1)*deplacement+j*6+5+MorphDecalage] - NormVertexTab[i*deplacement +j*6+5+MorphDecalage];
baa = NormVertexTab[i*deplacement+(j+1)*6+4+MorphDecalage] - NormVertexTab[i*deplacement +j*6+4+MorphDecalage];
ba  = NormVertexTab[i*deplacement+(j+1)*6+3+MorphDecalage] - NormVertexTab[i*deplacement +j*6+3+MorphDecalage];
ca  = NormVertexTab[(i+1)*deplacement+j*6+3+MorphDecalage] - NormVertexTab[i*deplacement +j*6+3+MorphDecalage];

NormVertexTab[i*deplacement +j*6   +MorphDecalage] = caa*bab - cab*baa;
NormVertexTab[i*deplacement +j*6 +1+MorphDecalage] = cab*ba  - ca*bab;
NormVertexTab[i*deplacement +j*6 +2+MorphDecalage] = ca*baa  - caa*ba;

double b4 = (double)sqrt(
       (NormVertexTab[i*deplacement +j*6  +MorphDecalage]*NormVertexTab[i*deplacement +j*6  +MorphDecalage+MorphDecalage]) +
       (NormVertexTab[i*deplacement +j*6+1+MorphDecalage]*NormVertexTab[i*deplacement +j*6+1+MorphDecalage+MorphDecalage]) +
       (NormVertexTab[i*deplacement +j*6+2+MorphDecalage]*NormVertexTab[i*deplacement +j*6+2+MorphDecalage+MorphDecalage]));

// This must be changed...
if(b4 > 0.00000001) {
 NormVertexTab[i*deplacement +j*6  +MorphDecalage]/=b4;
 NormVertexTab[i*deplacement +j*6+1+MorphDecalage]/=b4;
 NormVertexTab[i*deplacement +j*6+2+MorphDecalage]/=b4;
}
}

i = nb_ligne -1;
 for (j=0; j < nb_colone -1   ; j++) {
 NormVertexTab[i*deplacement +j*6  +MorphDecalage] = NormVertexTab[(i-1)*deplacement +j*6  +MorphDecalage];
 NormVertexTab[i*deplacement +j*6+1+MorphDecalage] = NormVertexTab[(i-1)*deplacement +j*6+1+MorphDecalage];
 NormVertexTab[i*deplacement +j*6+2+MorphDecalage] = NormVertexTab[(i-1)*deplacement +j*6+2+MorphDecalage];
 }

j =nb_colone -1;
 for (i=0; i < nb_ligne -1  ; i++) {
 NormVertexTab[i*deplacement +j*6  +MorphDecalage] = NormVertexTab[i*deplacement +(j-1)*6  +MorphDecalage];
 NormVertexTab[i*deplacement +j*6+1+MorphDecalage] = NormVertexTab[i*deplacement +(j-1)*6+1+MorphDecalage];
 NormVertexTab[i*deplacement +j*6+2+MorphDecalage] = NormVertexTab[i*deplacement +(j-1)*6+2+MorphDecalage];
 }

 i = nb_ligne -1; j =nb_colone -1;
 NormVertexTab[i*deplacement +j*6  +MorphDecalage]  = NormVertexTab[(i-1)*deplacement +(j-1)*6  +MorphDecalage];
 NormVertexTab[i*deplacement +j*6+1+MorphDecalage]  = NormVertexTab[(i-1)*deplacement +(j-1)*6+1+MorphDecalage];
 NormVertexTab[i*deplacement +j*6+2+MorphDecalage]  = NormVertexTab[(i-1)*deplacement +(j-1)*6+2+MorphDecalage];

} /// End of for(n=0; n<...)




///++++++++++++++++++++++++++++++++++++++++++++++++++++///
///++++++++++++++++++++++++++++++++++++++++++++++++++++///

// calcul des minimas et des maximas des coordonnees: X,Y et Z

MINX =999999999;//Tre2[0][0];
MINY =999999999;//Tre2[1][0];
MINZ =999999999;//Tre2[2][0];

MAXX =-999999999;//Tre2[0][0];
MAXY =-999999999;//Tre2[1][0];
MAXZ =-999999999;//Tre2[2][0];

 for (i=0; i < NbStep*NbVertex   ; i++) {
     if(MINX > NormVertexTab[i*6 + 3] ) MINX = NormVertexTab[i*6 + 3];

     if(MINY > NormVertexTab[i*6 + 4] ) MINY = NormVertexTab[i*6 + 4];

     if(MINZ > NormVertexTab[i*6 + 5] ) MINZ = NormVertexTab[i*6 + 5];

     if(MAXX < NormVertexTab[i*6 + 3] ) MAXX = NormVertexTab[i*6 + 3];

     if(MAXY < NormVertexTab[i*6 + 4] ) MAXY = NormVertexTab[i*6 + 4];

     if(MAXZ < NormVertexTab[i*6 + 5] ) MAXZ = NormVertexTab[i*6 + 5];
    }
// On recherche la plus grande "difference" de distance entre les points
// pour reduire la figure a un cube d'une longueur de 1.
// On utilisera apres cette figure pour l'agrandir et bien la placer dans
// la fenetre de vue:

  DIFX = MAXX - MINX ;
  DIFY = MAXY - MINY ;
  DIFZ = MAXZ - MINZ ;

// Recherche du maximum :
  DIFMAXIMUM = DIFX;

  if (DIFY > DIFMAXIMUM) {DIFMAXIMUM = DIFY;};
  if (DIFZ > DIFMAXIMUM) {DIFMAXIMUM = DIFZ;};

/// On va inclure cet objet dans un cube de langueur maximum
/// egale a "hauteur_fenetre"

double decalage_xo = -(MINX +MAXX)/2 ;
double decalage_yo = -(MINY +MAXY)/2 ;
double decalage_zo = -(MINZ +MAXZ)/2 ;
double rapport = hauteur_fenetre/DIFMAXIMUM;

 for (i=0; i < NbStep*NbVertex   ; i++) {
  NormVertexTab[i*6 + 3] = rapport * (NormVertexTab[i*6 + 3] + decalage_xo) ;
  NormVertexTab[i*6 + 4] = rapport * (NormVertexTab[i*6 + 4] + decalage_yo) ;
  NormVertexTab[i*6 + 5] = rapport * (NormVertexTab[i*6 + 5] + decalage_zo) ;
    }

MINX = rapport * (MINX + decalage_xo);
MINY = rapport * (MINY + decalage_yo);
MINZ = rapport * (MINZ + decalage_zo);

MAXX = rapport * (MAXX + decalage_xo);
MAXY = rapport * (MAXY + decalage_yo);
MAXZ = rapport * (MAXZ + decalage_zo);

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++///
///+++++++++ Now we save all theses Arrays for further use +++++///
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++///

/// 1) Save Vertex :
memcpy(NormVertexTabPt, NormVertexTab, NbStep*6*NbVertex*sizeof(GLfloat));


/// 2) Save Index Polygones:

   k=0;
   for (i=0; i< nb_ligne - coupure_ligne -1; i++)
      for (j=0; j< nb_colone - coupure_col -1; j++) {
     IndexPolyTab[k  ] = i*nb_colone + j;
     IndexPolyTab[k+1] = (i+1)*nb_colone + j;
     IndexPolyTab[k+2] = (i+1)*nb_colone + (j+1);
     IndexPolyTab[k+3] = i*nb_colone + (j+1);
     k+=4;
    }
NbPolygn = 4*(nb_ligne  - coupure_ligne -1)*(nb_colone - coupure_col -1);

    // Generate the Indices Tables for all Morph Frames :
  for(j =1; j < NbStep; j++)
    for(i =0; i < (int)NbPolygn; i++){
    IndexPolyTab[j*NbPolygn + i] = IndexPolyTab[i] + j*nb_ligne*nb_colone;
    }
memcpy(IndexPolyTabPt, IndexPolyTab, NbStep*NbPolygn*sizeof(GLuint));


/// 3) Nb Poly & Vertex :
 for(i =0; i < NbStep; i++) {
   NbPolygnNbVertex[2*i  ] = NbPolygn;
   NbPolygnNbVertex[2*i+1] = i*NbPolygn;//nb_ligne*nb_colone;
   };
memcpy(NbPolygnNbVertexPt, NbPolygnNbVertex, 2*NbStep*sizeof(GLuint));

 }


///*****************************************************************************/
///*****************************************************************************/
void  Model3D:: SpecialAnim_2(GLfloat *, GLuint *) {
 }

///*****************************************************************************/
///*****************************************************************************/
void  Model3D::calcul_objet3() {
    double vals[] = {0,0,0,0,0,0};
    double vals2[] = {0,0,0,0,0,0};
    double iprime, jprime, valeur_de_fct_implicite;
    double spherical_val, cylindrical_val, U_step, V_step;

// we initialise the hidden_points array so all points are ready to be drawn
   for(int j=0; j < nb_ligne   ; j++)
    for (int i=0; i < nb_colone  ; i++)
         hidden_points[j][i]    =  1;
         there_is_hidden_points = -1;
// this is for the morph effect...
if(morph_param >= 0.0) {
 vals[2] = vals2[2] = morph_param ;
}
else {
 vals[2] = vals2[2] = -morph_param ;
}
morph_param -= step ;
if( morph_param <= -1) morph_param = 1;

if ( supershape == 1){
double r1, r2;
  // Begin First case : n = 1, 3, 5.....
//  if(coefficent_fct_implicite_parity == 1)
    for(int j=0; j < nb_ligne   ; j++) {
    jprime = (double)j/(double)(nb_ligne -1 ) ;
    jprime = jprime * dif_u  + u_inf;
     for (int i=0; i < nb_colone   ; i++)
       {
   iprime = (double)i/(double)(nb_colone-1 ) ;
   iprime = iprime * dif_v + v_inf;
   r1 = pow(
        pow(fabs(cos(m1*jprime/4)/a_1), n2_1) +
        pow(fabs(sin(m1*jprime/4)/b_1), n3_1)
        , -1/n1_1);

   r2 = pow(
        pow(fabs(cos(m2*iprime/4)/a_2), n2_2) +
        pow(fabs(sin(m2*iprime/4)/b_2), n3_2)
        , -1/n1_2);

   Tre2[j*3    ][i]  = r1 * cos(jprime) * r2 * cos(iprime);
   Tre2[j*3 + 1][i]  = r1 * sin(jprime) * r2 * cos(iprime);
   Tre2[j*3 + 2][i]  = r2 * sin(iprime);
  }       }

  // End of first case : n = 1, 3, 5.....
}

 else if (cylindricaldef == 1){

  // Begin First case : n = 1, 3, 5.....
//  if(coefficent_fct_implicite_parity == 1)
    for(int j=0; j < nb_ligne   ; j++) {
    jprime = (double)j/(double)(nb_ligne -1 ) ;
    jprime = jprime * dif_u  + u_inf;
  for (int i=0; i < nb_colone   ; i++)
      {
   iprime = (double)i/(double)(nb_colone-1 ) ;
   iprime = iprime * dif_v + v_inf;

   vals[0]=jprime; vals[1]=iprime;   // u = jprime ; v = iprime;

   vals[3] = cos(jprime) ; // because  X = cos(u)
   vals[4] = sin(jprime);  // because  Y = sin(u)
   vals[5] = iprime  ;     // because  Z = v
   cylindrical_val = myParser_cylindrical.Eval(vals) ;

   (cylindrical_val  >= 0 ) ?
   cylindrical_val  =  pow(cylindrical_val, 1/coefficent_fct_implicite) :
   cylindrical_val  = -pow(-cylindrical_val, 1/coefficent_fct_implicite);

   Tre2[j*3    ][i]  = vals[3] * cylindrical_val;
   Tre2[j*3 + 1][i]  = vals[4] * cylindrical_val;
   Tre2[j*3 + 2][i]  = vals[5] ;

  }      }

  // End of first case : n = 1, 3, 5.....
}
else if (sphericaldef == 1){

  // Begin First case : n = 1, 3, 5.....
//  if(coefficent_fct_implicite_parity == 1)
    for(int j=0; j < nb_ligne   ; j++) {
    jprime = (double)j/(double)(nb_ligne -1 ) ;
    jprime = jprime * dif_u  + u_inf;
     for (int i=0; i < nb_colone   ; i++)
    {
   iprime = (double)i/(double)(nb_colone-1 ) ;
   iprime = iprime * dif_v + v_inf;

   vals[0]=jprime; vals[1]=iprime;   // u = jprime ; v = iprime;


//double supershape(double n1, double n2, double n3, int m, double a, double b, double teta)
   vals[3] = cos(iprime)*cos(jprime) ; // because  X = cos(v)*cos(u)
   vals[4] = sin(iprime)*cos(jprime);  // because  Y = sin(v)*cos(u)
   vals[5] = sin(jprime)  ;            // because  Z = sin(u)
   spherical_val = myParser_spherical.Eval(vals) ;

   (spherical_val  >= 0 ) ?
   spherical_val  =  pow(spherical_val, 1/coefficent_fct_implicite) :
   spherical_val  = -pow(-spherical_val, 1/coefficent_fct_implicite);

   Tre2[j*3    ][i]  = vals[3] * spherical_val;
   Tre2[j*3 + 1][i]  = vals[4] * spherical_val;
   Tre2[j*3 + 2][i]  = vals[5] * spherical_val;


  }   }

  // End of first case : n = 1, 3, 5.....
}
else

if(sixdimshapes == 1){

  for(int j=0; j < nb_ligne   ; j++) {
    jprime = (double)j/(double)(nb_ligne -1 ) ;
    jprime = jprime * dif_u  + u_inf;
 for (int i=0; i < nb_colone   ; i++)
      {
   iprime = (double)i/(double)(nb_colone-1 ) ;
   iprime = iprime * dif_v + v_inf;

   vals[0]=jprime; vals[1]=iprime;

   shape6D[j*6    ][i]  = vals[3] = myParserX.Eval(vals);
   shape6D[j*6 + 1][i]  = vals[4] = myParserY.Eval(vals);
   shape6D[j*6 + 2][i]            = myParserZ.Eval(vals);
   shape6D[j*6 + 3][i]            = myParserW.Eval(vals);
   shape6D[j*6 + 4][i]            = myParserT.Eval(vals);
   shape6D[j*6 + 5][i]            = myParserS.Eval(vals);
  }    }

   boite_englobante6D();
   project_6D_to_5D();
   project_5D_to_4D();
   project_4D_to_3D();

                  }
else

if(fivedimshapes == 1){

  for(int j=0; j < nb_ligne   ; j++) {
    jprime = (double)j/(double)(nb_ligne -1 ) ;
    jprime = jprime * dif_u  + u_inf;
  for (int i=0; i < nb_colone   ; i++)
   {
   iprime = (double)i/(double)(nb_colone-1 ) ;
   iprime = iprime * dif_v + v_inf;

   vals[0]=jprime; vals[1]=iprime;

   shape5D[j*5    ][i]  = vals[3] = myParserX.Eval(vals);
   shape5D[j*5 + 1][i]  = vals[4] = myParserY.Eval(vals);
   shape5D[j*5 + 2][i]            = myParserZ.Eval(vals);
   shape5D[j*5 + 3][i]            = myParserW.Eval(vals);
   shape5D[j*5 + 4][i]            = myParserT.Eval(vals);
  }     }

   boite_englobante5D();
   project_5D_to_4D();
   project_4D_to_3D();
                  }

else

if(fourdimshapes == 1){
  for(int j=0; j < nb_ligne   ; j++) {
    jprime = (double)j/(double)(nb_ligne -1 ) ;
    jprime = jprime * dif_u  + u_inf;
  for (int i=0; i < nb_colone   ; i++)
  {
   iprime = (double)i/(double)(nb_colone-1 ) ;
   iprime = iprime * dif_v + v_inf;

   vals[0]=jprime; vals[1]=iprime;

   vals[3] = shape4D[j*4    ][i]  = myParserX.Eval(vals);
   vals[4] = shape4D[j*4 + 1][i]  = myParserY.Eval(vals);
   shape4D[j*4 + 2][i]  = myParserZ.Eval(vals);
   shape4D[j*4 + 3][i]  = myParserW.Eval(vals);
  }     }

   boite_englobante4D();
   project_4D_to_3D();
                  }

else


if(two_system == -1)     // Just one system...cooooooooooool
 if(  implicitdef != 1 )    {
 // in this case we have a simple equation system...
  if(there_is_condition == -1) // No condition to verify
  for(int j=0; j < nb_ligne   ; j++) {
    jprime = (double)j/(double)(nb_ligne -1 ) ;
    jprime = jprime * dif_u  + u_inf;

  for (int i=0; i < nb_colone   ; i++)
  {
   iprime = (double)i/(double)(nb_colone-1 ) ;
   iprime = iprime * dif_v + v_inf;
   vals[0]=jprime; vals[1]=iprime;

   vals[3] = Tre2[j*3    ][i]  = myParserX.Eval(vals);
   vals[4] = Tre2[j*3 + 1][i]  = myParserY.Eval(vals);
   Tre2[j*3 + 2][i]  = myParserZ.Eval(vals);
  }
   } // End of if(there_is_condition == -1)

  // Here There is a condition to verify
  else {
       /// Calculate the grid
   for(int j=0; j < nb_ligne   ; j++) {
    jprime = (double)j/(double)(nb_ligne -1 ) ;
    jprime = jprime * dif_u  + u_inf;
 for (int i=0; i < nb_colone   ; i++) {
   iprime = (double)i/(double)(nb_colone-1 ) ;
   iprime = iprime * dif_v + v_inf;

   vals[0]=jprime; vals[1]=iprime;

   vals[3] = Tre2[j*3    ][i]  = myParserX.Eval(vals);
   vals[4] = Tre2[j*3 + 1][i]  = myParserY.Eval(vals);
   vals[5] = Tre2[j*3 + 2][i]  = myParserZ.Eval(vals);
       if( myParser_condition.Eval(vals) == 0) {
          hidden_points[j][i] = 0;
          there_is_hidden_points = 1; //
                                                }
                                            }
                                        }
        /// We will try to resove HP

  } // End  There is a condition to verify

} // End  if(  implicitdef != 1 )
// here we are going to work with implicit equation...

 else
   {
  // Begin First case : n = 1, 3, 5...
  if(coefficent_fct_implicite_parity == 1)
    for(int j=0; j < nb_ligne   ; j++) {
    jprime = (double)j/(double)(nb_ligne -1 ) ;
    jprime = jprime * dif_u  + u_inf;

  for (int i=0; i < nb_colone   ; i++)
   {
   iprime = (double)i/(double)(nb_colone-1 ) ;
   iprime = iprime * dif_v + v_inf;
   vals[0]=jprime; vals[1]=iprime;
   vals[3] = Tre2[j*3    ][i]  = jprime; // because  X = u
   vals[4] = Tre2[j*3 + 1][i]  = iprime; // because  Y = v
   //Tre2[j*3 + 2][i]  = pow(myParserZ.Eval(vals), 1/coefficent_fct_implicite);

   valeur_de_fct_implicite = myParserZ.Eval(vals) ;
   (valeur_de_fct_implicite  >= 0 ) ?
   Tre2[j*3 + 2][i]  = pow(valeur_de_fct_implicite, 1/coefficent_fct_implicite) :
   Tre2[j*3 + 2][i]  = -pow(-valeur_de_fct_implicite, 1/coefficent_fct_implicite);

  }    }

  // End of first case : n = 1, 3, 5...

  // Begin Second case : n = 2, 4, 6.....

 else {
// We begin with half of the grid...be careful...
  for(int j=0; j < nb_ligne ; j++) {
    jprime = (double)j/(double)(nb_ligne -1 ) ;
    jprime = jprime * dif_u  + u_inf;

  for (int i=0; i < nb_colone   ; i++)
{
   iprime = (double)i/(double)(nb_colone -1 ) ;
   iprime = iprime * dif_v + v_inf;
   vals[0]= vals[3] = jprime; vals[1] = vals[4] = iprime;

   Tre2[j*3    ][i]  =  jprime;
   Tre2[j*3 + 1][i]  =  iprime;
   valeur_de_fct_implicite = myParserZ.Eval(vals) ;

   if (valeur_de_fct_implicite  >= 0 )  Tre2[j*3 + 2][i] =  pow(valeur_de_fct_implicite, 1/coefficent_fct_implicite);


   else  {
   hidden_points[j][i]  = 0;
   there_is_hidden_points = 1; // we give the signal to take care of the fact that we have some HP
   }
 }
}


//we tray to fix some points of the grid

  for(int j=0; j < nb_ligne -1   ; j++)
    for (int i=0; i < nb_colone -1  ; i++)
         {
      if((hidden_points[j  ][i  ] +
          hidden_points[j+1][i  ] +
          hidden_points[j+1][i+1] +
          hidden_points[j  ][i+1]) >=3)
         {
   if(hidden_points[j][i] == 0)
       Tre2[j*3 + 2][i] = (Tre2[(j+1)*3 + 2][i] + Tre2[j*3 + 2][i+1])/2;

   else if(hidden_points[j+1][i] == 0)
       Tre2[(j+1)*3 + 2][i] = (Tre2[(j+1)*3 + 2][i+1] + Tre2[j*3 + 2][i])/2;

   else if(hidden_points[j+1][i+1] == 0)
       Tre2[(j+1)*3 + 2][i+1] = (Tre2[(j+1)*3 + 2][i] + Tre2[j*3 + 2][i+1])/2;

   else if(hidden_points[j][i+1] == 0)
       Tre2[j*3 + 2][i+1] = (Tre2[j*3 + 2][i] + Tre2[(j+1)*3 + 2][i+1])/2;
                  }
          }
/*
// The new way to calculate the new values to replace HP
if(there_is_hidden_points == 1){

 U_step = (double)dif_u/(double)( (nb_colone-1) * precision) ;
 V_step = (double)dif_v/(double)( (nb_colone-1) * precision) ;

  for(int j=0; j < nb_ligne -1   ; j++)
    for (int i=0; i < nb_colone -1  ; i++)
      if((hidden_points[j][i]     +
          hidden_points[j+1][i]   +
          hidden_points[j+1][i+1] +
          hidden_points[j][i+1])    >=3)
          {
   // DL = Down-Left
   if(hidden_points[j][i] == 0)
          for(int k=1; k < 11   ; k++)  {
   DL2[j*3    ][i] = vals[0] = vals[3] = (Tre2[j*3    ][i] + (double)k*(double)U_step);
   DL2[j*3 + 1][i] = vals[1] = vals[4] = (Tre2[j*3 + 1][i] + (double)k*(double)V_step);
   valeur_de_fct_implicite = myParserZ.Eval(vals) ;
   if(valeur_de_fct_implicite >=0) {
   DL2[j*3 + 2][i] =  pow(valeur_de_fct_implicite, 1/coefficent_fct_implicite);
   k = 10;
                                   }
                          }
   // HL = Height-Left
   else if(hidden_points[j+1][i] == 0)
          for(int k=1; k < 11   ; k++)   {
   HL2[(j+1)*3    ][i] = vals[0] = vals[3] = (Tre2[(j+1)*3    ][i] - (double)k*(double)U_step);
   HL2[(j+1)*3 + 1][i] = vals[1] = vals[4] = (Tre2[(j+1)*3 + 1][i] + (double)k*(double)V_step);
   valeur_de_fct_implicite = myParserZ.Eval(vals) ;
   if(valeur_de_fct_implicite >=0) {
   HL2[(j+1)*3 + 2][i] =  pow(valeur_de_fct_implicite, 1/coefficent_fct_implicite);
   k = 10;
                                   }
                               }
   // HR = Height-Right
   else if(hidden_points[j+1][i+1] == 0)
          for(int k=1; k < 11   ; k++)   {
   HR2[(j+1)*3    ][i+1] = vals[0] = vals[3] = (Tre2[(j+1)*3    ][i+1] - (double)k*(double)U_step);
   HR2[(j+1)*3 + 1][i+1] = vals[1] = vals[4] = (Tre2[(j+1)*3 + 1][i+1] - (double)k*(double)V_step);
   valeur_de_fct_implicite = myParserZ.Eval(vals) ;
   if(valeur_de_fct_implicite >=0) {
   HR2[(j+1)*3 + 2][i+1] =  pow(valeur_de_fct_implicite, 1/coefficent_fct_implicite);
   k = 10;
                                   }
                               }
   // DR = Down-Right
   else if(hidden_points[j][i+1] == 0)
          for(int k=1; k < 11   ; k++)   {
   DR2[j*3    ][i+1] = vals[0] = vals[3] = (Tre2[j*3    ][i+1] + (double)k*(double)U_step);
   DR2[j*3 + 1][i+1] = vals[1] = vals[4] = (Tre2[j*3 + 1][i+1] - (double)k*(double)V_step);
   valeur_de_fct_implicite = myParserZ.Eval(vals) ;
   if(valeur_de_fct_implicite >=0) {
   DR2[j*3 + 2][i+1] =  pow(valeur_de_fct_implicite, 1/coefficent_fct_implicite);
   k = 10;
                                   }
                                }

                  }   // End of   if((hidden_points[j][i]+...)
}; // End of if(there_is_hidden_points == 1)
*/


   }  // End of Second case : n = 2, 4, 6...

   } // end of implicit equation...

//================ Begin treatement of two systemes ============

 else {

moitie_colone = nb_colone/2;

// We begin with half of the grid...be careful...
  for(int j=0; j < nb_ligne   ; j++) {
    jprime = (double)j/(double)(nb_ligne -1 ) ;
    jprime = jprime * dif_u  + u_inf;

  for (int i=0; i < moitie_colone   ; i++)
{
   iprime = (double)i/(double)(moitie_colone -1 ) ;
   iprime = iprime * dif_v + v_inf;

   vals[0]=jprime; vals[1]=iprime;

   vals[3] = Tre2[j*3    ][i]  = myParserX.Eval(vals);
   vals[4] = Tre2[j*3 + 1][i]  = myParserY.Eval(vals);
   vals[5] = Tre2[j*3 + 2][i]  = myParserZ.Eval(vals);
   /*
          if( myParser_condition.Eval(vals) == 0) {
          hidden_points[j][i] = 0;
          there_is_hidden_points = 1; //
                                                }
   */
 }
                                       }

// we finish the remaining of the grid...
  for(int j=0; j < nb_ligne   ; j++) {
    jprime = (double)j/(double)(nb_ligne -1 ) ;
    jprime = jprime * dif_u_2  + u_inf_2;

  for (int i=moitie_colone-1; i < nb_colone   ; i++)
      {
   iprime = (double)(i - moitie_colone+1)/(double)(nb_colone - moitie_colone ) ;
   iprime = iprime * dif_v_2 + v_inf_2;

   vals2[0]=jprime; vals2[1]=iprime;

   vals2[3] = Tre2[j*3    ][i]  = myParserX_2.Eval(vals2);
   vals2[4] = Tre2[j*3 + 1][i]  = myParserY_2.Eval(vals2);
   vals2[5] = Tre2[j*3 + 2][i]  = myParserZ_2.Eval(vals2);
   /*
          if( myParser_condition.Eval(vals2) == 0) {
          hidden_points[j][i] = 0;
          there_is_hidden_points = 1; //
                                                }
   */
  }
                                       }

}

/// In This code we attempt resolve some missing Points
// DB=Defined Border, NDB=Non defined Border, MP = Middle Point

double DB_X, DB_Y,
       NDB_X, NDB_Y,
       MP_X, MP_Y;
int    precision_step, i, j;


if(there_is_condition == 1 && implicitdef != 1) {

 U_step =  dif_u/(double)(nb_ligne  -1);
 V_step =  dif_v/(double)(nb_colone -1);

// In this case, we have just one missing point

  for(j=0; j < nb_ligne -1   ; j++)
    for (i=0; i < nb_colone -1  ; i++)

      if((hidden_points[j  ][i  ]  +
          hidden_points[j+1][i  ]  +
          hidden_points[j+1][i+1]  +
          hidden_points[j  ][i+1]) >=3)
 {
///============= First case : DL = Down-Left=====================
   if(hidden_points[j][i] == 0) {
   // initialisation
   DB_X  =  ((double)(j+1)) * U_step + u_inf;
   DB_Y  =  ((double)(i+1)) * V_step + v_inf;
   //DB_X  =  ((double)(j+1)) * U_step + u_inf;
   //DB_Y  =  ((double)(i)) * V_step + v_inf;

   NDB_X =  ((double)(j)) * U_step + u_inf;
   NDB_Y =  ((double)(i)) * V_step + v_inf;

   DL2[j*3    ][i] = Tre2[(j+1)*3    ][i];
   DL2[j*3 + 1][i] = Tre2[(j+1)*3 + 1][i];
   DL2[j*3 + 2][i] = Tre2[(j+1)*3 + 2][i];

   precision_step = 0; // Approximation by 2^5
   while ( precision_step < 5){
         MP_X = (DB_X + NDB_X)/2;
         MP_Y = (DB_Y + NDB_Y)/2;
   // We compute this point and look if it fulfill the condition
   // If yes => DB = MP; else NDB = MP;

   vals[0] = MP_X;
   vals[1] = MP_Y;
   vals[3] = myParserX.Eval(vals);
   vals[4] = myParserY.Eval(vals);
   vals[5] = myParserZ.Eval(vals);

   if( myParser_condition.Eval(vals) == 0) {
   NDB_X = MP_X;
   NDB_Y = MP_Y;
       } // End of if( myParser_condition.Eval(vals) == 0)
   else {
   DB_X = MP_X;
   DB_Y = MP_Y;
   DL2[j*3    ][i] = vals[3];
   DL2[j*3 + 1][i] = vals[4];
   DL2[j*3 + 2][i] = vals[5];
        }
   precision_step++;
   }// End of while ( precision_step < 5)...

   } // End of if(hidden_points[j][i] == 0)


///============= Second case : HL = Height-Left ============

   else if(hidden_points[j+1][i] == 0) {
   // initialisation
   DB_X  =  ((double)(j))   * U_step + u_inf;
   DB_Y  =  ((double)(i+1)) * V_step + v_inf;

   //DB_X  =  ((double)(j+1))   * U_step + u_inf;
   //DB_Y  =  ((double)(i+1)) * V_step + v_inf;

   NDB_X =  ((double)(j+1)) * U_step + u_inf;
   NDB_Y =  ((double)(i))   * V_step + v_inf;

   HL2[(j+1)*3    ][i] = Tre2[(j+1)*3    ][i+1];
   HL2[(j+1)*3 + 1][i] = Tre2[(j+1)*3 + 1][i+1];
   HL2[(j+1)*3 + 2][i] = Tre2[(j+1)*3 + 2][i+1];

   precision_step = 0; // Approximation by 2^5

   while ( precision_step < 5){
         MP_X = (DB_X + NDB_X)/2;
         MP_Y = (DB_Y + NDB_Y)/2;
   // We compute this point and look if it fulfill the condition
   // If yes => DB = MP; else NDB = MP;

   vals[0] = MP_X;
   vals[1] = MP_Y;
   vals[3] = myParserX.Eval(vals);
   vals[4] = myParserY.Eval(vals);
   vals[5] = myParserZ.Eval(vals);

   if( myParser_condition.Eval(vals) == 0) {
   NDB_X = MP_X;
   NDB_Y = MP_Y;
       } // End of if( myParser_condition.Eval(vals) == 0)
   else {
   DB_X = MP_X;
   DB_Y = MP_Y;
   HL2[(j+1)*3    ][i] = vals[3];
   HL2[(j+1)*3 + 1][i] = vals[4];
   HL2[(j+1)*3 + 2][i] = vals[5];
        }
   precision_step++;
   }// End of while ( precision_step < 5)...
   } // End of if(hidden_points[j][i] == 0)


///============= Third case : HR = Height-Right ============

   else if(hidden_points[j+1][i+1] == 0) {
   // initialisation
   DB_X  =  ((double)(j))   * U_step + u_inf;
   DB_Y  =  ((double)(i))   * V_step + v_inf;
   //DB_X  =  ((double)(j))   * U_step + u_inf;
   //DB_Y  =  ((double)(i+1))   * V_step + v_inf;

   NDB_X =  ((double)(j+1)) * U_step + u_inf;
   NDB_Y =  ((double)(i+1)) * V_step + v_inf;

   HR2[(j+1)*3    ][i+1] = Tre2[j*3    ][i+1];
   HR2[(j+1)*3 + 1][i+1] = Tre2[j*3 + 1][i+1];
   HR2[(j+1)*3 + 2][i+1] = Tre2[j*3 + 2][i+1];

   precision_step = 0; // Approximation by 2^5

   while ( precision_step < 5){
         MP_X = (DB_X + NDB_X)/2;
         MP_Y = (DB_Y + NDB_Y)/2;
   // We compute this point and look if it fulfill the condition
   // If yes => DB = MP; else NDB = MP;

   vals[0] = MP_X;
   vals[1] = MP_Y;
   vals[3] = myParserX.Eval(vals);
   vals[4] = myParserY.Eval(vals);
   vals[5] = myParserZ.Eval(vals);

   if( myParser_condition.Eval(vals) == 0) {
   NDB_X = MP_X;
   NDB_Y = MP_Y;
       } // End of if( myParser_condition.Eval(vals) == 0)
   else {
   DB_X = MP_X;
   DB_Y = MP_Y;
   HR2[(j+1)*3    ][i+1] = vals[3];
   HR2[(j+1)*3 + 1][i+1] = vals[4];
   HR2[(j+1)*3 + 2][i+1] = vals[5];
        }
   precision_step++;
   }// End of while ( precision_step < 5)...
   } // End of if(hidden_points[j][i] == 0)



///============= Fourth case : DR = Height-Right ============

   else if(hidden_points[j][i+1] == 0) {
   // initialisation
   DB_X  =  ((double)(j+1))   * U_step + u_inf;
   DB_Y  =  ((double)(i))   * V_step + v_inf;
   //DB_X  =  ((double)(j))   * U_step + u_inf;
   //DB_Y  =  ((double)(i))   * V_step + v_inf;

   NDB_X =  ((double)(j)) * U_step + u_inf;
   NDB_Y =  ((double)(i+1))   * V_step + v_inf;

   DR2[j*3    ][i+1] = Tre2[j*3    ][i];
   DR2[j*3 + 1][i+1] = Tre2[j*3 + 1][i];
   DR2[j*3 + 2][i+1] = Tre2[j*3 + 2][i];

   precision_step = 0; // Approximation by 2^5

   while ( precision_step < 5){
         MP_X = (DB_X + NDB_X)/2;
         MP_Y = (DB_Y + NDB_Y)/2;
   // We compute this point and look if it fulfill the condition
   // If yes => DB = MP; else NDB = MP;

   vals[0] = MP_X;
   vals[1] = MP_Y;
   vals[3] = myParserX.Eval(vals);
   vals[4] = myParserY.Eval(vals);
   vals[5] = myParserZ.Eval(vals);

   if( myParser_condition.Eval(vals) == 0) {
   NDB_X = MP_X;
   NDB_Y = MP_Y;
       } // End of if( myParser_condition.Eval(vals) == 0)
   else {
   DB_X = MP_X;
   DB_Y = MP_Y;
   DR2[j*3    ][i+1] = vals[3];
   DR2[j*3 + 1][i+1] = vals[4];
   DR2[j*3 + 2][i+1] = vals[5];
        }

   precision_step++;
   }// End of while ( precision_step < 5)...

   } // End of if(hidden_points[j][i] == 0)

                  } // End of if((hidden_points[j][i] + ...)



double DB2_X, DB2_Y,
    NDB2_X, NDB2_Y,
    MP2_X, MP2_Y;

//==============================================================
//========== In this case, we have two missing point ===========
//==============================================================
  for(j=0; j < nb_ligne -1   ; j++)
    for (i=0; i < nb_colone -1  ; i++)

      if((hidden_points[j  ][i  ]  +
          hidden_points[j+1][i  ]  +
          hidden_points[j+1][i+1]  +
          hidden_points[j  ][i+1]) == 2)
              {
///==================================
   if(hidden_points[j][i] == 0 && hidden_points[j][i+1] == 0) {
   // initialisation
   DB_X  =  ((double)(j+1)) * U_step + u_inf;
   DB_Y  =  ((double)(i)) * V_step + v_inf;

   NDB_X =  ((double)(j)) * U_step + u_inf;
   NDB_Y =  ((double)(i)) * V_step + v_inf;

   DL2[j*3    ][i] = Tre2[(j+1)*3    ][i];
   DL2[j*3 + 1][i] = Tre2[(j+1)*3 + 1][i];
   DL2[j*3 + 2][i] = Tre2[(j+1)*3 + 2][i];

   DB2_X  =  ((double)(j+1))   * U_step + u_inf;
   DB2_Y  =  ((double)(i+1))   * V_step + v_inf;

   NDB2_X =  ((double)(j)) * U_step + u_inf;
   NDB2_Y =  ((double)(i+1))* V_step + v_inf;

   DR2[j*3    ][i+1] = Tre2[(j+1)*3    ][i+1];
   DR2[j*3 + 1][i+1] = Tre2[(j+1)*3 + 1][i+1];
   DR2[j*3 + 2][i+1] = Tre2[(j+1)*3 + 2][i+1];

   // First point solution
   precision_step = 0;
   while ( precision_step < 5){
         MP_X = (DB_X + NDB_X)/2;
         MP_Y = (DB_Y + NDB_Y)/2;

   vals[0] = MP_X;
   vals[1] = MP_Y;
   vals[3] = myParserX.Eval(vals);
   vals[4] = myParserY.Eval(vals);
   vals[5] = myParserZ.Eval(vals);

   if( myParser_condition.Eval(vals) == 0) {
   NDB_X = MP_X;
   NDB_Y = MP_Y;
       } // End of if( myParser_condition.Eval(vals) == 0)
   else {
   DB_X = MP_X;
   DB_Y = MP_Y;
   DL2[j*3    ][i] = vals[3];
   DL2[j*3 + 1][i] = vals[4];
   DL2[j*3 + 2][i] = vals[5];
        }

   precision_step++;
   }// End of while ( precision_step < 5)...

   // Second point solution
   precision_step = 0;
   while ( precision_step < 5){
         MP2_X = (DB2_X + NDB2_X)/2;
         MP2_Y = (DB2_Y + NDB2_Y)/2;

   vals[0] = MP2_X;
   vals[1] = MP2_Y;
   vals[3] = myParserX.Eval(vals);
   vals[4] = myParserY.Eval(vals);
   vals[5] = myParserZ.Eval(vals);

   if( myParser_condition.Eval(vals) == 0) {
   NDB2_X = MP2_X;
   NDB2_Y = MP2_Y;
       }
   else {
   DB2_X = MP2_X;
   DB2_Y = MP2_Y;
   DR2[j*3    ][i+1] = vals[3];
   DR2[j*3 + 1][i+1] = vals[4];
   DR2[j*3 + 2][i+1] = vals[5];
        }

   precision_step++;
   }// End of while ( precision_step < 5)...


   } // End of if(hidden_points[j][i] == 0 && hidden_points[j][i+1] == 0)


///=========================

   else if(hidden_points[j][i] == 0 && hidden_points[j+1][i] == 0) {
   // initialisation
   DB_X  =  ((double)(j)) * U_step + u_inf;
   DB_Y  =  ((double)(i+1))* V_step + v_inf;

   NDB_X =  ((double)(j)) * U_step + u_inf;
   NDB_Y =  ((double)(i)) * V_step + v_inf;

   DL2[j*3    ][i] = Tre2[j*3    ][i+1];
   DL2[j*3 + 1][i] = Tre2[j*3 + 1][i+1];
   DL2[j*3 + 2][i] = Tre2[j*3 + 2][i+1];


   DB2_X  =  ((double)(j+1))   * U_step + u_inf;
   DB2_Y  =  ((double)(i+1))   * V_step + v_inf;

   NDB2_X =  ((double)(j+1)) * U_step + u_inf;
   NDB2_Y =  ((double)(i))   * V_step + v_inf;

   HL2[(j+1)*3    ][i] = Tre2[(j+1)*3    ][i+1];
   HL2[(j+1)*3 + 1][i] = Tre2[(j+1)*3 + 1][i+1];
   HL2[(j+1)*3 + 2][i] = Tre2[(j+1)*3 + 2][i+1];

   // First point solution
   precision_step = 0;
   while ( precision_step < 5){
         MP_X = (DB_X + NDB_X)/2;
         MP_Y = (DB_Y + NDB_Y)/2;

   vals[0] = MP_X;
   vals[1] = MP_Y;
   vals[3] = myParserX.Eval(vals);
   vals[4] = myParserY.Eval(vals);
   vals[5] = myParserZ.Eval(vals);

   if( myParser_condition.Eval(vals) == 0) {
   NDB_X = MP_X;
   NDB_Y = MP_Y;
       } // End of if( myParser_condition.Eval(vals) == 0)
   else {
   DB_X = MP_X;
   DB_Y = MP_Y;
   DL2[j*3    ][i] = vals[3];
   DL2[j*3 + 1][i] = vals[4];
   DL2[j*3 + 2][i] = vals[5];
        }

   precision_step++;
   }// End of while ( precision_step < 5)...


   // Second point solution
   precision_step = 0;
   while ( precision_step < 5){
         MP2_X = (DB2_X + NDB2_X)/2;
         MP2_Y = (DB2_Y + NDB2_Y)/2;

   vals[0] = MP2_X;
   vals[1] = MP2_Y;
   vals[3] = myParserX.Eval(vals);
   vals[4] = myParserY.Eval(vals);
   vals[5] = myParserZ.Eval(vals);

   if( myParser_condition.Eval(vals) == 0) {
   NDB2_X = MP2_X;
   NDB2_Y = MP2_Y;
       }
   else {
   DB2_X = MP2_X;
   DB2_Y = MP2_Y;
   HL2[(j+1)*3    ][i] = vals[3];
   HL2[(j+1)*3 + 1][i] = vals[4];
   HL2[(j+1)*3 + 2][i] = vals[5];
        }

   precision_step++;
   }// End of while ( precision_step < 5)...


   } // End of if(hidden_points[j][i] == 0 && hidden_points[j+1][i] == 0)


///=========================

   else if(hidden_points[j+1][i] == 0 && hidden_points[j+1][i+1] == 0) {
   // initialisation
   DB_X  =  ((double)(j)) * U_step + u_inf;
   DB_Y  =  ((double)(i+1)) * V_step + v_inf;

   NDB_X =  ((double)(j+1)) * U_step + u_inf;
   NDB_Y =  ((double)(i+1)) * V_step + v_inf;

   HR2[(j+1)*3    ][i+1] = Tre2[j*3    ][i+1];
   HR2[(j+1)*3 + 1][i+1] = Tre2[j*3 + 1][i+1];
   HR2[(j+1)*3 + 2][i+1] = Tre2[j*3 + 2][i+1];



   DB2_X  =  ((double)(j))   * U_step + u_inf;
   DB2_Y  =  ((double)(i)) * V_step + v_inf;

   NDB2_X =  ((double)(j+1)) * U_step + u_inf;
   NDB2_Y =  ((double)(i))   * V_step + v_inf;

   HL2[(j+1)*3    ][i] = Tre2[j*3    ][i];
   HL2[(j+1)*3 + 1][i] = Tre2[j*3 + 1][i];
   HL2[(j+1)*3 + 2][i] = Tre2[j*3 + 2][i];

   // First point solution
   precision_step = 0;
   while ( precision_step < 5){
         MP_X = (DB_X + NDB_X)/2;
         MP_Y = (DB_Y + NDB_Y)/2;

   vals[0] = MP_X;
   vals[1] = MP_Y;
   vals[3] = myParserX.Eval(vals);
   vals[4] = myParserY.Eval(vals);
   vals[5] = myParserZ.Eval(vals);

   if( myParser_condition.Eval(vals) == 0) {
   NDB_X = MP_X;
   NDB_Y = MP_Y;
       } // End of if( myParser_condition.Eval(vals) == 0)
   else {
   DB_X = MP_X;
   DB_Y = MP_Y;
   HR2[(j+1)*3    ][i+1] = vals[3];
   HR2[(j+1)*3 + 1][i+1] = vals[4];
   HR2[(j+1)*3 + 2][i+1] = vals[5];
        }

   precision_step++;
   }// End of while ( precision_step < 5)...


   // Second point solution
   precision_step = 0;
   while ( precision_step < 5){
         MP2_X = (DB2_X + NDB2_X)/2;
         MP2_Y = (DB2_Y + NDB2_Y)/2;

   vals[0] = MP2_X;
   vals[1] = MP2_Y;
   vals[3] = myParserX.Eval(vals);
   vals[4] = myParserY.Eval(vals);
   vals[5] = myParserZ.Eval(vals);

   if( myParser_condition.Eval(vals) == 0) {
   NDB2_X = MP2_X;
   NDB2_Y = MP2_Y;
       }
   else {
   DB2_X = MP2_X;
   DB2_Y = MP2_Y;
   HL2[(j+1)*3    ][i] = vals[3];
   HL2[(j+1)*3 + 1][i] = vals[4];
   HL2[(j+1)*3 + 2][i] = vals[5];
        }

   precision_step++;
   }// End of while ( precision_step < 5)...

   } // End of if(hidden_points[j+1][i] == 0 && hidden_points[j+1][i+1] == 0)

///============= Fourth case : DR = Height-Right ============

   else if(hidden_points[j+1][i+1] == 0 && hidden_points[j][i+1] == 0) {
   // initialisation
   DB_X  =  ((double)(j+1)) * U_step + u_inf;
   DB_Y  =  ((double)(i)) * V_step + v_inf;

   NDB_X =  ((double)(j+1)) * U_step + u_inf;
   NDB_Y =  ((double)(i+1)) * V_step + v_inf;

   HR2[(j+1)*3    ][i+1] = Tre2[(j+1)*3    ][i];
   HR2[(j+1)*3 + 1][i+1] = Tre2[(j+1)*3 + 1][i];
   HR2[(j+1)*3 + 2][i+1] = Tre2[(j+1)*3 + 2][i];

   DB2_X  =  ((double)(j)) * U_step + u_inf;
   DB2_Y  =  ((double)(i)) * V_step + v_inf;

   NDB2_X =  ((double)(j)) * U_step + u_inf;
   NDB2_Y =  ((double)(i+1))* V_step + v_inf;

   DR2[j*3    ][i+1] = Tre2[j*3    ][i];
   DR2[j*3 + 1][i+1] = Tre2[j*3 + 1][i];
   DR2[j*3 + 2][i+1] = Tre2[j*3 + 2][i];

   // First point solution
   precision_step = 0;
   while ( precision_step < 5){
         MP_X = (DB_X + NDB_X)/2;
         MP_Y = (DB_Y + NDB_Y)/2;

   vals[0] = MP_X;
   vals[1] = MP_Y;
   vals[3] = myParserX.Eval(vals);
   vals[4] = myParserY.Eval(vals);
   vals[5] = myParserZ.Eval(vals);

   if( myParser_condition.Eval(vals) == 0) {
   NDB_X = MP_X;
   NDB_Y = MP_Y;
       } // End of if( myParser_condition.Eval(vals) == 0)
   else {
   DB_X = MP_X;
   DB_Y = MP_Y;
   HR2[(j+1)*3    ][i+1] = vals[3];
   HR2[(j+1)*3 + 1][i+1] = vals[4];
   HR2[(j+1)*3 + 2][i+1] = vals[5];
        }

   precision_step++;
   }// End of while ( precision_step < 5)...

   // Second point solution
   precision_step = 0;
   while ( precision_step < 5){
         MP2_X = (DB2_X + NDB2_X)/2;
         MP2_Y = (DB2_Y + NDB2_Y)/2;

   vals[0] = MP2_X;
   vals[1] = MP2_Y;
   vals[3] = myParserX.Eval(vals);
   vals[4] = myParserY.Eval(vals);
   vals[5] = myParserZ.Eval(vals);

   if( myParser_condition.Eval(vals) == 0) {
   NDB2_X = MP2_X;
   NDB2_Y = MP2_Y;
       }
   else {
   DB2_X = MP2_X;
   DB2_Y = MP2_Y;
   DR2[j*3    ][i+1] = vals[3];
   DR2[j*3 + 1][i+1] = vals[4];
   DR2[j*3 + 2][i+1] = vals[5];
        }
   precision_step++;
   }// End of while ( precision_step < 5)...


   } // End of if(hidden_points[j+1][i+1] == 0 && hidden_points[j][i+1] == 0)

} // End of if((hidden_points[j][i] + ...)

}; // End of if(there_is_hidden_points == 1)

// Computes Points axes if activated :
// This must be changed for better performances...
if(drawaxes_ok == 1) {

MINX =999999999;
MINY =999999999;
MINZ =999999999;;

MAXX =-999999999;
MAXY =-999999999;
MAXZ =-999999999;

 for (i=0; i < nb_ligne   ; i++)
    for (j=0; j < nb_colone   ; j++) {
     if(hidden_points[i][j] == 1 || implicitdef != 1) {
     if(MINX > Tre2[i*3    ][j] ) MINX = Tre2[i*3    ][j] ;

     if(MINY > Tre2[i*3 + 1][j] ) MINY = Tre2[i*3 + 1][j] ;

     if(MINZ > Tre2[i*3 + 2][j] ) MINZ = Tre2[i*3 + 2][j] ;

     if(MAXX < Tre2[i*3    ][j] ) MAXX = Tre2[i*3    ][j] ;

     if(MAXY < Tre2[i*3 + 1][j] ) MAXY = Tre2[i*3 + 1][j] ;

     if(MAXZ < Tre2[i*3 + 2][j] ) MAXZ = Tre2[i*3 + 2][j] ;
                                  }
    }

  DIFX = MAXX - MINX ;
  DIFY = MAXY - MINY ;
  DIFZ = MAXZ - MINZ ;

double StepX, StepY, StepZ, center_x, center_y, center_z;

StepX = fabs((2./3.)*DIFX*axe_size/(double)(nb_licol-1));
StepY = fabs((2./3.)*DIFY*axe_size/(double)(nb_licol-1));
StepZ = fabs((2./3.)*DIFZ*axe_size/(double)(nb_licol-1));

if(axe_center == -1) {
 center_x = (MAXX + MINX)/2.;
 center_y = (MAXY + MINY)/2.;
 center_z = (MAXZ + MINZ)/2.;

StepX = (2./3.)*DIFX*axe_size/(double)(nb_licol-1);
StepY = (2./3.)*DIFY*axe_size/(double)(nb_licol-1);
StepZ = (2./3.)*DIFZ*axe_size/(double)(nb_licol-1);

}
else center_x = center_y = center_z = 0;

for (i=0; i < nb_licol ; i++) {
        Axes_array2[0][i*3    ] = center_x + i*StepX;
        Axes_array2[0][i*3 + 1] = center_y;
        Axes_array2[0][i*3 + 2] = center_z;

        Axes_array2[1][i*3    ] = center_x;
        Axes_array2[1][i*3 + 1] = center_y + i*StepY;
        Axes_array2[1][i*3 + 2] = center_z;

        Axes_array2[2][i*3    ] = center_x;
        Axes_array2[2][i*3 + 1] = center_y;
        Axes_array2[2][i*3 + 2] = center_z + i*StepZ;
                          }

} // End of if(drawaxes_ok == 1);

} // End of the fct calcul_objet3()

/*****************************************************************************/
/*****************************************************************************/
void  Model3D::boite_englobante3() {
int i, j;
// calcul des minimas et des maximas des coordonnees: X,Y et Z

MINX =999999999;//Tre2[0][0];
MINY =999999999;//Tre2[1][0];
MINZ =999999999;//Tre2[2][0];

MAXX =-999999999;//Tre2[0][0];
MAXY =-999999999;//Tre2[1][0];
MAXZ =-999999999;//Tre2[2][0];

 for (i=0; i < nb_ligne   ; i++)
    for (j=0; j < nb_colone   ; j++) {
     if(hidden_points[i][j] == 1 || implicitdef != 1) {
     if(MINX > Tre2[i*3    ][j] ) MINX = Tre2[i*3    ][j] ;

     if(MINY > Tre2[i*3 + 1][j] ) MINY = Tre2[i*3 + 1][j] ;

     if(MINZ > Tre2[i*3 + 2][j] ) MINZ = Tre2[i*3 + 2][j] ;

     if(MAXX < Tre2[i*3    ][j] ) MAXX = Tre2[i*3    ][j] ;

     if(MAXY < Tre2[i*3 + 1][j] ) MAXY = Tre2[i*3 + 1][j] ;

     if(MAXZ < Tre2[i*3 + 2][j] ) MAXZ = Tre2[i*3 + 2][j] ;
                                  }
    }
// On recherche la plus grande "difference" de distance entre les points
// pour reduire la figure a un cube d'une longueur de 1.
// On utilisera apres cette figure pour l'agrandir et bien la placer dans
// la fenetre de vue:

  DIFX = MAXX - MINX ;
  DIFY = MAXY - MINY ;
  DIFZ = MAXZ - MINZ ;

// save theses values for the equations generator :
  DIFX_tmp = DIFX; DIFY_tmp = DIFY; DIFZ_tmp = DIFZ;
  MINX_tmp = MINX; MINY_tmp = MINY; MINZ_tmp = MINZ;

// Recherche du maximum :
  DIFMAXIMUM = DIFX;

  if (DIFY > DIFMAXIMUM) {DIFMAXIMUM = DIFY;};
  if (DIFZ > DIFMAXIMUM) {DIFMAXIMUM = DIFZ;};

/// On va inclure cet objet dans un cube de langueur maximum
/// egale a "hauteur_fenetre"

double decalage_xo = -(MINX +MAXX)/2 ;
double decalage_yo = -(MINY +MAXY)/2 ;
double decalage_zo = -(MINZ +MAXZ)/2 ;

 for (i=0; i < nb_ligne   ; i++)
    for (j=0; j < nb_colone   ; j++) {
    Tre2[i*3    ][j] = hauteur_fenetre * (Tre2[i*3    ][j] + decalage_xo)/DIFMAXIMUM ;
    Tre2[i*3 + 1][j] = hauteur_fenetre * (Tre2[i*3 + 1][j] + decalage_yo)/DIFMAXIMUM ;
    Tre2[i*3 + 2][j] = hauteur_fenetre * (Tre2[i*3 + 2][j] + decalage_zo)/DIFMAXIMUM ;
    }

/// This part is for the calculation of the Axes Points:
if(drawaxes_ok == 1)
for (j=0; j < 3   ; j++)
 for (i=0; i < nb_licol   ; i++){
    Axes_array2[j][i*3   ] = hauteur_fenetre * (Axes_array2[j][i*3   ] + decalage_xo)/DIFMAXIMUM ;
    Axes_array2[j][i*3 +1] = hauteur_fenetre * (Axes_array2[j][i*3 +1] + decalage_yo)/DIFMAXIMUM ;
    Axes_array2[j][i*3 +2] = hauteur_fenetre * (Axes_array2[j][i*3 +2] + decalage_zo)/DIFMAXIMUM ;
}
/// End of calculation of the Axes Points

if(there_is_condition == 1 )
 for (i=0; i < nb_ligne   ; i++)
    for (j=0; j < nb_colone   ; j++)
if(hidden_points[i][j] == 0) {
   // HR
    HR2[i*3    ][j] = hauteur_fenetre * (HR2[i*3    ][j] + decalage_xo)/DIFMAXIMUM ;
    HR2[i*3 + 1][j] = hauteur_fenetre * (HR2[i*3 + 1][j] + decalage_yo)/DIFMAXIMUM ;
    HR2[i*3 + 2][j] = hauteur_fenetre * (HR2[i*3 + 2][j] + decalage_zo)/DIFMAXIMUM ;

   // DR
    DR2[i*3    ][j] = hauteur_fenetre * (DR2[i*3    ][j] + decalage_xo)/DIFMAXIMUM ;
    DR2[i*3 + 1][j] = hauteur_fenetre * (DR2[i*3 + 1][j] + decalage_yo)/DIFMAXIMUM ;
    DR2[i*3 + 2][j] = hauteur_fenetre * (DR2[i*3 + 2][j] + decalage_zo)/DIFMAXIMUM ;

   // HL
    HL2[i*3    ][j] = hauteur_fenetre * (HL2[i*3    ][j] + decalage_xo)/DIFMAXIMUM ;
    HL2[i*3 + 1][j] = hauteur_fenetre * (HL2[i*3 + 1][j] + decalage_yo)/DIFMAXIMUM ;
    HL2[i*3 + 2][j] = hauteur_fenetre * (HL2[i*3 + 2][j] + decalage_zo)/DIFMAXIMUM ;

   // DL
    DL2[i*3    ][j] = hauteur_fenetre * (DL2[i*3    ][j] + decalage_xo)/DIFMAXIMUM ;
    DL2[i*3 + 1][j] = hauteur_fenetre * (DL2[i*3 + 1][j] + decalage_yo)/DIFMAXIMUM ;
    DL2[i*3 + 2][j] = hauteur_fenetre * (DL2[i*3 + 2][j] + decalage_zo)/DIFMAXIMUM ;
     }

MINX = hauteur_fenetre * (MINX + decalage_xo)/DIFMAXIMUM;
MINY = hauteur_fenetre * (MINY + decalage_yo)/DIFMAXIMUM;
MINZ = hauteur_fenetre * (MINZ + decalage_zo)/DIFMAXIMUM;

MAXX = hauteur_fenetre * (MAXX + decalage_xo)/DIFMAXIMUM;
MAXY = hauteur_fenetre * (MAXY + decalage_yo)/DIFMAXIMUM;
MAXZ = hauteur_fenetre * (MAXZ + decalage_zo)/DIFMAXIMUM;

  // Construction de la boite englobante...

  boiteenglobante2[0] = MAXX;
  boiteenglobante2[1] = MAXY;
  boiteenglobante2[2] = MAXZ;

  boiteenglobante2[3] = MINX;
  boiteenglobante2[4] = MAXY;
  boiteenglobante2[5] = MAXZ;

  boiteenglobante2[6] = MINX;
  boiteenglobante2[7] = MAXY;
  boiteenglobante2[8] = MINZ;

  boiteenglobante2[9]  = MAXX;
  boiteenglobante2[10] = MAXY;
  boiteenglobante2[11] = MINZ;

  boiteenglobante2[12] = MAXX;
  boiteenglobante2[13] = MINY;
  boiteenglobante2[14] = MAXZ;

  boiteenglobante2[15] = MINX;
  boiteenglobante2[16] = MINY;
  boiteenglobante2[17] = MAXZ;

  boiteenglobante2[18] = MINX;
  boiteenglobante2[19] = MINY;
  boiteenglobante2[20] = MINZ;

  boiteenglobante2[21]  = MAXX;
  boiteenglobante2[22]  = MINY;
  boiteenglobante2[23]  = MINZ;
}

/*****************************************************************************/
/*****************************************************************************/
void  Model3D::project_4D_to_3D(){
int i, j;
double c4;
for ( i=0; i < nb_ligne - coupure_ligne; ++i)
	for ( j=0; j < nb_colone - coupure_col  ; ++j){
       c4 = 1/(shape4D[i*4 + 3][j] - 2);
       Tre2[i*3  ][j] = c4*shape4D[i*4    ][j];
       Tre2[i*3+1][j] = c4*shape4D[i*4 + 1][j];
       Tre2[i*3+2][j] = c4*shape4D[i*4 + 2][j];
                                                  }
      }
/*****************************************************************************/
/*****************************************************************************/
void  Model3D::boite_englobante4D() {
// calcul des minimas et des maximas des coordonnees: X,Y et Z

MINX =999999999;
MINY =999999999;
MINZ =999999999;
MINW =999999999;

MAXX =-999999999;
MAXY =-999999999;
MAXZ =-999999999;
MAXW =-999999999;

 for (int i=0; i < nb_ligne   ; i++)
    for (int j=0; j < nb_colone   ; j++) {

     if(MINX > shape4D[i*4    ][j] ) MINX = shape4D[i*4    ][j] ;
     if(MINY > shape4D[i*4 + 1][j] ) MINY = shape4D[i*4 + 1][j] ;
     if(MINZ > shape4D[i*4 + 2][j] ) MINZ = shape4D[i*4 + 2][j] ;
     if(MINW > shape4D[i*4 + 3][j] ) MINW = shape4D[i*4 + 3][j] ;


     if(MAXX < shape4D[i*4    ][j] ) MAXX = shape4D[i*4    ][j] ;
     if(MAXY < shape4D[i*4 + 1][j] ) MAXY = shape4D[i*4 + 1][j] ;
     if(MAXZ < shape4D[i*4 + 2][j] ) MAXZ = shape4D[i*4 + 2][j] ;
     if(MAXW < shape4D[i*4 + 3][j] ) MAXW = shape4D[i*4 + 3][j] ;
    }

// On recherche la plus grande "difference" de distance entre les points
// pour reduire la figure a un cube d'une longueur de 1.
// On utilisera apres cette figure pour l'agrandir et bien la placer dans
// la fenetre de vue:

  DIFX = MAXX - MINX ;
  DIFY = MAXY - MINY ;
  DIFZ = MAXZ - MINZ ;
  DIFW = MAXW - MINW ;

// Recherche du maximum :
  DIFMAXIMUM = DIFX;

  if (DIFY > DIFMAXIMUM) {DIFMAXIMUM = DIFY;};
  if (DIFZ > DIFMAXIMUM) {DIFMAXIMUM = DIFZ;};
  if (DIFW > DIFMAXIMUM) {DIFMAXIMUM = DIFW;};

// On va inclure cet objet dans un HperCube de langueur maximum
// egale a "hauteur_fenetre"

double decalage_xo = -(MINX +MAXX)/2 ;
double decalage_yo = -(MINY +MAXY)/2 ;
double decalage_zo = -(MINZ +MAXZ)/2 ;
double decalage_wo = -(MINW +MAXW)/2 ;

 for (int i=0; i < nb_ligne   ; i++)
    for (int j=0; j < nb_colone   ; j++) {
    shape4D[i*4    ][j] = (shape4D[i*4    ][j] + decalage_xo)/DIFMAXIMUM ;
    shape4D[i*4 + 1][j] = (shape4D[i*4 + 1][j] + decalage_yo)/DIFMAXIMUM ;
    shape4D[i*4 + 2][j] = (shape4D[i*4 + 2][j] + decalage_zo)/DIFMAXIMUM ;
    shape4D[i*4 + 3][j] = (shape4D[i*4 + 3][j] + decalage_wo)/DIFMAXIMUM ;
    }
}
/*****************************************************************************/
/*****************************************************************************/
void  Model3D::project_5D_to_4D(){
int i, j;
double c4;
for ( i=0; i < nb_ligne - coupure_ligne; ++i)
	for ( j=0; j < nb_colone - coupure_col  ; ++j){
       c4 = 1/(shape5D[i*5 + 4][j] - 2);
       shape4D[i*4  ][j] = c4*shape5D[i*5    ][j];
       shape4D[i*4+1][j] = c4*shape5D[i*5 + 1][j];
       shape4D[i*4+2][j] = c4*shape5D[i*5 + 2][j];
       shape4D[i*4+3][j] = c4*shape5D[i*5 + 3][j];
                                                  }
      }
/*****************************************************************************/
/*****************************************************************************/
void  Model3D::boite_englobante5D() {
// calcul des minimas et des maximas des coordonnees: X,Y et Z

MINX =999999999;
MINY =999999999;
MINZ =999999999;
MINW =999999999;
MINT =999999999;

MAXX =-999999999;
MAXY =-999999999;
MAXZ =-999999999;
MAXW =-999999999;
MAXT =-999999999;

 for (int i=0; i < nb_ligne   ; i++)
    for (int j=0; j < nb_colone   ; j++) {

     if(MINX > shape5D[i*5    ][j] ) MINX = shape5D[i*5    ][j] ;
     if(MINY > shape5D[i*5 + 1][j] ) MINY = shape5D[i*5 + 1][j] ;
     if(MINZ > shape5D[i*5 + 2][j] ) MINZ = shape5D[i*5 + 2][j] ;
     if(MINW > shape5D[i*5 + 3][j] ) MINW = shape5D[i*5 + 3][j] ;
     if(MINT > shape5D[i*5 + 4][j] ) MINT = shape5D[i*5 + 4][j] ;

     if(MAXX < shape5D[i*5    ][j] ) MAXX = shape5D[i*5    ][j] ;
     if(MAXY < shape5D[i*5 + 1][j] ) MAXY = shape5D[i*5 + 1][j] ;
     if(MAXZ < shape5D[i*5 + 2][j] ) MAXZ = shape5D[i*5 + 2][j] ;
     if(MAXW < shape5D[i*5 + 3][j] ) MAXW = shape5D[i*5 + 3][j] ;
     if(MAXT < shape5D[i*5 + 4][j] ) MAXT = shape5D[i*5 + 4][j] ;
    }

// On recherche la plus grande "difference" de distance entre les points
// pour reduire la figure a un cube d'une longueur de 1.
// On utilisera apres cette figure pour l'agrandir et bien la placer dans
// la fenetre de vue:

  DIFX = MAXX - MINX ;
  DIFY = MAXY - MINY ;
  DIFZ = MAXZ - MINZ ;
  DIFW = MAXW - MINW ;
  DIFT = MAXT - MINT ;

// Recherche du maximum :
  DIFMAXIMUM = DIFX;

  if (DIFY > DIFMAXIMUM) {DIFMAXIMUM = DIFY;};
  if (DIFZ > DIFMAXIMUM) {DIFMAXIMUM = DIFZ;};
  if (DIFW > DIFMAXIMUM) {DIFMAXIMUM = DIFW;};
  if (DIFT > DIFMAXIMUM) {DIFMAXIMUM = DIFT;};

// On va inclure cet objet dans un HyperCube de langueur maximum
// egale a "hauteur_fenetre"

double decalage_xo = -(MINX +MAXX)/2 ;
double decalage_yo = -(MINY +MAXY)/2 ;
double decalage_zo = -(MINZ +MAXZ)/2 ;
double decalage_wo = -(MINW +MAXW)/2 ;
double decalage_to = -(MINT +MAXT)/2 ;

 for (int i=0; i < nb_ligne   ; i++)
    for (int j=0; j < nb_colone   ; j++) {
    shape5D[i*5    ][j] = (shape5D[i*5    ][j] + decalage_xo)/DIFMAXIMUM ;
    shape5D[i*5 + 1][j] = (shape5D[i*5 + 1][j] + decalage_yo)/DIFMAXIMUM ;
    shape5D[i*5 + 2][j] = (shape5D[i*5 + 2][j] + decalage_zo)/DIFMAXIMUM ;
    shape5D[i*5 + 3][j] = (shape5D[i*5 + 3][j] + decalage_wo)/DIFMAXIMUM ;
    shape5D[i*5 + 4][j] = (shape5D[i*5 + 4][j] + decalage_to)/DIFMAXIMUM ;

    }
}
/*****************************************************************************/
/*****************************************************************************/
void  Model3D::project_6D_to_5D(){
int i, j;
double c4;
for ( i=0; i < nb_ligne - coupure_ligne; ++i)
	for ( j=0; j < nb_colone - coupure_col  ; ++j){
       c4 = 1/(shape6D[i*6 + 5][j] - 2);
       shape5D[i*5  ][j] = c4*shape6D[i*6    ][j];
       shape5D[i*5+1][j] = c4*shape6D[i*6 + 1][j];
       shape5D[i*5+2][j] = c4*shape6D[i*6 + 2][j];
       shape5D[i*5+3][j] = c4*shape6D[i*6 + 3][j];
       shape5D[i*5+4][j] = c4*shape6D[i*6 + 4][j];
                                                  }
      }

/*****************************************************************************/
/*****************************************************************************/
void  Model3D::boite_englobante6D() {
// calcul des minimas et des maximas des coordonnees: X,Y et Z
MINX =999999999;
MINY =999999999;
MINZ =999999999;
MINW =999999999;
MINT =999999999;
MINS =999999999;

MAXX =-999999999;
MAXY =-999999999;
MAXZ =-999999999;
MAXW =-999999999;
MAXT =-999999999;
MAXS =-999999999;

 for (int i=0; i < nb_ligne   ; i++)
    for (int j=0; j < nb_colone   ; j++) {

     if(MINX > shape6D[i*6    ][j] ) MINX = shape6D[i*6    ][j] ;
     if(MINY > shape6D[i*6 + 1][j] ) MINY = shape6D[i*6 + 1][j] ;
     if(MINZ > shape6D[i*6 + 2][j] ) MINZ = shape6D[i*6 + 2][j] ;
     if(MINW > shape6D[i*6 + 3][j] ) MINW = shape6D[i*6 + 3][j] ;
     if(MINT > shape6D[i*6 + 4][j] ) MINT = shape6D[i*6 + 4][j] ;
     if(MINS > shape6D[i*6 + 5][j] ) MINS = shape6D[i*6 + 5][j] ;


     if(MAXX < shape6D[i*6    ][j] ) MAXX = shape6D[i*6    ][j] ;
     if(MAXY < shape6D[i*6 + 1][j] ) MAXY = shape6D[i*6 + 1][j] ;
     if(MAXZ < shape6D[i*6 + 2][j] ) MAXZ = shape6D[i*6 + 2][j] ;
     if(MAXW < shape6D[i*6 + 3][j] ) MAXW = shape6D[i*6 + 3][j] ;
     if(MAXT < shape6D[i*6 + 4][j] ) MAXT = shape6D[i*6 + 4][j] ;
     if(MAXS < shape6D[i*6 + 5][j] ) MAXS = shape6D[i*6 + 5][j] ;
    }

// On recherche la plus grande "difference" de distance entre les points
// pour reduire la figure a un cube d'une longueur de 1.
// On utilisera apres cette figure pour l'agrandir et bien la placer dans
// la fenetre de vue:

  DIFX = MAXX - MINX ;
  DIFY = MAXY - MINY ;
  DIFZ = MAXZ - MINZ ;
  DIFW = MAXW - MINW ;
  DIFT = MAXT - MINT ;
  DIFS = MAXS - MINS ;
// Recherche du maximum :
  DIFMAXIMUM = DIFX;

  if (DIFY > DIFMAXIMUM) {DIFMAXIMUM = DIFY;};
  if (DIFZ > DIFMAXIMUM) {DIFMAXIMUM = DIFZ;};
  if (DIFW > DIFMAXIMUM) {DIFMAXIMUM = DIFW;};
  if (DIFT > DIFMAXIMUM) {DIFMAXIMUM = DIFT;};
  if (DIFS > DIFMAXIMUM) {DIFMAXIMUM = DIFS;};

// On va inclure cet objet dans un HyperCube de langueur maximum
// egale a "hauteur_fenetre"

double decalage_xo = -(MINX +MAXX)/2 ;
double decalage_yo = -(MINY +MAXY)/2 ;
double decalage_zo = -(MINZ +MAXZ)/2 ;
double decalage_wo = -(MINW +MAXW)/2 ;
double decalage_to = -(MINT +MAXT)/2 ;
double decalage_so = -(MINS +MAXS)/2 ;

 for (int i=0; i < nb_ligne   ; i++)
    for (int j=0; j < nb_colone   ; j++) {
    shape6D[i*6    ][j] = (shape6D[i*6    ][j] + decalage_xo)/DIFMAXIMUM ;
    shape6D[i*6 + 1][j] = (shape6D[i*6 + 1][j] + decalage_yo)/DIFMAXIMUM ;
    shape6D[i*6 + 2][j] = (shape6D[i*6 + 2][j] + decalage_zo)/DIFMAXIMUM ;
    shape6D[i*6 + 3][j] = (shape6D[i*6 + 3][j] + decalage_wo)/DIFMAXIMUM ;
    shape6D[i*6 + 4][j] = (shape6D[i*6 + 4][j] + decalage_to)/DIFMAXIMUM ;
    shape6D[i*6 + 5][j] = (shape6D[i*6 + 5][j] + decalage_so)/DIFMAXIMUM ;
    }
}
