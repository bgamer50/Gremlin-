#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <vector>
#include "VertexProperty.h"
#include "Element.h"

class Vertex : public Element {
public:
	/*
		Create a new Vertex; does nothing since
		Vertex is just an interface
	*/
	Vertex(){};

	/*
		Return a pointer to the Graph's unique 
		Vertex id for this Vertex.
	*/
	virtual void const* id() = 0;

	/*
		Return a pointer to the Graph's label
		for this Vertex.  If this Vertex does
		not have a label, return NULL.
	*/
	virtual std::string const* label() = 0;

	/*
		Get the property corresponding to the given
		key.
	*/
	virtual VertexProperty<void*>* property(std::string key) = 0;

	/*
		Set the property corresponding to the given
		key assuming the given cardinality.
	*/
	virtual VertexProperty<void*>* property(Cardinality cardinality, std::string key, void* value) = 0;

	/*
		Set the property corresponding to the given
		key.
	*/
	virtual VertexProperty<void*>* property(std::string key, void* value) = 0;
};

#endif