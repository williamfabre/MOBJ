#ifndef NETLIST_CELL_WIDGET_H
#define NETLIST_CELL_WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QRect>
#include <QPoint>

class QPainter;

#include "Box/Box.h"


// On va gerer nous meme le tracer et ne pas utiliser les fonctions
// qui gerent eux meme le tracer. il y aura un seul Qwidget
// Systeme de coordonnees :
// le 0,0 du screen est en haut a gauche -> balayage faisceau cathodique
// le 0,0 du schema est en bas a gauche
//
// le viewport est l'enveloppe englobante du schema. c'est la portion du schema
// affichee par le widget
//
// l'unite est le pixel pour les deux.
//
// decoupler les uniter pour creer un zoom
//
// coordonnees du viewport (surface du Qwidget): coord de fenetre exprimee
// dans le systeme de repere du schema.
// Xschema
namespace Netlist {

class Cell;
class NodeTerm;


class CellWidget : public QWidget {
	Q_OBJECT;
private:
	Box viewport_; // la vue dans la fenetre
	Cell* cell_;

public:
	CellWidget(QWidget* parent=NULL);
	virtual ~CellWidget();
	void setCell (Cell*);
	inline Cell* getCell() const;
	virtual QSize minimumSizeHint() const;
	virtual void resizeEvent(QResizeEvent*); // redimentionner
	inline QRect boxToScreenRect(const Box&) const;
	inline QPoint pointToScreenPoint(const Point &) const;
	inline Box screenRectToBox(const QRect&) const;
	inline Point screenPointToPoint(const QPoint &) const;
	inline int xToScreenX(int x) const;
	inline int yToScreenY(int y) const;
	inline int screenXToX(int x) const;
	inline int screenYToY(int y) const;

	void goRight();
	void goUp();
	void goLeft();
	void goDown();

	void query(unsigned  int flags , QPainter& painter);

protected:
	// redefinition des methodes QT il faut respecter le prototype
	virtual void paintEvent(QPaintEvent*); // re tracer le dessin
	virtual void keyPressEvent(QKeyEvent *); // appuie / relachement
};


inline Cell* CellWidget::getCell() const
{
	return cell_;
}

// juste x c'est schema, si c'est screen screenx ou screeny
// XschemaToScreenX
// qt en long
// toutes ces fonctions dependandent du viewport
inline int CellWidget::xToScreenX(int x) const
{
	return x - viewport_.getX1();
}

inline int CellWidget::yToScreenY(int y) const
{
	return viewport_.getY2() - y;
}

inline int CellWidget::screenXToX(int x) const
{
	return x + viewport_.getX1();
}

inline int CellWidget::screenYToY(int y) const
{
	return viewport_.getY2() - y;
}

inline QRect CellWidget::boxToScreenRect(const Box& box) const
{
	return QRect(xToScreenX(box.getX1()),
			yToScreenY(box.getY1()),
			xToScreenX(box.getX1()),
			yToScreenY(box.getY1()));

}

inline QPoint CellWidget::pointToScreenPoint(const Point& point) const
{
	return QPoint(xToScreenX(point.getX()),
		      yToScreenY(point.getY()));
}

inline Box CellWidget::screenRectToBox(const QRect& qrect) const
{
	int *x1, *y1, *x2, *y2;
	int tmp1, tmp2;
	// get coords from top left and bottom right
	qrect.getCoords(x1, y1, x2, y2);
	tmp1 = *y1;
	tmp2 = *y2;

	*y1 = tmp1; // transform coord in bottom left
	*x1 = tmp2; // transform in top right
	return Box(screenXToX(*x1),
		   screenYToY(*y1),
		   screenXToX(*x2),
		   screenYToY(*y2));
}

inline Point CellWidget::screenPointToPoint(const QPoint& qpoint) const
{
	return Point(screenXToX(qpoint.x()),
			screenYToY(qpoint.y()));
}

}  // Netlist namespace.

#endif  // NETLIST_CELL_WIDGET_H
