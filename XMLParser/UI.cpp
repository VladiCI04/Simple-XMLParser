#include "UI.h"
#include "XPath.h"

void printMenu() {
	std::cout << "----------Menu:----------" << std::endl;
	std::cout << "| 1. Open               |" << std::endl;
	std::cout << "| 2. Close              |" << std::endl;
	std::cout << "| 3. Save               |" << std::endl;
	std::cout << "| 4. Save As            |" << std::endl;
	std::cout << "| 5. Help               |" << std::endl;
	std::cout << "| 6. Exit               |" << std::endl;
	std::cout << "-------------------------" << std::endl;
}

void printHelpMenu() {
	std::cout << "----------Help Menu:-----------" << std::endl;
	std::cout << "| 1. print		      |" << std::endl;
	std::cout << "| 2. select <id> <key>        |" << std::endl;
	std::cout << "| 3. set <id> <key> <value>   |" << std::endl;
	std::cout << "| 4. children <id>            |" << std::endl;
	std::cout << "| 5. child <id> <n>           |" << std::endl;
	std::cout << "| 6. text <id>                |" << std::endl;
	std::cout << "| 7. delete <id> <key>        |" << std::endl;
	std::cout << "| 8. newchild <id>            |" << std::endl;
	std::cout << "| 9. xpath <XPath>            |" << std::endl;
	std::cout << "-------------------------------" << std::endl;
}

void UserInterface::start()
{
	try {
		XMLDocument document;
		XPath path(document);

		std::cout << "----------XMLParser----------" << std::endl;
		String command;
		char fileName[100];
		while (command != "Exit") {
			printMenu();
			std::cin >> command;

			if (command == "Open" || command == "1" || command == "open" || command == "1. Open" || command == "1. open" || command == "1.Open" || command == "1.open") {
				std::cout << "Enter File Name: ";
				std::cin >> fileName;
				document.parseXML(fileName);
				std::cout << "File is opened!" << std::endl;
				continue;
			}
			else if (command == "Close" || command == "2" || command == "close" || command == "2. Close" || command == "2. close" || command == "2.Close" || command == "2.close") {
				document.close();
				std::cout << "File is closed!" << std::endl;
				continue;
			}
			else if (command == "Save" || command == "3" || command == "save" || command == "3. Save" || command == "3. save" || command == "3.Save" || command == "3.save") {
				document.saveToFile(fileName);
				std::cout << "File is saved!" << std::endl;
				continue;
			}
			else if (command == "Save As" || command == "4" || command == "save as" || command == "4. Save As" || command == "4. save as" || command == "4.SaveAs" || command == "4.saveas") {
				std::cout << "Enter File Name: ";
				std::cin >> fileName;
				document.saveToFile(fileName);
				std::cout << "File is saved!" << std::endl;
				continue;
			}
			else if (command == "Help" || command == "5" || command == "help" || command == "5. Help" || command == "5. help" || command == "5.Help" || command == "5.help") {
				printHelpMenu();
				continue;
			}
			else if (command == "Exit" || command == "6" || command == "exit" || command == "6. Exit" || command == "6. exit" || command == "6.Exit" || command == "6.exit") {
				continue;
			}
			else if (command == "print" || command == "Print") {
				document.print();
				continue;
			}

			int spaceSeparator = command.find(' ', command.getLength());
			String command2 = command.substr2(0, spaceSeparator);
			if (command2 == "select" || command2 == "Select") {
				int spaceSeparator2 = command.find(spaceSeparator + 1, ' ', command.getLength());
				int spaceSeparator3 = command.find(spaceSeparator2 + 1, ' ', command.getLength());

				String id = command.substr2(spaceSeparator, spaceSeparator2);
				String key = command.substr2(spaceSeparator2, spaceSeparator3);
				String value = command.substr2(spaceSeparator3, command.getLength());

				document.set(id, key, value);
			}
			else if (command2 == "set" || command2 == "Set") {
				int spaceSeparator2 = command.find(spaceSeparator + 1, ' ', command.getLength());
				String id = command.substr2(spaceSeparator, spaceSeparator2);
				String key = command.substr2(spaceSeparator2, command.getLength());
			}
			else if (command2 == "children" || command2 == "Children") {

			}
			else if (command2 == "child" || command2 == "Child") {

			}
			else if (command2 == "text" || command2 == "Text") {

			}
			else if (command2 == "delete" || command2 == "Delete") {

			}
			else if (command2 == "newchild" || command2 == "Newchild" || command2 == "newChild" || command2 == "NewChild") {

			}
			else if (command2 == "xpath" || command2 == "Xpath" || command2 == "xPath" || command2 == "XPath") {
				String query = command.substr2(spaceSeparator, command.getLength());

				path.execute(query);
			}
			else {
				std::cout << "Invalid command!" << std::endl << std::endl;
			}
		}

		std::cout << "Bye! Bye!" << std::endl << std::endl << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl << std::endl << std::endl;
	}
}