#pragma once
#include <d3d9.h>
#include <d3dx9tex.h>
#include <vector>
#include <queue>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/channel_layout.h>
#include <libswresample/swresample.h>
#include <libavutil/opt.h>
#include <libavutil/imgutils.h>
}


class eopVideo
{
public:
	eopVideo(char* path, IDirect3DDevice9* d3dDevice);
	~eopVideo();
	void PlayFrame();
    void restartVideo();
    void stopVideo();

    int GetXSize();
    void SetXSize(int size);
    int GetYSize();
    void SetYSize(int size);
    bool IsOk();
    bool IsVideoEnded() { return IsPlayEnded; }
    std::string getErrorMessage() { return ErrorOnLoading; }
private:
    void resetContext();

    std::string ErrorOnLoading;
    bool IsBadState = false;
    bool IsPlayEnded = false;

    int videoStreamIndex = -1;
    int audioStreamIndex = -1;
    bool loadVideo(const char* path);

    bool decodeFrame();
    void uploadFrameToDirectXTexture();

    AVFormatContext* formatContext = nullptr;
    AVCodecContext* codecContext = nullptr;
    // audio
    AVCodecContext* audioCodecContext = nullptr;
    SwrContext* swrContext = nullptr;
    AVFrame* audioFrame = nullptr;

    AVFrame* frame = nullptr;
    AVPacket* packet = nullptr;
    SwsContext* swsContext = nullptr;

    IDirect3DTexture9* videoTexture = nullptr;
    int ImageX = 0;
    int ImageY = 0;

    int videoWidth = 0;
    int videoHeight = 0;
    int frameDelay = 0;

    // audio playback data
    std::vector<int16_t> audioSamples;
    int audioChannels = 0;
    int audioSampleRate = 0;
    void* soundBuffer = nullptr; // opaque pointer to SFML objects (created in cpp)
    void* sound = nullptr;
    bool audioStarted = false;


    std::chrono::steady_clock::time_point lastFrameTime = std::chrono::steady_clock::now();

};

