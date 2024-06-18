#pragma once
#include "XMLDocument.h"

class XPath {
private:
	XMLDocument& curDocument;

	void select(const String id, const String key);

public:
	XPath() = default;
	XPath(XMLDocument& document);

	void execute(const String query);
	unsigned count();
};