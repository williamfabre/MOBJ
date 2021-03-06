#include "CellsModel/CellsModel.h"
#include "Cell/Cell.h"


namespace Netlist {

CellsModel::CellsModel(QObject* parent):
	QAbstractTableModel(parent),cell_(NULL)
{
}

CellsModel::~CellsModel()
{
}

void CellsModel::setCell(Cell* cell)
{
	emit layoutAboutToBeChanged();
	cell_ = cell;
	emit layoutChanged();
}

int CellsModel::rowCount(const QModelIndex& parent) const
{
	return Cell::getAllCells().size();
}

int CellsModel::columnCount(const QModelIndex& parent) const
{
	// il n'y a pas de mastercell
	return 1;
}

QVariant CellsModel::data(const QModelIndex& index, int role) const
{
	if (not index.isValid()) return QVariant();

	if (role == Qt::DisplayRole){

		int row = index.row();
		return Cell::getAllCells()[row]->getName().c_str();
	}
	return QVariant();
}

QVariant CellsModel::headerData(int section,
				Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Vertical) return QVariant();
	if (role != Qt::DisplayRole) return QVariant();

	if (section == 0) return "Cell";
	return QVariant();
}

Cell* CellsModel::getModel(int row)
{
	if (not cell_) return NULL;

	if (row >= (int)Cell::getAllCells().size()) return NULL;

	return Cell::getAllCells()[row];
}

void CellsModel::updateDatas()
{
	// il faut mettre a jour le layout et
	emit layoutAboutToBeChanged();
	cerr << "rechergement" << endl;
	emit layoutChanged();
	// utuliser le cell widget
}

}
