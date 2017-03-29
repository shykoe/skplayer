#include "caffethread.h"

CaffeThread::CaffeThread(QObject *parent)
	: QThread(parent)
{

}

CaffeThread::~CaffeThread()
{

}
void CaffeThread::SetConf(std::string model_file, std::string trained_file, std::string mean_file)
{
	this->model_file = model_file;
	this->trained_file = trained_file;
	this->mean_file = mean_file;
}

void CaffeThread::run()
{
	cly = new caffe::Classifier(model_file, trained_file, mean_file);
	emit CaffeInit();
}
