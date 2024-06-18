#pragma once
#include "XMLDocument.h"

class XPath {
private:
	XMLDocument curDocument;

public:
	XPath(XMLDocument& document);

	void execute(const String query);
	unsigned count();
};