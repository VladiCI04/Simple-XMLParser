#include "Parent.h"

Parent::Parent() = default;

Parent::Parent(const String tag, const String attribute, const String attributeValue, const String value) : tag(tag), attribute(attribute), attributeValue(attributeValue), value(value)
{

}

void Parent::addChild(const Child& child)
{
    children.push(child);
}

void Parent::setValue(String value)
{
	this->value = value;
}

Queue<Child>& Parent::getChildren()
{
	return children;
}

String Parent::getTag() const
{
	return tag;
}

String Parent::getAttribute() const
{
	return attribute;
}

String Parent::getAttributeValue() const
{
	return attributeValue;
}

String Parent::getValue() const
{
	return value;
}
