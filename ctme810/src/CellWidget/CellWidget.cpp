// -*- explicit-buffer-name: "CellWidget.cpp<M1-MOBJ/8-10>" -*-

#include <QResizeEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QApplication>
#include "CellWidget/CellWidget.h"
#include "Term/Term.h"
#include "Instance/Instance.h"
#include "Symbol/Symbol.h"
#include "Shape/Shape.h"
#include "Shape/definition/BoxShape.h"
#include "Shape/definition/TermShape.h"
#include "Shape/definition/LineShape.h"
#include "Shape/definition/ArcShape.h"
#include "Shape/definition/EllipseShape.h"
#include "Node/Node.h"
#include "Cell/Cell.h"
#include "Line/Line.h"
#include "Net/Net.h"


namespace Netlist {

using namespace std;


ostream& operator<< (ostream& o, const QRect& rect)
{
	o << "<QRect x:" << rect.x()
		<<       " y:" << rect.y()
		<<       " w:" << rect.width()
		<<       " h:" << rect.height() << ">";
	return o;
}


ostream& operator<< (ostream& o, const QPoint& p)
{ o << "<QRect x:" << p.x() << " y:" << p.y() << ">"; return o; }



CellWidget::CellWidget(QWidget* parent):
	cell_(NULL),
	viewport_(Box(0 ,0 ,500 ,500)),
	QWidget(parent)
{
	setAttribute     (Qt:: WA_OpaquePaintEvent);
	setAttribute     (Qt:: WA_NoSystemBackground);
	setSizePolicy    (QSizePolicy::Expanding // X direction.
			  ,QSizePolicy::Expanding);// Y direction.
	setFocusPolicy   (Qt:: StrongFocus);
	setMouseTracking(true);
}



CellWidget::~CellWidget ()
{ }


void  CellWidget::setCell (Cell* cell)
{
	cell_ = cell;
	repaint();
}


QSize  CellWidget::minimumSizeHint () const
{
	return QSize(500,500);
}


void CellWidget::resizeEvent(QResizeEvent* event)
{
	const  QSize& size = event ->size ();
	//  Assume  the  resize  is  always  done by  drawing  the  bottom
	//  right  corner.
	viewport_.setX2(viewport_.getX1() + size.width  ());
	viewport_.setY1(viewport_.getY2() - size.height ());
	cerr  << "CellWidget :: resizeEvent ()␣viewport_:" << viewport_  <<
		endl;
}

void CellWidget::keyPressEvent(QKeyEvent* event)
{
	event ->ignore ();
	if (event ->modifiers () & (Qt:: ControlModifier|Qt:: ShiftModifier))
		return;
	switch(event ->key()) {
	case Qt:: Key_Up:    goUp    ();  break;
	case Qt:: Key_Down: goDown  ();  break;
	case Qt:: Key_Left: goLeft  ();  break;
	case Qt:: Key_Right:goRight ();  break;
	default: return;
	}
	event ->accept ();
}

void CellWidget::goRight ()
{
	viewport_.translate(Point (-20, 0));
	repaint ();
}

void CellWidget::goUp()
{
	viewport_.translate(Point (0, -20));
	repaint ();
}

// TODO
void CellWidget::goLeft()
{
	viewport_.translate(Point (20, 0));
	repaint ();
}

// TODO
void CellWidget::goDown()
{
	viewport_.translate(Point (0, 20));
	repaint ();
}


void CellWidget::paintEvent (QPaintEvent* event)
{

	QPainter painter(this);
	painter.setBackground(QBrush(Qt::black));
	painter.eraseRect(QRect(QPoint (0,0), size()));
	QRect rect = boxToScreenRect(viewport_); // anciennement appelait box
	painter.drawRect(rect) ;

	// line
	painter.setPen(QPen(Qt::cyan, 1));
	query(1, painter);

	// ellipse
	painter.setPen(QPen(Qt::cyan, 1));
	//painter.setBrush(QBrush(Qt::cyan));
	query(2, painter);

	// arc
	painter.setPen(QPen(Qt::darkGreen, 3));
	//painter.setBrush(QBrush(Qt::darkGreen));
	query(3, painter);

	// instance
	painter.setPen(QPen(Qt::yellow, 2));
	query(4, painter);

	// term
	painter.setPen(QPen(Qt::red, 5));
	query(5, painter);

	// Nodeterm
	painter.setPen(QPen(Qt::red, 5));
	query(6, painter);

	// NodePoint
	painter.setPen(QPen(Qt::cyan, 5));
	query(7, painter);

	// Line
	// term modele
	painter.setPen(QPen(Qt::red, 10));
	query(9, painter);

	painter.setPen(QPen(Qt::cyan, 1));
	query(10, painter);




}

void CellWidget::query(unsigned  int flags , QPainter& painter)
{
	BoxShape* boxShape = NULL;
	TermShape* termShape = NULL;
	LineShape* lineShape = NULL;
	ArcShape* arcShape = NULL;
	EllipseShape* ellipseShape = NULL;
	NodeTerm* nodeTerm = NULL;
	NodePoint* nodePoint = NULL;
	Line* line = NULL;

	if ((not  cell_) or (not  flags))  return;

	const vector <Instance*>& instances = cell_->getInstances();
	for (size_t i = 0; i < instances.size() ; i++) {
		Point instPos = instances[i]->getPosition();
		// NAME
		const QPoint name = pointToScreenPoint(instPos.translate(0,0));
		painter.drawText(name , QString::fromStdString(instances[i]->getName()));


		const Symbol* symbol = instances[i]->getMasterCell()->getSymbol();

		if (not symbol) continue;

		const vector<Shape*>& shapes = symbol->getShapes();

		for (size_t j=0 ; j < shapes.size() ; j++) {

			if (shapes[j]){
				boxShape = dynamic_cast<BoxShape*>(shapes[j]);
				lineShape = dynamic_cast<LineShape*>(shapes[j]);
				ellipseShape = dynamic_cast<EllipseShape*>(shapes[j]);
				arcShape = dynamic_cast<ArcShape*>(shapes[j]);
				termShape = dynamic_cast<TermShape*>(shapes[j]);
			}

			if (lineShape && (flags==1)) {
				const QPoint a = pointToScreenPoint(Point(lineShape->getX1(), lineShape->getY1()).translate(instPos));
				const QPoint b = pointToScreenPoint(Point(lineShape->getX2(), lineShape->getY2()).translate(instPos));
				QLine ql = QLine(a, b);
				painter.drawLine(ql);
			}

			if (ellipseShape && (flags==2)) {
				Box box = ellipseShape->getBoundingBox();
				QPoint a = pointToScreenPoint(Point(box.getX1(), box.getY1()).translate(instPos));
				QPoint b = pointToScreenPoint(Point(box.getX2(), box.getY2()).translate(instPos));
				QRect rect = QRect(a,b);
				painter.drawEllipse(rect);
			}

			if (arcShape && (flags==3)) {
				Box box = arcShape->getBoundingBox();
				QPoint a = pointToScreenPoint(Point(box.getX1(), box.getY1()).translate(instPos));
				QPoint b = pointToScreenPoint(Point(box.getX2(), box.getY2()).translate(instPos));

				QRect rect = QRect(a,b);
				// Draws the arc defined by the given rectangle, startAngle and spanAngle.
				// The startAngle and spanAngle must be specified in 1/16th of a degree, i.e. a
				// full circle equals 5760 (16 * 360). Positive values for the angles mean
				// counter-clockwise while negative values mean the clockwise direction.
				// Zero degrees is at the 3 o'clock position.
				painter.drawArc(rect, arcShape->getStart()*16, arcShape->getSpan()*16);
				//painter.drawArc(rect, arcShape->getStart(), arcShape->getSpan());
			}

			if (boxShape && (flags==4)) {
				Box box = boxShape->getBoundingBox();
				QPoint a = pointToScreenPoint(Point(box.getX1(), box.getY1()).translate(instPos));
				QPoint b = pointToScreenPoint(Point(box.getX2(), box.getY2()).translate(instPos));
				QRect rect = QRect(a,b);
				painter.drawRect(rect);
			}

			if (termShape && (flags==5)) {
				const QPoint a = pointToScreenPoint(Point(termShape->getX(), termShape->getY()).translate(instPos));
				painter.drawPoint(a);
			}
		}
	}


	/********************* terms **********************/
	const vector<Term*>& terms = cell_->getTerms();
	for (size_t i = 0; i < terms.size() ; i++) {
		if (terms[i] && (flags==9)) {
			const QPoint a = pointToScreenPoint(terms[i]->getPosition());
			//const QPoint a = QPoint(terms[i]->getPosition().getX(), terms[i]->getPosition().getY());
			painter.drawPoint(a);

			//name
			const QPoint name = pointToScreenPoint(terms[i]->getPosition().translate(0,10));
			painter.drawText(name , QString::fromStdString(terms[i]->getName()));
		}
	}

	const vector<Net*>& nets = cell_->getNets();
	for (size_t i = 0; i < nets.size() ; i++) {

		//******************** lines ********************
		const vector<Line*>& lines = nets[i]->getLines();
		for (size_t j=0 ; j < lines.size() ; j++) {
			if (lines[j]) {
				line = lines[j];
				if (line && (flags==10)) {
					const QPoint a = pointToScreenPoint(line->getSourcePosition());
					const QPoint b = pointToScreenPoint(line->getTargetPosition());
					QLine ql = QLine(a, b);
					painter.drawLine(ql);
				}
			}
		}

		//******************** nodeterm *********************
		const vector<Node*>& nodes = nets[i]->getNodes();
		for (size_t j=0 ; j < nodes.size() ; j++) {

			if (nodes[j]){
				nodeTerm = dynamic_cast<NodeTerm*>(nodes[j]);
				nodePoint = dynamic_cast<NodePoint*>(nodes[j]);
			}

			if (nodeTerm && (flags==6)) {
				const QPoint a = pointToScreenPoint(nodeTerm->getPosition());
				painter.drawPoint(a);
				const QPoint name = pointToScreenPoint(nodeTerm->getPosition().translate(0,10));
				painter.drawText(name , QString::fromStdString(nodeTerm->getTerm()->getName()));

			}

			if (nodePoint && (flags==7)) {
				const QPoint a = pointToScreenPoint(nodePoint->getPosition());
				painter.drawPoint(a);
			}
		}
	}
}

}  // Netlist namespace.
