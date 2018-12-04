#ifndef  NETLIST_CELLS_MODEL_H
#define  NETLIST_CELLS_MODEL_H

#include <QAbstractTableModel>
#include <vector>
#include <QFont>
#include <QApplication>


namespace Netlist {

class Cell;

class CellsModel : public QAbstractTableModel {
	Q_OBJECT;
private:
	Cell* cell_ ;

public:
	CellsModel(QObject * parent = NULL);
	virtual ~CellsModel();
	void setCell(Cell *);
	Cell* getModel(int row);
	int rowCount(const QModelIndex& parent = QModelIndex()) const ;
	int columnCount(const QModelIndex& parent = QModelIndex()) const ;
	QVariant data(const QModelIndex& index,
		      int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation,
			    int role = Qt::DisplayRole) const ;
};

}

#endif //  NETLIST_CELLS_MODEL_H_
