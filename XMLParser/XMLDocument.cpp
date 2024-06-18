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
        String attributeValue(line.substr(equalSign + 2, endTag - 1));
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

void XMLDocument::saveToFile(const char* fileName)
{
    std::ofstream out(fileName);
    if (!out.is_open()) {
        throw std::exception("Error while open the file!");
    }

    Queue<Root> rootsCopy = roots;
    while (!rootsCopy.isEmpty()) {
        Parent curParent = rootsCopy.peek().nodes.peek();

        String curParentTag = curParent.getTag();
        String curParentAttribute = curParent.getAttribute();
        String curParentAttributeValue = curParent.getAttributeValue();
        String curParentValue = curParent.getValue();

        out << '<' << curParentTag;
        if (curParentAttribute != nullptr) {
            out << ' ' << curParentAttribute << "=\"" << curParentValue << "\"";
        }
        if (curParentValue != nullptr) {
            out << '>' << curParentValue << "</" << curParentTag;
        }
        out << '>' << std::endl;

        Queue<Child> curChildren = curParent.getChildren();
        while (!curChildren.isEmpty()) {
            Child curChild = curChildren.peek();

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
            out << '>' << std::endl;

            curChildren.pop();
        }
        out << "</" << curParentTag << '>' << std::endl;

        rootsCopy.pop();
    }

    std::cout << "Saved!" << std::endl;
}

void XMLDocument::print()
{
    Queue<Root> rootsCopy = roots;
    while (!rootsCopy.isEmpty()) {
        Parent curParent = rootsCopy.peek().nodes.peek();

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

        Queue<Child> curChildren = curParent.getChildren();
        while (!curChildren.isEmpty()) {
            Child curChild = curChildren.peek();

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
            std::cout << '>' << std::endl;

            curChildren.pop();
        }
        std::cout << "</" << curParentTag << '>' << std::endl;

        rootsCopy.pop();
    }
}

void XMLDocument::close()
{
    roots = Queue<Root>();
}

void XMLDocument::select(String id, String key)
{
    Queue<Root> rootsCopy = roots;
    while (!rootsCopy.isEmpty()) {
        Parent curParent = rootsCopy.peek().nodes.peek();
        if (curParent.getAttribute() == id && curParent.getAttributeValue() == key) {
            std::cout << curParent.getValue() << std::endl;
            return;
        }

        Queue<Child> children = curParent.getChildren();
        while (!children.isEmpty()) {
            Child curChild = children.peek();
            if (curChild.getAttribute() == id && curChild.getAttributeValue() == key) {
                std::cout << curChild.getValue() << std::endl;
                return;
            }

            children.pop();
        }

        rootsCopy.pop();
    }
}

void XMLDocument::set(String id, String key, String value)
{
    Queue<Root> rootsCopy = roots;
    Queue<Root> rootsNew;

    while (!rootsCopy.isEmpty()) {
        Parent curParent = rootsCopy.peek().nodes.peek();
        if (curParent.getAttribute() == id && curParent.getAttributeValue() == key) {
            curParent.setValue(value);
        }
        
        Queue<Child> children = curParent.getChildren();
        while (!children.isEmpty()) {
            Child curChild = children.peek();
            if (curChild.getAttribute() == id && curChild.getAttributeValue() == key) {
                curChild.setValue(value);
            }
        
            children.pop();
        }

        Root curRoot;
        curRoot.nodes.push(curParent);
        rootsNew.push(curRoot);

        rootsCopy.pop();
    }

    roots = rootsNew;
}

Queue<String> XMLDocument::operator/(const String query)
{
    int separateSign = query.find(1, '/', query.getLength() - 1);

    String tag1(query.substr2(0, separateSign));
    String tag2(query.substr2(separateSign + 1, query.getLength()));

    Queue<String> result;
    Queue<Root> rootsCopy = roots;

    while (!rootsCopy.isEmpty()) {
        Parent curRoot = rootsCopy.peek().nodes.peek();

        if (curRoot.getTag() == tag1) {
            Queue<Child> curChildren = curRoot.getChildren();

            while (!curChildren.isEmpty()) {
                if (curChildren.peek().getTag() == tag2 || tag2 == "*") {
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
    int separateSign1 = query.find('[', query.getLength());
    int separateSign2 = query.find(separateSign1, ']', query.getLength());

    String query2 = query.substr2(0, separateSign1);
    String index = query.substr(separateSign1 + 1, separateSign2);

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
    int separateTag = query.find('[', query.getLength());

    String tag = query.substr2(0, separateTag);
    String attribute = query.substr2(separateTag + 2, query.getLength() - 1);
    
    Queue<String> result;
    Queue<Root> rootsCopy = roots;

    while (!rootsCopy.isEmpty()) {
        Parent curRoot = rootsCopy.peek().nodes.peek();

        if (curRoot.getTag() == tag && curRoot.getAttribute() == attribute) {
            result.push(curRoot.getAttributeValue());
        }
        else if (curRoot.getTag() == tag) {
            Queue<Child> children = curRoot.getChildren();

            while (!children.isEmpty()) {
                if (children.peek().getAttribute() == attribute) {
                    result.push(children.peek().getAttributeValue());
                }

                children.pop();
            }
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