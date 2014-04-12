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
#include "PovConfig.h"
#include <cstdlib>

     static QString        xterm="", 
            Width="200", Height="200", 
            Start_RowEdit="0", End_RowEdit="200", 
            Start_ColumnEdit="0", End_ColumnEdit="200", 
            Test_Abort_CountEdit="50",
            Pause_When_Done = "+P",
            Continue ="", 
            Output_File_NameEdit="+Oscene", FileExtension=".tga  +FT ",
            Input_File_NameEdit="+Itest.pov",
            OutPutBuffer="", IncludeHeaderFile="", LibraryPath="";
    
    static int verbose = -1, ImageSize_Field_changed =-1, testabort = 1, pausewhendone = 1,
           continuecheckbox = -1, outputfile = -1, inputfile = -1, outputbuffer = -1;
 
 PovConfig::PovConfig(k3dsurface *pointertowindow) : QMainWindow( 0, "player", WDestructiveClose | WStyle_StaysOnTop ) {
    resize(360, 280);
    setCaption( "Pov-Ray Config" );
    ptr = pointertowindow;
    //setFixedSize ( QSize(360, 280));
    IniTabs = new QTabWidget( this, "IniTabs" );
    IniTabs->setEnabled( TRUE );
    IniTabs->setGeometry( QRect( 0, 0, 360, 280 ) );
    IniTabs->setMinimumSize( QSize( 230, 250 ) );
    IniTabs->setMaximumSize( QSize( 32767, 32767 ) );

    Output = new QWidget( IniTabs, "Output" );

    Image_SizeGp_2 = new QGroupBox( Output, "Image_SizeGp_2" );
    Image_SizeGp_2->setGeometry( QRect( 20, 10, 300, 108 ) );
    Image_SizeGp_2->setFrameShape( QGroupBox::GroupBoxPanel );
    Image_SizeGp_2->setColumnLayout(0, Qt::Vertical );
    Image_SizeGp_2->layout()->setSpacing( 6 );
    Image_SizeGp_2->layout()->setMargin( 11 );
    Image_SizeGp_2Layout = new QGridLayout( Image_SizeGp_2->layout() );
    Image_SizeGp_2Layout->setAlignment( Qt::AlignTop );

    WidthEdit_2 = new QLineEdit( Image_SizeGp_2, "WidthEdit_2" );

    Image_SizeGp_2Layout->addMultiCellWidget( WidthEdit_2, 0, 0, 1, 2 );

    WidthLabel_2 = new QLabel( Image_SizeGp_2, "WidthLabel_2" );

    Image_SizeGp_2Layout->addWidget( WidthLabel_2, 0, 0 );

    Start_ColumnEdit_2 = new QLineEdit( Image_SizeGp_2, "Start_ColumnEdit_2" );

    Image_SizeGp_2Layout->addWidget( Start_ColumnEdit_2, 1, 5 );

    Start_ColumnLabel_2 = new QLabel( Image_SizeGp_2, "Start_ColumnLabel_2" );

    Image_SizeGp_2Layout->addMultiCellWidget( Start_ColumnLabel_2, 1, 1, 3, 4 );

    End_ColumnEdit_2 = new QLineEdit( Image_SizeGp_2, "End_ColumnEdit_2" );

    Image_SizeGp_2Layout->addWidget( End_ColumnEdit_2, 2, 5 );

    End_RowLabel_2 = new QLabel( Image_SizeGp_2, "End_RowLabel_2" );

    Image_SizeGp_2Layout->addMultiCellWidget( End_RowLabel_2, 2, 2, 0, 1 );

    End_ColumnLabel_2 = new QLabel( Image_SizeGp_2, "End_ColumnLabel_2" );

    Image_SizeGp_2Layout->addMultiCellWidget( End_ColumnLabel_2, 2, 2, 3, 4 );

    End_RowEdit_2 = new QLineEdit( Image_SizeGp_2, "End_RowEdit_2" );

    Image_SizeGp_2Layout->addWidget( End_RowEdit_2, 2, 2 );

    Start_RowLabel_2 = new QLabel( Image_SizeGp_2, "Start_RowLabel_2" );

    Image_SizeGp_2Layout->addMultiCellWidget( Start_RowLabel_2, 1, 1, 0, 1 );

    Start_RowEdit_2 = new QLineEdit( Image_SizeGp_2, "Start_RowEdit_2" );

    Image_SizeGp_2Layout->addWidget( Start_RowEdit_2, 1, 2 );

    HeightLabel_2 = new QLabel( Image_SizeGp_2, "HeightLabel_2" );

    Image_SizeGp_2Layout->addWidget( HeightLabel_2, 0, 3 );

    HeightEdit_2 = new QLineEdit( Image_SizeGp_2, "HeightEdit_2" );

    Image_SizeGp_2Layout->addMultiCellWidget( HeightEdit_2, 0, 0, 4, 5 );

    Display_Relating_SettingsGp_2 = new QGroupBox( Output, "Display_Relating_SettingsGp_2" );
    Display_Relating_SettingsGp_2->setGeometry( QRect( 20, 130, 300, 100 ) );

    ContinueCheckbox_2 = new QCheckBox( Display_Relating_SettingsGp_2, "ContinueCheckbox_2" );
    ContinueCheckbox_2->setGeometry( QRect( 190, 20, 101, 16 ) );
    ContinueCheckbox_2->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, ContinueCheckbox_2->sizePolicy().hasHeightForWidth() ) );
    if(continuecheckbox == 1)ContinueCheckbox_2->setChecked( TRUE );

    Draw_VistasCheckbox_2 = new QCheckBox( Display_Relating_SettingsGp_2, "Draw_VistasCheckbox_2" );
    Draw_VistasCheckbox_2->setGeometry( QRect( 190, 40, 101, 16 ) );

    verbosebutton = new QCheckBox( Display_Relating_SettingsGp_2, "verbosebutton" );
    verbosebutton->setGeometry( QRect( 10, 20, 140, 16 ) );
    if(verbose == 1)verbosebutton->setChecked( TRUE );

    Pause_When_DoneCheckbox_2 = new QCheckBox( Display_Relating_SettingsGp_2, "Pause_When_DoneCheckbox_2" );
    Pause_When_DoneCheckbox_2->setGeometry( QRect( 10, 40, 140, 16 ) );
    if(pausewhendone == 1) Pause_When_DoneCheckbox_2->setChecked( TRUE );

    Test_AbortCheckbox_2 = new QCheckBox( Display_Relating_SettingsGp_2, "Test_AbortCheckbox_2" );
    Test_AbortCheckbox_2->setGeometry( QRect( 10, 60, 110, 16 ) );
    Test_AbortCheckbox_2->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, Test_AbortCheckbox_2->sizePolicy().hasHeightForWidth() ) );
    if(testabort == 1) Test_AbortCheckbox_2->setChecked( TRUE );

    Test_Abort_CountEdit_2 = new QLineEdit( Display_Relating_SettingsGp_2, "Test_Abort_CountEdit_2" );
    Test_Abort_CountEdit_2->setGeometry( QRect( 190, 60, 80, 20 ) );
    Test_Abort_CountEdit_2->setMinimumSize( QSize( 40, 0 ) );

    Test_Abort_CountLabel_2 = new QLabel( Display_Relating_SettingsGp_2, "Test_Abort_CountLabel_2" );
    Test_Abort_CountLabel_2->setGeometry( QRect( 130, 60, 60, 16 ) );
    IniTabs->insertTab( Output, QString::fromLatin1("") );

    Parsing = new QWidget( IniTabs, "Parsing" );

    InputFileNameButton_2 = new QPushButton( Parsing, "InputFileNameButton_2" );
    InputFileNameButton_2->setGeometry( QRect( 280, 10, 30, 20 ) );
    InputFileNameButton_2->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, InputFileNameButton_2->sizePolicy().hasHeightForWidth() ) );
    InputFileNameButton_2->setMaximumSize( QSize( 30, 32767 ) );

    Input_File_NameLabel_2 = new QLabel( Parsing, "Input_File_NameLabel_2" );
    Input_File_NameLabel_2->setGeometry( QRect( 30, 10, 93, 16 ) );

    QWidget* privateLayoutWidget_33 = new QWidget( Parsing, "layout33" );
    privateLayoutWidget_33->setGeometry( QRect( 20, 30, 300, 203 ) );
    layout33 = new QVBoxLayout( privateLayoutWidget_33, 0, 0, "layout33"); 

    layout32 = new QGridLayout( 0, 1, 1, 0, 6, "layout32"); 

    Include_Header_RemoveButton_2 = new QPushButton( privateLayoutWidget_33, "Include_Header_RemoveButton_2" );

    layout32->addWidget( Include_Header_RemoveButton_2, 1, 1 );

    Include_HeaderListview_2 = new QListView( privateLayoutWidget_33, "Include_HeaderListview_2" );
    Include_HeaderListview_2->addColumn( tr( "Include Header" ) );
    Include_HeaderListview_2->header()->setClickEnabled( FALSE, Include_HeaderListview_2->header()->count() - 1 );
    Include_HeaderListview_2->setMaximumSize( QSize( 500, 75 ) );
    Include_HeaderListview_2->setResizePolicy( QListView::AutoOneFit );

    layout32->addMultiCellWidget( Include_HeaderListview_2, 0, 1, 0, 0 );

    Include_Header_AddButton_2 = new QPushButton( privateLayoutWidget_33, "Include_Header_AddButton_2" );

    layout32->addWidget( Include_Header_AddButton_2, 0, 1 );
    layout33->addLayout( layout32 );

    layout3_2 = new QGridLayout( 0, 1, 1, 1, 2, "layout3_2"); 

    Library_PathListview_2 = new QListView( privateLayoutWidget_33, "Library_PathListview_2" );
    Library_PathListview_2->addColumn( tr( "Library Path" ) );
    Library_PathListview_2->header()->setClickEnabled( FALSE, Library_PathListview_2->header()->count() - 1 );
    Library_PathListview_2->setMaximumSize( QSize( 500, 75 ) );
    Library_PathListview_2->setResizePolicy( QListView::AutoOneFit );

    layout3_2->addMultiCellWidget( Library_PathListview_2, 0, 1, 0, 0 );

    Library_Path_RemoveButton_2 = new QPushButton( privateLayoutWidget_33, "Library_Path_RemoveButton_2" );

    layout3_2->addWidget( Library_Path_RemoveButton_2, 1, 1 );

    Library_Path_AddButton_2 = new QPushButton( privateLayoutWidget_33, "Library_Path_AddButton_2" );

    layout3_2->addWidget( Library_Path_AddButton_2, 0, 1 );
    layout33->addLayout( layout3_2 );

    layout17_3 = new QGridLayout( 0, 1, 1, 0, 6, "layout17_3"); 

    Include_IniListview_2 = new QListView( privateLayoutWidget_33, "Include_IniListview_2" );
    Include_IniListview_2->addColumn( tr( "Include Ini" ) );
    Include_IniListview_2->header()->setClickEnabled( FALSE, Include_IniListview_2->header()->count() - 1 );
    Include_IniListview_2->setEnabled( FALSE );
    Include_IniListview_2->setMaximumSize( QSize( 500, 32767 ) );
    Include_IniListview_2->setResizePolicy( QListView::AutoOneFit );

    layout17_3->addMultiCellWidget( Include_IniListview_2, 0, 1, 0, 0 );

    Include_Ini_RemoveButton_2 = new QPushButton( privateLayoutWidget_33, "Include_Ini_RemoveButton_2" );
    Include_Ini_RemoveButton_2->setEnabled( FALSE );

    layout17_3->addWidget( Include_Ini_RemoveButton_2, 1, 1 );

    Include_Ini_AddButton_2 = new QPushButton( privateLayoutWidget_33, "Include_Ini_AddButton_2" );
    Include_Ini_AddButton_2->setEnabled( FALSE );

    layout17_3->addWidget( Include_Ini_AddButton_2, 0, 1 );
    layout33->addLayout( layout17_3 );

    Input_File_NameEdit_2 = new QLineEdit( Parsing, "Input_File_NameEdit_2" );
    Input_File_NameEdit_2->setGeometry( QRect( 130, 10, 121, 20 ) );
    IniTabs->insertTab( Parsing, QString::fromLatin1("") );

    File_Output = new QWidget( IniTabs, "File_Output" );

    File_OutputGp_2 = new QGroupBox( File_Output, "File_OutputGp_2" );
    File_OutputGp_2->setGeometry( QRect( 10, 10, 330, 180 ) );

    Output_File_NameEdit_2 = new QLineEdit( File_OutputGp_2, "Output_File_NameEdit_2" );
    Output_File_NameEdit_2->setGeometry( QRect( 150, 50, 100, 20 ) );

    Buffer_SizeEdit_2 = new QLineEdit( File_OutputGp_2, "Buffer_SizeEdit_2" );
    Buffer_SizeEdit_2->setEnabled( FALSE );
    Buffer_SizeEdit_2->setGeometry( QRect( 150, 140, 130, 21 ) );

    Bits_Per_ColorSpinbox_2 = new QSpinBox( File_OutputGp_2, "Bits_Per_ColorSpinbox_2" );
    Bits_Per_ColorSpinbox_2->setGeometry( QRect( 150, 110, 130, 21 ) );
    Bits_Per_ColorSpinbox_2->setMaxValue( 16 );
    Bits_Per_ColorSpinbox_2->setMinValue( 5 );

    OutputFileNameButton_2 = new QPushButton( File_OutputGp_2, "OutputFileNameButton_2" );
    OutputFileNameButton_2->setGeometry( QRect( 250, 50, 30, 20 ) );
    OutputFileNameButton_2->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, OutputFileNameButton_2->sizePolicy().hasHeightForWidth() ) );
    OutputFileNameButton_2->setMaximumSize( QSize( 30, 32767 ) );

    Output_File_TypeLabel_2 = new QLabel( File_OutputGp_2, "Output_File_TypeLabel_2" );
    Output_File_TypeLabel_2->setGeometry( QRect( 10, 80, 130, 20 ) );

    Output_File_NameLabel_2 = new QLabel( File_OutputGp_2, "Output_File_NameLabel_2" );
    Output_File_NameLabel_2->setGeometry( QRect( 10, 50, 130, 20 ) );

    Bits_Per_ColorLabel_2 = new QLabel( File_OutputGp_2, "Bits_Per_ColorLabel_2" );
    Bits_Per_ColorLabel_2->setGeometry( QRect( 10, 110, 130, 21 ) );

    Buffer_OutputCheckbox_2 = new QCheckBox( File_OutputGp_2, "Buffer_OutputCheckbox_2" );
    Buffer_OutputCheckbox_2->setGeometry( QRect( 10, 140, 130, 21 ) );

    Output_To_FileCheckbox_2 = new QCheckBox( File_OutputGp_2, "Output_To_FileCheckbox_2" );
    Output_To_FileCheckbox_2->setGeometry( QRect( 110, 20, 120, 20 ) );
    Output_To_FileCheckbox_2->setChecked( TRUE );

    Output_File_TypeCombobox_2 = new QComboBox( FALSE, File_OutputGp_2, "Output_File_TypeCombobox_2" );
    Output_File_TypeCombobox_2->setGeometry( QRect( 150, 80, 130, 27 ) );
    IniTabs->insertTab( File_Output, QString::fromLatin1("") );

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

    Image_SizeGp_2->setTitle( tr( "Image size" ) );
    QWhatsThis::add( Image_SizeGp_2, tr( "These switches set the height and width of the image in pixels. This specifies the image size for file output. The preview display, if on, will generally attempt to pick a video mode to accommodate this size but the display settings do not in any way affect the resulting file output.\n"
"\n"
"The Start_Row, End_Row,  Start_Column and End_Column options allow you to define the subset area to be rendered. The default values are the full size of the image from (1,1) which is the upper left to (w,h) on the lower right where w and h are the Width=n and  Height=n values you have set." ) );
    WidthEdit_2->setText( tr( Width ) );
    QToolTip::add( WidthEdit_2, tr( "Width=n  	Sets screen width to n pixels" ) );
    QWhatsThis::add( WidthEdit_2, tr( "Width=n  	Sets screen width to n pixels" ) );
    WidthLabel_2->setText( tr( "Width :" ) );
    Start_ColumnEdit_2->setText( tr( Start_ColumnEdit ) );
    QToolTip::add( Start_ColumnEdit_2, tr( "Start_Column=n  	Set first column to n pixels" ) );
    QWhatsThis::add( Start_ColumnEdit_2, tr( "Start_Column=n  	Set first column to n pixels\n"
"Start_Column=0.n 	Set first column to n percent of width\n"
"+SCn or +SC0.n 	Same as Start_Column" ) );
    Start_ColumnLabel_2->setText( tr( "Start Column :" ) );
    End_ColumnEdit_2->setText( tr( End_ColumnEdit ) );
    QToolTip::add( End_ColumnEdit_2, tr( "End_Column=n  	Set last column to n pixels" ) );
    QWhatsThis::add( End_ColumnEdit_2, tr( "End_Column=n  	Set last column to n pixels\n"
"End_Column=0.n 	Set last column to n percent of width\n"
"+ECn or +EC0.n 	Same as End_Column" ) );
    End_RowLabel_2->setText( tr( "End Row :" ) );
    End_ColumnLabel_2->setText( tr( "End Column :" ) );
    End_RowEdit_2->setText( tr( End_RowEdit ) );
    QToolTip::add( End_RowEdit_2, tr( "End_Row=n  	Set last row to n pixels" ) );
    QWhatsThis::add( End_RowEdit_2, tr( "End_Row=n  	Set last row to n pixels\n"
"End_Row=0.n 	Set last row to n percent of height\n"
"+ERn or +En 	Same as End_Row=n\n"
"+ER0.n or +E0.n 	Same as End_Row=0.n" ) );
    Start_RowLabel_2->setText( tr( "Start Row :" ) );
    Start_RowEdit_2->setText( tr( Start_RowEdit ) );
    QToolTip::add( Start_RowEdit_2, tr( "Start_Row=n  	Set first row to n pixels" ) );
    QWhatsThis::add( Start_RowEdit_2, tr( "Start_Row=n  	Set first row to n pixels\n"
"Start_Row=0.n 	Set first row to n percent of height\n"
"+SRn or +Sn 	Same as Start_Row=n\n"
"+SR0.n or +S0.n 	Same as Start_Row=0.n" ) );
    HeightLabel_2->setText( tr( "Height :" ) );
    HeightEdit_2->setText( tr( Height ) );
    QToolTip::add( HeightEdit_2, tr( "Height=n  	Sets screen height to n pixels" ) );
    QWhatsThis::add( HeightEdit_2, tr( "Height=n  	Sets screen height to n pixels" ) );
    Display_Relating_SettingsGp_2->setTitle( tr( "Display related settings" ) );
    QWhatsThis::add( Display_Relating_SettingsGp_2, tr( "______________________________________________________________________________\n"
"On some systems, when the image is complete, the graphics display is cleared and POV-Ray switches back into text mode to print the final statistics and to exit. Normally when the graphics display is on, you want to look at the image awhile before continuing. Using Pause_When_Done=on  or +P causes POV-Ray to pause in graphics mode until you press a key to continue. The default is not to pause (-P).\n"
"\n"
"When the graphics display is not used, it is often desirable to monitor progress of the rendering. Using Verbose=on or +V turns on verbose reporting of your rendering progress. This reports the number of the line currently being rendered, the elapsed time for the current frame and other information. On some systems, this textual information can conflict with the graphics display. You may need to turn this off when the display is on. The default setting is off (-V).\n"
"\n"
"The option Draw_Vistas=on or +UD was originally a debugging help for POV-Ray's vista buffer feature but it was such fun we decided to keep it. Vista buffering is a spatial sub-division method that projects the 2-D extents of bounding boxes onto the viewing window. POV-Ray tests the 2-D x, y pixel location against these rectangular areas to determine quickly which objects, if any, the viewing ray will hit. This option shows you the 2-D rectangles used. The default setting is off (-UD) because the drawing of the rectangles can take considerable time on complex scenes and it serves no critical purpose. See section \"Automatic Bounding Control\" for more details." ) );
    ContinueCheckbox_2->setText( tr( "Continue" ) );
    QToolTip::add( ContinueCheckbox_2, tr( "Continue_Trace=bool  	Sets continued trace on/off" ) );
    QWhatsThis::add( ContinueCheckbox_2, tr( "Continue_Trace=bool  	Sets continued trace on/off\n"
"+C 	Sets continued trace on\n"
"-C 	Sets continued trace off" ) );
    Draw_VistasCheckbox_2->setText( tr( "Draw vistas" ) );
    QToolTip::add( Draw_VistasCheckbox_2, tr( "Draw_Vistas=bool  	Turn draw vistas on/off" ) );
    QWhatsThis::add( Draw_VistasCheckbox_2, tr( "Draw_Vistas=bool  	Turn draw vistas on/off\n"
"+UD 	Turn draw vistas on\n"
"-UD 	Turn draw vistas off\n"
"\n"
"The option Draw_Vistas=on or +UD was originally a debugging help for POV-Ray's vista buffer feature but it was such fun we decided to keep it. Vista buffering is a spatial sub-division method that projects the 2-D extents of bounding boxes onto the viewing window. POV-Ray tests the 2-D x, y pixel location against these rectangular areas to determine quickly which objects, if any, the viewing ray will hit. This option shows you the 2-D rectangles used. The default setting is off (-UD) because the drawing of the rectangles can take considerable time on complex scenes and it serves no critical purpose. See section \"Automatic Bounding Control\" for more details." ) );
    verbosebutton->setText( tr( "Verbose Mode" ) );
    Pause_When_DoneCheckbox_2->setText( tr( "Pause when done" ) );
    QToolTip::add( Pause_When_DoneCheckbox_2, tr( "Pause_When_Done=bool  	Sets pause when done on/off" ) );
    QWhatsThis::add( Pause_When_DoneCheckbox_2, tr( "Pause_When_Done=bool  	Sets pause when done on/off\n"
"+P 	Sets pause when done on\n"
"-P 	Sets pause when done off\n"
"\n"
"On some systems, when the image is complete, the graphics display is cleared and POV-Ray switches back into text mode to print the final statistics and to exit. Normally when the graphics display is on, you want to look at the image awhile before continuing. Using Pause_When_Done=on  or +P causes POV-Ray to pause in graphics mode until you press a key to continue. The default is not to pause (-P)." ) );
    Test_AbortCheckbox_2->setText( tr( "Test abort" ) );
    QToolTip::add( Test_AbortCheckbox_2, tr( "Test_Abort=bool  	Turn test for user abort on/off" ) );
    QWhatsThis::add( Test_AbortCheckbox_2, tr( "Test_Abort=bool  	Turn test for user abort on/off\n"
"+X 	Turn test abort on\n"
"-X 	Turn test abort off" ) );
    Test_Abort_CountEdit_2->setText( tr( Test_Abort_CountEdit ) );
    QToolTip::add( Test_Abort_CountEdit_2, tr( "Test_Abort_Count=n  	Set to test for abort every n pixels" ) );
    QWhatsThis::add( Test_Abort_CountEdit_2, tr( "Test_Abort_Count=n  	Set to test for abort every n pixels\n"
"+Xn 	Set to test for abort every n pixels on\n"
"-Xn 	Set to test for abort off (in future test every n pixels)" ) );
    Test_Abort_CountLabel_2->setText( tr( "Count :" ) );
    IniTabs->changeTab( Output, tr( "Output" ) );
    InputFileNameButton_2->setText( QString::null );
    Input_File_NameLabel_2->setText( tr( "Input File Name" ) );
    Include_Header_RemoveButton_2->setText( tr( "Remove" ) );
    Include_HeaderListview_2->header()->setLabel( 0, tr( "Include Header" ) );
    QToolTip::add( Include_HeaderListview_2, tr( "Include_Header=file  	Sets primary include file name to file" ) );
    QWhatsThis::add( Include_HeaderListview_2, tr( "Include_Header=file  	Sets primary include file name to file\n"
"+HIfile 	Same as Include_Header=file\n"
"\n"
"This option allows you to include a file as the first include file of a scene file. You can for example use this option to always include a specific set of default include files used by all your scenes." ) );
    Include_Header_AddButton_2->setText( tr( "Add" ) );
    Library_PathListview_2->header()->setLabel( 0, tr( "Library Path" ) );
    QToolTip::add( Library_PathListview_2, tr( "Library_Path=path  	Add path to list of library paths" ) );
    QWhatsThis::add( Library_PathListview_2, tr( "Library_Path=path  	Add path to list of library paths\n"
"+Lpath 	Same as Library_Path=path\n"
"\n"
"POV-Ray looks for files in the current directory. If it does not find a file it needs it looks in various other library directories which you specify. POV-Ray does not search your operating system path. It only searches the current directory and directories which you specify with this option. For example the standard include files are usually kept in one special directory. You tell POV-Ray to look there with...\n"
"\n"
" Library_Path=c:\\povray3\\include\n"
"\n"
"You must not specify any final path separators (\"\\\" or \"/\") at the end.\n"
"\n"
"Multiple uses of this option switch do not override previous settings. Up to twenty unique paths may be specified. If you specify the exact same path twice it is only counted once. The current directory will be searched first followed by the indicated library directories in the order in which you specified them." ) );
    Library_Path_RemoveButton_2->setText( tr( "Remove" ) );
    Library_Path_AddButton_2->setText( tr( "Add" ) );
    Include_IniListview_2->header()->setLabel( 0, tr( "Include Ini" ) );
    QToolTip::add( Include_IniListview_2, tr( "Include_Header=file  	Sets primary include file name to file" ) );
    QWhatsThis::add( Include_IniListview_2, tr( "Include_Header=file  	Sets primary include file name to file\n"
"+HIfile 	Same as Include_Header=file\n"
"\n"
"This option allows you to include a file as the first include file of a scene file. You can for example use this option to always include a specific set of default include files used by all your scenes." ) );
    Include_Ini_RemoveButton_2->setText( tr( "Remove" ) );
    Include_Ini_AddButton_2->setText( tr( "Add" ) );
    Input_File_NameEdit_2->setText( tr( "test.pov" ) );
    QToolTip::add( Input_File_NameEdit_2, tr( "Input_File_Name=file  	Sets input file name to file" ) );
    QWhatsThis::add( Input_File_NameEdit_2, tr( "Input_File_Name=file  	Sets input file name to file\n"
"+Ifile 	Same as Input_File_Name=file\n"
"\n"
"Note: there may be no space between +I and file.\n"
"\n"
"You will probably always set this option but if you do not the default input filename is object.pov. If you do not have an extension then .pov is assumed. On case-sensitive operating systems both .pov and .POV are tried. A full path specification may be used (on MS-DOS systems +Ic:\\povray3\\mystuff\\myfile.pov is allowed for example). In addition to specifying the input file name this also establishes the scene name.\n"
"\n"
"The scene name is the input name with drive, path and extension stripped. In the above example the scene name is myfile. This name is used to create a default output file name and it is referenced other places.\n"
"\n"
"Note: as per version 3.5 you can now specify a POV file on the command-line without the use of the +i switch (i.e. it works the same way as specifying an INI file without a switch), the POV file then should be the last on the commandline.\n"
"\n"
"If you use \"-\" as the input file name the input will be read from standard input. Thus you can pipe a scene created by a program to POV-Ray and render it without having a scene file." ) );
    IniTabs->changeTab( Parsing, tr( "Parsing" ) );
    File_OutputGp_2->setTitle( tr( "File output" ) );
    QWhatsThis::add( File_OutputGp_2, tr( "Most of these formats output 24 bits per pixel with 8 bits for each of red, green and blue data. PNG and PPM allow you to optionally specify the output bit depth from 5 to 16 bits for each of the red, green, and blue colors, giving from 15 to 48 bits of color information per pixel. The default output depth for all formats is 8 bits/color (16 million possible colors), but this may be changed for PNG and PPM format files by setting Bits_Per_Color=n  or by specifying +FNn or +FPn, where n is the desired bit depth.\n"
"\n"
"Specifying a smaller color depth like 5 bits/color (32768 colors) may be enough for people with 8- or 16-bit (256 or 65536 color) displays, and will improve compression of the PNG file. Higher bit depths like 10 or 12 may be useful for video or publishing applications, and 16 bits/color is good for grayscale height field output (See section \"Height Field\" for details on height fields).\n"
"\n"
"Targa format also allows 8 bits of alpha transparency data to be output, while PNG format allows 5 to 16 bits of alpha transparency data, depending on the color bit depth as specified above. You may turn this option on with Output_Alpha=on or +UA. The default is off or -UA." ) );
    Output_File_NameEdit_2->setText( tr( "scene" ) );
    QToolTip::add( Output_File_NameEdit_2, tr( "Output_File_Name=file  	Sets output file to file" ) );
    QWhatsThis::add( Output_File_NameEdit_2, tr( "Output_File_Name=file  	Sets output file to file\n"
"+Ofile 	Same as Output_File_Name=file\n"
"\n"
"The default output filename is created from the scene name and need not be specified. The scene name is the input name with all drive, path, and extension information stripped. For example if the input file name is c:\\povray3\\mystuff\\myfile.pov the scene name is myfile. The proper extension is appended to the scene name based on the file type. For example myfile.tga or myfile.png might be used." ) );
    QToolTip::add( Buffer_SizeEdit_2, tr( "Buffer_Size=n  	Set output buffer size to n kilobytes. If n is zero, no buffering. If n < system default, the system default is used." ) );
    QWhatsThis::add( Buffer_SizeEdit_2, tr( "Buffer_Size=n  	Set output buffer size to n kilobytes. If n is zero, no buffering. If n &lt; system default, the system default is used.\n"
"+Bn 	Turn buffer on, set size n\n"
"-Bn 	Turn buffer off, but for future set size n\n"
"\n"
"The Buffer_Output and Buffer_Size options and the +B switch allows you to assign large buffers to the output file. This reduces the amount of time spent writing to the disk. If this parameter is not specified, then as each row of pixels is finished, the line is written to the file and the file is flushed. On most systems, this operation ensures that the file is written to the disk so that in the event of a system crash or other catastrophic event, at least a part of the picture has been stored properly and retrievable on disk. The default is not to use any buffer." ) );
    QToolTip::add( Bits_Per_ColorSpinbox_2, tr( "Bits_Per_Color=n  	Sets file output bits/color to n" ) );
    QWhatsThis::add( Bits_Per_ColorSpinbox_2, tr( "Specifying a smaller color depth like 5 bits/color (32768 colors) may be enough for people with 8- or 16-bit (256 or 65536 color) displays, and will improve compression of the PNG file. Higher bit depths like 10 or 12 may be useful for video or publishing applications, and 16 bits/color is good for grayscale height field output (See section \"Height Field\" for details on height fields)." ) );
    OutputFileNameButton_2->setText( QString::null );
    Output_File_TypeLabel_2->setText( tr( "Output File type" ) );
    Output_File_NameLabel_2->setText( tr( "Output File Name :" ) );
    Bits_Per_ColorLabel_2->setText( tr( "Bits Per Color" ) );
    Buffer_OutputCheckbox_2->setText( tr( "Buffer Output" ) );
    QToolTip::add( Buffer_OutputCheckbox_2, tr( "Buffer_Output=bool  	Turn output buffering on/off" ) );
    QWhatsThis::add( Buffer_OutputCheckbox_2, tr( "Buffer_Output=bool  	Turn output buffering on/off\n"
"+B 	Turn output buffering on\n"
"-B 	Turn output buffering off\n"
"\n"
"The Buffer_Output and Buffer_Size options and the +B switch allows you to assign large buffers to the output file. This reduces the amount of time spent writing to the disk. If this parameter is not specified, then as each row of pixels is finished, the line is written to the file and the file is flushed. On most systems, this operation ensures that the file is written to the disk so that in the event of a system crash or other catastrophic event, at least a part of the picture has been stored properly and retrievable on disk. The default is not to use any buffer." ) );
    Output_To_FileCheckbox_2->setText( tr( "Output File" ) );
    QToolTip::add( Output_To_FileCheckbox_2, tr( "Output_to_File=bool  	Sets file output on/off" ) );
    QWhatsThis::add( Output_To_FileCheckbox_2, tr( "Output_to_File=bool  	Sets file output on/off\n"
"+F 	Sets file output on (use default type)\n"
"-F 	Sets file output off\n"
"\n"
"By default, POV-Ray writes an image file to disk. When you are developing a scene and doing test renders, the graphic preview may be sufficient. To save time and disk activity you may turn file output off with Output_to_File=off or -F." ) );
    Output_File_TypeCombobox_2->clear();
    Output_File_TypeCombobox_2->insertItem( tr( "Compressed Targa" ) );
    Output_File_TypeCombobox_2->insertItem( tr( "PNG" ) );
    Output_File_TypeCombobox_2->insertItem( tr( "Unix PPM" ) );
    Output_File_TypeCombobox_2->insertItem( tr( "System Specific" ) );
    Output_File_TypeCombobox_2->insertItem( tr( "Uncompressed Targa" ) );
    QToolTip::add( Output_File_TypeCombobox_2, tr( "Output_File_Type=x  	Sets file output format to x" ) );
    QWhatsThis::add( Output_File_TypeCombobox_2, tr( "Output_File_Type=x  	Sets file output format to x\n"
"+Fxn 	Sets file output on; sets format x, depth n\n"
"-Fxn 	Sets file output off; but in future use format x, depth n\n"
"\n"
"You may select one of several different file types using Output_File_Type=x or +Fx  where x is one of the following...\n"
"+FC 	Compressed Targa-24 format (RLE, run length encoded)\n"
"+FN 	PNG (portable network graphics) format\n"
"+FP 	Unix PPM format\n"
"+FS 	System-specific such as Mac Pict or Windows BMP\n"
"+FT 	Uncompressed Targa-24 format" ) );
    IniTabs->changeTab( File_Output, tr( "File Output" ) );












};


 PovConfig::~PovConfig(){

};

void PovConfig::HeightImageSizeChanged(const QString& str){Height = str;};
void PovConfig::WidthImageSizeChanged(const QString& str){Width = str;};
void PovConfig::Start_ColumnImageSizeChanged(const QString& str){Start_ColumnEdit = str;};
void PovConfig::End_ColumnImageSizeChanged(const QString& str){End_ColumnEdit = str;};
void PovConfig::Start_RowImageSizeChanged(const QString& str){Start_RowEdit = str;};
void PovConfig::End_RowImageSizeChanged(const QString& str){End_RowEdit = str;};
void PovConfig::Test_Abort_CountEditChanged(const QString& str){Test_Abort_CountEdit = str;};

void PovConfig::connectcontrols(){
    // signals and slots connections
    connect( HeightEdit_2, SIGNAL( textChanged(const QString&) ), this, SLOT( HeightImageSizeChanged(const QString&)));
    connect( WidthEdit_2, SIGNAL( textChanged(const QString&) ), this, SLOT( WidthImageSizeChanged(const QString&)));
    connect( Start_ColumnEdit_2, SIGNAL( textChanged(const QString&) ), this, SLOT(Start_ColumnImageSizeChanged(const QString&)));
    connect( End_ColumnEdit_2, SIGNAL( textChanged(const QString&) ), this, SLOT(End_ColumnImageSizeChanged(const QString&)));
    connect( End_RowEdit_2, SIGNAL( textChanged(const QString&) ), this, SLOT(End_RowImageSizeChanged(const QString&)));
    connect( Start_RowEdit_2, SIGNAL( textChanged(const QString&) ), this, SLOT(Start_RowImageSizeChanged(const QString&)));
    connect( Test_Abort_CountEdit_2, SIGNAL( textChanged(const QString&) ), this, SLOT(Test_Abort_CountEditChanged(const QString&)));

    connect( Pause_When_DoneCheckbox_2, SIGNAL( clicked() ), this, SLOT( Pause_when_Donetoggled() ) );
    connect( Test_AbortCheckbox_2, SIGNAL( clicked() ), this, SLOT( Test_AbortCheckboxtoggled() ) );
    connect( verbosebutton, SIGNAL( clicked() ), this, SLOT( verbose_ok() ) );
    connect( Test_AbortCheckbox_2, SIGNAL( toggled(bool) ), Test_Abort_CountEdit_2, SLOT( setEnabled(bool) ) );
    connect( ContinueCheckbox_2, SIGNAL( clicked() ), this, SLOT( ContinueCheckBoxtoggled() ) );
    connect( OutputFileNameButton_2, SIGNAL( clicked() ), this, SLOT( OutputFileNameButton_clicked() ) );
    connect( Output_File_TypeCombobox_2, SIGNAL( highlighted(const QString&) ), this, SLOT( Output_File_TypeCombobox_highlighted(const QString&) ) );
    connect( Output_To_FileCheckbox_2, SIGNAL( clicked() ), this, SLOT( OutputFile_toggled() ) );
    connect( Output_To_FileCheckbox_2, SIGNAL( toggled(bool) ), this, SLOT( Output_To_FileCheckbox_toggled(bool) ) );
    connect( Buffer_OutputCheckbox_2, SIGNAL( clicked() ), this, SLOT( OutPutBuffer_toggled() ) );
    connect( Buffer_OutputCheckbox_2, SIGNAL( toggled(bool) ), this, SLOT( Buffer_OutputCheckbox_toggled(bool) ) );
    connect( Include_Header_RemoveButton_2, SIGNAL( clicked() ), this, SLOT( Include_Header_RemoveButton_clicked() ) );
    connect( Include_Header_AddButton_2, SIGNAL( clicked() ), this, SLOT( Include_Header_AddButton_clicked() ) );
    connect( Library_Path_RemoveButton_2, SIGNAL( clicked() ), this, SLOT( Library_Path_RemoveButton_clicked() ) );
    connect( Library_Path_AddButton_2, SIGNAL( clicked() ), this, SLOT( Library_Path_AddButton_clicked() ) );
    connect( Include_Ini_RemoveButton_2, SIGNAL( clicked() ), this, SLOT( Include_Ini_RemoveButton_clicked() ) );
    connect( Include_Ini_AddButton_2, SIGNAL( clicked() ), this, SLOT( Include_Ini_AddButton_clicked() ) );
    connect( InputFileNameButton_2, SIGNAL( clicked() ), this, SLOT( InputFile_toggled() ) );
    connect( InputFileNameButton_2, SIGNAL( clicked() ), this, SLOT( InputFileNameButton_clicked() ) );
    connect( Output_File_TypeCombobox_2, SIGNAL( activated(int) ), this, SLOT( File_Extension_Changed(int) ) );
};


void PovConfig::Include_Ini_AddButton_clicked()
{
       QString   include_ini = QFileDialog::getOpenFileName(
            "",
            tr("Povray ini files (*.ini);;All files (* *.*)"),
            this,
            "open file dialog",
            tr("Please choose the include ini") );
    if (include_ini.length() && !Include_IniListview_2->findItem(include_ini,0))
    {
        new QListViewItem(Include_IniListview_2,include_ini);
    }
}
//====================================

void PovConfig::Include_Ini_RemoveButton_clicked()
{
    if (Include_IniListview_2->currentItem())
    {
        delete Include_IniListview_2->currentItem();
    }
}
//====================================
void PovConfig::InputFileNameButton_clicked()
{

    QString filename = QFileDialog::getSaveFileName(
            "",
            tr("Povray scripts (*.pov)"),
            this,
            "save file dialog",
            tr("Please choose the output file") );
    if (filename.length())
    {
        Input_File_NameEdit_2->setText(filename);
    }
}

//====================================
void PovConfig::Include_Header_AddButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
            "",
            tr("Povray files (*.inc *.pov)"),
            this,
            "open file dialog",
            tr("Please choose the include header") );
    if (filename.length() && !Include_HeaderListview_2->findItem(filename,0))
    {
        new QListViewItem(Include_HeaderListview_2,filename);
    }

   IncludeHeaderFile += " +HI"+filename;
}
//====================================
void PovConfig::Include_Header_RemoveButton_clicked()
{
    if (Include_HeaderListview_2->currentItem())
    {
        delete Include_HeaderListview_2->currentItem();
    }
}

//====================================

void PovConfig::Library_Path_RemoveButton_clicked()
{
    if (Library_PathListview_2->currentItem())
    {
        delete Library_PathListview_2->currentItem();
    }
}
//====================================
void PovConfig::Declare_AddButton_clicked()
{
}
//====================================
void PovConfig::Declare_RemoveButton_clicked()
{
}
//====================================
void PovConfig::Test_AbortCheckbox_toggled( bool )
{
    Test_Abort_CountLabel_2->setEnabled(Test_AbortCheckbox_2->isChecked());
    Test_Abort_CountEdit_2->setEnabled(Test_AbortCheckbox_2->isChecked());
}

//====================================

void PovConfig::Create_IniCheckbox_toggled( bool )
{/*
    Create_IniEdit_2->setEnabled(Create_IniCheckbox_2->isChecked());
*/}
//====================================
void PovConfig::OutputFileNameButton_clicked()
{
    QString filename = QFileDialog::getSaveFileName(
            "",
            tr("Images (*.png *.jpg *.jpeg *.tif *.tiff *.ppm *.tga *.pgm)"),
            this,
            "save file dialog",
            tr("Please choose the output file") );
    if (filename.length())
    {
        Output_File_NameEdit_2->setText(filename);
    }
}

//====================================
void PovConfig::Buffer_OutputCheckbox_toggled( bool )
{
    Buffer_SizeEdit_2->setEnabled(Output_To_FileCheckbox_2->isChecked() && Buffer_OutputCheckbox_2->isChecked());
}

//====================================
void PovConfig::Output_To_FileCheckbox_toggled( bool )
{
//    Output_AlphaCheckbox_2->setEnabled(Output_To_FileCheckbox_2->isChecked());
    Output_File_NameLabel_2->setEnabled(Output_To_FileCheckbox_2->isChecked());
    Output_File_NameEdit_2->setEnabled(Output_To_FileCheckbox_2->isChecked());
    Output_File_TypeLabel_2->setEnabled(Output_To_FileCheckbox_2->isChecked());
    Output_File_TypeCombobox_2->setEnabled(Output_To_FileCheckbox_2->isChecked());
    Bits_Per_ColorLabel_2->setEnabled(Output_To_FileCheckbox_2->isChecked());
    Bits_Per_ColorSpinbox_2->setEnabled(Output_To_FileCheckbox_2->isChecked());
    Buffer_OutputCheckbox_2->setEnabled(Output_To_FileCheckbox_2->isChecked());
    Buffer_SizeEdit_2->setEnabled(Output_To_FileCheckbox_2->isChecked() && Buffer_OutputCheckbox_2->isChecked());
}
//====================================
void PovConfig::Output_File_TypeCombobox_highlighted( QString & item)
{
    Bits_Per_ColorLabel_2->setEnabled((item == "PNG") || (item == "Unix PPM"));
    Bits_Per_ColorSpinbox_2->setEnabled((item == "PNG") || (item == "Unix PPM"));
}

//====================================

void PovConfig::whatsThisButton_clicked()
{
    QWhatsThis::enterWhatsThisMode();
}

//====================================
void PovConfig::Butto_OK_Clicked(){
}

//====================================
void PovConfig::runpovray()
{   QString execute_commande, Test_Abort_CountEdit3;
    int result;

    if(verbose ==1) xterm ="xterm -e ";
    else  xterm = "";

    if(testabort == 1) { Test_Abort_CountEdit3 = Test_Abort_CountEdit;} 
    else Test_Abort_CountEdit3 = "" ;

    if(pausewhendone ==1) { Pause_When_Done = "+P"; }
    else  Pause_When_Done = "";

    if( continuecheckbox ==1) {  Continue= "+C"; }
    else  Continue = "";

    if(outputfile==1) Output_File_NameEdit="+O"+Output_File_NameEdit_2->text()+FileExtension+" ";
   // else { Output_File_NameEdit="";
   //        FileExtension = "";}

    if(inputfile==1) Input_File_NameEdit="+I"+Input_File_NameEdit_2->text();
    //else Input_File_NameEdit="";

    if(outputbuffer==1) OutPutBuffer="+B["+Buffer_SizeEdit_2->text()+"]";
    else OutPutBuffer="";

    execute_commande = xterm+" povray "+Input_File_NameEdit+" "+Output_File_NameEdit+" "\
     +"+W"+Width+" "+"+H"+Height+" \
     "+"+SR"+Start_RowEdit+" "+"+ER"+End_RowEdit+" \
     "+"+SC"+Start_ColumnEdit+" "+"+EC"+End_ColumnEdit+" \
     "+Pause_When_Done+" "+"+X"+Test_Abort_CountEdit3+"\
     "+OutPutBuffer+" "+IncludeHeaderFile+" "+Continue+"  &";
    result = std::system(execute_commande);
   if(result != 1) std::cout << "Ok \n";

};
//====================================

void PovConfig::InputFile_toggled(){

    inputfile *= -1;
}
//====================================

void PovConfig::OutputFile_toggled(){

    outputfile *= -1;
}

//====================================
void PovConfig::verbose_ok()
{
verbose  *= -1;
}

//====================================
void PovConfig::ImageSizeChanged()
{ ImageSize_Field_changed =1;
}

//====================================
void PovConfig::whatsButton_clicked()
{
    QWhatsThis::enterWhatsThisMode();
}
//====================================
void PovConfig::povPreference()
{
}

//====================================
void PovConfig::Pause_when_Donetoggled(){
    pausewhendone *= -1;
}

//====================================
void PovConfig::OutPutBuffer_toggled(){
    outputbuffer *= -1;
}

//====================================
void PovConfig::ContinueCheckBoxtoggled(){

    continuecheckbox *= -1;
}
//====================================
void PovConfig::Test_AbortCheckboxtoggled(){

    testabort *= -1;
}
//====================================
void PovConfig::Library_Path_AddButton_clicked()
{
    QString dirname = QFileDialog::getExistingDirectory(
            "",
            this,
            "open directory dialog",
            tr("Please choose the directory containing the libs") );
    if (dirname.length() && !Library_PathListview_2->findItem(dirname,0))
    {
        new QListViewItem(Library_PathListview_2,dirname);
    }
    
    LibraryPath += " +L"+dirname;
}

//====================================
void PovConfig::Frames_Path_clicked()
{
}
