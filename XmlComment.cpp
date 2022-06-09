//
// Created by raymond-du on 2022/5/19.
//

#include "XmlComment.h"
#include <sstream>

XmlComment::XmlComment(XmlNode *parent, size_t layer) :
                        XmlNode(enum_xml_type_comment, parent, layer) {}

std::string XmlComment::toString() {
    std::stringstream ss;
    dump(ss);
    return ss.str();
}

std::ostream &XmlComment::dump(std::ostream &os) {
    os << getTabsStr(m_layer);
    if (!m_comment.empty()) {
        os << "<!--" << m_comment << "-->";
    }
    return os;
}

const char *XmlComment::parse(const char *data) {
    const char *pData = data;
    if (!stringMatch(pData, "<!--", false)) {
        s_errno = 10;
        return nullptr;
    }
    pData += sizeof("<!--");
    while (*pData != '\0') {
        if (stringMatch(pData, "-->", false)) {
            pData += 3;
            break;
        }
        m_comment.push_back(*pData);
        ++pData;
    }
    m_data = data;
    m_lenth = pData - data;
    return pData;
}