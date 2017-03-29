#pragma once
#include <QWidget>
#include <QSortFilterProxyModel>
#include "ui_caffeui.h"
#include"segtablemodel.hpp"
#include"caffethread.h"
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
private slots:
	void contextMenu(const QPoint &pos);
	void splitvideo();
	void Caffed();
signals:
	void sendconf(QString model, QString proto, QString mean);
private:
	Ui::caffeui ui;
	QMenu *menu;
	QSortFilterProxyModel *proxyModel;
	SegTableModel *_model;
	CaffeThread* mythread;
};
