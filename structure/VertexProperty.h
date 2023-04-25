#pragma once

#include <set>
#include <exception>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <functional>
#include <boost/any.hpp>
#include "Property.h"

enum Cardinality {SINGLE, LIST, SET};

class VertexProperty: public Property {
	private:
		// kv pairs
		std::unordered_map<std::string, Property> my_values;
	public:
		VertexProperty(std::string new_key, boost::any new_value)
		: Property(new_key, new_value) {}

		VertexProperty(std::string new_key, boost::any new_value, std::unordered_map<std::string, Property>& new_values)
		: Property(new_key, new_value) {
			my_values = new_values;
		}

		virtual std::unordered_map<std::string, Property> values() {
			return my_values;
		}
};
