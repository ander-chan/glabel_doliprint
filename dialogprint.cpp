#include "dialogprint.h"
#include "ui_dialogprint.h"
#include <QDebug>
#include <QLabel>
#include "model/PageRenderer.h"
DialogPrint::DialogPrint(QWidget *parent) : QDialog(parent),
                                            ui(new Ui::DialogPrint)
{
    ui->setupUi(this);
}

DialogPrint::~DialogPrint()
{
    delete ui;
}

void DialogPrint::setPageRender(glabels::model::PageRenderer *render, QSize dim)
{
    this->setWindowTitle("Printing " + QString::number(render->nItems()) + " items on " + QString::number(render->nPages()) + " pages.");
    this->render = render;
    ui->scrollArea->resize(dim.width(), ui->scrollArea->height());
    ui->verticalLayout->setContentsMargins(0, 0, 0, 0);
    // for(int page=0;page<this->render->nPages() ;page++){

    label_page = new QLabel(this);
    ui->verticalLayout->addWidget(label_page);
    label_page->resize(dim);
    QPixmap pix(dim);

    QPainter paint(&pix);
    pix.fill(Qt::white);
    this->render->printPage(&paint, currentPage);
    // pix.fill( Qt::white );
    // paint.setPen(QColor(0, 0, 0, 255));
    // paint.drawRect(QRect(80,120,200,100));
    // debug pix width
    // qDebug()<<paint.width();
    label_page->setPixmap(pix);
     QString footer = "Page " + QString::number(currentPage+1) + " of " + QString::number(render->nPages());
        ui->label_page->setText(footer);

    //}

    update();
}
double DialogPrint::ptToPx(double pt)
{
    return pt / 72 * dpi;
}
void DialogPrint::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
}
// implement slot on_pushButton_back_clicked
void DialogPrint::renderPage()
{
    QPixmap pix(label_page->size());
    QPainter paint(&pix);
    pix.fill(Qt::white);
    this->render->printPage(&paint, currentPage);
    label_page->setPixmap(pix);
}

void DialogPrint::on_pushButton_back_clicked()
{
    // debug method
    qDebug() << "back";
    if (currentPage > 0)
    {
        currentPage--;
        //build footer
        QString footer = "Page " + QString::number(currentPage+1) + " of " + QString::number(render->nPages());
        ui->label_page->setText(footer);
        renderPage();
    }
}
// implement slot on_pushButton_next_clicked

void DialogPrint::on_pushButton_next_clicked()
{
    // debug method
    qDebug() << "next" << render->nPages();
    if (currentPage < render->nPages() - 1)
    {
        currentPage++;
        //build footer
        QString footer = "Page " + QString::number(currentPage+1) + " of " + QString::number(render->nPages());
        ui->label_page->setText(footer);
        renderPage();
    }
}
