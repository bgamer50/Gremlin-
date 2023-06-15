#pragma once

#include <stdlib.h>
#include <string>
#include <utility>

#include "structure/Element.h"
#include "structure/Graph.h"
#include "structure/VertexProperty.h"

namespace gremlinxx {

	class Vertex;

	class Edge : public Element {
	public:
		/*
			Create a new Edge; does nothing
			since Edge is just an interface.
		*/
		Edge() {};

		/*
			Get the Graph this Edge belongs to.
		*/
		virtual Graph* getGraph() = 0;

		/*
			Return a pointer to the Graph's unique 
			Edge id for this Edge.
		*/
		virtual boost::any id() = 0;

		/*
			Return a pointer to the Graph's label
			for this Edge.
		*/
		virtual std::string label() = 0;

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

			Default Implementation: Call outV()
			and inV(), and return them as a Pair.
		*/
		virtual std::pair<Vertex*, Vertex*> bothV();

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
		virtual Property* property(std::string key, boost::any& value) = 0;

		/*
			Return a vector of
			properties on this Element.
		*/
		virtual std::vector<Property*> properties(std::vector<std::string> keys) = 0;
	};

}