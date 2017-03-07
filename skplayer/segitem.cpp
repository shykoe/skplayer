#include "segitem.hpp"

segitem::segitem(segmentation *seg, QObject * parent) :_seg(seg), QObject(parent) 
{
	
}

int segitem::columnCount()
{
	return 5;
}
QString int2time(int sec)
{
	return QString("%1:%2").arg(sec / 60).arg(sec % 60, 2 ,10, QLatin1Char('0'));
}
int time2int(QString time)
{
	if (time.contains(QRegExp("^\\d+:\\d{0,2}$")))
	{
		return time.section(':', 0, 0).toInt() * 60 + time.section(':', 1, 1).toInt();
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
		case 1://starttime
			return QVariant(int2time(_seg->StartTime));
		case 2://endtime
			return QVariant(int2time(_seg->EndTime));
		case 3://duration
			return QVariant(int2time(_seg->Duration));
		case 4:
			return QVariant(_seg->name);
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
		_seg->id = value.toInt();
		return;
	case 1:
		_seg->StartTime = time2int(value.toString());
		return;
	case 2:
		_seg->EndTime = time2int(value.toString());
		return;
	case 3:
		_seg->Duration = time2int(value.toString());
		return;
	case 4:
		_seg->name = value.toString();
		return;
	default:
		return;
	}
}

segitem::~segitem() {
	
}

segmentation::segmentation(int id, int stime, int endtime, int duration, QString name)
	:id(id), StartTime(stime), EndTime(endtime), Duration(duration), name(name)
{
}
