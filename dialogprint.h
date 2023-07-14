#ifndef DIALOGPRINT_H
#define DIALOGPRINT_H

#include <QDialog>
#include <QGuiApplication>
#include <QLabel>
#include <QScreen>

#include <model/PageRenderer.h>

namespace Ui {
class DialogPrint;
}

class DialogPrint : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPrint(QWidget *parent = nullptr);
    ~DialogPrint();
    void setPageRender(glabels::model::PageRenderer *render, QSize dim);
protected:
    void paintEvent(QPaintEvent *e);
private slots:
    void on_pushButton_back_clicked();
    void on_pushButton_next_clicked();
private:
    Ui::DialogPrint *ui;
    glabels::model::PageRenderer *render;
    double dpi = QGuiApplication::primaryScreen()->physicalDotsPerInch();
    double ptToPx(double pt);
    int currentPage=0;
    QLabel *label_page;
    QPainter *paint;

    void renderPage();
};

#endif // DIALOGPRINT_H
