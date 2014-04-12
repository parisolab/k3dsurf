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
#ifndef editeur_H
#define editeur_H
#include <qmainwindow.h>

class QTextEdit;

class editeur: public QMainWindow
{
    Q_OBJECT

public:
    editeur();
    ~editeur();

    QTextEdit *e;
protected:
    void closeEvent( QCloseEvent* );

public slots:
    void newDoc();
    void choose();
    void load( const QString &fileName );
    void save();
    void saveAs();
    void settext(const QString & txt );
    void append(const QString & txt );
    void changecolor(const QColor & c );
    void about();
    void aboutQt();
    void runpovray();
    void saveScript(QString &, QString );
private:
    QString workfile;
    QString filename;
};


#endif
