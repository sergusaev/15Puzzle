#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "gameboard.h"
#include "recordsmodel.h"
#include "usersettings.h"


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


//    qmlRegisterType<GameBoard>("Game", 1, 0, "GameBoardModel");
//    qmlRegisterType<RecordsModel>("Records", 1, 0, "RecordsModel");


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("gameBoardModel", &model);
    engine.rootContext()->setContextProperty("timeRecordsModel", &timeRecordsModel);
    engine.rootContext()->setContextProperty("turnsRecordsModel", &turnsRecordsModel);
    engine.rootContext()->setContextProperty("userSettings", &settings);



    engine.load(url);

    settings.writeSettings("Stupid", "Asshole", 4);
    qDebug() << settings.readNickname();
    qDebug() << settings.readPassword();
    qDebug() << settings.readDimension();

    return app.exec();
}
