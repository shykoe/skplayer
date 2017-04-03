#ifndef CAFFETHREAD_H
#define CAFFETHREAD_H

#include <QThread>
#ifdef STRICT
#undef STRICT
#define __CLASSIFIER__
#include"Classifier.h"
#endif
#ifndef __CLASSIFIER__
#define __CLASSIFIER__
#include"Classifier.h"
#endif // !__CLASSIFIER__

class CaffeThread : public QThread
{
	Q_OBJECT

public:
	static CaffeThread* Getcaffe()
	{
		static CaffeThread ct((QObject *)NULL);
		return &ct;
	}
	CaffeThread(QObject *parent);
	~CaffeThread();
	void SetConf(std::string model_file, std::string trained_file, std::string mean_file);
	void run();
	void SetCaf(caffe::Classifier* cf);

private:
	std::string model_file;
	std::string trained_file;
	std::string mean_file;
	caffe::Classifier* cly;
signals:
	void CaffeInit();
	void message(int timestamp, float scores);

};

#endif // CAFFETHREAD_H
