#include "importdialog.h"
#include "ui_importdialog.h"

#include <QJsonObject>
#include <QKeyEvent>
#include <QPushButton>
#include <QDebug>
ImportDialog::ImportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportDialog)
{
    ui->setupUi(this);
    ui->listWidget->setWindowTitle("Placeholder Title");
    //emit signal to keypress event on text edit search
    connect(ui->txtSearch,&QLineEdit::textChanged,[=](const QString &text){
        emit keyPressed(new QKeyEvent(QEvent::KeyPress,Qt::Key_Return,Qt::NoModifier,text));
    });
    //disable ok button
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false); 
    //check if seletion is not empty


    //on select item in list
    connect(ui->listWidget,&QListWidget::itemSelectionChanged,[=](){
        if(ui->listWidget->selectedItems().size()==0){
            return;
        }
        //get selected item
        QListWidgetItem *item=ui->listWidget->selectedItems().first();
        //get data from item
        QJsonObject obj=item->data(Qt::UserRole).toJsonObject();
        //get json array for lines field
        QJsonArray lines=obj.value("lines").toArray();
         //clear maps
        productsIds.clear();
        productsQtys.clear();
         ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(lines.size()>0);
        //if lines is empty
        if(lines.size()==0){
            return;
        }
       
        //fill map of products ids and their quantity with  id and qty
        for (const QJsonValue &value : lines) {
            QJsonObject obj = value.toObject();
             productsIds.insert(obj.value("fk_product").toString(),obj.value("product_ref").toString());
            productsQtys.insert(obj.value("product_ref").toString(),obj.value("qty").toString());
        }
    });
}

ImportDialog::~ImportDialog()
{
    delete ui;
}

void ImportDialog::setPurchaseOrderList(const QJsonArray &orders)
{
    //clear list
    ui->listWidget->clear();
    //debug size of purchase orders
    qDebug()<<"size of purchase orders"<<orders.size();
    // iterate and set ref and every object has data in list
    for (const QJsonValue &value : orders) {
        QJsonObject obj = value.toObject();
        ui->listWidget->addItem(obj.value("ref").toString());
        ui->listWidget->item(ui->listWidget->count()-1)->setData(Qt::UserRole,obj);
        //update list
        ui->listWidget->update();
    }


}

const QMap<QString, QString> &ImportDialog::getProductsIds() const
{
    return productsIds;
}

const QMap<QString, QString> &ImportDialog::getProductsQtys() const
{
    return productsQtys;
}
