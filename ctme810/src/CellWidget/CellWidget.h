#ifndef NETLIST_CELL_WIDGET_H
#define NETLIST_CELL_WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QRect>
#include <QPoint>

class QPainter;

#include "Box/Box.h"


namespace Netlist {

class Cell;
class NodeTerm;


class CellWidget : public QWidget {
	Q_OBJECT;
private:
	Cell* cell_;

public:
	CellWidget(QWidget* parent=NULL);
	virtual ~CellWidget();
	void setCell (Cell*);
	inline Cell* getCell() const;
	virtual QSize minimumSizeHint() const;
	virtual void resizeEvent(QResizeEvent*);
	//inline QRect boxToScreenRect(const Box&) const;
	//inline QPoint pointToScreenPoint(const Point &) const;
	//inline Box screenRectToBox(const QRect&) const;
	//inline Point screenPointToPoint(const QPoint &) const;

protected:
	virtual void paintEvent(QPaintEvent*);
	//virtual void keyPressEvent(QKeyEvent *);
};


inline Cell* CellWidget::getCell() const
{
	return cell_;
}

}  // Netlist namespace.

#endif  // NETLIST_CELL_WIDGET_H
