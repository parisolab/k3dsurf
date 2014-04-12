/***************************************************************************
 *   Copyright (C) 2005 by Abderrahman Taha                                *
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
#include <math.h>

class Matrix5D {
public:
    double xx, xy, xz, xw, xt, xo;
    double yx, yy, yz, yw, yt, yo;
    double zx, zy, zz, zw, zt, zo;
    double wx, wy, wz, ww, wt, wo;
    double tx, ty, tz, tw, tt, to;
    double kx, ky, kz, kw, kt, ko;
    
    double pi;
    public:
    Matrix5D();
    void scale(double );
    void scale_2(double, double, double, double, double);
    void translate(double, double, double, double, double);
    
    void xzrot(double);
    void yzrot(double);
    void xyrot(double);
    void xwrot(double);
    void ywrot(double);
    void zwrot(double);
    void xtrot(double);
    void ytrot(double);
    void ztrot(double);
    void wtrot(double);
    
    
    void mult(Matrix5D);
    void unit();
};

