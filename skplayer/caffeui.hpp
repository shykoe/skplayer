#pragma once
#include <QWidget>
#include <QSortFilterProxyModel>
#include <vector>
#include <tuple>
#include "ui_caffeui.h"
#include"segtablemodel.hpp"
#include"caffethread.h"
#include"sffmpeg.h"
#ifdef STRICT
#undef STRICT
#define __CLASSIFIER__
#include"Classifier.h"
#endif
#ifndef __CLASSIFIER__
#define __CLASSIFIER__
#include"Classifier.h"
#endif // !__CLASSIFIER__
class caffeui : public QWidget {
	Q_OBJECT

public:
	caffeui(QWidget * parent = Q_NULLPTR);
	void timerEvent(QTimerEvent *e);
	~caffeui();
public slots:
	void SetModelFile();
	void SetMeanFile();
	void SetProtoFile();
	void SetOutputFile();
	void InitCaffe();
	void AnalysisMsg();
private slots:
	void contextMenu(const QPoint &pos);
	void splitvideo_s();
	void splitvideo_e();
	void toPlay();
	void Caffed();
	void getmes(int time, float score);
signals:
	void sendconf(QString model, QString proto, QString mean);
private:
	void AddSegitem(int stime, float score);
	Ui::caffeui ui;
	QMenu *menu;
	QSortFilterProxyModel *proxyModel;
	SegTableModel *_model;
	caffe::Classifier* cly = NULL;
	CaffeThread* mythread;
	int startItem = -1;
	int endItem = -1;
	std::vector<std::tuple<int, float> > data;
};
