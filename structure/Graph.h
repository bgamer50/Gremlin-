#pragma once

#include <vector>

#include "structure/Edge.h"
#include "structure/Vertex.h"
#include "maelstrom/storage/datatype.h"
#include "maelstrom/containers/vector.h"

namespace gremlinxx {

	class GraphTraversalSource;

	class Graph {
		public:
			Graph(){}
			virtual GraphTraversalSource* traversal() = 0;

			/**
			 * Returns a copy of this Graph's vertices.
			 **/
			virtual std::vector<Vertex*> vertices() = 0;

			/**
			 * Returns a copy of this Graph's edges.
			**/
			virtual std::vector<Edge*> edges() = 0;

			virtual Vertex* add_vertex(std::string label) = 0;
			virtual Vertex* add_vertex() = 0;
			virtual Edge* add_edge(Vertex* from_vertex, Vertex* to_vertex, std::string label) = 0;

			/*
				Sets the vertex properties of the given vertices to the given values.
			*/
			virtual void setVertexProperties(std::string property_name, maelstrom::vector& vertices, maelstrom::vector& property_values) = 0;

			/*
				Gets the vertex properties of the given vertices.
				Returns a pair where the first vector consists of the vertices that had this property
				and the second vector consists of the property values of those vertices.

				If return_values is true, the values are returned.
				If return_values is false, an empty vector is returned in place of the values.
			*/
			virtual std::pair<maelstrom::vector, maelstrom::vector> getVertexProperties(std::string property_name, maelstrom::vector& vertices, bool return_values=true) = 0;

			virtual maelstrom::dtype_t get_vertex_dtype() = 0;
			virtual maelstrom::dtype_t get_edge_dtype() = 0;
	};
	
}

#include "traversal/GraphTraversalSource.h"