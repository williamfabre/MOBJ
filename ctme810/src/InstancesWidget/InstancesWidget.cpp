#include "InstancesWidget/InstancesWidget.h"
#include "Cell/Cell.h"
#include "CellViewer/CellViewer.h"
#include <QHeaderView>

namespace Netlist{

InstancesWidget::InstancesWidget(QWidget* parent) :
	QWidget(parent),
	cellViewer_(NULL),
	baseModel_(new InstancesModel(this)),
	view_(new QTableView(this)),
	load_(new QPushButton(this))
{
	setAttribute(Qt::WA_QuitOnClose, false);
	setAttribute(Qt::WA_DeleteOnClose, false);
	setContextMenuPolicy(Qt::ActionsContextMenu);

	view_->setShowGrid(false);
	view_->setAlternatingRowColors(true);
	view_->setSelectionBehavior(QAbstractItemView::SelectRows);
	view_->setSelectionMode(QAbstractItemView::SingleSelection);
	view_->setSortingEnabled(true);
	view_->setModel(baseModel_);

	this->setMinimumSize(500,500);

	QHeaderView* horizontalHeader = view_->horizontalHeader();
	horizontalHeader->setDefaultAlignment(Qt::AlignHCenter);
	horizontalHeader->setMinimumSectionSize(300);
	horizontalHeader->setStretchLastSection(true);

	QHeaderView* verticalHeader = view_->verticalHeader();
	verticalHeader->setVisible(false);

	load_->setText("Load");
	connect( load_, SIGNAL( clicked() ), this, SLOT( load() ) );

	QHBoxLayout* hLayout = new QHBoxLayout();
	hLayout->addStretch();
	hLayout->addWidget( load_ );
	hLayout->addStretch();


	QVBoxLayout* vLayout = new QVBoxLayout();
	vLayout->addWidget(view_);
	vLayout->addLayout( hLayout );
	setLayout( vLayout );
}

void InstancesWidget::setCellViewer(CellViewer* cellViewer)
{
	if(cellViewer_)
		disconnect(this,0,cellViewer_,0);
	cellViewer_ = cellViewer;
}

int InstancesWidget::getSelectedRow() const
{
	QModelIndexList selecteds = view_->selectionModel()->
		selection().indexes();
	if(selecteds.empty()) return -1;
	return selecteds.first().row();
}

void InstancesWidget::load()
{
	int selectedRow = getSelectedRow();
	if(selectedRow < 0) return;
	cellViewer_->setCell(baseModel_->getModel(selectedRow));
}

void InstancesWidget::closeEvent(QCloseEvent* event)
{
	this->showMinimized();
	event->ignore();
}

}
