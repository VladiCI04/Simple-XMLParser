#include "XPath.h"

static int counter = 0;

void printQuery(Vector<String> queryResult) {
	counter = 0;
	size_t index = 0;

	while (index < queryResult.getSize()) {
		counter++;
		std::cout << queryResult[index] << std::endl;
		index++;
	}
}

void printQuery(String queryResult) {
	counter = 1;
	std::cout << queryResult << std::endl;
}

XPath::XPath(XMLDocument& document) : curDocument(document)
{
	
}

void XPath::execute(const String query)
{
	if (query == "count" || query == "Count") {
		printQuery(count());
		
		return;
	}

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
		std::cout << "Invalid query!" << std::endl << std::endl;
	}
}

unsigned XPath::count()
{
	return counter;
}