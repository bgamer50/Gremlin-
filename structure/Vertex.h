#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <vector>
#include <boost/any.hpp>
#include "structure/Property.h"
#include "structure/VertexProperty.h"
#include "structure/Element.h"
#include "structure/Direction.h"

class Graph;

class Vertex : public Element {
public:
	/*
		Create a new Vertex; does nothing since
		Vertex is just an interface
	*/
	Vertex(){};

	/*
		Get the Graph this Vertex belongs to.
	*/
	virtual Graph* getGraph() = 0;

	/*
		Return a pointer to the Graph's unique 
		Vertex id for this Vertex.
	*/
	virtual boost::any id() = 0;

	/*
		Return the label of this Vertex.
	*/
	virtual std::string label() = 0;

	/*
		Get the edges for this Vertex in the given direction.
	*/
	virtual std::vector<Edge*> edges(Direction dir) = 0;

	/*
		Get the property corresponding to the given
		key.
	*/
	virtual Property* property(std::string key) = 0;

	/*
		Set the property corresponding to the given
		key assuming the given cardinality.
	*/
	virtual Property* property(Cardinality cardinality, std::string key, boost::any& value) = 0;

	/*
		Return the property
		with the given property value.  If
		no such property exists, returns
		an empty Property object.
	*/
	virtual Property* property(std::string key, boost::any value) {
		return this->property(SINGLE, key, value);
	}

	/*
		Return a vector of properties 
		on this Element.
		Note: should not have a default implementation as backends may or not support
		multiproperties and need to handle these appropriately.
	*/
	virtual std::vector<Property*> properties(std::vector<std::string> keys) = 0;
};

#include "structure/Graph.h"

#endif