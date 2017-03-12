//#include "SplitThread.h"
//
//
//
//SplitThread::SplitThread()
//{
//}
//
//void SplitThread::run()
//{
//	while (!isExit)
//	{
//		auto task = getTask();
//		unsigned start = std::get<0>(task);
//		unsigned duration = std::get<1>(task);
//		std::string filename = std::get<2>(task);
//		if (filename != "")
//		{
//
//		}
//
//	}
//}
//bool SplitThread::addTask(unsigned start, unsigned duration, std::string filename)
//{
//	QMutexLocker lc(&mutex);
//	sptask.push(std::make_tuple(start, duration, filename));
//	return true;
//}
//
//std::tuple<unsigned int, unsigned int, std::string> SplitThread::getTask()
//{
//	QMutexLocker lc(&mutex);
//	if (sptask.empty())
//	{
//		return std::tuple<unsigned int, unsigned int, std::string>();
//	}
//		
//	auto task = sptask.front();
//	sptask.pop();
//	return std::tuple<unsigned int, unsigned int, std::string>();
//}
//
//
//SplitThread::~SplitThread()
//{
//}
