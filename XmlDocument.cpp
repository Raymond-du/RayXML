//
// Created by raymond-du on 2022/5/21.
//

#include "XmlDocument.h"
#include "XmlComment.h"
#include "XmlElement.h"
#include <fstream>

XmlDocument::XmlDocument() : m_declaration(nullptr) {

}

XmlDocument::~XmlDocument() {
    if (m_declaration != nullptr) {
        delete m_declaration;
    }
    for (auto it : m_nodes) {
        delete it;
    }
}

int XmlDocument::loadFile(const char *filePath) {
    std::ifstream ifs(filePath);
    if (!ifs) {
        XmlNode::s_errno = 2;
        return 2;
    }
    ifs.seekg(0, ifs.end);
    int fileLen = ifs.tellg();
    ifs.seekg(0, ifs.beg);

    m_context.resize(fileLen + 1);
    ifs.read(const_cast<char *>(m_context.c_str()), fileLen);

    int ret = 0;
    if (ifs) {
        ret = __parse_file_context();
    } else {
        XmlNode::s_errno = 2;
        ret = 2;
    }

    ifs.close();
    return ret;
}

int XmlDocument::outputContext(std::function<void(const std::string &, bool)> func) {
    if (m_declaration != nullptr) {
        func(m_declaration->toString(), false);
    }
    func("\n", false);
    for (auto it : m_nodes) {
        func(it->toString(), false);
        func("\n", false);
    }
    return 0;
}

std::string XmlDocument::getValue(const char *path) {
    return std::__cxx11::string();
}

int XmlDocument::__parse_file_context() {
    const char *pData = m_context.c_str();
    pData = XmlBase::stepWhiteSpace(pData);
    XmlDeclaration *declaration = nullptr;
    std::vector<XmlNode *> nodes;
    bool hasRoot = false; //xml只能存在一个根

    if (XmlBase::stringMatch(pData, "<?", false)) {
        declaration = new XmlDeclaration();
        pData = declaration->parse(pData);
        if (pData == nullptr) {
            goto error;
        }
    }

    pData = XmlBase::stepWhiteSpace(pData);
    while (*pData != '\0') {
        XmlNode *node = nullptr;
        if (XmlBase::stringMatch(pData, "<!--", false)) {
            node = new XmlComment(nullptr, 0);
            pData = node->parse(pData);
        } else if (*pData == '<' && hasRoot == false) {
            hasRoot = true;
            node = new XmlElement(nullptr, 0);
            pData = node->parse(pData);
        } else {
            XmlBase::s_errno = 8;
            goto error;
        }
        if (pData == nullptr) {
            goto error;
        }
        nodes.push_back(node);
        pData = XmlBase::stepWhiteSpace(pData);
    }
    if (!hasRoot) {
        XmlBase::s_errno = 7;
        goto error;
    }
    m_declaration = declaration;
    m_nodes = std::move(nodes);
    return 0;

error:
    delete declaration;
    for (auto it : nodes) {
        delete it;
    }
    return XmlBase::s_errno;
}

