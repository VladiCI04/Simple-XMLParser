#pragma once
#include "Root.h"

class XMLDocument {
private:
	Queue<Root> roots;

public:
	void parseXML(const char* content);
	void saveToFile(const char* fileName);
	void print();
	void close();

	void select(String id, String key);
	void set(String id, String key, String value);

	Queue<String> operator/(const String query);
	String operator[](const String query);
	Queue<String> id(const String query);
	Queue<String> operator=(const String query);
};