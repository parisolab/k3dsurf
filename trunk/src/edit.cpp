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
#include "edit.h"
#include <qimage.h>
#include <qpixmap.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qpopupmenu.h>
#include <qmenubar.h>
#include <qtextedit.h>
#include <qfile.h>
#include <qfiledialog.h>
#include <qstatusbar.h>
#include <qmessagebox.h>
#include <qapplication.h>
#include <qaccel.h>
#include <qtextstream.h>
#include <qpainter.h>
#include <qpaintdevicemetrics.h>
#include <qwhatsthis.h>

#include "filesave.xpm"
#include "fileopen.xpm"

editeur::editeur()
    : QMainWindow( 0, "editeur", WDestructiveClose | WStyle_StaysOnTop)
{
    workfile = "test.pov";

    QPixmap openIcon, saveIcon, runIcon;

    QToolBar * fileTools = new QToolBar( this, "file operations" );
    fileTools->setLabel( tr("File Operations") );

    openIcon = QPixmap( fileopen );
    QToolButton * fileOpen = new QToolButton( openIcon, tr("Open File"), QString::null,
                           this, SLOT(choose()), fileTools, "open file" );

    saveIcon = QPixmap( filesave );
    QToolButton * fileSave = new QToolButton( saveIcon, tr("Save File"), QString::null, this, SLOT(save()), fileTools, "save file" );

    (void)QWhatsThis::whatsThisButton( fileTools );

    QString fileOpenText = tr("<p><img source=\"fileopen\"> "
         "Click this button to open a <em>new file</em>. <br>"
                 "You can also select the <b>Open</b> command "
                 "from the <b>File</b> menu.</p>");

    QWhatsThis::add( fileOpen, fileOpenText );

    QMimeSourceFactory::defaultFactory()->setPixmap( "fileopen", openIcon );

    QString fileSaveText = tr("<p>Click this button to save the file you "
                 "are editeuring. You will be prompted for a file name.\n"
                 "You can also select the <b>Save</b> command "
                 "from the <b>File</b> menu.</p>");

    QWhatsThis::add( fileSave, fileSaveText );

    QString filePrintText = tr("Click this button to print the file you "
                 "are editeuring.\n You can also select the Print "
                 "command from the File menu.");

    QPopupMenu * file = new QPopupMenu( this );
    menuBar()->insertItem( tr("&File"), file );

    file->insertItem( tr("&New"), this, SLOT(newDoc()), CTRL+Key_N );

    int id;
    id = file->insertItem( openIcon, tr("&Open..."),
   this, SLOT(choose()), CTRL+Key_O );
    file->setWhatsThis( id, fileOpenText );

    id = file->insertItem( saveIcon, tr("&Save"),
   this, SLOT(save()), CTRL+Key_S );
    file->setWhatsThis( id, fileSaveText );

    id = file->insertItem( tr("Save &As..."), this, SLOT(saveAs()) );
    file->setWhatsThis( id, fileSaveText );

    file->insertSeparator();

    file->insertItem( tr("&Close"), this, SLOT(close()), CTRL+Key_W );

    file->insertItem( tr("&Quit"), qApp, SLOT( closeAllWindows() ), CTRL+Key_Q );

    menuBar()->insertSeparator();

    QPopupMenu * help = new QPopupMenu( this );
    menuBar()->insertItem( tr("&Help"), help );

    help->insertItem( tr("&About"), this, SLOT(about()), Key_F1 );
    help->insertItem( tr("About &Qt"), this, SLOT(aboutQt()) );
    help->insertSeparator();
    help->insertItem( tr("What's &This"), this, SLOT(whatsThis()), SHIFT+Key_F1 );

    e = new QTextEdit( this, "Editor" );
    e->setFocus();
    setCentralWidget( e );
    statusBar()->message( tr("Ready"), 2000 );

    resize( 350, 300 );
}


editeur::~editeur()
{
    delete e;
}

void editeur::settext(const QString & txt )
{
    e->setText(txt );
}

void editeur::append(const QString & txt )
{
    e->append(txt );
}

void editeur::changecolor(const QColor & c )
{
    e->setColor(c);
}

void editeur::newDoc()
{
    editeur *ed = new editeur;
    ed->setCaption(tr("Qt Example - Application"));
    ed->show();
}

void editeur::choose()
{
    QString fn = QFileDialog::getOpenFileName( "../examples", QString::null, this);
    if ( !fn.isEmpty() ) load( fn );
    else statusBar()->message( tr("Loading aborted"), 2000 );
    workfile = fn;
}


void editeur::load( const QString &fileName )
{
    QFile f( fileName );
    if ( !f.open( IO_ReadOnly ) )
     return;

    QTextStream ts( &f );
    e->setText( ts.read() );
    e->setModified( FALSE );
    setCaption( fileName );
    statusBar()->message( tr("Loaded document %1").arg(fileName), 2000 );

}


void editeur::saveScript(QString &text, QString name)
{
      QFile f( name );
    if ( !f.open( IO_WriteOnly ) ) {
statusBar()->message( tr("Could not write to %1").arg(name),
      2000 );
return;
    }

    QTextStream t( &f );
    t << text;
    f.close();
}



void editeur::save()
{
    if ( filename.isEmpty() ) {
saveAs();
return;
    }

    QString text = e->text();
    QFile f( filename );
    if ( !f.open( IO_WriteOnly ) ) {
statusBar()->message( tr("Could not write to %1").arg(filename),
      2000 );
return;
    }

    QTextStream t( &f );
    t << text;
    f.close();

    e->setModified( FALSE );

    setCaption( filename );

    statusBar()->message( tr( "File %1 saved" ).arg( filename ), 2000 );
}


void editeur::saveAs()
{
    QString fn = QFileDialog::getSaveFileName( QString::null, QString::null,
       this );
    if ( !fn.isEmpty() ) {
filename = fn;
save();
    } else {
statusBar()->message( tr("Saving aborted"), 2000 );
    }
    workfile = fn;

}

/*
void editeur::print()
{
    // ###### Rewrite to use QSimpleRichText to print here as well
    const int Margin = 10;
    int pageNo = 1;

    if ( printer->setup(this) ) {// printer dialog
statusBar()->message( tr("Printing...") );
QPainter p;
if( !p.begin( printer ) )               // paint on printer
    return;

p.setFont( e->font() );
int yPos= 0;// y-position for each line
QFontMetrics fm = p.fontMetrics();
QPaintDeviceMetrics metrics( printer ); // need width/height
// of printer surface
for( int i = 0 ; i < e->lines() ; i++ ) {
    if ( Margin + yPos > metrics.height() - Margin ) {
QString msg( "Printing (page " );
msg += QString::number( ++pageNo );
msg += ")...";
statusBar()->message( msg );
printer->newPage();// no more room on this page
yPos = 0;// back to top of page
    }
    p.drawText( Margin, Margin + yPos,
metrics.width(), fm.lineSpacing(),
ExpandTabs | DontClip,
e->text( i ) );
    yPos = yPos + fm.lineSpacing();
}
p.end();// send job to printer
statusBar()->message( tr("Printing completed"), 2000 );
    } else {
statusBar()->message( tr("Printing aborted"), 2000 );
    }
}
*/
void editeur::closeEvent( QCloseEvent* ce )
{
    if ( !e->isModified() ) {
ce->accept();
return;
    }

    switch( QMessageBox::information( this, tr("Qt Application Example"),
      tr("Do you want to save the changes"
      " to the document?"),
      tr("Yes"), tr("No"), tr("Cancel"),
      0, 1 ) ) {
    case 0:
save();
ce->accept();
break;
    case 1:
ce->accept();
break;
    case 2:
    default: // just for sanity
ce->ignore();
break;
    }
}


void editeur::about()
{
    QMessageBox::about( this, tr("Qt Application Example"),
tr("This example demonstrates simple use of "
"QMainWindow,\nQMenuBar and QToolBar."));

}

void editeur::runpovray()
{ /*int retour;
retour = system("povray +I"+workfile+" +Oscene.tga +L/root/Desktop/pov/povray-3.6.1/scenes/incdemo/glasses  +FT +W250 +H250 +P +X10 &");
*/
}


void editeur::aboutQt()
{
    QMessageBox::aboutQt( this, tr("Qt Application Example") );
}
