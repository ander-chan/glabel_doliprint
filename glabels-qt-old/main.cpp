#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QPrinter>
#include <QPrinterInfo>
#include <QTranslator>
#include <QLibraryInfo>
#include "merge/Factory.h"
#include "model/XmlLabelParser.h"
#include "model/Version.h"
#include "model/FileUtil.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName( "glabels.org" );
        QCoreApplication::setOrganizationDomain( "glabels.org" );
        QCoreApplication::setApplicationName( "glabels-batch-qt" );
        QCoreApplication::setApplicationVersion( glabels::model::Version::LONG_STRING );

        //
        // Setup translators
        //
        QLocale locale = QLocale::system();
        QString qtTranslationsDir = QLibraryInfo::location( QLibraryInfo::TranslationsPath );
        QString myTranslationsDir = glabels::model::FileUtil::translationsDir().canonicalPath();

        QTranslator qtTranslator;
        if ( qtTranslator.load( locale, "qt", "_", qtTranslationsDir ) )
        {
            a.installTranslator(&qtTranslator);
        }

        QTranslator glabelsTranslator;
        if ( glabelsTranslator.load( locale, "glabels", "_", myTranslationsDir ) )
        {
            a.installTranslator(&glabelsTranslator);
        }

        QTranslator templatesTranslator;
        if ( templatesTranslator.load( locale, "templates", "_", myTranslationsDir ) )
        {
            a.installTranslator(&templatesTranslator);
        }
    MainWindow w;
    w.show();
    return a.exec();
}
