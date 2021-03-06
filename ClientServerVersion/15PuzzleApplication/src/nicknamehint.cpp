#include "nicknamehint.h"
#include "requestshandlerclient.h"

NicknameHint::NicknameHint()
{
    connect(RequestsHandlerClient::instance(), &RequestsHandlerClient::nicknameExistanceRequestCompleted,
            this, &NicknameHint::onNicknameExistanceRequestCompleted);
}

bool NicknameHint::requestNicknameExistanceCheck(const QString &nickname)
{
    return RequestsHandlerClient::instance()->requestNicknameExistance(nickname);
}

void NicknameHint::onNicknameExistanceRequestCompleted(bool exist)
{

        emit nicknameExists(exist);
}
