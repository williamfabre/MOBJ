#include "Shape/definition/LineShape.h"


namespace Netlist
{

LineShape::LineShape(Symbol* owner, int x1, int y1,int x2, int y2)
	:Shape(owner), x1_(x1), y1_(y1), x2_(x2), y2_(y2)
{
}

LineShape::~LineShape()
{

}


Box LineShape::getBoundingBox () const
{
	return Box(min(x1_, x2_),
		   min(y1_, y2_),
		   max(x1_, x2_),
		   max(y1_, y2_));
}

void LineShape::toXml(std::ostream& stream) const
{
	stream << indent
		<< "<line x1=\"" << getX1() << "\" "
		<< "y1=\"" << getY1() << "\" "
		<< "x2=\"" << getX2() << "\" "
		<< "y2=\"" << getY2()
		<< "\" />" << endl;
}

LineShape* LineShape::fromXml(Symbol* owner, xmlTextReaderPtr reader)
{
	LineShape* lshape = NULL;

	int x1;
	int y1;
	int x2;
	int y2;
	int nodeType;

	xmlChar* xml_x1_value;
	xmlChar* xml_y1_value;
	xmlChar* xml_x2_value;
	xmlChar* xml_y2_value;

	const xmlChar* xml_x1;
	const xmlChar* xml_y1;
	const xmlChar* xml_x2;
	const xmlChar* xml_y2;
	const xmlChar* xml_line;
	const xmlChar* nodeName;

	string s_x1;
	string s_y1;
	string s_x2;
	string s_y2;

	// s'il y a declaration d'un name
	xml_x1 = (const xmlChar*)"x1";
	xml_y1 = (const xmlChar*)"y1";
	xml_x2 = (const xmlChar*)"x2";
	xml_y2 = (const xmlChar*)"y2";
	xml_line = (const xmlChar*)"line";

	// prendre la valeur de la declaration
	xml_x1_value = xmlTextReaderGetAttribute(reader, xml_x1);
	xml_y1_value = xmlTextReaderGetAttribute(reader, xml_y1);
	xml_x2_value = xmlTextReaderGetAttribute(reader, xml_x2);
	xml_y2_value = xmlTextReaderGetAttribute(reader, xml_y2);
	nodeName = xmlTextReaderConstLocalName(reader);

	// transformer cette valeur en string
	s_x1 = xmlCharToString(xml_x1_value);
	s_y1 = xmlCharToString(xml_y1_value);
	s_x2 = xmlCharToString(xml_x2_value);
	s_y2 = xmlCharToString(xml_y2_value);
	nodeType = xmlTextReaderNodeType(reader);

	//cerr << "WEIUFNIUGFENRIGUENRGIENGIUNGIUNGERGNIONEGRIUNERUGNERG";

	//if (nodeType == XML_READER_TYPE_ELEMENT && nodeName == xml_line){
		if ( not (s_x1.empty() && s_x2.empty() && s_y1.empty()
			  && s_y2.empty())){
			x1 = atoi(s_x1.c_str());
			x2 = atoi(s_x2.c_str());
			y1 = atoi(s_y1.c_str());
			y2 = atoi(s_y2.c_str());
			lshape = new LineShape(owner, x1, y1, x2, y2);
		}
	//}
	return lshape;

}

}
