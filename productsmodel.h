#ifndef PRODUCTSMODEL_H
#define PRODUCTSMODEL_H

// ProductsModel.h
#include <QAbstractTableModel>
#include <QJsonArray>
#include <QJsonObject>
#include <QVector>

class ProductsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ProductsModel(QObject *parent = nullptr);
    void setProducts(const QJsonArray &products);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
     QVector<bool> getCheckboxValues() const;
    QVector<long> getQuantityValues() const;
    void setQuantityValues(const QMap<QString,QString> &qyts);

    QString getStatusText(const QJsonObject &product) const;


    const QStringList &checkedRefs() const;

    const QJsonArray &products() const;

private:
    QJsonArray m_products;
    QVector<bool> m_checkboxValues;

    QVector<long> m_quantityValues;
    const int TRUNC=32;
};


#endif // PRODUCTSMODEL_H
