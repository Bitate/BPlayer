#include "srtHandler.hpp"

srtHandler::srtHandler(QObject *parent)
    : QObject(parent), fileDialog(new QFileDialog), pushButton(new QPushButton)
{
    QObject::connect(this, &srtHandler::fileUrlChanged, this, &srtHandler::responseToFileUrlChanged);
}

QUrl srtHandler::fileUrl()
{
    return fileDialog->getOpenFileUrl();
}

void srtHandler::setFileUrl(QUrl &new_file_url)
{
    fileDialog->selectUrl(new_file_url);
    emit fileUrlChanged(new_file_url);
}

void srtHandler::openSrtFile(QString& file_name)
{
    qDebug() << "Slot openSrtFile() gets invoked!";
    QFile srtFile(QString(fileDialog->getOpenFileName()));
    srtFile.open(QIODevice::ReadOnly);
    if(!srtFile.isOpen())
        std::cout << "Can't open srt file" << std::endl;
}

void srtHandler::responseToFileUrlChanged(QUrl& new_file_url)
{
    qDebug() << "Slot responseToFileUrlChanged() gets invoked!";
    QString url_string = new_file_url.toString();
    qDebug() << "URL string is: " << url_string;
}
