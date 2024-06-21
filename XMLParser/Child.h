#pragma once
#include "String.h"

class Child {
private:
	String key = nullptr;
	String id = nullptr;
	String idValue = nullptr;
	String value = nullptr;

public:
	Child();
	Child(const String key, const String id, const String idValue, const String value);

	void setKey(String key);
	void setId(String id);
	void setIdValue(String idValue);
	void setValue(String value);

	String getKey() const;
	String getId() const;
	String getIdValue() const;
	String getValue() const;
};