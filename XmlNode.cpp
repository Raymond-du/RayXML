//
// Created by raymond-du on 2022/5/18.
//

#include "XmlNode.h"

XmlNode::XmlNode(Type type, XmlNode *parent, size_t layer) :
                m_type(type),
                m_parentNode(parent),
                m_layer(layer) {

}
