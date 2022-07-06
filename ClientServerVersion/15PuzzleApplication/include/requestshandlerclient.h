#ifndef REQUESTSHANDLERCLIENT_H
#define REQUESTSHANDLERCLIENT_H

#include <QObject>
#include "record.h"
#include <networktypes.h>
#include "clientmanager.h"

using Row = std::pair<QString, int>;

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
    bool requestPasswordValidation (const QString &nickname, const QString &password);
    bool requestNicknameExistance (const QString &nickname);
    QByteArray encodePassword(const QString& password);


signals:
    void topTimeRequestCompleted(const std::vector<Row>& data);
    void topTurnsRequestCompleted(const std::vector<Row>& data);
    void recordAdditionRequestCompleted(bool additionResult);
    void cacheDataAdditionRequestCompleted(bool additionResult);
    void userAdditionRequestCompleted(bool additionResult);
    void passwordValidationRequestCompleted(const bool validationResult);
    void nicknameExistanceRequestCompleted(bool exist);
    void internalServerErrorOccured(net::InternalServerError error);

private slots:
    void onTopTimeDownloadSucceed(const std::vector<QVariant>& data);
    void onTopTurnsDownloadSucceed(const std::vector<QVariant>& data);
    void onRecordAdditionSucceed(const QVariant &data);
    void onCacheDataAdditionSucceed(const QVariant &data);
    void onUserAdditionSucceed(const QVariant &data);
    void onPasswordValidationSucceed(const QVariant& data);
    void onNicknameExistanceRequestSucceed(const QVariant& data);
    void onInternalServerError(const QVariant& data);

private:
    RequestsHandlerClient();
};

#endif // REQUESTSHANDLERCLIENT_H
