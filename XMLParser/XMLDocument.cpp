#include "XMLDocument.h"
#include <fstream>

size_t getFileSize(std::ifstream& in) {
    size_t currentPos = in.tellg();
    in.seekg(0, std::ios::end);

    size_t size = in.tellg();
    in.seekg(currentPos);

    return size;
}

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
        String attributeValue(line.substr(equalSign + 1, endTag));
        String value(line.substr(endTag + 1, (line.getLength() - 1) - (tag.getLength() + 2)));

        if (tag[0] == '/') { // Closing tag
            Root curRoot;
            curRoot.nodes.push(curParent); 
            roots.push(curRoot);
            Parent parent(nullptr, nullptr, nullptr, nullptr);
            curParent = parent;
        }
        else {
            if (endTag == line.getLength() - 1) {
                Parent parent(tag, attribute, attributeValue, nullptr);
                curParent = parent;
            }
            else {
                if (curParent.getTag() == nullptr) {
                    Parent curChild(tag, attribute, attributeValue, value);
                    Root curRoot;
                    curRoot.nodes.push(curParent);
                    roots.push(curRoot);
                    Parent parent(nullptr, nullptr, nullptr, nullptr);
                    curParent = parent;
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

Queue<String> XMLDocument::operator/(const String query)
{
    int separateSign = query.find(1, '/', query.getLength() - 1);
    String tag1;
    String tag2;
    if (separateSign == -1) {
        tag1 = query;
        tag2 = nullptr;
    }
    else {
        String tag1_1(query.substr2(0, separateSign));
        tag1 = tag1_1;

        String tag2_2(query.substr2(separateSign + 1, query.getLength()));
        tag2 = tag2_2;
    }

    Queue<String> result;
    Queue<Root> rootsCopy = roots;

    while (!rootsCopy.isEmpty()) {
        Parent curRoot = rootsCopy.peek().nodes.peek();

        if (curRoot.getTag() == tag1) {
            Queue<Child> curChildren = curRoot.getChildren();

            while (!curChildren.isEmpty()) {
                if (curChildren.peek().getTag() == tag2 || tag2 == '*') {
                    result.push(curChildren.peek().getValue());
                }

                curChildren.pop();
            }
        }

        rootsCopy.pop();
    }

    return result;
}

String XMLDocument::operator[](const String query)
{
    String query2 = query.substr2(0, query.find('[', query.getLength()));
    String index = query.substr(query.find('[', query.getLength()) + 1, query.find(']', query.getLength()));
    unsigned parsedIndex = 0;
    unsigned i = 0;
    while (i < index.getLength()) {
        parsedIndex *= 10;
        parsedIndex += index[i] - '0';
        i++;
    }

    Queue<String> children = operator/(query2);
    for (unsigned i = 0; i < parsedIndex; i++) {
        children.pop();
    }

    return children.peek();
}

Queue<String> XMLDocument::id(const String query)
{
    String tag = query.substr2(0, query.find('[', query.getLength()));
    
    Queue<String> result;
    Queue<Root> rootsCopy = roots;

    while (!rootsCopy.isEmpty()) {
        Parent curRoot = rootsCopy.peek().nodes.peek();

        if (curRoot.getTag() == tag) {
            result.push(curRoot.getAttributeValue());
        }

        rootsCopy.pop();
    }

    return result;
}

Queue<String> XMLDocument::operator=(const String query)
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

    Queue<String> result2;
    Queue<Root> rootsCopy = roots;

    while (!rootsCopy.isEmpty()) {
        Parent curRoot = rootsCopy.peek().nodes.peek();

        if (curRoot.getTag() == tag) {
            Queue<Child> curChildren = curRoot.getChildren();
            Queue<String> result;

            bool hasValue = false;
            while (!curChildren.isEmpty()) {
                if (curChildren.peek().getTag() == value && hasValue) {
                    result2.push(curChildren.peek().getValue());
                }
                else if (curChildren.peek().getTag() == value) {
                    result.push(curChildren.peek().getValue());
                    hasValue = true;
                }

                if (curChildren.peek().getTag() == attribute && curChildren.peek().getValue() == attributeValue && hasValue) {
                    result2 = result;
                }

                curChildren.pop();
            }
        }

        rootsCopy.pop();
    }

    return result2;
}