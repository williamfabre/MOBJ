# -*- explicit-buffer-name: "CMakeLists.txt<M1-MOBJ/4-5>" -*-
#
# To display executed commands, use:
#     > cmake -DCMAKE_VERBOSE_MAKEFILE:STRING=YES ../src

# Detection de LibXml2.

cmake_minimum_required(VERSION 2.8.0)
project(SCHEMATIC)

find_package(LibXml2)
set (CMAKE_CXX_FLAGS            "-Wall -g" CACHE STRING "C++ Compiler Release options." FORCE)
set (CMAKE_INSTALL_PREFIX       "../install" )


include_directories( ${SCHEMATIC_SOURCE_DIR} ${LIBXML2_INCLUDE_DIR})

set( includes
	Term/Term.h
	Net/Net.h
	Instance/Instance.h
	Point/Point.h
	Indentation/Indentation.h
	Node/Node.h
	Cell/Cell.h
	Xml/XmlUtil.h
	Box/Box.h
	Line/Line.h

	Shape/Shape.h

	Shape/definition/LineShape.h
	Shape/definition/EllipseShape.h
	Shape/definition/ArcShape.h
	Shape/definition/TermShape.h
	Shape/definition/BoxShape.h

	Symbol/Symbol.h
	)

set( cpps
	Indentation/Indentation.cpp
	Term/Term.cpp
	Net/Net.cpp
	Instance/Instance.cpp
	Point/Point.cpp
	Node/Node.cpp
	Cell/Cell.cpp
	Main/Main.cpp
	Xml/XmlUtil.cpp
	Box/Box.cpp
	Line/Line.cpp
	Symbol/Symbol.cpp

	Shape/Shape.cpp

	Shape/implementation/LineShape.cpp
	Shape/implementation/EllipseShape.cpp
	Shape/implementation/ArcShape.cpp
	Shape/implementation/BoxShape.cpp
	Shape/implementation/TermShape.cpp

	)

add_executable ( tme7 ${cpps} )
target_link_libraries ( tme7 ${LIBXML2_LIBRARIES} )
install ( TARGETS      tme7         DESTINATION bin )
install ( FILES        ${includes}  DESTINATION include )
