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
#include <qpointarray.h>
#include <qpainter.h>
#include <qbrush.h>
#include <qstring.h>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <list>
#include <qgl.h>
#include "fparser/fparser.h"


/** The representation of a 3D model */
class GL3D {
public:
    GLfloat ArrayNorVer[6*20000];
    GLuint  PolyIndices[4*20000];
    double  ArrayNorVer[6*20000];


    FunctionParser myParser, myParserX, myParserY, myParserZ, myParserW,  myParserT, myParserS,
                   myParserX_2, myParserY_2, myParserZ_2, f1,
                   myParser_spherical, myParser_cylindrical,
                   myParser_condition;
    QString  expression_X, expression_Y, expression_Z, expression_W, expression_T, expression_S,
             inf_u, sup_u, inf_v, sup_v,
             expression_Z_2, expression_Y_2, expression_X_2, inf_u_2, sup_u_2, inf_v_2, sup_v_2,
             newfct, expression_implicite, coefficient_n, keyboard,
             spherical_expression, cylindrical_expression, condition_expression,
             expression_X_save, expression_Y_save, expression_Z_save, quotient;

    GLuint timer_id, colortype, btgauche, btdroit, btmilieu,
           anim_ok, morph_ok,width, height, latence, count,
           nb_ligne, nb_colone, coupure_col, coupure_ligne,
           old_x, old_y, old_z, Axe_x, Axe_y, Axe_z,
           IDGlWindow, PolyNumber, VertexNumber;
};



