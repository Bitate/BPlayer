#include <gtest/gtest.h>

#include <string>

struct testVector {
    std::string sequneceNumber;
    std::string timeCodes;
    std::string caption;
};

testVector parseSrtUnit(const std::string& srtUnit)
{
    // srtUnit is in the form of:
    //     "1\r\n"
    //     "00:00:00,000 --> 00:00:02,000\r\n"
    //     "Subtitles created by Somebody\r\n"
    
    std::string srtUnitCopy = srtUnit;
    
    auto sequenceNumberEndPosition = srtUnitCopy.find("\r\n");

    std::string sequenceNumber = srtUnitCopy.substr(0, sequenceNumberEndPosition);
    
    std::string srtUnitWithoutSequenceNumber = srtUnitCopy.substr(sequenceNumberEndPosition + 2);

    auto timeCodesEndPosition = srtUnitWithoutSequenceNumber.find("\r\n");

    std::string timeCodes = srtUnitWithoutSequenceNumber.substr(0, timeCodesEndPosition);

    std::string caption = srtUnitWithoutSequenceNumber.substr(timeCodesEndPosition + 2);

    return { sequenceNumber, timeCodes, caption };
}

std::vector< testVector > parsesrtString(const std::string& srtString)
{
    std::string srtStringCopy = srtString;

    std::vector< testVector > parsedResult;

    while(srtStringCopy.find("\r\n\r\n") != std::string::npos)
    {
        auto srtUnitEndPosition = srtStringCopy.find("\r\n\r\n");

        std::string srtUnit = srtStringCopy.substr(0, srtUnitEndPosition+2);
    
        srtStringCopy = srtStringCopy.substr(srtUnitEndPosition + 4);

        parsedResult.push_back(parseSrtUnit(srtUnit));
    }
    
    return parsedResult;
}

long long convertTimeCodeToMilliseconds(const std::string& timeCode)
{
    int hours = std::stoi(timeCode.substr(0, 2));
    int minutes = std::stoi(timeCode.substr(3, 2));
    int seconds = std::stoi(timeCode.substr(6, 2));
    int milliseconds = std::stoi(timeCode.substr(9, 3));

    return milliseconds + ((seconds + minutes*60 + hours*60*60) * 1000);
}

TEST(srtHandlerTest, parseSrtStringTest)
{
    std::string srtString = {
        "1\r\n"
        "00:00:00,000 --> 00:00:02,000\r\n"
        "Subtitles created by Somebody\r\n"
        "\r\n"

        "2\r\n"
        "00:00:03,289 --> 00:00:05,462\r\n"
        "I'm Peppa Pig. (OINKS)\r\n"
        "\r\n"
        
        "3\r\n"
        "00:00:05,577 --> 00:00:07,970\r\n"
        "This is my little brother, George. (OINKS)\r\n"
    };

    std::vector< testVector > testCases = {
        { "1", "00:00:00,000 --> 00:00:02,000", "Subtitles created by Somebody\r\n" },
        { "2", "00:00:03,289 --> 00:00:05,462", "I'm Peppa Pig. (OINKS)\r\n"},
        { "3", "00:00:05,577 --> 00:00:07,970", "This is my little brother, George. (OINKS)\r\n"}
    };

    int index = 0;
    for(auto& srtUnit : parsesrtString(srtString))
    {
        EXPECT_EQ(srtUnit.sequneceNumber, testCases[index].sequneceNumber) << index << '\n';
        EXPECT_EQ(srtUnit.timeCodes, testCases[index].timeCodes) << index << '\n';
        EXPECT_EQ(srtUnit.caption, testCases[index].caption) << index << '\n';
        ++index;
    }
}

TEST(srtHandlerTest, convertTimeCodeToMillisecondsTest)
{
    std::vector< std::string > testCases {
        "00:00:03,289",
        "00:07:07,970",
        "05:00:05,577"
    };

    std::vector< long long > expectedResults {
        3289,
        427970,
        18005577
    };

    int index = 0;
    for(auto& testCase : testCases)
    {
        EXPECT_EQ(convertTimeCodeToMilliseconds(testCase), expectedResults[index]) << index << '\n';
        ++index;
    }
}