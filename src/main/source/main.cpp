
#include <QFont>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "processes_manager.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);

	QFont fon("Helvetica", 16);
	app.setFont(fon);

	QQmlApplicationEngine engine;
	QQmlContext * context = engine.rootContext();

	ProcessesManager::RegisterClasses();
//	ProcessesManager	proc;		// process to mount network drive
//	context->setContextProperty("proc", & proc);


	const QUrl url(QStringLiteral("qrc:/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
					 &app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);
	engine.load(url);

	return app.exec();
}
