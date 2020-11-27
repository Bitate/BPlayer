#include "..\include\srtHandler.hpp"
#include "srtHandler.hpp"

srtHandler::srtHandler(QObject *parent)
    : QObject(parent), fileDialog(new QFileDialog), currentSectionSequenceIntegerNumber(0),
      currentSectionBeginMilliseconds(0), currentSectionEndMilliseconds(0), hasSrtFileFlag(false)
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

void srtHandler::loadSrtFile(QString local_file_path)
{
    std::ifstream file(local_file_path.toStdString());
    std::ostringstream srtStringStream;

    if(file.is_open())
    {
        qDebug() << "Succeeds in opening file: " << local_file_path;
        srtStringStream << file.rdbuf();    
        file.close();
    }
    else
    {
        qDebug() << "Can't open srt file: " << local_file_path;
        file.close();
    }

   srtObject = parseSrtString(srtStringStream.str());

   setCurrentSectionBegin(srtObject[0].beginTimeMilliseconds);
   setCurrentSectionEnd(srtObject[0].endTimeMilliseconds);
   hasSrtFileFlag = true;
}

void srtHandler::responseToFileUrlChanged(QUrl& new_file_url)
{
    QString local_file_path = new_file_url.toLocalFile();
    loadSrtFile(local_file_path);
}

void srtHandler::popUpErrorMessage(QString errorBoxTitle, QString errorDescription)
{
    QMessageBox::warning(nullptr, errorBoxTitle, errorDescription);
}

std::vector< srtUnit > srtHandler::parseSrtString(const std::string srtString)
{
    std::string srtStringCopy = srtString;

    std::vector< srtUnit > parsedResult;

    while(srtStringCopy.find("\n\n") != std::string::npos)
    {
        auto srtUnitEndPosition = srtStringCopy.find("\n\n");

        std::string srtUnit = srtStringCopy.substr(0, srtUnitEndPosition+2);

        srtStringCopy = srtStringCopy.substr(srtUnitEndPosition + 2);

        parsedResult.push_back(parseSrtUnitString(srtUnit));
    }

    return parsedResult;
}

srtUnit srtHandler::parseSrtUnitString(const std::string srtUnitString)
{
    // srtUnit is in the form of:
    //     "1\n"
    //     "00:00:00,000 --> 00:00:02,000\n"
    //     "Subtitles created by Somebody\n"
    
    std::string srtUnitCopy = srtUnitString;
    
    auto sequenceNumberEndPosition = srtUnitCopy.find("\n");

    std::string sequenceNumberString = srtUnitCopy.substr(0, sequenceNumberEndPosition);
    
    std::string srtUnitWithoutSequenceNumber = srtUnitCopy.substr(sequenceNumberEndPosition + 1);

    auto timeCodesEndPosition = srtUnitWithoutSequenceNumber.find("\n");

    std::string timeCodes = srtUnitWithoutSequenceNumber.substr(0, timeCodesEndPosition);

    std::string caption = srtUnitWithoutSequenceNumber.substr(timeCodesEndPosition + 1);
    
    // Let sequence number starts from 0 as the index of array.
    int sequenceNumber = std::stoi(sequenceNumberString)-1;

    // 00:00:00,000 --> 00:00:02,000
    std::string beginTimeString = timeCodes.substr(0, 12);
    std::string endTimeString = timeCodes.substr(17, 12);

    int beginTimeMilliseconds = convertTimeCodeToMilliseconds(beginTimeString);
    int endTimeMilliseconds = convertTimeCodeToMilliseconds(endTimeString);

    return { sequenceNumber, beginTimeMilliseconds, endTimeMilliseconds, caption };
}

int srtHandler::convertTimeCodeToMilliseconds(const std::string& timeCode)
{
    int hours = std::stoi(timeCode.substr(0, 2));
    int minutes = std::stoi(timeCode.substr(3, 2));
    int seconds = std::stoi(timeCode.substr(6, 2));
    int milliseconds = std::stoi(timeCode.substr(9, 3));

    return milliseconds + ((seconds + minutes*60 + hours*60*60) * 1000);
}

int srtHandler::currentSectionBegin()
{
    if(srtObject.size() != 0)
        currentSectionBeginMilliseconds = srtObject[currentSectionSequenceIntegerNumber].beginTimeMilliseconds;
    return currentSectionBeginMilliseconds;
}

int srtHandler::currentSectionEnd()
{
    if(srtObject.size() != 0)
        currentSectionEndMilliseconds = srtObject[currentSectionSequenceIntegerNumber].endTimeMilliseconds;
    return currentSectionEndMilliseconds;
}

int srtHandler::currentSectionSequenceNumber()
{
    return currentSectionSequenceIntegerNumber;
}

bool srtHandler::hasSrtFile() const
{
    return hasSrtFileFlag;
}

QString srtHandler::subtitleText() const
{
    if (srtObject.size() != 0)
        return QString(srtObject[currentSectionSequenceIntegerNumber].caption.c_str());
    else
        return QString();
}

void srtHandler::setCurrentSectionBegin(const int newCurrentSectionBegin)
{
    currentSectionBeginMilliseconds = newCurrentSectionBegin;
    emit currentSectionBeginChanged(newCurrentSectionBegin);
}

void srtHandler::setCurrentSectionEnd(const int newCurrentSectionEnd)
{
    currentSectionEndMilliseconds = newCurrentSectionEnd;
    emit currentSectionEndChanged(newCurrentSectionEnd);
}

void srtHandler::setCurrentSectionSequenceNumber(const int newCurrentSectionSequenceNumber)
{
    currentSectionSequenceIntegerNumber = newCurrentSectionSequenceNumber;
    emit currentSectionSequenceNumberChanged(newCurrentSectionSequenceNumber);
}

void srtHandler::slotOfCurrentSectionSequenceNumberChanged(const int newCurrentSectionSequenceNumber)
{
    currentSectionBeginMilliseconds = srtObject[newCurrentSectionSequenceNumber].beginTimeMilliseconds;
    currentSectionEndMilliseconds = srtObject[newCurrentSectionSequenceNumber].endTimeMilliseconds;
}

