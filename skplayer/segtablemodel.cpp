#include "segtablemodel.hpp"

SegTableModel::SegTableModel(QObject * parent) : QAbstractTableModel(parent) {
	
}

SegTableModel::~SegTableModel() {
	
}

int SegTableModel::rowCount(const QModelIndex & parent) const
{
	return _items.count();
}

int SegTableModel::columnCount(const QModelIndex & parent) const
{
	return segitem::columnCount();
}

QVariant SegTableModel::data(const QModelIndex & index, int role) const
{
	if(!index.isValid())
		return QVariant();
	auto item = getItem(index.row());
	return item->data(index.column(), role);
}

QModelIndex SegTableModel::index(int row, int column, const QModelIndex & parent) const
{
	if (row < 0 || row >= _items.size()) 
		return QModelIndex();
	else
	{
		auto item = getItem(row);
		return createIndex(row, column, item.get());
	}
}

QVariant SegTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Vertical || role != Qt::DisplayRole) {
		return QVariant();
	}
	switch (section)
	{
	case 0:
		return QVariant(tr("ID"));
	case 1:
		return QVariant(tr("StartTime"));
	case 2:
		return QVariant(tr("EndTime"));
	case 3:
		return QVariant(tr("Duration"));
	case 4:
		return QVariant(tr("name"));
	default:
		return QVariant();
	}
}

std::shared_ptr<segitem> SegTableModel::getItem(const int & row) const
{
	return _items.at(row);
}

bool SegTableModel::appendItem(segmentation * seg, const QModelIndex & parent)
{
	seg->id = _items.count();
	std::shared_ptr<segitem> newItem = std::make_shared<segitem>(seg, this);
	beginInsertRows(parent, _items.count(), _items.count() + 1);
	_items.append(newItem);
	endInsertRows();

	return true;
}

Qt::ItemFlags SegTableModel::flags(const QModelIndex & index) const
{
	if (!index.isValid())
		return QAbstractItemModel::flags(index);
	if (index.column() == 0)
	{
		return QAbstractItemModel::flags(index);
	}
	return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool SegTableModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
	if (index.isValid() && role == Qt::EditRole) 
	{
		auto item = getItem(index.row());
		item->setData(index.column(), value);
		emit dataChanged(index, index);
		return true;
	}
	return false;
}
