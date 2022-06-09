//
// Created by raymond-du on 2022/5/18.
//

#ifndef XML_XMLNODE_H
#define XML_XMLNODE_H

#include "XmlBase.h"

class XmlNode : public XmlBase {

protected:
    enum Type {
        enum_xml_type_comment,
        enum_xml_type_declaration,
        enum_xml_type_element,
        enum_xml_type_value,
    };

public:
    XmlNode(Type type, XmlNode *parent, size_t layer);

    inline Type getType() {
        return m_type;
    }

    inline size_t getLayer() {
        return m_layer;
    }

protected:
    size_t          m_layer;
    XmlNode         *m_parentNode;
    Type            m_type;
};


#endif //XML_XMLNODE_H
