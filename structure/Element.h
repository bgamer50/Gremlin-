#ifndef ELEMENT_H
#define ELEMENT_H
#include <boost/any.hpp>
class Graph;

class Element {
	virtual boost::any id() = 0;
	virtual std::string label() = 0;
	virtual Graph* getGraph() = 0;
};

#include "structure/Graph.h"

#endif