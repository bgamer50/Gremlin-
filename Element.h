#ifndef ELEMENT_H
#define ELEMENT_H
#include <boost/any.hpp>

class Element {
	virtual boost::any id() = 0;
	virtual std::string label() = 0;
};

#endif