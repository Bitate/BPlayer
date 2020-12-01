#include "video.hpp"

Video::Video()
    : fps(0), frameCount(0), startMilliseconds(0), endMilliseconds(0)
{
}

bool Video::clipVideo(
    const std::string &targetVideoPath,
    const int beginMilliseconds,
    const int endMilliseconds,
    const std::string &newVideoPath)
{
    //open the video file for reading
    cv::VideoCapture targetVideo(targetVideoPath);
    
    if (!targetVideo.isOpened())
    {
        std::cout << "Cannot open the video file" << std::endl;
        targetVideo.release();
        return false;
    }
    
    // Set starting time in milliseconds
    targetVideo.set(cv::CAP_PROP_POS_MSEC, beginMilliseconds);
    
    // Get target original frame size
    int frame_width = static_cast<int>(targetVideo.get(cv::CAP_PROP_FRAME_WIDTH));   //get the width of frames of the video
    int frame_height = static_cast<int>(targetVideo.get(cv::CAP_PROP_FRAME_HEIGHT)); //get the height of frames of the video
    cv::Size frame_size(frame_width, frame_height);
    fps = targetVideo.get(cv::CAP_PROP_POS_MSEC); // GET fps of opened video file

    //Create and initialize the VideoWriter object 
    cv::VideoWriter videoWriterObject(
                        newVideoPath,
                        cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 
                        fps, 
                        frame_size, 
                        true
                    ); 
    
    //If the VideoWriter object is not initialized successfully, exit the program
    if (videoWriterObject.isOpened() == false) 
    {
        std::cout << "Cannot save the video to a file" << std::endl;
        targetVideo.release();
        return false;
    }

    while( targetVideo.get(cv::CAP_PROP_POS_MSEC) <= endMilliseconds )
    {
        cv::Mat frame;
        
        // read a new frame from the video camera
        bool isSuccess = targetVideo.read(frame); 

        //Breaking the while loop if frames cannot be read from the camera
        if (isSuccess == false)
        {
            std::cout << "Finish reading frames" << std::endl;
            targetVideo.release();
            break;
        }

        /**
         * Process each frame.
         *   e.g.
         *      1. Change brightness/contrast of the image
         *      2. Smooth/Blur image
         *      3. Crop the image
         *      4. Rotate the image
         *      5. Draw shapes on the image  
         */
        //write the video frame to the file
        videoWriterObject.write(frame); 
    }

    //Flush and close the video file
    videoWriterObject.release();

    // //get the frames rate of the video
    // double fps = targetVideo.get(CAP_PROP_FPS);
    // frameCount = targetVideo.get(CAP_PROP_FRAME_COUNT);

    // cout << "Frames per seconds : " << fps << endl;
    // cout << "Total frames are: " << frameCount << endl;

    // String window_name = "My First Video";

    // namedWindow(window_name, WINDOW_NORMAL); //create a window

    // while (targetVideo.get(CAP_PROP_POS_MSEC) <= endMilliseconds)
    // {
    //     Mat frame;
        
    //     bool bSuccess = targetVideo.read(frame); // read a new frame from video

    //     //Breaking the while loop at the end of the video
    //     if (bSuccess == false)
    //     {
    //         cout << "Found the end of the video" << endl;
    //         break;
    //     }

    //     //show the frame in the created window
    //     imshow(window_name, frame);

    //     //wait for for 10 ms until any key is pressed.
    //     //If the 'Esc' key is pressed, break the while loop.
    //     //If the any other key is pressed, continue the loop
    //     //If any key is not pressed withing 10 ms, continue the loop
    //     if (waitKey(10) == 27)
    //     {
    //         cout << "Esc key is pressed by user. Stoppig the video" << endl;
    //         break;
    //     }
    // }
    return true;
}
