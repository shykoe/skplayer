#pragma once
#include <QWidget>
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
private:
	Ui::caffeui ui;
	SegTableModel *_model;
};
