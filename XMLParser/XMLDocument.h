#pragma once
#include "HelperFunctions.h"

class XMLDocument : private HelperFunctions {
private:
	Vector<Parent> roots;

public:
	void parseXML(const char* content);
	void saveToFile(const char* filePath, const char* fileName);
	void print();
	void close();

	void select(const String id, const String key);
	void set(const String id, const String key, const String value);
	void children(const String id);
	void child(const String id, const String n);
	void text(const String id);
	void deleted(const String id, const String key);
	void newChild(const String id, const String key);

	Vector<String> operator/(const String query);
	String operator[](const String query);
	Vector<String> id(const String query);
	Vector<String> operator=(const String query);
};