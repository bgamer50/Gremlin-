#ifndef VERTEX_H
#define VERTEX_H

#include <string>

class Vertex {
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
};

#endif