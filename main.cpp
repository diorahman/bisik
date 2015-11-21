#include <QQmlContext>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "app.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    suara::App mainApp;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("App", &mainApp);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

