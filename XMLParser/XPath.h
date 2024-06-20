#pragma once
#include "XMLDocument.h"

class XPath {
private:
	XMLDocument& curDocument;

public:
	XPath() = default;
	XPath(XMLDocument& document);

	void execute(const String query);
	unsigned count();
};