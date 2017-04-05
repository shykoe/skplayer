#ifndef SKPLAYER_H
#define SKPLAYER_H

#include <QtWidgets/QWidget>
#include "ui_skplayer.h"
#include"segtablemodel.hpp"
#include"caffethread.h"
#include <QSortFilterProxyModel>
#include <vector>
#include <tuple>
class skplayer : public QWidget
{
	Q_OBJECT

public:
	skplayer(QWidget *parent = 0);
	~skplayer();
	void timerEvent(QTimerEvent *e);
	void resizeEvent(QResizeEvent *e);
	void openFile(QString filename);
public slots:
	void open();
	void sliderPressed();
	void sliderReleased();
	void play();
	void splitvideo_s();
	void splitvideo_e();
	void contextMenu(const QPoint &pos);
	void SetModelFile();
	void SetMeanFile();
	void SetProtoFile();
	void SetOutputFile();
	void InitCaffe();
	void AnalysisMsg();
	void getmes(int time, float score);
	void Caffed();
	void toPlay();
	void splitvideo();
	void RestRE();
protected:
//	void closeEvent(QCloseEvent *event) override;

private:
	void AddSegitem(int stime, float score);
	int VideoWidth = 0;
	int VideoHeight = 0;
	QMenu *menu;
	QSortFilterProxyModel *proxyModel;
	SegTableModel *_model;
	caffe::Classifier* cly = NULL;
	CaffeThread* mythread;
	int startItem = -1;
	int endItem = -1;
	std::vector<std::tuple<int, float> > data;
	Ui::skplayerClass ui;
};

#endif // SKPLAYER_H
