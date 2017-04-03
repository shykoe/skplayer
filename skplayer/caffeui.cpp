﻿#include "caffeui.hpp"
#include "qfiledialog.h"
#include "qstring.h"
#include "qtableview.h"
#include "SplitVideo.h"
#include "qmessagebox.h"
#include <QMenu>

caffeui::caffeui(QWidget * parent) : QWidget(parent) {
	ui.setupUi(this);
	//ui.Seginfo->
	_model = new SegTableModel();
	proxyModel = new QSortFilterProxyModel(this);
	proxyModel->setSourceModel(_model);
	proxyModel->setSortRole(Qt::EditRole);
	proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
	proxyModel->setFilterKeyColumn(-1);
	ui.Seginfo->setModel(proxyModel);
	ui.Seginfo->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.Seginfo->setContextMenuPolicy(Qt::CustomContextMenu);
	ui.LogText->setReadOnly(true);
	ui.OutputDirEdit->setText(QCoreApplication::applicationDirPath());
	menu = new QMenu();
	QAction *splitAction = menu->addAction(QString::fromLocal8Bit("分割视频"));

	mythread = CaffeThread::Getcaffe();


	string model_file = "E:\\videocaffedata\\template_net.prototxt";
	string trained_file = "E:\\videocaffedata\\_iter_15000.caffemodel";
	string mean_file = "E:\\videocaffedata\\seg_leveldb_mean";
	string label_file = "synset_words.txt";
	ui.ModelEdit->setText(QString(QString::fromLocal8Bit(trained_file.c_str())));
	ui.ProtoEdit->setText(QString(QString::fromLocal8Bit(model_file.c_str())));
	ui.MeanEdit->setText(QString(QString::fromLocal8Bit(mean_file.c_str())));
	

	connect(this->mythread, SIGNAL(CaffeInit()), this, SLOT(Caffed()));
	connect(this->mythread, SIGNAL(message(int,float)), this, SLOT(getmes(int, float)));
	connect(ui.Seginfo, SIGNAL(customContextMenuRequested(const QPoint)), this, SLOT(contextMenu(const QPoint)));
	connect(splitAction, &QAction::triggered, this, &caffeui::splitvideo);
	connect(ui.InitCaffe, SIGNAL(clicked()), SLOT(InitCaffe()));
	connect(ui.AnalysisBt, SIGNAL(clicked()), this, SLOT(AnalysisMsg()));


	//debug
	AddSegitem( 11, 2, 33, tr("test.mp4"));
	AddSegitem(11, 2, 33, tr("test.mp4"));
	AddSegitem(11, 2, 33, tr("test.mp4"));

	//SplitVideo::Get()->OpenSource("D:\\BaiduYunDownload\\Ariana Grande - Into You.mp4");


	//startTimer(40);
	
}
void caffeui::splitvideo()
{
	printf("%d\n", ui.Seginfo->currentIndex().row());
	auto start = _model->getItem(ui.Seginfo->currentIndex().row())->truedata(1);
	auto end = _model->getItem(ui.Seginfo->currentIndex().row())->truedata(2);
	auto dur = _model->getItem(ui.Seginfo->currentIndex().row())->truedata(3);
	auto name = _model->getItem(ui.Seginfo->currentIndex().row())->truedata(4);
	printf("%s\n", SplitVideo::Get()->getpath().c_str());
	printf("%d-%d-%d-%s\n", start.toInt(), end.toInt(), dur.toInt(),name.toString().toStdString().c_str());
	if (SplitVideo::Get()->isopen)
	{
		SplitVideo::Get()->Split(start.toInt(), dur.toInt(), ui.OutputDirEdit->text().toStdString() + "//"+name.toString().toStdString());
	}
	
}
void caffeui::contextMenu(const QPoint &pos)
{
	int row = ui.Seginfo->rowAt(pos.y());
	if (row != -1)
	{
		QAction *action = menu->exec(ui.Seginfo->mapToGlobal(pos));
		//printf("menu %d,%d" ,pos.x(), pos.y());
	}
	return;
}
void caffeui::SetModelFile()
{
	QString name = QFileDialog::getOpenFileName(
		this, QString::fromLocal8Bit("选择caffemodel文件"));
	if (name.isEmpty())
	{
		return;
	}
	printf("%s", name.toStdString().c_str());
	ui.ModelEdit->setText(name);
}
void caffeui::SetProtoFile()
{
	QString name = QFileDialog::getOpenFileName(
		this, QString::fromLocal8Bit("选择proto文件"));
	if (name.isEmpty())
	{
		return;
	}
	printf("%s", name.toStdString().c_str());
	ui.ProtoEdit->setText(name);
}
void caffeui::SetMeanFile()
{
	QString name = QFileDialog::getOpenFileName(
		this, QString::fromLocal8Bit("选择mean文件"));
	if (name.isEmpty())
	{
		return;
	}
	printf("%s", name.toStdString().c_str());
	ui.MeanEdit->setText(name);
}
void caffeui::SetOutputFile()
{
	QString name = QFileDialog::getExistingDirectory(
		this, QString::fromLocal8Bit("选择存放位置")
	);
	if (name.isEmpty())
	{
		return;
	}
	printf("%s", name.toStdString().c_str());
	ui.OutputDirEdit->setText(name);
}
void caffeui::InitCaffe()
{
	if (cly != NULL)
		delete cly;
	auto modelfile = ui.ModelEdit->text();
	auto protofile = ui.ProtoEdit->text();
	auto meanfile = ui.MeanEdit->text();
	if (modelfile.isEmpty())
	{
		QMessageBox::StandardButton reply;
		reply = QMessageBox::critical(this, tr("error"),
			tr("modelfile empty"),
			QMessageBox::Abort);
		return;
	}
	if (protofile.isEmpty())
	{
		QMessageBox::StandardButton reply;
		reply = QMessageBox::critical(this, tr("error"),
			tr("protofile empty"),
			QMessageBox::Abort);
		return;
	}
	if (meanfile.isEmpty())
	{
		QMessageBox::StandardButton reply;
		reply = QMessageBox::critical(this, tr("error"),
			tr("meanfile empty"),
			QMessageBox::Abort);
		return;
	}
	ui.InitCaffe->setEnabled(false);
	cly = new caffe::Classifier(protofile.toStdString(), modelfile.toStdString(), meanfile.toStdString());
	//mythread->SetConf(protofile.toStdString(),modelfile.toStdString(), meanfile.toStdString());
	mythread->SetCaf(cly);
	this->mythread->start();
}
void caffeui::Caffed()
{
	ui.LogText->append("init caffe success");
}
void caffeui::getmes(int time, float score)
{
	char buf[100];
	sprintf(buf,"%2d:%2d -- %f", time / 60, time % 60, score);
	//printf(buf, "%2d:%2d -- %f", time / 60, time % 60, score);
	ui.LogText->append(buf);
	data.push_back(std::make_tuple(time, score));
}
void caffeui::AddSegitem(int stime, int endtime, int duration, QString name)
{
	segmentation *test = new segmentation(0, stime, endtime, duration, name);
	_model->appendItem(test);

}
void caffeui::AnalysisMsg()
{
	QString pdata = ui.ScoreIp->text();
	bool flag = true;
	string suffixName = SplitVideo::Get()->suffixName;
	float score = pdata.toFloat(&flag);
	vector<int> segtime;
	vector<int> segind;
	if (pdata.isEmpty() || !flag)
	{
		ui.LogText->append("invalid score input");
		return;
	}
	for (auto p = data.begin(); p != data.end(); p++)
	{
		float Pscore = std::get<1>(*p);
		if (Pscore > score)
		{
			segtime.push_back(std::get<0>(*p));
		}
	}
	if (segtime.empty())
		return;
	for (auto p = segtime.begin(); p != segtime.end(); p++)
	{
		if (p == segtime.begin())
		{
			segind.push_back(*p);
		}
		else if (*(p) - *(p-1) > 10)
		{
			segind.push_back(*(p - 1));
			segind.push_back(*p);
		}
	}
	segind.push_back(SplitVideo::Get()->totalSec);
	for (auto p = segind.begin() + 1; p != segind.end(); p = p + 2)
	{
		QString name = QString("%1.%2").arg(*p).arg(suffixName.c_str());
		int start = *(p-1);
		int end = *p;
		int duration = end - start;
		AddSegitem(start, end, duration, name);

	}
}
void caffeui::timerEvent(QTimerEvent * e)
{
	/*if (SplitVideo::Get()->bufsize > 0)
	{
		ui.LogText->setText(SplitVideo::Get()->getbuf());
	}*/
}
caffeui::~caffeui() {
	
}
