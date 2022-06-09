//
// Created by raymond-du on 2022/5/18.
//

#ifndef XML_XMLATTRIBUTE_H
#define XML_XMLATTRIBUTE_H

#include "XmlBase.h"
#include <set>
#include <string>
/**
 * 属性
 */
class XmlAttribute : public XmlBase {

public:
    std::string toString() override;

    const char* parse(const char *data) override;

    std::ostream& dump(std::ostream& os) override;

    struct Compare {
        bool operator()(XmlAttribute *attr1, XmlAttribute *attr2);
    };

    inline const std::string& getKey() {
        return m_key;
    }

    inline const std::string& getValue() {
        return m_value;
    }
private:
    const char* __prase_key(const char *data);

    const char* __prase_value(const char *data);

private:
    std::string     m_key;
    std::string     m_value;
};

using XmlAttributeSet = std::set<XmlAttribute *, XmlAttribute::Compare>;

#endif //XML_XMLATTRIBUTE_H
