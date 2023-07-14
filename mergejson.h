#ifndef MERGEJSON_H
#define MERGEJSON_H
#include "merge/Merge.h"

#include <QFile>


namespace glabels
{
    namespace merge
    {

        ///
        /// MergeJson Merge Backend
        ///
        struct MergeJson : public Merge
        {

            /////////////////////////////////
            // Life Cycle
            /////////////////////////////////
            MergeJson(QList<glabels::merge::Record> records, QList<QString> keys);
        protected:


            MergeJson( const MergeJson* merge );
            ~MergeJson() override = default;


            /////////////////////////////////
            // Implementation of virtual methods
            /////////////////////////////////
        public:
            QStringList keys() const override;
            QString primaryKey() const override;
        protected:
            void open() override;
            void close() override;
            Record* readNextRecord() override;


            /////////////////////////////////
            // Private methods
            /////////////////////////////////
            QString keyFromIndex( int iField ) const;
            QStringList parseLine();


            /////////////////////////////////
            // Private data
            /////////////////////////////////
        private:
           QList<Record> m_records;
           QListIterator<Record> m_iter_records;
           QStringList keys_;
           int pos=0;
            /////////////////////////////////
            // Object duplication
            /////////////////////////////////
        public:
            MergeJson* clone() const override;


            /////////////////////////////////
            // Static methods
            /////////////////////////////////
        public:
            static QString id();
            static Merge* create();


        };

    }
}



#endif // MERGEJSON_H
