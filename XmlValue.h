//
// Created by raymond-du on 2022/5/21.
//

#ifndef XML_XMLVALUE_H
#define XML_XMLVALUE_H

#include "XmlNode.h"

class XmlValue : public XmlNode {

public:
    XmlValue(XmlNode *parent, size_t layer);

    std::string toString() ;

    std::ostream& dump(std::ostream &os) override;

    const char * parse(const char *data) override;

private:
    const char * __parse_xml_entity(const char *data, std::string *out);

private:
    std::string         m_value;

};


#endif //XML_XMLVALUE_H
