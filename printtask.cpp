#include "printtask.h"
#include <QProcess>
#include <QDebug>
#include <QTemporaryFile>
PrintTask::PrintTask(QObject *parent) : QObject(parent)
{

}
void PrintTask::set(QString csv,QString labeltpl,QString printername,QString jobname)
{
    this->csv=csv;
    this->labeltpl=labeltpl;
    this->printername=printername;
    this->jobname=jobname;
}

void PrintTask::run()
{
    QString tmpFile;
    QTemporaryFile file_;

    //if (  file.open( QIODevice::WriteOnly )) {
    if (  file_.open()) {
        tmpFile=file_.fileName();
        file_.close();
        QFile file(tmpFile);
        file.open( QIODevice::WriteOnly );
        QTextStream stream(&file);
        //qDebug()<<csv;
        stream << csv;
        file.close();

        QProcess *process1=new QProcess(this->parent());
        QProcess *process2=new QProcess(this->parent());
        QProcess *process3=new QProcess(this->parent());
        QProcess *process4=new QProcess(this->parent());
        process1->setProcessChannelMode(QProcess::ForwardedChannels);
        process2->setProcessChannelMode(QProcess::ForwardedChannels);
        process3->setProcessChannelMode(QProcess::ForwardedChannels);
        process4->setProcessChannelMode(QProcess::ForwardedChannels);

        process1->setStandardOutputProcess(process2);
        process2->setStandardOutputProcess(process3);
        process3->setStandardOutputProcess(process4);


        connect(process1, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                [process1](int exitCode, QProcess::ExitStatus exitStatus){
            qDebug()<<"process1"<<exitCode<<exitStatus;

        });
        connect(process2, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                [process2](int exitCode, QProcess::ExitStatus exitStatus){
            qDebug()<<"process2"<<exitCode<<exitStatus;
        });
        connect(process3, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                [process3](int exitCode, QProcess::ExitStatus exitStatus){
            qDebug()<<"process3"<<exitCode<<exitStatus;
        });
        connect(process4, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                [&file,process4](int exitCode, QProcess::ExitStatus exitStatus){
            qDebug()<<"process4"<<exitCode<<exitStatus;
        });

        // qDebug()<<"echo '"+csv+"'";
        //process1->write(csv);
        process2->start("glabels-3-batch"
                        ,QStringList()
                        <<"-i"
                        <<"-"
                        <<"-o"
                        <<"/dev/stdout"
                        <<labeltpl+".glabels"
                        );

        process3->start("sed", QStringList() << "-n"<<"/%PDF-1.5/,/%%EOF/p");
        process4->start("lp", QStringList() <<"-d"<<printername<<"-t"<<jobname);
        // process2.setProcessChannelMode(QProcess::ForwardedChannels);


    }

    qDebug()<< QString("glabels-3-batch -i %1 -o /dev/stdout %2.glabels | sed -n '/%PDF-1.5/,/%%EOF/p' | lp -d %3 -t %4")
               .arg(tmpFile,labeltpl,printername,jobname);
}

