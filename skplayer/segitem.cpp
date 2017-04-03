#include "segitem.hpp"

segitem::segitem(segmentation *seg, QObject * parent) :_seg(seg), QObject(parent) 
{
	
}

int segitem::columnCount()
{
	return 3;
}
QString int2time(int sec)
{
	return QString("%1:%2").arg(sec / 60).arg(sec % 60, 2 ,10, QLatin1Char('0'));
}
unsigned int time2int(QString time)
{
	if (time.contains(QRegExp("^\\d+:\\d{0,2}$")))
	{
		return time.section(':', 0, 0).toUInt() * 60 + time.section(':', 1, 1).toUInt();
	}
	return 0;
}
QVariant segitem::data(int column, int role) const
{
	if (!_seg)
	{
		return QVariant();
	}
	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		switch (column)
		{
		case 0://id
			return QVariant(_seg->id);
		case 1://time
			return QVariant(int2time(_seg->_time));
		case 2://score
			return QVariant(_seg->_score);
		default:
			return QVariant();
		}
	}
	if (role == Qt::BackgroundRole)
	{
		if(this->segflag ==  Start)//start 
			return QColor(87, 132, 149);
		if (this->segflag == End)//end
			return QColor(152, 84, 115);
		return QVariant();
	}
	return QVariant();

}

QVariant segitem::truedata(int column) const
{
	if (!_seg)
	{
		return QVariant();
	}
	else
	{
		switch (column)
		{
		case 0://id
			return QVariant(_seg->id);
		case 1://starttime
			return QVariant(_seg->_time);
		case 2://endtime
			return QVariant(_seg->_score);
		default:
			return QVariant();
		}
	}
	return QVariant();
}

void segitem::setData(int column, QVariant value)
{
	if (column > columnCount() || column < 0)
	{
		return;
	}
	switch (column)
	{
	case 0:
		_seg->id = value.toUInt();
		return;
	case 1:
		_seg->_time = time2int(value.toString());
		return;
	case 2:
		_seg->_score = value.toFloat();
		return;
	default:
		return;
	}
}

void segitem::setflag(SegTabCl flag)
{
	this->segflag = flag;
}

segitem::~segitem() {
	
}

segmentation::segmentation(int id, int time, float score)
	:id(id), _time(time), _score(score)
{
}
