#pragma once
#include "String.h"

class Child {
private:
	String tag = nullptr;
	String attribute = nullptr;
	String attributeValue = nullptr;
	String value = nullptr;

public:
	Child();
	Child(const String tag, const String attribute, const String attributeValue, const String value);

	void setValue(String value);

	String getTag() const;
	String getAttribute() const;
	String getAttributeValue() const;
	String getValue() const;
};