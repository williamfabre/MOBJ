#include "Instance/Instance.h"
#include "Cell/Cell.h"
#include "InstancesModel/InstancesModel.h"


// InstancesWidget (.h, .cpp) et le modèle correspondant InstancesModel
// (.h,.cpp), table contenant les instances présentes dans le modèle
// actuellement chargé, ainsi que les master Cells associées.
namespace Netlist {

InstancesModel::InstancesModel(QObject* parent) :
	QAbstractTableModel(parent),cell_(NULL)
{
}

InstancesModel::~InstancesModel()
{
}

void InstancesModel::setCell(Cell* cell)
{
	emit layoutAboutToBeChanged();
	cell_ = cell;
	emit layoutChanged();
}

// Renvoie le nombre d'instances
int InstancesModel::rowCount(const QModelIndex& parent) const
{
	return (cell_) ? cell_->getInstances().size() : 0;
}

//
int InstancesModel::columnCount(const QModelIndex& parent) const
{
	return 2;
}


//Gestion de l'affichage, soit on met le nom de l'instance soit on met la mastercell
QVariant InstancesModel::data(const QModelIndex& index, int role) const
{
	if (not cell_ or not index.isValid()) return QVariant();

	if (role == Qt::DisplayRole){

		int row = index.row();

		switch (index.column()){
			case 0: return cell_->getInstances()[row]->getName().
				c_str();
			case 1: return cell_->getInstances()[row]->
			getMasterCell()->getName().c_str();
		}
	}
	return QVariant();
}


QVariant InstancesModel::headerData(int section,
				    Qt::Orientation orientation, int role) const
{
// InstancesWidget (.h, .cpp) et le modèle correspondant InstancesModel
// (.h,.cpp), table contenant les instances présentes dans le modèle
// actuellement chargé, ainsi que les master Cells associées.
	if (orientation == Qt::Vertical) return QVariant();
	if (role != Qt::DisplayRole) return QVariant();

	switch (section){
		case 0: return "Instances";
		case 1: return "MasterCell";
	}

	return QVariant();
}

// renvoie la cell a partir du row selectionne
Cell* InstancesModel::getModel(int row)
{
	if (not cell_) return NULL;

	if (row >= (int)cell_->getInstances().size()) return NULL;

	return cell_->getInstances()[row]->getMasterCell();
}

}
