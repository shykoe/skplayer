#pragma once
class sAudioPlay
{
public:
	static sAudioPlay * Get();

	virtual bool Start() = 0;

	virtual bool Play(bool isPlay) = 0;

	virtual void Stop() = 0;

	virtual bool Write(const char *data, int datasize) = 0;

	virtual int GetFree() = 0;
	virtual ~sAudioPlay();
	int sampleRate = 48000;
	int sampleSize = 16;
	int channel = 2;
protected:
	sAudioPlay();
};

