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
    int beginTimeMilliseconds;
    int endTimeMilliseconds;
    std::string caption;
};
class srtHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl fileUrl READ fileUrl WRITE setFileUrl NOTIFY fileUrlChanged)
    Q_PROPERTY(int currentSectionBegin READ currentSectionBegin WRITE setCurrentSectionBegin NOTIFY currentSectionBeginChanged)
    Q_PROPERTY(int currentSectionEnd READ currentSectionEnd WRITE setCurrentSectionEnd NOTIFY currentSectionEndChanged)
    Q_PROPERTY(int currentSectionSequenceNumber READ currentSectionSequenceNumber WRITE setCurrentSectionSequenceNumber NOTIFY currentSectionSequenceNumberChanged)
    Q_PROPERTY(bool hasSrtFile READ hasSrtFile)
    Q_PROPERTY(QString subtitleText READ subtitleText)
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
     * @brief  Convert timecode string to milliseconds with type of int integer.
     * @param  timeCode Srt time code string.
     * @return  Milliseconds.
     */
    int convertTimeCodeToMilliseconds(const std::string& timeCode);

    // Qt getters
public:
    QUrl fileUrl();
    int currentSectionBegin();
    int currentSectionEnd();
    int currentSectionSequenceNumber();
    bool hasSrtFile() const;
    QString subtitleText() const;

    // Qt setters
public:
    void setFileUrl(QUrl& new_file_url);
    void setCurrentSectionBegin(const int newCurrentSectionBegin);
    void setCurrentSectionEnd(const int newCurrentSectionEnd);
    void setCurrentSectionSequenceNumber(const int newCurrentSectionSequenceNumber);

    // Qt signals
signals:
    void fileUrlChanged(QUrl& new_file_url);
    void currentSectionBeginChanged(const int newCurrentSectionBegin);
    void currentSectionEndChanged(const int newCurrentSectionEnd);
    void currentSectionSequenceNumberChanged(const int newCurrentSectionSequenceNumber);


    // Qt slots
private slots:
    /**
     * @brief  The parameter of signal fileUrlChanged() will be passed to be used in this slot.
     * @param  new_file_url  Newly set file url passed from signal fileUrlChanged().
     */
    void responseToFileUrlChanged(QUrl& new_file_url);

    void slotOfCurrentSectionSequenceNumberChanged(const int newCurrentSectionSequenceNumber);

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

    int currentSectionSequenceIntegerNumber;

    int currentSectionBeginMilliseconds;
    int currentSectionEndMilliseconds;
    bool hasSrtFileFlag;
};

#endif // SRTHANDLER_H
