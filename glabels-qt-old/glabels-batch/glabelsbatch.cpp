#include "glabelsbatch.h"
/*  main.cpp
 *
 *  Copyright (C) 2013-2016  Jim Evins <evins@snaught.com>
 *
 *  This file is part of gLabels-qt.
 *
 *  gLabels-qt is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  gLabels-qt is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with gLabels-qt.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "model/FileUtil.h"
#include "model/Db.h"
#include "model/Model.h"
#include "model/PageRenderer.h"
#include "model/Settings.h"
#include "model/Version.h"
#include "model/XmlLabelParser.h"

#include "barcode/Backends.h"
#include "merge/Factory.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QLibraryInfo>
#include <QLocale>
#include <QPrinter>
#include <QPrinterInfo>
#include <QTranslator>


namespace
{

#if defined(Q_OS_WIN)
    const QString STDOUT_FILENAME = "CON:";
    const QString STDIN_FILENAME  = "CON:";
#elif defined(Q_OS_LINUX)
    const QString STDOUT_FILENAME = "/dev/stdout";
    const QString STDIN_FILENAME  = "/dev/stdin";
#else
    const QString STDOUT_FILENAME = "/dev/stdout";
    const QString STDIN_FILENAME  = "/dev/stdin";
#endif

}

GlabelsBatch::GlabelsBatch(QObject *parent) : QObject(parent)
{

}
int GlabelsBatch::main( QString filename ,QString printername,QString outputFilename , QString source/*QMap<QString,QString> variableDefinitions*/)
{
    QString sheets, copies, first="1";
    bool collated =true,groups=false,outlines=false,crop_marks =false,reverse=false;

    //
    // Parse variable definitions from command line, if any
    //

    //
    // Initialize subsystems
    //
    glabels::model::Settings::init();
    glabels::model::Db::init();
    glabels::merge::Factory::init();
    glabels::barcode::Backends::init();
   // variableDefinitions["ref"]="123";
   // variableDefinitions["label"]="uno-dos-tres";

    if ( !filename.isEmpty())
    {
        qDebug() << "Batch mode.";


        if ( filename == "-" )
        {
            filename = STDIN_FILENAME;
        }
        qDebug() << "Project file =" << filename;

        glabels::model::Model *model = glabels::model::XmlLabelParser::readFile( filename );
        if ( model )
        {
              model->merge()->setSource(source);
            //model->variables()->setVariables( variableDefinitions );

            //qDebug()<<"variables"<<model->variables()->hasVariable("ref");


            QPrinter printer( QPrinter::HighResolution );
            printer.setColorMode( QPrinter::Color );
            if ( !printername.isEmpty())
            {
                qDebug() << "Printer =" << printername;
                printer.setPrinterName( printername );
            }
            else if (!outputFilename.isEmpty() )
            {

                if ( outputFilename == "-" )
                {
                    outputFilename = STDOUT_FILENAME;
                }
                qDebug() << "Output =" << outputFilename;
                printer.setOutputFileName( outputFilename );
            }
            else
            {
                qDebug() << "Batch mode.  printer =" << QPrinterInfo::defaultPrinterName();
            }

            glabels::model::PageRenderer renderer( model );
           //qDebug()<<"keys"<< model->merge()->keys();
           //qDebug()<<"source"<<

            if ( model->merge()->keys().empty() )
            {
                // Simple project (no merge)
                if ( !sheets.isEmpty() )
                {
                    // Full sheets of simple items
                    renderer.setNCopies( sheets.toInt() * model->frame()->nLabels() );
                    renderer.setStartItem( 0 );
                }
                else if ( !copies.isEmpty() )
                {
                    // Partial sheet(s) of simple items
                    renderer.setNCopies( copies.toInt() );
                    renderer.setStartItem( first.toInt() - 1 );
                }
                else
                {
                    // One full sheet of simple items
                    renderer.setNCopies( 1 );
                    renderer.setStartItem( 0 );
                }
            }
            else
            {
                // Project with merge
                renderer.setNCopies( 2 );
                renderer.setStartItem( first.toInt() - 1 );
                renderer.setIsCollated( collated );
                renderer.setAreGroupsContiguous( !groups);
            }
            renderer.setPrintOutlines( outlines );
            renderer.setPrintCropMarks(crop_marks );
            renderer.setPrintReverse( reverse  );

            // Item and page count summary
            if ( renderer.nPages() == 1 )
            {
                if ( renderer.nItems() == 1 )
                {
                    qDebug() <<  "Printing 1 item on 1 page.";
                }
                else
                {
                    qDebug() <<  "Printing" << renderer.nItems() << "items on 1 page.";
                }
            }
            else
            {
                qDebug() << "Printing" << renderer.nItems() << "items on" << renderer.nPages() << "pages.";
            }

            // Do it!
            renderer.print( &printer );
        }
    }
    else
    {
        QFileInfo fi(filename);
        if ( fi.suffix()=="glabels")
        {
            qWarning() << "Error: missing glabels project file.";
        }
        else
        {
            qWarning() << "Error: batch mode supports only one glabels project file.";
        }
        return -1;
    }

    return 0;
}
