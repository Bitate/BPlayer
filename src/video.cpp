#include "video.hpp"

bool Video::clipVideo(
    const std::string& targetVideoPath,
    const int beginMilliseconds,
    const int endMilliseconds,
    const std::string& newVideoPath
)
{
    if(targetVideoPath.empty())
        return false;

    cv::VideoCapture capture(targetVideoPath.c_str());

    if(!capture.isOpened())
        std::cout << "Can't open video" << std::endl;

    return true;
}
