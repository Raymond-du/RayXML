cmake_minimum_required(VERSION 3.19)
project(xml)

set(CMAKE_C_FLAGS -w)
set(XML_SRC XmlBase.cpp
        XmlDeclaration.cpp
        XmlNode.cpp
        XmlNode.h
        XmlParse.cpp
        XmlParse.h
        XmlAttribute.cpp
        XmlAttribute.h
        XmlComment.cpp
        XmlComment.h
        XmlElement.cpp
        XmlElement.h
        XmlValue.cpp
        XmlValue.h
        XmlDocument.cpp
        XmlDocument.h)

set(CMAKE_CXX_STANDARD 14)

add_executable(xml main.cpp ${XML_SRC})