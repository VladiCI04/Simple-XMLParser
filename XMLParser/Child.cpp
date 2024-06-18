#include "Child.h"

Child::Child() = default;

Child::Child(const String tag, const String attribute, const String attributeValue, const String value) : tag(tag), attribute(attribute), attributeValue(attributeValue), value(value)
{

}

String Child::getTag() const
{
    return tag;
}

String Child::getAttribute() const
{
    return attribute;
}

String Child::getAttributeValue() const
{
    return attributeValue;
}

String Child::getValue() const
{
    return value;
}