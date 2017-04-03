#pragma once
#include <QObject>
#include <QVariant>
#include <memory>
#include<qstring.h>
#include <QColor>
#ifndef SEGITEM_H
#define SEGITEM_H

typedef struct segmentation
{
	segmentation(int id, int stime,float score);
	unsigned int id;
	unsigned int _time;
	float _score;
}segmentation;
class segitem : public QObject {
	Q_OBJECT

public:
	enum SegTabCl { Skip, Start, End };
	explicit segitem(segmentation *seg, QObject * parent = Q_NULLPTR);
	static int columnCount();
	QVariant data(int column, int role = Qt::DisplayRole) const;
	QVariant truedata(int column) const;
	void setData(int column,QVariant value);
	void setflag(SegTabCl flag);
	~segitem();

private:
	int segflag = 0;
	std::shared_ptr<segmentation> _seg;
	
};
#endif