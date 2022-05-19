#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "gameboard.h"
#include "recordsmodel.h"


int main(int argc, char *argv[])
{

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    GameBoard model;
    RecordsModel recordsModel;

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
    engine.rootContext()->setContextProperty("recordsModel", &recordsModel);

    engine.load(url);

    return app.exec();
}
