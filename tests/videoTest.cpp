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

    /*video.clipVideo(
        targetVideoPath,
        beginMilliseconds,
        endMilliseconds,
        newVideoPath
    );*/
}

TEST(vidoeTest, ffmpegTest)
{
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
        // AVCodecParameters describes the properties of a codec used by the stream i
        AVCodecParameters* codecParameters = formatContext->streams[i]->codecpar;

        // Find the registered decoder for the codec id and return an AVCodec
        AVCodec* codec = avcodec_find_decoder(codecParameters->codec_id);

        // print infos about the codecs
        if(codecParameters->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            printf(
                "Video Codec: resolution %d x %d with the index of %d within format context\n", 
                codecParameters->width, 
                codecParameters->height, 
                i
            );

            // codecContext holds the context for our decode/encode process
            AVCodecContext* codecContext = avcodec_alloc_context3(codec);

            // Fill the context with codec parameters
            avcodec_parameters_to_context(codecContext, codecParameters);

            // Open the codec so that we can use it
            avcodec_open2(codecContext, codec, nullptr);

            // Now we're going to read the packets from the stream 
            // and decode them into frames.
            AVPacket* packet = av_packet_alloc();
            AVFrame* frame = av_frame_alloc();

            // Feed packets from the streams while it has packets
            while(av_read_frame(formatContext, packet) >= 0)
            {
                avcodec_send_packet(codecContext, packet);

                avcodec_receive_frame(codecContext, frame);

                printf(
                    "Frame %c (%d) pts %d dts %d key_frame %d [coded_picture_number %d, display_picture_number %d]",
                    av_get_picture_type_char(frame->pict_type),
                    codecContext->frame_number,
                    frame->pts,
                    frame->pkt_dts,
                    frame->key_frame,
                    frame->coded_picture_number,
                    frame->display_picture_number
                );
            }
        }else if(codecParameters->codec_type == AVMEDIA_TYPE_AUDIO)
        {
            printf(
                "Audio Codec: %d channels and sample rate %d with the index of %d within format context\n", 
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