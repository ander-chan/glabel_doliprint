#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <glabels-batch/glabelsbatch.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GlabelsBatch gb(this);
   QMap<QString,QString> map;
   map["ref"]="123";
   map["labe"]="uno";
   gb.main("/home/ander/qtproyects/glabels-qt/sticker32x25.glabels","PDF","","/home/ander/qtproyects/glabels-qt/glabels-input.csv");
}

MainWindow::~MainWindow()
{
    delete ui;
}

