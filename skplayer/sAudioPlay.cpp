#include "sAudioPlay.h"
#include <QAudioOutput>
#include <qthread.h>
#include <qmutex.h>
class skAudioPlay :public sAudioPlay
{
public:
	QAudioOutput *output = NULL;
	QIODevice *io = NULL;
	QMutex mutex;

	void Stop()
	{
		mutex.lock();
		if (output)
		{
			output->stop();
			delete output;
			output = NULL;
			io = NULL;
		}
		mutex.unlock();
	}
	// Í¨¹ý sAudioPlay ¼Ì³Ð
	virtual bool Start() override
	{
		Stop();
		mutex.lock();
		QAudioFormat fmt;
		fmt.setSampleRate(this->sampleRate);
		fmt.setSampleSize(this->sampleSize);
		fmt.setChannelCount(this->channel);
		fmt.setCodec("audio/pcm");
		fmt.setByteOrder(QAudioFormat::LittleEndian);
		fmt.setSampleType(QAudioFormat::UnSignedInt);
		output = new QAudioOutput(fmt);
		io = output->start();
		mutex.unlock();
		return true;
	}
	virtual bool Play(bool isPlay) override
	{
		mutex.lock();
		if (!output)
		{
			mutex.unlock();
			return false;
		}
		if (isPlay)
		{
			output->resume();
		}
		else
		{
			output->suspend();
		}
		mutex.unlock();
	}
	virtual bool Write(const char * data, int datasize) override
	{
		if (!data || datasize <= 0)
			return false;
		mutex.lock();
		if (io)
			io->write(data, datasize);
		mutex.unlock();
		return true;
	}

	virtual int GetFree()
	{
		mutex.lock();
		if (!output)
		{
			mutex.unlock();
			return 0;
		}
		int free = output->bytesFree();
		mutex.unlock();
		return free;
	}
};

sAudioPlay::sAudioPlay()
{
}


sAudioPlay * sAudioPlay::Get()
{
	static skAudioPlay ap;
	return &ap;
}

sAudioPlay::~sAudioPlay()
{
}
