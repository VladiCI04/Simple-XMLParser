#pragma once
#include "HelperFunctions.h"

class XMLDocument : private HelperFunctions {
private:
	Vector<Parent> roots;

public:
	void parseXML(const char* content);
	void saveToFile(const char* fileName);
	void print();
	void close();

	void select(const String id, const String key);
	void set(const String id, const String key, const String value);
	void children(const String id);
	void child(const String id, const String n);


	Vector<String> operator/(const String query);
	String operator[](const String query);
	Vector<String> id(const String query);
	Vector<String> operator=(const String query);
};