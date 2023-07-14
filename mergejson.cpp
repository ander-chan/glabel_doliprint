#include "mergejson.h"
#include<QMap>
#include "merge/Record.h"
namespace glabels
{
    namespace merge
    {



        MergeJson::MergeJson(QList<Record> records,QList<QString> keys):m_records(records),m_iter_records(records),keys_(keys)
        {
             //setSource("");
        }

        MergeJson::MergeJson(const MergeJson *merge): Merge( merge )
          , m_records(merge->m_records)
          ,m_iter_records(merge->m_records)
        ,keys_(merge->keys_)
        {

        }

        ///



        ///
        /// Get key list
        ///
        QStringList MergeJson::keys() const        {

            return keys_;
        }


        ///
        /// Get primary key
        ///
        QString MergeJson::primaryKey() const
        {
            return keyFromIndex(0);
        }


        ///
        /// Open source
        ///
        void MergeJson::open()
        {

        }


        ///
        /// Close source
        ///
        void MergeJson::close()
        {

        }


        ///
        /// Read next record
        ///
        Record* MergeJson::readNextRecord()
        {
            //const Record *next = &m_records.next();

          if(m_iter_records.hasNext()){
            return new Record(m_iter_records.next());
          }

          return nullptr;
        }


        ///
        /// Key from field index
        ///
        QString MergeJson::keyFromIndex( int iField ) const
        {
                return QString::number( iField+1 );
        }

        ///
                /// Clone
                ///
                MergeJson* MergeJson::clone() const
                {
                    return new MergeJson( this );
                }


                ///
                /// Get ID
                ///
                QString MergeJson::id()
                {
                    return "text/json";
                }


                ///
                /// Create
                ///
                Merge* MergeJson::create()
                {
                    return new MergeJson( QList<Record>(), QList<QString>());
                }


    } // namespace merge
} // namespace glabels
