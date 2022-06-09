//
// Created by raymond-du on 2022/5/17.
//

#include "XmlBase.h"

bool XmlBase::s_isFormating = false;

std::vector<XMLEntity> XmlBase::s_entitys = {
        { "&amp;",  5, '&' },
        { "&lt;",   4, '<' },
        { "&gt;",   4, '>' },
        { "&quot;", 6, '\"' },
        { "&apos;", 6, '\'' },
};

int XmlBase::s_errno = 0;

XmlBase::XmlBase() : m_data(nullptr), m_lenth(0) {}

const char * XmlBase::getRawData() {
    return m_data;
}

int XmlBase::getLenth() {
    return m_lenth;
}

std::ostream& operator<< (std::ostream& os, XmlBase *base) {
    return base->dump(os);
}

void XmlBase::setFormating(bool v) {
    XmlBase::s_isFormating = v;
}

bool XmlBase::getFormating() {
    return XmlBase::s_isFormating;
}

bool XmlBase::isWhiteSpace(char c) {
    if (isspace(c) || c == '\r' || c == '\n')
        return true;
    return false;
}

const char * XmlBase::stepWhiteSpace(const char *data) {
    while (*data != '\0') {
        if (isWhiteSpace(*data)) {
            ++data;
        } else {
            break;
        }
    }
    return data;
}

std::istream& XmlBase::stepWhiteSpace(std::istream &is) {
    while (is.good()) {
        char c = is.peek();
        if (isWhiteSpace(c)) {
            is.get();
        } else {
            break;
        }
    }
    return is;
}

int XmlBase::getToWhiteSpace(const char *data, int offset, std::string *out) {
    while (data[offset] != '\0') {
        char c = data[offset];
        if (isWhiteSpace(c)) {
            break;
        } else {
            out->push_back(c);
        }
    }
    return offset;
}

std::istream& XmlBase::getToWhiteSpace(std::istream &is, std::string *out) {
    while (is.good()) {
        char c = is.peek();
        if (isWhiteSpace(c)) {
            break;
        } else {
            out->push_back(c);
        }
        is.get();
    }
    return is;
}

bool XmlBase::stringMatch(const char *src, const char *tag, bool ignoreCase) {
    if (ignoreCase) {
        while (*src && *tag && tolower(*src) == tolower(*tag)) {
            ++src;
            ++tag;
        }
        if (*tag == 0) {
            return true;
        }
    } else {
        while (*src && *tag && *src == *tag) {
            ++src;
            ++tag;
        }
        if (*tag == 0) {
            return true;
        }
    }
    return false;
}

bool XmlBase::stlStringICaseEqual(const std::string &s1, const std::string s2) {
    return s1.size() == s2.size() && std::equal(s1.begin(), s1.end(), s2.begin(), s2.end(), [](char a, char b) {
        return std::tolower(a) == std::tolower(b);
    });
}

std::string XmlBase::getTabsStr(size_t count) {
    if (!s_isFormating)
        return "";
    std::string res;
    while (count--) {
        res.push_back('\t');
    }
    return res;
}
