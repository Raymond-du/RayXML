//
// Created by raymond-du on 2022/5/19.
//

#ifndef XML_XMLCOMMENT_H
#define XML_XMLCOMMENT_H

#include "XmlNode.h"

class XmlComment : public XmlNode {

public:
    explicit XmlComment(XmlNode *parent, size_t layer);

public:
    std::string toString() override;
    
    const char * parse(const char *data) override;

    std::ostream& dump(std::ostream& os) override;

    inline const std::string& getComment() {
        return m_comment;
    }

private:
    std::string m_comment;
};

#endif //XML_XMLCOMMENT_H
