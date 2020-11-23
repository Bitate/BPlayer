#ifndef SRTHANDLER_H
#define SRTHANDLER_H

#include <QObject>
#include <QFileDialog>
#include <QString>
#include <QFile>
#include <QAbstractButton>
#include <QPushButton>
#include <QDebug>

#include <memory>
#include <iostream>

class srtHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl fileUrl READ fileUrl WRITE setFileUrl NOTIFY fileUrlChanged)
public:
    explicit srtHandler(QObject *parent = nullptr);

public:
    QUrl fileUrl();
    void setFileUrl(QUrl& new_file_url);

signals:
    void fileUrlChanged(QUrl& new_file_url);

private slots:
    /**
     * @brief  The parameter of signal fileUrlChanged() will be passed to be used in this slot.
     * @param  new_file_url  Newly set file url passed from signal fileUrlChanged().
     */
    void responseToFileUrlChanged(QUrl& new_file_url);
    void openSrtFile(QString& file_name);


private:
    QFileDialog* fileDialog;
    QPushButton* pushButton;
    std::vector< QString > srtString;
};

#endif // SRTHANDLER_H
