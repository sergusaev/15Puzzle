#include "errorhandler.h"
#include "requestshandlerclient.h"
#include "authorizationmanager.h"

ErrorHandler::ErrorHandler()   
{
    connect(RequestsHandlerClient::instance(), &RequestsHandlerClient::internalServerErrorOccured,
            this, &ErrorHandler::onInternalServerErrorOccured);
//    connect(AuthorizationManager::instance(), &AuthorizationManager::noServerConnection,
//            this, &ErrorHandler::onNoServerConnection);
}


ErrorHandler::~ErrorHandler()
{

}

bool ErrorHandler::noServerConnection() const
{
    return m_noServerConnection;
}

void ErrorHandler::setNoServerConnection(bool newNoServerConnection)
{
    if (m_noServerConnection == newNoServerConnection)
        return;
    m_noServerConnection = newNoServerConnection;
    emit noServerConnectionChanged();
}

bool ErrorHandler::internalServerError() const
{
    return m_internalServerError;
}

void ErrorHandler::setInternalServerError(bool newInternalServerError)
{
    if (m_internalServerError == newInternalServerError)
        return;
    m_internalServerError = newInternalServerError;
    emit internalServerErrorChanged();
}

bool ErrorHandler::cacheAddingTextVisible() const
{
    return m_cacheAddingTextVisible;
}

void ErrorHandler::setCacheAddingTextVisible(bool newCacheAddingTextVisible)
{
    if (m_cacheAddingTextVisible == newCacheAddingTextVisible)
        return;
    m_cacheAddingTextVisible = newCacheAddingTextVisible;
    emit cacheAddingTextVisibleChanged();
}

void ErrorHandler::onNoServerConnection()
{
    setNoServerConnection(true);
}


void ErrorHandler::onInternalServerErrorOccured(const QVariant &data)
{

        QVariantList dataList = data.toList();
        QVariant errorType = dataList.front();
        dataList.pop_front();
        switch(static_cast<net::InternalServerError>(errorType.toInt())) {
        case net::InternalServerError::RECORD_ADDITION_ERROR: {
            qDebug() << "Internal server error occured, adding record into cache";
            Record record;
            record.setNickname(dataList.front().toString());
            dataList.pop_front();
            record.setTime(dataList.front().toInt());
            record.setTurns(dataList.back().toInt());
            CacheHandler::instance()->addRecord(record);
            setCacheAddingTextVisible(true);
            break;
        }
        case net::InternalServerError::PASSWORD_ERROR:
        case net::InternalServerError::USER_ADDITION_ERROR:
        case net::InternalServerError::TOP_TIME_ERROR:
        default:
            break;
        }
        setInternalServerError(true);
}




