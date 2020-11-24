#include "srtHandler.hpp"

srtHandler::srtHandler(QObject *parent)
    : QObject(parent), fileDialog(new QFileDialog)
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
    QFile srtFile(local_file_path);

    if(!srtFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Cannot open srt file with the path: " << local_file_path;
        QMessageBox::information(nullptr, "error", srtFile.errorString());
    }
    else
    {
        qDebug() << "Succeeds in opening srt file: " << local_file_path;
    }

    QTextStream srtTextStream(&srtFile);

    std::string srtTextString = srtFile.readAll().toStdString();
    while(!srtTextStream.atEnd())
    {
        // BUG: after reading, the \r\n is cut off.
        // add \r\n at the end to facilite the parsing process
        srtTextString.append(srtTextStream.readLine().toStdString());
    }

    std::cout << "srtTextString: " << srtTextString;

    srtObject = parseSrtString(srtTextString);

    for(auto srt : srtObject)
    {
        std::cout << srt.caption << std::endl;
    }
    srtFile.close();
}

void srtHandler::responseToFileUrlChanged(QUrl& new_file_url)
{
    QString local_file_path = new_file_url.toLocalFile();
    loadSrtFile(local_file_path);
}

void srtHandler::throwErrorMessage(QString errorSummary, QString concreteDescriptions)
{
    QMessageBox::warning(nullptr, errorSummary, concreteDescriptions);
}

std::vector< srtUnit > srtHandler::parseSrtString(const std::string srtString)
{
    std::string srtStringCopy = srtString;
    std::cout << "srtString is: " << srtStringCopy;
    std::vector< srtUnit > parsedResult;

    while(srtStringCopy.find("\r\n\r\n") != std::string::npos)
    {
        auto srtUnitEndPosition = srtStringCopy.find("\r\n\r\n");

        std::string srtUnit = srtStringCopy.substr(0, srtUnitEndPosition+2);

        srtStringCopy = srtStringCopy.substr(srtUnitEndPosition + 4);

        parsedResult.push_back(parseSrtUnitString(srtUnit));
    }

    return parsedResult;
}

srtUnit srtHandler::parseSrtUnitString(const std::string srtUnitString)
{
    // srtUnit is in the form of:
    //     "1\r\n"
    //     "00:00:00,000 --> 00:00:02,000\r\n"
    //     "Subtitles created by Somebody\r\n"
    
    std::string srtUnitCopy = srtUnitString;
    
    auto sequenceNumberEndPosition = srtUnitCopy.find("\r\n");

    std::string sequenceNumberString = srtUnitCopy.substr(0, sequenceNumberEndPosition);
    
    std::string srtUnitWithoutSequenceNumber = srtUnitCopy.substr(sequenceNumberEndPosition + 2);

    auto timeCodesEndPosition = srtUnitWithoutSequenceNumber.find("\r\n");

    std::string timeCodes = srtUnitWithoutSequenceNumber.substr(0, timeCodesEndPosition);

    std::string caption = srtUnitWithoutSequenceNumber.substr(timeCodesEndPosition + 2);
    
    int sequenceNumber = std::stoi(sequenceNumberString);

    // 00:00:00,000 --> 00:00:02,000
    std::string beginTimeString = timeCodes.substr(0, 12);
    std::string endTimeString = timeCodes.substr(18, 12);

    long long beginTimeMilliseconds = convertTimeCodeToMilliseconds(beginTimeString);
    long long endTimeMilliseconds = convertTimeCodeToMilliseconds(endTimeString);

    return { sequenceNumber, beginTimeMilliseconds, endTimeMilliseconds, caption };
}

long long srtHandler::convertTimeCodeToMilliseconds(const std::string& timeCode)
{
    int hours = std::stoi(timeCode.substr(0, 2));
    int minutes = std::stoi(timeCode.substr(3, 2));
    int seconds = std::stoi(timeCode.substr(6, 2));
    int milliseconds = std::stoi(timeCode.substr(9, 3));

    return milliseconds + ((seconds + minutes*60 + hours*60*60) * 1000);
}
