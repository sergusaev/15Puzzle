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
    void onTopTimeDownloaded(const std::vector<Record> &data);
    void onTopTurnsDownloaded(const std::vector<Record> &data);
    void onRecordAdded();
    void onUserAdded();
    void onPasswordDownloaded(const QString &password);



private:

    std::vector<Record> m_records;
    RequestsHandlerClient m_recordsHandler;
    CacheHandler m_cacheHandler;

    enum RecordRoles {
        NicknameRole = Qt::UserRole + 1,
        TimeRole,
        TurnsRole,
        DimensionRole,
    };
};

#endif // RECORDSMODEL_H
