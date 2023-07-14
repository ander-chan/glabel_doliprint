#ifndef GLABELSQT_H
#define GLABELSQT_H

#include <QGuiApplication>
#include <QScreen>
#include <QObject>

#include <model/Model.h>

class GlabelsQt : public QObject
{
    Q_OBJECT


    void renderModel(QWidget *parent,glabels::model::Model *model,QString source,  QString sheets,QString copies,QString first="1" );

    void renderModel(QWidget *parent, glabels::model::Model *model, QList<glabels::merge::Record> records, QString sheets, QString copies, QString first);
    double ptToPx(double pt);
    double dpi = QGuiApplication::primaryScreen()->physicalDotsPerInch();
    void renderModel(QWidget *parent, glabels::model::Model *model, QString printername, QString outputFilename, QList<glabels::merge::Record> records, QString sheets, QString copies, QString first);
public:
    explicit GlabelsQt(QObject *parent = nullptr);
    int Print(QString filename, QString printername, QString outputFilename, QString source);
     int Render(QWidget *parent,QString filename, QString printername, QString outputFilename, QString source);
     int Render(QWidget *parent, QString filename,QString printername, QString outputFilename,QList<glabels::merge::Record> records);

signals:

private slots:

};

#endif // GLABELSQT_H
