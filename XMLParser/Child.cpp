#include "Child.h"

Child::Child() = default;

Child::Child(const String key, const String id, const String idValue, const String value) : key(key), id(id), idValue(idValue), value(value)
{

}

void Child::setKey(String key)
{
    this->key = key;
}

void Child::setId(String id)
{
    this->key = key;
}

void Child::setIdValue(String idValue)
{
    this->idValue = idValue;
}

void Child::setValue(String value)
{
    this->value = value;
}

String Child::getKey() const
{
    return key;
}

String Child::getId() const
{
    return id;
}

String Child::getIdValue() const
{
    return idValue;
}

String Child::getValue() const
{
    return value;
}