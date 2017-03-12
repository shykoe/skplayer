#pragma once
#include <QObject>
#include <QVariant>
#include <memory>
#include<qstring.h>
#ifndef SEGITEM_H
#define SEGITEM_H
typedef struct segmentation
{
	segmentation(int id, int stime, int endtime, int duration, QString name);
	unsigned int id;
	unsigned int StartTime;
	unsigned int EndTime;
	unsigned int Duration;
	QString name;
}segmentation;
class segitem : public QObject {
	Q_OBJECT

public:
	explicit segitem(segmentation *seg, QObject * parent = Q_NULLPTR);
	static int columnCount();
	QVariant data(int column, int role = Qt::DisplayRole) const;
	void setData(int column,QVariant value);
	~segitem();

private:
	std::shared_ptr<segmentation> _seg;
	
};
#endif