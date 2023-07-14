#include "dialogprint.h"
#include "glabelsqt.h"
#include "mergejson.h"
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
#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLibraryInfo>
#include <QLocale>
#include <QPrinter>
#include <QPrinterInfo>
#include <QTranslator>

#include <model/Units.h>


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

GlabelsQt::GlabelsQt(QObject *parent) : QObject(parent)
{

}
int GlabelsQt::Print( QString filename ,QString printername,QString outputFilename , QString source/*QMap<QString,QString> variableDefinitions*/)
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
            QMap<QString,QString> m;
            QFile file(source);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
                QTextStream in(&file);
                while (!in.atEnd()) {
                    QString line = in.readLine();
                    qDebug()<<(line);
                }
            }
            m["ref"]="ccc";
            model->variables()->setVariables(m);

            qDebug()<<"variables"<<model->variables()->hasVariable("ref");


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
//implement method  Render equal as Print
void GlabelsQt::renderModel( QWidget *parent,glabels::model::Model *model,QString source,  QString sheets,QString copies,QString first )
{
    //QString sheets, copies, first="1";
    bool collated =true,groups=false,outlines=false,crop_marks =false,reverse=false;
    if ( model )
    {
        model->merge()->setSource(source);
        QMap<QString,QString> m;
        QFile file(source);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                qDebug()<<(line);
            }
        }
        m["ref"]="ccc";
        model->variables()->setVariables(m);





        glabels::model::PageRenderer renderer( model );
        qDebug()<<"n labels="<<model->frame()->nLabels();
        qDebug()<<"h"<< model->frame()->h();
        //debug w
        qDebug()<<"w"<< model->frame()->w();
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
        //show dialog with qpainter widget
        QDialog *dialog = new QDialog(parent);
        dialog->setWindowTitle("Products");
        dialog->setWindowModality(Qt::ApplicationModal);
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        // QPainter *paint= new QPainter(dialog);

        QPixmap pixmap(200,300);
        pixmap.fill(QColor("transparent"));

        QPainter *painter=new QPainter(&pixmap);

        QLabel label("rifgrth",dialog);


        //HLayout->addWidget(QLabel);
        QHBoxLayout *HLayout = new QHBoxLayout(dialog);


        dialog->setLayout (HLayout);
        renderer.printPage(painter,0);
        label.setPixmap(pixmap);

        QPen pen;
        pen.setWidth(40);
        pen.setColor(Qt::red);
        QRect rect;

        painter->setPen(pen);
        rect.setTopLeft(QPoint(100,100));
        rect.setWidth(100);
        rect.setHeight(200);
        painter->drawRect(rect);
        label.show();
        HLayout->addWidget (&label);
        dialog->exec();
    }
}

//implement method  Render equal as Print
void GlabelsQt::renderModel( QWidget *parent,glabels::model::Model *model,QString printername,QString outputFilename,QList<glabels::merge::Record> records,  QString sheets,QString copies,QString first )
{
    qDebug()<<"GlabelsQt::renderModel=";
    copies="2", first="1";
    sheets="1";

    bool collated =false,groups=false,outlines=true,crop_marks =true,reverse=false;
    if ( model )
    {


        qDebug()<<"records="<<model->merge()->recordList().size();
        //clear recordList
        //implements anonymous class from abstract class glabels::merge::Merge
        QList<QString> keys = records.first().uniqueKeys();
        //qDebug()<<"records keys="<<keys.toStdList();
        model->setMerge(new glabels::merge::MergeJson(records,keys));

        // model->variables()->setVariables(m);
        // qDebug()<<"variables"<<model->variables();

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
        model->merge()->setSource("");
        qDebug()<<"n labels="<<model->frame()->nLabels();
        //qDebug()<<"h"<< model->frame()->h();


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
            // qDebug()<<"keys"<< model->merge()->keys();
            // Project with merge
            renderer.setNCopies( 1 );
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


        double h = model->frame()->h().inUnits(glabels::model::Units::pt());
        double w = model->frame()->w().inUnits(glabels::model::Units::pt());
        QSize dim( (w),(h));
        DialogPrint  dp(parent);
        dp.setPageRender(&renderer,QSize(renderer.pageRect().width(),renderer.pageRect().height()));
        //dp.exec();
        //if dialog exec is OK
        if(dp.exec() == QDialog::Accepted){
            QSizeF pageSize( model->tmplate()->pageWidth().pt(), model->tmplate()->pageHeight().pt() );
            printer.setPageSize( QPageSize(pageSize, QPageSize::Point) );
            printer.setFullPage( true );
            printer.setPageMargins( 0, 0, 0, 0, QPrinter::Point );

            QPainter painter( &printer );
			
            QRectF rectPx  = printer.paperRect( QPrinter::DevicePixel );
            QRectF rectPts = printer.paperRect( QPrinter::Point );
			painter.scale( rectPx.width()/rectPts.width(), rectPx.height()/rectPts.height() );


            for ( int iPage = 0; iPage < renderer.nPages(); iPage++ )
			{
				if ( iPage )
				{
                    printer.newPage();
				}

				renderer.printPage( &painter, iPage );
			}
        }

    }
}
double GlabelsQt::ptToPx(double pt) {
    return pt/72*dpi;
}
int GlabelsQt::Render( QWidget *parent,QString filename ,QString printername,QString outputFilename , QString source/*QMap<QString,QString> variableDefinitions*/)
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
        renderModel(parent,model,source,sheets,copies,first);
    }
    return 0;
}
int GlabelsQt::Render( QWidget *parent,QString filename ,QString printername,QString outputFilename,QList<glabels::merge::Record> records )
{
    QString sheets="1", copies="1", first="1";
    bool collated =true,groups=true,outlines=false,crop_marks =false,reverse=false;

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
    //filename=outputFilename;
    if ( !filename.isEmpty())
    {
        qDebug() << "Batch mode.";


        if ( filename == "-" )
        {
            filename = STDIN_FILENAME;
        }
        qDebug() << "Project file =" << filename;

        glabels::model::Model *model = glabels::model::XmlLabelParser::readFile( filename );
        renderModel(parent,model, printername,outputFilename,records,sheets,copies,first);
        return 0;
    }
}
