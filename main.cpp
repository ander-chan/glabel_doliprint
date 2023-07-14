
#include "mainwindow.h"
#include <QTranslator>
#include <QApplication>
#include <QTemporaryDir>
#include <QTemporaryFile>
#include <QPrinter>
#include <QPrintEngine>
#include <QPrinterInfo>
#include <QTextDocument>
#include <QPrintDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QBuffer>
#include <iostream>
#include <QIODevice>

#include <model/Config.h>
using namespace glabels::model;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    QApplication::installTranslator(&translator);
    QDir dir;

    // First, try finding templates directory relative to application path
    dir.cd( QApplication::applicationDirPath() );
    qDebug()<<dir.dirName();
    if ( (dir.dirName() == "bin") &&
         dir.cdUp() && dir.cd( "share" ) && dir.cd( "glabels-qt" ) && dir.cd( "templates" ) )
    {

    }

    // Next, try running out of the source directory.
    qDebug()<<Config::PROJECT_SOURCE_DIR;
    if ( dir.cd( Config::PROJECT_SOURCE_DIR ) && dir.cd( "templates" ) )
    {
        qDebug()<<"Ok tpl";
    }
    MainWindow w;
    w.show();
    return a.exec();
}
