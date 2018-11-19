#ifndef EDGE_H
#define EDGE_H

#include <stdlib.h>
#include <string>
#include "Vertex.h"
#include "Element.h"

class Edge : public Element {
public:
	/*
		Create a new Edge; does nothing
		since Edge is just an interface.
	*/
	Edge() {};

	/*
		Return a pointer to the Graph's unique 
		Edge id for this Edge.
	*/
	virtual void const* id() = 0;

	/*
		Return a pointer to the Graph's label
		for this Edge.
	*/
	virtual std::string const* label() = 0;

	/*
		Return the out-Vertex of this Edge
	*/
	virtual Vertex* outV() = 0;

	/*
		Return the in-Vertex of this Edge
	*/
	virtual Vertex* inV() = 0;

	/*
		Return the pair of Vertices related
		to this edge as an (outV, inV) pair.
	*/
	virtual Vertex** bothV() {
		Vertex** vertices = (Vertex**)malloc(sizeof(Vertex*) * 2);
		vertices[0] = outV();
		vertices[1] = inV();
		return vertices;
	}
};

#endif