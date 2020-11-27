#include "video.hpp"

#include <gtest/gtest.h>

TEST(videoTest, clipVideoTest)
{
    Video video;

    std::string targetVideoPath = "C:/Users/16605/Music/Something Just Like This.mp4";
    std::string newVideoPath = "C:/Users/16605/Music/Something Just Like This Clipped.mp4";
    int beginMilliseconds = 1000;
    int endMilliseconds = 5000;

    video.clipVideo(
        targetVideoPath,
        beginMilliseconds,
        endMilliseconds,
        newVideoPath
    );
    
}
