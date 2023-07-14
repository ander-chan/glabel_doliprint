#ifndef GLABELSBATCH_H
#define GLABELSBATCH_H

#include <QObject>

class GlabelsBatch : public QObject
{
    Q_OBJECT
public:
    explicit GlabelsBatch(QObject *parent = nullptr);
     int main( QString filename ,QString printername,QString outputFilename, QString source );

signals:

};

#endif // GLABELSBATCH_H
