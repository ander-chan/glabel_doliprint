#ifndef PRINTTASK_H
#define PRINTTASK_H

#include <QObject>

class PrintTask : public QObject
{
    Q_OBJECT
public:
    explicit PrintTask(QObject *parent = nullptr);
    void set(QString csv, QString labeltpl, QString printername, QString jobname);
private:
    QString csv;
    QString labeltpl;
    QString printername;
    QString jobname;
public slots:
    void run();

signals:
      void finished();
};

#endif // PRINTTASK_H
