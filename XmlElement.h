//
// Created by raymond-du on 2022/5/19.
//

#ifndef XML_XMLELEMENT_H
#define XML_XMLELEMENT_H

#include "XmlNode.h"
#include "XmlAttribute.h"
#include <vector>
#include <set>

class XmlElement : public XmlNode {

public:
    explicit XmlElement(XmlElement *parent, size_t layer);

    ~XmlElement() override;

    std::string toString() override;

    std::ostream& dump(std::ostream &os) override;

    const char * parse(const char *data) override;

private:
    const char *__parse_node_name(const char *data, std::string *out, int *status, XmlAttributeSet *attrs);

    const char * __parse_child_node(const char *data, std::vector<XmlNode *> *childs);

    const char * __parse_node_value(const char *data, std::vector<XmlNode *> *value);

    const char * __parse_node_ending(const char *data, const std::string &name);

private:

    std::string             m_nodeName;
    XmlAttributeSet         m_attrs;
    std::vector<XmlNode *>  m_childs;

};


#endif //XML_XMLELEMENT_H
