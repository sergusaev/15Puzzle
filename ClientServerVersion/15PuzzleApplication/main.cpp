#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "gameboard.h"
#include "recordsmodel.h"
#include "usersettings.h"
#include "clientmanager.h"


int main(int argc, char *argv[])
{

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif


    QGuiApplication app(argc, argv);
    QCoreApplication::setOrganizationName("MySoft");
    QCoreApplication::setOrganizationDomain("myunexistentdomain.com");
    QCoreApplication::setApplicationName("15Puzzle");
    UserSettings settings;

    GameBoard model;
    RecordsModel timeRecordsModel;
    RecordsModel turnsRecordsModel;


//  register QML type, importing as module (deprecated)
//  qmlRegisterType<GameBoard>("Game", 1, 0, "GameBoardModel");
//  qmlRegisterType<RecordsModel>("Records", 1, 0, "RecordsModel");

    net::ConnectionArgumentsParser parser (*QCoreApplication::instance());
    ClientManager::instance()->setConnectionSettings(parser);

//  register C++ singlton as singlton in QML
    qmlRegisterSingletonInstance("AuthorizationManager", 1, 0, "AuthorizationManager", AuthorizationManager::instance());

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

//  register QML object from C++ via rootContext(), using it an object known all over QML
    engine.rootContext()->setContextProperty("gameBoardModel", &model);
    engine.rootContext()->setContextProperty("timeRecordsModel", &timeRecordsModel);
    engine.rootContext()->setContextProperty("turnsRecordsModel", &turnsRecordsModel);
    engine.rootContext()->setContextProperty("userSettings", &settings);



    engine.load(url);
    return app.exec();
}
