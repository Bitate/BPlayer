#pragma once

#include <string>
#include <iostream>
#include "opencv"


class Video
{
public:
    Video();
    ~Video();

public:
    bool clipVideo(
        const std::string& targetVideoPath,
        const int beginMilliseconds,
        const int endMilliseconds,
        const std::string& newVideoPath
    );


    

    
};
