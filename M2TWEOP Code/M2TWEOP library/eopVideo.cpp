#include "pch.h"
#include "eopVideo.h"

#include "imgui/imgui.h"
#include <SFML/Audio.hpp>
#include <libswresample/swresample.h>

eopVideo::eopVideo(char* path, IDirect3DDevice9* d3dDevice)
{
	if (!loadVideo(path))
	{
		IsBadState = true;
		return;
	}

	if (FAILED(d3dDevice->CreateTexture(videoWidth, videoHeight, 1, 0, D3DFMT_X8R8G8B8, D3DPOOL_MANAGED, &videoTexture, nullptr)))
	{
		ErrorOnLoading = "Failed to create DirectX texture for video:" + std::string(path);;
		IsBadState = true;
		return;
	}
	ImageX = videoWidth;
	ImageY = videoHeight;

}

eopVideo::~eopVideo()
{
	av_frame_free(&frame);
	av_packet_free(&packet);
	avcodec_free_context(&codecContext);
	avformat_close_input(&formatContext);
	sws_freeContext(swsContext);
	if (audioFrame) av_frame_free(&audioFrame);
	if (audioCodecContext) avcodec_free_context(&audioCodecContext);
	if (swrContext) swr_free(&swrContext);
	if (sound) { delete reinterpret_cast<sf::Sound*>(sound); sound = nullptr; }
	if (soundBuffer) { delete reinterpret_cast<sf::SoundBuffer*>(soundBuffer); soundBuffer = nullptr; }
}

void eopVideo::PlayFrame()
{
	if (IsPlayEnded)
	{
		ImGui::Image((void*)videoTexture, ImVec2(ImageX, ImageY));
		return;
	}

	auto now = std::chrono::steady_clock::now();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFrameTime).count();

	if (elapsedTime >= frameDelay)
	{
		if (decodeFrame())
		{
			uploadFrameToDirectXTexture();
		}
		else
		{
			// video ended - stop playback and audio
			stopVideo();
		}
		lastFrameTime = now;
	}


	ImGui::Image((void*)videoTexture, ImVec2(ImageX, ImageY));

	// start audio playback once when the first frame is displayed
	if (!audioStarted && sound) {
		sf::Sound* s = reinterpret_cast<sf::Sound*>(sound);
		s->play();
		audioStarted = true;
	}
}

void eopVideo::stopVideo()
{
	IsPlayEnded = true;
	// stop audio if playing
	if (sound) {
		sf::Sound* s = reinterpret_cast<sf::Sound*>(sound);
		if (s->getStatus() == sf::Sound::Playing) {
			s->stop();
		}
	}
	audioStarted = false;
}

void eopVideo::restartVideo()
{
	IsPlayEnded = false;

	resetContext();

	if (av_seek_frame(formatContext, videoStreamIndex, 0, AVSEEK_FLAG_BACKWARD) < 0) {
		//error
	}
	else {
		avcodec_flush_buffers(codecContext);
	}

	// reset audio playback state
	audioStarted = false;
	if (sound) {
		sf::Sound* s = reinterpret_cast<sf::Sound*>(sound);
		s->stop();
		s->setPlayingOffset(sf::Time::Zero);
	}
}

int eopVideo::GetXSize()
{
	return ImageX;
}

void eopVideo::SetXSize(int size)
{
	ImageX = size;
}

int eopVideo::GetYSize()
{
	return ImageY;
}

void eopVideo::SetYSize(int size)
{
	ImageY = size;
}

bool eopVideo::IsOk()
{
	return !IsBadState;
}

void eopVideo::resetContext()
{
	avcodec_flush_buffers(codecContext);


	lastFrameTime = std::chrono::steady_clock::now();
}

bool eopVideo::loadVideo(const char* path)
{
	if (avformat_open_input(&formatContext, path, nullptr, nullptr) != 0) {
		ErrorOnLoading = "Failed to open video file: " + std::string(path);
		return false;
	}
	if (avformat_find_stream_info(formatContext, nullptr) < 0) {
		ErrorOnLoading = "Failed to retrieve stream info from video file.";
		return false;
	}

	// find video and audio streams
	videoStreamIndex = -1;
	audioStreamIndex = -1;
	for (unsigned int i = 0; i < formatContext->nb_streams; ++i) {
		if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
			videoStreamIndex = i;
		}
		if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
			audioStreamIndex = i;
		}
	}

	if (videoStreamIndex == -1) {
		ErrorOnLoading = "Failed to find video stream in file.";
		return false;
	}

	// open video codec
	AVCodecParameters* codecParams = formatContext->streams[videoStreamIndex]->codecpar;
	const AVCodec* codec = avcodec_find_decoder(codecParams->codec_id);
	if (!codec) {
		ErrorOnLoading = "Failed to find video codec.";
		return false;
	}

	codecContext = avcodec_alloc_context3(codec);
	if (!codecContext) {
		ErrorOnLoading = "Failed to allocate video codec context.";
		return false;
	}

	if (avcodec_parameters_to_context(codecContext, codecParams) < 0) {
		ErrorOnLoading = "Failed to copy video codec parameters to codec context.";
		return false;
	}

	if (avcodec_open2(codecContext, codec, nullptr) < 0) {
		ErrorOnLoading = "Failed to open video codec.";
		return false;
	}

	// if audio exists, open audio codec and decode full audio into buffer
	if (audioStreamIndex != -1) {
		AVCodecParameters* aParams = formatContext->streams[audioStreamIndex]->codecpar;
		const AVCodec* aCodec = avcodec_find_decoder(aParams->codec_id);
		if (aCodec) {
			audioCodecContext = avcodec_alloc_context3(aCodec);
			if (avcodec_parameters_to_context(audioCodecContext, aParams) >= 0) {
				if (avcodec_open2(audioCodecContext, aCodec, nullptr) == 0) {
					// prepare resampler to S16 interleaved using swr_alloc_set_opts2
					AVChannelLayout outLayout = AV_CHANNEL_LAYOUT_STEREO;
					if (swr_alloc_set_opts2(&swrContext,
						&outLayout, AV_SAMPLE_FMT_S16, audioCodecContext->sample_rate,
						&aParams->ch_layout, audioCodecContext->sample_fmt, audioCodecContext->sample_rate,
						0, nullptr) >= 0) {
						if (swr_init(swrContext) < 0) {
							swr_free(&swrContext);
						}
					}
				}
			}
		}
	}

	videoWidth = codecContext->width;
	videoHeight = codecContext->height;

	// Frame delay based on video frame rate
	AVRational frameRate = formatContext->streams[videoStreamIndex]->r_frame_rate;
	frameDelay = static_cast<int>(1000 * frameRate.den / frameRate.num);

	frame = av_frame_alloc();
	if (!frame) {
		ErrorOnLoading = "Failed to allocate frame.";
		return false;
	}
	packet = av_packet_alloc();
	if (!packet) {
		ErrorOnLoading = "Failed to allocate packet.";
		return false;
	}

	// allocate audio frame if needed
	if (audioStreamIndex != -1) {
		audioFrame = av_frame_alloc();
		if (!audioFrame) {
			// continue without audio
			audioStreamIndex = -1;
		}
	}

	// use BGRA to match D3D9 D3DFMT_X8R8G8B8 memory layout (BGR byte order)
	swsContext = sws_getContext(videoWidth, videoHeight, codecContext->pix_fmt, videoWidth, videoHeight, AV_PIX_FMT_BGRA, SWS_BILINEAR, nullptr, nullptr, nullptr);
	if (!swsContext) {
		ErrorOnLoading = "Failed to initialize SwsContext for frame scaling.";
		return false;
	}

	// If audio is available, decode audio packets now into memory buffer (simple approach)
	if (audioStreamIndex != -1 && audioCodecContext && audioFrame && swrContext) {
		// read through file and decode audio
		while (av_read_frame(formatContext, packet) >= 0) {
			if (packet->stream_index == audioStreamIndex) {
				if (avcodec_send_packet(audioCodecContext, packet) == 0) {
					while (avcodec_receive_frame(audioCodecContext, audioFrame) == 0) {
						// convert samples to S16 stereo
						const int out_channels = 2;
						const int out_sample_rate = audioCodecContext->sample_rate;
						int out_nb_samples = av_rescale_rnd(swr_get_delay(swrContext, audioCodecContext->sample_rate) + audioFrame->nb_samples, out_sample_rate, audioCodecContext->sample_rate, AV_ROUND_UP);
						std::vector<uint8_t> outbuf(out_nb_samples * out_channels * av_get_bytes_per_sample(AV_SAMPLE_FMT_S16));
						uint8_t* outptr[2] = { outbuf.data(), nullptr };
						int converted = swr_convert(swrContext, outptr, out_nb_samples, (const uint8_t**)audioFrame->extended_data, audioFrame->nb_samples);
						if (converted > 0) {
							int samples = converted * out_channels;
							int16_t* samples16 = reinterpret_cast<int16_t*>(outbuf.data());
							audioSamples.insert(audioSamples.end(), samples16, samples16 + samples);
						}
					}
				}
			}
			av_packet_unref(packet);
		}

		// remember audio format info
		audioChannels = 2;
		audioSampleRate = audioCodecContext->sample_rate;

		// create SFML sound buffer if we have samples
		if (!audioSamples.empty()) {
			try {
				sf::SoundBuffer* sb = new sf::SoundBuffer();
				if (sb->loadFromSamples(reinterpret_cast<const sf::Int16*>(audioSamples.data()), (sf::Uint64)audioSamples.size(), audioChannels, audioSampleRate)) {
					sf::Sound* s = new sf::Sound();
					s->setBuffer(*sb);
					soundBuffer = sb;
					sound = s;
				} else {
					delete sb;
				}
			} catch (...) {
				// ignore audio creation failures
			}
		}

		// seek back to start for video decoding
		if (av_seek_frame(formatContext, videoStreamIndex, 0, AVSEEK_FLAG_BACKWARD) < 0) {
			//error seeking
		}
		avcodec_flush_buffers(codecContext);
	}

	return true;
}

bool eopVideo::decodeFrame()
{
	while (av_read_frame(formatContext, packet) >= 0) {
		if (avcodec_send_packet(codecContext, packet) == 0) {
			if (avcodec_receive_frame(codecContext, frame) == 0) {
				av_packet_unref(packet);
				return true;
			}
		}
		av_packet_unref(packet);
	}
	return false;
}

void eopVideo::uploadFrameToDirectXTexture()
{
	if (!frame || !videoTexture) return;

	uint8_t* data[1] = { nullptr };
	int linesize[1] = { 0 };

	std::vector<uint8_t> rgbData(videoWidth * videoHeight * 4);
	data[0] = rgbData.data();
	linesize[0] = videoWidth * 4;

	sws_scale(swsContext, frame->data, frame->linesize, 0, videoHeight, data, linesize);

	D3DLOCKED_RECT lockedRect;
	if (SUCCEEDED(videoTexture->LockRect(0, &lockedRect, nullptr, D3DLOCK_DISCARD))) {
		uint8_t* dest = static_cast<uint8_t*>(lockedRect.pBits);
		for (int y = 0; y < videoHeight; ++y) {
			memcpy(dest + y * lockedRect.Pitch, rgbData.data() + y * linesize[0], linesize[0]);
		}
		videoTexture->UnlockRect(0);
	}
}



