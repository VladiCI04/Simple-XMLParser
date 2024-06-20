#include <fstream>
#include "HelperFunctions.h"

size_t HelperFunctions::getFileSize(std::ifstream& in)
{
    size_t currentPos = in.tellg();
    in.seekg(0, std::ios::end);

    size_t size = in.tellg();
    in.seekg(currentPos);

    return size;
}

unsigned HelperFunctions::parseNumber(const String number) {
    unsigned parsedNumber = 0;
    unsigned index = 0;

    while (index < number.getLength()) {
        parsedNumber *= 10;
        parsedNumber += number[index - '0'];
        index++;
    }

    return parsedNumber;
}

void HelperFunctions::printParent(const Parent curParent)
{
    String curParentTag = curParent.getTag();
    String curParentAttribute = curParent.getAttribute();
    String curParentAttributeValue = curParent.getAttributeValue();
    String curParentValue = curParent.getValue();

    std::cout << '<' << curParentTag;
    if (curParentAttribute != nullptr) {
        std::cout << ' ' << curParentAttribute << "=\"" << curParentAttributeValue << "\"";
    }
    if (curParentValue != nullptr) {
        std::cout << '>' << curParentValue << "</" << curParentTag;
    }
    std::cout << '>' << std::endl;
}

void HelperFunctions::printChild(const Child curChild)
{
    String curChildTag = curChild.getTag();
    String curChildAttribute = curChild.getAttribute();
    String curChildAttributeValue = curChild.getAttributeValue();
    String curChildValue = curChild.getValue();

    std::cout << "\t<" << curChildTag;
    if (curChildAttribute != nullptr) {
        std::cout << ' ' << curChildAttribute << "=\"" << curChildAttributeValue << "\"";
    }
    if (curChildValue != nullptr) {
        std::cout << '>' << curChildValue << "</" << curChildTag;
    }
    else {
        std::cout << "></" << curChildTag;
    }
    std::cout << '>' << std::endl;
}

void HelperFunctions::printParentToFile(std::ofstream& out, const Parent curParent)
{
    String curParentTag = curParent.getTag();
    String curParentAttribute = curParent.getAttribute();
    String curParentAttributeValue = curParent.getAttributeValue();
    String curParentValue = curParent.getValue();

    out << '<' << curParentTag;
    if (curParentAttribute != nullptr) {
        out << ' ' << curParentAttribute << "=\"" << curParentAttributeValue << "\"";
    }
    if (curParentValue != nullptr) {
        out << '>' << curParentValue << "</" << curParentTag;
    }
    out << '>' << std::endl;
}

void HelperFunctions::printChildToFile(std::ofstream& out, const Child curChild)
{
    String curChildTag = curChild.getTag();
    String curChildAttribute = curChild.getAttribute();
    String curChildAttributeValue = curChild.getAttributeValue();
    String curChildValue = curChild.getValue();

    out << "\t<" << curChildTag;
    if (curChildAttribute != nullptr) {
        out << ' ' << curChildAttribute << "=\"" << curChildAttributeValue << "\"";
    }
    if (curChildValue != nullptr) {
        out << '>' << curChildValue << "</" << curChildTag;
    }
    else {
        out << "></" << curChildTag;
    }
    out << '>' << std::endl;
}