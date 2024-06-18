#pragma once
#include "Root.h"

class XMLDocument {
private:
	Queue<Root> roots;

public:
	void parseXML(const char* content);

	Queue<String> operator/(const String query);
	String operator[](const String query);
	Queue<String> id(const String query);
	Queue<String> operator=(const String query);
};