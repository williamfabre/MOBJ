#include "Shape/definition/BoxShape.h"

namespace Netlist
{

BoxShape::BoxShape(Symbol* owner, const Box& box)
	:Shape(owner), box_(box)
{
}

BoxShape::BoxShape(Symbol* owner, int x1 , int y1, int x2, int y2)
	:Shape(owner),box_(x1,y1,x2,y2)
	 // CALL du constructeur de la class de base
{

}

BoxShape::~BoxShape()
{
	return;
}

Box BoxShape::getBoundingBox() const
{
	return box_;
}

void BoxShape::toXml(ostream& stream) const
{
	stream << indent
	<< "<box x1=\"" << box_.getX1() << "\" "
	<< "y1=\"" << box_.getY1() << "\" "
	<< "x2=\"" << box_.getX2() << "\" "
	<< "y2=\"" << box_.getY2()
	<< "\" />" << endl;
}

BoxShape* BoxShape::fromXml(Symbol* owner, xmlTextReaderPtr reader)
{
	BoxShape* bshape = NULL;

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
	const xmlChar* xml_bst;
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
	xml_bst = (const xmlChar*)"box";

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
	const xmlChar* nodeTag  = xmlTextReaderConstString(reader, (const xmlChar*)"box");

	if (nodeName == nodeTag){
		if ( not (s_x1.empty() && s_x2.empty() && s_y1.empty()
			  && s_y2.empty())){
			x1 = atoi(s_x1.c_str());
			x2 = atoi(s_x2.c_str());
			y1 = atoi(s_y1.c_str());
			y2 = atoi(s_y2.c_str());
			bshape = new BoxShape(owner, x1, y1, x2, y2);
		}
		return bshape;
	}
	return bshape;
}

}
