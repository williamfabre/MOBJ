#include "CellsLib/CellsLib.h"
#include "Cell/Cell.h"
#include "CellViewer/CellViewer.h"
#include <QCloseEvent>
#include <QMessageBox>
#include <QTranslator>
#include <QHeaderView>

namespace Netlist{

CellsLib::CellsLib(QWidget* parent) :
QWidget(parent, Qt::Window),
//QWidget(parent),
cellViewer_(NULL),
baseModel_(new CellsModel(this)),
view_(new QTableView(this)),
load_(new QPushButton(this))
{
	// ne pas detruire la fenetre
	setAttribute(Qt::WA_QuitOnClose, false);
	setAttribute(Qt::WA_DeleteOnClose, false);
	setContextMenuPolicy(Qt::ActionsContextMenu);

	view_->setShowGrid(false);
	view_->setAlternatingRowColors(true);
	view_->setSelectionBehavior(QAbstractItemView::SelectRows);
	view_->setSelectionMode(QAbstractItemView::SingleSelection);
	view_->setSortingEnabled(true);
	view_->setModel(baseModel_);
	view_->setMinimumWidth(400);
	view_->setMinimumHeight(400);


	QHeaderView* horizontalHeader = view_->horizontalHeader();
	horizontalHeader->setDefaultAlignment(Qt::AlignHCenter);
	horizontalHeader->setMinimumSectionSize(300);
	horizontalHeader->setStretchLastSection(true);

	QHBoxLayout* hLayout = new QHBoxLayout();
	load_->setText("Load");
	hLayout->addStretch();
	hLayout->addWidget(load_);
	hLayout->addStretch();

	QVBoxLayout* vLayout = new QVBoxLayout();
	vLayout->setSizeConstraint(QLayout::SetFixedSize);
	vLayout->addWidget(view_);
	vLayout->addLayout(hLayout);
	setLayout(vLayout);



	QHeaderView* verticalHeader = view_->verticalHeader();
	verticalHeader->setVisible(false);

	load_->setText("Load");
	connect( load_, SIGNAL( clicked() ), this, SLOT( load() ) );

}


int CellsLib::getSelectedRow() const
{
	QModelIndexList selecteds = view_->selectionModel()->
		selection().indexes();
	if (selecteds.empty()) return -1;
	return selecteds.first().row();
}

void CellsLib::load()
{
	int selectedRow = getSelectedRow();
	if (selectedRow < 0) return;
	cellViewer_->setCell(baseModel_->getModel(selectedRow));
}
void CellsLib::setCellViewer(CellViewer* cellViewer)
{
	if (cellViewer_)
		disconnect(this, 0, 0 ,0);
	cellViewer_ = cellViewer;
}

void CellsLib::closeEvent (QCloseEvent *event)
{
	QMessageBox::StandardButton resBtn =
		QMessageBox::question( this, tr("toto\n"),
			tr("Are you sure?\n"),
			QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
			QMessageBox::Yes);
	if (resBtn != QMessageBox::Yes) {
		event->ignore();
	} else {
		event->accept();
	}
}

}
