#include "nicknamehint.h"
#include "requestshandlerclient.h"

NicknameHint::NicknameHint()
{
    connect(RequestsHandlerClient::instance(), &RequestsHandlerClient::nicknameExistanceRequestCompleted,
            this, &NicknameHint::onNicknameExistanceRequestCompleted);
}

void NicknameHint::requestNicknameExistanceCheck(const QString &nickname)
{
    RequestsHandlerClient::instance()->requestNicknameExistance(nickname);
}

void NicknameHint::onNicknameExistanceRequestCompleted(bool exist)
{
    if(exist) {
        emit nicknameExists();
    }
}
