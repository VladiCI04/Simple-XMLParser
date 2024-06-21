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
        parsedNumber += number[index] - '0';
        index++;
    }

    return parsedNumber;
}

void HelperFunctions::printParent(const Parent curParent)
{
    String curParentKey = curParent.getKey();
    String curParentId = curParent.getId();
    String curParentIdValue = curParent.getIdValue();

    std::cout << '<' << curParentKey;
    if (curParentId != nullptr) {
        std::cout << ' ' << curParentId << "=\"" << curParentIdValue << "\"";
    }
    std::cout << '>' << std::endl;
}

void HelperFunctions::printChild(const Child curChild)
{
    String curChildKey = curChild.getKey();
    String curChildId = curChild.getId();
    String curChildIdValue = curChild.getIdValue();
    String curChildValue = curChild.getValue();

    std::cout << "\t<" << curChildKey;
    if (curChildId != nullptr) {
        std::cout << ' ' << curChildId << "=\"" << curChildIdValue << "\"";
    }
    if (curChildValue != nullptr) {
        std::cout << '>' << curChildValue << "</" << curChildKey;
    }
    else {
        std::cout << "></" << curChildKey;
    }
    std::cout << '>' << std::endl;
}

void HelperFunctions::printParentToFile(std::ofstream& out, const Parent curParent)
{
    String curParentKey = curParent.getKey();
    String curParentId = curParent.getId();
    String curParentIdValue = curParent.getIdValue();

    out << '<' << curParentKey;
    if (curParentId != nullptr) {
        out << ' ' << curParentId << "=\"" << curParentIdValue << "\"";
    }
    out << '>' << std::endl;
}

void HelperFunctions::printChildToFile(std::ofstream& out, const Child curChild)
{
    String curChildKey = curChild.getKey();
    String curChildId = curChild.getId();
    String curChildIdValue = curChild.getIdValue();
    String curChildValue = curChild.getValue();

    out << "\t<" << curChildKey;
    if (curChildId != nullptr) {
        out << ' ' << curChildId << "=\"" << curChildIdValue << "\"";
    }
    if (curChildValue != nullptr) {
        out << '>' << curChildValue << "</" << curChildKey;
    }
    else {
        out << "></" << curChildKey;
    }
    out << '>' << std::endl;
}