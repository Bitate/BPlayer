#ifndef SRTHANDLER_H
#define SRTHANDLER_H

#include <QObject>
#include <QFileDialog>
#include <QString>
#include <QFile>
#include <QAbstractButton>
#include <QTextStream>
#include <QTime>
#include <QDebug>
#include <QMessageBox>

#include <memory>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <iostream>

/**
 * SRT file format:
 * https://www.3playmedia.com/blog/create-srt-file/
 */
struct srtUnit {
    int sequenceNumber;
    long long beginTimeMilliseconds;
    long long endTimeMilliseconds;
    std::string caption;
};
class srtHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl fileUrl READ fileUrl WRITE setFileUrl NOTIFY fileUrlChanged)
public:
    explicit srtHandler(QObject *parent = nullptr);

public:
    QUrl fileUrl();
    void setFileUrl(QUrl& new_file_url);
    /**
     * @brief Load srt file.
     * @param local_file_path File to be opened.
     */
    void loadSrtFile(QString local_file_path);
    
    std::vector< srtUnit > parseSrtString(const std::string srtString);

private:
    void throwErrorMessage(QString errorSummary, QString concreteDescriptions);
    srtUnit parseSrtUnitString(const std::string srtUnitString);
    long long convertTimeCodeToMilliseconds(const std::string& timeCode);

signals:
    void fileUrlChanged(QUrl& new_file_url);

private slots:
    /**
     * @brief The parameter of signal fileUrlChanged() will be passed to be used in this slot.
     * @param new_file_url  Newly set file url passed from signal fileUrlChanged().
     */
    void responseToFileUrlChanged(QUrl& new_file_url);

private:
    QFileDialog* fileDialog;
    std::vector< srtUnit > srtObject;


    
};

#endif // SRTHANDLER_H
