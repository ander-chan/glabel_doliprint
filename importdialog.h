#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include <QDialog>
#include <QJsonArray>
#include <QMap>

namespace Ui {
class ImportDialog;
}

class ImportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImportDialog(QWidget *parent = nullptr);
    ~ImportDialog();
    //set list of purchase order in list
    void setPurchaseOrderList(const QJsonArray &purchaseOrders);

    //signal to keypress event
    const QMap<QString, QString> &getProductsIds() const;

    const QMap<QString, QString> &getProductsQtys() const;

signals:
    void keyPressed(QKeyEvent *event);
    
private:
    Ui::ImportDialog *ui;
    //map of products ids and their quantity
    QMap<QString,QString> productsIds;
    //map of products ids and their quantity
    QMap<QString,QString> productsQtys;

};

#endif // IMPORTDIALOG_H
