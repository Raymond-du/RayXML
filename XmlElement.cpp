//
// Created by raymond-du on 2022/5/19.
//

#include <sstream>
#include "XmlElement.h"
#include "XmlComment.h"
#include "XmlValue.h"
#include "XmlAttribute.h"

XmlElement::XmlElement(XmlElement *parent, size_t layer) :
                        XmlNode(enum_xml_type_element, parent, layer) {}

std::string XmlElement::toString() {
    std::stringstream ss;
    dump(ss);
    return ss.str();
}

std::ostream& XmlElement::dump(std::ostream &os) {
    os << getTabsStr(m_layer) << "<" << m_nodeName;
    for (auto attr : m_attrs) {
        os << " ";
        os << attr;
    }
    os << ">";

    if (m_childs.size() == 1 && m_childs[0]->getType() == enum_xml_type_value) {
        os << m_childs[0];
    } else if (!m_childs.empty()){
        os << "\n";
        for (auto child : m_childs) {
            os << child << "\n";
        }
        os << getTabsStr(m_layer);
    }
    os << "</" << m_nodeName << ">";
    return os;
}

XmlElement::~XmlElement() {
    for (auto child : m_childs) {
        delete child;
    }
    for (auto attr : m_attrs) {
        delete attr;
    }
}

static void realse_xml_attr_set(XmlAttributeSet &attrs) {
    for (auto attr : attrs) {
        delete attr;
    }
}

static void realse_xml_node_vec(std::vector<XmlNode *> &nodes) {
    for (auto node : nodes) {
        delete node;
    }
}

#define ErrorRet(no) \
                s_errno = no;       \
                return nullptr

const char *XmlElement::parse(const char *data) {
    const char *pData = data;

    std::string             nodeName;
    std::string             value;
    XmlAttributeSet         attrs;
    std::vector<XmlNode *>  childs;

    int status = 0;
    pData = __parse_node_name(pData, &nodeName, &status, &attrs);
    if (pData == nullptr)  {
        s_errno = 4;
        goto error;
    }
    pData = stepWhiteSpace(pData);
    while (*pData != '\0' && status) {
        if (stringMatch(pData, "</", false)) { //</结束>
            if (nullptr == (pData = __parse_node_ending(pData, nodeName)))
                goto error;
            break;
        } else if (*pData == '<') {
            pData = __parse_child_node(pData, &childs);
        } else {
            pData = __parse_node_value(pData, &childs);
        }
        if (pData == nullptr) {
            goto error;
        }
        pData = stepWhiteSpace(pData);
    }
    if (pData == nullptr) {
        s_errno = 3;
        goto error;
    }
    m_nodeName  = std::move(nodeName);
    m_attrs     = std::move(attrs);
    m_childs    = std::move(childs);

    m_data = pData;
    m_lenth = pData - data;
    return pData;

error:
    realse_xml_attr_set(attrs);
    realse_xml_node_vec(childs);
    return nullptr;
}
#undef ErrorRet

//字母、数字、中横线、下划线、点  //这个地方需要返回节点是否结束
const char * XmlElement::__parse_node_name(const char *data, std::string *out, int *status, XmlAttributeSet *attrs) {
    const char *pData = data;
    if (*pData != '<') {
        return nullptr;
    }
    ++pData;
    //开头必须是字母或下划线
    if (!isalpha(*pData) && *pData != '_') {
        return nullptr;
    }
    while (isalpha(*pData) || isdigit(*pData) || *pData == '-' || *pData == '_' || *pData == '.') {
        out->push_back(*pData);
        pData++;
    }
    pData = stepWhiteSpace(pData);

    while (isalpha(*pData)) {
        auto *attr = new XmlAttribute;
        pData = attr->parse(pData);
        if (pData == nullptr)
            break;
        auto item = attrs->find(attr);
        if (item != attrs->end()) {
            delete attr;
            return nullptr;
        }
        attrs->insert(attr);
    }
    pData = stepWhiteSpace(pData);
    if (*pData == '>') {
        *status = 1;
        pData++;
    } else if (stringMatch(pData, "/>", false)) {
        *status = 0;
        pData += 2;
    } else {
        return nullptr;
    }
    return pData;
}

const char * XmlElement::__parse_child_node(const char *data, std::vector<XmlNode *> *childs) {
    const char *pData = data;
    XmlNode *node = nullptr;
    if (stringMatch(pData, "<!--", false)) {
        node = new XmlComment(this, m_layer + 1);
    } else {
        node = new XmlElement(this, m_layer + 1);
    }
    pData = node->parse(pData);
    if (pData == nullptr) {
        delete node;
        return nullptr;
    }
    childs->push_back(node);
    return pData;
}

const char *XmlElement::__parse_node_value(const char *data, std::vector<XmlNode *> *value) {
    const char *pData = data;
    XmlNode *node = new XmlValue(this, m_layer + 1);

    pData = node->parse(pData);
    if (pData == nullptr) {
        delete node;
        return nullptr;
    }
    value->push_back(node);
    return pData;
}

const char * XmlElement::__parse_node_ending(const char *data, const std::string &name) {
    const char *pData = data;
    if (!stringMatch(pData, "</", false)) {
        return nullptr;
    }
    pData += 2;

    if (!stringMatch(pData, name.c_str(), false)) {
        return nullptr;
    }
    pData += name.length();
    pData = stepWhiteSpace(pData);
    if (!stringMatch(pData, ">", false)) {
        return nullptr;
    }
    pData += 1;
    return pData;
}
