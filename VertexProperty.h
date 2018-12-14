#ifndef VERTEX_PROPERTY_H
#define VERTEX_PROPERTY_H

#include <set>
#include <exception>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <functional>
#include <boost/any.hpp>
#include "Property.h"

enum Cardinality {SINGLE, LIST, SET};

template<typename T>
class VertexProperty {
	private:
		std::string my_key;
		std::vector<T>* my_values;
	public:
		VertexProperty(Cardinality card, std::string new_key, std::vector<T> new_values, std::function<bool(boost::any, boost::any)> comparator) {
			this->my_key = new_key;

			if(card == SET) {
				std::set<T>* s = new std::set<T>();
				for_each(new_values.begin(), new_values.end(), [&s](T t){s->insert(t);});
				my_values = new std::vector<T>(s->begin(), s->end());
				delete s;
			}
			else if(card == LIST) {
				my_values = new std::vector<T>(new_values.begin(), new_values.end());
			}
			else {
				if(new_values.size() > 1) throw std::runtime_error("Specified single Cardinality but provided a vector of size > 1!");
				my_values = new std::vector<T>(new_values.begin(), new_values.end());	
			}
		}

		VertexProperty(Cardinality card, std::string new_key, std::vector<T> new_values) {
			return VertexProperty::VertexProperty(card, new_key, new_values, [](){return false;};);
		}

		std::string key() {
			return my_key;
		}

		std::vector<T> values() {
			return *my_values;
		}

		T value() {
			return my_values->at(0);
		}
};

#endif