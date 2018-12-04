#ifndef  NETLIST_INSTANCES_WIDGET_H
#define  NETLIST_INSTANCES_WIDGET_H

#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include "InstancesModel/InstancesModel.h"
#include <QCloseEvent>

namespace Netlist {

class CellViewer;

class InstancesWidget : public QWidget {
	Q_OBJECT;
public:
	InstancesWidget(QWidget* parent = NULL);
	void setCellViewer(CellViewer*);
	int getSelectedRow() const;
	inline void setCell(Cell*);
	virtual void closeEvent(QCloseEvent*);

	public slots:
		void load();
private:
	CellViewer* cellViewer_;
	InstancesModel* baseModel_;
	QTableView* view_;
	QPushButton* load_;
};

inline void InstancesWidget::setCell(Cell* cell){baseModel_->setCell(cell);}
};

#endif //  NETLIST_INSTANCES_WIDGET_H_
