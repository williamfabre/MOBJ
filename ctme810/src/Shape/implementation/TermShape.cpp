#include "Cell/Cell.h"
#include "Term/Term.h"
#include "Shape/Shape.h"
#include "Shape/definition/TermShape.h"


namespace Netlist
{

TermShape::TermShape(Symbol* owner , string  name , int x1, int y1)
	:Shape(owner), term_(NULL), x1_(x1), y1_(y1), align_(TermShape::TopLeft)
{
	Cell* cell = getCell();
	term_ = cell->getTerm(name);
}

TermShape::~TermShape()
{
}

string TermShape::a2s(TermShape::NameAlign align)
{
	if (align == TopLeft)
		return "top_left";
	if (align == TopRight)
		return "top_right";
	if (align == BottomLeft)
		return "bottom_left";
	else
		return "bottom_right";

}
TermShape::NameAlign TermShape::s2a(string align)
{
	if (align == "top_left")
		return TopLeft ;
	if (align == "top_right")
		return TopRight;
	if (align == "bottom_left")
		return BottomLeft ;
	if (align == "bottom_right")
		return BottomRight ;
	else
		return BottomRight;
}

Box TermShape::getBoundingBox() const
{
	return Box(x1_, y1_, x1_, y1_);
}

void TermShape::setNameAlign(TermShape::NameAlign align)
{
	align_ = align;
}

void TermShape::toXml(std::ostream& stream) const
{
	stream  << indent
		<< "<term name=\"" << term_->getName() << "\" "
		<< "x1=\"" << x1_ << "\" "
		<< "y1=\"" << y1_ << "\" "
		<< "align=\"" << a2s(align_) << "\" />" << std::endl;
}

TermShape* TermShape::fromXml(Symbol* owner, xmlTextReaderPtr reader)
{
	TermShape* tshape = NULL;

	int x1;
	int y1;

	xmlChar* xml_x1_value;
	xmlChar* xml_y1_value;
	xmlChar* xml_termname_value;
	xmlChar* xml_align_value;

	const xmlChar* xml_x1;
	const xmlChar* xml_y1;
	const xmlChar* xml_termname;
	const xmlChar* xml_align;
	const xmlChar* nodeName;

	string s_x1;
	string s_y1;
	string s_termname;
	string s_align;

	// s'il y a declaration d'un name
	xml_x1 = (const xmlChar*)"x1";
	xml_y1 = (const xmlChar*)"y1";
	xml_termname = (const xmlChar*)"name";
	xml_align = (const xmlChar*)"align";

	// prendre la valeur de la declaration
	xml_x1_value = xmlTextReaderGetAttribute(reader, xml_x1);
	xml_y1_value = xmlTextReaderGetAttribute(reader, xml_y1);
	xml_termname_value = xmlTextReaderGetAttribute(reader, xml_termname);
	xml_align_value = xmlTextReaderGetAttribute(reader, xml_align);
	nodeName = xmlTextReaderConstLocalName(reader);

	// transformer cette valeur en string
	s_x1 = xmlCharToString(xml_x1_value);
	s_y1 = xmlCharToString(xml_y1_value);
	s_termname = xmlCharToString(xml_termname_value);
	s_align = xmlCharToString(xml_align_value);
	const xmlChar* nodeTag  = xmlTextReaderConstString(reader, (const xmlChar*)"term");

	if (nodeName == nodeTag){
		if ( not (s_x1.empty() && s_y1.empty() && s_align.empty()
			  && s_termname.empty())){
			x1 = atoi(s_x1.c_str());
			y1 = atoi(s_y1.c_str());
			tshape = new TermShape(owner, s_termname, x1, y1);
			tshape->setNameAlign(s2a(s_align));
		}
		return tshape;
	}
	return tshape;

}
}
