/***************************************************************************
 *   Copyright (C) 2007 by Abderrahman Taha                                *
 *                                                                         *
 *                                                                         *
 *   This program is free software;you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation;either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY;without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program;if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA            *
 ***************************************************************************/
 #include "ParisoMathObject.h"
 #include <qfile.h>
 #include <iostream>

 //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
ParisoMathObject::ParisoMathObject(){
pariso.EquationsNumber = 0;
EquationsNames.append(";Icosahedron;");
EquationsNames.append(";pseudo_Duplin;");
EquationsNames.append(";pseudo_Torus;");
EquationsNames.append(";Bugs;");
EquationsNames.append(";DifferenceSpheres;");
EquationsNames.append(";BlendSpheres;");
EquationsNames.append(";Holes;");
EquationsNames.append(";Gyroid;");
EquationsNames.append(";Diamand;");
EquationsNames.append(";Tetrahedral;");
EquationsNames.append(";DuplinCyclides;");
EquationsNames.append(";Hyperboloid;");
EquationsNames.append(";Hyperbolic;");
EquationsNames.append(";Sinus;");	
EquationsNames.append(";Octahedron;");
EquationsNames.append(";UnionSpheres;");
EquationsNames.append(";IntersectSpheres;");
EquationsNames.append(";Blobs;");
EquationsNames.append(";Virus;");
EquationsNames.append(";BlobySchwartz;");
EquationsNames.append(";Blobs_2;");
EquationsNames.append(";OrthoCircle;");	
EquationsNames.append(";CubeSphere;");
EquationsNames.append(";CubeSphere_2;");	
EquationsNames.append(";Holes_2;");
EquationsNames.append(";Virus_2;");	
EquationsNames.append(";Schwartz;");
EquationsNames.append(";Schwartz_Morph;");	
EquationsNames.append(";Blob_Morph;");
EquationsNames.append(";Torus;");	
EquationsNames.append(";TwoCylinderBlend;");
EquationsNames.append(";BlendThreeCylinder;");	
EquationsNames.append(";Sphere;");
EquationsNames.append(";RoundCube;");	
EquationsNames.append(";Toupie;");
EquationsNames.append(";Chmutov;");	
EquationsNames.append(";Chmutov_2;");
EquationsNames.append(";Clebsch;");
EquationsNames.append(";DingDong;");	
EquationsNames.append(";Trap;");
EquationsNames.append(";Cube;");
EquationsNames.append(";Drope;");	
EquationsNames.append(";Leminescape;");
EquationsNames.append(";Klein;");
EquationsNames.append(";Chain;");
EquationsNames.append(";Chain_2;");
EquationsNames.append(";TickIso;");
EquationsNames.append(";TickIso_1;");
EquationsNames.append(";CloseIso;");
EquationsNames.append(";CloseIso_1;");
EquationsNames.append(";CloseIso_2;");
EquationsNames.append(";Warning;");
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
ParisoMathObject::~ParisoMathObject(){
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
void ParisoMathObject::DrawIsoSurface(){
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
void ParisoMathObject::LoadScript (QString filename, int type){
int current = 0, currentfunction = 0, separator =0;
QString name, line, function, xlimit, ylimit, zlimit, ulimit, vlimit,
        xmin, xmax, ymin, ymax, zmin, zmax,
        umin, umax, vmin, vmax,
        Xfct, Yfct, Zfct, condition,
        Au, Bu, Cu, Duv, Euv, Fuv, comments, fctcomts, cndcomments;
static int equationsNumber=0;







//static int previousequationsNumber=0;
QFile file( filename );
if(type == 1) {
    if ( file.open( IO_ReadOnly ) ) {
        QTextStream stream( &file );
        while ( !stream.atEnd() ) {
            line = (stream.readLine()).simplifyWhiteSpace();// line of text excluding '\n'
                       if (line.contains("F():"))    currentfunction =  1;
                  else if (line.contains("[x]:"))    currentfunction =  2;
                  else if (line.contains("[y]:"))    currentfunction =  3;
                  else if (line.contains("[z]:"))    currentfunction =  4;
                  else if (line.contains("Cnd:"))    currentfunction =  5;
                  else if (line.contains("A[u]:"))   currentfunction =  6;
                  else if (line.contains("B[u]:"))   currentfunction =  7;
                  else if (line.contains("C[u]:"))   currentfunction =  8;
                  else if (line.contains("D[u,v]:")) currentfunction =  9;
                  else if (line.contains("E[u,v]:")) currentfunction = 10;
                  else if (line.contains("F[u,v]:")) currentfunction = 11;
                  else if (line.contains("#"))       currentfunction = 12;
                  else if (line.contains("/*"))      currentfunction = 13;
                  else if (line.contains("*/"))      currentfunction = 14;
                  else if (line.contains("Name:"))   currentfunction = 15;
                  else if (line.contains(";"))       currentfunction = 16;
                  else                               currentfunction = 18;
  switch(currentfunction) {
   case  1: function  = line.remove(0, 4);current = 1;break;
   case  2: xlimit    = line.remove(0, 4);current = 2;break;
   case  3: ylimit    = line.remove(0, 4);current = 3;break;
   case  4: zlimit    = line.remove(0, 4);current = 4;break;
   case  5: condition = line.remove(0, 4);current = 5;break;
   case  6: Au        = line.remove(0, 5);current = 6;break;
   case  7: Bu        = line.remove(0, 5);current = 7;break;
   case  8: Cu        = line.remove(0, 5);current = 8;break;
   case  9: Duv       = line.remove(0, 7);current = 9;break;
   case 10: Euv       = line.remove(0, 7);current =10;break;
   case 11: Fuv       = line.remove(0, 7);current =11;break;
   case 12: comments  = line+"\n";        current =12;break;
   case 13: fctcomts  = line+"\n";        current =13;break;
   case 14: fctcomts += line+"\n";        current =14;break;
   case 15: name      = line.remove(0, 5);current =15;break;
   case 16:
    // Save the equation:
    name = name.simplifyWhiteSpace();
    if( EquationsNames.contains(";"+name+";") == 0){
    pariso.EquationsNumber                      = equationsNumber + 1;
    (name != "") ? pariso.FunctionsNames[equationsNumber]= name :
    pariso.FunctionsNames[equationsNumber] = QString::number(pariso.EquationsNumber);
    EquationsNames.append(";"+pariso.FunctionsNames[equationsNumber]+";");
    pariso.FunctionsInfos[equationsNumber]      = comments;
    pariso.FunctionsEquations[equationsNumber]  = fctcomts+"\n"+(function.simplifyWhiteSpace());
    pariso.FunctionsConditions[equationsNumber] = condition;

    xlimit    = xlimit.simplifyWhiteSpace();
    separator = xlimit.find(",");
    xmin      = xlimit.left(separator);
    xmax      = xlimit.remove(xmin+",");
    pariso.xlimitinfsup[0][equationsNumber] = xmin.simplifyWhiteSpace();
    pariso.xlimitinfsup[1][equationsNumber] = xmax.simplifyWhiteSpace();

    ylimit    = ylimit.simplifyWhiteSpace();
    separator = ylimit.find(",");
    ymin      = ylimit.left(separator);
    ymax      = ylimit.remove(ymin+",");
    pariso.ylimitinfsup[0][equationsNumber] = ymin.simplifyWhiteSpace();
    pariso.ylimitinfsup[1][equationsNumber] = ymax.simplifyWhiteSpace();

    zlimit    = zlimit.simplifyWhiteSpace();
    separator = zlimit.find(",");
    zmin      = zlimit.left(separator);
    zmax      = zlimit.remove(zmin+",");
    pariso.zlimitinfsup[0][equationsNumber] = zmin.simplifyWhiteSpace();
    pariso.zlimitinfsup[1][equationsNumber] = zmax.simplifyWhiteSpace();
    equationsNumber++;
    }
	else {
/*
    QMessageBox     message;
    message.setText(tr(QString("The name \""+name+"\" is already used...")));
    message.adjustSize ();
    message.exec();
*/
	}
    current =16;
    // Init all Parameters fo new formula:
    name = comments = fctcomts = condition = "";
    xmin = xmax = ymin = ymax = zmin = zmax = "";
    xlimit = ylimit = zlimit = "";
    break;
   case 18:      if (current ==  1) function  += line;
            else if (current ==  2) xlimit    += line;
            else if (current ==  3) ylimit    += line;
            else if (current ==  4) zlimit    += line;
            else if (current ==  5) condition += line;
            else if (current ==  6) Au        += line;
            else if (current ==  7) Bu        += line;
            else if (current ==  8) Cu        += line;
            else if (current ==  9) Duv       += line;
            else if (current == 10) Euv       += line;
            else if (current == 11) Fuv       += line;
            else if (current == 12) comments  += line;
            else if (current == 13) fctcomts  += line+"\n";
            else if (current == 14) fctcomts  += line;
            else if (current == 15) name      += line;
            else if (current == 16);
            break;
                }
                      }
    file.close();
/*
    pariso.EquationsNumber = equationsNumber + 1;
    pariso.FunctionsNames[equationsNumber]      = name;
    pariso.FunctionsInfos[equationsNumber]      = comments;
    pariso.FunctionsEquations[equationsNumber]  = fctcomts+"\n"+(function.simplifyWhiteSpace());
    pariso.FunctionsConditions[equationsNumber] = condition;

    xlimit    = xlimit.simplifyWhiteSpace();
    separator = xlimit.find(",");
    xmin      = xlimit.left(separator);
    xmax      = xlimit.remove(xmin+",");
    pariso.xlimitinfsup[0][equationsNumber] = xmin.simplifyWhiteSpace();
    pariso.xlimitinfsup[1][equationsNumber] = xmax.simplifyWhiteSpace();

    ylimit    = ylimit.simplifyWhiteSpace();
    separator = ylimit.find(",");
    ymin      = ylimit.left(separator);
    ymax      = ylimit.remove(ymin+",");
    pariso.ylimitinfsup[0][equationsNumber] = ymin.simplifyWhiteSpace();
    pariso.ylimitinfsup[1][equationsNumber] = ymax.simplifyWhiteSpace();

    zlimit    = zlimit.simplifyWhiteSpace();
    separator = zlimit.find(",");
    zmin      = zlimit.left(separator);
    zmax      = zlimit.remove(zmin+",");
    pariso.zlimitinfsup[0][equationsNumber] = zmin.simplifyWhiteSpace();
    pariso.zlimitinfsup[1][equationsNumber] = zmax.simplifyWhiteSpace();
*/
    }
}









else
    if ( file.open( IO_ReadOnly ) ) {
        QTextStream stream( &file );
        while ( !stream.atEnd() ) {
            line = stream.readLine();// line of text excluding '\n'
                       if (line.contains("X():")) currentfunction = 1;
                  else if (line.contains("Y():")) currentfunction = 2;
                  else if (line.contains("Z():")) currentfunction = 3;
                  else if (line.contains("[u]:")) currentfunction = 4;
                  else if (line.contains("[v]:")) currentfunction = 5;
                  else if (!line.contains("#"))   currentfunction = 6;
                  else                            currentfunction = 7;

  switch(currentfunction) {
   case 1: Xfct    = line.remove(0, 4);current = 1;break;
   case 2: Yfct    = line.remove(0, 4);current = 2;break;
   case 3: Zfct    = line.remove(0, 4);current = 3;break;
   case 4: ulimit  = line.remove(0, 4);current = 4;break;
   case 5: vlimit  = line.remove(0, 4);current = 5;break;
   case 6:      if (current == 1) Xfct   += line;
           else if (current == 2) Yfct   += line;
           else if (current == 3) Zfct   += line;
           else if (current == 4) ulimit += line;
           else if (current == 5) vlimit += line;
                  break;
   case 7: break;
                }
                      }
    file.close();
    pariso.XFunctionsEquations[0]  = Xfct.simplifyWhiteSpace();
    pariso.YFunctionsEquations[0]  = Yfct.simplifyWhiteSpace();
    pariso.ZFunctionsEquations[0]  = Zfct.simplifyWhiteSpace();

    ulimit    = ulimit.simplifyWhiteSpace();
    separator = ulimit.find(",");
    umin      = ulimit.left(separator);
    umax      = ulimit.remove(umin+",");
    pariso.ulimitinfsup[0][0] = umin.simplifyWhiteSpace();
    pariso.ulimitinfsup[1][0] = umax.simplifyWhiteSpace();

    vlimit    = vlimit.simplifyWhiteSpace();
    separator = vlimit.find(",");
    vmin      = vlimit.left(separator);
    vmax      = vlimit.remove(vmin+",");
    pariso.vlimitinfsup[0][0] = vmin.simplifyWhiteSpace();
    pariso.vlimitinfsup[1][0] = vmax.simplifyWhiteSpace();
    }
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
void ParisoMathObject::ExecuteScript(){

};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
QString ParisoMathObject::ChangeScript(QString result, QString name, QString CND, QString* limits, QString* uservariables){
QString FinalText, isofct, comment, tmp;
int startcomment, endcomment, length;

if(limits == NULL) {
result = result.replace("[x,y]","xy");
result = result.replace("[x,z]","xz");
result = result.replace("[y,z]","yz");
result = result.replace("[y,x]","yx");
result = result.replace("[z,x]","zx");
result = result.replace("[z,y]","zy");
result = result.replace("[","");
result = result.replace("]","");
result = result.replace("f(x,y,z)=","");

startcomment = result.find("/*");
endcomment   = result.find("*/");
result = result.remove(startcomment, endcomment - startcomment +2);

return(result);
}
else {
//Name:
FinalText   += "Name: "+name+"\n";
// User defined variables:
if(!(uservariables[0]== "") || !(uservariables[1]== "") || !(uservariables[2]== "") || 
   !(uservariables[3]== "") || !(uservariables[4]== "") || !(uservariables[5]== "")
  ){
FinalText   += "# User defined variables for calcul optimisation:\n";
if(uservariables[0]!="") FinalText += "A[u]: "+uservariables[0]+"\n";
if(uservariables[1]!="") FinalText += "B[u]: "+uservariables[1]+"\n";
if(uservariables[2]!="") FinalText += "C[u]: "+uservariables[2]+"\n";
if(uservariables[3]!="") FinalText += "D[u,v]: "+uservariables[3]+"\n";
if(uservariables[4]!="") FinalText += "E[u,v]: "+uservariables[4]+"\n";
if(uservariables[5]!="") FinalText += "F[u,v]: "+uservariables[5]+"\n";
FinalText +="\n";
}

// Main isosurface formulas:
//FinalText   += "# Isosurface formulas:\n";
length       = result.length();
startcomment = result.find("/*");
endcomment   = result.find("*/");

tmp          = result;
isofct       = (tmp.remove(startcomment,endcomment-startcomment+2));

tmp          = result;
comment      = tmp.remove(isofct);

if(comment  != "") FinalText    += comment+"\n";
FinalText   += "F(): "+isofct.remove("\n")+"\n";

// Domaine definition:
FinalText += "[x]: "+limits[0]+" , "+limits[1]+"\n";
FinalText += "[y]: "+limits[2]+" , "+limits[3]+"\n";
FinalText += "[z]: "+limits[4]+" , "+limits[5]+"\n";

//Condition:
if(CND != "") {
//FinalText += "#Condition:\n";
FinalText += "Cnd: "+CND+"\n";
}

FinalText += ";";
return(FinalText);
}
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
void ParisoMathObject::LookForIsosurfaceEquation(QString choix){

  if(choix == QString("Icosahedron")) {

  Isosurface[0] = QString("if( (x^2 + y^2 +z^2 < 35), 2 - (cos(x + (1+sqrt(5))/2*y) + cos(x - (1+sqrt(5))/2*y) + cos(y + (1+sqrt(5))/2*z) + cos(y - (1+sqrt(5))/2*z) + cos(z - (1+sqrt(5))/2*x) + cos(z + (1+sqrt(5))/2*x)) , 1)");
  Isosurface[1] = "-5.5";
  Isosurface[2] = "-5.5";
  Isosurface[3] = "-5.5";
  Isosurface[4] = "5.5";
  Isosurface[5] = "5.5";
  Isosurface[6] = "5.5";
    }
  else   if(choix == QString("pseudo_Duplin")) {
  Isosurface[0] = "(2^2 - 0^2 - (2 + 2.1)^2) * (2^2 - 0^2 - (2 - 2.1)^2)*(((x/0.6)/3.9)^4+(y*cos(0.575383*(x/0.6)) - z*sin(0.575383*(x/0.6)))^4+(y*sin(0.575383*(x/0.6)) + z*cos(0.575383*(x/0.6)))^4)+ 2*((2^2 - 0^2 - (2 + 2.1)^2 )*(2^2 - 0^2 - (2 - 2.1)^2)* (((x/0.6)/3.9)^2 * (y*cos(0.575383*(x/0.6)) - z*sin(0.575383*(x/0.6)))^2+((x/0.6)/3.9)^2 * (y*sin(0.575383*(x/0.6)) + z*cos(0.575383*(x/0.6)))^2+(y*cos(0.575383*(x/0.6)) - z*sin(0.575383*(x/0.6)))^2 * (y*sin(0.575383*(x/0.6)) + z*cos(0.575383*(x/0.6)))^2))+2* 2^2 *((-0^2-2^2+2^2+2.1^2)* (2 *((x/0.6)/3.9) *2+2* (y*cos(0.575383*(x/0.6)) - z*sin(0.575383*(x/0.6)))* 0-2^2)-4*0 *2.1^2 *(y*cos(0.575383*(x/0.6)) - z*sin(0.575383*(x/0.6))))*(((x/0.6)/3.9)^2+(y*cos(0.575383*(x/0.6)) - z*sin(0.575383*(x/0.6)))^2+(y*sin(0.575383*(x/0.6)) + z*cos(0.575383*(x/0.6)))^2)+ 4 * 2^4 * (2 *((x/0.6)/3.9)+0 *(y*cos(0.575383*(x/0.6)) - z*sin(0.575383*(x/0.6))))* (-2^2+0 * (y*cos(0.575383*(x/0.6)) - z*sin(0.575383*(x/0.6)))+2 * ((x/0.6)/3.9))+4* 2^4 * 2.1^2 * (y*cos(0.575383*(x/0.6)) - z*sin(0.575383*(x/0.6)))^2+2^8";
  Isosurface[1] = "-2*3.9*0.6";
  Isosurface[2] = "-2";
  Isosurface[3] = "-2";
  Isosurface[4] = "2.2*3.9*0.6";
  Isosurface[5] = "2";
  Isosurface[6] = "2";
    }
  else if(choix == QString("pseudo_Torus")) {
  Isosurface[0] = "(sqrt((x/2.7)*(x/2.7)+(y*sin(0.436332*x) + z*cos(0.436332*x))*(y*sin(0.436332*x) + z*cos(0.436332*x)))-3)^2 + (y*cos(0.436332*x) - z*sin(0.436332*x))*(y*cos(0.436332*x) - z*sin(0.436332*x)) - 1";
  Isosurface[1] = "-4*2.7";
  Isosurface[2] = "-4";
  Isosurface[3] = "-4";
  Isosurface[4] = "4*2.7";
  Isosurface[5] = "4";
  Isosurface[6] = "4";
    }
  else    if(choix == QString("Bugs")) {
  Isosurface[0] = "min( ((x*cos(0.866646*y) - z*sin(0.866646*y))-0.7)*((x*cos(0.866646*y) - z*sin(0.866646*y))-0.7) + (y/2.9)*(y/2.9) + (x*sin(0.866646*y) + z*cos(0.866646*y))*(x*sin(0.866646*y) + z*cos(0.866646*y)) - 1,  ((x*cos(0.866646*y) - z*sin(0.866646*y))+0.5)*((x*cos(0.866646*y) - z*sin(0.866646*y))+0.5) + (y/2.9)*(y/2.9) + (x*sin(0.866646*y) + z*cos(0.866646*y))*(x*sin(0.866646*y) + z*cos(0.866646*y)) - 1)";
  Isosurface[1] = "-2";
  Isosurface[2] = "-2*2.9*1";
  Isosurface[3] = "-2";
  Isosurface[4] = "2";
  Isosurface[5] = "2*2.9*1";
  Isosurface[6] = "2";
    }
  else
if(choix == QString("DifferenceSpheres")) {
  Isosurface[0] = "((x-0.7)*(x-0.7) + y*y + z*z - 1)*min( (x-0.7)*(x-0.7) + y*y + z*z - 1, (x+0.3)*(x+0.3) + y*y + z*z - 1) +0.02";
  Isosurface[1] = "-2";
  Isosurface[2] = "-1";
  Isosurface[3] = "-1";
  Isosurface[4] = "0.1";
  Isosurface[5] = "1";
  Isosurface[6] = "1";
    }
  else    if(choix == QString("BlendSpheres")) {
  Isosurface[0] = "((x-0.9)*(x-0.9) + y*y + z*z - 1)*((x+0.9)*(x+0.9) + y*y + z*z - 1) -0.3";
  Isosurface[1] = "-2";
  Isosurface[2] = "-2";
  Isosurface[3] = "-2";
  Isosurface[4] = "2";
  Isosurface[5] = "2";
  Isosurface[6] = "2";
    }

  else   if(choix == QString("Holes")) {
  Isosurface[0] = "3*(cos(x) + cos(y) + cos(z)) + 4* cos(x) * cos(y) * cos(z)";
  Isosurface[1] = "-3";
  Isosurface[2] = "-3";
  Isosurface[3] = "-3";
  Isosurface[4] = "3";
  Isosurface[5] = "3";
  Isosurface[6] = "3";
    }
  else   if(choix == QString("Gyroid")) {
  Isosurface[0] = "cos(x) * sin(y) + cos(y) * sin(z) + cos(z) * sin(x)";
  Isosurface[1] = "-4";
  Isosurface[2] = "-4";
  Isosurface[3] = "-4";
  Isosurface[4] = "4";
  Isosurface[5] = "4";
  Isosurface[6] = "4";
    }
  else   if(choix == QString("Diamand")) {
  Isosurface[0] = "sin(x) *sin(y) *sin(z) +sin(x) * cos(y) * cos(z) +cos(x) * sin(y) * cos(z) + cos(x) * cos(y) * sin(z)";
  Isosurface[1] = "-4";
  Isosurface[2] = "-4";
  Isosurface[3] = "-4";
  Isosurface[4] = "4";
  Isosurface[5] = "4";
  Isosurface[6] = "4";
    }
  else if(choix == QString("Tetrahedral")) {
  Isosurface[0] = "(x^2 + y^2 + z^2)^2 + 8*x*y*z - 10*(x^2 + y^2 + z^2) + 25";
  Isosurface[1] = "-4";
  Isosurface[2] = "-4";
  Isosurface[3] = "-4";
  Isosurface[4] = "4";
  Isosurface[5] = "4";
  Isosurface[6] = "4";
    }
  else if(choix == QString("DuplinCyclides")) {
  Isosurface[0] = "(2^2 - 0^2 - (2 + 2.1)^2) * (2^2 - 0^2 - (2 - 2.1)^2)*(x^4+y^4+z^4)+ 2*((2^2 - 0^2 - (2 + 2.1)^2 )*(2^2 - 0^2 - (2 - 2.1)^2)* (x^2 * y^2+x^2 * z^2+y^2 * z^2))+2* 2^2 *((-0^2-2^2+2^2+2.1^2)* (2 *x *2+2* y* 0-2^2)-4*0 *2.1^2 *y)*(x^2+y^2+z^2)+ 4 * 2^4 * (2 *x+0 *y)* (-2^2+0 * y+2 * x)+4* 2^4 * 2.1^2 * y^2+2^8";
  Isosurface[1] = "-2";
  Isosurface[2] = "-2";
  Isosurface[3] = "-1.3";
  Isosurface[4] = "2.2";
  Isosurface[5] = "2";
  Isosurface[6] = "1.3";
    }
  else 
  if(choix == QString("Hyperboloid")) {
  Isosurface[0] = "x^2 + y^2 - z^2 -0.3";
  Isosurface[1] = "-2";
  Isosurface[2] = "-2";
  Isosurface[3] = "-1.8";
  Isosurface[4] = "2";
  Isosurface[5] = "2";
  Isosurface[6] = "1.8";
    }
  else if(choix == QString("Hyperbolic")) {
  Isosurface[0] = "x*x + y - z*z";
  Isosurface[1] = "-1";
  Isosurface[2] = "-1";
  Isosurface[3] = "-1";
  Isosurface[4] = "1";
  Isosurface[5] = "1";
  Isosurface[6] = "1";
}
  else if(choix == QString("Sinus")) {
  Isosurface[0] = "sin(pi*((x)^2+(y)^2))/2 +z";
  Isosurface[1] = "-1";
  Isosurface[2] = "-1";
  Isosurface[3] = "-1";
  Isosurface[4] = "1";
  Isosurface[5] = "1";
  Isosurface[6] = "1";
    }

  else  if(choix == QString("Octahedron")) {
  Isosurface[0] = "abs(x)+abs(y)+abs(z) - 1";
  Isosurface[1] = "-1";
  Isosurface[2] = "-1";
  Isosurface[3] = "-1";
  Isosurface[4] = "1";
  Isosurface[5] = "1";
  Isosurface[6] = "1";
    }
  else  if(choix == QString("UnionSpheres")) {
  Isosurface[0] = "min( (x-0.7)*(x-0.7) + y*y + z*z - 1,  (x+0.5)*(x+0.5) + y*y + z*z - 1)";
  Isosurface[1] = "-2";
  Isosurface[2] = "-2";
  Isosurface[3] = "-2";
  Isosurface[4] = "2";
  Isosurface[5] = "2";
  Isosurface[6] = "2";
    }
  else  if(choix == QString("IntersectSpheres")) {
  Isosurface[0] = "max( (x-0.7)*(x-0.7) + y*y + z*z - 1,  (x+0.5)*(x+0.5) + y*y + z*z - 1)";
  Isosurface[1] = "-2";
  Isosurface[2] = "-2";
  Isosurface[3] = "-2";
  Isosurface[4] = "2";
  Isosurface[5] = "2";
  Isosurface[6] = "2";
    }
  else   if(choix == QString("Blobs")) {
  Isosurface[0] = "x^2 + y ^2 + z^2 +cos(4*x)+cos(4*y)+cos(4*z)-0.2";
  Isosurface[1] = "-2";
  Isosurface[2] = "-2";
  Isosurface[3] = "-2";
  Isosurface[4] = "2";
  Isosurface[5] = "2";
  Isosurface[6] = "2";
    }
  else   if(choix == QString("Blobs_2")) {
  Isosurface[0] = "x^2 + y ^2 + z^2 +sin(4*x) + sin(4*y) + sin(4*z) -1";
  Isosurface[1] = "-2";
  Isosurface[2] = "-2";
  Isosurface[3] = "-2";
  Isosurface[4] = "2";
  Isosurface[5] = "2";
  Isosurface[6] = "2";
    }

  else   if(choix == QString("OrthoCircle")) {
  Isosurface[0] = "((x^2 + y^2 - 1)^2 + z^2)* ((y^2 + z^2 - 1)^2 + x^2)* ((z^2 + x^2 - 1)^2 + y^2) - 0.075^2 *(1 + 3* (x^2 + y^2 + z^2))";
  Isosurface[1] = "-1.5";
  Isosurface[2] = "-1.5";
  Isosurface[3] = "-1.5";
  Isosurface[4] = "1.5";
  Isosurface[5] = "1.5";
  Isosurface[6] = "1.5";
    }

  else   if(choix == QString("CubeSphere")) {
  Isosurface[0] = " ((1/2.3)^2 *(x^2 + y^2 + z^2))^-6 + ( (1/2)^8 * (x^8 + y^8 + z^8) )^6 -1";
  Isosurface[1] = "-2";
  Isosurface[2] = "-2";
  Isosurface[3] = "-2";
  Isosurface[4] = "2";
  Isosurface[5] = "2";
  Isosurface[6] = "2";
    }
  else   if(choix == QString("CubeSphere_2")) {
  Isosurface[0] = "12 - ((1/2.3)^2 *(x^2 + y^2 + z^2))^-6 - ( (1/2)^8 * (x^8 + y^8 + z^8) )^6";
  Isosurface[1] = "-2";
  Isosurface[2] = "-2";
  Isosurface[3] = "-2";
  Isosurface[4] = "2";
  Isosurface[5] = "2";
  Isosurface[6] = "2";
    }


  else   if(choix == QString("Holes_2")) {
  Isosurface[0] = "sin(4*x) + sin(4*y) + sin(4*z)  + 4*x*y*z";
  Isosurface[1] = "-2";
  Isosurface[2] = "-2";
  Isosurface[3] = "-2";
  Isosurface[4] = "2";
  Isosurface[5] = "2";
  Isosurface[6] = "2";
    }

  else   if(choix == QString("Virus_2")) {
  Isosurface[0] = "cos(x) + cos(y) + cos(z) - 1";
  Isosurface[1] = "-4";
  Isosurface[2] = "-4";
  Isosurface[3] = "-4";
  Isosurface[4] = "4";
  Isosurface[5] = "4";
  Isosurface[6] = "4";
    }

  else   if(choix == QString("Schwartz")) {
  Isosurface[0] = "/* \n\
Author: Schwartz ... \n\
*/\n -(cos(x) + cos(y) + cos(z))";
  Isosurface[1] = "-4";
  Isosurface[2] = "-4";
  Isosurface[3] = "-4";
  Isosurface[4] = "4";
  Isosurface[5] = "4";
  Isosurface[6] = "4";
    }

  else   if(choix == QString("Schwartz_Morph")) {
  Isosurface[0] = "/* \n This example is to demonstrate the Morph effect  \n*/\n\
  -(cos(x) + cos(y) + cos(z) - t)";
  Isosurface[1] = "-4";
  Isosurface[2] = "-4";
  Isosurface[3] = "-4";
  Isosurface[4] = "4";
  Isosurface[5] = "4";
  Isosurface[6] = "4";
    }

  else   if(choix == QString("Blob_Morph")) {
  Isosurface[0] = "/* \n This example is to demonstrate the Morph effect  \n*/\n\
  ((x-0.9*2*t)*(x-0.9*2*t)+y*y+z*z-1)*((x+0.9*2*t)*(x+0.9*2*t)+y*y+z*z -1)-0.3";
  Isosurface[1] = "-3";
  Isosurface[2] = "-2";
  Isosurface[3] = "-2";
  Isosurface[4] = "3";
  Isosurface[5] = "2";
  Isosurface[6] = "2";
    }

  else   if(choix == QString("Torus")) {
  Isosurface[0] = "(sqrt(x*x+y*y)-3)^2 + z*z - 1";
  Isosurface[1] = "-4";
  Isosurface[2] = "-4";
  Isosurface[3] = "-1";
  Isosurface[4] = "4";
  Isosurface[5] = "4";
  Isosurface[6] = "1";
    }
   else   if(choix == QString("TwoCylinderBlend")) {
  Isosurface[0] = "(x^2 + y^2 - 1) * ( x^2 + z^2 - 1) - 1";
  Isosurface[1] = "-3";
  Isosurface[2] = "-3";
  Isosurface[3] = "-3";
  Isosurface[4] = "3";
  Isosurface[5] = "3";
  Isosurface[6] = "3";
    }
  else   if(choix == QString("BlendThreeCylinder")) {
  Isosurface[0] = "(x^2 + y^2 - 1) * ( x^2 + z^2 - 1)* ( y^2 + z^2 - 1) - 1";
  Isosurface[1] = "-3";
  Isosurface[2] = "-3";
  Isosurface[3] = "-3";
  Isosurface[4] = "3";
  Isosurface[5] = "3";
  Isosurface[6] = "3";
    }
  else   if(choix == QString("Sphere")) {
  Isosurface[0] = "x*x + y*y + z*z - 1";
  Isosurface[1] = "-1";
  Isosurface[2] = "-1";
  Isosurface[3] = "-1";
  Isosurface[4] = "1";
  Isosurface[5] = "1";
  Isosurface[6] = "1";
    }
  else   if(choix == QString("RoundCube")) {
  Isosurface[0] = "x^4 + y^4 + z^4 - (x^2 + y^2 + z^2)";
  Isosurface[1] = "-2";
  Isosurface[2] = "-2";
  Isosurface[3] = "-2";
  Isosurface[4] = "2";
  Isosurface[5] = "2";
  Isosurface[6] = "2";
    }
  else   if(choix == QString("Toupie")) {
  Isosurface[0] = "(sqrt(x*x+y*y)-3)^3 + z*z - 1";
  Isosurface[1] = "-4";
  Isosurface[2] = "-4";
  Isosurface[3] = "-6";
  Isosurface[4] = "4";
  Isosurface[5] = "4";
  Isosurface[6] = "6";
    }
  else   if(choix == QString("Chmutov")) {
  Isosurface[0] = "x^4 + y^4 + z^4 - (x^2 + y^2 + z^2-0.3)";
  Isosurface[1] = "-1.5";
  Isosurface[2] = "-1.5";
  Isosurface[3] = "-1.5";
  Isosurface[4] = "1.5";
  Isosurface[5] = "1.5";
  Isosurface[6] = "1.5";
    }
      else   if(choix == QString("Chmutov_2")) {
  Isosurface[0] = "2*(x^2*(3-4*x^2)^2+y^2*(3-4*y^2)^2+z^2*(3-4*z^2)^2) -3";
  Isosurface[1] = "-1.3";
  Isosurface[2] = "-1.3";
  Isosurface[3] = "-1.3";
  Isosurface[4] = "1.3";
  Isosurface[5] = "1.3";
  Isosurface[6] = "1.3";
    }
      else   if(choix == QString("Clebsch")) {
  Isosurface[0] = "81*(x^3+y^3+z^3)-189*(x^2*y+x^2*z+y^2*x+y^2*z+z^2*x+z^2*y) +54*x*y*z+126*(x*y+x*z+y*z)-9*(x^2+y^2+z^2)-9*(x+y+z)+1";
  Isosurface[1] = "-1";
  Isosurface[2] = "-1";
  Isosurface[3] = "-1";
  Isosurface[4] = "1";
  Isosurface[5] = "1";
  Isosurface[6] = "1";
    }
   else   if(choix == QString("DingDong")) {
  Isosurface[0] = "x^2 +y^2 -(1-z)*z^2";
  Isosurface[1] = "-1.5";
  Isosurface[2] = "-1.5";
  Isosurface[3] = "-1";
  Isosurface[4] = "1.5";
  Isosurface[5] = "1.5";
  Isosurface[6] = "1";
    }
  else   if(choix == QString("Trap")) {
  Isosurface[0] = "(x^8 + z^30 + y^8 - (x^4 + z^50 + y^4 -0.3))*(x^2 + y^2 + z^2 -0.5)";
  Isosurface[1] = "-1.2";
  Isosurface[2] = "-1.3";
  Isosurface[3] = "-1.5";
  Isosurface[4] = "1.2";
  Isosurface[5] = "1.3";
  Isosurface[6] = "1.5";
    }
 else   if(choix == QString("Cube")) {
  Isosurface[0] = "x^100 + y^100 + z^100 -1";
  Isosurface[1] = "-2";
  Isosurface[2] = "-2";
  Isosurface[3] = "-2";
  Isosurface[4] = "2";
  Isosurface[5] = "2";
  Isosurface[6] = "2";
    }

  else   if(choix == QString("Drope")) {
  Isosurface[0] = "z - 4*x*exp(-x^2-y^2)";
  Isosurface[1] = "-2";
  Isosurface[2] = "-2";
  Isosurface[3] = "-1.7";
  Isosurface[4] = "2";
  Isosurface[5] = "2";
  Isosurface[6] = "1.7";
    }

  else   if(choix == QString("Leminescape")) {
  Isosurface[0] = "4*x^2*(x^2+y^2+z^2+z)+y^2*(y^2+z^2-1)";
  Isosurface[1] = "-0.5";
  Isosurface[2] = "-1";
  Isosurface[3] = "-1";
  Isosurface[4] = "0.5";
  Isosurface[5] = "1";
  Isosurface[6] = "1";
    }

  else   if(choix == QString("Klein")) {
  Isosurface[0] = "(x^2+y^2+z^2+2*y-1)*((x^2+y^2+z^2-2*y-1)^2-8*z^2)+16*x*z*(x^2+y^2+z^2-2*y-1)";
  Isosurface[1] = "-3";
  Isosurface[2] = "-3.1";
  Isosurface[3] = "-4";
  Isosurface[4] = "3";
  Isosurface[5] = "3.1";
  Isosurface[6] = "4";
    }
  else   if(choix == QString("Chain_2")) {
  Isosurface[0] = "/* \n By replacing \":\" by the operator \"*\", we obtain  ONE unique isosurface composed of six Torus \n */ \n\
((sqrt(x*x+y*y)-3)^2 + z*z - 0.4) *\n\
((sqrt((x-4.5)*(x-4.5)+z*z)-3)^2 + y*y - 0.4) *\n\
((sqrt((x+4.5)*(x+4.5)+z*z)-3)^2 + y*y - 0.4 ) *\n\
((sqrt((y+4.5)*(y+4.5)+z*z)-3)^2 + x*x - 0.4 ) *\n\
((sqrt((y-4.5)*(y-4.5)+z*z)-3)^2 + x*x - 0.4 ) *\n\
((sqrt(x*x+y*y)-5)^2 + z*z - 0.4)";
  Isosurface[1] = "-8.2";
  Isosurface[2] = "-8.2";
  Isosurface[3] = "-4";
  Isosurface[4] = "8.2";
  Isosurface[5] = "8.2";
  Isosurface[6] = "4";
    }
  else   if(choix == QString("Chain")) {
  Isosurface[0] = "/* \n Another example made by six independants Isosurfaces (Torus) \n */ \n\
((sqrt(x*x+y*y)-3)^2 + z*z - 0.4) :\n\
((sqrt((x-4.5)*(x-4.5)+z*z)-3)^2 + y*y - 0.4) :\n\
((sqrt((x+4.5)*(x+4.5)+z*z)-3)^2 + y*y - 0.4 ) :\n\
((sqrt((y+4.5)*(y+4.5)+z*z)-3)^2 + x*x - 0.4 ) :\n\
((sqrt((y-4.5)*(y-4.5)+z*z)-3)^2 + x*x - 0.4 ) :\n\
((sqrt(x*x+y*y)-5)^2 + z*z - 0.4) :";
  Isosurface[1] = "-8.2";
  Isosurface[2] = "-8.2";
  Isosurface[3] = "-4";
  Isosurface[4] = "8.2";
  Isosurface[5] = "8.2";
  Isosurface[6] = "4";
    }
  else   if(choix == QString("Virus")) {
  Isosurface[0] = "/* \n This example was obtained by using the above formula ! \n */ \n\
  -(x^2 + y ^2 + z^2) +cos(5*x)*cos(5*y)*cos(5*z)+0.215";
  Isosurface[1] = "-.8";
  Isosurface[2] = "-.8";
  Isosurface[3] = "-.8";
  Isosurface[4] = ".8";
  Isosurface[5] = ".8";
  Isosurface[6] = ".8";
    }
  else   if(choix == QString("BlobySchwartz")) {
  Isosurface[0] = "/* \n We can even obtain a smoothly closed Schwartz Isosurface... \n */ \n\
  -(x^2 + y ^2 + z^2) +cos(5*x)+cos(5*y)+cos(5*z) -.1";
  Isosurface[1] = "-2";
  Isosurface[2] = "-2";
  Isosurface[3] = "-2";
  Isosurface[4] = "2";
  Isosurface[5] = "2";
  Isosurface[6] = "2";
    }
  else if(choix == QString("Warning")) {
  Isosurface[0] = "/*\n This Example is to show how to draw multiple Isosurfaces by using the separator \":\"\n*/\n\
\
-x^2 + y^2/3 - z^2 +0.1 :\n\
x^2/3 - y^2 - z^2 +0.1 :\n\
-x^2 - y^2 + z^2/3 +0.1 :\n\
x^2 + y^2 + z^2 - 2 :";
  Isosurface[1] = "-4";
  Isosurface[2] = "-4";
  Isosurface[3] = "-4";
  Isosurface[4] = "4";
  Isosurface[5] = "4";
  Isosurface[6] = "4";
    }
  else if(choix == QString("TickIso")) {
  Isosurface[0] = "/*\n\
To make  \"tick\" isosurfaces, you can use this general  method:\n\
G[x, y, z] = F[x, y, z] * F[x - (T/R)*dF()/dx, y - (T/R)*dF()/dy, z - (T/R)*df()/dz]\n\
dF()/dx == partial derivative of F() to the variable x.\n\
F[x, y, z]  : The original Isosurface formula.\n\
G[x, y, z] : The new Isosurface formula.\n\
R = sqrt[(dF()/dx)^2 + (dF()/dy)^2 + (dF()/dz)^2]\n\
T = Tickness value\n\
Applied to Schwartz (F[]= cos(x) + cos(y) + cos(z) , T = 1/2) ,we obtain the following formula:\n\
*/\n\
(cos(x) + cos(y) + cos(z))*(\n\
(\n\
cos(x + sin(x)/(2*sqrt(sin(x)^2 + sin(y)^2 + sin(z)^2))) +\n\
cos(y + sin(y)/(2*sqrt(sin(x)^2 + sin(y)^2 + sin(z)^2))) +\n\
cos(z + sin(z)/(2*sqrt(sin(x)^2 + sin(y)^2 + sin(z)^2)))\n\
)\n\
)";
  Isosurface[1] = "-4";
  Isosurface[2] = "-4";
  Isosurface[3] = "-4";
  Isosurface[4] = "4";
  Isosurface[5] = "4";
  Isosurface[6] = "4";
    }
  else if(choix == QString("CloseIso")) {
  Isosurface[0] = "/*\n\
To make a closed Isosurface, you can use the \"if\" instruction like in this example with Schwartz :\n\
if(\n\
(x^10 + y^10 +z^10 < 200000),   // We use a Cube as a condition\n\
-(cos(x) + cos(y) + cos(z) ) ,           // Schwartz\n\
(x^10 + y^10 +z^10 - 200000 )     // Cube\n\
*/\n\
if((x^10 + y^10 +z^10 < 200000),\n\
-(cos(x) + cos(y) + cos(z) ) ,\n\
(x^10 + y^10 +z^10 - 200000))";
  Isosurface[1] = "-4";
  Isosurface[2] = "-4";
  Isosurface[3] = "-4";
  Isosurface[4] = "4";
  Isosurface[5] = "4";
  Isosurface[6] = "4";
    }
  else if(choix == QString("CloseIso_1")) {
  Isosurface[0] = "/*\n\
Another closed isosurface but in this case we consider the outside volume\n\
delimited by the Schwartz surface.\n\
The \"outside\" volume is defined by deleting the signe \"-\"\n\
*/\n\
if((x^10 + y^10 +z^10 < 100000), (cos(x) + cos(y) + cos(z) ) , (x^10 + y^10 +z^10 - 100000))";
  Isosurface[1] = "-4";
  Isosurface[2] = "-4";
  Isosurface[3] = "-4";
  Isosurface[4] = "4";
  Isosurface[5] = "4";
  Isosurface[6] = "4";
    }
  else if(choix == QString("CloseIso_2")) {
  Isosurface[0] = "/*\n\
And now, to make a tick and closed Schwartz Isosurface, we use the two formulas described above :\n\
*/\n\
if((x^10 + y^10 +z^10 < 3*(3.5^10)),\n\
(cos(x) + cos(y) + cos(z))*((cos(x + sin(x)/(2*sqrt(sin(x)^2 + sin(y)^2 + sin(z)^2))) +cos(y + sin(y)/(2*sqrt(sin(x)^2 + sin(y)^2 + sin(z)^2))) +cos(z + sin(z)/(2*sqrt(sin(x)^2 + sin(y)^2 + sin(z)^2))))) ,\n\
(x^10 + y^10 +z^10 - 3*(3.5^10)))";
  Isosurface[1] = "-4";
  Isosurface[2] = "-4";
  Isosurface[3] = "-4";
  Isosurface[4] = "4";
  Isosurface[5] = "4";
  Isosurface[6] = "4";
    }
  else if(choix == QString("ChmutySchwartz")) {
  Isosurface[0] = "/*\n\
We used Schwartz formula to make a parametrable Chmutov-like  isosurface:\n\
-------------- ChmutySchwartz ------------\n\
(x^N + y ^N + z^N) - (cos(m*7*x) + cos(n*7*y) + cos(k*7*z)) + l\n\
------------------------------------------\n\
N : Even integer > 4 --> Sharpness of edges.\n\
n, m, k : integers --> number of holes.\n\
l : Real number [-3,1] --> Thickness\n\
*/\n\
(x^16 + y ^16 + z^16 ) -(cos(7*x) +cos(7*y) +cos(7*z)) -.1";
  Isosurface[1] = "-1.1";
  Isosurface[2] = "-1.1";
  Isosurface[3] = "-1.1";
  Isosurface[4] = "1.1";
  Isosurface[5] = "1.1";
  Isosurface[6] = "1.1";
    }

  else{
  int i, currentIso=0;
  for(i=0;i<pariso.EquationsNumber;i++)
   if(choix == pariso.FunctionsNames[i]) currentIso = i;
  Isosurface[0] = pariso.FunctionsEquations[currentIso];
  Isosurface[1] = pariso.xlimitinfsup[0][currentIso];
  Isosurface[2] = pariso.ylimitinfsup[0][currentIso];
  Isosurface[3] = pariso.zlimitinfsup[0][currentIso];
  Isosurface[4] = pariso.xlimitinfsup[1][currentIso];
  Isosurface[5] = pariso.ylimitinfsup[1][currentIso];
  Isosurface[6] = pariso.zlimitinfsup[1][currentIso];
  }


};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
void ParisoMathObject::LookForParametricEquation(QString choix){

                        if(choix == QString("Hurricane")) {

  Parametric[0] = "1 * (2*cosh(v/2)*cos(u) * cos((2.1 * (2*cosh(v/2)*sin(u) * sin((2*cosh(v/2)*cos(u) - -5.01836)*2*pi*0/10.0367) + 2*(v) * cos((2*cosh(v/2)*cos(u) - -5.01836)*2*pi*0/10.0367))   - -13.1947)*2*pi*1.5/26.3894) - 2.1 * (2*cosh(v/2)*sin(u) * cos((2*cosh(v/2)*cos(u) - -5.01836)*2*pi*0/10.0367) - 2*(v) * sin((2*cosh(v/2)*cos(u) - -5.01836)*2*pi*0/10.0367))   * sin((2.1 * (2*cosh(v/2)*sin(u) * sin((2*cosh(v/2)*cos(u) - -5.01836)*2*pi*0/10.0367) + 2*(v) * cos((2*cosh(v/2)*cos(u) - -5.01836)*2*pi*0/10.0367))   - -13.1947)*2*pi*1.5/26.3894))";

  Parametric[1] = "1 * (2*cosh(v/2)*cos(u) * sin((2.1 * (2*cosh(v/2)*sin(u) * sin((2*cosh(v/2)*cos(u) - -5.01836)*2*pi*0/10.0367) + 2*(v) * cos((2*cosh(v/2)*cos(u) - -5.01836)*2*pi*0/10.0367))   - -13.1947)*2*pi*1.5/26.3894) + 2.1 * (2*cosh(v/2)*sin(u) * cos((2*cosh(v/2)*cos(u) - -5.01836)*2*pi*0/10.0367) - 2*(v) * sin((2*cosh(v/2)*cos(u) - -5.01836)*2*pi*0/10.0367))   * cos((2.1 * (2*cosh(v/2)*sin(u) * sin((2*cosh(v/2)*cos(u) - -5.01836)*2*pi*0/10.0367) + 2*(v) * cos((2*cosh(v/2)*cos(u) - -5.01836)*2*pi*0/10.0367))   - -13.1947)*2*pi*1.5/26.3894)) ";

  Parametric[2] = "2.1 * (2*cosh(v/2)*sin(u) * sin((2*cosh(v/2)*cos(u) - -5.01836)*2*pi*0/10.0367) + 2*(v) * cos((2*cosh(v/2)*cos(u) - -5.01836)*2*pi*0/10.0367))  ";
  Parametric[3] = "-pi";
  Parametric[4] = "pi";
  Parametric[5] = "-pi";
  Parametric[6] = "pi";
    }
               else         if(choix == QString("Pseudo_Torus")) {

  Parametric[0] = "(1+ 0.5*cos(u))*cos(v)";

  Parametric[1] = "0.632456 * ((1+ 0.5*cos(u))*sin(v) * cos(((1+ 0.5*cos(u))*cos(v) - -1.5)*2*pi*0.9/3) - 0.5*sin(u) * sin(((1+ 0.5*cos(u))*cos(v) - -1.5)*2*pi*0.9/3))  ";

  Parametric[2] = " 0.632456 * ((1+ 0.5*cos(u))*sin(v) * sin(((1+ 0.5*cos(u))*cos(v) - -1.5)*2*pi*0.9/3) + 0.5*sin(u) * cos(((1+ 0.5*cos(u))*cos(v) - -1.5)*2*pi*0.9/3))";

  Parametric[3] = "0";
  Parametric[4] = "2*pi";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";

    }

            else     if(choix == QString("Pseudo_Cube")) {

  Parametric[0] = "0.848528 * (cos(u)*cos(v)*(abs(cos(4*u/4))^100 + abs(sin(4*u/4))^100)^(-1/100)*(abs(cos(4*v/4))^100 + abs(sin(4*v/4))^100)^(-1/100) * cos((1.6*(sin(u)*(abs(cos(4*u/4))^100 + abs(sin(4*u/4))^100)^(-1/100)) - -1.6)*2*pi*0.3/3.2) - cos(u)*sin(v)*(abs(cos(4*u/4))^100 + abs(sin(4*u/4))^100)^(-1/100)*(abs(cos(4*v/4))^100 + abs(sin(4*v/4))^100)^(-1/100) * sin((1.6*(sin(u)*(abs(cos(4*u/4))^100 + abs(sin(4*u/4))^100)^(-1/100)) - -1.6)*2*pi*0.3/3.2))  ";

  Parametric[1] = "0.848528 * (cos(u)*cos(v)*(abs(cos(4*u/4))^100 + abs(sin(4*u/4))^100)^(-1/100)*(abs(cos(4*v/4))^100 + abs(sin(4*v/4))^100)^(-1/100) * sin((1.6*(sin(u)*(abs(cos(4*u/4))^100 + abs(sin(4*u/4))^100)^(-1/100)) - -1.6)*2*pi*0.3/3.2) + cos(u)*sin(v)*(abs(cos(4*u/4))^100 + abs(sin(4*u/4))^100)^(-1/100)*(abs(cos(4*v/4))^100 + abs(sin(4*v/4))^100)^(-1/100) * cos((1.6*(sin(u)*(abs(cos(4*u/4))^100 + abs(sin(4*u/4))^100)^(-1/100)) - -1.6)*2*pi*0.3/3.2))  ";
  Parametric[2] = "1.6*(sin(u)*(abs(cos(4*u/4))^100 + abs(sin(4*u/4))^100)^(-1/100))";
  Parametric[3] = "-pi/2";
  Parametric[4] = "pi/2";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";

    }

                else        if(choix == QString("Pseudo_Hexagon")) {

  Parametric[0] = "1.7*(cos(u)*cos(v)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)*(abs(cos(6*v/4))^400 + abs(sin(6*v/4))^400)^(-1/1000))";

  Parametric[1] = "0.743482 * (1.5*(cos(u)*sin(v)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)*(abs(cos(6*v/4))^400 + abs(sin(6*v/4))^400)^(-1/1000)) * cos((1.7*(cos(u)*cos(v)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)*(abs(cos(6*v/4))^400 + abs(sin(6*v/4))^400)^(-1/1000)) - -1.7)*2*pi*0.3/3.4) - 0.7*(sin(u)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)) * sin((1.7*(cos(u)*cos(v)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)*(abs(cos(6*v/4))^400 + abs(sin(6*v/4))^400)^(-1/1000)) - -1.7)*2*pi*0.3/3.4))  ";

  Parametric[2] = "0.743482 * (1.5*(cos(u)*sin(v)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)*(abs(cos(6*v/4))^400 + abs(sin(6*v/4))^400)^(-1/1000)) * sin((1.7*(cos(u)*cos(v)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)*(abs(cos(6*v/4))^400 + abs(sin(6*v/4))^400)^(-1/1000)) - -1.7)*2*pi*0.3/3.4) + 0.7*(sin(u)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)) * cos((1.7*(cos(u)*cos(v)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)*(abs(cos(6*v/4))^400 + abs(sin(6*v/4))^400)^(-1/1000)) - -1.7)*2*pi*0.3/3.4))";

  Parametric[3] = "-pi/2";
  Parametric[4] = "pi/2";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }


             else           if(choix == QString("Pseudo_Cone")) {

  Parametric[0] = "u*cos(v)";
  Parametric[1] = "0.848528 * (u*sin(v) * cos((u*cos(v) - -1)*2*pi*1/2) - u * sin((u*cos(v) - -1)*2*pi*1/2)) ";
  Parametric[2] = "0.848528 * (u*sin(v) * sin((u*cos(v) - -1)*2*pi*1/2) + u * cos((u*cos(v) - -1)*2*pi*1/2))";
  Parametric[3] = "-1";
  Parametric[4] = "1";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }


                 else       if(choix == QString("Pseudo_Helix")) {

  Parametric[0] = "0.717627 * ((1-0.1*cos(v))*cos(u) * cos(((1-0.1*cos(v))*sin(u) - -1.1)*2*pi*0.2/2.2) - 0.1*(sin(v) + u/1.7 -10) * sin(((1-0.1*cos(v))*sin(u) - -1.1)*2*pi*0.2/2.2))  ";
  Parametric[1] = "(1-0.1*cos(v))*sin(u)";
  Parametric[2] = " 0.717627 * ((1-0.1*cos(v))*cos(u) * sin(((1-0.1*cos(v))*sin(u) - -1.1)*2*pi*0.2/2.2) + 0.1*(sin(v) + u/1.7 -10) * cos(((1-0.1*cos(v))*sin(u) - -1.1)*2*pi*0.2/2.2))  ";
  Parametric[3] = "0";
  Parametric[4] = "4*pi";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }


               else         if(choix == QString("Pseudo_Sphere")) {
  Parametric[0] = " cos(u)*cos(v)+sin((sin(u)+1)*2*pi) ";
  Parametric[1] = "cos(u)*sin(v)+cos((sin(u)+1)*2*pi) ";
  Parametric[2] = " 4*sin(u) ";
  Parametric[3] = "-pi/2";
  Parametric[4] = "pi/2";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }
             else           if(choix == QString("Pseudo_Catenoid")) {

  Parametric[0] = " 2.2*(2*cosh(v/2)*cos(u)) ";
  Parametric[1] = " 1.51166 * (2*cosh(v/2)*sin(u) * cos((2.2*(2*cosh(v/2)*cos(u)) - -11.0404)*2*pi*1/22.0513) - 1.8*(v) * sin((2.2*(2*cosh(v/2)*cos(u)) - -11.0404)*2*pi*1/22.0513)) ";
  Parametric[2] = " 1.51166 * (2*cosh(v/2)*sin(u) * sin((2.2*(2*cosh(v/2)*cos(u)) - -11.0404)*2*pi*1/22.0513) + 1.8*(v) * cos((2.2*(2*cosh(v/2)*cos(u)) - -11.0404)*2*pi*1/22.0513)) ";
  Parametric[3] = "-pi";
  Parametric[4] = "pi";
  Parametric[5] = "-pi";
  Parametric[6] = "pi";
    }

             else           if(choix == QString("Prism")) {
  Parametric[0] = "cos(u)*cos(v)*(abs(cos(3*v/4))^500 + abs(sin(3*v/4))^500)^(-1/260)*(abs(cos(4*u/4))^200 + abs(sin(4*u/4))^200)^(-1/200)";
  Parametric[1] = "cos(u)*sin(v)*(abs(cos(3*v/4))^500 + abs(sin(3*v/4))^500)^(-1/260)*(abs(cos(4*u/4))^200 + abs(sin(4*u/4))^200)^(-1/200)";
  Parametric[2] = "sin(u)*(abs(cos(4*u/4))^200 + abs(sin(4*u/4))^200)^(-1/200)";
  Parametric[3] = "-pi/2";
  Parametric[4] = "pi/2";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }
             else           if(choix == QString("Cube")) {
  Parametric[0] = "cos(u)*cos(v)*(abs(cos(4*u/4))^100 + abs(sin(4*u/4))^100)^(-1/100)*(abs(cos(4*v/4))^100 + abs(sin(4*v/4))^100)^(-1/100)";
  Parametric[1] = "cos(u)*sin(v)*(abs(cos(4*u/4))^100 + abs(sin(4*u/4))^100)^(-1/100)*(abs(cos(4*v/4))^100 + abs(sin(4*v/4))^100)^(-1/100)";
  Parametric[2] = "sin(u)*(abs(cos(4*u/4))^100 + abs(sin(4*u/4))^100)^(-1/100)";
  Parametric[3] = "-pi/2";
  Parametric[4] = "pi/2";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }

              else          if(choix == QString("Hexagon")) {
  Parametric[0] = "cos(u)*cos(v)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)*(abs(cos(6*v/4))^400 + abs(sin(6*v/4))^400)^(-1/1000)";
  Parametric[1] = "cos(u)*sin(v)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)*(abs(cos(6*v/4))^400 + abs(sin(6*v/4))^400)^(-1/1000)";
  Parametric[2] = "sin(u)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)";
  Parametric[3] = "-pi/2";
  Parametric[4] = "pi/2";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }
             else           if(choix == QString("Cone")) {
  Parametric[0] = "cos(u)*cos(v)*(abs(cos(4*u/4))^1 + abs(sin(4*u/4))^1)^(-1/1)*(abs(cos(4*v/4))^1 + abs(sin(4*v/4))^1)^(-1/100)";
  Parametric[1] = "cos(u)*sin(v)*(abs(cos(4*u/4))^1 + abs(sin(4*u/4))^1)^(-1/1)*(abs(cos(4*v/4))^1 + abs(sin(4*v/4))^1)^(-1/100)";
  Parametric[2] = "sin(u)*(abs(cos(4*u/4))^1 + abs(sin(4*u/4))^1)^(-1/1)";
  Parametric[3] = "-pi/2";
  Parametric[4] = "pi/2";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }
            else             if(choix == QString("Diamond")) {
  Parametric[0] = "cos(u)*cos(v)*(abs(cos(4*u/4))^1 + abs(sin(4*u/4))^1)^(-1/1)*(abs(cos(4*v/4))^1 + abs(sin(4*v/4))^1)^(-1/1)";
  Parametric[1] = "cos(u)*sin(v)*(abs(cos(4*u/4))^1 + abs(sin(4*u/4))^1)^(-1/1)*(abs(cos(4*v/4))^1 + abs(sin(4*v/4))^1)^(-1/1)";
  Parametric[2] = "sin(u)*(abs(cos(4*u/4))^1 + abs(sin(4*u/4))^1)^(-1/1)";
  Parametric[3] = "-pi/2";
  Parametric[4] = "pi/2";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }

            else             if(choix == QString("Shape_10")) {
  Parametric[0] = "cos(u)*cos(v)*(abs(cos(3*u/4))^1 + abs(sin(3*u/4))^1)^(-1/1)*(abs(cos(6*v/4))^1 + abs(sin(6*v/4))^1)^(-1/1)";
  Parametric[1] = "cos(u)*sin(v)*(abs(cos(3*u/4))^1 + abs(sin(3*u/4))^1)^(-1/1)*(abs(cos(6*v/4))^1 + abs(sin(6*v/4))^1)^(-1/1)";
  Parametric[2] = "sin(u)*(abs(cos(3*u/4))^1 + abs(sin(3*u/4))^1)^(-1/1)";
  Parametric[3] = "-pi/2";
  Parametric[4] = "pi/2";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";

    }
             else            if(choix == QString("Star_7")) {

  Parametric[0] = "cos(u)*cos(v)*(abs(cos(7*v/4))^1.7 + abs(sin(7*v/4))^1.7)^(-1/0.2)*(abs(cos(7*u/4))^1.7 + abs(sin(7*u/4))^1.7)^(-1/0.2)";

  Parametric[1] = "cos(u)*sin(v)*(abs(cos(7*v/4))^1.7 + abs(sin(7*v/4))^1.7)^(-1/0.2)*(abs(cos(7*u/4))^1.7 + abs(sin(7*u/4))^1.7)^(-1/0.2)";

  Parametric[2] = "sin(u)*(abs(cos(7*u/4))^1.7 + abs(sin(7*u/4))^1.7)^(-1/0.2)";
  Parametric[3] = "-pi/2";
  Parametric[4] = "pi/2";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }
             else            if(choix == QString("Shape_8")) {
  Parametric[0] = "cos(u)*cos(v)*(abs(cos(3*u/4))^100 + abs(sin(3*u/4))^100)^(-1/100)*(abs(cos(2*v/4))^0.3 + abs(sin(2*v/4))^0.2)^(-1/0.7)";
  Parametric[1] = "cos(u)*sin(v)*(abs(cos(3*u/4))^100 + abs(sin(3*u/4))^100)^(-1/100)*(abs(cos(2*v/4))^0.3 + abs(sin(2*v/4))^0.2)^(-1/0.7)";
  Parametric[2] = "sin(u)*(abs(cos(3*u/4))^100 + abs(sin(3*u/4))^100)^(-1/100)";
  Parametric[3] = "-pi/2";
  Parametric[4] = "pi/2";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }
             else            if(choix == QString("Shape_9")) {
  Parametric[0] = "cos(u)*cos(v)*(abs(cos(2*u/4))^10 + abs(sin(2*u/4))^10)^(-1/10)*(abs(cos(8*v/4))^100 + abs(sin(8*v/4))^30)^(-1/60)"; 
  Parametric[1] = "cos(u)*sin(v)*(abs(cos(2*u/4))^10 + abs(sin(2*u/4))^10)^(-1/10)*(abs(cos(8*v/4))^100 + abs(sin(8*v/4))^30)^(-1/60)";
  Parametric[2] = "sin(u)*(abs(cos(2*u/4))^10 + abs(sin(2*u/4))^10)^(-1/10)";
  Parametric[3] = "-pi/2";
  Parametric[4] = "pi/2";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }
             else             if(choix == QString("Star")) {
  Parametric[0] = "cos(u)*cos(v)*(abs(cos(1*u/4))^0.5 + abs(sin(1*u/4))^0.5)^(-1/0.3)*(abs(cos(5*v/4))^1.7 + abs(sin(5*v/4))^1.7)^(-1/0.1)";
  Parametric[1] = "cos(u)*sin(v)*(abs(cos(1*u/4))^0.5 + abs(sin(1*u/4))^0.5)^(-1/0.3)*(abs(cos(5*v/4))^1.7 + abs(sin(5*v/4))^1.7)^(-1/0.1)";
  Parametric[2] = "sin(u)*(abs(cos(1*u/4))^0.5 + abs(sin(1*u/4))^0.5)^(-1/0.3)";
  Parametric[3] = "-pi/2";
  Parametric[4] = "pi/2";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }

             else           if(choix == QString("Implicit_Lemniscape")) {
  Parametric[0] = "cos(v)*sqrt(abs(sin(2*u)))*cos(u)";
  Parametric[1] = "cos(v)*sqrt(abs(sin(2*u)))*sin(u)";
  Parametric[2] = "x^2 - y^2 + 2*x*y*(tan(v)^2)";
  Parametric[3] = "0";
  Parametric[4] = "pi";
  Parametric[5] = "0";
  Parametric[6] = "pi";
    }
             else           if(choix == QString("Twisted_heart")) {
  Parametric[0] = "( abs(v) - abs(u) - abs(tanh((1/sqrt(2))*u)/(1/sqrt(2))) + abs(tanh((1/sqrt(2))*v)/(1/sqrt(2))) )*sin(v)";
  Parametric[1] = "( abs(v) - abs(u) - abs(tanh((1/sqrt(2))*u)/(1/sqrt(2))) - abs(tanh((1/sqrt(2))*v)/(1/sqrt(2))) )*cos(v)";
  Parametric[2] = "(1/sqrt(2))*( u^2 + v^2 ) / ( cosh((1/sqrt(2))*u)*cosh((1/sqrt(2))*v) )";
  Parametric[3] = "0";
  Parametric[4] = "pi";
  Parametric[5] = "-pi";
  Parametric[6] = "pi";
    }
             else           if(choix == QString("Folium")) {
  Parametric[0] = "cos(u) *(2*v/pi - tanh(v))";
  Parametric[1] = "cos(u + 2*pi / 3) / cosh(v)";
  Parametric[2] = "cos(u - 2*pi / 3) / cosh(v)";
  Parametric[3] = "-pi";
  Parametric[4] = "pi";
  Parametric[5] = "-pi";
  Parametric[6] = "pi";
    }
            else            if(choix == QString("Heart")) {
  Parametric[0] = "cos(u)*(4*sqrt(1-v^2)*sin(abs(u))^abs(u))";
  Parametric[1] = "sin(u) *(4*sqrt(1-v^2)*sin(abs(u))^abs(u))";
  Parametric[2] = "v";
  Parametric[3] = "-pi";
  Parametric[4] = "pi";
  Parametric[5] = "-1";
  Parametric[6] = "1";
    }
           else            if(choix == QString("Bow_Tie")) {
  Parametric[0] = "sin(u) / (sqrt(2) + sin(v))";
  Parametric[1] = "sin(u) / (sqrt(2) + sin(v))";
  Parametric[2] = "cos(u) / (1 + sqrt(2))";
  Parametric[3] = "-pi";
  Parametric[4] = "pi";
  Parametric[5] = "-pi";
  Parametric[6] = "pi";
    }

            else          if(choix == QString("Triaxial_Hexatorus")) {
  Parametric[0] = "sin(u) / (sqrt(2) + cos(v))";
  Parametric[1] = "sin(u+2*pi/3) / (sqrt(2) + cos(v+2*pi/3))";
  Parametric[2] = "cos(u-2*pi/3) / (sqrt(2) + cos(v-2*pi/3))";
  Parametric[3] = "-pi";
  Parametric[4] = "pi";
  Parametric[5] = "-pi";
  Parametric[6] = "pi";
    }

           else         if(choix == QString("Ghost_Plane")) {
  Parametric[0] = "cos(u)*sinh(v) / (cosh(v) - cos(u))";
  Parametric[1] = "cos(u)*sin(u) / (cosh(v) - cos(u))";
  Parametric[2] = "sin(u)";
  Parametric[3] = "-pi";
  Parametric[4] = "pi";
  Parametric[5] = "-pi";
  Parametric[6] = "pi";
    }

            else            if(choix == QString("Bent_Horns")) {
  Parametric[0] = "(2 + cos(u))*(v/3 - sin(v))";
  Parametric[1] = "(2 + cos(u - 2*pi / 3)) *(cos(v) - 1) ";
  Parametric[2] = "(2 + cos(u + 2*pi / 3))*(cos(v) - 1) ";
  Parametric[3] = "-pi";
  Parametric[4] = "pi";
  Parametric[5] = "-2*pi";
  Parametric[6] = "2*pi";
    }
            else            if(choix == QString("Richmond")) {
  Parametric[0] = "(-3* u - u*5 + 2*u^3*v^2 + 3*u*v^4) / (6*(u*u + v*v))";
  Parametric[1] = "(-3*v - 3*u^4*v - 2*u^2*v^3 + v^5) / (6*(u*u + v*v))";
  Parametric[2] = "u";
  Parametric[3] = "-pi";
  Parametric[4] = "pi";
  Parametric[5] = "-pi";
  Parametric[6] = "pi";
    }
            else            if(choix == QString("Kidney")) {
  Parametric[0] = "cos(u) *(3  *cos(v) - cos(3  *v))";
  Parametric[1] = "sin(u)  *(3  *cos(v) - cos(3 * v))";
  Parametric[2] = "3  *sin(v) - sin(3 * v)";
  Parametric[3] = "0";
  Parametric[4] = "2*pi";
  Parametric[5] = "-pi/2";
  Parametric[6] = "pi/2";
    }
            else            if(choix == QString("Kinky_Torus")) {
  Parametric[0] = "1/cosh(u) - cos(v)";
  Parametric[1] = "sin(v)";
  Parametric[2] = "u / pi - tanh(v)";
  Parametric[3] = "-2*pi";
  Parametric[4] = "2*pi";
  Parametric[5] = "-pi";
  Parametric[6] = "pi";
    }
             else           if(choix == QString("Snail")) {
  Parametric[0] = "u*cos(v)*sin(u)";
  Parametric[1] = "u*cos(u)*cos(v)";
  Parametric[2] = "-u*sin(v)";
  Parametric[3] = "0";
  Parametric[4] = "2";
  Parametric[5] = "-pi/2";
  Parametric[6] = "pi/2";
    }
             else           if(choix == QString("Limpet_Torus")) {
  Parametric[0] = "cos(u) / (sqrt(2) + sin(v))";
  Parametric[1] = "sin(u) / (sqrt(2) + sin(v))";
  Parametric[2] = "1 / (sqrt(2) + cos(v))";
  Parametric[3] = "-pi";
  Parametric[4] = "pi";
  Parametric[5] = "-pi";
  Parametric[6] = "pi";
    }

            else   if(choix == QString("Twisted_Triaxial")) {

  Parametric[0] = "(1-sqrt(u*u + v*v) / sqrt(2*pi*pi))*cos(u)*cos(v)+sqrt(u*u + v*v) / sqrt(2*pi*pi)*sin(u)*sin(v)";
  Parametric[1] = "(1-sqrt(u*u + v*v) / sqrt(2*pi*pi))*cos(u+2*pi/3)*cos(v+2*pi/3)+sqrt(u*u + v*v) / sqrt(2*pi*pi)*sin(u+2*pi/3)*sin(v+2*pi/3)";
  Parametric[2] = " (1-sqrt(u*u + v*v) / sqrt(2*pi*pi))*cos(u+4*pi/3)*cos(v+4*pi/3)+sqrt(u*u + v*v) / sqrt(2*pi*pi)*sin(u+4*pi/3)*sin(v+4*pi/3)";
  Parametric[3] = "-pi";
  Parametric[4] = "pi";
  Parametric[5] = "-pi";
  Parametric[6] = "pi";
    }
             else           if(choix == QString("Apple")) {
  Parametric[0] = "cos(u) *(4 + 3.8* cos(v))";
  Parametric[1] = "sin(u) *(4 + 3.8* cos(v))";
  Parametric[2] = "(cos(v) + sin(v) - 1)* (1 + sin(v)) *log(1 - pi *v / 10) + 7.5 *sin(v)";
  Parametric[3] = "0";
  Parametric[4] = "2*pi";
  Parametric[5] = "-pi";
  Parametric[6] = "pi";
    }
                        if(choix == QString("Boy")) {
  Parametric[0] = "2/3* (cos(u)* cos(2*v) + sqrt(2)* sin(u)* cos(v))* cos(u) / (sqrt(2) - sin(2*u)* sin(3*v))";
  Parametric[1] = "2/3* (cos(u)* sin(2*v) - sqrt(2)* sin(u)* sin(v))* cos(u) / (sqrt(2) - sin(2*u)* sin(3*v))";
  Parametric[2] = "sqrt(2)* cos(u)* cos(u) / (sqrt(2) - sin(2*u)* sin(3*v))";
  Parametric[3] = "0";
  Parametric[4] = "pi";
  Parametric[5] = "0";
  Parametric[6] = "pi";
    }
             else           if(choix == QString("Maeder's_Owl")) {
  Parametric[0] = "v *cos(u) - 0.5* v^2 * cos(2* u)";
  Parametric[1] = "-v *sin(u) - 0.5* v^2 * sin(2* u)";
  Parametric[2] = "4 *v^1.5 * cos(3 *u / 2) / 3";
  Parametric[3] = "0";
  Parametric[4] = "4*pi";
  Parametric[5] = "0";
  Parametric[6] = "1";
    }
             else           if(choix == QString("Cone")) {
  Parametric[0] = "u*cos(v)";
  Parametric[1] = "u*sin(v)";
  Parametric[2] = "u";
  Parametric[3] = "-1";
  Parametric[4] = "1";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }
             else           if(choix == QString("Eight")) {
  Parametric[0] = "(2 + 0.2*sin(2*pi*u))*sin(pi*v)";
  Parametric[1] = "0.2*cos(2*pi*u) *3*cos(2*pi*v)";
  Parametric[2] = "(2 + 0.2*sin(2*pi*u))*cos(pi*v)";
  Parametric[3] = "0";
  Parametric[4] = "pi/2";
  Parametric[5] = "0";
  Parametric[6] = "3*pi/4";
    }
             else           if(choix == QString("Drop")) {
  Parametric[0] = "u*cos(v)";
  Parametric[1] = "u*sin(v)";
  Parametric[2] = "exp(-u*u)*(sin(2*pi*u) - u*cos(3*v))";
  Parametric[3] = "0";
  Parametric[4] = "2";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }
             else           if(choix == QString("Plan")) {
  Parametric[0] = "u";
  Parametric[1] = "0";
  Parametric[2] = "v";
  Parametric[3] = "-1";
  Parametric[4] = "1";
  Parametric[5] = "-1";
  Parametric[6] = "1";
    }
             else           if(choix == QString("Ellipsoide")) {
  Parametric[0] = "cos(u)*cos(v)";
  Parametric[1] = "sin(u)*cos(v)";
  Parametric[2] = "sin(v)";
  Parametric[3] = "0";
  Parametric[4] = "6.2831";
  Parametric[5] = "-1.57";
  Parametric[6] = "1.5708";
    }
             else           if(choix == QString("EightSurface")) {
  Parametric[0] = "cos(u)*sin(2*v)";
  Parametric[1] = "sin(u)*sin(2*v)";
  Parametric[2] = "sin(v)";
  Parametric[3] = "0";
  Parametric[4] = "2*pi";
  Parametric[5] = "-pi/2";
  Parametric[6] = "pi/2";
    }
             else           if(choix == QString("Dini")) {
  Parametric[0] = "cos(u)*sin(v)";
  Parametric[1] = "sin(u)*sin(v)";
  Parametric[2] = "(cos(v)+log(tan(v/2))) + 0.2*u";
  Parametric[3] = "0";
  Parametric[4] = "12.4";
  Parametric[5] = "0.1";
  Parametric[6] = "2";
    }
             else           if(choix == QString("Flower")) {
  Parametric[0] = "v *cos(u) -0.5*v^2*cos(2*u)";
  Parametric[1] = "-v*sin(u) -0.5*v^2*sin(2*u)";
  Parametric[2] = "4* v^1.5 *cos(3* u / 2) / 3";
  Parametric[3] = "0";
  Parametric[4] = "4*pi";
  Parametric[5] = "0";
  Parametric[6] = "1";
    }
            else  if(choix == QString("Cosinus")) {
  Parametric[0] = "u";
  Parametric[1] = "v";
  Parametric[2] = "sin(pi*((u)^2+(v)^2))/2";
  Parametric[3] = "-1";
  Parametric[4] = "1";
  Parametric[5] = "-1";
  Parametric[6] = "1";
    }
             else   if(choix == QString("Shell")) {
  Parametric[0] = "1.2^v*(sin(u)^2 *sin(v))";
  Parametric[1] = "1.2^v*(sin(u)^2 *cos(v))";
  Parametric[2] = "1.2^v*(sin(u)*cos(u))";
  Parametric[3] = "0";
  Parametric[4] = "pi";
  Parametric[5] = "-pi/4";
  Parametric[6] = "5*pi/2";
    }
           if(choix == QString("Sphere")) {
  Parametric[0] = "cos(u)*cos(v)";
  Parametric[1] = "cos(u)*sin(v)";
  Parametric[2] = "sin(u)";
  Parametric[3] = "-pi/2";
  Parametric[4] = "pi/2";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }
             else     if(choix == QString("Steiner")) {
  Parametric[0] = "(sin(2 * u) * cos(v) * cos(v))";
  Parametric[1] = "(sin(u) * sin(2 * v))";
  Parametric[2] = "(cos(u) * sin(2 * v))";
  Parametric[3] = "-pi/2";
  Parametric[4] = "pi/2";
  Parametric[5] = "-pi/2";
  Parametric[6] = "pi/2";
    }
             else   if(choix == QString("Cross_cap")) {
  Parametric[0] = "(sin(u) * sin(2 * v) / 2)";
  Parametric[1] = "(sin(2 * u) * cos(v) * cos(v))";
  Parametric[2] = "(cos(2 * u) * cos(v) * cos(v))";
  Parametric[3] = "-pi/2";
  Parametric[4] = "pi/2";
  Parametric[5] = "-pi/2";
  Parametric[6] = "pi/2";
    }
             else     if(choix == QString("Boys")) {
  Parametric[0] = "(2/3)*(cos(u)*cos(2*v)+sqrt(2)*sin(u)*cos(v))*cos(u) /(sqrt(2) - sin(2*u)*sin(3*v))";
  Parametric[1] = "(2/3)*(cos(u)*sin(2*v)-sqrt(2)*sin(u)*sin(v))*cos(u) /(sqrt(2)-sin(2*u)*sin(3*v))";
  Parametric[2] = "sqrt(2)*cos(u)^2 / (sqrt(2) - sin(2*u)*sin(2*v))";
  Parametric[3] = "-pi/2";
  Parametric[4] = "pi/2";
  Parametric[5] = "-pi/2";
  Parametric[6] = "pi/2";
    }
             else     if(choix == QString("Torus")) {
  Parametric[0] = "(1+ 0.5*cos(u))*cos(v)";
  Parametric[1] = "(1+ 0.5*cos(u))*sin(v)";
  Parametric[2] = "0.5*sin(u)";
  Parametric[3] = "0";
  Parametric[4] = "2*pi";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }
             else    if(choix == QString("Klein")) {
  Parametric[0] = "(3*(1+sin(v)) + 2*(1-cos(v)/2)*cos(u))*cos(v)";
  Parametric[1] = "(4+2*(1-cos(v)/2)*cos(u))*sin(v)";
  Parametric[2] = "-2*(1-cos(v)/2) * sin(u)";
  Parametric[3] = "0";
  Parametric[4] = "2*pi";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }

             else    if(choix == QString("Moebius")) {
  Parametric[0] = "cos(v)+u*cos(v/2)*cos(v)";
  Parametric[1] = "sin(v)+u*cos(v/2)*sin(v)";
  Parametric[2] = "u*sin(v/2)";
  Parametric[3] = "-0.4";
  Parametric[4] = "0.4";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }
          if(choix == QString("Riemann")) {
  Parametric[0] = "u*v";
  Parametric[1] = "v^2 - u^2";
  Parametric[2] = "30*u";
  Parametric[3] = "-6";
  Parametric[4] = "6";
  Parametric[5] = "-25";
  Parametric[6] = "25";
    }

             else     if(choix == QString("Klein_2")) {
  Parametric[0] = "(2 + cos(v/2)* sin(u) - sin(v/2)* sin(2 *u))* cos(v)";
  Parametric[1] = "(2 + cos(v/2)* sin(u) - sin(v/2)* sin(2 *u))* sin(v)";
  Parametric[2] = "sin(v/2)* sin(u) + cos(v/2) *sin(2* u)";
  Parametric[3] = "0";
  Parametric[4] = "2*pi";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }

             else    if(choix == QString("Henneberg")) {
  Parametric[0] = "2*sinh(u)*cos(v) -(2/3)*sinh(3*u)*cos(3*v)";
  Parametric[1] = "2*sinh(u)*sin(v) +(2/3)*sinh(3*u)*sin(3*v)";
  Parametric[2] = "2*cosh(2*u)*cos(2*v)";
  Parametric[3] = "-1";
  Parametric[4] = "1";
  Parametric[5] = "-pi/2";
  Parametric[6] = "pi/2";
    }

             else    if(choix == QString("Enneper")) {
  Parametric[0] = "u -u^3/3  + u*v^2";
  Parametric[1] = "v -v^3/3  + v*u^2";
  Parametric[2] = "u^2 - v^2";
  Parametric[3] = "-2";
  Parametric[4] = "2";
  Parametric[5] = "-2";
  Parametric[6] = "2";
    }
            else    if(choix == QString("Helix")) {
  Parametric[0] = "(1-0.1*cos(v))*cos(u)";
  Parametric[1] = "(1-0.1*cos(v))*sin(u)";
  Parametric[2] = "0.1*(sin(v) + u/1.7 -10)";
  Parametric[3] = "0";
  Parametric[4] = "4*pi";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }

            else    if(choix == QString("Hexaedron")) {
  Parametric[0] = "cos(v)^3*cos(u)^3";
  Parametric[1] = "sin(v)^3*cos(u)^3";
  Parametric[2] = "sin(u)^3";
  Parametric[3] = "-1.3";
  Parametric[4] = "1.3";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }
            else     if(choix == QString("Sphere_1")) {
  Parametric[0] = "cos(u)*cos(v)";
  Parametric[1] = "cos(u)*sin(v)";
  Parametric[2] = "sin(u)";
  Parametric[3] = "-pi/2";
  Parametric[4] = "pi/2";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }
             else    if(choix == QString("Sphere_2")) {
  Parametric[0] = "cos(u)*cos(v)";
  Parametric[1] = "cos(u)*sin(v)";
  Parametric[2] = "sin(u)*sin(v)";
  Parametric[3] = "-pi/2";
  Parametric[4] = "pi/2";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }
              else    if(choix == QString("Sphere_3")) {
  Parametric[0] = "cos(u)*cos(v)";
  Parametric[1] = "cos(u)*sin(v)";
  Parametric[2] = "sin(u)*sin(v)*cos(v)";
  Parametric[3] = "-pi/2";
  Parametric[4] = "pi/2";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }
             else      if(choix == QString("Sphere_4")) {
  Parametric[0] = "cos(u)*cos(v)";
  Parametric[1] = "cos(u)*sin(v)*sin(v)";
  Parametric[2] = "sin(u)*sin(v)";
  Parametric[3] = "-pi/2";
  Parametric[4] = "0";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }
             else    if(choix == QString("Sphere_5")) {
  Parametric[0] = "cos(u)*cos(v)*sin(v)";
  Parametric[1] = "cos(u)*sin(v)*sin(v)";
  Parametric[2] = "sin(u)*sin(v)";
  Parametric[3] = "-pi/2";
  Parametric[4] = "0";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }
             else     if(choix == QString("Sphere_6")) {
  Parametric[0] = "cos(u)*cos(v)*sin(u)";
  Parametric[1] = "sin(u)";
  Parametric[2] = "sin(u)*sin(v)*sin(u)";
  Parametric[3] = "-pi/2";
  Parametric[4] = "0";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }
             else    if(choix == QString("Sphere_7")) {
  Parametric[0] = "cos(u)*cos(v)*sin(u)";
  Parametric[1] = "sin(u)*sin(v)*cos(u)";
  Parametric[2] = "sin(u)*sin(v)*sin(u)";
  Parametric[3] = "-pi/2";
  Parametric[4] = "0";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }
             else    if(choix == QString("Sphere_8")) {
  Parametric[0] = "cos(u)*cos(v)*sin(u)";
  Parametric[1] = "cos(u)*sin(v)*cos(u)";
  Parametric[2] = "sin(u)*sin(v)*sin(u)";
  Parametric[3] = "-pi/2";
  Parametric[4] = "0";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }
             else    if(choix == QString("Sphere_9")) {
  Parametric[0] = "cos(u)*cos(v)*sin(u)";
  Parametric[1] = "cos(u)*sin(v)*cos(u)*sin(v)";
  Parametric[2] = "sin(u)*sin(v)*sin(u)*sin(v)";
  Parametric[3] = "-pi/2";
  Parametric[4] = "0";
  Parametric[5] = "0";
  Parametric[6] = "pi";
    }
            else    if(choix == QString("Sphere_10")) {
  Parametric[0] = "cos(u)*cos(v)*sin(u)*sin(v)*sin(v)*sin(v)";
  Parametric[1] = "cos(u)*sin(v)*cos(u)*sin(v)";
  Parametric[2] = "sin(u)*sin(v)*sin(u)*sin(v)*cos(u)";
  Parametric[3] = "-pi/2";
  Parametric[4] = "0";
  Parametric[5] = "0";
  Parametric[6] = "pi";
    }
             else    if(choix == QString("Catalan")) {
  Parametric[0] = "u-sin(u)*cosh(v)";
  Parametric[1] = "1-cos(u)*cosh(v)";
  Parametric[2] = "4*sin(1/2*u)*sinh(v/2)";
  Parametric[3] = "-pi";
  Parametric[4] = "3*pi";
  Parametric[5] = "-2";
  Parametric[6] = "2";
    }
             else    if(choix == QString("Toupie")) {
  Parametric[0] = "(abs(u)-1)^2 * cos(v)";
  Parametric[1] = "(abs(u)-1)^2 * sin(v)";
  Parametric[2] = "u";
  Parametric[3] = "-1";
  Parametric[4] = "1";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }
             else    if(choix == QString("Bonbon")) {
  Parametric[0] = "u";
  Parametric[1] = "cos (u)*cos (v)";
  Parametric[2] = "cos (u)*sin (v)";
  Parametric[3] = "0";
  Parametric[4] = "2*pi";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }
            else    if(choix == QString("Curve")) {
  Parametric[0] = "cos(2*u)";
  Parametric[1] = "sin(3*u)";
  Parametric[2] = "cos(u)";
  Parametric[3] = "0";
  Parametric[4] = "2*pi";
  Parametric[5] = "0";
  Parametric[6] = "0";
    }
             else    if(choix == QString("Trumpet")) {
  Parametric[0] = "cos(u)*sin(v)";
  Parametric[1] = "sin(u)*sin(v)";
  Parametric[2] = "(cos(v)+log(tan(1/2*v)))";
  Parametric[3] = "0";
  Parametric[4] = "2*pi";
  Parametric[5] = "0.03";
  Parametric[6] = "2";
    }
             else    if(choix == QString("Helice_Curve")) {
  Parametric[0] = "sin(u)";
  Parametric[1] = "cos(u)";
  Parametric[2] = "(u^2)/100";
  Parametric[3] = "0";
  Parametric[4] = "6*pi";
  Parametric[5] = "0";
  Parametric[6] = "0";
    }
             else      if(choix == QString("Cresent")) {
  Parametric[0] = "(2 + sin(2* pi* u) *sin(2 *pi* v)) *sin(3* pi *v)";
  Parametric[1] = "(2 + sin(2* pi *u) *sin(2 *pi *v)) *cos(3* pi *v)";
  Parametric[2] = "cos(2* pi *u) *sin(2* pi* v) + 4 *v - 2";
  Parametric[3] = "0";
  Parametric[4] = "1";
  Parametric[5] = "0";
  Parametric[6] = "1";
    }
             else     if(choix == QString("Shoe")) {
  Parametric[0] = "u";
  Parametric[1] = "v";
  Parametric[2] = "1/3*u^3  - 1/2*v^2";
  Parametric[3] = "-2";
  Parametric[4] = "2";
  Parametric[5] = "-2";
  Parametric[6] = "2";
    }
             else    if(choix == QString("Snake")) {
  Parametric[0] = "1.2*(1 -v/(2*pi))*cos(3*v)*(1 + cos(u)) + 3*cos(3*v)";
  Parametric[1] = "1.2*(1 -v/(2*pi))*sin(3*v)*(1 + cos(u)) + 3*sin(3*v)";
  Parametric[2] = "9*v/(2*pi) + 1.2*(1 - v/(2*pi))*sin(u)";
  Parametric[3] = "0";
  Parametric[4] = "2*pi";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }
             else     if(choix == QString("Roman")) {
  Parametric[0] = "1/2*sin(2*u)*sin(v)^2";
  Parametric[1] = "1/2*sin(u)*cos(2*v)";
  Parametric[2] = "1/2*cos(u)*sin(2*v)";
  Parametric[3] = "0";
  Parametric[4] = "pi";
  Parametric[5] = "-pi/2";
  Parametric[6] = "pi/2";
    }
             else       if(choix == QString("Hyperhelicoidal")) {
  Parametric[0] = "(sinh(v)*cos(3*u))/(1+cosh(u)*cosh(v))";
  Parametric[1] = "(sinh(v)*sin(3*u))/(1+cosh(u)*cosh(v))";
  Parametric[2] = "(cosh(v)*sinh(u))/(1+cosh(u)*cosh(v))";
  Parametric[3] = "-pi";
  Parametric[4] = "pi";
  Parametric[5] = "-pi";
  Parametric[6] = "pi";
    }
             else       if(choix == QString("Horn")) {
  Parametric[0] = "(2 + u*cos(v))*sin(2*pi*u)";
  Parametric[1] = "(2 + u*cos(v))*cos(2*pi*u) + 2*u";
  Parametric[2] = "u *sin(v)";
  Parametric[3] = "0";
  Parametric[4] = "1";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }
             else      if(choix == QString("Helicoidal")) {
  Parametric[0] = "sinh(v)*sin(u)";
  Parametric[1] = "-sinh(v)*cos(u)";
  Parametric[2] = "3*u";
  Parametric[3] = "-pi";
  Parametric[4] = "pi";
  Parametric[5] = "-pi";
  Parametric[6] = "pi";
    }
             else       if(choix == QString("Catenoid")) {
  Parametric[0] = "2*cosh(v/2)*cos(u)";
  Parametric[1] = "2*cosh(v/2)*sin(u)";
  Parametric[2] = "v";
  Parametric[3] = "-pi";
  Parametric[4] = "pi";
  Parametric[5] = "-pi";
  Parametric[6] = "pi";
    }
             else     if(choix == QString("Kuen")) {
  Parametric[0] = "(2*(cos(u) + u*sin(u))*sin(v))/(1+ u^2*sin(v)^2)";
  Parametric[1] = "(2*(sin(u) - u*cos(u))*sin(v))/(1+ u^2*sin(v)^2)";
  Parametric[2] = "log(tan(1/2 *v)) + (2*cos(v))/(1+ u^2*sin(v)^2)";
  Parametric[3] = "0";
  Parametric[4] = "2*pi";
  Parametric[5] = "0.01";
  Parametric[6] = "pi-0.01";
    }
             else       if(choix == QString("Hellipticparaboloid")) {
  Parametric[0] = "v*2*cos(u)";
  Parametric[1] = "v*sin(u)";
  Parametric[2] = "v^2";
  Parametric[3] = "0";
  Parametric[4] = "2*pi";
  Parametric[5] = "0";
  Parametric[6] = "2";
    }
             else       if(choix == QString("Enneper_2")) {
  Parametric[0] = "u*cos(v)-u^3/3*cos(3*v)";
  Parametric[1] = "-u*sin(v)-u^(3)/3*sin(3*v)";
  Parametric[2] = "u^2*cos(2*v)";
  Parametric[3] = "0";
  Parametric[4] = "1.2";
  Parametric[5] = "-pi";
  Parametric[6] = "pi";
    }
             else       if(choix == QString("Stereosphere")) {
  Parametric[0] = "2.*u/(u*u+v*v+1.)";
  Parametric[1] = "2.*v/(u*u+v*v+1.)";
  Parametric[2] = "(u*u+v*v-1.)/(u*u+v*v+1.)";
  Parametric[3] = "-2";
  Parametric[4] = "2";
  Parametric[5] = "-2";
  Parametric[6] = "2";
    }
             else       if(choix == QString("Cliffordtorus")) {
  Parametric[0] = "cos(u+v)/(sqrt(2.)+cos(v-u))";
  Parametric[1] = "sin(u+v)/(sqrt(2.)+cos(v-u))";
  Parametric[2] = "sin(v-u)/(sqrt(2.)+cos(v-u))";
  Parametric[3] = "0";
  Parametric[4] = "pi";
  Parametric[5] = "0";
  Parametric[6] = "2*pi";
    }
             else       if(choix == QString("Fresnel_1")) {
  Parametric[0] = "cos(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)+pi)/3.)+0.8)";
  Parametric[1] = "sin(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)+pi)/3.)+0.8)";
  Parametric[2] = "sin(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)+pi)/3.)+0.8)";
  Parametric[3] = "0";
  Parametric[4] = "2*pi";
  Parametric[5] = "-pi/2";
  Parametric[6] = "pi/2";
    }
             else       if(choix == QString("Fresnel_2")) {
  Parametric[0] = "cos(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)-pi)/3.)+0.8)";
  Parametric[1] = "sin(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)-pi)/3.)+0.8)";
  Parametric[2] = "sin(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)-pi)/3.)+0.8)";
  Parametric[3] = "0";
  Parametric[4] = "2*pi";
  Parametric[5] = "-pi/2";
  Parametric[6] = "pi/2";
    }
             else       if(choix == QString("Breather")) {
  Parametric[0] = "(2*sqrt(0.84)*cosh(0.4*u)*(-(sqrt(0.84)*cos(v)*cos(sqrt(0.84)*v)) - sin(v)*sin(sqrt(0.84)*v)))/(0.4*((sqrt(0.84)*cosh(0.4*u))^2 + (0.4*sin(sqrt(0.84)*v))^2))";
  Parametric[1] = "(2*sqrt(0.84)*cosh(0.4*u)*(-(sqrt(0.84)*sin(v)*cos(sqrt(0.84)*v)) + cos(v)*sin(sqrt(0.84)*v)))/(0.4*((sqrt(0.84)*cosh(0.4*u))^2 + (0.4*sin(sqrt(0.84)*v))^2))";
  Parametric[2] = "-u + (2*0.84*cosh(0.4*u)*sinh(0.4*u))/(0.4*((sqrt(0.84)*cosh(0.4*u))^2 + (0.4*sin(sqrt(0.84)*v))^2))";
  Parametric[3] = "-13.2";
  Parametric[4] = "13.2";
  Parametric[5] = "-37.4";
  Parametric[6] = "37.4";
    }
};





void ParisoMathObject::Look4DParametricEquation(QString choix){

                        if(choix == QString("shell4D")) {
  Parametric[0] = "1.2^v*(sin(u)^2 *sin(v))";
  Parametric[1] = "1.2^v*(sin(u)^2 *cos(v))";
  Parametric[2] = "1.2^v*(sin(u)*cos(u))";
  Parametric[3] = "cos(u)*sinh(u)";
  Parametric[4] = "0";
  Parametric[5] = "pi";
  Parametric[6] = "-pi/4";
  Parametric[7] = "5*pi/2";
    }

                       else if(choix == QString("Curve4D")) {
  Parametric[0] = "sin(pi*u)";
  Parametric[1] = "cos(pi*u)";
  Parametric[2] = "sin(3*pi*u)";
  Parametric[3] = "cos(3*pi*u)";
  Parametric[4] = "0";
  Parametric[5] = "2";
  Parametric[6] = "1";
  Parametric[7] = "1";
    }
                       else if(choix == QString("Klein4D")) {
  Parametric[0] = "(1 +0.3*cos(2*pi*u))*cos(2*pi*v)";
  Parametric[1] = "(1+0.3*cos(2*pi*u))*cos(pi*u)*sin(2*pi*v)";
  Parametric[2] = "(1+0.3*cos(2*pi*u))*sin(pi*u)*sin(2*pi*v)";
  Parametric[3] = "cos(2*pi*u)";
  Parametric[4] = "0";
  Parametric[5] = "1";
  Parametric[6] = "0";
  Parametric[7] = "1";
    }
                       else if(choix == QString("FlatTorus4D")) {

  Parametric[0] = "sin(2*pi*u)";
  Parametric[1] = "cos(2*pi*u)";
  Parametric[2] = "sin(2*pi*v)";
  Parametric[3] = "cos(2*pi*v)";
  Parametric[4] = "0";
  Parametric[5] = "1";
  Parametric[6] = "0";
  Parametric[7] = "1";
    }

                       else if(choix == QString("LawsonHelicoidal")) {
  Parametric[0] = "cos(u)*cos(v)";
  Parametric[1] = "cos(0.7*pi/4)*cos(u)*sin(v)-sin(1.2*pi/4)*sin(u)*cos(0.5*v)";
  Parametric[2] = "sin(u)*sin(0.5*v)";
  Parametric[3] = "sin(0.7*pi/4)*cos(u)*sin(v)+cos(1.2*pi/4)*sin(u)*cos(0.5*v)";
  Parametric[4] = "0";
  Parametric[5] = "2*pi";
  Parametric[6] = "0";
  Parametric[7] = "2*pi";
    }
                       else if(choix == QString("Hyperbolichelicoidal_2")) {
  Parametric[0] = "sinh(v)*cos(4*u)";
  Parametric[1] = "sinh(v)*sin(4*u)";
  Parametric[2] = "cosh(v)*sinh(u)";
  Parametric[3] = "cosh(u)*cosh(v)";
  Parametric[4] = "-2.5";
  Parametric[5] = "2.5";
  Parametric[6] = "-4";
  Parametric[7] = "4";
    }
                       else if(choix == QString("Hopftorus4D")) {
  Parametric[0] = "cos(0.46)*cos(u+v)";
  Parametric[1] = "cos(0.46)*sin(u+v)";
  Parametric[2] = "sin(0.46)*sin(v)";
  Parametric[3] = "sin(0.46)*cos(v)";
  Parametric[4] = "0";
  Parametric[5] = "2*pi";
  Parametric[6] = "0";
  Parametric[7] = "2*pi";
    }
                        else if(choix == QString("Flower")) {
  Parametric[0] = "v *cos(u) -0.5*v^2*cos(2*u)";
  Parametric[1] = "-v*sin(u) -0.5*v^2*sin(2*u)";
  Parametric[2] = "4* v^1.5 *cos(3* u / 2) / 3";
  Parametric[3] = "cos(u)";
  Parametric[4] = "0";
  Parametric[5] = "4*pi";
  Parametric[6] = "0";
  Parametric[7] = "1";
    }

                       else if(choix == QString("Cosinus")) {
  Parametric[0] = "u";
  Parametric[1] = "v";
  Parametric[2] = "sin(t*pi*((u)^2+(v)^2))/2";
  Parametric[3] = "cos(u)";
  Parametric[4] = "-1";
  Parametric[5] = "1";
  Parametric[6] = "-1";
  Parametric[7] = "1";
    }
                      else if(choix == QString("Shell")) {
  Parametric[0] = "1.2^v*(sin(u)^2 *sin(v))";
  Parametric[1] = "1.2^v*(sin(u)^2 *cos(v))";
  Parametric[2] = "1.2^v*(sin(u)*cos(u))";
  Parametric[3] = "cos(u)";
  Parametric[4] = "0";
  Parametric[5] = "pi";
  Parametric[6] = "-pi/4";
  Parametric[7] = "5*pi/2";
    }
                     else if(choix == QString("Sphere")) {
  Parametric[0] = "cos(u)*cos(v)";
  Parametric[1] = "cos(u)*sin(v)";
  Parametric[2] = "sin(u)";
  Parametric[3] = "cos(u)";
  Parametric[4] = "-pi/2";
  Parametric[5] = "pi/2";
  Parametric[6] = "0";
  Parametric[7] = "2*pi";
    }
                     else if(choix == QString("Steiner")) {
  Parametric[0] = "(sin(2 * u) * cos(v) * cos(v))";
  Parametric[1] = "(sin(u) * sin(2 * v))";
  Parametric[2] = "(cos(u) * sin(2 * v))";
  Parametric[3] = "cos(u)";
  Parametric[4] = "-pi/2";
  Parametric[5] = "pi/2";
  Parametric[6] = "-pi/2";
  Parametric[7] = "pi/2";
    }
                    else if(choix == QString("Cross_cap")) {;
  Parametric[0] = "(sin(u) * sin(2 * v) / 2)";
  Parametric[1] = "(sin(2 * u) * cos(v) * cos(v))";
  Parametric[2] = "(cos(2 * u) * cos(v) * cos(v))";
  Parametric[3] = "cos(u)";
  Parametric[4] = "-pi/2";
  Parametric[5] = "pi/2";
  Parametric[6] = "-pi/2";
  Parametric[7] = "pi/2";
    }
                    else if(choix == QString("Boys")) {
  Parametric[0] = "(2/3)*(cos(u)*cos(2*v)+sqrt(2)*sin(u)*cos(v))*cos(u) /(sqrt(2) - sin(2*u)*sin(3*v))";
  Parametric[1] = "(2/3)*(cos(u)*sin(2*v)-sqrt(2)*sin(u)*sin(v))*cos(u) /(sqrt(2)-sin(2*u)*sin(3*v))";
  Parametric[2] = "sqrt(2)*cos(u)^2 / (sqrt(2) - sin(2*u)*sin(2*v))";
  Parametric[3] = "cos(u)";
  Parametric[4] = "-pi/2";
  Parametric[5] = "pi/2";
  Parametric[6] = "-pi/2";
  Parametric[7] = "pi/2";
    }

                    else if(choix == QString("Torus")) {
  Parametric[0] = "(1+ 0.5*cos(u))*cos(v)";
  Parametric[1] = "(1+ 0.5*cos(u))*sin(v)";
  Parametric[2] = "0.5*sin(u)";
  Parametric[3] = "cos(u)";
  Parametric[4] = "0";
  Parametric[5] = "2*pi";
  Parametric[6] = "0";
  Parametric[7] = "2*pi";
    }

                    else if(choix == QString("Klein")) {
  Parametric[0] = "(3*(1+sin(v)) + 2*(1-cos(v)/2)*cos(u))*cos(v)";
  Parametric[1] = "(4+2*(1-cos(v)/2)*cos(u))*sin(v)";
  Parametric[2] = "-2*(1-cos(v)/2) * sin(u)";
  Parametric[3] = "cos(u)";
  Parametric[4] = "0";
  Parametric[5] = "2*pi";
  Parametric[6] = "0";
  Parametric[7] = "2*pi";
    }
                    else if(choix == QString("Moebius")) {
  Parametric[0] = "cos(v)+u*cos(v/2)*cos(v)";
  Parametric[1] = "sin(v)+u*cos(v/2)*sin(v)";
  Parametric[2] = "u*sin(v/2)";
  Parametric[3] = "cos(u)";
  Parametric[4] = "-0.4";
  Parametric[5] = "0.4";
  Parametric[6] = "0";
  Parametric[7] = "2*pi";
    }
                    else if(choix == QString("Riemann")) {
  Parametric[0] = "u*v";
  Parametric[1] = "v^2 - u^2";
  Parametric[2] = "30*u";
  Parametric[3] = "cos(u)";
  Parametric[4] = "-6";
  Parametric[5] = "6";
  Parametric[6] = "-25";
  Parametric[7] = "25";
    }
                    else if(choix == QString("Klein_2")) {
  Parametric[0] = "(2 + cos(v/2)* sin(u) - sin(v/2)* sin(2 *u))* cos(v)";
  Parametric[1] = "(2 + cos(v/2)* sin(u) - sin(v/2)* sin(2 *u))* sin(v)";
  Parametric[2] = "sin(v/2)* sin(u) + cos(v/2) *sin(2* u)";
  Parametric[3] = "cos(u)";
  Parametric[4] = "0";
  Parametric[5] = "2*pi";
  Parametric[6] = "0";
  Parametric[7] = "2*pi";
    }
                    else if(choix == QString("Henneberg")) {
  Parametric[0] = "2*sinh(u)*cos(v) -(2/3)*sinh(3*u)*cos(3*v)";
  Parametric[1] = "2*sinh(u)*sin(v) +(2/3)*sinh(3*u)*sin(3*v)";
  Parametric[2] = "2*cosh(2*u)*cos(2*v)";
  Parametric[3] = "cos(u)";
  Parametric[4] = "-1";
  Parametric[5] = "1";
  Parametric[6] = "-pi/2";
  Parametric[7] = "pi/2";
    }
                     else if(choix == QString("Enneper")) {
  Parametric[0] = "u -u^3/3  + u*v^2";
  Parametric[1] = "v -v^3/3  + v*u^2";
  Parametric[2] = "u^2 - v^2";
  Parametric[3] = "cos(u)";
  Parametric[4] = "-2";
  Parametric[5] = "2";
  Parametric[6] = "-2";
  Parametric[7] = "2";
    }
                    else if(choix == QString("Helix")) {
  Parametric[0] = "(1-0.1*cos(v))*cos(u)";
  Parametric[1] = "(1-0.1*cos(v))*sin(u)";
  Parametric[2] = "0.1*(sin(v) + u/1.7 -10)";
  Parametric[3] = "cos(u)";
  Parametric[4] = "0";
  Parametric[5] = "4*pi";
  Parametric[6] = "0";
  Parametric[7] = "2*pi";
    }
                    else if(choix == QString("Hexaedron")) {
  Parametric[0] = "cos(v)^3*cos(u)^3";
  Parametric[1] = "sin(v)^3*cos(u)^3";
  Parametric[2] = "sin(u)^3";
  Parametric[3] = "cos(u)";
  Parametric[4] = "-1.3";
  Parametric[5] = "1.3";
  Parametric[6] = "0";
  Parametric[7] = "2*pi";
    }
                     else if(choix == QString("Sphere_1")) {
  Parametric[0] = "cos(u)*cos(v)";
  Parametric[1] = "cos(u)*sin(v)";
  Parametric[2] = "sin(u)";
  Parametric[3] = "cos(u)";
  Parametric[4] = "-pi/2";
  Parametric[5] = "pi/2";
  Parametric[6] = "0";
  Parametric[7] = "2*pi";
    }
                      else if(choix == QString("Catalan")) {
  Parametric[0] = "u-sin(u)*cosh(v)";
  Parametric[1] = "1-cos(u)*cosh(v)";
  Parametric[2] = "4*sin(1/2*u)*sinh(v/2)";
  Parametric[3] = "cos(u)";
  Parametric[4] = "-pi";
  Parametric[5] = "3*pi";
  Parametric[6] = "-2";
  Parametric[7] = "2";
    }
                      else if(choix == QString("Toupie")) {
  Parametric[0] = "(abs(u)-1)^2 * cos(v)";
  Parametric[1] = "(abs(u)-1)^2 * sin(v)";
  Parametric[2] = "u";
  Parametric[3] = "cos(u)";
  Parametric[4] = "-1";
  Parametric[5] = "1";
  Parametric[6] = "0";
  Parametric[7] = "2*pi";
    }
                      else if(choix == QString("Bonbon")) {
  Parametric[0] = "u";
  Parametric[1] = "cos (u)*cos (v)";
  Parametric[2] = "cos (u)*sin (v)";
  Parametric[3] = "cos(u)";
  Parametric[4] = "0";
  Parametric[5] = "2*pi";
  Parametric[6] = "0";
  Parametric[7] = "2*pi";
    }
                     else if(choix == QString("Curve")) {
  Parametric[0] = "cos(2*u)";
  Parametric[1] = "sin(3*u)";
  Parametric[2] = "cos(u)";
  Parametric[3] = "cos(u)";
  Parametric[4] = "0";
  Parametric[5] = "2*pi";
  Parametric[6] = "0";
  Parametric[7] = "0";
    }
                     else if(choix == QString("Trumpet")) {
  Parametric[0] = "cos(u)*sin(v)";
  Parametric[1] = "sin(u)*sin(v)";
  Parametric[2] = "(cos(v)+log(tan(1/2*v)))";
  Parametric[3] = "cos(u)";
  Parametric[4] = "0";
  Parametric[5] = "2*pi";
  Parametric[6] = "0.03";
  Parametric[7] = "2";
    }
                     else if(choix == QString("Helice_Curve")) {
  Parametric[0] = "sin(u)";
  Parametric[1] = "cos(u)";
  Parametric[2] = "(u^2)/100";
  Parametric[3] = "cos(u)";
  Parametric[4] = "0";
  Parametric[5] = "6*pi";
  Parametric[6] = "0";
  Parametric[7] = "0";
    }
                    else if(choix == QString("Cresent")) {
  Parametric[0] = "(2 + sin(2* pi* u) *sin(2 *pi* v)) *sin(3* pi *v)";
  Parametric[1] = "(2 + sin(2* pi *u) *sin(2 *pi *v)) *cos(3* pi *v)";
  Parametric[2] = "cos(2* pi *u) *sin(2* pi* v) + 4 *v - 2";
  Parametric[3] = "cos(u)";
  Parametric[4] = "0";
  Parametric[5] = "1";
  Parametric[6] = "0";
  Parametric[7] = "1";
    }
                    else if(choix == QString("Shoe")) {
  Parametric[0] = "u";
  Parametric[1] = "v";
  Parametric[2] = "1/3*u^3  - 1/2*v^2";
  Parametric[3] = "cos(u)";
  Parametric[4] = "-2";
  Parametric[5] = "2";
  Parametric[6] = "-2";
  Parametric[7] = "2";
    }
                    else if(choix == QString("Snake")) {
  Parametric[0] = "1.2*(1 -v/(2*pi))*cos(3*v)*(1 + cos(u)) + 3*cos(3*v)";
  Parametric[1] = "1.2*(1 -v/(2*pi))*sin(3*v)*(1 + cos(u)) + 3*sin(3*v)";
  Parametric[2] = "9*v/(2*pi) + 1.2*(1 - v/(2*pi))*sin(u)";
  Parametric[3] = "cos(u)";
  Parametric[4] = "0";
  Parametric[5] = "2*pi";
  Parametric[6] = "0";
  Parametric[7] = "2*pi";
    }
                   else  if(choix == QString("Roman")) {
  Parametric[0] = "1/2*sin(2*u)*sin(v)^2";
  Parametric[1] = "1/2*sin(u)*cos(2*v)";
  Parametric[2] = "1/2*cos(u)*sin(2*v)";
  Parametric[3] = "cos(u)";
  Parametric[4] = "0";
  Parametric[5] = "pi";
  Parametric[6] = "-pi/2";
  Parametric[7] = "pi/2";
    }
                    else if(choix == QString("Hyperhelicoidal")) {
  Parametric[0] = "(sinh(v)*cos(3*u))/(1+cosh(u)*cosh(v))";
  Parametric[1] = "(sinh(v)*sin(3*u))/(1+cosh(u)*cosh(v))";
  Parametric[2] = "(cosh(v)*sinh(u))/(1+cosh(u)*cosh(v))";
  Parametric[3] = "cos(u)";
  Parametric[4] = "-pi";
  Parametric[5] = "pi";
  Parametric[6] = "-pi";
  Parametric[7] = "pi";
    }
                    else if(choix == QString("Horn")) {
  Parametric[0] = "(2 + u*cos(v))*sin(2*pi*u)";
  Parametric[1] = "(2 + u*cos(v))*cos(2*pi*u) + 2*u";
  Parametric[2] = "u *sin(v)";
  Parametric[3] = "cos(u)";
  Parametric[4] = "0";
  Parametric[5] = "1";
  Parametric[6] = "0";
  Parametric[7] = "2*pi";
    }
                   else if(choix == QString("Helicoidal")) {
  Parametric[0] = "sinh(v)*sin(u)";
  Parametric[1] = "-sinh(v)*cos(u)";
  Parametric[2] = "3*u";
  Parametric[3] = "cos(u)";
  Parametric[4] = "-pi";
  Parametric[5] = "pi";
  Parametric[6] = "-pi";
  Parametric[7] = "pi";
    }
                    else if(choix == QString("Catenoid")) {
  Parametric[0] = "2*cosh(v/2)*cos(u)";
  Parametric[1] = "2*cosh(v/2)*sin(u)";
  Parametric[2] = "v";
  Parametric[3] = "cos(u)";
  Parametric[4] = "-pi";
  Parametric[5] = "pi";
  Parametric[6] = "-pi";
  Parametric[7] = "pi";
    }
                   else if(choix == QString("Kuen")) {
  Parametric[0] = "(2*(cos(u) + u*sin(u))*sin(v))/(1+ u^2*sin(v)^2)";
  Parametric[1] = "(2*(sin(u) - u*cos(u))*sin(v))/(1+ u^2*sin(v)^2)";
  Parametric[2] = "log(tan(1/2 *v)) + (2*cos(v))/(1+ u^2*sin(v)^2)";
  Parametric[3] = "cos(u)";
  Parametric[4] = "0";
  Parametric[5] = "2*pi";
  Parametric[6] = "0.01";
  Parametric[7] = "pi-0.01";
    }
                    else if(choix == QString("Hellipticparaboloid")) {
  Parametric[0] = "v*2*cos(u)";
  Parametric[1] = "v*sin(u)";
  Parametric[2] = "v^2";
  Parametric[3] = "cos(u)";
  Parametric[4] = "0";
  Parametric[5] = "2*pi";
  Parametric[6] = "0";
  Parametric[7] = "2";
    }
                    else if(choix == QString("Enneper_2")) {
  Parametric[0] = "u*cos(v)-u^3/3*cos(3*v)";
  Parametric[1] = "-u*sin(v)-u^(3)/3*sin(3*v)";
  Parametric[2] = "u^2*cos(2*v)";
  Parametric[3] = "cos(u)";
  Parametric[4] = "0";
  Parametric[5] = "1.2";
  Parametric[6] = "-pi";
  Parametric[7] = "pi";
    }
                    else if(choix == QString("Stereosphere")) {
  Parametric[0] = "2.*u/(u*u+v*v+1.)";
  Parametric[1] = "2.*v/(u*u+v*v+1.)";
  Parametric[2] = "(u*u+v*v-1.)/(u*u+v*v+1.)";
  Parametric[3] = "cos(u)";
  Parametric[4] = "-2";
  Parametric[5] = "2";
  Parametric[6] = "-2";
  Parametric[7] = "2";
    }
                    else if(choix == QString("Cliffordtorus")) {
  Parametric[0] = "cos(u+v)/(sqrt(2.)+cos(v-u))";
  Parametric[1] = "sin(u+v)/(sqrt(2.)+cos(v-u))";
  Parametric[2] = "sin(v-u)/(sqrt(2.)+cos(v-u))";
  Parametric[3] = "cos(u)";
  Parametric[4] = "0";
  Parametric[5] = "pi";
  Parametric[6] = "0";
  Parametric[7] = "2*pi";
    }
                    else if(choix == QString("Fresnel_1")) {
  Parametric[0] = "cos(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)+pi)/3.)+0.8)";
  Parametric[1] = "sin(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)+pi)/3.)+0.8)";
  Parametric[2] = "sin(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)+pi)/3.)+0.8)";
  Parametric[3] = "cos(u)";
  Parametric[4] = "0";
  Parametric[5] = "2*pi";
  Parametric[6] = "-pi/2";
  Parametric[7] = "pi/2";
    }
                    else if(choix == QString("Fresnel_2")) {
  Parametric[0] = "cos(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)-pi)/3.)+0.8)";
  Parametric[1] = "sin(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)-pi)/3.)+0.8)";
  Parametric[2] = "sin(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)-pi)/3.)+0.8)";
  Parametric[3] = "cos(u)";
  Parametric[4] = "0";
  Parametric[5] = "2*pi";
  Parametric[6] = "-pi/2";
  Parametric[7] = "pi/2";
    }

};




