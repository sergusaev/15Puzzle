#ifndef RECORDSMODEL_H
#define RECORDSMODEL_H

#include <QAbstractListModel>
#include <vector>
#include <utility>
#include "record.h"
#include "cachehandler.h"
#include "requestshandlerclient.h"

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

private slots:
    void onTopTimeDownloaded(const std::vector<Row> &data);
    void onTopTurnsDownloaded(const std::vector<Row> &data);

private:
    using Row = std::pair<QString, int>;

    std::vector<Row> m_recordRows;

    enum RecordRoles {
        NicknameRole = Qt::UserRole + 1,
        TimeRole,
        TurnsRole
    };
};

#endif // RECORDSMODEL_H
