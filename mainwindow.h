#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "apiclient.h"
#include "productsmodel.h"

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QMetaMethod>
#include <QNetworkRequest>
#include <QProcess>
#include <QTemporaryFile>
#include <QSettings>
#include <QJsonValueRef>
#include <merge/Record.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
inline void swap(QJsonValueRef v1, QJsonValueRef v2)
{
    QJsonValue temp(v1);
    v1 = QJsonValue(v2);
    v2 = temp;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void list();




public slots:

    void productsReceived(const QJsonArray &products);
protected slots:

private slots:

    void getProducts(QNetworkReply *reply);
    void sendPrint(bool);
    void on_txtSearch_returnPressed();
    void on_tableProducts_headerClicked(int logicalIndex);
    void openLabelDesign();
    void importPurchaseOrder();
    void importReception();
private:
    Ui::MainWindow *ui;
     QSettings *settings;
    bool masiveCheck=false;
    QNetworkAccessManager manager;
    QString token;
    QString baseurl;

    QNetworkRequest getResource( QString segments);
    void buildCsv(QJsonObject obj);
    QString buildCsvStr(QVariantMap obj);
    QMap<QString,QJsonObject> products;
    QProcess *process;

    QTemporaryFile* tmpFile(QString csv);
    void addQueryItem(QNetworkRequest &resource,QMap<QString,QVariant> params);
    QList< glabels::merge::Record> records;
    void getSelectRecords();
    bool refExists(const  QList< glabels::merge::Record> records, const QString valExists);
    QList<QString> selectedRefs(const  QList< glabels::merge::Record> records);
       QList<QString> selectedRefs_;
    //Api client
    ApiClient *api;
    //products model
    ProductsModel *model;


};
#endif // MAINWINDOW_H
