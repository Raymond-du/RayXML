//
// Created by raymond-du on 2022/5/17.
//

#ifndef XML_XMLBASE_H
#define XML_XMLBASE_H

#include <string>
#include <ostream>
#include <istream>
#include <vector>

#include "XmlCommon.h"

class XmlBase {

public:
    XmlBase();

    virtual ~XmlBase() = default;

    virtual std::string toString() = 0;

    virtual std::ostream& dump(std::ostream& os) = 0;

    friend std::ostream& operator<< (std::ostream& os, XmlBase *base);

    /**
     * 解析data
     * @param data 字符串
     * @param offset 偏移
     * @return  返回下一段的偏移
     */
    virtual const char * parse(const char *data) = 0;

    const char * getRawData();

    int getLenth();

    static int s_errno;
public:
    static void setFormating(bool v);

    static bool getFormating();

    static bool isWhiteSpace(char c);

    /**
     * 跳过空白处
     */
    static const char * stepWhiteSpace(const char *data);

    static std::istream& stepWhiteSpace(std::istream &is);

     /**
      * 获取当前位置到下一空白位置之前的字段
      * @param out 输出
      * @return 返回空白位置或结束的位置
      */
    static int getToWhiteSpace(const char *data, int offset, std::string *out);

    static std::istream& getToWhiteSpace(std::istream &is, std::string *out);

    static bool stringMatch(const char *src, const char *tag, bool ignoreCase);

    static bool stlStringICaseEqual(const std::string &s1, const std::string s2);

    static std::string getTabsStr(size_t count);

protected:
    static bool s_isFormating; //格式化
    static std::vector<XMLEntity> s_entitys;

protected:
    long            m_lenth;
    const char      *m_data;
};


#endif //XML_XMLBASE_H
