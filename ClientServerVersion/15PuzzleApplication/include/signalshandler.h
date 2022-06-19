#ifndef SIGNALSHANDLER_H
#define SIGNALSHANDLER_H

#include "networktypes.h"
#include <QObject>

class SignalsHandler : public QObject
{
    Q_OBJECT
public:
    SignalsHandler();

private slots:
    void onNoServerConnection();
    void onNicknameChanged(const QString &nickname);
    void onPasswordChanged(const QString &password);
    void onEthalonPasswordChanged(const QString &ethalonPassword);
    void onDimensionChanged(int dimension);

signals:
    void noServerConnection();
    void nicknameChanged();
    void passwordChanged();
    void ethalonPasswordChanged();
    void dimensionChanged();
};

#endif // SIGNALSHANDLER_H
