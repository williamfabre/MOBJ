#ifndef  NETLIST_CELL_VIEWER_H
#define  NETLIST_CELL_VIEWER_H

#include <QMainWindow>
#include "CellWidget/CellWidget.h"

namespace Netlist {
class Cell;
class SaveCellDialog;

class CellViewer : public QMainWindow {
	Q_OBJECT;
private:
	CellWidget* cellWidget_;
	SaveCellDialog* saveCellDialog_;

public:
	CellViewer(QWidget* parent=NULL);
	virtual ~CellViewer();

	void setCell(Cell* cell)
	{
		cellWidget_->setCell(cell);
	}

	Cell* getCell()  const
	{
		return cellWidget_->getCell();
	}

	void saveCell();
};

}

#endif
