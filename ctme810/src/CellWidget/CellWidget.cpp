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
#include "Cell/Cell.h"
#include "Line/Line.h"
#include "Node/Node.h"
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
QWidget(parent),
cell_(NULL),
viewport_(Box (0 ,0 ,500 ,500))
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
	painter.setPen(QPen(Qt::darkGreen , 1));
	QRect rect = boxToScreenRect(viewport_); // anciennement appelait box
	painter.drawRect(rect) ;

	// instance
	painter.setPen(QPen(Qt::red , 0));
	//painter.setBrush(QBrush(Qt::red));
	query(1, painter);
	painter.drawRect(rect);

	// other
	painter.setPen(QPen(Qt::darkGreen, 3));
	//painter.setBrush(QBrush(Qt::darkGreen));
	query(2, painter);
	painter.drawRect(rect);

	painter.setPen(QPen(Qt::cyan, 1));
	//painter.setBrush(QBrush(Qt::darkGreen));
	query(3, painter);
	painter.drawRect(rect);

}

void CellWidget::query(unsigned  int flags , QPainter& painter)
{
	unsigned int InstanceShapes = 1;

	unsigned int TermShapes = 2;
	unsigned int LineShapes = 3;
	unsigned int ArcShapes = 4;
	unsigned int EllipseShapes= 5;

	unsigned int Children = 6;

	BoxShape* boxShape = NULL;
	TermShape* termShape = NULL;
	LineShape* lineShape = NULL;
	ArcShape* arcShape = NULL;
	EllipseShape* ellipseShape = NULL;

	if ((not  cell_) or (not  flags))  return;

	const vector <Instance*>& instances = cell_->getInstances();

	for (size_t i = 0; i < instances.size() ; ++i) {
		Point instPos = instances[i]->getPosition();
		const Symbol* symbol = instances[i]->getMasterCell()->getSymbol ();

		if (not symbol) continue;

		//if (flags & InstanceShapes) {

			//const vector<Shape*>& shapes = symbol->getShapes();

			//symbol->toXml(cerr);
			//cerr << endl;
			//for (size_t j=0 ; j < shapes.size() ; j++) {

				//if (shapes[j]){
					//boxShape = dynamic_cast<BoxShape*>(shapes[j]);
					//cerr << j << " : ";
					//shapes[j]->toXml(cerr);
					//cerr << endl;
				//}

				//if (boxShape) {
					//cerr << "test1234" << endl;
					//Box box = boxShape->getBoundingBox();
					//QRect rect = boxToScreenRect(box.translate(instPos));
					//painter.drawRect(rect);
				//}
			//}
		//}
		//if (flags & TermShapes) {

			//const vector<Shape*>& shapes = symbol->getShapes();

			//symbol->toXml(cerr);
			//cerr << endl;
			//for (size_t j=0 ; j < shapes.size() ; j++) {

				//if (shapes[j]){
					//termShape = dynamic_cast<TermShape*>(shapes[j]);
					//cerr << j << " : ";
					//shapes[j]->toXml(cerr);
					//cerr << endl;
				//}

				//if (termShape) {
					//cerr << "test1234" << endl;
					//Box box = termShape->getBoundingBox();
					//QRect rect = boxToScreenRect(box.translate(instPos));
					//painter.drawRect(rect);
				//}
			//}
		//}
		if (flags) {
			const vector<Shape*>& shapes = symbol->getShapes();

			symbol->toXml(cerr);
			cerr << endl;
			for (size_t j=0 ; j < shapes.size() ; j++) {

				if (shapes[j]){
					boxShape = dynamic_cast<BoxShape*>(shapes[j]);
					lineShape = dynamic_cast<LineShape*>(shapes[j]);
					ellipseShape = dynamic_cast<EllipseShape*>(shapes[j]);
					arcShape = dynamic_cast<ArcShape*>(shapes[j]);
					termShape = dynamic_cast<TermShape*>(shapes[j]);
					cerr << j << " : ";
					shapes[j]->toXml(cerr);
					cerr << endl;
				}

				if (lineShape) {
					const QPoint a = pointToScreenPoint(
						Point(lineShape->getX1(), lineShape->getY1()));
					const QPoint b = pointToScreenPoint(
						Point(lineShape->getX2(), lineShape->getY2()));
					QLine ql = QLine(a, b);
					painter.drawLine(ql);
				}

				if (ellipseShape) {
					Box box = ellipseShape->getBoundingBox();
					QRect rect = boxToScreenRect(box.translate(instPos));
					//QRect rect = boxToScreenRect(box);
					painter.drawEllipse(rect);
				}

				if (arcShape) {
					Box box = arcShape->getBoundingBox();
					QRect rect = boxToScreenRect(box.translate(instPos));
					//QRect rect = boxToScreenRect(box);
					painter.drawArc(rect, arcShape->getStart(), arcShape->getSpan());
;
				}
				if (boxShape) {
					Box box = boxShape->getBoundingBox();
					QRect rect = boxToScreenRect(box.translate(instPos));
					painter.drawRect(rect);
				}
				if (termShape) {
					Box box = termShape->getBoundingBox();
					//QRect rect = boxToScreenRect(box.translate(instPos));
					QRect rect = boxToScreenRect(box);
					painter.drawRect(rect);
				}

			}
		}

	}
}

}  // Netlist namespace.
