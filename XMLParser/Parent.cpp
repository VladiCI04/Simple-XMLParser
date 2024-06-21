#include "Parent.h"

Parent::Parent() = default;

Parent::Parent(const String key, const String id, const String idValue) : key(key), id(id), idValue(idValue)
{

}

void Parent::addChild(const Child& child)
{
    children.pushBack(child);
}

Vector<Child>& Parent::getChildren()
{
	return children;
}

String Parent::getKey() const
{
	return key;
}

String Parent::getId() const
{
	return id;
}

String Parent::getIdValue() const
{
	return idValue;
}