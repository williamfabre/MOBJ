#include <cstdlib>
#include "Symbol/Symbol.h"
#include "Shape/Shape.h"
#include "Shape/definition/LineShape.h"
#include "Shape/definition/BoxShape.h"
#include "Shape/definition/TermShape.h"
#include "Shape/definition/EllipseShape.h"
#include "Shape/definition/ArcShape.h"

namespace Netlist
{

Shape::Shape(Symbol* owner) : owner_(owner)
{
	owner_->add(this);
}

Shape::~Shape()
{
	owner_->remove(this);
}

Shape* Shape::fromXml (Symbol* owner, xmlTextReaderPtr reader)
{
	Shape* shape = NULL;

	const xmlChar* xml_box_tag;
	const xmlChar* xml_ellipse_tag;
	const xmlChar* xml_arc_tag;
	const xmlChar* xml_line_tag;
	const xmlChar* xml_term_tag;
	const xmlChar* nodeName;

	// s'il y a declaration d'un name
	xml_box_tag = (const xmlChar*)"box";
	xml_ellipse_tag = (const xmlChar*)"ellipse";
	xml_arc_tag = (const xmlChar*)"arc";
	xml_line_tag = (const xmlChar*)"line";
	xml_term_tag = (const xmlChar*)"term";

	if (xml_box_tag == nodeName)
		shape = BoxShape::fromXml(owner, reader);
	//if (xml_ellipse_tag == nodeName)
		//shape = EllipseShape::fromXml(owner, reader);
	//if (xml_arc_tag == nodeName)
		//shape = ArcShape::fromXml(owner, reader);
	if (xml_line_tag == nodeName)
		shape = LineShape::fromXml(owner, reader);
	//if (xml_term_tag == nodeName)
		//shape = TermShape::fromXml(owner, reader);
	if (shape == NULL){
		cerr << __func__ << endl;
	}
	return shape;
}
}
