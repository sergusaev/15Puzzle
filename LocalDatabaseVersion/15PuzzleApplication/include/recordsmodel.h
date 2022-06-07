#ifndef RECORDSMODEL_H
#define RECORDSMODEL_H

#include <QAbstractListModel>
#include <vector>
#include <utility>
#include "record.h"
#include "recordshandler.h"

class RecordsModel: public QAbstractListModel
{
    Q_OBJECT
public:

    RecordsModel();

    QHash<int, QByteArray> roleNames() const override;

    int rowCount(const QModelIndex &parent = {}) const override;

    QVariant data(const QModelIndex &index = {}, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE void getTimeRanking(int dimension);

    Q_INVOKABLE void getTurnsRanking(int dimension);

    QString timeToString(int time) const; // func to display time in records table

    Q_INVOKABLE QString rankToString(int rank) const;




private:

    std::vector<Record> m_records;

    RecordsHandler m_recordsHandler;

    enum RecordRoles {
        NicknameRole = Qt::UserRole + 1,
        TimeRole,
        TurnsRole,
        DimensionRole,
    };
};

#endif // RECORDSMODEL_H
