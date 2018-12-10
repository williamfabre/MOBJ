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
	Cell* cell_;

public:
	CellWidget(QWidget* parent=NULL);
	virtual ~CellWidget();
	void setCell (Cell*);
	inline Cell* getCell() const;
	virtual QSize minimumSizeHint() const;
	virtual void resizeEvent(QResizeEvent*); // redimentionner
	//inline QRect boxToScreenRect(const Box&) const;
	//inline QPoint pointToScreenPoint(const Point &) const;
	//inline Box screenRectToBox(const QRect&) const;
	//inline Point screenPointToPoint(const QPoint &) const;
	//inline int xToScreenX(int x) const;
	//inline int yToScreenY(int y) const;
	//inline int screenXToX(int x) const;
	//inline int screenYToY(int y) const;

protected:
	// redefinition des methodes QT il faut respecter le prototype
	virtual void paintEvent(QPaintEvent*); // re tracer le dessin
	//virtual void keyPressEvent(QKeyEvent *); // appuie / relachement
};


inline Cell* CellWidget::getCell() const
{
	return cell_;
}

// juste x c'est schema, si c'est screen screenx ou screeny
// XschemaToScreenX
// qt en long
// toutes ces fonctions dependandent du viewport
//inline int CellWidget::xToScreenX(int x) const
//{
	//return 0;
//}
//inline int CellWidget::yToScreenY(int y) const
//{
	//return 0;
//}
//inline int CellWidget::screenXToX(int x) const
//{
	//return 0;
//}
//inline int CellWidget::screenYToY(int y) const
//{
	//return 0;
//}
//inline QRect boxToScreenRect(const Box& box) const
//{
	//return NULL;
//}
//inline QPoint pointToScreenPoint(const Point& point) const
//{
	//return NULL;
//}
//inline Box screenRectToBox(const QRect& qrect) const
//{
	//return NULL;
//}
//inline Point screenPointToPoint(const QPoint & qpoint) const
//{
	//return ;
//}

}  // Netlist namespace.

#endif  // NETLIST_CELL_WIDGET_H
