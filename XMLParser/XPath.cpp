#include "XPath.h"

static int counter = 0;

void printQuery(Queue<String> queryResult) {
	counter = 0;
	while (!queryResult.isEmpty()) {
		counter++;
		std::cout << queryResult.peek() << std::endl;
		queryResult.pop();
	}

	std::cout << "-------------------------------------------" << std::endl;
}

void printQuery(String queryResult) {
	counter = 1;
	std::cout << queryResult << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
}

XPath::XPath(XMLDocument& document) : curDocument(document)
{
	
}

void XPath::execute(const String query)
{
	int separateListIndex = query.find('/', query.getLength());
	int separateIndexIndex = query.find('[', query.getLength());
	int separateIdIndex = query.find('@', query.getLength());
	int separateEqualIndex = query.find('=', query.getLength());

	if (separateListIndex > -1 && separateIndexIndex == -1 && separateIdIndex == -1 && separateEqualIndex == -1) {
		printQuery(curDocument/query);
	}
	else if (separateIndexIndex > -1 && separateIdIndex == -1 && separateEqualIndex == -1) {
		printQuery(curDocument[query]);
	}
	else if (separateIdIndex > -1) {
		printQuery(curDocument.id(query));
	}
	else if (separateEqualIndex > -1) {
		printQuery(curDocument=query);
	}
	else {
		throw std::exception("Invalid query!");
	}
}

unsigned XPath::count()
{
	return counter;
}