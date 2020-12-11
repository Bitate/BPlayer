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

    // TODO: fix this function using ffmpeg library
    /*video.clipVideo(
        targetVideoPath,
        beginMilliseconds,
        endMilliseconds,
        newVideoPath
    );*/
}

TEST(vidoeTest, ffmpegTest)
{
    // We first need to load our media file into a component called AVFormatContext.
    // The video container is also known as format.
    // This component doesn't fully load the whole file, it reads the header of the file.
    AVFormatContext* formatContext = avformat_alloc_context();
    
    avformat_open_input(
        &formatContext,
        "C:/Users/16605/Music/Something Just Like This.mp4",
        nullptr,
        nullptr
    );

    printf(
        "This file has %d streams with the duration of %lld and the url of %s\n",
        formatContext->nb_streams,
        formatContext->duration,
        formatContext->url
    );

    // Read data from the media
    avformat_find_stream_info(formatContext, nullptr);

    // loop through all the streams
    for(int i = 0; i < formatContext->nb_streams; ++i)
    {
        // AVCodecParameters describes the properties of an encoded codec/stream with the index of i
        AVCodecParameters* codecParameters = formatContext->streams[i]->codecpar;

        // TODO: What is AVStream used for?
        //  1. We have both video stream and audio stream
    
        // Find the registered decoder for the given codec id and return an AVCodec struct.
        // The AVCodec is a struct used to hold information about the codec such as codec name, etc.
        // Codec Id is predefined by ffmpeg, for more see declaration of enum AVCodecID in ffmpeg source code.
        AVCodec* codec = avcodec_find_decoder(codecParameters->codec_id);

        // print infos about the codecs
        if(codecParameters->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            printf(
                "Video Codec(%s): resolution %d x %d with the index of %d within format context\n", 
                codec->long_name,
                codecParameters->width, 
                codecParameters->height, 
                i
            );

            // // codecContext holds the context for our decode/encode process
            // AVCodecContext* codecContext = avcodec_alloc_context3(codec);

            // // Fill the context with codec parameters
            // avcodec_parameters_to_context(codecContext, codecParameters);

            // // Open the codec so that we can use it
            // avcodec_open2(codecContext, codec, nullptr);

            // // Now we're going to read the packets from the stream 
            // // and decode them into frames.
            // AVPacket* packet = av_packet_alloc();
            // AVFrame* frame = av_frame_alloc();

            // // Feed packets from the streams while it has packets
            // while(av_read_frame(formatContext, packet) >= 0)
            // {
            //     avcodec_send_packet(codecContext, packet);

            //     avcodec_receive_frame(codecContext, frame);

            //     printf(
            //         "Frame %c (%d) pts %d dts %d key_frame %d [coded_picture_number %d, display_picture_number %d]",
            //         av_get_picture_type_char(frame->pict_type),
            //         codecContext->frame_number,
            //         frame->pts,
            //         frame->pkt_dts,
            //         frame->key_frame,
            //         frame->coded_picture_number,
            //         frame->display_picture_number
            //     );
            // }
        }else if(codecParameters->codec_type == AVMEDIA_TYPE_AUDIO)
        {
            printf(
                "Audio Codec(%s): %d channels and sample rate %d with the index of %d within format context\n", 
                codec->long_name,
                codecParameters->channels, 
                codecParameters->sample_rate, 
                i
            );
        }else // other types
        {
            printf(
                "Codec %s ID %d bit rate %lld with the index of %d within format context\n",
                codec->long_name, 
                codec->id, 
                codecParameters->bit_rate, 
                i
            );
        }  
    }
}

TEST(videoTest, ffmpegMuxingDemuxingTest)
{
    /**
     * Emmm, what is muxing and demuxing ???
     *      Demuxing:   Read multimedia streams from a particular type of media file. 
     *                  See: https://ffmpeg.org/doxygen/trunk/group__lavf__decoding.html
     *                                               -------------> stream 1 (e.g. audio)
     *                                              /
     *                  input multimedia file ----  --------------> stream 2 (e.g. video)
     *                                              \
     *                                               -------------> stream 3 (e.g. subtitle)
     * 
     *      Muxing:     Write multimedia streams to a particular type of media file.
     *                  See: https://ffmpeg.org/doxygen/4.0/group__lavf__encoding.html
     *                  stream 1 ----------------
     *                                           \
     *                  stream 2 ----------------  ----> output multimedia file
     *                                           /
     *                  stream 3 ----------------
     */

    /**
     * Demuxing/Decoding/Read
     */
    AVFormatContext* videoFormatContext = avformat_alloc_context();

    // Open video file and allocate format context
    if(avformat_open_input(&videoFormatContext, "C:/Users/16605/Music/Something Just Like This.mp4", nullptr, nullptr) < 0)
    {
        printf("Can't open input file");
        abort();
    }

    // Retrieve stream information
    if(avformat_find_stream_info(videoFormatContext, nullptr) < 0)
    {
        printf("Can't Retrieve stream info");
        abort();
    }    

    // Loop each stream
    for(int i = 0; i < videoFormatContext->nb_streams; ++i)
    {
        // Each stream has a corresponding AVCodec
        // Each AVCodec has a corresponding AVCodecContext
        
        // We first need to find a decoder for a specific stream,
        AVCodec* videoDecoder = avcodec_find_decoder(videoFormatContext->streams[i]->codecpar->codec_id);
        if(!videoDecoder)
        {
            std::cout << "Failed to find video decoder" << std::endl;
            exit(1);
        }

        // Then allocate a codec context for that decoder.
        AVCodecContext* videoCodecContext = avcodec_alloc_context3(videoDecoder);
        if(!videoCodecContext)
        {
            std::cout << "Failed to allocate the codec context" << std::endl;
            exit(1);
        }

        // TODO: is codec within a stream?
        // Copy codec parameters from input stream to output codec context
        if(avcodec_parameters_to_context(videoCodecContext, videoFormatContext->streams[i]->codecpar) < 0)
        {
            std::cout << "Failed to copy codec parameters from intput stream to output codec context" << std::endl;
            exit(1);
        }
        
        // Init the decoder
        if(avcodec_open2(videoCodecContext, videoDecoder, nullptr) < 0)
        {
            std::cout << "Failed to init decoder" << std::endl;
            exit(1);
        }

        // Initialize packet, set data to null and let the demuxer fill it.
        AVPacket packet;
        av_init_packet(&packet);
        packet.data = nullptr;
        packet.size = 0;

        // Read frames from the file
        while(av_read_frame(videoFormatContext, &packet) >= 0)
        {
            // Check if the packet belongs to a stream we are interested in.
            // That is whether we are dealing with video stream or audio stream 
            // or both, otherwise skip that packet.
            if(videoFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
            {
                // Submit the packet to the decoder
                // TODO: Error in this function
                int sendPacketResult = avcodec_send_packet(videoCodecContext, &packet);

                if(sendPacketResult < 0)
                {
                    std::cout << "Error sending a packet to decoder" << std::endl;
                }

                // Get all the available frames from the decoder
                while(sendPacketResult >= 0)
                {
                    AVFrame* frame = av_frame_alloc();

                    // Retrieve/receive frame from decoder.
                    // Note: before you call avcodec_receive_frame(), 
                    // you must allocate memory for a frame
                    // by calling function av_frame_alloc().
                    sendPacketResult = avcodec_receive_frame(videoCodecContext, frame);
                    
                    
                    if( sendPacketResult < 0 
                        && (sendPacketResult != AVERROR_EOF || sendPacketResult != AVERROR(EAGAIN)) )
                    {
                        std::cout << "Error during decoding" << std::endl;
                    }
                    
                    // Write the frame data to output file
                    // Allocate image where the decoded image/frame will be put
                    uint8_t* videoDestinationData[4] = { nullptr };
                    int videoDestinationLinesize[4];

                    // Allocate Pixel 
                    enum AVPixelFormat pixelFormat;
                    
                    // Copy/Write decoded video frame to destination output file's buffer:
                    // this is required since rawvideo expects non aligned data
                    av_image_copy(
                        videoDestinationData,
                        videoDestinationLinesize,
                        (const uint8_t**)(frame->data),
                        frame->linesize,
                        videoCodecContext->pix_fmt,
                        frame->width,
                        frame->height
                    );

                    // TODO: wirte to video output file
                }

            }
            else if(videoFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
            {
                
            }
        }

        
    }

    /**
     * Muxing/Encoding/Write
     */
    AVFormatContext* muxingFormatContext = avformat_alloc_context();

    

    // TODO: how to write to a media file?
    // avformat_write_header(muxingFormatContext, nullptr);
    // av_write_frame(muxingFormatContext, nullptr);
    // av_write_trailer(muxingFormatContext);
}

TEST(videoTest, ffmpegAVPacketTest)
{
    /**
     *  AVPacket structure stores compressed data.
     */
    AVPacket* avPacket = nullptr;
    avPacket->data;         // Actual byte?
    avPacket->pts;          // PTS(Presentation Timestamp)
    avPacket->dts;          // DTS(Decompression Timestamp)
    avPacket->stream_index; // ???

    AVStream* avStream = nullptr;
}

TEST(videoTest, ffmpegTimeTest)
{
    /**
     * What is timestamp, timescale and timebase?
     *  Each frame has a timestamp;
     *  Timescale is the reciprocal of the timebase;
     *  Timebase is used in the resolution of timestamps;
     */
}