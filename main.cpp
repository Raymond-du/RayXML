#include <iostream>
#include "XmlDocument.h"

bool stlStringICaseEqual(const std::string &s1, const std::string s2) {
    return s1.size() == s2.size() && std::equal(s1.begin(), s1.end(), s2.begin(), s2.end(), [](char a, char b) {
        return std::tolower(a) == std::tolower(b);
    });
}

class Test {
public:
    virtual std::string tostring() {
        return "bash";
    }

    friend std::ostream& operator <<(std::ostream& os, Test* t) {
        os << t->tostring() << std::endl;
        return os;
    }
    int a = 10;
    int b = 11;
};

class Test2 : public Test {
public:
    std::string tostring() override {
        return "bash2";
    }
};


int main() {
//    const char *data = R"(<note>
//                        <to name="dsa">Tove<!--dsd--></to>
//                        <!--dsadsa-->
//                        <from>Jani&quot;</from>
//                        <heading>Reminder</heading>
//                        <body>Don't forget me this weekend!</body>
//                        </note>)";
//    XmlElement elem(nullptr, 0);
//    auto pData = elem.parse(data);
//    std::cout << elem.toString();
//    return 0;

//    Test2 t;
//    std::cout << &t;

    XmlDocument document;
    XmlBase::setFormating(true);
    document.loadFile("/home/raymond-du/test.xml");
    document.outputContext([](const std::string& str, bool end){
       std::cout << str;
    });
    return 0;
}
