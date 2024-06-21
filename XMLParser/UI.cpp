#include "UI.h"
#include "XPath.h"

void printMenu() {
	std::cout << "----------Menu:----------" << std::endl;
	std::cout << "| 1. Open               |" << std::endl;
	std::cout << "| 2. Close              |" << std::endl;
	std::cout << "| 3. Save               |" << std::endl;
	std::cout << "| 4. SaveAs             |" << std::endl;
	std::cout << "| 5. Help               |" << std::endl;
	std::cout << "| 6. Exit               |" << std::endl;
	std::cout << "-------------------------" << std::endl;
}

void printHelpMenu() {
	std::cout << "-------Help Menu:--------" << std::endl;
	std::cout << "| 1. print		|" << std::endl;
	std::cout << "| 2. select		|" << std::endl;
	std::cout << "| 3. set		|" << std::endl;
	std::cout << "| 4. children		|" << std::endl;
	std::cout << "| 5. child		|" << std::endl;
	std::cout << "| 6. text		|" << std::endl;
	std::cout << "| 7. delete		|" << std::endl;
	std::cout << "| 8. newchild		|" << std::endl;
	std::cout << "| 9. newparent		|" << std::endl;
	std::cout << "| 10. xpath		|" << std::endl;
	std::cout << "-------------------------" << std::endl;
}

void UserInterface::start()
{
	try {
		XMLDocument document;
		XPath path(document);

		std::cout << "----------XMLParser----------" << std::endl;
		String command;
		char filePath[BUFFERSIZE_CONSTANT];
		char fileName[BUFFERSIZE_CONSTANT] { '\0' };
		while (command != "Exit" && command != "exit" && command != "6" && command != "6." && command != "6.exit" && command != "6.Exit" && command != "6exit" && command != "6Exit") {
			printMenu();
			std::cin >> command;

			if (command == "Open" || command == "1" || command == "open" || command == "1.Open" || command == "1.open") {
				if (fileName[0] != '\0') {
					std::cout << std::endl;
					std::cout << "You already opened file and have to close it!" << std::endl; 
					continue;
				}
				std::cout << "Enter File Name: ";
				std::cin >> fileName;
				document.parseXML(fileName);

				std::cout << std::endl;
				std::cout << "File is opened!" << std::endl;
			}
			else if (command == "Close" || command == "2" || command == "close" || command == "2.Close" || command == "2.close") {
				if (fileName[0] == '\0') {
					std::cout << std::endl;
					std::cout << "There isn't file to close!" << std::endl;
					continue;
				}

				document.close();
				fileName[0] = '\0';

				std::cout << std::endl;
				std::cout << "File is closed!" << std::endl;
			}
			else if (command == "Save" || command == "3" || command == "save" || command == "3.Save" || command == "3.save") {
				document.saveToFile(nullptr, fileName);

				std::cout << std::endl;
				std::cout << "File is saved!" << std::endl;
			}
			else if (command == "SaveAs" || command == "4" || command == "saveas" || command == "4.SaveAs" || command == "4.saveas") {
				std::cout << "Enter File Path: ";
				std::cin >> filePath;
				document.saveToFile(filePath, fileName);

				std::cout << std::endl;
				std::cout << "File is saved!" << std::endl;
			}
			else if (command == "Help" || command == "5" || command == "help" || command == "5.Help" || command == "5.help") {
				std::cout << std::endl;
				printHelpMenu();
			}
			else if (command == "Exit" || command == "6" || command == "exit" || command == "6.Exit" || command == "6.exit") {
			}
			else if (command == "print" || command == "Print") {
				std::cout << std::endl;
				document.print();
			}
			else if (command == "select" || command == "Select") {
				std::cout << "Enter id: ";
				String id;
				std::cin >> id;

				std::cout << "Enter key: ";
				String key;
				std::cin >> key;

				std::cout << std::endl;
				document.select(id, key);
			}
			else if (command == "set" || command == "Set") {
				std::cout << "Enter id: ";
				String id;
				std::cin >> id;

				std::cout << "Enter key: ";
				String key;
				std::cin >> key;

				std::cout << "Enter value: ";
				String value;
				std::cin >> value;

				std::cout << std::endl;
				document.set(id, key, value);
				std::cout << "New value is set!" << std::endl;
			}
			else if (command == "children" || command == "Children") {
				std::cout << "Enter id: ";
				String id;
				std::cin >> id;

				std::cout << std::endl;
				document.children(id);
			}
			else if (command == "child" || command == "Child") {
				std::cout << "Enter id: ";
				String id;
				std::cin >> id;

				std::cout << "Enter n: ";
				String n;
				std::cin >> n;

				std::cout << std::endl;
				document.child(id, n);
			}
			else if (command == "text" || command == "Text") {
				std::cout << "Enter id: ";
				String id;
				std::cin >> id;

				std::cout << std::endl;
				document.text(id);
			}
			else if (command == "delete" || command == "Delete") {
				std::cout << "Enter id: ";
				String id;
				std::cin >> id;
				
				std::cout << "Enter key: ";
				String key;
				std::cin >> key;

				std::cout << std::endl;
				document.deleted(id, key);
				std::cout << "Attribute is deleted!" << std::endl;
			}
			else if (command == "newchild" || command == "Newchild" || command == "newChild" || command == "NewChild") {
				std::cout << "Enter Parent id: ";
				String parentId;
				std::cin >> parentId;

				std::cout << "Enter Child key: ";
				String childKey;
				std::cin >> childKey;

				std::cout << "Enter Child type: ";
				String childId;
				std::cin >> childId;

				std::cout << "Enter Child type value: ";
				String childIdValue;
				std::cin >> childIdValue;

				std::cout << "Enter Child value: ";
				String childValue;
				std::cin >> childValue;

				std::cout << std::endl;
				document.newChild(parentId, childKey, childId, childIdValue, childValue);
				std::cout << "Added new child!" << std::endl;
			}
			else if (command == "newparent" || command == "Newparent" || command == "newParent" || command == "NewParent") {
				std::cout << "Enter Parent key: ";
				String parentKey;
				std::cin >> parentKey;

				std::cout << "Enter Parent id: ";
				String parentIdValue;
				std::cin >> parentIdValue;

				std::cout << std::endl;
				document.newParent(parentKey, "id", parentIdValue);
				std::cout << "Added new parent!" << std::endl;
				}
			else if (command == "xpath" || command == "Xpath" || command == "xPath" || command == "XPath") {
				std::cout << "Enter query: ";

				String query;
				std::cin >> query;

				std::cout << std::endl;
				path.execute(query);
			}
			else {
				std::cout << std::endl;
				std::cout << "Invalid command!" << std::endl << std::endl;
			}
		}

		std::cout << std::endl;
		std::cout << "Bye! Bye!" << std::endl << std::endl << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl << std::endl << std::endl;
	}
}