#pragma once

#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <libavcodec/avcodec.h>
#include <libavutil/mathematics.h>

class Video
{
public:
    Video();
public:
    bool clipVideo(
        const std::string& targetVideoPath,
        const int beginMilliseconds,
        const int endMilliseconds,
        const std::string& newVideoPath
    );

private:
    // frame per second
    double fps;
    double frameCount;
    int startMilliseconds;
    int endMilliseconds;
};
