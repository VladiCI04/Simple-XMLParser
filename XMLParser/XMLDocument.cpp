#include "XMLDocument.h"
#include <fstream>

void XMLDocument::parseXML(const char* content)
{
    std::ifstream stream(content);
    if (!stream.is_open()) {
        throw std::exception("Error while reading from file!");
    }

    size_t fileSize = getFileSize(stream);
    if (fileSize == 0) {
        throw std::exception("File is empty!");
    }

    char lineInput[1024];
    stream.getline(lineInput, 1024, '\n');

    Parent curParent;

    while (lineInput[0] != '\0') {
        String line(lineInput);

        int endTag = line.find('>', line.getLength());
        int openTag = line.find('<', endTag);
        int space = line.find(' ', endTag);
        int equalSign = line.find('=', endTag);

        String tag(line.substr(openTag + 1, space));
        if (tag == nullptr) {
            String tag2(line.substr(openTag + 1, endTag));
            tag = tag2;
        }
        String attribute(line.substr(space + 1, equalSign));
        String attributeValue(line.substr(equalSign + 2, endTag - 1));
        String value(line.substr(endTag + 1, (line.getLength() - 1) - (tag.getLength() + 2)));

        if (tag[0] == '/') { // Closing tag            
            roots.pushBack(curParent);
            Parent parent(nullptr, nullptr, nullptr, nullptr);
            curParent = parent;
        }
        else {
            if (endTag == line.getLength() - 1) {
                Parent parent(tag, attribute, attributeValue, nullptr);
                curParent = parent;
            }
            else {
                if (curParent.getValue() != nullptr) {
                    Parent curChild(tag, attribute, attributeValue, value);
                    roots.pushBack(curChild);
                }
                else {
                    Child curChild(tag, attribute, attributeValue, value);
                    curParent.addChild(curChild);
                }
            }
        }

        stream.getline(lineInput, 1024, '\n');
    }
}

void XMLDocument::saveToFile(const char* fileName)
{
    std::ofstream out(fileName);
    if (!out.is_open()) {
        throw std::exception("Error while open the file!");
    }

    size_t index = 0;

    while (index < roots.getSize()) {
        Parent curParent = roots[index];

        String curParentTag = curParent.getTag();
        printParentToFile(out, curParent);

        Vector<Child> curChildren = curParent.getChildren();
        size_t index2 = 0;

        while (index2 < curChildren.getSize()) {
            Child curChild = curChildren[index2];

            printChildToFile(out, curChild);

            index2++;
        }
        out << "</" << curParentTag << '>' << std::endl;

        index++;
    }

    std::cout << "Saved!" << std::endl;
}

void XMLDocument::print()
{
    size_t index = 0;

    while (index < roots.getSize()) {
        Parent curParent = roots[index];
        printParent(curParent);

        Vector<Child> curChildren = curParent.getChildren();
        size_t index2 = 0;

        while (index2 < curChildren.getSize()) {
            Child curChild = curChildren[index2];

            printChild(curChild);

            index2++;
        }
        std::cout << "</" << curParent.getTag() << '>' << std::endl;

        index++;
    }
}

void XMLDocument::close()
{
    roots = Vector<Parent>();
}

void XMLDocument::select(const String id, const String key)
{
    size_t index = 0;

    while (index < roots.getSize()) {
        Parent curParent = roots[index];
        if (curParent.getAttribute() == id && curParent.getAttributeValue() == key) {
            std::cout << curParent.getValue() << std::endl;
            return;
        }

        Vector<Child> curChildren = curParent.getChildren();
        size_t index2 = 0;

        while (index2 < curChildren.getSize()) {
            Child curChild = curChildren[index2];

            if (curChild.getAttribute() == id && curChild.getAttributeValue() == key) {
                std::cout << curChild.getValue() << std::endl;
                return;
            }

            index2++;
        }

        index++;
    }
}

void XMLDocument::set(const String id, const String key, const String value)
{
    size_t index = 0;

    while (index < roots.getSize()) {
        Parent curParent = roots[index];
        if (curParent.getAttribute() == id && curParent.getAttributeValue() == key) {
            curParent.setValue(value);
            return;
        }
        
        Vector<Child> children = curParent.getChildren();
        size_t index2 = 0;

        while (index2 < children.getSize()) {
            Child curChild = children[index2];

            if (curChild.getAttribute() == id && curChild.getAttributeValue() == key) {
                roots[index].getChildren()[index2].setValue(value);
                return;
            }
        
            index2++;
        }

        index++;
    }
}

void XMLDocument::children(const String id)
{
    size_t index = 0;

    while (index < roots.getSize()) {
        Parent curParent = roots[index];
        Vector<Child> curChildren = curParent.getChildren();

        if (curParent.getAttributeValue() == id) {
            size_t index2 = 0;

            while (index2 < curChildren.getSize()) {
                Child curChild = curChildren[index2];

                std::cout << index2 << ". " << curChild.getTag() << std::endl;

                index2++;
            }
        }

        index++;
    }
}

void XMLDocument::child(const String id, const String n)
{
    unsigned parsedN = parseNumber(n);
    size_t index = 0;

    while (index < roots.getSize()) {
        Parent curParent = roots[index];

        if (curParent.getAttributeValue() == id) {
            Vector<Child> curChildren = curParent.getChildren();
            printChild(curChildren[n]);
            return;
        }

        index++;
    }
}

Vector<String> XMLDocument::operator/(const String query)
{
    int separateSign = query.find(1, '/', query.getLength() - 1);

    String tag1(query.substr2(0, separateSign));
    String tag2(query.substr2(separateSign + 1, query.getLength()));

    Vector<String> result;
    size_t index = 0;

    while (index < roots.getSize()) {
        Parent curRoot = roots[index];

        if (curRoot.getTag() == tag1) {
            Vector<Child> curChildren = curRoot.getChildren();
            size_t index2 = 0;

            while (index2 < curChildren.getSize()) {
                if (curChildren[index2].getTag() == tag2 || tag2 == "*") {
                    result.pushBack(curChildren[index2].getValue());
                }

                index2++;
            }
        }

        index++;
    }

    return result;
}

String XMLDocument::operator[](const String query)
{
    int separateSign1 = query.find('[', query.getLength());
    int separateSign2 = query.find(separateSign1, ']', query.getLength());

    String query2 = query.substr2(0, separateSign1);
    String index = query.substr(separateSign1 + 1, separateSign2);

    unsigned parsedIndex = parseNumber(index);

    Vector<String> children = operator/(query2);

    return children[parsedIndex];
}

Vector<String> XMLDocument::id(const String query)
{
    int separateTag = query.find('[', query.getLength());

    String tag = query.substr2(0, separateTag);
    String attribute = query.substr2(separateTag + 2, query.getLength() - 1);
    
    Vector<String> result;
    size_t index = 0;

    while (index < roots.getSize()) {
        Parent curRoot = roots[index];

        if (curRoot.getTag() == tag && curRoot.getAttribute() == attribute) {
            result.pushBack(curRoot.getAttributeValue());
        }
        else if (curRoot.getTag() == tag) {
            Vector<Child> children = curRoot.getChildren();
            size_t index2 = 0;

            while (index2 < children.getSize()) {
                if (children[index2].getAttribute() == attribute) {
                    result.pushBack(children[index2].getAttributeValue());
                }

                index2++;
            }
        }

        index++;
    }

    return result;
}

Vector<String> XMLDocument::operator=(const String query)
{
    int tagIndex = query.find('[', query.getLength());
    int attributeIndex = query.find(tagIndex, '=', query.getLength());
    int attributeValueIndex = query.find(attributeIndex, '"', query.getLength());
    int attributeValueIndex2 = query.find(attributeValueIndex + 1, '"', query.getLength());
    int valueIndex = query.find(attributeValueIndex, '/', query.getLength());

    String tag(query.substr2(0, tagIndex));
    String attribute(query.substr(tagIndex + 1, attributeIndex));
    String attributeValue(query.substr(attributeIndex + 2, attributeValueIndex2));
    String value(query.substr(valueIndex + 1, query.getLength()));

    Vector<String> result;
    size_t index = 0;

    while (index < roots.getSize()) {
        Parent curRoot = roots[index];

        if (curRoot.getTag() == tag) {
            Vector<Child> curChildren = curRoot.getChildren();
            Vector<String> result2;
            bool hasValue = false;
            size_t index2 = 0;

            while (index2 < curChildren.getSize()) {
                if (curChildren[index2].getTag() == value && hasValue) {
                    result.pushBack(curChildren[index2].getValue());
                }
                else if (curChildren[index2].getTag() == value) {
                    result2.pushBack(curChildren[index2].getValue());
                    hasValue = true;
                }

                if (curChildren[index2].getTag() == attribute && curChildren[index2].getValue() == attributeValue && hasValue) {
                    result = result2;
                }

                index2++;
            }
        }

        index++;
    }

    return result;
}