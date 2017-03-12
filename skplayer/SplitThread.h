#pragma once
#include "QThread"
#include <vector>
#include <tuple>
#include <queue>
#include <string>
#include <qmutex.h>
#include <QMutexLocker> 
class SplitThread :
	public QThread
{
public:
	static SplitThread* Get()
	{
		static SplitThread st;
		return &st;
	}
	SplitThread();
	void run();
	virtual ~SplitThread();
	bool addTask(unsigned start, unsigned duration, std::string filename);
private:
	bool isExit;
	//bool hasTsk;
	
	std::tuple<unsigned int, unsigned int, std::string> getTask();
	std::queue< std::tuple<unsigned int, unsigned int, std::string> > sptask;
	QMutex mutex;
};

