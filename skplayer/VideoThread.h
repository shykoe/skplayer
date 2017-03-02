#pragma once
#include<qthread.h>
class VideoThread:public QThread
{
public:
	static VideoThread* Get()
	{
		static VideoThread vt;
		return &vt;

	}
	VideoThread();
	void run();
	virtual ~VideoThread();
	bool isexited;
};

