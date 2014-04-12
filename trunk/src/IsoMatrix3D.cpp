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
#include "IsoMatrix3D.h"

    /** Create a new unit matrix */
  IsoMatrix3D::IsoMatrix3D() {
    
	pi = 3.14159265;
	xx = 1.0f;
	yy = 1.0f;
	zz = 1.0f;
	wo = 1.0f;
	xy= xz =xo =yx =yz= yo =zx = zy = wx= wy= wz= 0;
	
    }
 /*********** PRODUIT  VECTORIEL  **************/

void IsoMatrix3D::CalcProdVect(double* v1,double* v2,double* v)
               {
	v[1]=v1[2]*v2[3]-v2[2]*v1[3];
        v[2]=v2[1]*v1[3]-v2[3]*v1[1];
	v[3]=v1[1]*v2[2]-v2[1]*v1[2];
		
		}

		
				
/********* Produit scalaire *******************/
double  IsoMatrix3D::prodscalaire(double*   v1,double*   v2)
{
 return (v1[1]*v2[1]+v1[2]*v2[2]+v1[3]*v2[3]);
 } 
