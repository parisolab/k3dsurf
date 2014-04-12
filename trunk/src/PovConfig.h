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

#include <qmainwindow.h>
#include <qtabwidget.h>
#include <qwidget.h>
#include <qgroupbox.h>
#include <qlayout.h>
#include <qfile.h>
#include <qfiledialog.h>
#include <iostream>
#include <qlineedit.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <qpushbutton.h>
#include <qlistview.h>
#include <qspinbox.h>
#include <qcombobox.h>
#include <qheader.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "k3dsurf.h"

class PovConfig: public QMainWindow
{
    Q_OBJECT

public:
    PovConfig(k3dsurface *);
    ~PovConfig();

public slots:
    void connectcontrols();
void Include_Ini_AddButton_clicked();
void Include_Ini_RemoveButton_clicked();
void InputFileNameButton_clicked();
void Include_Header_AddButton_clicked();
void Include_Header_RemoveButton_clicked();
void Library_Path_RemoveButton_clicked();
void Declare_AddButton_clicked();
void Declare_RemoveButton_clicked();
void Test_AbortCheckbox_toggled( bool );
void Create_IniCheckbox_toggled( bool );
void OutputFileNameButton_clicked();
void Buffer_OutputCheckbox_toggled( bool );
void Output_To_FileCheckbox_toggled( bool );
void Output_File_TypeCombobox_highlighted(QString&);
void whatsThisButton_clicked();
void Butto_OK_Clicked();
void runpovray();
void InputFile_toggled();
void OutputFile_toggled();
void verbose_ok();
void ImageSizeChanged();
void whatsButton_clicked();
void povPreference();
void Pause_when_Donetoggled();
void OutPutBuffer_toggled();
void ContinueCheckBoxtoggled();
void Test_AbortCheckboxtoggled();
void Library_Path_AddButton_clicked();
void Frames_Path_clicked();

void HeightImageSizeChanged(const QString&);
void WidthImageSizeChanged(const QString&);
void Start_ColumnImageSizeChanged(const QString&);
void End_ColumnImageSizeChanged(const QString&);
void Start_RowImageSizeChanged(const QString&);
void End_RowImageSizeChanged(const QString&);
void Test_Abort_CountEditChanged(const QString&);

public :
    k3dsurface * ptr;
    QTabWidget * IniTabs;
    QWidget  * Output;
    QGroupBox *Image_SizeGp_2;
    QGridLayout *Image_SizeGp_2Layout;
    QLineEdit* WidthEdit_2;
    QLabel* WidthLabel_2;
    QLineEdit* Start_ColumnEdit_2;
    QLabel* Start_ColumnLabel_2;
    QLineEdit* End_ColumnEdit_2;
    QLabel* End_RowLabel_2;
    QLabel* End_ColumnLabel_2;
    QLineEdit* End_RowEdit_2;
    QLabel* Start_RowLabel_2;
    QLineEdit* Start_RowEdit_2;
    QLabel* HeightLabel_2;
    QVBoxLayout *layout33;
    QGridLayout *layout32;
    QLineEdit* HeightEdit_2;
    QGroupBox* Display_Relating_SettingsGp_2;
    QCheckBox* ContinueCheckbox_2;
    QCheckBox* Draw_VistasCheckbox_2;
    QCheckBox* verbosebutton;
    QCheckBox* Pause_When_DoneCheckbox_2;
    QCheckBox* Test_AbortCheckbox_2;
    QLineEdit* Test_Abort_CountEdit_2;
    QLabel* Test_Abort_CountLabel_2;
    QWidget* Parsing;
    QPushButton* InputFileNameButton_2;
    QLabel* Input_File_NameLabel_2;
    QPushButton* Include_Header_RemoveButton_2;
    QListView* Include_HeaderListview_2;
    QPushButton* Include_Header_AddButton_2;
    QListView* Library_PathListview_2;
    QPushButton* Library_Path_RemoveButton_2;
    QPushButton* Library_Path_AddButton_2;
    QListView* Include_IniListview_2;
    QPushButton* Include_Ini_RemoveButton_2;
    QPushButton* Include_Ini_AddButton_2;
    QLineEdit* Input_File_NameEdit_2;
    QWidget* File_Output;
    QGroupBox* File_OutputGp_2;
    QLineEdit* Output_File_NameEdit_2;
    QLineEdit* Buffer_SizeEdit_2;
    QSpinBox* Bits_Per_ColorSpinbox_2;
    QPushButton* OutputFileNameButton_2;
    QLabel* Output_File_TypeLabel_2;
    QLabel* Output_File_NameLabel_2;
    QLabel* Bits_Per_ColorLabel_2;
    QCheckBox* Buffer_OutputCheckbox_2;
    QCheckBox* Output_To_FileCheckbox_2;
    QComboBox* Output_File_TypeCombobox_2;
    QGridLayout *layout3_2;
    QGridLayout *layout17_3;

};
