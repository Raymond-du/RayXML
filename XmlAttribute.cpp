//
// Created by raymond-du on 2022/5/18.
//

#include "XmlAttribute.h"

std::string XmlAttribute::toString() {
    std::string res;
    res.append(m_key).append("=").append(m_value);
    return res;
}

std::ostream& XmlAttribute::dump(std::ostream& os) {
    os << m_key << "=\"" << m_value << "\"";
    return os;
}

const char *XmlAttribute::parse(const char *data) {
    const char *pData = data;
    if (*pData != '\0') {
        pData = __prase_key(pData);
        if (pData == nullptr)
            goto error;

        pData = stepWhiteSpace(pData);
        if (*pData != '=')
            goto error;
        ++pData;
        pData = stepWhiteSpace(pData);

        pData = __prase_value(pData);
        if (pData == nullptr)
            goto error;
    }
    m_data = data;
    m_lenth = pData - data;

error:
    s_errno = 6;
    return pData;
}

//开头必须是英文 只能包含 英文大小写 _ 数字
const char* XmlAttribute::__prase_key(const char *data) {
    const char *pData = data;
    std::string key;
    //先判断开头
    if (!isalpha(*pData))
        return nullptr;
    while (isalpha(*pData) || isdigit(*pData) || *pData == '_') {
        key.push_back(*pData);
        ++pData;
    }
    if (!isWhiteSpace(*pData) && *pData != '=')
        return nullptr;

    m_key = key;
    return pData;
}

//必须是双引号包括起来 属性值中不能够直接包含<  & '或”
const char* XmlAttribute::__prase_value(const char *data) {
    const char *pData = data;
    char surround;
    std::string value;
    if (*pData != '"' && *pData != '\'')
        return nullptr;
    surround = *pData;
    ++pData;
    while (*pData != '\0') {
        if (*pData == '<' || *pData == '&') {
            return nullptr;
        } else if (*pData == surround) {
            ++pData;
            break;
        } else {
            value.push_back(*pData);
            ++pData;
        }
    }
    m_value = value;
    return pData;
}

bool XmlAttribute::Compare::operator()(XmlAttribute *attr1, XmlAttribute *attr2) {
    return attr1->m_key == attr2->m_key;
}

