#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <vector>
#include <boost/any.hpp>
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
		Return a pointer to the Graph's label
		for this Vertex.  If this Vertex does
		not have a label, return NULL.
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
	virtual VertexProperty<boost::any>* property(std::string key) = 0;

	/*
		Set the property corresponding to the given
		key assuming the given cardinality.
	*/
	virtual VertexProperty<boost::any>* property(Cardinality cardinality, std::string key, boost::any& value) = 0;

	/*
		Set the property corresponding to the given
		key.
	*/
	virtual VertexProperty<boost::any>* property(std::string key, boost::any& value) = 0;
};

#include "structure/Graph.h"

#endif