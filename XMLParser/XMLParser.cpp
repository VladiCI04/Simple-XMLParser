#include <iostream>
#include "XPath.h"

int main()
{
    try {
        XMLDocument doc;
        doc.parseXML("example.xml");

        XPath path(doc);

        path.execute("person/address");
        std::cout << path.count() << std::endl << std::endl;

        path.execute("person/address[0]");
        std::cout << path.count() << std::endl << std::endl;

        path.execute("person[@id]");
        std::cout << path.count() << std::endl << std::endl;

        path.execute("person[address=\"Bulgaria\"]/name");
        std::cout << path.count() << std::endl << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}