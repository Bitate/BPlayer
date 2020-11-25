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
    // Life time management
public:
    explicit srtHandler(QObject *parent = nullptr);

    // Public methods
public:
    /**
     * @brief  Load srt file.
     * @param  local_file_path  Path to the file that will be loaded and parsed.
     */
    void loadSrtFile(QString local_file_path);
    
    std::vector< srtUnit > parseSrtString(const std::string srtString);

    // Private methods
private:
    /**
     * @brief  Pop up Qt error message box.
     * @param  errorBoxTitle  Error box's title.
     * @param  errorDescription  Error description.
     */
    void popUpErrorMessage(QString errorBoxTitle, QString errorDescription);

    /**
     * @brief  Parse srtUnit string and fill the srtUnit struct.
     * @param  srtUnitString  Each srt unit string.
     * @return  srtUnit structure.
     */
    srtUnit parseSrtUnitString(const std::string srtUnitString);

    /**
     * @brief  Convert timecode string to milliseconds with type of long long integer.
     * @param  timeCode Srt time code string.
     * @return  Milliseconds.
     */
    long long convertTimeCodeToMilliseconds(const std::string& timeCode);

    // Qt getters
public:
    QUrl fileUrl();

    // Qt setters
public:
    void setFileUrl(QUrl& new_file_url);

    // Qt signals
signals:
    void fileUrlChanged(QUrl& new_file_url);

    // Qt slots
private slots:
    /**
     * @brief  The parameter of signal fileUrlChanged() will be passed to be used in this slot.
     * @param  new_file_url  Newly set file url passed from signal fileUrlChanged().
     */
    void responseToFileUrlChanged(QUrl& new_file_url);

    // Private variables
private:
    /**
     * @brief  file dialog handler.
     */
    QFileDialog* fileDialog;

    /**
     * @brief  After loading srt file, the srt string will be parsed and stored to this variable.
     */
    std::vector< srtUnit > srtObject;
};

#endif // SRTHANDLER_H
