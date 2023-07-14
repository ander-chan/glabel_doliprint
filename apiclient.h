#ifndef APICLIENT_H
#define APICLIENT_H


// ApiClient.h
#include <QObject>
#include <QJsonArray>

class QNetworkAccessManager;
class QNetworkReply;
class QNetworkRequest;

class ApiClient : public QObject
{
    Q_OBJECT

public:
    explicit ApiClient(QObject *parent = nullptr,const QString baseurl="", const QString token="",const QString entity="1");
    void getProducts(const QStringList &refs, const QString &searchText);

    QNetworkRequest getResource(QString segemnts);
    void addQueryItem(QNetworkRequest &resource, QMap<QString, QVariant> params);
    void getSupplierOrders(const QString &sortField="t.rowid", const QString &sortOrder="ASC", long limit=10, long page=0,
                           const QString &thirdPartyIds="", const QString &productIds="", const QString &status="",
                           const QString &sqlFilters="");
    void jsonArrayReceived(QString type, QJsonArray array);
signals:
    void productsReceived(const QJsonArray &products);
    void supplierOrdersReceived(const QJsonArray &orders);

private slots:
    void handleNetworkReply(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_manager;
    QString baseurl;
    QString token;
    QString entity;
};


#endif // APICLIENT_H
