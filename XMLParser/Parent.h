#pragma once
#include "Queue.hpp"
#include "Child.h"

class Parent {
private:
	String tag = nullptr;
	String attribute = nullptr;
	String attributeValue = nullptr;
	String value = nullptr;
	Queue<Child> children;

public:
	Parent();
	Parent(const String tag, const String attribute, const String attributeValue, const String value);

	void addChild(const Child& child);

	void setValue(String value);

	Queue<Child>& getChildren();
	String getTag() const;
	String getAttribute() const;
	String getAttributeValue() const;
	String getValue() const;
};