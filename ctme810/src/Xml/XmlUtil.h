#ifndef NETLIST_XMLUTIL_H
#define NETLIST_XMLUTIL_H

#include <libxml/xmlreader.h>
#include <string>

namespace Netlist {

std::string xmlCharToString(xmlChar*);

// Attention au type def on manipule un pointeur.
// Typedef xmlTextReader * xmlTextReaderPtr

bool xmlGetIntAttribute(xmlTextReaderPtr,
			const std::string& attribute,
			int& value);

// dans la Cell
bool isEnd(xmlTextReaderPtr reader);

// dans la Cell
bool isElement(xmlTextReaderPtr reader);

}  // Netlist namespace.

#endif  // NETLIST_XMLUTIL_H
