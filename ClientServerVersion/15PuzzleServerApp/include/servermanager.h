#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <QTcpServer>
#include <package.h>
#include "requestshandlerserver.h"
#include <connectionargumentsparser.h>
#include <QMutex>

class ServerManager : public QObject
{
    Q_OBJECT
public:
    ServerManager(const net::ConnectionArgumentsParser& parser);

private slots:
    void onNewConnection();
    void onClientDisconnected();
    void onDataArrived();

    void notify(const net::Package& package, QTcpSocket* socket);

private:
    QTcpServer m_server;
    QMutex m_mux;
    const net::ConnectionArgumentsParser& m_parser;

    std::vector<QTcpSocket*> m_clients;
    RequestHandlerServer m_requestHandler;

    void handlePackage(net::Package& package, QTcpSocket* socket);

    void connectSignals();
    void connectSocketSignals(QTcpSocket* socket);
};

#endif //SERVERMANAGER_H
