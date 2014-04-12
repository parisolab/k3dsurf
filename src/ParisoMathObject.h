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

#include <qstring.h>
#include <qfile.h>
#include <qstringlist.h>
 
 struct parisostruct {
        QString modeltype[1000]; /// Isosurface, parametric surface...
        QString FunctionsNames[1000];
        QString FunctionsInfos[1000];
        QString FunctionsConditions[1000];

        QString FunctionsEquations[1000];
        QString xlimitinfsup[2][1000];
        QString ylimitinfsup[2][1000];
        QString zlimitinfsup[2][1000];

        QString XFunctionsEquations[1000];
        QString YFunctionsEquations[1000];
        QString ZFunctionsEquations[1000];
        QString ulimitinfsup[2][1000];
        QString vlimitinfsup[2][1000];

        double  color[1000][4]; /// Front, Back, Grid, CND, !CND, Background...
        int gridresolution[6];
        int EquationsNumber;

};

class ParisoMathObject {
public :
parisostruct pariso;
QString EquationsNames;
QString Isosurface[10];
QString Parametric[20];
public :
   ParisoMathObject();
   ~ParisoMathObject();

   void LoadScript (QString, int);
   void ExecuteScript();
   void DrawIsoSurface();
   QString ChangeScript(QString, QString="", QString ="", QString* = NULL, QString* = NULL);
   void LookForIsosurfaceEquation(QString);
   void LookForParametricEquation(QString);
   void Look4DParametricEquation(QString);
};
