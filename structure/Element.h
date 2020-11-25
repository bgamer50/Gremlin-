#ifndef ELEMENT_H
#define ELEMENT_H
#include <boost/any.hpp>
class Graph;
class Property;

/*
	The Element Interface

	Note: Returned pointers to properties are allowed to be
	either copies or references to the actual property on
	the Element.  This is left up to the backend.
*/
class Element {
	/*
		Return the id of this Element.
	*/
	virtual boost::any id() = 0;

	/*
		Return the label of this Element.
	*/
	virtual std::string label() = 0;
	
	/*
		Return a pointer to the Graph that
		this Element belongs to.
	*/
	virtual Graph* getGraph() = 0;
	
	/*
		Return the property
		with the given property key.  If
		no such property exists, returns
		an empty Property object.
	*/
	virtual Property* property(std::string key) = 0;

	/*
		Return the property
		with the given property value.  If
		no such property exists, returns
		an empty Property object.
	*/
	virtual Property* property(std::string key, boost::any value) = 0;

	/*
		Return a vector of
		properties on this Element.
	*/
	virtual std::vector<Property*> properties(std::vector<std::string> keys) = 0;

	/*
		Return the property with
		the given key.  If no such property exists,
		throws an exception.

		Default implementation: Get the value by
		calling property().
	*/
	virtual boost::any value(std::string key);

	/*
		Return the values of all properties
		of this Element.

		Default implementation: Get the values by
		calling properties().
	*/
	virtual std::vector<boost::any> values(std::vector<std::string> keys);
	
	/*
		Permanently removes this Element from
		the Graph.

		Default implementation: Throws an exception.
	*/
	virtual void remove() {
		throw std::runtime_error("Element removal not supported!");
	}
};

#include "structure/Graph.h"
#include "structure/Property.h"

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

#endif