#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>
#include "telegid.h"
#include "fso.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    app.setOrganizationName("programmstroy");
    app.setOrganizationDomain("programmstroy.ru");
    app.setApplicationName("QTVPlayer");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    TELEGID gid;
    FSO fso;

    QQmlContext* context = engine.rootContext();
    context->setContextProperty("telegid", &gid);
    context->setContextProperty("fso",&fso);

    qmlRegisterUncreatableType<FSO>("ru.programmstroy.QTVPlayer", 1, 0,
                                    "FileSystemModel",
                                    "Cannot create a FileSystemModel instance");

    engine.load(url);
    return app.exec();
}
