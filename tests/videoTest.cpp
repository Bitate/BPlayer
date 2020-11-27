#include "video.hpp"

#include <gtest/gtest.h>

TEST(videoTest, clipVideoTest)
{
    Video video;

    std::string targetVideoPath = "...";
    std::string newVideoPath = "...";
    int beginMilliseconds = 1000;
    int endMilliseconds = 5000;

    video.clipVideo(
        targetVideoPath,
        newVideoPath,
        beginMilliseconds,
        endMilliseconds
    );
    
}