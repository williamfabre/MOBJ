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
	Indentation/Indentation.h
	Term/Term.h
	Net/Net.h
	Instance/Instance.h
	Point/Point.h
	Node/Node.h
	Cell/Cell.h
	Xml/XmlUtil.h
	Nox/Box.h
	Line/Line.h

	Shape/Shape.h
	Shape/definition/ArcShape.h
	Shape/definition/BoxShape.h
	Shape/definition/EllipseShape.h
	Shape/definition/LineShape.h
	Shape/definition/TermShape.h

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

	Shape/Shape.cpp
	Shape/implementation/ArcShape.cpp
	Shape/implementation/BoxShape.cpp
	Shape/implementation/EllipseShape.cpp
	Shape/implementation/LineShape.cpp
	Shape/implementation/TermShape.cpp

	Symbol/Symbol.cpp
	)

add_executable ( tme7 ${cpps} )
target_link_libraries ( tme7 ${LIBXML2_LIBRARIES} )
install ( TARGETS      tme7         DESTINATION bin )
install ( FILES        ${includes}  DESTINATION include )
