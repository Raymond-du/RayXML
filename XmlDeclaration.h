//
// Created by raymond-du on 2022/5/17.
//

#ifndef XML_XMLDECLARATION_H
#define XML_XMLDECLARATION_H

#include "XmlNode.h"
//xml的声明
class XmlDeclaration : public XmlNode {

public:
    XmlDeclaration();

    const char * parse(const char *data) override;

    virtual std::string toString() override;

    virtual std::ostream& dump(std::ostream &os) override;

private:
    bool __check_version(const std::string &str);

    bool __check_encoding(const std::string &str);

    bool __check_standalone(const std::string &str);

private:
    std::string m_version;
    std::string m_encoding;
    std::string m_standalone; //默认值为yes 表示没有约束文件 no表示存在约束文件
};


#endif //XML_XMLDECLARATION_H
