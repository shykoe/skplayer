#pragma once
#include <QWidget>
#include <QSortFilterProxyModel>
#include "ui_caffeui.h"
#include"segtablemodel.hpp"
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
private slots:
	void contextMenu(const QPoint &pos);
	void splitvideo();
private:
	Ui::caffeui ui;
	QMenu *menu;
	QSortFilterProxyModel *proxyModel;
	SegTableModel *_model;
};
