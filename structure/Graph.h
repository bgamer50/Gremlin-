#pragma once

#include <vector>

#include "structure/Edge.h"
#include "structure/Vertex.h"
#include "maelstrom/storage/datatype.h"

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

			virtual maelstrom::dtype_t get_vertex_dtype() = 0;
			virtual maelstrom::dtype_t get_edge_dtype() = 0;
	};
	
}

#include "traversal/GraphTraversalSource.h"