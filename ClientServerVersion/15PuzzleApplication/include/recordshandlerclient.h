#ifndef RECORDSHANDLERCLIENT_H
#define RECORDSHANDLERCLIENT_H

#include <QObject>
#include "record.h"
#include <networktypes.h>
#include "clientmanager.h"

class RecordsHandlerClient : public QObject
{
    Q_OBJECT
public:
    RecordsHandlerClient();
    bool requestTopTime(int dimension);
    bool requestTopTurns(int dimension);
    bool requestRecordAddition (const Record& record);
    bool requestUserAddition (const QString &nickname, const QString &password);
    bool requestPassword (const QString &nickname);

signals:
    void topTimeRequestCompleted(const std::vector<Record>& data);
    void topTurnsRequestCompleted(const std::vector<Record>& data);
    void recordAdditionCompleted();
    void userAdditionCompleted();
    void passwordRequestCompleted(const QString& password);

private slots:
    void onConnectionStateChanged(net::ConnectionState state);
    void onTopTimeDownloadSucceed(const std::vector<QVariant>& data);
    void onTopTurnsDownloadSucceed(const std::vector<QVariant>& data);
    void onRecordAdditionSucceed();
    void onUserAdditionSucceed();
    void onPasswordDownloadSucceed(const QVariant& data);

private:
    ClientManager& m_clientManager;
};

#endif // RECORDSHANDLERCLIENT_H
