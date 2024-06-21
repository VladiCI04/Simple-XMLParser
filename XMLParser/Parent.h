#pragma once
#include "Child.h"
#include "Vector.hpp"

class Parent {
private:
	String key = nullptr;
	String id = nullptr;
	String idValue = nullptr;
	Vector<Child> children;

public:
	Parent();
	Parent(const String key, const String id, const String idValue);

	void addChild(const Child& child);

	void setId(const String id);
	void setIdValue(const String idValue);

	Vector<Child>& getChildren();
	String getKey() const;
	String getId() const;
	String getIdValue() const;
};