//
// Created by raymond-du on 2022/5/17.
//

#include <cstring>
#include <sstream>
#include "XmlDeclaration.h"
#include "XmlAttribute.h"

std::string XmlDeclaration::toString() {
    std::stringstream ss;
    dump(ss);
    return ss.str();
}

std::ostream& XmlDeclaration::dump(std::ostream &os) {
    if (m_version.empty()) {
        return os;
    }
    os << "<?xml version=\"" << m_version << "\"";
    if (!m_encoding.empty()) {
        os << " encoding=\"" << m_encoding << "\"";
    }
    if (!m_standalone.empty()) {
        os << " standalone=\""<< m_standalone << "\"";
    }
    os << "?>" << std::endl;
}

const char * XmlDeclaration::parse(const char *data) {
    const char *pData = data;
    if (!stringMatch(pData, XmlDeclarHeader, true)) {
        goto error;
    }
    pData += std::strlen(XmlDeclarHeader);
    while (*pData != '\0') {
        pData = stepWhiteSpace(pData);
        if (stringMatch(pData, "?>", false)) {
            pData += 2;
            break;
        };

        XmlAttribute attr;
        pData = attr.parse(pData);
        if (pData == nullptr)
            break;

        if (stlStringICaseEqual(attr.getKey(), "version")) {
            if (__check_version(attr.getValue()))
                m_version = attr.getValue();
            else
                goto error;
        } else if (stlStringICaseEqual(attr.getKey(), "encoding")) {
            if (__check_encoding(attr.getValue()))
                m_encoding = attr.getValue();
            else
                goto error;
        } else if (stlStringICaseEqual(attr.getKey(), "standalone")) {
            if (__check_standalone(attr.getValue()))
                m_standalone = attr.getValue();
            else
                goto error;
        } else {
            goto error;
        }
    }
    if (pData == nullptr || *pData == '\0') {
        goto error;
    }
    m_data = data;
    m_lenth = pData - data;

    return pData;
error:
    s_errno = 11;
    return nullptr;
}

bool XmlDeclaration::__check_version(const std::string &str) {
    return (str == "1.0");
}

bool XmlDeclaration::__check_encoding(const std::string &str) {
    return stlStringICaseEqual(str, "utf-8");
}

bool XmlDeclaration::__check_standalone(const std::string &str) {
    return stlStringICaseEqual(str, "yes") || stlStringICaseEqual(str, "no");
}

XmlDeclaration::XmlDeclaration() : XmlNode(enum_xml_type_declaration, nullptr, 0) {

}
