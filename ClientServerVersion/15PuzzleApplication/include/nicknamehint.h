#ifndef NICKNAMEHINT_H
#define NICKNAMEHINT_H

#include <QObject>


class NicknameHint : public QObject
{
    Q_OBJECT
public:
    NicknameHint();
    Q_INVOKABLE void requestNicknameExistanceCheck(const QString &nickname);

signals:
    void nicknameExists();

private slots:
    void onNicknameExistanceRequestCompleted(bool exist);

};

#endif // NICKNAMEHINT_H
