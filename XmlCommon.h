//
// Created by raymond-du on 2022/5/17.
//

#ifndef XML_XMLCOMMON_H
#define XML_XMLCOMMON_H

constexpr char* const XMLERROR[] = {
        "No error",                 //0
        "Error",                    //1
        "Failed to open file",      //2
        "Error parsing Element.",   //3
        "Failed to read Element name",//4
        "Error reading Element m_value.",//5
        "Error reading Attributes.", //6
        "Error: empty tag.",         //7
        "Error reading end tag.",       //8
        "Error parsing Unknown.",       //9
        "Error parsing Comment.",       //10
        "Error parsing Declaration.",    //11
        "Error document empty.",       //12
        "Error null (0) or unexpected EOF found in input stream.",  //13
        "Error parsing CDATA.",       //14
        "Error parsing context error" //15
};
constexpr size_t XMLERRORCOUNT = sizeof(XMLERROR) / sizeof(void *);
constexpr char XmlDeclarHeader[] = "<?xml ";
constexpr char XmlCommonHeader[] = "<!--";
constexpr char XmlDtdHeader[] = "<!"; //用来验证XML格式的
constexpr char XmlCDataHeader[] = "<![CDATA["; //原始数据,不被xml解析 以]]>结束

//xml 的实体 &quot;等
struct XMLEntity {
    const char      *str; //原字符串
    const size_t    len; //字符串长度
    char            chr; //对应的实体字符
};

static char *XmlStrErrno(int no) {
    if (no < 0 || no >= XMLERRORCOUNT) {
        return "";
    }
    return XMLERROR[no];
}

struct XmlCursor {
    XmlCursor() {
        row = 0;
        col = 0;
    }

    int row;
    int col;
};

#endif //XML_XMLCOMMON_H
