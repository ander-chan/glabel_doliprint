#include "apiclient.h"


// ApiClient.cpp
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include <QString>

ApiClient::ApiClient(QObject *parent, QString baseurl, QString token,QString entity) : QObject(parent)
{
    this->baseurl=baseurl;
    this->token=token;
    this->entity=entity;
    m_manager = new QNetworkAccessManager(this);
}

void ApiClient::getProducts(const QStringList &refs, const QString &searchText)
{
    QNetworkRequest request = getResource("products");

    QMap<QString, QVariant> params;
    params["limit"] = 30;

    QString sqlfilters = "";

    if (!refs.isEmpty()) {
        sqlfilters = QString("(ref IN ('%1'))").arg(refs.join("','"));
        sqlfilters.append(" OR ");
    }

    sqlfilters.append(QString("((label:LIKE:'%%1%') OR (ref:LIKE:'%%1%') OR (barcode:LIKE:'%%1%'))").arg(searchText));
    params["sqlfilters"] = sqlfilters;

    addQueryItem(request, params);

    QNetworkReply *reply = m_manager->get(request);
    //add type to reply
    reply->setProperty("type", "products");
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        handleNetworkReply(reply);
    });
}
void ApiClient::addQueryItem(QNetworkRequest &resource,QMap<QString,QVariant> params)
{
    QUrl url = resource.url();

    QUrlQuery query( url.query());
    QMapIterator<QString, QVariant> i(params);
    while (i.hasNext()) {
        i.next();
        i.value();
        query.addQueryItem(i.key(), i.value().toString());
    }
    url.setQuery(query.query());
    resource.setUrl(url);
}

QNetworkRequest ApiClient::getResource(QString segemnts){
    QNetworkRequest rc(QUrl(this->baseurl+segemnts));
    qDebug()<<QUrl(this->baseurl+segemnts)<<token;


    rc.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    rc.setRawHeader("DOLAPIKEY", this->token.toUtf8());

    return rc;
}

//emit Json array recieved
void ApiClient::jsonArrayReceived(QString type, QJsonArray array)
{
    if(type=="products"){
        emit productsReceived(array);
    }else if(type=="supplierorders"){
        emit supplierOrdersReceived(array);
    }
}


void ApiClient::handleNetworkReply(QNetworkReply *reply)
{
    const QString type = reply->property("type").toString();
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if (statusCode.isValid() && statusCode.toInt() != 200) {
        QString error = reply->errorString();
        QRegExp rx(".*- server replied:(.*)");
        int pos = rx.indexIn(error);
        QStringList list = rx.capturedTexts();
        if (list.size() > 0) error = list.at(1);
        jsonArrayReceived(type,QJsonArray());
      
        return;
    }

    QByteArray response_data = reply->readAll();
    QJsonDocument json = QJsonDocument::fromJson(response_data);

    if (!json.isArray()) {
        jsonArrayReceived(type,QJsonArray());
        return;
    }

    QJsonArray array = json.array();
      jsonArrayReceived(type,array);

    reply->deleteLater();
}

void ApiClient::getSupplierOrders(const QString &sortField, const QString &sortOrder, long limit, long page,
                                  const QString &thirdPartyIds, const QString &productIds, const QString &status,
                                  const QString &sqlFilters)
{
    QNetworkRequest request = getResource("supplierorders");

    QMap<QString, QVariant> params;
    params["sortfield"] = sortField;
    params["sortorder"] = sortOrder;
    params["limit"] = QString::number(limit);
    params["page"] = QString::number(page);
    params["thirdparty_ids"] = thirdPartyIds;
    params["product_ids"] = productIds;
    params["status"] = status;
    params["sqlfilters"] = sqlFilters;

    addQueryItem(request, params);

    QNetworkReply *reply = m_manager->get(request);
    //add param to reply
    reply->setProperty("type","supplierorders");

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        handleNetworkReply(reply);
    });
}
