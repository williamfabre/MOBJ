#ifndef  NETLIST_INSTANCES_MODEL_H
#define  NETLIST_INSTANCES_MODEL_H


#include <QAbstractTableModel>
#include <vector>
#include <QFont>
#include <QApplication>


namespace Netlist {

class Cell;

class InstancesModel : public QAbstractTableModel {
	Q_OBJECT;
private:
	Cell * cell_ ;

public:
	InstancesModel(QObject * parent = NULL);
	virtual ~InstancesModel();

	voidsetCell(Cell *);
	Cell* getModel(int row);
	int rowCount(const QModelIndex& parent = QModelIndex()) const ;
	int columnCount(const QModelIndex& parent = QModelIndex()) const ;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation,
			    int role = Qt::DisplayRole) const ;
};

}

#endif //  NETLIST_INSTANCES_MODEL_H_
