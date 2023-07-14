#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstddef>
#include <QtNetwork/QNetworkRequest>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QUrlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QMetaMethod>
#include <QPushButton>
#include <QDir>
#include <QTableWidgetItem>
#include <QJsonArray>
#include <QPrinterInfo>
#include <QPushButton>
#include <QObject>
#include <QMap>
#include <QProcess>
#include <QTableWidget>
#include <QTimer>
#include <QTemporaryFile>
#include <merge/Record.h>
#include "apiclient.h"
#include "dialogprint.h"
#include "glabelsqt.h"
#include "importdialog.h"
#include "printtask.h"
#include <QDialogButtonBox>
#include <QEvent>
#include <QFileDialog>
#include <QKeyEvent>
#include <QListWidget>
#include <QMap>
#include <QMap>
#include <QMessageBox>
#include <QSettings>
#include <QTextEdit>
#include <QThread>
#include <QVector>
#include <QVector>

void MainWindow::getSelectRecords()
{

    records.clear();
    // iterate products with for loop
    const QJsonArray products = model->products();
    QVector<bool> checkboxValues = model->getCheckboxValues();
    QVector<long> quantityValues = model->getQuantityValues();
    for(int row=0; row < products.size(); row++)
    {
        // if  col 4 in table is not checked continue
        //if( ui->tableProducts->item(row,6)->checkState() != Qt::Checked)
        if(checkboxValues[row] == false)
            continue;
        //get int qty from col 6
        //int qty = ui->tableProducts->item(row,5)->text().toInt();
        int qty = quantityValues[row];
        // if qty is empty or 0 continue
        if(qty <= 0) continue;
        // get product ref from col 0
        //QString ref = products[row].toObject().value("ref").toString();

        //get p from products
        QVariantMap pMap = products[row].toObject().toVariantMap();
        QMap<QString,QVariant>::const_iterator iter = pMap.constBegin();
        glabels::merge::Record r=new glabels::merge::Record( );

        while(iter != pMap.constEnd())
        {
            r[iter.key()]=iter.value().toString();
            r.setSelected(true);            
            // append qty times r in records
            //qDebug()<<"key:" <<iter.key()<<" value"<<iter.value();
            ++iter;
        }
        for(int i=0;i<qty;i++)
            records.append(r);

        qDebug()<<"total records added="<<records.size();

    }
}

bool MainWindow::refExists( const QList<glabels::merge::Record> records, const QString ref)
{
    //qDebug()<<"refExists()";
    foreach(glabels::merge::Record r, records)
    {
        //qDebug()<<r["ref"].trimmed()<< ref.trimmed();
        if(r["ref"].trimmed() == ref.trimmed())
        {
            return true;
        }
    }
    return false;
}

QList<QString> MainWindow::selectedRefs(const QList<glabels::merge::Record> records)
{
    QList<QString> refs;
    foreach(glabels::merge::Record r, records)
    {
        refs.append( r["ref"].trimmed());
    }
    return refs;
}

void MainWindow::sendPrint(bool)
{

    getSelectRecords();
    //get fileLabel from settings
    settings->beginGroup("files");
    QString fileLabel = settings->value("file_label").toString();
    settings->endGroup();

    GlabelsQt gl(this);
    //if empty fileLabel show error and return
    if(fileLabel.isEmpty())
    {
        QMessageBox::critical(this,"Error","Please set file label in settings");
        return;
    }
    //if records size is 0 show tooltip in button and return else clean tooltip
    if(records.size() == 0)
    {
        ui->btnPrint->setToolTip("No products selected");
        return;
    }
    else
        ui->btnPrint->setToolTip("");
    gl.Render(this,fileLabel,ui->cb_printers->currentText(),"/home/ander/PDF/home_ander_PDF.pdf",records);
    qDebug()<<"Dialog!!";
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new ProductsModel(ui->tableView);
    ui->tableView->setModel(model);

    QIcon icon(":img/glabels-icon.png");
    setWindowIcon(icon);


    connect(ui->btnPrint, &QPushButton::clicked, this,
            &MainWindow::sendPrint
            );

    QList<QPrinterInfo> info_list = QPrinterInfo::availablePrinters();
    foreach ( QPrinterInfo info, info_list )
    {
        ui->cb_printers->addItem(info.printerName().toUtf8());
    }
    ui->cb_printers->setCurrentText(QPrinterInfo::defaultPrinter().printerName());

    // load url,entity,login, password from settings->ini file loclal path
    settings= new QSettings("settings.ini", QSettings::IniFormat);
    //debug settings file path
    qDebug() <<"try to loading "<< settings->fileName();
    settings->beginGroup("server");
    QString url = settings->value("url").toString();
    QString entity = settings->value("entity").toString();
    QString login = settings->value("login").toString();
    QString password = settings->value("password").toString();
    //token
    QString token = settings->value("token").toString();
    settings->endGroup();

    baseurl=url+"/api/index.php/";

    api = new ApiClient(this,baseurl,token,entity);
    //conect signal on finished to on get products
    connect(api, &ApiClient::productsReceived, this, &MainWindow::productsReceived);


    /*
    connect(&manager, &QNetworkAccessManager::finished, this, &MainWindow::onLogin);
    QNetworkRequest userLogin(QUrl(baseurl+"login"));
    userLogin.setRawHeader("Content-Type", "application/json");



    QJsonObject obj;

    obj["login"] = login;
    obj["password"] = password;
    obj["entity"] = entity;
    qDebug().noquote()<<url<<QJsonDocument(obj).toJson();
    QNetworkReply *reply = manager.post(userLogin,QJsonDocument(obj).toJson());
    connect(reply, &QNetworkReply::finished, this, [this,reply]{
        QVariant statusCode = reply->attribute( QNetworkRequest::HttpStatusCodeAttribute );

        if (statusCode.isValid()) {
            qDebug() << "Status Code: " << statusCode.toString();
            //simulate enter press on search
            QKeyEvent *event = new QKeyEvent ( QEvent::KeyPress, Qt::Key_Enter, Qt::NoModifier);
            QCoreApplication::postEvent (ui->txtSearch, event);

            //  QThread::sleep(1);
            //check all items table on init
            //  for(int i=0;i<ui->tableProducts->rowCount();i++)  {
            // col 4 checkbox is checked
            //    ui->tableProducts->item(i,4)->setCheckState(Qt::Checked);
            // }
        }else{
            qDebug() << "Status Code: " << statusCode.toString();
            qDebug() << reply->error();
        }
        this->onLogin(reply);
    });

    qDebug()<<"start";
    */
    ui->cb_printers->setCurrentIndex(1);

    //add button to toolbar with label icon and open file dialog
    ui->toolBar->addAction(QIcon(":img/glabels.png"),tr("Open label file"),this,&MainWindow::openLabelDesign);
    //add button to toolbar for purchase order
    ui->toolBar->addAction(QIcon(":img/file-invoice-solid.png"),tr("Import from purchase order"),this,&MainWindow::importPurchaseOrder);
    //add button to toolbar for import from recepction
    ui->toolBar->addAction(QIcon(":img/dolly-solid.png"),tr("Import from reception"),this,&MainWindow::importReception);

    list();


}
//productsReceived
void MainWindow::productsReceived(const QJsonArray &products)
{
    //get list from products
     QVariantList products_ = products.toVariantList();
    //set products to model
    //
    std::sort(products_.begin(), products_.end(), [this](const QVariant &p1, const QVariant &p2) {


        QString ref=p1.toMap().value("ref").toString();
        QString ref2=p2.toMap().value("ref").toString();
        foreach ( glabels::merge::Record r, this->records) {
            // qDebug()<<ref<<ref2<<r["ref"];
            if (ref == r["ref"]){
                return true;
            }
            else if(ref2 == r["ref"]){
                return false;
            }
        }

        return ref < ref2;
    });
    model->setProducts(products);
    //check all items in records
   /* for(int i=0;i<ui->tableView->rowCount();i++)  {
        //get ref from table
        QString ref=ui->tableView->item(i,0)->text();
         if(refExists(records,ref)){
        // col 4 checkbox is checked
        model->setData(model->index(i,4),Qt::Checked,Qt::CheckStateRole);
         }
    }*/

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::list()
{

    QStringList refs = model->checkedRefs();

        api->getProducts(refs,ui->txtSearch->text());

}

void MainWindow::getProducts(QNetworkReply *reply){
    QByteArray response_data;

    QJsonDocument json = QJsonDocument::fromJson(response_data);
    QJsonObject obj = json.object();
    obj.toVariantMap();
    reply->deleteLater();
}

QNetworkRequest MainWindow::getResource(QString segemnts){
    QNetworkRequest rc(QUrl(this->baseurl+segemnts));


    rc.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    rc.setRawHeader("DOLAPIKEY", this->token.toUtf8());

    return rc;
}
// create slot to search on txtSearc key press enter
void MainWindow::on_txtSearch_returnPressed()
{
    selectedRefs_=selectedRefs(records);
    list();
    getSelectRecords();

}
//create method  slot when header clicked
void MainWindow::on_tableProducts_headerClicked(int logicalIndex)
{
    if(logicalIndex==4){
        //if clicked on checkbox column
        //get all refs from table
        QStringList refs;
        masiveCheck=!masiveCheck;
       /* for(int i=0;i<ui->tableProducts->rowCount();i++){
            //check col 4 item
            ui->tableProducts->item(i,4)->setCheckState(masiveCheck?Qt::Checked:Qt::Unchecked);
        }*/
    }
}
// created method slot openLabelDesign
void MainWindow::openLabelDesign()
{
    //open label design
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"), "",
                                                    tr("Label Files (*.glabels)"));
    DialogPrint *dialogPrint = new DialogPrint(this);
    if(!fileName.isEmpty()){
        //store in settings fileName as file_label in group files
        settings->beginGroup("files");
        settings->setValue("file_label",fileName);
        settings->endGroup();
        sendPrint(true);
    }
    //else show warning
    else{
        QMessageBox::warning(this, tr("Error"),
                             tr("No file selected"));
    }
}
//importPurchaseOrder
void MainWindow::importPurchaseOrder()
{
    //show a dialog on fly with a text edit and list of purchase orders and waith to press key

    //build dialog
    ImportDialog dialog(this);
    //set title 
    dialog.setWindowTitle(tr("Import from purchase order"));
    //get all purchase orders
    //sqlfilter fk_statut>0

    api->getSupplierOrders("t.rowid","DESC",10,0,"","","fk_statut>0");
    //connect signal finished to slot getSupplierOrders
   connect(api, &ApiClient::supplierOrdersReceived, [this, &dialog](const QJsonArray &orders) {
    // Aquí puedes realizar las acciones que deseas con los pedidos recibidos
        dialog.setPurchaseOrderList(orders);
        dialog.show();
    });
   //on ok pressed
   if(dialog.exec() ==  QDialog::Accepted){
       //get map of selected products
       const QMap<QString,QString> mapProducts= dialog.getProductsQtys();
       //get Qstringlist of keys
       const QStringList keys=mapProducts.keys();

       //get product
       api->getProducts(keys,"__NOTHING__");
       //connect signal finished to slot getProducts
       connect(api, &ApiClient::productsReceived, [this, mapProducts](const QJsonArray &products) {
            //debug size of products
              qDebug()<<"size of products"<<products.size();

           model->setProducts(products);
           model->setQuantityValues(mapProducts);
           //update table
           ui->tableView->update();
       });
   }
   //destroy dialog
    dialog.deleteLater();



}
//importReception
void MainWindow::importReception()
{

}
