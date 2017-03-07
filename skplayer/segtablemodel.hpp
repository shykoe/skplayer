#pragma once
#include <QAbstractTableModel>
#include<qlist.h>
#include<memory>
#include"segitem.hpp"
class SegTableModel : public QAbstractTableModel {
	Q_OBJECT

public:
	explicit SegTableModel(QObject * parent = Q_NULLPTR);
	~SegTableModel();
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	std::shared_ptr<segitem> getItem(const int &row) const;
	bool appendItem(segmentation* seg, const QModelIndex &parent = QModelIndex());
	Qt::ItemFlags flags(const QModelIndex &index) const override;
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
private:
	QList< std::shared_ptr<segitem> > _items;
	
};
