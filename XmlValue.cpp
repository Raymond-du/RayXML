//
// Created by raymond-du on 2022/5/21.
//

#include "XmlValue.h"

XmlValue::XmlValue(XmlNode *parent, size_t layer) :
                    XmlNode(enum_xml_type_value, parent, layer) {}

std::string XmlValue::toString() {
    std::string res;
    for (auto c : m_value) {
        switch (c) {
            case '&':
                res.append(s_entitys[0].str);
                break;
            case  '<':
                res.append(s_entitys[1].str);
                break;
            case '>':
                res.append(s_entitys[2].str);
                break;
            default:
                res.push_back(c);
        }
    }
    return res;
}

std::ostream& XmlValue::dump(std::ostream &os) {
    return os << toString();
}

const char * XmlValue::parse(const char *data) {
    const char *pData = data;
    std::string tmp;
    while (*pData != '\0') {
        if (*pData == '&') {
            pData = __parse_xml_entity(pData, &tmp);
            if (pData == nullptr) {
                s_errno = 15;
                return nullptr;
            }
        } else if (*pData == '<') {
            break;
        } else if (isWhiteSpace(*pData)) {
            pData = stepWhiteSpace(pData);
            if (*pData != '<')
                tmp.push_back(' ');
        } else {
            tmp.push_back(*pData);
            ++pData;
        }
    }
    m_value = tmp;
    return pData;
}

const char * XmlValue::__parse_xml_entity(const char *data, std::string *out) {
    const char *pData = nullptr;
    for (auto entity : s_entitys) {
        if (stringMatch(data, entity.str, false)) {
            out->push_back(entity.chr);
            pData = (data + entity.len);
            break;
        }
    }
    return pData;
}