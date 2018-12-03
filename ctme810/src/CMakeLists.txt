# -*- explicit-buffer-name: "CMakeLists.txt<M1-MOBJ/8-10>" -*-
# To display executed commands, use:
#     > cmake -DCMAKE_VERBOSE_MAKEFILE:STRING=YES ../src

cmake_minimum_required(VERSION 2.8.0)
project(SCHEMATIC)

set (CMAKE_CXX_FLAGS "-Wall -g" CACHE STRING "C++ Compiler Release options." FORCE)
set (CMAKE_INSTALL_PREFIX "../install" )

find_package(LibXml2 REQUIRED)
find_package(Qt4     REQUIRED)
include(${QT_USE_FILE})

include_directories( ${SCHEMATIC_SOURCE_DIR} ${LIBXML2_INCLUDE_DIR})

set( includes
	Indentation/Indentation.h
	Xml/XmlUtil.h
	Point/Point.h
	Box/Box.h
	Term/Term.h
	Net/Net.h
	Instance/Instance.h
	Node/Node.h
	Line/Line.h

	Shape/Shape.h

	Shape/definition/LineShape.h
	Shape/definition/EllipseShape.h
	Shape/definition/ArcShape.h
	Shape/definition/TermShape.h
	Shape/definition/BoxShape.h

	Symbol/Symbol.h
	Cell/Cell.h
	)

set( mocIncludes
	SaveCellDialog/SaveCellDialog.h
	CellWidget/CellWidget.h
	CellViewer/CellViewer.h
	)

set( cpps
	Indentation/Indentation.cpp
	Xml/XmlUtil.cpp
	Point/Point.cpp
	Box/Box.cpp
	Term/Term.cpp
	Net/Net.cpp
	Instance/Instance.cpp
	Node/Node.cpp
	Line/Line.cpp
	Shape/Shape.cpp
	Symbol/Symbol.cpp
	Cell/Cell.cpp

	Shape/implementation/LineShape.cpp
	Shape/implementation/EllipseShape.cpp
	Shape/implementation/ArcShape.cpp
	Shape/implementation/BoxShape.cpp
	Shape/implementation/TermShape.cpp


	SaveCellDialog/SaveCellDialog.cpp
	CellWidget/CellWidget.cpp
	CellViewer/CellViewer.cpp

	Main/Main.cpp
	)

qt4_wrap_cpp( mocCpps      ${mocIncludes} )

add_executable( tme810       ${cpps} ${mocCpps} )
target_link_libraries( tme810       ${QT_LIBRARIES} ${LIBXML2_LIBRARIES} )
install( TARGETS      tme810                      DESTINATION bin )
install( FILES        ${includes} ${mocIncludes}  DESTINATION include )
