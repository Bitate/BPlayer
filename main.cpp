#include <string>
#include <iostream>

#include <QtGui>
#include <QWidget>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include <QGuiApplication>
#include <QQuickItem>
#include <QQuickView>
#include <QAudio>
#include <QAudioDeviceInfo>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QObject>
#include <QFileDialog>

#include "include/srtHandler.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("app_directory_path", QApplication::applicationDirPath());

    srtHandler srt;
    engine.rootContext()->setContextProperty("srt_handler", &srt);

    engine.load(QUrl::fromLocalFile(":/qml/mainWindow.qml"));

    return app.exec();
}
