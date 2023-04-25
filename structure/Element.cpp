#include "structure/Element.h"
#include "Property.h"

/*
	Return the property with
	the given key.  If no such property exists,
	throws an exception.

	Default implementation: Get the value by
	calling property().
*/
boost::any Element::value(std::string key) {
	return this->property(key)->value();
}

/*
	Return the values of all properties
	of this Element.

	Default implementation: Get the values by
	calling properties().
*/
std::vector<boost::any> Element::values(std::vector<std::string> keys) {
	std::vector<Property*> props = this->properties(keys);
	size_t sz = props.size();

	std::vector<boost::any> vals(sz);
	for(int k = 0; k < sz; ++k) vals[k] = props[k]->value();
	return vals;
}
