//
// Created by raymond-du on 2022/5/21.
//

#ifndef XML_XMLDOCUMENT_H
#define XML_XMLDOCUMENT_H

#include "XmlDeclaration.h"
#include "XmlNode.h"
#include <functional>

class XmlDocument {

public:
    XmlDocument();

    ~XmlDocument();

    int loadFile(const char *filePath);

    //func的以一个参数的是内容  第二个参数是否结束
    int outputContext(std::function<void(const std::string &, bool)> func);

    //note.name  .表示属性  note->from 表示note的子节点from的值
    std::string getValue(const char *path);

private:
    int __parse_file_context();

private:
    std::string                 m_context;
    XmlDeclaration              *m_declaration;
    std::vector<XmlNode *>      m_nodes;
};


#endif //XML_XMLDOCUMENT_H
