#include "video.hpp"

#include <gtest/gtest.h>

TEST(videoTest, clipVideoTest)
{
    Video video;

    // Change following two paths according to your need
    std::string targetVideoPath = "C:/Users/16605/Music/Something Just Like This.mp4";
    std::string newVideoPath = "C:/Users/16605/Music/Something Just Like This Clipped.mp4";
    int beginMilliseconds = 0;
    int endMilliseconds   = 100000;

    video.clipVideo(
        targetVideoPath,
        beginMilliseconds,
        endMilliseconds,
        newVideoPath
    );
}

TEST(vidoeTest, ffmpegTest)
{
    AVCodec* code;
    
    // TODO: Add ffmpeg examples here

}