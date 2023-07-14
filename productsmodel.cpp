#include "productsmodel.h"

#include <QCheckBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QTableWidget>

ProductsModel::ProductsModel(QObject *parent) : QAbstractTableModel(parent)
{
}

void ProductsModel::setProducts(const QJsonArray &products)
{
    beginResetModel();
    m_products = products;
    m_checkboxValues.resize(products.size());
    m_quantityValues.resize(products.size()); // Default quantity value is 1
    endResetModel();
    //get table view parent
    QTableView *table = qobject_cast<QTableView *>(parent());
    //iterate cols
    //expand table
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int i = 0; i < columnCount(); i++)
    {
        //set col width
        table->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
    
}
// get status text
QString ProductsModel::getStatusText(const QJsonObject &product) const
{
    QString status = "";
    if (product.value("status_buy").toString() == "1")
    {
        status += "En venta";
    }
    else
    {
        status += "Fuera de venta";
    }
    if (product.value("status").toString() == "1")
    {
        status += "/En compra";
    }
    else
    {
        status += "/Fuera de compra";
    }
    return status;
}


const QStringList &ProductsModel::checkedRefs() const
{
    // Return a list of checked refs
     QStringList *refs = new QStringList();
    for (int i = 0; i < m_checkboxValues.size(); i++){
        if (m_checkboxValues[i]){
            QJsonObject product = m_products[i].toObject();
            refs->append(product.value("ref").toString());
        }
    }
    return *refs;
}

const QJsonArray &ProductsModel::products() const
{
    return m_products;
}
int ProductsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_products.size();
}

int ProductsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 7; // Assuming 7 columns as in the original code
}

    QVariant ProductsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role == Qt::ToolTipRole && index.column() == 2)
    {
         QJsonObject product = m_products[index.row()].toObject();
        return product.value("label").toString();
    }
    if (role == Qt::DisplayRole)
    {
        QJsonObject product = m_products[index.row()].toObject();
        QString ref = product.value("ref").toString();
        QString barcode = product.value("barcode").toString();
       // QString label = product.value("label").toString();
        QString label=product.value("label").toString();
       
        if(label.length()>TRUNC){
            label.truncate(TRUNC);
            label.append("...");
        }
        
        QString stockReel = product.value("stock_reel").toString();
        QString status = getStatusText(product);

        switch (index.column())
        {
        case 0:
            return ref;
        case 1:
            return barcode;
        case 2:
            //return QtableWidgetItem(label);
            return label;
        case 3:
            return stockReel;
        case 4:
            return status;
        case 5:
            return QVariant::fromValue(m_quantityValues[index.row()]);
        case 6:
            return m_checkboxValues[index.row()];
        default:
            return QVariant();
        }
    }

    if (role == Qt::EditRole && index.column() == 5)
    {
        return QVariant::fromValue(m_quantityValues[index.row()]);
    }

    if (role == Qt::CheckStateRole && index.column() == 6)
    {
        return m_checkboxValues[index.row()] ? Qt::Checked : Qt::Unchecked;
    }

    return QVariant();
}

QVariant ProductsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole && section != 6)
        return QVariant();
   
    

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:
            return "Ref";
        case 1:
            return "Barcode";
        case 2:
            return "Label";
        case 3:
            return "Stock";
        case 4:
            return "Status";
        case 5:
            return "Cant.";
        case 6: 
        
            return "Select";
        default:
            return QVariant();
        }
    }

    return QVariant();
}

Qt::ItemFlags ProductsModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if (index.isValid() && (index.column() == 5 || index.column() == 6))
    {
        flags |= Qt::ItemIsEditable;
    }
    if (index.isValid() && index.column() == 6)
    {
        flags |= Qt::ItemIsUserCheckable;
    }
    return flags;
}

bool ProductsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole && index.column() == 5)
    {
        int quantity = value.toInt();
        if (quantity > 0)
        {
            m_quantityValues[index.row()] = quantity;
            emit dataChanged(index, index, {role});
            return true;
        }
    }

    if (role == Qt::CheckStateRole && index.column() == 6)
    {
        m_checkboxValues[index.row()] = (value == Qt::Checked);
        emit dataChanged(index, index, {role});
        return true;
    }

    return false;
}

QVector<bool> ProductsModel::getCheckboxValues() const
{
    return m_checkboxValues;
}



QVector<long> ProductsModel::getQuantityValues() const
{
    return m_quantityValues;
}
// setQuantityValues
void ProductsModel::setQuantityValues(const QMap<QString, QString> &qyts)
{
    // find row by ref (first col)

    for (int row = 0; row < m_products.size(); row++)
    {
        for (auto it = qyts.begin(); it != qyts.end(); ++it)
        {
            if (m_products[row].toObject().value("ref").toString() == it.key())
            {
                setData(index(row, 5), it.value(), Qt::EditRole);
                m_quantityValues[row]=it.value().toULong();
                // if qty > 0 then check the checkbox
                if (it.value().toInt() > 0)
                {
                    m_checkboxValues[row]=true;
                    setData(index(row, 6), Qt::Checked, Qt::CheckStateRole);
                }
                break;
            }
        }
    }
}
