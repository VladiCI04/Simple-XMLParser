#include "XMLDocument.h"
#pragma warning (disable : 4996)

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

        String key(line.substr(openTag + 1, space));
        if (key == nullptr) {
            String key2(line.substr(openTag + 1, endTag));
            key = key2;
        }
        String id(line.substr(space + 1, equalSign));
        String idValue(line.substr(equalSign + 2, endTag - 1));

        if (key[0] == '/') { // Closing tag            
            roots.pushBack(curParent);
            Parent parent(nullptr, nullptr, nullptr);
            curParent = parent;
        }
        else {
            if (endTag == line.getLength() - 1) {
                Parent parent(key, id, idValue);
                curParent = parent;
            }
            else {
                String value(line.substr(endTag + 1, (line.getLength() - 1) - (key.getLength() + 2)));
                Child curChild(key, id, idValue, value);
                curParent.addChild(curChild);
            }
        }

        stream.getline(lineInput, 1024, '\n');
    }
}

void XMLDocument::saveToFile(const char* filePath, const char* fileName)
{
    char file[BUFFERSIZE_CONSTANT * 2];
    if (filePath != nullptr) {
        strcpy(file, filePath);
        strcat(file, "\\");
        strcat(file, fileName);
    }
    else {
        strcpy(file, fileName);
    }

    std::ofstream out(file);
    if (!out.is_open()) {
        throw std::exception("Error while open the file!");
    }

    size_t index = 0;

    while (index < roots.getSize()) {
        Parent curParent = roots[index];

        String curParentTag = curParent.getKey();
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
        std::cout << "</" << curParent.getKey() << '>' << std::endl;

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
        if (curParent.getIdValue() == id) {
            Vector<Child> curChildren = curParent.getChildren();
            size_t index2 = 0;

            while (index2 < curChildren.getSize()) {
                Child curChild = curChildren[index2];

                if (curChild.getKey() == key) {
                    std::cout << curChild.getValue() << std::endl;
                }

                index2++;
            }

            return;
        }

        index++;
    }

    std::cout << "Can't find this attribute in this element!" << std::endl;
}

void XMLDocument::set(const String id, const String key, const String value)
{
    size_t index = 0;

    while (index < roots.getSize()) {
        Parent& curParent = roots[index];

        if (curParent.getIdValue() == id) {
            Vector<Child>& children = curParent.getChildren();
            size_t index2 = 0;

            while (index2 < children.getSize()) {
                Child& curChild = children[index2];

                if (curChild.getKey() == key) {
                    curChild.setValue(value);
                    return;
                }

                index2++;
            }

            std::cout << "Can't find this attribute in this element!" << std::endl;
            return;
        }
    }

    std::cout << "Can't find this attribute in this element!" << std::endl;
}

void XMLDocument::children(const String id)
{
    size_t index = 0;

    while (index < roots.getSize()) {
        Parent curParent = roots[index];

        if (curParent.getIdValue() == id) {
            Vector<Child> curChildren = curParent.getChildren();
            size_t index2 = 0;

            while (index2 < curChildren.getSize()) {
                Child curChild = curChildren[index2];

                std::cout << index2 << ". " << curChild.getKey() << std::endl;

                index2++;
            }

            return;
        }

        index++;
    }

    std::cout << "Can't find this attribute in this element!" << std::endl;
}

void XMLDocument::child(const String id, const String n)
{
    unsigned parsedN = parseNumber(n);
    size_t index = 0;

    while (index < roots.getSize()) {
        Parent& curParent = roots[index];

        if (curParent.getIdValue() == id) {
            Vector<Child>& curChildren = curParent.getChildren();
            Child& curChild = curChildren[n];
            printChild(curChild);

            std::cout << "Enter new tag: ";
            String newKey;
            std::cin >> newKey;
            curChild.setKey(newKey);

            std::cout << "Enter new value: ";
            String newValue;
            std::cin >> newValue;
            curChild.setValue(newValue);

            return;
        }

        index++;
    }

    std::cout << "Can't find this attribute in this element!" << std::endl;
}

void XMLDocument::text(const String id)
{
    size_t index = 0;

    while (index < roots.getSize()) {
        Parent& curParent = roots[index];

        if (curParent.getIdValue() == id) {  
            Vector<Child>& curChildren = curParent.getChildren();
            size_t index2 = 0;

            while (index2 < curChildren.getSize()) {
                Child& curChild = curChildren[index2];

                printChild(curChild);
                std::cout << "Enter new value: ";
                String newValue;
                std::cin >> newValue;
                curChild.setValue(newValue);

                index2++;
            }

            return;
        }

        index++;
    }

    std::cout << "Can't find this attribute in this element!" << std::endl;
}

void XMLDocument::deleted(const String id, const String key)
{
    size_t index = 0;

    while (index < roots.getSize()) {
        Parent& curParent = roots[index];
        if (curParent.getIdValue() == id) {
            Vector<Child>& curChildren = curParent.getChildren();
            size_t index2 = 0;

            while (index2 < curChildren.getSize()) {
                Child& curChild = curChildren[index2];

                if (curChild.getKey() == key) {
                    curChildren.popAt(index2);
                    return;
                }

                index2++;
            }

            std::cout << "Can't find this attribute in this element!" << std::endl;
            return;
        }

        index++;
    }

    std::cout << "Can't find this attribute in this element!" << std::endl;
}

void XMLDocument::newChild(const String id, const String key)
{
    size_t index = 0;

    while (index < roots.getSize()) {
        Parent& curParent = roots[index];
        if (curParent.getIdValue() == id) {
            Vector<Child>& curChildren = curParent.getChildren();
            Child curChild(key, nullptr, nullptr, nullptr);
            curChildren.pushBack(curChild);
            return;
        }

        index++;
    }

    std::cout << "Can't find this element!" << std::endl;
}

Vector<String> XMLDocument::operator/(const String query)
{
    int separateSign = query.find(1, '/', query.getLength() - 1);

    String key1(query.substr2(0, separateSign));
    String key2(query.substr2(separateSign + 1, query.getLength()));

    Vector<String> result;
    size_t index = 0;

    while (index < roots.getSize()) {
        Parent curRoot = roots[index];

        if (curRoot.getKey() == key1) {
            Vector<Child> curChildren = curRoot.getChildren();
            size_t index2 = 0;

            while (index2 < curChildren.getSize()) {
                if (curChildren[index2].getKey() == key2 || key2 == "*") {
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

    String key = query.substr2(0, separateTag);
    String idValue = query.substr2(separateTag + 2, query.getLength() - 1);
    
    Vector<String> result;
    size_t index = 0;

    while (index < roots.getSize()) {
        Parent curRoot = roots[index];

        if (curRoot.getKey() == key && curRoot.getIdValue() == idValue) {
            Vector<Child> children = curRoot.getChildren();
            size_t index2 = 0;

            while (index2 < children.getSize()) {
                Child curChild = children[index2];

                result.pushBack(curChild.getKey());

                index2++;
            }

            break;
        }

        index++;
    }

    return result;
}

Vector<String> XMLDocument::operator=(const String query)
{
    int parentKeyIndex = query.find('[', query.getLength());
    int childIdIndex = query.find(parentKeyIndex, '=', query.getLength());
    int childIdValueIndex = query.find(childIdIndex, '"', query.getLength());
    int childIdValueIndex2 = query.find(childIdValueIndex + 1, '"', query.getLength());
    int childKeyIndex = query.find(childIdValueIndex, '/', query.getLength());

    String key(query.substr2(0, parentKeyIndex));
    String childId(query.substr(parentKeyIndex + 1, childIdIndex));
    String childIdValue(query.substr(childIdIndex + 2, childIdValueIndex2));
    String childKey(query.substr(childKeyIndex + 1, query.getLength()));

    Vector<String> result;
    size_t index = 0;

    while (index < roots.getSize()) {
        Parent curRoot = roots[index];

        if (curRoot.getKey() == key) {
            Vector<Child> curChildren = curRoot.getChildren();
            Vector<String> result2;
            bool hasValue = false;
            size_t index2 = 0;

            while (index2 < curChildren.getSize()) {
                if (curChildren[index2].getKey() == childKey && hasValue) {
                    result.pushBack(curChildren[index2].getValue());
                }
                else if (curChildren[index2].getKey() == childKey) {
                    result2.pushBack(curChildren[index2].getValue());
                    hasValue = true;
                }

                if (curChildren[index2].getKey() == childId && curChildren[index2].getValue() == childIdValue && hasValue) {
                    result = result2;
                }

                index2++;
            }
        }

        index++;
    }

    return result;
}