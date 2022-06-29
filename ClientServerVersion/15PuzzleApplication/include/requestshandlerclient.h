#ifndef REQUESTSHANDLERCLIENT_H
#define REQUESTSHANDLERCLIENT_H

#include <QObject>
#include "record.h"
#include <networktypes.h>
#include "clientmanager.h"

class RequestsHandlerClient : public QObject
{
    Q_OBJECT
public:
    ~RequestsHandlerClient();
    static RequestsHandlerClient *instance();
    bool requestTopTime(int dimension);
    bool requestTopTurns(int dimension);
    bool requestRecordAddition (const Record& record);
    bool requestRecordAdditionMultiple(const std::vector<DBTypes::DBEntry>& entries);
    bool requestUserAddition (const QString &nickname, const QString &password);
    bool requestPassword (const QString &nickname);
    bool requestNicknameExistance (const QString &nickname);

signals:
    void topTimeRequestCompleted(const std::vector<Record>& data);
    void topTurnsRequestCompleted(const std::vector<Record>& data);
    void recordAdditionRequestCompleted(bool additionResult);
    void cacheDataAdditionRequestCompleted(bool additionResult);
    void userAdditionRequestCompleted(bool additionResult);
    void passwordRequestCompleted(const QString& password);
    void nicknameExistanceRequestCompleted(bool exist);
    void internalServerErrorOccured(net::InternalServerError error);

private slots:
    void onConnectionStateChanged(net::ConnectionState state);
    void onTopTimeDownloadSucceed(const std::vector<QVariant>& data);
    void onTopTurnsDownloadSucceed(const std::vector<QVariant>& data);
    void onRecordAdditionSucceed(const QVariant &data);
    void onCacheDataAdditionSucceed(const QVariant &data);
    void onUserAdditionSucceed(const QVariant &data);
    void onPasswordDownloadSucceed(const QVariant& data);
    void onNicknameExistanceRequestSucceed(const QVariant& data);
    void onInternalServerError(const QVariant& data);

private:
    RequestsHandlerClient();
};

#endif // REQUESTSHANDLERCLIENT_H
